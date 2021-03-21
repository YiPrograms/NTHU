#include <stdio.h>
#include <string.h>

char s[105], rs[105];

int main() {
    scanf("%s", s);
    int len = strlen(s);
    int ok = 1;
    for (int i = len - 1; i >= 0; i--) {
        if (s[i] == '0')
            rs[len-1 - i] = '0';
        else if (s[i] == '1')
            rs[len-1 - i] = '1';
        else if (s[i] == '6')
            rs[len-1 - i] = '9';
        else if (s[i] == '8')
            rs[len-1 - i] = '8';
        else if (s[i] == '9')
            rs[len-1 - i] = '6';
        else {
            ok = 0;
            break;
        }
    }
    if (ok) {
        int still_zero = 1;
        for (int i = 0; i < len; i++) {
            if (rs[i] == '0') {
                if (still_zero)
                    continue;
            } else {
                still_zero = 0;
            }
            printf("%c", rs[i]);
        }
        printf("\n");
    } else
        printf("No\n");
}
