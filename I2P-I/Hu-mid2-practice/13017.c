#include <stdio.h>
#include <string.h>

char s[500005];

int main() {
    fgets(s, sizeof(s), stdin);
    int slen = strlen(s) - 1;
    int now = -1;
    int lastcorrect = -1;
    char p[10];
    while (fgets(p, sizeof(p), stdin) != NULL) {
        if (p[0] == '\\') {
            if (now > -1) {
                if (now == lastcorrect)
                    lastcorrect--;
                now--;
            }
        } else {
            now++;
            if (now - 1 == lastcorrect) {
                if (now < slen && p[0] == s[now])
                    lastcorrect++;
            }
        }
        if (now == lastcorrect)
            printf("1\n");
        else
            printf("0\n");
    }
    if (now == slen - 1 && now == lastcorrect)
        printf("Correct\n");
    else
        printf("Incorrect\n");
}
