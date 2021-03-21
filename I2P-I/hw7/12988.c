#include <stdio.h>

int a[15];
int n, k;

int sums[7];

int prem(int now) {
    if (now == n) {
        for (int i = 1; i < k; i++)
            if (sums[i] != sums[i-1])
                return 0;
        return 1;
    }

    for (int i = 0; i < k; i++) {
        sums[i] += a[now];
        if (prem(now + 1))
            return 1;
        sums[i] -= a[now];
    }
    return 0;
}

int main() {
    int q;
    scanf("%d", &q);
    while (q--) {
        memset(sums, 0, sizeof(sums));
        scanf("%d %d", &n, &k);
        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);
        if (prem(0))
            printf("True\n");
        else
            printf("False\n");
    }
}
