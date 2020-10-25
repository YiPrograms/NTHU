#include <stdio.h>

int fpow(long long x, long long y, int m) {
    if (y == 0)
        return 1 % m;
    long long res = fpow((x * x) % m, y/2, m);
    if (y & 1)
        res = (res * x) % m;
    return res;
}

int main() {
    long long x, y;
    int m;
    scanf("%ld %ld %d", &x, &y, &m);
    printf("%d\n", fpow(x % m, y, m));
}
