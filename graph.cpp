//
// Created by 裴磊 on 2018/10/28.
//
#include <vector>
#include <queue>
#include <iostream>
#include <map>
#include <memory>
#include "graph.h"

using std::vector; using std::queue; using std::map; using std::shared_ptr; using std::make_shared; using std::min;


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
        if(x) L.push_back(x);
        for(int j=0; j<graph[x].size(); j++){
            int t = graph[x][j];
            du[t]--;
            if(!du[t])
                Q.push(t);
        }
    }

    return L;
}

void dijkstra(Graph gr){
    /*
     * 寻找单源最短路径（图中不能有负权的边）
     * 复杂度O(N**2)
     */
    int N = gr.graph.size();     // 点数
    int dis[N], g[N][N];         // dis:全局变量dis[i]表示节点1到i的最短距离，g[i][j]表示i到j之间边的距离
    bool v[N];
    for(int i=1; i<=N; ++i) dis[i] = INF;
    dis[1]=0;
    memset(v, 0, sizeof v);
    for(int i=1; i<=N; ++i){
        int mark=-1, mindis=INF;
        for(int j=1; j<=N; ++j)
            if(!v[j]&&dis[j]<mindis){
                mindis=dis[j];
                mark = j;
            }
        v[mark]=1;
        for(int j=1; j<=N; ++j)
            if(!v[j])
                dis[j]=min(dis[j], dis[mark]+g[mark][j]);
    }
}