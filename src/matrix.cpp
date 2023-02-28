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

vector<double> Matrix::gaussian_elimination(){
    /**
     * 高斯消元，用于求解多元一次方程，复杂度O(n**3)
     * return:方程解集
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
            if (fabs(tmp.matrix[j][i]) > 0){
                for (int k = i; k < n; ++k)
                    std::swap(tmp.matrix[j][k], tmp.matrix[r][k]);
                break;
            }
        if (fabs(tmp.matrix[r][i]) < 0)    continue;
        for (int j=0; j<n; ++j)
            if (j != r && fabs(tmp.matrix[j][i]) > 0){
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

vector<double> operator * (vector<double> a, double b){
    size_t N = a.size();
    vector<double> res(N, 0);
    for(int i=0; i<N; ++i)
        res[i] = a[i]*b;
    return res;
}

vector<double> operator - (vector<double> a, vector<double> b){
    size_t N = a.size();
    vector<double> res(N, 0);
    for (int i=0; i<N; ++i)
        res[i] = a[i] - b[i];
    return res;
}

vector<vector<double>> Matrix::inverse(){
    /**
     * 矩阵转置，复杂度O(n**3)
     * return:转置后的矩阵
     */
    if(col!=row){
        cout<<"col must equal to row"<<endl;
    } else {
        int N = col;    // 矩阵的阶
        vector<double> b(col, 0);
        vector<vector<double>> reverse(row, b);
        vector<vector<double>> original;
        original = matrix;

        for (int i = 0; i < row; ++i) {
            reverse[i][i] = 1;
        }

        for (int i = 0; i < N; ++i) {
            for (int j = i; j < N; ++j)
                if (fabs(original[j][i]) > 0) {     // 此处目的为保证对角线不为0，若为0就交换
                    swap(original[i], original[j]);
                    swap(reverse[i], reverse[j]);
                    break;
                }
            reverse[i] = reverse[i] * (1 / original[i][i]);
            original[i] = original[i] * (1 / original[i][i]);
            for (int j = 0; j < N; ++j)
                if (j != i && fabs(original[j][i]) > 0) {
                    reverse[j] = reverse[j] - reverse[i] * original[j][i];
                    original[j] = original[j] - original[i] * original[j][i];
                }
        }
        return reverse;
    }
}