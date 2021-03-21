#include <stdio.h>
#include <stdlib.h>


int post[105];
int in[105];

void printpre(int pl, int pr, int il, int ir) {
    if (pl > pr || il > ir)
        return;
    int now = post[pr];
    printf("%d ", now);
    int k;
    for (k = 0; il + k <= ir; k++)
        if (in[il + k] == now)
            break;
    printpre(pl, pl+k-1, il, il+k-1);
    printpre(pl+k, pr-1, il+k+1, ir);
}

int main() {
    int n;
    for (int t = 1; ~scanf("%d", &n); t++) {
        for (int i = 0; i < n; i++)
            scanf("%d", &in[i]);
        for (int i = 0; i < n; i++)
            scanf("%d", &post[i]);
        printf("testcase%d: ", t);
        printpre(0, n-1, 0, n-1);
        printf("\n");
    }
}
