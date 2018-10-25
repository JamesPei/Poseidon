//
// Created by 裴磊 on 2018/10/25.
//
#include <cstring>
#include <vector>
#include <cmath>
#include "primenumber.h"

using std::vector;

bool valid[MAXN];

vector<int> getPrime(int n){
    /*
     * find all prime number from 2 to n
     * Time complexity:O(N)
     * return: all prime number from 2 to n
     */
    //Sets the first num bytes of the block of memory pointed by ptr to the specified value
    int total = 0;
    vector<int> ans(n, 0);
    memset(valid, true, sizeof(valid));
    for(int i=2; i<=n; i++){
        if(valid[i]){
            total++;
            ans[total]=i;
        }
        for(int j=1; ((j<=total) && (i*ans[j]<=n)); j++){
            valid[i*ans[j]] = false;
            if(i%ans[j] == 0) break;
        }
    }
    for(size_t i = ans.size(); i>0; --i){
        if(ans[i]==0) ans.pop_back();
        else break;
    }
    return ans;
}

bool isPrime(int n){
    /*
     * is N a prime number?
     * Time complexity:O(logN)
     * return: bool
     */

}

void prime_factor_Decomposition(int n){
    /*
     * Time complexity:O(sqrt(n))
     * 
     */
    int temp, i, now, tot;
    vector<int> a, b;
    temp=(int)((double)sqrt(n)+1);
    tot = 0;
    now = n;
    for(i=2; i<=temp; ++i)
        if(now%i==0){
            a[++tot]=i;
            b[tot]=0;
            while(now%i==0){
                ++b[tot];
                now/=i;
            }
        }
    if(now!=1){
        a[++tot] = now;
        b[tot]=1;
    }
}