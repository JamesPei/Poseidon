//
// Created by 裴磊 on 2018/11/21.
//
#include <vector>

using std::vector;

int N=100,M=300;
int fa[100];

struct edge{
    int x, y, w;
    edge(int x=0,int y=0,int w=0): x(x), y(y), w(w){}
};

int getfather(int x){
    if(x==fa[x]) return x;
    else return fa[x]==getfather(fa[x]);
}

int kruscal(){
    int cnt=N;
    for(int i=1; i<=N; ++i) fa[i]=i;
    
}