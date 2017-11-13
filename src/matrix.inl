#include "matrix.h"
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "matrixDecomposer.h"
#include "linearSystemSolver.h"

template<typename TField>
Matrix<TField>::Matrix(const int & _m, const int & _n,
										   const TField & _diag, const TField & _others) : rows {_m}, cols {_n} {

    // Test nullity of number of cols and rows
    if (!_m or !_n)
        throw std::logic_error("A matrix cannot have zero rows or columns.");

    // Create data and populate it
    data = new TField* [_m];
    for (int i = 0; i < _m; ++i) {
        *(data + i) = new TField[_n];
        for (int j = 0; j < _n; ++j) {
			if (i == j)
				data[i][j] = _diag;
			else
				data[i][j] = _others;
        }
    }
}

template<typename TField>
Matrix<TField>::Matrix(const int & _m, const int & _n, const TField & _initial) : rows {_m}, cols {_n} {

    // Test nullity of number of cols and rows
    if (!_m or !_n)
        throw std::logic_error("A matrix cannot have zero rows or columns.");

    // Create data and populate it
    data = new TField* [_m];
    for (int i = 0; i < _m; ++i) {
        *(data + i) = new TField[_n];
        for (int j = 0; j < _n; ++j) {
            data[i][j] = _initial;
        }
    }
}

template<typename TField>
Matrix<TField>::Matrix(const int & _m, const TField & _initial) : Matrix(_m, _m, _initial) {/* empty */}

template<typename TField>
Matrix<TField>::Matrix(const int & _m) : Matrix(_m, _m, 0) {
    for (int i = 0; i < _m; ++i)
        this->data[i][i] = 1;
}

template<typename TField>
Matrix<TField>::Matrix(const Matrix<TField> & from) :  rows {from.rows}, cols {from.cols} {
    this->data = new TField * [from.rows];
    for (int i = 0; i < from.rows; ++i)
        this->data[i] = new TField[from.cols];
    for (int i = 0; i < from.rows; ++i) {
        for (int j = 0; j < from.cols; ++j) {
            this->data[i][j] = from[i][j];
        }
    }
}

template<typename TField>
Matrix<TField>::Matrix(const std::initializer_list<std::initializer_list<TField>> & l) : data{nullptr} {
    this->rows = l.size();

    if (this->rows == 0)
        throw std::invalid_argument("Zero lines not allowed!");
    else {
        this->cols = l.begin()->size();
        if (this->cols == 0)
            throw std::invalid_argument("Zero columns not allowed!");
        else {
            this->data = new TField * [this->rows];
            for (int i = 0; i < this->rows; ++i)
                this->data[i] = new TField[this->cols];
        }
    }

    int i = 0;
    for (auto r : l) {
       int j = 0;
       if ((int) r.size() != this->cols)
           throw std::logic_error("Some element of the matrix is missing!");
       for (auto e : r) {
           data[i][j] = e;
           ++j;
       }
       ++i;
    }
}

template<typename TField>
Matrix<TField>::Matrix(const int & n, const TField * array) : Matrix(n, 1, array[0]) {
	for (int i = 0; i < n; ++i)
		this->data[i][0] = array[i];
}

template<typename TField>
Matrix<TField>::~Matrix() {
    if (data != nullptr) {
        for (int i = 0; i < this->rows; ++i)
            delete [] this->data[i];
        delete [] this->data;
    }
}

template<typename TField>
void Matrix<TField>::set(const int & i, const int & j, const TField & value) {
    data[i][j] = value;
}

template<typename TField>
const TField & Matrix<TField>::at(const int & i, const int & j) const {
    return data[i][j];
}

template<typename TField>
void Matrix<TField>::swap_lines(const int & i, const int & j) {
    for (int c = 0; c < this->cols; ++c) {
        std::swap(data[i][c], data[j][c]);
    }
}

template<typename TField>
void Matrix<TField>::swap_lines(const int & i, const int & j, const int c1, const int c2) {
    for (int c = c1; c <= c2; ++c) {
        std::swap(data[i][c], data[j][c]);
    }
}

template<typename TField>
TField * & Matrix<TField>::operator[](const int & i) {
    if (i < 0 || i >= rows)
            throw std::logic_error("Accessing position out of bounds.");
    return data[i];
}

template<typename TField>
TField * Matrix<TField>::operator[](const int & i) const {
    if (i < 0 || i >= rows)
            throw std::logic_error("Accessing position out of bounds.");
    return data[i];
}


template<typename TField>
Matrix<TField> Matrix<TField>::operator+(const Matrix & _rhs) {
    if (rows != _rhs.rows || cols != _rhs.cols)
        throw std::logic_error("Matrices must have the same size!");
    Matrix<TField> sum {rows, cols, 0};
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sum[i][j] = this->data[i][j] + _rhs[i][j];
        }
    }
    return sum;
}

template<typename TField>
Matrix<TField> & Matrix<TField>::operator+=(const Matrix<TField> & _rhs) {
    if (rows != _rhs.rows || cols != _rhs.cols)
        throw std::logic_error("Matrices must have the same size!");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            this->data[i][j] += _rhs[i][j];
        }
    }
    return *this;
}

template<typename TField>
Matrix<TField> Matrix<TField>::operator-(const Matrix<TField> & _rhs) {
    if (rows != _rhs.rows || cols != _rhs.cols)
        throw std::logic_error("Matrices must have the same size!");
    Matrix<TField> diff {rows, cols, 0};
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            diff[i][j] = this->data[i][j] - _rhs[i][j];
        }
    }
    return diff;
}

template<typename TField>
Matrix<TField> & Matrix<TField>::operator-=(const Matrix<TField> & _rhs) {
    if (rows != _rhs.rows || cols != _rhs.cols)
        throw std::logic_error("Matrices must have the same size!");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            this->data[i][j] -= _rhs[i][j];
        }
    }
    return *this;
}

template<typename TField>
Matrix<TField> Matrix<TField>::operator*(const Matrix<TField> & _rhs) {
    // Check multiplication condition
    if (cols != _rhs.rows)
        throw std::logic_error("You must provide matrices mxn and nxp.");
    // Multiply
    Matrix<TField> prod {rows, _rhs.cols, 0};
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < _rhs.cols; ++j) {
            for (int k = 0; k < cols; ++k) {
                prod[i][j] = prod[i][j] + this->data[i][k] * _rhs[k][j];
            }
        }
    }
    return prod;
}

template<typename TField>
Matrix<TField> & Matrix<TField>::operator=(Matrix<TField> m) {
    if (m.cols != this->cols || m.rows != this->rows) {
		if (data != nullptr) {
			for (int i = 0; i < this->rows; ++i)
				delete [] this->data[i];
			delete [] this->data;
		}
        this->data = new TField * [m.rows];
        for (int i = 0; i < m.rows; ++i)
            this->data[i] = new TField[m.cols];
    }
    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            this->data[i][j] = m[i][j];
        }
    }
    this->cols = m.cols;
    this->rows = m.rows;
    return *(this);
}

template<typename TField>
Matrix<TField> operator*(const TField & _scalar, Matrix<TField> & _rhs) {
    Matrix<TField> prod {_rhs.rows, _rhs.cols, 0};
    for (int i = 0; i < _rhs.rows; ++i) {
        for (int j = 0; j < _rhs.cols; ++j) {
            prod[i][j] = _rhs[i][j] * _scalar;
        }
    }
    return prod;
}

template<typename TField>
Matrix<TField> operator*(Matrix<TField> & _rhs, const TField & _scalar) {
    return (_scalar)*(_rhs);
}


template<typename TField>
std::ostream& operator<<(std::ostream& os, const Matrix<TField>& matrix) {
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            os << std::setprecision(6) << matrix[i][j] << " ";
        }
        os << std::endl;
    }
    os << std::endl;
    return os;
}

template<typename TField>
Matrix<TField> Matrix<TField>::transpose() const{

    Matrix<TField> transposed {this->cols, this->rows, 0};
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            transposed[j][i] = this->data[i][j];
        }
    }

    return transposed;
}

template<typename TField>
bool Matrix<TField>::isSymmetric() const{
    if(this->rows != this->cols) {
        return false;
    }else{
        for(int i = 0; i < this->rows; ++i){
            for(int j = i+1; j < this->cols; ++j){
                if(this->data[i][j] != this->data[j][i])
                    return false;
            }
        }
    }

    return true;
}

template<typename TField>
Matrix<TField> Matrix<TField>::diagonal() const{

    Matrix<TField> d {this->cols, this->rows, 0};
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            if (i == j){
                d[i][j] = this->data[i][j];
            }
        }
    }

    return d;
}

template<typename TField>
Matrix<TField> Matrix<TField>::symmetric() const{

    Matrix<TField> s {this->cols, this->rows, 0};
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
                if (this->data[i][j] == 0){
                    s[i][j] = 0; // for some reason -1*0 = -0
                } else {
                    s[i][j] = -1*this->data[i][j];
                }
        }
    }
    return s;
}

template<typename TField>
Matrix<TField> Matrix<TField>::pow(int k) const{

    Matrix<TField> p {this->cols, this->rows, 0};
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
                p[i][j] = std::pow(this->data[i][j], k);
        }
    }
    return p;
}

template<typename TField>
Matrix<TField> Matrix<TField>::inverse() const{

	if (this->rows != this->cols)
		throw std::runtime_error("inverse: The matrix must be square.");

	Matrix<TField> inverse {this->rows, this->cols, 1, 0};
	// LU decomposition
	Matrix<TField> L {this->rows, this->cols, 1, 0};
	Matrix<TField> U {*this};
	Matrix<TField> P {this->rows, this->cols, 1, 0};
	MatrixDecomposer<TField>::lu(*this, L,U,P);

	// Solve n linear systems
	Matrix<TField> I {this->rows, this->cols, 1, 0};	// Identity matrix, source of canonical vectors
	for (int j = 0; j < this->cols; ++j) {
		Matrix<TField> b {this->rows, I[j]};
		Matrix<TField> y {this->rows, 1, 0};
		LinearSystemSolver<TField>::forward_substitution(L, P*b, y);
		Matrix<TField> x {this->rows, 1, 0};
		LinearSystemSolver<TField>::back_substitution(U, y, x);
		for (int jj = 0; jj < this->cols; ++jj)
			inverse[jj][j] = x[jj][0];
	}
	return inverse;
}
