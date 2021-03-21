#include <stdio.h>

long long s[1000005];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int ei;
        scanf("%d", &ei);
        s[i] = s[i-1] + ei;
    }
    int q;
    scanf("%d", &q);
    while (q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%ld\n", s[r] - s[l-1]);
    }
}
