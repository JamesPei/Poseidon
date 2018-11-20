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
using std::max;


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

void dijkstra(vector<vector<int>> g){
    /*
     * 寻找单源最短路径（图中不能有负权的边）
     * 复杂度O(N**2)
     * n:图中的点数
     */
    size_t n=g.size();
    int dis[n];         // dis:全局变量dis[i]表示节点1到i的最短距离，g[i][j]表示i到j之间边的距离
    bool v[n];
    for(int i=1; i<=n; ++i) dis[i] = INF;
    dis[1]=0;
    memset(v, 0, sizeof v);
    for(int i=1; i<=n; ++i){
        int mark=-1, mindis=INF;
        for(int j=1; j<=n; ++j)
            if(!v[j]&&dis[j]<mindis){
                mindis=dis[j];
                mark = j;
            }
        v[mark]=1;
        for(int j=1; j<=n; ++j)
            if(!v[j])
                dis[j]=min(dis[j], dis[mark]+g[mark][j]);
    }
}

void floyd_warshall(vector<vector<int>> g){
    /*
     * 复杂度O(N**3)
     */
    int N=g.size();
    for(int k=1; k<=N; ++k)
        for(int i=1; i<=N; ++i)
            for(int j=1; j<=N; ++j)
                g[i][j]=min(g[i][j], g[i][k]+g[k][j]);
}

int dag_path(int N, int x){
    int g[N][N], f[N], n;
    bool done[N];
    if(done[x]) return f[x];
    for(int i=1; i<=n; ++i)
        if(g[i][x])
            f[x]=max(f[x], f[i]+g[i][x]);
    done[x]=true;
    return f[x];
}