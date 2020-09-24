#include <stdio.h>

int siz;
int nm, nn;

char a[15][15];

int place(int x, int y, char type) {
    //printf("%d, %d: Check %c\n", x, y, type);
    for (int i = 0; i < siz; i++) {
        if (a[x][i] != 0 || a[i][y] != 0)
            return 0;
    }
    for (int i = x, j = y; i < siz && j < siz; i++, j++)
        if (a[i][j] == 'M' || type == 'M' && a[i][j] == 'N')
            return 0;
    for (int i = x, j = y; i >= 0 && j < siz; i--, j++)
        if (a[i][j] == 'M' || type == 'M' && a[i][j] == 'N')
            return 0;
    for (int i = x, j = y; i < siz && j >= 0; i++, j--)
        if (a[i][j] == 'M' || type == 'M' && a[i][j] == 'N')
            return 0;
    for (int i = x, j = y; i >= 0 && j >= 0; i--, j--)
        if (a[i][j] == 'M' || type == 'M' && a[i][j] == 'N')
            return 0;
    return 1;
}

int prem(int x, int y, int m, int n) {
    if (m == 0 && n == 0) {
        return 1;
    }
    if (x >= siz)
        return 0;
    int res = 0;
    int i = x, j = y+1;
    if (j >= siz) {
        j = 0;
        i++;
    }
    
    if (m > 0 && place(x, y, 'M')) {
        a[x][y] = 'M';
        res += prem(i, j, m-1, n);
        a[x][y] = 0;
    }
    if (n > 0 && place(x, y, 'N')) {
        a[x][y] = 'N';
        res += prem(i, j, m, n-1);
        a[x][y] = 0;
    }
    res += prem(i, j, m, n); 
    return res;
}


int main() {
    scanf("%d %d", &nm, &nn);
    siz = nm + nn;
    printf("%d\n", prem(0, 0, nm, nn));
}
