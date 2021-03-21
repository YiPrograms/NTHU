#include <stdio.h>

const long long M = 1e9+7;

void printmat(long long* a) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", a[i*3 + j]);
        }
        printf("\n");
    }
    printf("\n");
}

void matmul(long long* a, long long* b, long long* res) {
    long long tmp[9] = {0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                tmp[i*3 + j] = (tmp[i*3 + j] + a[i*3 + k] * b[k*3 + j]) % M;
            }
        }
    }
    //printmat(a);
    //printf("X\n");
    //printmat(b);
    //printf("=\n");
    //printmat(tmp);
    //printf("-----------\n");
    for (int i = 0; i < 9; i++)
        res[i] = tmp[i];
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        long long x;
        scanf("%ld", &x);
        if (x == 1)
            printf("1\n");
        else if (x == 2)
            printf("12\n");
        else if (x == 3)
            printf("13\n");
        else {
            x -= 3;
            long long a[] = {1, 2, 1, 1, 0, 0, 0, 1, 0};
            long long ans[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
            while (x) {
                if (x & 1)
                    matmul(ans, a, ans);
                matmul(a, a, a);
                x >>= 1;
            }
            printf("%ld\n", (ans[0] * 13 + ans[1] * 12 + ans[2] * 1) % M);
        }
    }
}
