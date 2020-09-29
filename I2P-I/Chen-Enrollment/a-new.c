#include <stdio.h>

int siz;
int nm, nn;

char a[15][15];

int place_m(int x, int y) {
    for (int i = 0; i < siz; i++) {
        if (a[x][i] != 0 || a[i][y] != 0)
            return 0;
    }
    for (int i = 1; i < siz * 2; i++) {
        if (x + i < siz && y + i < siz && a[x+i][y+i] != 0)
            return 0;
        if (x + i < siz && y - i >= 0 && a[x+i][y-i] != 0)
            return 0;
        if (x - i >= 0 && y + i < siz && a[x-i][y+i] != 0)
            return 0;
        if (x - i >= 0 && y - i >= 0 && a[x-i][y-i] != 0)
            return 0;
    }
    return 1;
}

int place_n(int x, int y) {
    for (int i = 0; i < siz; i++) {
        if (a[x][i] != 0 || a[i][y] != 0)
            return 0;
    }
    for (int i = 1; i < siz * 2; i++) {
        if (x + i < siz && y + i < siz && a[x+i][y+i] == 'M')
            return 0;
        if (x + i < siz && y - i >= 0 && a[x+i][y-i] == 'M')
            return 0;
        if (x - i >= 0 && y + i < siz && a[x-i][y+i] == 'M')
            return 0;
        if (x - i >= 0 && y - i >= 0 && a[x-i][y-i] == 'M')
            return 0;
    }
    return 1;
}


int prem(int x, int m, int n) {
    if (m == 0 && n == 0)
        return 1;
    if (x >= siz)
        return 0;
    
    int res = 0;
    for (int y = 0; y < siz; y++) {
        if (m > 0 && place_m(x, y)) {
            a[x][y] = 'M';
            res += prem(x+1, m-1, n);
            a[x][y] = 0;
        }
        if (n > 0 && place_n(x, y)) {
            a[x][y] = 'N';
            res += prem(x+1, m, n-1);
            a[x][y] = 0;
        }
    }
    return res;
}


int main() {
    scanf("%d %d", &nm, &nn);
    siz = nm + nn;
    printf("%d\n", prem(0, nm, nn));
}
