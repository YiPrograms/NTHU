#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int k = n+1;
    int highest = 0; //bool
    for (int i = 10; i >= 0; i--) {
        if (k & (1 << i)) {
            printf("%d", 1);
            highest = 1;
        } else {
            if (highest) {
                printf("%d", 0);
            }
        }
    }

    int carry = 0;
    for (int i = 0; i <= 10; i++) {
        if (n & (1 << i)) {
            carry += 1;
        } else {
            break;
        }
    }

    printf(" %d", carry);
}