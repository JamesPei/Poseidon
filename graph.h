//
// Created by 裴磊 on 2018/10/27.
//

#ifndef POSEIDON_GRAPH_H
#define POSEIDON_GRAPH_H

#include <vector>
#include <iostream>
#include <map>

class Graph{
    /*
     * 图的表示方法，包括前向星和邻接集两种方式
     */
public:
    typedef std::vector<int> VI;
    int type;
    VI info, next, to;
    std::map<int, VI> graph;
    Graph(int n=0, int m=0): to(n), next(m){
        type = 1;
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

    Graph(std::map<int, VI> g){
        type = 2;
        graph = g;
    }

    int edge_size(){    //返回边数量
        if(type==1){
            return to.size();
        }else{
            int size=0;
            std::map<int, VI>::iterator it;
            for(it = graph.begin(); it!=graph.end(); ++it){
                size += (it->second).size();
            }
            return size;
        }
    }

    int vertex_size(){  //返回值为最大点的编号+1
        if(type==1)
            return info.size();
        else
            return graph.size();
    }

    void add(int i, int j){     //添加一条i到j的边
        if(type==1){
            expand(i), expand(j);
            to.push_back(j);
            next.push_back(info[i]);
            info[i] = to.size()-1;
        }else{
            graph[i].push_back(j);
        }

    }

    void del_back(){        // 删除最后一次添加的边
        if(type==1){
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
        }else{
            std::cout<<"adjacency list not supported"<<std::endl;
        }
    }

    void clear(){           // 清空图类
        if(type==1){
            info.clear();
            next.resize(0);
            to.resize(0);
        }else{
            graph.clear();
        }
    }

    void print(){
        if(type==1) {
            std::vector<int>::iterator it;
            std::cout << "info:" << "\n";
            for (it = info.begin(); it != info.end(); ++it)
                std::cout << *it << " ";
            std::cout << std::endl;

            std::cout << "next:" << "\n";
            for (it = next.begin(); it != next.end(); ++it)
                std::cout << *it << " ";
            std::cout << std::endl;

            std::cout << "to:" << "\n";
            for (it = to.begin(); it != to.end(); ++it)
                std::cout << *it << " ";
            std::cout << std::endl;
        }else{
            std::map<int, VI>::iterator it;
            for(it = graph.begin(); it!=graph.end(); ++it){
                std::cout<<it->first<<":";
                for(int i:it->second)
                    std::cout<<i<<" ";
                std::cout<<std::endl;
            }
        }
    }

private:
    void expand(int i){
        if(info.size() < i+1)
            info.resize(i+1);
    }
};

bool topsort();
void dijkstra();
void floyd_warshall();

#endif //POSEIDON_GRAPH_H
