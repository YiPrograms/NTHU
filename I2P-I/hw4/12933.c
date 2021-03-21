#include <stdio.h>

int a[1005][1005];

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &a[i][j]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            printf("%d", a[j][i]);
            if (j == m-1)
                printf("\n");
            else
                printf(" ");
        }

}
