#include <stdio.h>
#include <stdlib.h>

const int M = 1e9+7;

void matmul(int* a, int* b, int* res) {
    int a0 = (a[0] * 1LL * b[0] + a[1] * 1LL * b[2]) % M;
    int a1 = (a[0] * 1LL * b[1] + a[1] * 1LL * b[3]) % M;
    int a2 = (a[2] * 1LL * b[0] + a[3] * 1LL * b[2]) % M;
    int a3 = (a[2] * 1LL * b[1] + a[3] * 1LL * b[3]) % M;
    res[0] = a0;
    res[1] = a1;
    res[2] = a2;
    res[3] = a3;
}

void fpow(int* x, long long y, int* res) {
    if (y == 0) {
        res[0] = 1;
        res[1] = 0;
        res[2] = 0;
        res[3] = 1;
        return;
    }
    int* tmp = malloc(sizeof(int) * 4);
    matmul(x, x, tmp);
    fpow(tmp, y/2, res);
    free(tmp);
    if (y & 1)
        matmul(res, x, res);
    return;
}

int main() {
    long long n;
    while (~scanf("%ld", &n)) {
        if (n <= 2) {
            printf("1\n");
        } else {
            int x[] = {1, 1, 1, 0};
            int* res = malloc(sizeof(int) * 4);
            fpow(x, n - 2, res);
            printf("%d\n", (res[0] + res[1]) % M);
        } 
    }
}
