/* 
 * File:   main.cpp
 * Author: Scott Williams
 *
 * Created on April 25, 2017, 8:51 AM
 */

#include <cstdlib>
#include "Matrix.hpp"
#include <vector>
#include <iostream>

/*
 * 
 */
int main(int argc, char** argv) {

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
    f.ref();
    f.print();


    
    return 0;
}

