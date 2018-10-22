//
// Created by James.Pei on 2018/10/21.
//

#ifndef CLIONPROJECTS_MATRIX_H
#define CLIONPROJECTS_MATRIX_H
#define EPS 1e-8

#include <vector>
#include <iostream>
#include <array>


class Matrix{
public:
    int row=0, col=0;
    std::vector<std::vector<double>> matrix;

    Matrix()= default;
    std::vector<std::vector<double>>::iterator iter;
    std::vector<double>::iterator iter2;

    Matrix(int row, int col, std::vector<std::vector<double>> v): row(row), col(col){
        if (v.size()!=row) {
            std::cout << "illegal row arguments" << std::endl;
        }
        std::vector<double> sv = *v.begin();
        if(sv.size()!=col)
            std::cout << "illegal column arguments" << std::endl;
        matrix = v;
    }

    void print();
    void clear();

    Matrix operator + (const Matrix &b);
    Matrix operator - (const Matrix &b);
    Matrix operator * (const Matrix &b);

    std::vector<double> gaussian_elimination();
    void inverse(std::vector<double> A[], std::vector<double> C[], int N);
};

#endif //CLIONPROJECTS_MATRIX_H
