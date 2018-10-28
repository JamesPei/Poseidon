#include <iostream>
#include <vector>
#include <map>
#include "matrix.h"
#include "primenumber.h"
#include "graph.h"

using std::vector; using std::cout; using std::endl; using std::map;

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


//    int n = 50;
//    vector<int> r=getPrime(n);
//    vector<int> r=prime_factor_Decomposition(n);
//    for(int i:r)
//        cout<<i<<endl;

//    Graph graph(0,0);
//    graph.add(1,5);
//    graph.add(2,1);
//    graph.add(2,3);
//    graph.add(2,5);
//    graph.add(3,5);
//    graph.add(5,6);
//    graph.add(6,3);
//    graph.add(6,4);

    map<int, vector<int>> map;
    Graph graph(map);
    graph.add(1,2);
    graph.add(1,3);
    graph.add(2,4);
    graph.add(2,5);
    graph.add(3,6);
    graph.add(4,7);
    graph.add(5,7);
    graph.add(6,5);
    graph.add(6,8);
    graph.add(7,9);
    graph.add(8,9);
    graph.add(9,NULL);
    graph.print();

}