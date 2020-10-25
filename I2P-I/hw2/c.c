#include <stdio.h>

int a[505][505];

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int main() {
    int n;
    scanf("%d", &n);
    n *= 2;
    int orgn = n;
    int first = 0;
    int now = 1;
    int d = 0, x = 0, y = -1;
    while (n > 0) {
        for (int i = 0; i < n; i++) {
            x += dx[d];
            y += dy[d];
            a[x][y] = now;
            now++;
        }
        d++;
        if (d == 4) d = 0;
        if (first) {
            first = 0;
        } else {
            n--;
            first = 1;
        }
    }
    for (int i = 0; i < orgn; i++) {
        for (int j = 0; j < orgn; j++) {
            printf("%d", a[i][j]);
            if (j == orgn - 1)
                printf("\n");
            else
                printf(" ");
        }
    }
}
