//typedef struct {
//	long long numerator; 
//	long long denominator; 
//} Fraction;

#include <stdlib.h>
#include "function.h"

Fraction CreateFrac(long long n, long long d) {
    Fraction res;
    res.numerator = n;
    res.denominator = d;
    return res;
}

long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a%b);
}

void Reduction(Fraction* f) {
    long long g = gcd(f->numerator, f->denominator);
    f->numerator /= g;
    f->denominator /= g;
}

Fraction Add(Fraction a, Fraction b) {
    Fraction res;
    res.denominator = a.denominator * b.denominator;
    res.numerator = a.numerator * b.denominator + b.numerator * a.denominator;
    Reduction(&res);
    return res;
}

Fraction Sub(Fraction a, Fraction b) {
    Fraction res;
    res.denominator = a.denominator * b.denominator;
    res.numerator = a.numerator * b.denominator - b.numerator * a.denominator;
    Reduction(&res);
    return res;
}

Fraction Mul(Fraction a, Fraction b) {
    Fraction res;
    res.denominator = a.denominator * b.denominator;
    res.numerator = a.numerator * b.numerator;
    Reduction(&res);
    return res;
}

Fraction Div(Fraction a, Fraction b) {
    Fraction res;
    res.denominator = a.denominator * b.numerator;
    res.numerator = a.numerator * b.denominator;
    Reduction(&res);
    return res;
}

int Compare(Fraction a, Fraction b) {
    if (a.numerator * b.denominator > b.numerator * a.denominator)
        return 1;
    return 0;
}
