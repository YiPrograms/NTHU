#include <stdio.h>

int main() {
    float f;
    while (~scanf("%f", &f)) {
        unsigned int* k = &f;
        for (int i = 31; i >= 0; i--) {
            if (*k & (1 << i)) {
                printf("1");
            } else {
                printf("0");
            }
        }
        printf("\n");
    }
}
