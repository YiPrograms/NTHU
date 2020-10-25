#include <stdio.h>
#include <stdlib.h>


int main() {
    int* a = (int*)calloc(105, sizeof(int));
    int* b = (int*)calloc(105, sizeof(int));
    int an;
    scanf("%d", &an);
    for (int i = 0; i < an; i++)
        scanf("%1d", a + 100-an + i);
    int bn;
    scanf("%d", &bn);
    for (int i = 0; i < bn; i++)
        scanf("%1d", b + 100-bn + i);
    int neg_flag = 0;
    for (int i = 0; i < 100; i++) {
        if (b[i] > a[i]) {
            neg_flag = 1;
            int* tmp = a;
            a = b;
            b = tmp;
            break;
        } else if (b[i] < a[i])
            break;
    }
    for (int i = 0; i < 100; i++) {
        a[i] -= b[i];
    }
    for (int i = 99; i > 0; i--) {
        if (a[i] < 0) {
            a[i] += 10;
            a[i-1]--;
        }
    }
    if (neg_flag)
        printf("-");
    int zero_flag = 1;
    for (int i = 0; i < 100; i++) {
        if (zero_flag && a[i] == 0) {
            continue;
        } else {
            zero_flag = 0;
        }
        
        printf("%d", a[i]);
    }
    if (zero_flag)
        printf("0");
}
