#include <stdio.h>

int a[(int)2e6 + 5];

int main() {
    int n, q;
    while (~scanf("%d %d", &n, &q)) {
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        while (q--) {
            int x;
            scanf("%d", &x);

            int l = 1, r = n;
            int res = -1;
            while (l <= r) {
                int m = (l + r) >> 1;
                if (a[m] == x) {
                    res = m;
                    break;
                }

                if (x > a[m])
                    l = m + 1;
                else
                    r = m - 1;
            }

            if (res == -1)
                printf("Break your bridge!\n");
            else
                printf("%d\n", res);
        }
    }
}
