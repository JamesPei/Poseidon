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
        next.reserve(m);
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

std::shared_ptr<std::vector<int>> toposort(Graph g);
void dijkstra();
void floyd_warshall();

#endif //POSEIDON_GRAPH_H
