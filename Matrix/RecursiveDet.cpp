#include "Matrix.h"

template <typename T>
float RecursiveDet(Matrix<T> matrix) {
    float det = 0;
    if (matrix.nrows() != matrix.ncolumns()) {
        std::cout << "Wrong matrix size";
        return det;
    }
    int degree = 1; // (-1)^(1+j)
    int size = matrix.nrows();

    if (size == 1)
        return matrix[0][0];
    if (size == 2)
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

    for (int j = 0; j < size; j++) {
        Matrix<T> newMatrix = Matrix<int>::MatrixWithoutRowCol(1, j + 1, matrix);
        det = det + (degree * matrix[0][j] * RecursiveDet(newMatrix));
        degree = -degree;
    }
    return det;
}