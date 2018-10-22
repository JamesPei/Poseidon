//
// Created by James.Pei on 2018/10/20.
//
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include "matrix.h"

using std::cout;
using std::endl;
using std::swap;
using std::vector;

void Matrix::print() {
    for (iter=matrix.begin(); iter!=matrix.end(); iter++){
        vector<double> vec_temp = *iter;
        for (iter2=vec_temp.begin(); iter2!=vec_temp.end(); iter2++){
            cout<<*iter2<<" ";
        }
        cout<<"\n";
    }
    cout<<endl;
}

void Matrix::clear() {
    row=col=0;
    matrix.clear();
}

Matrix Matrix::operator+(const Matrix &b) {
    Matrix tmp;
    tmp.row = row;
    tmp.col = col;
    tmp.matrix = matrix;
    for (int i=0; i<row; ++i)
        for (int j=0; j<col; j++)
            tmp.matrix[i][j] += b.matrix[i][j];
    return tmp;
}

Matrix Matrix::operator-(const Matrix &b) {
    Matrix tmp;
    tmp.row = row;
    tmp.col = col;
    tmp.matrix = matrix;
    for (int i=0; i<row; ++i)
        for (int j=0; j<col; ++j)
            tmp.matrix[i][j] -= b.matrix[i][j];
    return tmp;
}

Matrix Matrix::operator*(const Matrix &b) {
    Matrix tmp;
    tmp.row = row;
    tmp.col = b.col;
    tmp.matrix = vector<vector<double>>(row, vector<double>(b.col, 0));
    for (int i=0; i<row; ++i)
        for (int j=0; j<b.col; ++j)
            for (int k=0; k<col; ++k)
                tmp.matrix[i][j] += matrix[i][k]*b.matrix[k][j];
    return tmp;
}

vector<double> Matrix::gaussian_elimination(){       //高斯消元
    /*
     * 复杂度O(n**3)
     * a:矩阵
     * n:未知数个数
     * l,ans 存储解，l[]表示是否为自由元
     * return:解空间的维数
     */
    int r = 0;
    const int n = row;
    bool l[n];
    vector<double> ans(n, 0.0);
    Matrix tmp;
    tmp.matrix = matrix;

    for (int i = 0; i < n; ++i){
        l[i] = false;
    }

    for (int i = 0; i < n; ++i){
        for (int j = r; j < n; ++j)
            if (fabs(tmp.matrix[j][i]) > EPS){
                for (int k = i; k < n; ++k)
                    std::swap(tmp.matrix[j][k], tmp.matrix[r][k]);
                break;
            }
        if (fabs(tmp.matrix[r][i]) < EPS)    continue;
        for (int j=0; j<n; ++j)
            if (j != r && fabs(tmp.matrix[j][i])>EPS){
                double scale = tmp.matrix[j][i] / tmp.matrix[r][i];
                for (int k=i; k<=n; ++k)
                    tmp.matrix[j][k] -= scale * tmp.matrix[r][k];
            }
        l[i] = true, ++r;
    }
    for(int i=0; i<n; ++i)
        if (l[i])
            for(int j=0; j<n; ++j)
                if(fabs(tmp.matrix[j][i])>0)
                    ans[i] = tmp.matrix[j][n]/tmp.matrix[j][i];

    return ans;
}

inline void Matrix::inverse(vector<double> A[], vector<double> C[], int N){
    /*
     * A:原矩阵
     * C:逆矩阵
     * N:矩阵的阶数
     */
}