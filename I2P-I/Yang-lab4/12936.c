#include <stdio.h>

int nn[50], nm[50];
int an[50][50], am[50][50];
char a[50][50];
int n, m;

int getValid() {
    for (int i = 0; i < n; i++) {
        int ni = nn[i];
        int ki = 0;
        int k = 0;
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 'x')
                continue;
            k++;
            if (j+1 >= m || a[i][j+1] == 'x') {
                if (ki >= ni || k != an[i][ki])
                    return 0;
                k = 0;
                ki++;
            }
        }
        if (ki != ni)
            return 0;
    }
    for (int j = 0; j < m; j++) {
        int ni = nm[j];
        int ki = 0;
        int k = 0;
        for (int i = 0; i < n; i++) {
            if (a[i][j] == 'x')
                continue;
            k++;
            if (i+1 >= n || a[i+1][j] == 'x') {
                if (k == 0)
                    continue;
                if (ki >= ni || k != am[j][ki])
                    return 0;
                k = 0;
                ki++;
            }
        }
        if (ki != ni)
            return 0;
    }
    return 1;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++) {
            scanf("%d", nn + i);
            for (int j = 0; j < nn[i]; j++)
                scanf("%d", an[i] + j);
        }
        for (int i = 0; i < m; i++) {
            scanf("%d", nm + i);
            for (int j = 0; j < nm[i]; j++)
                scanf("%d", am[i] + j);
        }
        getchar();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                scanf("%c", &a[i][j]);
            getchar();
        }
        if (getValid()) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
}
