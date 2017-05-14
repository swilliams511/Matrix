/* 
 * File:   Matrix.hpp
 * Author: Scott Williams
 *
 * Created on April 25, 2017, 8:52 AM
 */

#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <vector>
#include <initializer_list>

class Matrix {
public:
    //construct a n * m (rectangular) matrix
    //All entries are zeros
    //O(n*m)
    Matrix(int rows, int columns);
    
    //creates a n x n (square) matrix
    //All entries are zeros
    //O(n^2)
    Matrix(int n);
    
    //vector of vectors constructor
    Matrix(std::vector<std::vector<double>> matrix);
    
    //initializer list constructor
    Matrix(std::initializer_list<std::initializer_list<double>> set);
    
    //creates an n x n identity matrix
    static Matrix identity(int n);
    
    ~Matrix();
    Matrix(const Matrix& other);
    Matrix operator= (Matrix other);
    
    
    bool operator== (const Matrix& other) const;
    
    //Replaces all entries in the matrix with value x
    //O(n*m)
    void fill(double x);
    
    //Precondition: index1 and index2 are not equal and are between 1 and rows.
    //assumes rows > 1, else type 1 exit
    //Postcondition: all elements from row x are swapped with those in row y
    //O(1)
    void rowSwap(int rowIndex1, int rowIndex2);
    
    //Precondition: index1 and index2 are not equal and are between 1 and columns.
    //assumes columns > 1, else type 1 exit
    //Postcondition: all elements from column x are swapped with those in column y
    //O(n), if n is the number of columns
    void columnSwap(int columnIndex1, int columnIndex2);
    
    //Multiplies all entries in row at index by x
    void multiplyRow(int index, double x);
    
    //Divides all entries in row at index by x
    void divideRow(int index, double x);
    
    
    //
    //adds each element from row x to row y, and stores the result in y
    void addRows(double scalar, int index1, int index2);
    
    
    void ref();
    void rref();
    
    int refDebug();
    void rrefDebug();
    
    void transpose();
    
    void print() const;
    
    //O(m*n) 
    Matrix operator+ (const Matrix& other) const;
    Matrix operator+= (const Matrix& other);
    Matrix operator- (const Matrix& other) const;
    Matrix operator-= (const Matrix& other);
    
    Matrix operator* (const double& scalar) const;
    
    
    
    double* operator[] (int index);
    double* operator[] (int index) const;
    
    
private:
    int rows;
    int columns;
    double** matrixArray;
    
    //helper functions to reduce overall operations
    void addRows(double scalar, int index1, int index2, int startIndex);
    void divideRow(int rowIndex, int startIndex, double x);
};


//commutativity multiplication of a scalar and a matrix
Matrix operator* (const double& scalar, const Matrix& rhs);

/* Exit types
 * exit(1) -> row or column swap indices not on a valid range
 * 
 * 
 * 
 * 
 */




#endif /* MATRIX_HPP */

