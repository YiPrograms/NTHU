#include <iostream>
#include <cstring>
#include <iomanip>
const int MAX_N = 102;
const int MOD = 10007;

class Matrix {
	public:
		Matrix() {
			row = col = 0;
			memset(mat, 0, sizeof(mat));
		}
		// TODO
		Matrix(int r, int c);
		const int &getrow() {
			return row;
		}
		const int &getcol() {
			return col;
		}
		// TODO
		int *operator[] (const int &x);
		const int *operator[] (const int &x) const {
			return mat[x];
		}
		// TODO
		Matrix operator+ (const Matrix &x) const;
		// TODO: be aware that this function is declared with friend!!!
		friend Matrix operator* (const Matrix &x, const Matrix &y);
		void print() {
			for(int i=0;i<row;i++) {
				if(i==0) std::cout << "/";
				else if(i==row-1) std::cout << "\\";
				else std::cout << "|";
				for(int j=0;j<col;j++) {
					std::cout << std::right << std::setw(8) << mat[i][j];
				}
				if(i==0) std::cout << " \\\n";
				else if(i==row-1) std::cout << " /\n";
				else std::cout << " |\n";
			}
		}
	private:
		int mat[MAX_N][MAX_N];
		int row, col;
};
