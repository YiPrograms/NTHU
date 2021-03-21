#include <iostream>
#include <queue>
#include <utility>

using namespace std;

char a[1005][1005];
queue<pair<int, pair<int, int>>> q;


int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];
    int ans = -1;
    int tcnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 'I') {
                q.emplace(make_pair(0, make_pair(i, j)));
            } else if (a[i][j] == 'T')
                tcnt++;
        }
    }

    while (!q.empty()) {
        auto f = q.front();
        q.pop();
        int step = f.first;
        int x = f.second.first, y = f.second.second;
        if (x < 0 || x >= n || y < 0 || y >= m || a[x][y] == 'C')
            continue;
        if (a[x][y] == 'T') {
            ans = max(ans, step);
            tcnt--;
        }
        a[x][y] = 'C';
        for (int d = 0; d < 4; d++)
            q.emplace(make_pair(step + 1, make_pair(x + dx[d], y + dy[d])));
    }

    cout << (tcnt == 0? ans: -1) << "\n";
}
