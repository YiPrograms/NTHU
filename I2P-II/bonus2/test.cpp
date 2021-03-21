// C++ Program to count pairs
// of array elements which are
// divisible by K when concatenated
#include <bits/stdc++.h>
using namespace std;

map<int, int> rem[11];

// Function to calculate and return the
// count of pairs
int countPairs(vector<int> a, int n, int k)
{

	vector<int> len(n);

	// Compute power of 10 modulo k
	vector<int> p(11);
	p[0] = 1;
	for (int i = 1; i <= 10; i++) {
		p[i] = (p[i - 1] * 10) % k;
	}

	for (int i = 0; i < n; i++) {
		int x = a[i];

		// Calculate length of a[i]
		while (x > 0) {
			len[i]++;
			x /= 10;
		}

		// Increase count of remainder
		rem[len[i]][a[i] % k]++;
	}

	int ans = 0;

	for (int i = 0; i < n; i++) {

		for (int j = 1; j <= 10; j++) {

			// Calculate (a[i]* 10^lenj) % k
			int r = (a[i] * p[j]) % k;

			// Calculate (k - (a[i]* 10^lenj)% k) % k
			int xr = (k - r) % k;

			// Increase answer by count
			ans += rem[j][xr];
            cout << rem[j][xr] << "\n";

			// If a pair (a[i], a[i]) is counted
			if (len[i] == j
				&& (r + a[i] % k) % k == 0)
				ans--;
		}
	}

	// Return the count of pairs
	return ans;
}

// Driver Code
int main()
{
	vector<int> a = { 45, 1, 10, 12, 11, 7 };
	int n = a.size(), k = 11;
	cout << countPairs(a, n, k);
}

