#include <stdio.h>

int prime[105];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        if (prime[i] != -1) {
            for (int j = i*i; j <= n; j *= i)
                prime[j] = -1;
        }
        int k = i;
        for (int j = 2; j <= i; j++) {
            if (prime[j] != -1) {
                while (k % j == 0) {
                    k /= j;
                    prime[j]++;
                }
            }
        }
    }
    unsigned long long ans = 1;
    for (int i = 2; i <= n; i++) {
        if (prime[i] != -1)
            ans *= prime[i] + 1;
    }
    printf("%lu", ans);
}
