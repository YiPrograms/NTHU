#include <stdio.h>

int aa[105][105], bb[105][105];

int main() {
    int n, m;
    int (*a)[105] = aa;
    int (*b)[105] = bb;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &a[i][j]);

    int q;
    scanf("%d", &q);
    q %= 4;
    while (q--) {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) 
                b[i][j] = a[n-1 - j][i];
        int tmp = n;
        n = m;
        m = tmp;

        int (*t)[105] = a;
        a = b;
        b = t;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            printf("%d", a[i][j]);
            if (j == m - 1)
                printf("\n");
            else
                printf(" ");
        }
}
