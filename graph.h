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
        //Resizes the container so that it contains n elements.
        //If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them).
        //If n is greater than the current container size, the content is expanded by inserting at the end as many elements
        //as needed to reach a size of n. If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.
        //If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
        //Notice that this function changes the actual content of the container by inserting or erasing elements from it.
        next.reserve(m);
        //Requests that the vector capacity be at least enough to contain n elements, If n is greater than the current
        //vector capacity, the function causes the container to reallocate its storage increasing its capacity to n (or greater).
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
                //Returns a reference to the last element in the vector. Unlike member vector::end, which returns an
                //iterator just past this element, this function returns a direct reference
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
