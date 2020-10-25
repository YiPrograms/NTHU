#include <stdio.h>

unsigned long long a[120];

int main() {
    a[0] = a[1] = a[2] = 1;
    for (int i = 3; i <= 116; i++)
        a[i] = a[i-1] + a[i-3];
    int n;
    scanf("%d", &n);
    printf("%lu\n", a[n]);
}
