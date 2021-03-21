#include <stdio.h>

int a[15][15];
int p[15][15];
long long ans = -1e16;
int found = 0;
int n;

int check(int x, int y) {
    for (int i = 0; i < n; i++)
        if (p[x][i] != 0)
            return 0;
    for (int i = x; i >= 0; i--)
        if (p[i][y] != 0)
            return 0;
    for (int i = x, j = y; i >= 0 && i < n && j >= 0 && j < n; i--, j--)
        if (p[i][j] != 0)
            return 0;
    for (int i = x, j = y; i >= 0 && i < n && j >= 0 && j < n; i--, j++)
        if (p[i][j] != 0)
            return 0;
    return 1;
}

void prem(long long points, int now) {
    if (now == n) {
        found = 1;
        if (points > ans)
            ans = points;
        return;
    }
    for (int i = 0; i < n; i++) {
        if (check(now, i)) {
            p[now][i] = 1;
            prem(points + a[now][i], now + 1);
            p[now][i] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &a[i][j]);
    prem(0, 0);
    if (found)
        printf("%ld\n", ans);
    else
        printf("no solution\n");
}
