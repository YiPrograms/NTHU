#include <iostream>
#include <cstring>

using namespace std;

int eqi[int(1e5) + 5];
int pri[int(1e5) + 5];

int main() {
    int t;
    cin >> t;
    while (t--) {
        memset(eqi, 0, sizeof(pri));
        memset(pri, 0, sizeof(pri));
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        for (int x = a; x <= b; x++) {
            eqi[x + b]++;
            eqi[x + c + 1]--;
        }

        for (int i = 1; i <= b + c; i++) {
            eqi[i] += eqi[i - 1];
            pri[i] = pri[i - 1] + eqi[i];
        }

        long long ans = 0;
        for (int z = c; z <= d; z++) {
            if (z <= b + c)
                ans += pri[b + c] - pri[z];
        }

        cout << ans << "\n";
    }
}
