#include <stdio.h>

int main() {
    double d;
    scanf("%lf", &d);
    int integ = d;
    double dec = d - integ;
    int new_int = 0;
    int i = 0;
    while (integ > 0) {
        new_int *= 10;
        new_int += integ % 10;
        integ /= 10;
        i++;
    }
    i = 6 - i;
    for (int k = 0; k < i; k++) {
        dec *= 10;
    }
    int dec_int = dec, new_dec = 0;
    while (dec_int > 0) {
        new_dec *= 10;
        new_dec += dec_int % 10;
        dec_int /= 10;
    }
    dec = new_dec;
    do {
        dec /= 10;
    } while (dec > 1);
    printf("%.3lf", d + new_int + dec);
}
