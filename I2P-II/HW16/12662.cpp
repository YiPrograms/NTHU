#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int a[int(3e5) + 5];
long long pri[int(3e5) + 5];


int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, p, k;
        cin >> n >> p >> k;

        for (int i = 1; i <= n; i++)
            cin >> a[i];

        sort(a + 1, a + 1 + n);

        pri[0] = 0;
        for (int i = 1; i <= n; i++) {
            if (i >= k)
                pri[i] = min(pri[i - k] + a[i], pri[i - 1] + a[i]);
            else
                pri[i] = pri[i - 1] + a[i];
        }

        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (pri[i] > p)
                continue;

            ans = i;
        }

        cout << ans << "\n";
    }
}
