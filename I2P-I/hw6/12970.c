#include <stdio.h>

int w[25], v[25];

int n, m;
long long ans = -1;

void prem(int now, int wei, long long val) {
    if (wei > m)
        return;
    if (val > ans)
        ans = val;
    for (int i = now + 1; i < n; i++)
        prem(i, wei + w[i], val + v[i]);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &w[i], &v[i]);
    }
    prem(-1, 0, 0);
    printf("%lld\n", ans);
}
