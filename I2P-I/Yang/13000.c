#include <stdio.h>


char s[25], p[25];
int cnt;

long long prem(int si, int pi) {
    if (p[pi] == '\0' && s[si] == '\0')
        cnt++;
    if (p[pi] == '#') {
        for (int i = 1; s[si + i-1] != '\0'; i++) {
            prem(si + i, pi + 1);
        }
    } else if (p[pi] == '$') {
        char c = s[si];
        for (int i = 1; s[si + i-1] != '\0' && s[si + i-1] == c; i++) {
            prem(si + i, pi + 1);
        }
    } else if (p[pi] == s[si]) {
        prem(si + 1, pi + 1);
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", s);
        scanf("%s", p);
        cnt = 0;
        prem(0, 0);
        printf("%lld\n", cnt);
    }
}
