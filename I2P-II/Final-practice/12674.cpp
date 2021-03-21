#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int a[3];
        cin >> a[0] >> a[1] >> a[2];

        sort(a, a + 3);

        int ans = 0;
        if (a[2] - a[1] >= a[0]) {
            ans += a[0];
            a[2] -= a[0];
            ans += min(a[1], a[2]);
        } else {
            ans += a[2] - a[1];
            a[0] -= a[2] - a[1];
            a[2] = a[1];
            ans += a[0] / 2 * 2;
            ans += a[2] - a[0] / 2;
        }
        cout << ans << "\n";
    }
}
