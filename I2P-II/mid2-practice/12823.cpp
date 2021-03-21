#include <iostream>
#include <cstring>

using namespace std;

int n, r, k;

bool vis[505];

int x[505], y[505];

int dfs(int now) {
    vis[now] = true;
    int siz = 1;
    for (int i = 0; i < n; i++) {
        if (vis[i])
            continue;
        int dx = x[now] - x[i], dy = y[now] - y[i];
        if (dx*dx + dy*dy <= r*r)
            siz += dfs(i);
    }
    return siz;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> r >> k;
        for (int i = 0; i < n; i++)
            cin >> x[i] >> y[i];

        memset(vis, 0, sizeof(vis));
        int lk = 0, gk = 0;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                int siz = dfs(i);
                if (siz >= k)
                    gk++;
                else
                    lk++;
            }
        }
        cout << lk << " " << gk << "\n";
    }
}
