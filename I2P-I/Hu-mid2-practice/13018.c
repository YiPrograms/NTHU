#include "function.h"
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(long long*)a - *(long long*)b > 0)? 1: -1;
}

long long list[505];

void array2d_sort(int row, int col, long long arr[][500]) {
    for (int i = -col + 1; i < row; i++) {
        int len = 0;
        for (int j = 0; j < col; j++) {
            if (i + j < 0 || i + j >= row)
                continue;
            list[len++] = arr[i + j][j];
        }
        qsort(list, len, sizeof(long long), cmp);
        int now = 0;
        for (int j = 0; j < col; j++) {
            if (i + j < 0 || i + j >= row)
                continue;
            arr[i + j][j] = list[now++];
        }
    }
}

