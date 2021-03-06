/* 
 * File:   main.cpp
 * Author: Scott Williams
 *
 * Created on April 25, 2017, 8:51 AM
 */


#include "Matrix.hpp"
#include <vector>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <cstdlib>

/*
 * 
 */
std::chrono::high_resolution_clock::time_point time();
void timeTaken(std::chrono::high_resolution_clock::time_point t1,
        std::chrono::high_resolution_clock::time_point t2);


int main(int argc, char** argv) {
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point stop;
    
    
//*** Constructor examples
    
    //vector constructor
    std::vector<std::vector<double>> fog { { 0, 1, 2, 1 },
                                           { 0, 2, 8, 2 },
                                           { 1, 9, 5, 1 }};                                      
    Matrix ref(fog);
    std::cout << "vector ctr\n";
    ref.print();
    //**********  

    //initializer list constructor
    Matrix f { { 0, 1, 2, 1 },
               { 0, 2, 8, 2 },
               { 1, 9, 5, 1 }};
    std::cout << "initializer list ctr\n";
    f.print();
    //**********  
               
    //construct an empty 5x5 matrix then manually assign elements
    int r = 5;
    int c = 5;
    Matrix rc(5,5);
    for(int i = 0; i < r; ++i)
        for(int j = 0; j < c; ++j)
            rc[i][j] = (i+1) * (j+1);
    std::cout << "manual ctr\n";
    rc.print();
    //**********    
    
    //construct a 3x3 identity matrix 
    Matrix identity = Matrix::identity(3);
    std::cout << "identity ctr\n";
    identity.print();
               
//testing operations
    /*
     * ref() of [0][1][2] [1]  is [1][9][5] [1] 
     *          [0][2][8] [2]     [0][1][4] [1]
     *          [1][9][5] [1]     [0][0][1] [0]
     * 
     * rref() of the same matrix returns [1][0][0] [-8]
     *                                   [0][1][0] [ 1]
     *                                   [0][0][1] [ 0]
     */ 
    f.print();
    start = time();
    f.rref();
    stop = time();
    timeTaken(start,stop);
    f.print();
    
    std::srand(1);
    start = time();
    int n = 4;
    Matrix test(n,n+1);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n+1; ++j) {
            test[i][j] = (rand() % 144) + 1;
        }
    }
    test.print();
    stop = time();
    timeTaken(start,stop);
    
    start = time();
    test.rrefDebug();
    test.rref();
    stop = time();
    timeTaken(start,stop);
    
    Matrix m1 { {1, 1, 1},
                {1, 1, 1},
                {1, 1, 1}};
    Matrix m2 { {1, 1, 1},
                {1, 1, 1}};
    Matrix m3 = m1 + m2;
    m3 = m1 + m1;
    m3.print();
    m3 += m3;
    m3.print();
    m3 * .25;
    m3.print();
    m3 = 12 * m3;
    std::cout << "made it\n";
    m3.print();
    
    Matrix t1 { { 1, 2, 3},
                { 4, 5, 6},
                { 7, 8, 9}};
    Matrix LU = t1;
    t1.print();
    t1.transpose();
    t1.print();
    m2.print();
    m2.transpose();
    m2.print();
    
    Matrix mult1 {{1, 2}, {3, 4}};
    Matrix mult2 {{2, 0}, {1, 2}};
    Matrix product = mult1 * mult2;
    product.print();
    
    //Testing Crout LU decomposition
    LU.LU();
    Matrix LU2 {{1,3,5},{2,4,7},{1,1,0}};
    std::vector<Matrix> luValues = LU2.LU();
    Matrix prod = luValues[0] * luValues[1];
    std::cout << "---Matrix L---\n";
    luValues[0].print();
    std::cout << "---Matrix U---\n";
    luValues[1].print();
    std::cout << "---L * U---\n";
    prod.print();
    std::cout << "---Starting Matrix, should equal L * U---\n";
    LU2.print();
            
    
    return 0;
}

std::chrono::high_resolution_clock::time_point time() {
    return std::chrono::high_resolution_clock::now();
}

void timeTaken(std::chrono::high_resolution_clock::time_point t1,
        std::chrono::high_resolution_clock::time_point t2) {

    std::cout  << std::fixed << "Tike taken: " << std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1).count()
            << "\n\n";
    std::cout.unsetf(std::ios_base::fixed);

}
