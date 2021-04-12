#include <bits/stdc++.h>
using namespace std;

vector<int> slots[15];

int main() {
    int t;
    cin >> t;
    while (t--) {
        int l, r;
        cin >> l >> r;
        cin.get();
        int mx = -1;
        for (int i = 0; i < 10; i++)
            slots[i].clear();
        while (r--) {
            string ln;
            getline(cin, ln);
            stringstream ss(ln);
            int sl;
            ss >> sl;
            int v;
            while (ss >> v)
                slots[sl].emplace_back(v);
            mx = max(mx, int(slots[sl].size()));
        }
       /* for (int i = 0; i < l; i++) {
            for (int k: slots[i])
                cout << k << " ";
            cout << "\n";
        }*/
        long long ans = 0;
        for (int i = 0; i < mx; i++) {
            long long res = 0;
            for (int j = 0; j < l; j++) {
                if (i < slots[j].size())
                    res += slots[j][i];
                res *= 10;
            }
            res /= 10;
            ans += res;
        }
        cout << ans << "\n";
    }
}
