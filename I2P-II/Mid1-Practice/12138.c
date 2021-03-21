#include <stdio.h>

long long a[(int)1e6 + 5];

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        int k;
        scanf("%d", &k);
        if (k >= 0)
            a[i] = a[i-1] + k;
        else
            a[i] = a[i-1];
    }
    while (q--) {
        int l, r, m;
        scanf("%d %d %d", &l, &r, &m);
        printf("%ld\n", a[l + (m-1)] - a[l-1]);
    }
}
