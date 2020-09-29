#include <stdio.h>

int main() {
    double a, b;
    char c;
    scanf("%lf%c%lf", &a, &c, &b);
    double res;
    switch(c) {
        case '+':
            res = a + b;
            break;
        case '-':
            res = a - b;
            break;
        case '*':
            res = a * b;
            break;
        case '/':
            if (b == 0) {
                res = 2e9;
            } else {
                res = a / b;
            }
    }
    if (res == 2e9) {
        printf("Error\n");
    } else {
        printf("%.3lf\n", res);
    }
}
