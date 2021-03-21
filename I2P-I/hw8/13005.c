#include <stdio.h>

int tile(int n, int k) {
    if (n < 0)
        return 0;
    if (k == 0) {
        if (n == 0)
            return 1;
        return tile(n - 2, 0) + 2*tile(n - 1, 1);
    } else {
        if (n == 0)
            return 0;
        return tile(n - 1, 0) + tile(n - 2, 1);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", tile(n, 0));
}
