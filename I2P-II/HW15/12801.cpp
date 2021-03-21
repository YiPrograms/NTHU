#include <iostream>
#include <algorithm>

using namespace std;

int a[int(2e5) + 5];

int n, m;

bool check(int d) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i] - i/d;
        if (sum >= m)
            return true;
    }
    return false;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 0; i < n; i++)
            cin >> a[i];

        int ans = -1;
        int l = 1, r = n + 1, m;
        while (r > l) {
            m = (l + r) >> 1;
            if (check(m))
                ans = r = m;
            else
                l = m + 1;
        }
        
        cout << ans << "\n";
    }
}
