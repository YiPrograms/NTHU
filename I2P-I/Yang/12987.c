#include <stdio.h>

char s[25], p[25];
char ans[25][25];
int ok = 0;

void prem(int si, int pi, int ai) {
    if (p[pi] == '\0' && s[si] == '\0') {
        for (int i = 0; i < ai; i++) {
            printf("%s", ans[i]);
            if (i == ai - 1)
                printf("\n");
            else
                printf(" ");
        }
        ok = 1;
    } else if (p[pi] == '#') {
        for (int k = 1; s[si + k-1] != '\0'; k++) {
            ans[ai][k-1] = s[si + k-1];
            ans[ai][k] = '\0';
            prem(si + k, pi + 1, ai + 1);
        }
        ans[ai][0] = '\0';
    } else if (p[pi] == s[si]) {
        prem(si + 1, pi + 1, ai);
    }
}


int main() {
    scanf("%s", s);
    scanf("%s", p);
    prem(0, 0, 0);
    if (!ok) {
        printf("What the hack!?\n");
    }
}
