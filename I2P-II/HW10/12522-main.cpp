#include <iostream>
#include "function.h"
using namespace std;

int r, c;
long long times;
char op;
Matrix M, ans;

Matrix fast_add(Matrix mat, long long t) {
	Matrix rtn(mat.getrow(), mat.getcol());
	for(; t; t >>= 1) {
		if(t&1) rtn = rtn + mat;
		mat = mat + mat;
	}
	return rtn;
}

Matrix fast_mul(Matrix mat, long long t) {
	Matrix rtn(mat.getrow(), mat.getcol());
	for(int i = 0; i < mat.getrow(); i++)
		rtn[i][i] = 1;
	for(; t; t >>= 1) {
		if(t&1) rtn = rtn * mat;
		mat = mat * mat;
	}
	return rtn;
}

int main() {
	cin >> r >> c >> times >> op;
	M = Matrix(r, c);
	for(int i=0, tmp;i<r;i++) for(int j=0;j<c;j++) {
		cin >> tmp;
		M[i][j] = tmp % MOD;
	}
	switch (op) {
		case '+':
			ans = fast_add(M, times);
			break;
		case '*':
			ans = fast_mul(M, times);
			break;
	}
	ans.print();
	return 0;
}
