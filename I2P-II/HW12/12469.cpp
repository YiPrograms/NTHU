#include "function.h"
#include <algorithm>

using namespace std; 


int getDigit(long long *m, int i) {
    char* p = reinterpret_cast<char*>(&m[i / 8]) + i % 8;
    return static_cast<int>(*p);
}

void setDigit(long long *m, int i, int d) {
    char* p = reinterpret_cast<char*>(&m[i / 8]) + i % 8;
    *p = static_cast<char>(d);
}

istream& operator>>(istream& in, BigInt& bi) {
    string s;
    in >> s;
    bi.sign = 1;
    bi.l = 0;
    for (int i = s.length() - 1; i >= 0; i--) {
        if (s[i] == '-') {
            bi.sign = 0;
        } else {
            setDigit(bi.m, bi.l++, s[i] - '0');
        }
    }
    return in;
}

ostream& operator<<(ostream& out, BigInt bi) {
    if (bi.sign == 0)
        out << '-';
    for (int i = bi.l - 1; i >= 0; i--) {
        out << getDigit(bi.m, i);
    }
    return out;
}

bool BigIntDig_gt(BigInt &a, BigInt &b) {
    if (a.l != b.l)
        return a.l > b.l;
    for (int i = a.l-1; i >= 0; i--)
        if (getDigit(a.m, i) != getDigit(b.m, i))
            return getDigit(a.m, i) > getDigit(b.m, i);
    return false;
}

BigInt BigInt::operator +( const BigInt &y ) {
    BigInt res;
    res.l = 0;
    BigInt *a = this, *b = (BigInt*) &y;
    if (sign ^ y.sign) { // Minus
        if (a->sign == 0)
            swap(a, b);
        if (BigIntDig_gt(*b, *a)) {
            swap(a, b);
            res.sign = 0;
        }
        for (int i = 0; i < max(a->l, b->l); i++) {
            int ad = ((i < a->l)? getDigit(a->m, i): 0), bd = ((i < b->l)? getDigit(b->m, i): 0);
            setDigit(res.m, res.l++, ad - bd);
        }
        for (int i = 0; i < res.l - 1; i++) {
            int d = getDigit(res.m, i);
            if (d < 0) {
                setDigit(res.m, i + 1, getDigit(res.m, i + 1) - 1);
                setDigit(res.m, i, d + 10);
            }
        }
        for (int i = res.l - 1; i >= 1; i--) {
            if (getDigit(res.m, i) != 0)
                break;
            res.l--;
        }
    } else {
        if (sign == 0)
            res.sign = 0;
        for (int i = 0; i < max(a->l, b->l); i++) {
            int ad = i < a->l? getDigit(a->m, i): 0, bd = i < b->l? getDigit(b->m, i): 0;
            setDigit(res.m, res.l++, ad + bd);
        }
        for (int i = 0; i < res.l; i++) {
            int d = getDigit(res.m, i);
            if (d >= 10) {
                if (i == res.l - 1) {
                    res.l++;
                    setDigit(res.m, i + 1, 1);
                } else
                    setDigit(res.m, i + 1, getDigit(res.m, i + 1) + 1);
                setDigit(res.m, i, d - 10);
            }
        }
    }
    if (res.l == 1 && getDigit(res.m, 0) == 0)
        res.sign = 1;
    return res;
}

BigInt BigInt::operator -( const BigInt &y ) {
    BigInt tmp = y;
    tmp.sign = !tmp.sign;
    return (*this) + tmp;
}

