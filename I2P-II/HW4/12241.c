#include <stdio.h>
#include <stdlib.h>

typedef struct Mat_ {
    int a, b, c, d;
} Mat;

const int M = 1e9 + 7;

void printMat(Mat* res) {
    printf("%d %d\n%d %d\n",
    res->a,
    res->b,
    res->c,
    res->d);
}


Mat* matmul(Mat* x, Mat* y) {
    Mat* res = (Mat*)malloc(sizeof(Mat));
    res->a = (x->a * 1LL * y->a + x->b * 1LL * y->c) % M;
    res->b = (x->a * 1LL * y->b + x->b * 1LL * y->d) % M;
    res->c = (x->c * 1LL * y->a + x->d * 1LL * y->c) % M;
    res->d = (x->c * 1LL * y->b + x->d * 1LL * y->d) % M;
//    printf("Mat a\n");
//    printMat(x);
//    printf("Mat b\n");
//    printMat(y);
//    printf("Mat axb\n");
//    printMat(res);
//    printf("\n");
    return res;
}

Mat* getMat(int a, int b, int c, int d) {
    Mat* res= (Mat*) malloc(sizeof(Mat));
    res->a = a;
    res->b = b;
    res->c = c;
    res->d = d;
//    printf("Get Mat %d %d %d %d\n", a, b, c, d);
//    printMat(res);
//    printf("\n");
    return res;
}

Mat* fpow(Mat* a, long long y) {
    if (y == 0) {
        free(a);
        return getMat(1, 0, 0, 1);
    }
    Mat* amula = matmul(a, a);
    Mat* res = fpow(amula, y/2);
//    printf("Res Mat\n");
//    printMat(res);
//    printf("\n");
    if (y & 1) {
        Mat* newres = matmul(res, a);
        free(res);
        res = newres;
    }
    free(a);
//    printMat(res);
    return res;
}

int main() {
    long long i;
    while (~scanf("%ld", &i)) {
        if (i <= 2)
            printf("1\n");
        else {
            Mat* x = getMat(1, 1, 1, 0);
            Mat* res = fpow(x, i-2);
            printf("%d\n", (res->a + res->b) % M);
        }
    }
}
