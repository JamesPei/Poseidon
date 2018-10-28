//
// Created by 裴磊 on 2018/10/28.
//
#include <vector>
#include <queue>
#include "graph.h"

using std::vector; using std::queue;

const int maxn = 100000;
vector<int> g[maxn];
int du[maxn], n, L[maxn];

int* toposort(){
    /*
     * 拓扑排序
     * 复杂度O(|V|+|E|)
     */
    memset(du, 0, sizeof(du));
    for(int i=0; i<n; i++)
        for(int j=0; j<g[i].size(); j++)
            du[g[i][j]]++;
    int tot = 0;
    queue<int> Q;       // 适配器，FIFO queue
    for(int i=0; i<n; i++)
        if(!du[i]) Q.push(i);
    while(!Q.empty()){
        int x = Q.front(); Q.pop();
        L[tot++] = x;
        for(int j=0; j<g[x].size(); j++){
            int t = g[x][j];
            du[t]--;
            if(!du[t])
                Q.push(t);
        }
    }
    int *res = L;
    return res;
}