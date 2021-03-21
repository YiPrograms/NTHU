#include <iostream>

using namespace std;

int x[1005], y[1005];
int n, r;
bool vis[1005];


int dfs(int now) {
    vis[now] = true;
    int res = 1;
    for (int i = 0; i < n; i++) {
        if (vis[i])
            continue;
        int dx = x[now] - x[i], dy = y[now] - y[i];
        if (dx*dx + dy*dy <= r*r) {
            res += dfs(i);
        }
    }
    return res;
}

int main() {
    cin >> n >> r;
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];
    int alive = 0, bh = 0;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            int res = dfs(i);
            if (res == 1)
                alive++;
            else
                bh++;
        }
    }
    cout << alive << " " << bh << '\n';
}
