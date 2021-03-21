#include <stdio.h>

char a[105][105];
int r, c;
int shortest = 1e9;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int dfs(int x, int y, int d) {
    if (x < 0 || x >= r || y < 0 || y >= c || a[x][y] == '#')
        return 0;
    if (a[x][y] == 'F') {
        if (d < shortest)
            shortest = d;
        return 1;
    }
    
    int res = 0;

    a[x][y] = '#';
    for (int i = 0; i < 4; i++)
        res += dfs(x + dx[i], y + dy[i], d + 1);
    a[x][y] = '$';

    return res;
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        scanf("%d %d", &r, &c);
        for (int i = 0; i < r; i++)
            scanf("%s", a[i]);
        
        int sx, sy;
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                if (a[i][j] == 'S')
                    sx = i, sy = j;
        shortest = 1e9;
        int ans = dfs(sx, sy, 0);
        if (ans == 0)
            printf("0 -1\n");
        else
            printf("%d %d\n", ans, shortest);
    }
}
