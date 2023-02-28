//
// Created by 裴磊 on 2018/11/21.
//
#include "graph.h"
#define N 500

using std::max;

int g[N][N], f[N], n;
bool done[N];

int dag_path(int x){
    /**
     * 无环图最短路(求出一个DAG从s到t的最短/长路)
     */
    if(done[x]) return f[x];
    for(int i=1; i<=n; ++i)
        if(g[i][x])
            f[x]=max(f[x], dag_path(i)+g[i][x]);
    done[x]=true;
    return f[x];
}

