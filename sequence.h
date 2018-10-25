//
// Created by 裴磊 on 2018/10/24.
//

#ifndef POSEIDON_SEQUENCE_H
#define POSEIDON_SEQUENCE_H

#include "matrix.h"

int clhr(int a[], int b[], int n, int t){
    /*
     * 常系数线性齐次齐次递推，复杂度O((n**3)*log(t))
     * a:常系数数组
     * b:初值数组
     * n:数组大小
     * t:要求解的项数
     * return: 函数在第t项的值ft
     */
    Matrix M, F, E;
    M.clear(), F.clear(), E.clear();
    M.row = M.col = n;
    E.row = E.col = n;
    F.row = n, F.col = 1;
    std::vector<double> v1(n, 0);
    std::vector<std::vector<double>> v(n, v1);
    std::vector<double> v2(1, 0);
    std::vector<std::vector<double>> vf(n, v2);
    M.matrix = E.matrix = v;
    F.matrix = vf;
    for(int i=0; i<n-1; ++i)
        M.matrix[i][i+1] = 1;
    for(int i=0; i<n; ++i){
        M.matrix[n-1][i] = a[i];
        F.matrix[i][0] = b[i];
        E.matrix[i][i] = i;
    }
    if(t<n)
        return F.matrix[t][0];
    for(t -= n-1; t; t/=2){
        if(t & 1)       // 若为奇数
            E = M * E;
        M = M * M;
    }
    F = E * F;
    return F.matrix[n-1][0];
}
#endif //POSEIDON_SEQUENCE_H
