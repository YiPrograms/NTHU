#include "function.h"
#include <stdlib.h>

int a, b, c;
unsigned*** new_3d_array(unsigned n,unsigned m,unsigned k) {
    a = n, b = m, c = k;
    unsigned int*** a = malloc(n * sizeof(unsigned int**));
    for (int i = 0; i < n; i++) {
        a[i] = malloc(m * sizeof(unsigned int*));
        for (int j = 0; j < m; j++) {
            a[i][j] = malloc(k * sizeof(unsigned int));
        }
    }
    return a;
}

void delete_3d_array(unsigned ***arr) {
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            free(arr[i][j]);
        }
        free(arr[i]);
    }
    free(arr);    
}

