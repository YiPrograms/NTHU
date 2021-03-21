#include <stdio.h>

int appeared[1030][15];

int main() {
    int n;
    scanf("%d", &n);
    int kinds = 0;
    while (n--) {
        char s[15];
        scanf("%s", s);
        int res = 0, x = -1;
        for (int i = 0; i < 10; i++) {
            if (s[i] == 'x')
                x = i;
            else if (s[i] == '1')
                res |= 1;
            if (i != 9)
                res <<= 1;
        }
        if (!appeared[res][x]) {
            appeared[res][x] = 1;
            kinds++;
        }
    }
    printf("%d\n", kinds);
}
