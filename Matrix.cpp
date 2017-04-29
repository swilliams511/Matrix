/* 
 * File:   Matrix.cpp
 * Author: Scott Williams
 *
 * Created on April 25, 2017, 8:52 AM
 */

#include "Matrix.hpp"
#include <iostream>

Matrix::Matrix(int rows, int columns) {
    matrixArray = new double* [rows];
    for(int i = 0; i < rows; ++i) {
        matrixArray[i] = new double[columns];
        for(int j = 0; j < columns; ++j)
            matrixArray[i][j] = 0;
    }
    this->rows = rows;
    this->columns = columns;
}

Matrix::Matrix(int n) {
    matrixArray = new double* [n];
    for(int i = 0; i < n; ++i) {
        matrixArray[i] = new double[n];
        for(int j = 0; j < n; ++j)
            matrixArray[i][j] = 0;
    }
    rows = n;
    columns = n;    
}

Matrix::Matrix(std::vector<std::vector<double>> matrix) {
    rows = matrix.size();
    columns = matrix.at(0).size();
    matrixArray = new double* [rows];
    for(int i = 0; i < rows; ++i) {
        matrixArray[i] = new double[columns];
        for(int j = 0; j < columns; ++j)
            matrixArray[i][j] = matrix[i][j];
    }
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> set) {
    std::vector<std::initializer_list<double>>setVec = set;
    
    std::vector<std::vector<double>> v;
    for(auto i = setVec.begin(); i != setVec.end(); i++) {
        v.push_back(std::vector<double>(*i));
    }
    rows = v.size();
    matrixArray = new double* [rows];
    columns = v.at(0).size();
    for(int i = 0; i < rows; ++i) {
        matrixArray[i] = new double[columns];
        for(int j = 0; j < columns; ++j)
            matrixArray[i][j] = v[i][j];
    }
    
    
    
    
    std::cout << "here\n";
}

Matrix::Matrix(const Matrix& other) {
    rows = other.rows;
    columns = other.columns;
    matrixArray = new double* [rows];
    for(int i = 0; i < rows; ++i) {
        matrixArray[i] = new double[columns];
        for(int j = 0; j < columns; ++j)
            matrixArray[i][j] = other.matrixArray[i][j];
    }
}

//Implemented following copy/swap paradigm
Matrix Matrix::operator= (Matrix other) {
    rows = other.rows;
    columns = other.columns;
    std::swap(matrixArray, other.matrixArray);
    return *this;
}

Matrix::~Matrix() {
    for(int i = 0; i < rows; ++i) 
        delete [] matrixArray[i];
    delete [] matrixArray;
}


double* Matrix::operator[] (int index) {
    return matrixArray[index];
}


void Matrix::identity() {
    if(rows == columns)
        for(int i = 0; i < rows; ++i)
            matrixArray[i][i] = 1;
}

void Matrix::fill(int x) {
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < columns; ++j)
            matrixArray[i][j] = x;
}


void Matrix::rowSwap(int rowIndex1, int rowIndex2) {
    if(rows < 2 || rowIndex1 < 0 || rowIndex2 < 0 || rowIndex1 > rows - 1 || rowIndex2 > rows - 1) {
        std::cout << "Invalid row swap parameters\n";
        exit;
    }
    std::swap(matrixArray[rowIndex1],matrixArray[rowIndex2]); 
}

void Matrix::columnSwap(int columnIndex1, int columnIndex2) {
    if(columns < 2 || columnIndex1 < 0 || columnIndex2 < 0 || 
       columnIndex1 > columns - 1 || columnIndex2 > columns - 1) {
        std::cout << "Invalid row swap parameters\n";
        exit;
    }    
    for(int i = 0; i < rows; ++i)
        std::swap(matrixArray[i][columnIndex1], matrixArray[i][columnIndex2]);
}

void Matrix::multiplyRow(int index, int x) {
    for(int i = 0; i < columns; ++i)
        matrixArray[index][i] *= x;
}

void Matrix::divideRow(int index, int x) {
    for(int i = 0; i < columns; ++i)
        matrixArray[index][i] /= x;    
}

void Matrix::addRows(int scalar, int index1, int index2) {
    for(int i = 0; i < columns; ++i)
        matrixArray[index2][i] += matrixArray[index1][i] * scalar;
}

void Matrix::ref(){
    //for each row
    for(int i = 0; i < rows; ++i) {
        //need to row swap
        if(matrixArray[i][i] == 0) { 
            for(int j = i + 1; j < rows; ++j){
                if(matrixArray[j][i] != 0) {
                    rowSwap(i, j);
                    break;
                }   
            }
        }
        //get a 1 in the pivot position
        if(matrixArray[i][i] != 1)
            divideRow(i, matrixArray[i][i]);
            
        //zero out entries below pivot
        for(int j = i + 1; j < rows; ++j) {
            if(matrixArray[j][i] != 0)
                addRows(-1 * matrixArray[j][i], i, j);
        }
    }
}

void Matrix::rref() {
    ref();
}



void Matrix::print() const {
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j)
            std::cout << "[" << matrixArray[i][j] << "]";
        std::cout << "\n";
    }
    std::cout << "\n";
}

