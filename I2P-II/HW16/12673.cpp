#include <iostream>
#include <cstring>

using namespace std;

int l[5005], r[5005];

int wall[5005];

int onlyone[5005];

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 1; i <= q; i++)
            cin >> l[i] >> r[i];

        memset(wall, 0, sizeof(wall));
        for (int i = 1; i <= q; i++)
            for (int k = l[i]; k <= r[i]; k++)
                wall[k]++;

        int ans = 0;

        for (int a = 1; a <= q; a++) {
            for (int k = l[a]; k <= r[a]; k++)
                wall[k]--;

            memset(onlyone, 0, sizeof(onlyone));
            for (int i = 1; i <= n; i++)
                onlyone[i] = onlyone[i - 1] + (wall[i] == 1);

            int guarded = 0;
            for (int i = 1; i <= n; i++)
                guarded += (wall[i] > 0);

            for (int b = 1; b <= q; b++) {
                if (a == b)
                    continue;
                const int deguard = onlyone[r[b]] - onlyone[l[b] - 1];
                ans = max(ans, guarded - deguard);
            }

            for (int k = l[a]; k <= r[a]; k++)
                wall[k]++;
        }
        cout << ans << "\n";
    }
}
