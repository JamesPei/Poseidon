//
// Created by 裴磊 on 2018/10/27.
//

#ifndef POSEIDON_GRAPH_H
#define POSEIDON_GRAPH_H

#include <vector>
#include <iostream>

class Graph{
    /*
     * 以前向星方式表示图
     * n:点
     * m:边
     */
public:
    typedef std::vector<int> VI;
    VI info, next, to;
    Graph(int n=0, int m=0): to(n), next(m){
        info.resize(n);
        next.reserve(m);
        to.reserve(m);
    }

    int edge_size(){    //返回边数量
        return to.size();
    }

    int vertex_size(){  //返回值为最大点的编号+1
        return info.size();
    }

    void expand(int i){
        if(info.size() < i+1)
            info.resize(i+1);
    }

    void add(int i, int j){     //添加一条i到j的边
        expand(i), expand(j);
        to.push_back(j);
        next.push_back(info[i]);
        info[i] = to.size()-1;
    }

    void del_back(){        // 删除最后一次添加的边
        int i;
        for(i=0; i<info.size(); i++)
            if(info[i]==to.size() - 1){
                info[i] = next.back();
                break;
            }
        to.pop_back();
        next.pop_back();
    }

    void clear(){           // 清空图类
        info.clear();
        next.resize(0);
        to.resize(0);
    }

    void print(){
        std::cout<<"info:"<<"\n";
        for(int i: info)
            std::cout<<i<<" ";
        std::cout<<std::endl;

        std::cout<<"next:"<<"\n";
        for(int i: next)
            std::cout<<i<<" ";
        std::cout<<std::endl;

        std::cout<<"to:"<<"\n";
        for(int i: to)
            std::cout<<i<<" ";
        std::cout<<std::endl;
    }

};
#endif //POSEIDON_GRAPH_H
