#include <iostream>
#include <vector>
#include "matrix.h"
#include "primenumber.h"

using std::vector; using std::cout; using std::endl;

int main() {
//    int l3[3][3] = {{2, 1, 1}, {6, 2, 1},{-2, 2, 1}};
//    vector<double> vs2{0,0,0};
//    vector<vector<double>> v3(3, vs2);
//    for (int i=0; i<v3.size(); i++){
//        size_t size = v3[0].size();
//        for (int j=0; j<size; j++){
//            v3[i][j] = l3[i][j];
//        }
//    }
//    Matrix matrix5(3,3,v3);
//    vector<vector<double>> inversed = matrix5.inverse();
//    for(vector<double> i: inversed){
//        for(double j:i){
//            cout<< j <<" ";
//        }
//        cout<< "\n";
//    }
//    cout<< endl;
//    matrix5.clear();


    int n = 50;
//    vector<int> r=getPrime(n);
    vector<int> r = prime_factor_Decomposition(n);
    for(int i:r)
        cout<<i<<endl;


}