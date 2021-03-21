#include "function.h"
using namespace std;

int n;
Dish dish;

int main() {
	cin >> n;
	while(n--) {
		cin >> dish;
		cout << dish.getFood() << endl;
	}
	return 0;
}
