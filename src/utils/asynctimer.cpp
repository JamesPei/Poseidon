#include <Posiedon/utils/asynctimer.h>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <errno.h>

struct TimerHdl{
    int32_t tm_fd_;
    std::function<void(void*)> cbk_;
    void* param_;
};

class AsyncTimer::AsyncTimerService{
    friend AsyncTimer;

    static const uint32_t kTimerMax = 4096;
    int32_t epoll_fd_;
    std::mutex timer_hdls_mtx_;
    std::map<uint32_t, std::shared_ptr<TimerHdl> > timer_hdls_;
    uint32_t timer_hdls_idx_;

    std::shared_ptr<std::thread> timer_thread_;
    bool timer_thread_running_;

public:
    AsyncTimerService():timer_hdls_idx_(0){
	    epoll_fd_ = epoll_create1(EPOLL_CLOEXEC);
        if(epoll_fd_<0){
            return;
        }
        timer_thread_running_ = true;
        timer_thread_ = std::make_shared<std::thread>(std::bind(&AsyncTimerService::TimerRoot, this));
    }

    ~AsyncTimerService(){
        char acTmp[4]{0};
        int32_t rtn = write(fd_ctl_[1], acTmp, 4);
        (void)rtn;

        timer_thread_running_ = false;
        if(timer_thread_ && timer_thread_->joinable()){
            timer_thread_->join();
        }

        close(epoll_fd_);
        for(auto it = timer_hdls_.begin(); it!=timer_hdls_.end();){
            (void)close(it->first);
            it = timer_hdls_.erase(it);
        }
    }

    void TimerRoot(void){
#define MAX_EVENTS 1024
        int32_t num_fd;
        ssize_t s;
        struct epoll_event events[MAX_EVENTS];

        while (timer_thread_running_){
            // On success, epoll_wait() returns the number of file descriptors ready
            // for the requested I/O, or zero if no file descriptor became
            // ready during the requested timeout milliseconds.
            num_fd = epoll_wait(epoll_fd_, events, MAX_EVENTS, -1);
            if(num_fd < 0){
                if(errno == EINTR){
                    continue;
                }
                break;
            }

            for(int n=0; n < num_fd; ++n){
                TimerHdl* hdl = (TimerHdl*)events[n].data.ptr;
                uint64_t exp;

                s = read(hdl->tm_fd_, &exp, sizeof(uint64_t));
                if(s == sizeof(uint64_t) && (hdl->cbk_)) {
                    hdl->cbk_(hdl->param_);
                }else{
                    return;
                }
            }
        }
    }
};

#if __cplusplus>=201402L
AsyncTimer::AsyncTimer(){
    async_timer_service = std::make_unique<AsyncTImerService>();
}
#else
AsyncTimer::AsyncTimer():async_timer_service(new AsyncTimerService){};
#endif

AsyncTimer::~AsyncTimer(){};

TIMER_FD AsyncTimer::add_task(uint32_t first_alarm_ms, uint64_t duration_ms, std::function<void(void*)> callback, void* param){
    if(!async_timer_service->timer_thread_running_){
	    return -EBADF;
    }

    {
        std::lock_guard<std::mutex> locker(async_timer_service->timer_hdls_mtx_);
        if(async_timer_service->kTimerMax < aysnc_timer_service->timer_hdls_.size()){
            return -ENOMEM;
        }
    }

    int32_t rtn;
    struct timespec now;
    /* 
    int clock_gettime(clockid_t clk_id,struct timespec *tp);
    基于Linux C语言的时间函数,可以用于计算精度和纳秒
    clk_id:检索和设置的clk_id指定的时钟时间,包括:
        CLOCK_REALTIME:系统实时时间,随系统实时时间改变而改变,即从UTC1970-1-1 0:0:0开始计时,
        中间时刻如果系统时间被用户改成其他,则对应的时间相应改变。
        CLOCK_MONOTONIC:不可设置的时钟，不受系统时钟中的非连续改变的影响。
　　     CLOCK_PROCESS_CPUTIME_ID:本进程到当前代码系统CPU花费的时间。
        CLOCK_THREAD_CPUTIME_ID:本线程到当前代码系统CPU花费的时间
    */ 
    rtn = clock_gettime(CLOCK_MONOTONIC, &now);
    if(0!=rtn){
        return -EINVAL;
    }

    // int timerfd_create(int clockid, int flags);
    // 创建定时器对象，返回一个指向该定时器的fd
    // timerfd_create把时间变成了一个文件描述符，该“文件”在定时器超时的那一刻变得可读，这样可以
    // 方便地融入到select/poll/epoll框架中，用统一的方式来处理IO事件和超时事件
    TIMER_FD tm_fd = timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC | TFD_NONBLOCK);
    if(tm_fd<0){
        return -EINVAL;
    }

    struct itimerspec cfg;
    // it_value:首次超时时间，需要填写从clock_gettime获取的时间，并加上要超时的时间
    cfg.it_value.tv_sec = now.tv_sec + first_alarm_ms/1000;
    cfg.it_value.tv_nsec = (now.tv_nsec + first_alarm_ms * 1000000) % 1000000000;
    // it_interval:后续周期性超时时间,不为0则表示是周期性定时器，大于0是周期性的时间
    if(duration_ms){
        cfg.it_interval.tv_sec  = durtion_ms / 1000;
        cfg.it_interval.tv_nsec = durtion_ms * 1000000 % 1000000000;
    }else{
        cfg.it_interval.tv_sec  = 0;
        cfg.it_interval.tv_nsec = 0;
    }

    // int timerfd_settime(int fd, int flags, const struct itimerspec *new_value, struct itimerspec *old_value);
    // 用于启动或停止绑定到fd的定时器
    // flags:  
    //  (1)0，启动一个相对定时器，基于当前时间 + new_value.it_value指定的相对定时值
    //  (2)TFD_TIMER_ABSTIME，启动一个绝对定时器（由new_value.it_value指定定时值）
    rtn = timerfd_settime(tm_fd, TFD_TIMER_ABSTIME, &cfg, NULL);
    if(0!=rtn){
        close(tm_fd);
        return -EFAULT;
    }

    {
        std::lock_guard<std::mutex> guard(async_timer_service->timer_hdls_mtx_);
        ++async_timer_service->timer_hdls_idx_;
        async_timer_service->timer_hdls_[hdl->tm_fd_] = hdl;
    }
    return tm_fd;
}

bool AsyncTimer::remove_task(TIMER_FD timer_fd){
    int rtn = epoll_ctl(async_timer_service->epoll_fd_, EPOLL_CTL_DEL, timer_fd, nullptr);
    if(0!=rtn){
        close(timer_fd);
        return false;
    }
    return true;
}

bool AsyncTimer::modify_task(TIMER_FD timer_fd, uint32_t first_alarm_ms, uint64_t durtion_ms, 
    std::function<void(void*)> callback, void* param){
    int32_t rtn;
    struct timespec now;
    rtn = clock_gettime(CLOCK_MONOTONIC, &now);
    if(0!=rtn){
        return -EINVAL;
    }

    struct itimerspec cfg;
    cfg.it_value.tv_sec  = now.tv_sec + first_alarm_ms / 1000;
    cfg.it_value.tv_nsec = (now.tv_nsec + first_alarm_ms * 1000000) % 1000000000;
    if (durtion_ms){
        cfg.it_interval.tv_sec  = durtion_ms / 1000;
        cfg.it_interval.tv_nsec = durtion_ms * 1000000 % 1000000000;
    }else{
        cfg.it_interval.tv_sec  = 0;
        cfg.it_interval.tv_nsec = 0;
    }

    rtn = timerfd_settime(timer_fd, TFD_TIMER_ABSTIME, &cfg, NULL);
    if (0 != rtn){
        return false;
    }

    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = EPOLLIN | EPOLLET;
    std::shared_ptr<TimerHdl> hdl = async_timer_service->timer_hdls_[timer_fd];
    std::lock_guard<std::mutex> locker(async_timer_service->timer_hdls_mtx_);
    hdl_>cbk_ = callback;
    hdl_>param_ = param;

    ev.data.ptr = (void*)hdl.get();
    rtn = epoll_ctl(aysnc_timer_service->epoll_fd_, EPOLL_CTL_MOD, timer_fd, &ev);
    if(0!=rtn){
        close(timer_fd);
        return false;
    }
    return true;
}