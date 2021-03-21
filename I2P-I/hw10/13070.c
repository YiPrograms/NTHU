#include <stdio.h>
#include <stdlib.h>

int a[100005];

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    qsort(a, n, sizeof(int), cmp);
    int q;
    int xp = 0, yp = 0;
    scanf("%d", &q);
    while (q--) {
        int op, x;
        scanf("%d %d", &op, &x);
        if (op == 1) {
            while (xp < n && a[xp] < x)
                xp++;

            while (xp < n && a[xp] == x) {
                a[xp] = -1;
                xp++;
            }
        } else {
            while (yp < n && a[yp] < x)
                yp++;

            if (a[yp] == x)
                printf("Yes\n");
            else
                printf("No\n");
        }
    }
}
