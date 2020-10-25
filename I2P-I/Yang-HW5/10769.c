#include <stdio.h>

int a[25][25];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &a[i][j]);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%d",a[i-j][j]);
            if (j == i)
                printf("\n");
            else
                printf(" ");
        }
    }
    for (int i = n-2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            printf("%d",a[n-1-j][n-1-i+j]);
            if (j == i)
                printf("\n");
            else
                printf(" ");
        }
    }
}
