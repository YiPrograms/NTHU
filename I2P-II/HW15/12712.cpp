#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        long long ans = 2e18;
        for (int i = 0; i <= 60; i++) {
            const long long tim1 = (1LL << i) - 1;

            long long l = 0, r = min(3e9, 1e18 / tim1), m;
            while (r >= l) {
                m = (l + r) >> 1;
                const long long k = 2*m + 1;
                const long long y = k * tim1  + ((k * (k-1)) >> 1);
                //if (i == 2)
                //    cout << m << " " << k << " " << y << "\n";
                if (y == n) {
                    ans = min(ans, (1LL << i) * k);
                    break;
                } else if (y > n)
                    r = m - 1;
                else 
                    l = m + 1;
            }
        }
        cout << (ans == 2e18? -1LL: ans) << "\n";
    }
}
