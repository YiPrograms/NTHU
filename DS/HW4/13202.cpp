#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;
vector<pii> e[105];

int dis[105][105];
vector<int> route[105][105];
double sum[105];

const int INF = 1e9;

vector<int> merge_route(vector<int> &a, vector<int> &b) {
    vector<int> res = a;
    res.insert(res.end(), b.begin(), b.end());
    return res;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int v;
            cin >> v;
            if (v != 0) {
                e[i].emplace_back(j, v);
                dis[i][j] = v;
                route[i][j].emplace_back(j);
            } else {
                dis[i][j] = INF;
            }
        }
    }

    for (int i = 0; i < n; i++)
        dis[i][i] = 0;

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dis[i][k] == INF || dis[k][j] == INF)
                    continue;
                if (dis[i][k] + dis[k][j] < dis[i][j] ||
                    dis[i][k] + dis[k][j] == dis[i][j] &&
                    merge_route(route[i][k], route[k][j]) < route[i][j]) {
                    
                    dis[i][j] = dis[i][k] + dis[k][j];
                    route[i][j] = merge_route(route[i][k], route[k][j]);
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j || dis[i][j] == INF)
                continue;
            cout << "Path(" << i << "," << j << "):" << i;
            for (int v: route[i][j])
                cout << "->" << v;
            cout << "\n";
            cout << "Difficulty:" << dis[i][j] << "\n";
            sum[j] += 1.0 / dis[i][j];
        }
    }

    cout << fixed << setprecision(3);
    for (int i = 0; i < n; i++)
        cout << "Centrality(" << i << "):" << sum[i] << "\n";
}
