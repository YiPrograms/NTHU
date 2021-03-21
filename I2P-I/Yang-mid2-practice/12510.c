#include <stdio.h>

int n, m;

char a[1005][1005];

int tpx[1000005], tpy[1000005], tps;

const int dx[] = {1, -1, 0, 0},
          dy[] = {0, 0, 1, -1};

int vist = 0;

int dfs(int x, int y) {
    int now = a[x][y];
    a[x][y] = '#';

    if (x == n-1 && y == m-1)
        return 1;

    if (now == 'T' && !vist) {
        vist = 1;
        for (int i = 0; i < tps; i++) {
            if (tpx[i] == x && tpx[i] == y || a[tpx[i]][tpy[i]] != 'T')
                continue;
            if (dfs(tpx[i], tpy[i]))
                return 1;
        }
    }

    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx < 0 || nx >= n || ny < 0 || ny >= m || a[nx][ny] == '#')
            continue;
        if (dfs(nx, ny))
            return 1;
    }
    return 0;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++)
            scanf("%s", a[i]);
        tps = 0;
        vist = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (a[i][j] == 'T')
                    tpx[tps] = i, tpy[tps] = j, tps++;

        if (dfs(0, 0))
            printf("Yes\n");
        else
            printf("No\n");
    }
}
