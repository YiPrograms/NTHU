#include <stdio.h>
#include <stdlib.h>

int x, y, z;
char* s;
long unsigned int slen;
int cur = 0;

char type[] = {' ', '+', '-', '*', '/'};

int getItem() {
    char itm[5];
    int len;
    for (len = 0; s[cur] != ' ' && s[cur] != '\n'; cur++, len++)
        itm[len] = s[cur];
    cur++;

    if (itm[0] == 'x')
        return -11;
    if (itm[0] == 'y')
        return -22;
    if (itm[0] == 'z')
        return -33;
    if (itm[0] == '+')
        return -1;
    if (itm[0] == '-')
        return -2;
    if (itm[0] == '*')
        return -3;
    if (itm[0] == '/')
        return -4;
    int res = 0;
    for (int i = 0; i < len; i++) {
        res *= 10;
        res += itm[i] - '0';
    }
    return res;
}

int getAns() {
    int now = getItem();
    //printf("Item %d", now);
    //getchar();
    if (now >= 0) {
        printf("%d", now);
        return now;
    }
    
    if (now >= -4) {
        int left = getAns();
        printf("%c", type[-now]);
        int right = getAns();
        if (now == -1)
            return left + right;
        if (now == -2)
            return left - right;
        if (now == -3)
            return left * right;
        if (now == -4)
            return left / right;
    }

    if (now == -11) {
        printf("x");
        return x;
    }
    if (now == -22) {
        printf("y");
        return y;
    }
    if (now == -33) {
        printf("z");
        return z;
    }

    return 0;
}

int main() {
    getline(&s, &slen, stdin);
    scanf("%d %d %d", &x, &y, &z);
    int ans = getAns();
    printf("\n");
    printf("%d\n", ans);
}
