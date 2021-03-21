#include <stdio.h>

char a[305][305];

int n, m;

int px[30], py[30];

const int dx[] = {1, -1, 0, 0},
          dy[] = {0, 0, 1, -1};

int dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m)
        return 0;
    char now = a[x][y];
    if (now == '#')
        return 0;
    if (now == '&')
        return 1;

    a[x][y] = '#';

    if (now >= 'a' && now <= 'z') {
        return dfs(px[now - 'a'], py[now - 'a']);
    } else {
        for (int d = 0; d < 4; d++) {
            if (dfs(x + dx[d], y + dy[d]))
                return 1;
        }
        return 0;
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++)
            scanf("%s", a[i]);
        int sx, sy;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (a[i][j] >= 'A' && a[i][j] <= 'Z')
                    px[a[i][j] - 'A'] = i, py[a[i][j] - 'A'] = j;
                else if (a[i][j] == '$')
                    sx = i, sy = j;
            }
        }
        if (dfs(sx, sy))
            printf("Yes\n");
        else
            printf("No\n");
    }
}
