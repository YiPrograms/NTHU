#include <iostream>
#include <algorithm>
using namespace std;

int num[5005];

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        for (int i = 0; i < n; i++)
            cin >> num[i];

        if (k >= m)
            k = m - 1;

        int res = -1;
        for (int a = 0; a <= k; a++) {
            int at_least = 2e9;
            for (int b = 0; b <= (m - 1 - k); b++)
                at_least = min(at_least, max(num[a + b], num[n-1 - ((m - k - 1) - b) - (k - a)]));
            res = max(res, at_least);
        }
        cout << res << "\n";
    }
}
