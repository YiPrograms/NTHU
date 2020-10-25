#include <stdio.h>

const int M = 1e9+7;

void matmul(int* a, int* b, int* res) {
    int r0 = (a[0]*1LL*b[0] + a[1]*1LL*b[2]) % M;
    int r1 = (a[0]*1LL*b[1] + a[1]*1LL*b[3]) % M;
    int r2 = (a[2]*1LL*b[0] + a[3]*1LL*b[2]) % M;
    int r3 = (a[2]*1LL*b[1] + a[3]*1LL*b[3]) % M;
    res[0] = r0, res[1] = r1, res[2] = r2, res[3] = r3;
}


int main() {
    long long n;
    while (~scanf("%lld", &n)) {
        if (n <= 2)
            printf("1\n");
        else {
            n -= 2;
            int x[] = {1, 1, 1, 0};
            int ans[] = {1, 0, 0, 1};
            while (n != 0) {
                if (n & 1) {
                    matmul(ans, x, ans);
                }
                matmul(x, x, x);
                n >>= 1;
            }
            printf("%d\n", (ans[0] + ans[1]) % M);
        }
    }
}
