#include <bits/stdc++.h>

using namespace std;

int dis[105][105];

const int INF = 1e9;

int main() {
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        cout << "Testcase" << tt << "\n";
        int n, q;
        cin >> n >> q;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int v;
                cin >> v;
                if (v == 0)
                    v = INF;
                dis[i][j] = v;
            }
        }

        for (int i = 0; i < n; i++)
            dis[i][i] = 0;

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dis[i][k] + dis[k][j] < dis[i][j])
                        dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }

        while (q--) {
            int a, b;
            cin >> a >> b;
            cout << "Cost(" << a << "," << b << "):";
            if (dis[a][b] == INF)
                cout << "No Service\n";
            else
                cout << dis[a][b] << "\n";
        }

    }
}
