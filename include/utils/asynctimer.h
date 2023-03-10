#pragma once

#include <memory>
#include <functional>
#include <mutex>
#include <map>
#include <iostream>

static std::mutex mtx;

typedef int32_t TIMER_FD;

class AsyncTimer{
public:
    static std::shared_ptr<AsyncTimer> Instance(){
	    std::lock_guard<std::mutex> locker(mtx);
	    static std::shared_ptr<AsyncTimer> instance = std::make_shared<AsyncTimer>();
	    return instance;
    };

    ~AsyncTimer();

    TIMER_FD add_task(uint32_t first_alarm_ms, uint64_t duration_ms, std::function<void(void*)> callback, void* param);
    bool remove_task(TIMER_FD timer_fd);
    bool modify_task(TIMER_FD timer_fd, uint32_t first_alarm_ms, uint64_t duration_ms, std::function<void(void*)> callback, void* param);

private:
    AsyncTimer();
    AsyncTimer(const AsyncTimer&) = delete;
    AsyncTimer& operator=(const AsyncTimer&) = delete;

    class AsyncTimerService;
    std::unique_ptr<AsyncTimerService> async_timer_service;
};
