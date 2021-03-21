#include<iostream>
#include<algorithm>
#include<string> 
using namespace std; 
#define MAX_N 1000
#define MAX_Bit 5
#define MAX 100000
class BigInt{
	public:
		int sign; // 正負號
		long long m[MAX_N];
		int l; //長度
		long long operator [](int i) const { return m[i]; }
		long long &operator [](int i) { return m[i]; }
		BigInt(){ l=1, m[0]=0; sign=1; }
		BigInt(int x){ (*this)=x; }
		BigInt(const char *s){ (*this)=s; }
        friend istream& operator>>(istream&, BigInt&);   
        friend ostream& operator<<(ostream&, BigInt);   
        BigInt operator +( const BigInt &y );  
        BigInt operator -( const BigInt &y );      
};



