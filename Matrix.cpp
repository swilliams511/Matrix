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
    
    //casts the double initializer list into a vector of initializer lists
    std::vector<std::initializer_list<double>>setVec = set;
    
    //Get the data out of the initializer lists
    std::vector<std::vector<double>> vector;
    for(auto i = setVec.begin(); i != setVec.end(); i++)
        vector.push_back(std::vector<double>(*i));
    
    rows = vector.size();
    matrixArray = new double* [rows];
    columns = vector.at(0).size();
    for(int i = 0; i < rows; ++i) {
        matrixArray[i] = new double[columns];
        for(int j = 0; j < columns; ++j)
            matrixArray[i][j] = vector[i][j];
    }
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
        std::swap(rows, other.rows);
        std::swap(columns, other.columns);
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

double* Matrix::operator[] (int index) const {
    return matrixArray[index];
}

Matrix Matrix::identity(int n) {
    Matrix identity(n);
    for(int i = 0; i < n; ++i)
        identity.matrixArray[i][i] = 1;
    return identity;
}


void Matrix::fill(double x) {
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < columns; ++j)
            matrixArray[i][j] = x;
}


void Matrix::rowSwap(int rowIndex1, int rowIndex2) {
    if(rows < 2 || rowIndex1 < 0 || rowIndex2 < 0 || rowIndex1 > rows - 1 || rowIndex2 > rows - 1) {
        std::cout << "Invalid row swap parameters\n";
        exit(1);
    }
    std::swap(matrixArray[rowIndex1],matrixArray[rowIndex2]); 
}

void Matrix::columnSwap(int columnIndex1, int columnIndex2) {
    if(columns < 2 || columnIndex1 < 0 || columnIndex2 < 0 || 
       columnIndex1 > columns - 1 || columnIndex2 > columns - 1) {
        std::cout << "Invalid column swap parameters\n";
        exit(1);
    }    
    for(int i = 0; i < rows; ++i)
        std::swap(matrixArray[i][columnIndex1], matrixArray[i][columnIndex2]);
}

void Matrix::multiplyRow(int index, double x) {
    for(int i = 0; i < columns; ++i)
        matrixArray[index][i] *= x;
}

void Matrix::divideRow(int index, double x) {
    if(x == 0) //cant divide by zero
        return;
    for(int i = 0; i < columns; ++i)
        matrixArray[index][i] /= x;    
}

void Matrix::divideRow(int rowIndex, int startIndex, double x) {
    if(x == 0) //cant divide by zero
        return;
    for(int i = startIndex; i < columns; ++i)
        matrixArray[rowIndex][i] /= x;    
}

void Matrix::addRows(double scalar, int index1, int index2) {
    for(int i = 0; i < columns; ++i)
        matrixArray[index2][i] += matrixArray[index1][i] * scalar;
}

void Matrix::addRows(double scalar, int index1, int index2, int startIndex) {
    for(int i = startIndex; i < columns; ++i)
        matrixArray[index2][i] += matrixArray[index1][i] * scalar;
}

void Matrix::ref(){
    //for each row
    for(int i = 0; i < rows; ++i) {
        //need to row swap
        if(matrixArray[i][i] == 0)
            for(int j = i + 1; j < rows; ++j)
                if(matrixArray[j][i] != 0) {
                    rowSwap(i, j);
                    break;
                }   
        //get a 1 in the pivot position
        if(matrixArray[i][i] != 1 && matrixArray[i][i] != 0)
            divideRow(i, i, matrixArray[i][i]);
            
        //zero out entries below pivot
        for(int j = i + 1; j < rows; ++j) 
            if(matrixArray[j][i] != 0)
                addRows(-1 * matrixArray[j][i], i, j, i);
    }
}

void Matrix::rref() {
    ref();
    //loop to get the bottom right diagonal and move up
    for(int i = rows - 1; i > -1; --i) 
        //look at each index above the current pivot
        for(int j = i - 1; j > -1; --j) 
            if(matrixArray[j][i] != 0) { 
                //zero out the indeces
                double scalar = -1 * matrixArray[j][i];
                matrixArray[j][i] += matrixArray[i][i] * scalar;
                //update the augmented matrix should one exist
                for(int k = rows; k < columns; ++k)
                    matrixArray[j][k] += matrixArray[i][k] * scalar;
            }
}


int Matrix::refDebug(){
    int step = 1;
    //for each row
    int additions = 0;
    for(int i = 0; i < rows; ++i) {
        //need to row swap
        if(matrixArray[i][i] == 0)
            for(int j = i + 1; j < rows; ++j)
                if(matrixArray[j][i] != 0) {
                    std::cout << "Step " << step++ << ": swap row " << i+1 << " with " << j+1 << "\n";
                    rowSwap(i, j);
                    print();
                    break;
                }   
        //get a 1 in the pivot position
        if(matrixArray[i][i] != 1 && matrixArray[i][i] != 0) {
            std::cout << "Step " << step++ << ": divide row " << i+1 << " by " << matrixArray[i][i] << "\n";
            divideRow(i, i, matrixArray[i][i]);
            print();
        }
            
        //zero out entries below pivot
        for(int j = i + 1; j < rows; ++j) 
            if(matrixArray[j][i] != 0) {
                std::cout << "Step " << step++ << ": multiply row " << i+1
                        << " by " << -1*matrixArray[j][i] << " and adding to row " << j+1 << "\n";
                addRows(-1 * matrixArray[j][i], i, j, i);
                ++additions;
                print();
            }
    }
    std::cout << "Number of row additions: " << additions << "\n";
    std::cout << "---Row Echelon Form Matrix---\n";
    print();
    return step;
}


void Matrix::rrefDebug() {
    int step = refDebug();
    //loop to get the bottom right diagonal and move up
    int additions = 0;
    for(int i = rows - 1; i > -1; --i) {
        //look at each index above the current pivot
        for(int j = i - 1; j > -1; --j) {
            if(matrixArray[j][i] != 0.0) {
                //zero out the indeces
                std::cout << "Step " << step++ << ": multiply row " << i+1
                << " by " << -1*matrixArray[j][i] << " and adding to row " << j+1 << "\n";
                //addRows(-1 * matrixArray[j][i], i, j);
                double scalar = -1 * matrixArray[j][i];
                matrixArray[j][i] += matrixArray[i][i] * scalar;
                
                //update the augmented matrix should one exist
                for(int k = rows; k < columns; ++k)
                    matrixArray[j][k] += matrixArray[i][k] * scalar;
                
                ++additions;
                print();
            }
        }
    }
    std::cout << "row addition operations: " << additions << "\n";
    std::cout << "---Recuded Row Echelon Form Matrix---\n";
    print();
}

void Matrix::transpose() {
    //if we have a square matrix
    if(rows == columns) {
        for(int i = 0; i < rows - 1; ++i)
            for(int j = i + 1; j < columns; ++j)
                std::swap(matrixArray[i][j], matrixArray[j][i]);
    }
    //we have a n x m matrix
    else {
        Matrix temp(columns, rows);
        for(int i = 0; i < rows; ++i)
            for(int j = 0; j < columns; ++j)
                temp[j][i] = matrixArray[i][j];
        *this = temp;
    }
}



//prints some debug info
void Matrix::print() const {
    //std::cout << rows << "," << columns << "\n";
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            if(matrixArray[i][j] == 0) //just so -0 doesnt get printed since that looks odd
                std::cout << "[" << 0 << "]";
            else
                std::cout << "[" << matrixArray[i][j] << "]";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

Matrix Matrix::operator +(const Matrix& other) const {
    //If we are doing an invalid sum, just return *this object
    if (rows != other.rows || columns != other.columns) {
        std::cout << "Invalid dimensions! " << rows << "x" << columns 
                << " must equal " << other.rows << "x" << other.columns << "\n";
        return *this;
    }
    
    Matrix sum(*this);
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < columns; ++j)
            sum[i][j] += other[i][j];
    return sum;
}

Matrix Matrix::operator +=(const Matrix& other) {
    *this = *this + other;
    return *this;
}

Matrix Matrix::operator -(const Matrix& other) const {
    //If we are doing an invalid sum, just return *this object
    if (rows != other.rows || columns != other.columns) {
        std::cout << "Invalid dimensions! " << rows << "x" << columns 
                << " must equal " << other.rows << "x" << other.columns << "\n";
        return *this;
    }
    
    Matrix difference(*this);
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < columns; ++j)
            difference[i][j] -= other[i][j];
    return difference;    
}

Matrix Matrix::operator -=(const Matrix& other) {
    *this = *this - other;
    return *this;
}

Matrix Matrix::operator* (const double& scalar) const {
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < columns; ++j)
            matrixArray[i][j] *= scalar;
    return *this;
}

Matrix operator* (const double& scalar, const Matrix& rhs){
    return rhs * scalar;
}