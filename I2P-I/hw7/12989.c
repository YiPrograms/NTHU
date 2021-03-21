#include <stdio.h>

char s[105];

int pair[105];
int stack[105];
int top = 0;

long long calc(int a, int b) {
    if (b - a == 1) // ()
        return 1;
    if (pair[a] == b) // (A)
        return calc(a+1, b-1) * 2;
    // AB
    return calc(a, pair[a]) + calc(pair[a] + 1, b);
}

int main() {
    int n;
    scanf("%d", &n);
    scanf("%s", s);
    for (int i = 0; i < n; i++) {
        if (s[i] == '(')
            stack[top++] = i;
        else if (s[i] == ')') {
            int t = stack[--top];
            pair[i] = t;
            pair[t] = i;
        }
    }
    printf("%lld\n", calc(0, n-1));
}
