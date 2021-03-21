#include "function.h"
#include <stdlib.h>


unsigned*** new_3d_array(unsigned n,unsigned m,unsigned k) {
    unsigned int ***a = malloc(n * sizeof(unsigned int **));
    unsigned int **b = malloc(n*m * sizeof(unsigned int *));
    unsigned int *c = malloc(n*m*k * sizeof(unsigned int));
    for (int i = 0; i < n; i++) {
        a[i] = &b[m*i];
        for (int j = 0; j < m; j++)
            a[i][j] = &c[m*k*i + k*j];
    }
    return a;
}

void delete_3d_array(unsigned ***arr) {
    free(arr[0][0]);
    free(arr[0]);
    free(arr);
}

