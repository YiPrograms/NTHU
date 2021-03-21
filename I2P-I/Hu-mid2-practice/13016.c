#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* g[2005];
int kis[2005];
long long sums[2005];
int maxs[2005];
int nums[1000005];

int sortlist[2005];

int cmp(const void *aa, const void *bb) {
    int a = *(int*)aa, b = *(int*)bb;
    if (sums[a] != sums[b])
        return (sums[a] > sums[b]? 1: -1);
    if (maxs[a] != maxs[b])
        return maxs[a] - maxs[b];
    if (kis[a] != kis[b])
        return kis[a] - kis[b];
    return b - a;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        int numnow = 0;
        memset(sums, 0, sizeof(sums));
        memset(maxs, 0, sizeof(maxs));
        for (int i = 0; i < n; i++) {
            int ki;
            scanf("%d", &ki);
            kis[i] = ki;
            g[i] = nums + numnow;
            numnow += ki;
            for (int k = 0; k < ki; k++) {
                int a;
                scanf("%d", &a);
                g[i][k] = a;
                sums[i] += a;
                if (a > maxs[i])
                    maxs[i] = a;
            }
            sortlist[i] = i;
        }
        qsort(sortlist, n, sizeof(int), cmp);
        for (int i = n - 1; i >= 0; i--) {
            int grp = sortlist[i];
            for (int j = 0; j < kis[grp]; j++) {
                printf("%d", g[grp][j]);
                if (j != kis[grp] - 1)
                    printf(" ");
                else
                    printf("\n");
            }
        }
    }
}



