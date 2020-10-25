#include <stdio.h>

int a[505][505];

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int main() {
    int n;
    scanf("%d", &n);
    n *= 2;
    int d = 0, x = 0, y = 0;
    int now = 1;
    while (now <= n*n) {
        a[x][y] = now;
        now++;
        x += dx[d];
        y += dy[d];
        if (x < 0 || y < 0 || x >= n || y >= n || a[x][y] != 0) {
            x -= dx[d];
            y -= dy[d];
            d++;
            if (d == 4) d = 0;
            x += dx[d];
            y += dy[d];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", a[i][j]);
            if (j == n - 1)
                printf("\n");
            else
                printf(" ");
        }
    }
}
