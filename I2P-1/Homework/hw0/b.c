#include <stdio.h>

int main() {
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    int sum = (x + y + z) / 2;
    printf("%d %d %d\n", sum - y, sum - z, sum - x);
}
