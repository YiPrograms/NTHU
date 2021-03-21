#include "function.h"
#include<iostream>
#include<string> 
using namespace std; 



int main(){
	BigInt a, b;
    while( cin >> a >> b ){
		cout << (a+b) << '\n';
		cout << (a-b) << '\n';
	}
    return 0;
}
