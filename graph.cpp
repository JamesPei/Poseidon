//
// Created by 裴磊 on 2018/10/28.
//
#include <vector>
#include <queue>
#include <iostream>
#include <map>
#include <memory>
#include "graph.h"

using std::vector; using std::queue; using std::map; using std::shared_ptr; using std::make_shared;


vector<int> toposort(Graph g){
    /*
     * 拓扑排序
     * 复杂度O(|V|+|E|)
     */
    map<int, vector<int>> graph = g.graph;
    map<int, vector<int>>::iterator it;
    int n = graph.size()+1;
    int du[n];
    vector<int> L;
    memset(du, 0 , sizeof(du));
    for(it=graph.begin(); it!=graph.end(); ++it)
        for(int j:it->second)
            du[j]++;
    int tot = 0;
    queue<int> Q;       // 适配器，FIFO queue
    for(int i=0; i<n; i++)
        if(!du[i]) Q.push(i);
    while(!Q.empty()){
        int x = Q.front(); Q.pop();
        L[tot++] = x;
        for(int j=0; j<graph[x].size(); j++){
            int t = graph[x][j];
            du[t]--;
            if(!du[t])
                Q.push(t);
        }
    }

    return L;
}