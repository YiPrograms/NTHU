#include <stdio.h>

int k;
char a[5][5];
char b[5][5];

int check() {
    //for (int i = 0; i < 3; i++)
    //    printf("%s\n", a[i]);
    //printf("\n");
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (a[i][j] != b[i][j])
                return 0;
    return 1;
}

const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};

int dfs(int x, int y, int now) {
    if (check())
        return 1;
    if (now == k)
        return 0;
    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx < 0 || nx >= 3 || ny < 0 || ny >= 3)
            continue;
        a[x][y] = a[nx][ny];
        a[nx][ny] = 'x';
        if (dfs(nx, ny, now + 1))
            return 1;
        a[nx][ny] = a[x][y];
        a[x][y] = 'x';
    }
    return 0;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &k);
        for (int i = 0; i < 3; i++)
            scanf("%s", a[i]);
        for (int i = 0; i < 3; i++)
            scanf("%s", b[i]);
        int ok;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (a[i][j] == 'x')
                    ok = dfs(i, j, 0);
        if (ok)
            printf("Yes\n");
        else
            printf("No\n");
    }
}
