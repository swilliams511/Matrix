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