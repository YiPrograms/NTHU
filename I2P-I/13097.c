#include <stdio.h>
#include <stdlib.h>

long long a[(int)1e5 + 5];

int cmp(const void *a, const void *b) {
    return *(long long *)a > *(long long *)b? 1: -1;
}

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);

    qsort(a + 1, n, sizeof(long long), cmp);

    int del_cnt = 0;
    int del_start = 1e9;
    int shift_cnt = 0;

    int q;
    scanf("%d", &q);
    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 1) {
            int del = (n & 1)? (n/2 + 1): (n/2);
            if (del >= del_start)
                del += del_cnt;
            else
                del_start = del;
            
            del_cnt++;
            n--;
        } else if (type == 2) {
            int k;
            scanf("%d", &k);

            if (shift_cnt >= 64) {
                printf("0\n");
                continue;
            }

            if (k >= del_start)
                k += del_cnt;

            printf("%lld\n", a[k] >> shift_cnt);
            shift_cnt++;
        }
    }

}
