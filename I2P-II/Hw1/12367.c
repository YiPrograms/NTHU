#include <stdio.h>

long long s[2000005];

int main() {
    int n, q;
    while (~scanf("%d %d", &n, &q)) {
        for (int i = 1; i <= n; i++) {
            int k;
            scanf("%d", &k);
            s[i] = s[i-1] + k;
        }
        int max_a, max_b;
        long long max_sum = -1;
        while (q--) {
            int a, b;
            scanf("%d %d", &a, &b);
            long long sum;
            if (a > b) {
                sum = s[b] + s[n] - s[a-1];
            } else {
                sum = s[b] - s[a-1];
            }
            if (sum > max_sum) {
                max_a = a;
                max_b = b;
                max_sum = sum;
            }
        }
        printf("Max_range: (%d,%d); Value: %lld\n", max_a, max_b, max_sum);
    }
}
