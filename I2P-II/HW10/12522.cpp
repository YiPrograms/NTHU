#include "function.h"
#include <cstring>
using namespace std;

const int M = 10007;

Matrix::Matrix(int r, int c) {
    row = r;
    col = c;
	memset(mat, 0, sizeof(mat));
}

int *Matrix::operator[] (const int &x) {
	return mat[x];
}

Matrix Matrix::operator+ (const Matrix &x) const {
    Matrix res{row, col};
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            res[i][j] = ((mat[i][j] + x[i][j]) % M + M) % M;
    return res;
}

Matrix operator* (const Matrix &x, const Matrix &y) {
    Matrix res{x.row, y.col};
    for (int i = 0; i < x.row; i++) {
        for (int j = 0; j < y.col; j++) {
            for (int k = 0; k < x.col; k++) {
                res[i][j] = ((res[i][j] + (x[i][k] * y[k][j])) % M + M) % M;
            }
        }
    }
    return res;
}


