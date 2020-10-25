#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sum[1005];

int main() {
    char* S = malloc(1005 * sizeof(char));
    char* p = malloc(1005 * sizeof(char));
    while (~scanf("%s %s", S, p)) {
        memset(sum, 0, sizeof(sum));
        int Slen = strlen(S), plen = strlen(p);
        for (int i = plen; i <= Slen; i++) {
            if (strncmp(S + i - plen, p, plen) == 0)
                sum[i] = sum[i-1] + 1;
            else
                sum[i] = sum[i-1];
        }
        int q;
        scanf("%d", &q);
        int max_ans = -1;
        while (q--) {
            int a, b;
            scanf("%d %d", &a, &b);
            if (b - a + 1 < plen)
                continue;
            int res = sum[b] - sum[a - 1 + plen - 1];
            if (res > max_ans)
                max_ans = res;
        }
        printf("%d\n", max_ans);
    }
}
