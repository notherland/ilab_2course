//
// Created by ksenia on 12.10.2020.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#endif //MATRIX_MATRIX_H

#include <iostream>
#include <algorithm>
#include <vector>

template<typename T>
class Matrix {
    T **matrix;
    int n, m;
public:
    //Constructors
    Matrix(int rows, int columns, T val = T{}) //constructor with value;
    {
        n = rows;
        m = columns;
        matrix = (T **) new T *[n];

        for (int i = 0; i < n; ++i) {
            matrix[i] = (T *) new T[m];
            for (int j = 0; j < m; ++j) {
                matrix[i][j] = val;
            }
        }
    }

    template<typename It>
    Matrix(int rows, int columns, It start, It fin) //constructor of existing sequence
    {
        It it = start;
        n = rows;
        m = columns;
        matrix = (T **) new T *[n];

        for (int i = 0; i < n; ++i) {
            matrix[i] = (T *) new T[m];
            for (int j = 0; j < m; ++j) {
                if (it <= fin) {
                    matrix[i][j] = *it;
                    it++;
                } else
                    matrix[i][j] = T{};
            }
        }
    }

    static Matrix eye(int n, int m) {
        Matrix newMatrix{n, m};

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i == j)
                    (newMatrix.matrix)[i][j] = 1;
            }
        }
        return newMatrix;
    }

    template<typename It>
    static Matrix triangle(int p, It start, It fin) //constructor of existing sequence
    {
        It it = start;
        Matrix newMatrix{p, p};

        for (int i = 0; i < p; i++) {
            for (int j = 0; j <= i; j++) {
                if (it <= fin) {
                    newMatrix[i][j] = *it;
                    it++;
                } else
                    newMatrix[i][j] = T{};
            }
        }
        return newMatrix;
    }

    static Matrix MatrixWithoutRowCol(int row, int col, Matrix matrix) {
        Matrix newMatrix{matrix.nrows() - 1, matrix.ncolumns() - 1};
        for (int i = 0; i < row - 1; ++i) {
            for (int j = 0; j < col - 1; ++j)
                newMatrix[i][j] = matrix[i][j];
            for (int j = col - 1; j < newMatrix.ncolumns(); ++j)
                newMatrix[i][j] = matrix[i][j + 1];
        }
        for (int i = row - 1; i < newMatrix.nrows(); ++i) {
            for (int j = 0; j < col - 1; ++j)
                newMatrix[i][j] = matrix[i + 1][j];
            for (int j = col - 1; j < newMatrix.ncolumns(); ++j)
                newMatrix[i][j] = matrix[i + 1][j + 1];
        }
        return newMatrix;
    }

    static Matrix RandomMatrix(int n, int m, int MAX)//generating of random matrix with setted sizes and max value
    {
        std::vector<T> vec;
        int size = n * m;
        for (int i = 0; i < size; i++)
            vec.push_back(rand() % MAX);
        Matrix<T> M{n, m, vec.begin(), vec.end()};
        return M;
    }

    Matrix(const Matrix &rhs) //copy constructor
    {
        n = rhs.n;
        m = rhs.m;
        matrix = (T **) new T *[n];

        for (int i = 0; i < n; ++i) {
            matrix[i] = (T *) new T[n];
            for (int j = 0; j < m; ++j) {
                matrix[i][j] = rhs.matrix[i][j];
            }
        }
    }

    Matrix &operator=(const Matrix &rhs) //assignment
    {
        if (this != &rhs) {
            for (int i = 0; i < n; i++)
                delete[] matrix[i];
            delete[] matrix;
        }

        n = rhs.n;
        m = rhs.m;
        matrix = (T **) new T *[n];

        for (int i = 0; i < n; i++) {
            matrix[i] = (T *) new T[m];
            for (int j = 0; j < m; j++) {
                matrix[i][j] = rhs[i][j];
            }
        }
        return *this;
    }

    //Basic fuctions
    int nrows() const {
        return n;
    }

    int ncolumns() const {
        return m;
    }

    const T *operator[](int i) const//getter
    {
        return &matrix[i][0];
    }

    T *operator[](int i)//setter
    {
        return &matrix[i][0];
    }

    //Calculation
    T trace() const // sum of elem on diagonal
    {
        T sum{};
        if (n != m) {
            return sum;
        }
        for (int i = 0; i < n; ++i) {
            sum += matrix[i][i];
        }
        return sum;
    }

    bool equal(const Matrix &other) const //checking equality
    {
        if (n != other.nrows() || m != other.ncolumns())
            return false;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (matrix[i][j] != other[i][j])
                    return false;
            }
        }
        return true;
    }

    Matrix &transpose() & //transposing of matrix
    {
        Matrix<T> oldMatrix{*this};
        for (int i = 0; i < n; i++)
            delete[] matrix[i];
        delete[] matrix;

        n = oldMatrix.ncolumns();
        m = oldMatrix.nrows();

        matrix = (T **) new T *[n];

        for (int i = 0; i < n; ++i) {
            matrix[i] = (T *) new T[m];
            for (int j = 0; j < m; ++j) {
                matrix[i][j] = oldMatrix[j][i];
            }
        }
        return *this;
    }

    void SwapRows(int a, int b) {
        if (a < 1 || b < 1)
            return;
        for (int j = 0; j < m; ++j)
            std::swap(matrix[a - 1][j], matrix[b - 1][j]);
    }

    float LUdet() {
        float det{}, sumU, sumL;
        if (n != m) {
            std::cout << "Wrong matrix sizes";
            return det;
        }
        Matrix<double> L{n, n}, U{n, n};

        int k = 2;
        int sign = 1;
        while (matrix[0][0] == 0 && k <= n) {
            SwapRows(1, k);
            k++;
            sign = -1 * sign;
        }

        if (matrix[0][0] == 0)
            return det;

        for (int j = 0; j < n; j++) {
            U[0][j] = matrix[0][j];
            L[j][0] = matrix[j][0] / U[0][0];
        }

        for (int i = 1; i < n; i++) {
            for (int j = i; j < n; j++) {
                sumU = sumL = 0;
                for (int k = 0; k < i; k++)
                    sumU += (L[i][k] * U[k][j]);
                U[i][j] = matrix[i][j] - sumU;
                for (int k = 0; k < i; k++)
                    sumL += (L[j][k] * U[k][i]);
                L[j][i] = (matrix[j][i] - sumL) / U[i][i];
            }
        }
        det = 1;
        for (int i = 0; i < n; i++)
            det *= U[i][i];

        return det * sign;
    }


//Overloading operators
    Matrix &negate() & //making a[i][j] -a[i][j]
    {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                matrix[i][j] = -matrix[i][j];
        return *this;
    }

    Matrix operator-() const {
        Matrix tmp{*this};
        return tmp.negate();
    }

    Matrix &operator+=(const Matrix &rhs) &{
        if (n != rhs.n || m != rhs.m)
            return *this;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; ++j)
                matrix[i][j] = matrix[i][j] + rhs[i][j];
        }
        return *this;
    }

    Matrix &operator-=(const Matrix &rhs) &{
        if (n != rhs.n || m != rhs.m)
            return *this;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j)
                matrix[i][j] = matrix[i][j] - rhs[i][j];
        }
        return *this;
    }

    Matrix &operator*=(int n) &{
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j)
                matrix[i][j] = matrix[i][j] * n;
        }
        return *this;
    }

    Matrix &prod(const Matrix &rhs) &{
        if (m != rhs.nrows())
            return *this;
        T p = m;

        Matrix<T> oldMatrix{*this};

        for (int i = 0; i < n; i++)
            delete[] matrix[i];
        delete[] matrix;

        n = oldMatrix.nrows();
        m = rhs.ncolumns();
        matrix = (T **) new T *[n];

        for (int i = 0; i < n; ++i) {
            matrix[i] = (T *)
                    new T[m];
            for (int j = 0; j < m; ++j) {
                T elem{};
                for (int k = 0; k < p; ++k)
                    elem += oldMatrix[i][k] * rhs[k][j];
                matrix[i][j] = elem;
            }
        }
        return *this;
    }

    Matrix operator+(const Matrix &rhs) {
        Matrix newMatrix{*this};
        newMatrix += rhs;
        return newMatrix;
    }

    Matrix operator-(const Matrix &rhs) {
        Matrix newMatrix{*this};
        newMatrix -= rhs;
        return newMatrix;
    }

    Matrix operator*(int n) {
        Matrix newMatrix{*this};
        newMatrix *= n;
        return newMatrix;
    }

    bool operator==(const Matrix &rhs) {
        return equal(rhs);
    }

    void dump(std::ostream &os = std::cout) const //output of matrix
    {
        os << n << "x" << m << std::endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                os << matrix[i][j] << " ";
            }
            os << std::endl;
        }
    }

    ~

    Matrix() //destructor
    {
        for (int i = 0; i < n; i++)
            delete[] matrix[i];
        delete[] matrix;
    }

};