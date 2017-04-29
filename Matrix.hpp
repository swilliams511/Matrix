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
    
    Matrix(std::vector<std::vector<double>> matrix);
    Matrix(std::initializer_list<std::initializer_list<double>> set);
    
    ~Matrix();
    Matrix(const Matrix& other);
    Matrix operator= (Matrix other);
    
    bool operator== (const Matrix& other) const;
    
    
    //Sets the matrix to the identity matrix. Pair this with the ctr
    //Precondition: rows = columns ie a square n*n matrix
    //Postcondition: overwrites matrixArray with identity matrix. If precondition
    //is false, this function does nothing.
    //O(n)
    void identity();
    
    //Replaces all entries in the matrix with value x
    //O(n*m)
    void fill(int x);
    
    //Precondition: index1 and index2 are not equal and are between 1 and rows.
    //assumes rows > 1
    //Postcondition: all elements from row x are swapped with those in row y
    //O(1)
    void rowSwap(int rowIndex1, int rowIndex2);
    
    //Precondition: index1 and index2 are not equal and are between 1 and columns.
    //assumes columns > 1
    //Postcondition: all elements from column x are swapped with those in column y
    //O(n), if n is the number of columns
    void columnSwap(int columnIndex1, int columnIndex2);
    
    //Multiplies all entries in row at index by x
    void multiplyRow(int index, int x);
    
    //Divides all entries in row at index by x
    void divideRow(int index, int x);
    
    //
    //adds each element from row x to row y, and stores the result in y
    void addRows(int scalar, int index1, int index2);
    
    void ref();
    void rref();
    
    void print() const;
    
    //O(m*n) 
    Matrix operator+ (const Matrix& other) const;
    Matrix operator+= (const Matrix& other);
    Matrix operator- (const Matrix& other) const;
    Matrix operator-= (const Matrix& other);
    
    double* operator[] (int index);
    
    
private:
    int rows;
    int columns;
    double** matrixArray;
    
    
    
};


#endif /* MATRIX_HPP */
