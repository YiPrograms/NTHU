#include <stdio.h>

int b[25][25];
int n, m;
int ans = -1;

int check() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (b[i][j] != 1)
                return 0;
    return 1;
}

void sw(int i, int j) {
    b[i][j] ^= 1;
    if (i - 1 >= 0)
        b[i - 1][j] ^= 1;
    if (j - 1 >= 0)
        b[i][j - 1] ^= 1;
    if (i + 1 < n)
        b[i + 1][j] ^= 1;
    if (j + 1 < m)
        b[i][j + 1] ^= 1;
}

void prem(int now, int i, int j) {
    if (check()) {
        if (ans == -1 || now < ans)
            ans = now;
        return;
    }
    if (i == n)
        return;

    int nxti = i, nxtj = j + 1;
    if (nxtj >= m) {
        nxtj = 0;
        nxti++;
    }

    prem(now, nxti, nxtj);

    sw(i, j);
    prem(now + 1, nxti, nxtj);
    sw(i, j);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &b[i][j]);
    prem(0, 0, 0);
    if (ans == -1)
        printf("no solution\n");
    else
        printf("%d\n", ans);
}
