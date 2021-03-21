#include "function.h"
#include <stdlib.h>
#include <math.h>

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int* ans[50000];

int** s(int* a,int len) {
    qsort(a, len, sizeof(int), cmp);
    int qlen = sqrt(len);
    for (int i = 0; i < qlen; i++) {
        ans[i] = a + qlen * i;
    }
    return ans;
}
