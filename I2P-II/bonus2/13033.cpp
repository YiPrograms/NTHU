#include <iostream>
#include <cmath>
#include <map>

using namespace std;

int a[int(2e5) + 5];

map<int, int> m[15];

int main() {
    int n, k;
    while (cin >> n >> k) {
        for (int i = 0; i <= 10; i++)
            m[i].clear();
        for (int i = 0; i < n; i++)
            cin >> a[i];
        for (int i = 0; i < n; i++) {
            int dig = log10(a[i]) + 1;
            m[dig][a[i] % k]++;
        }
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            int tmp = a[i] % k;
            for (int l = 1; l <= 10; l++) {
                tmp = (tmp * 10) % k;
                auto f = m[l].find((k - tmp) % k);
                if (f == m[l].end())
                    continue;
                ans += (*f).second;
                if (l == int(log10(a[i]) + 1) && a[i] % k == (k - tmp) % k)
                    ans--;
            }
        }
        cout << ans << "\n";
    }
}
