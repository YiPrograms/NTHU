#include <stdio.h>
#include <string.h>

int took[25];

int ok(int n, int k) {
    if (k <= 0)
        return 1;
    int res = 0;
    for (int i = 1; i <= n; i++) {
        if (took[i])
            continue;
        took[i] = 1;
        if (!ok(n, k - i))
            res = 1;
        took[i] = 0;
    }
    return res;
}

int main() {
    int q;
    scanf("%d", &q);
    while (q--) {
        int n, k;
        scanf("%d %d", &n, &k);
        if (ok(n, k))
            printf("True\n");
        else
            printf("False\n");
    }
}
