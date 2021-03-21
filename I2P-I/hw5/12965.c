#include <stdio.h>

int used[25];
int num[25];
int seq[25];
int n, m;

void perm(int now, int k) {
    if (now == m) {
        for (int i = 0; i < m; i++) {
            printf("%d", seq[i]);
            if (i != m-1)
                printf(" ");
        }
        printf("\n");
        return;
    }

    for (int i = k; i < n; i++) {
        if (!used[i]) {
            used[i] = 1;
            seq[now] = num[i];
            perm(now + 1, i + 1);
            used[i] = 0;
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &num[i]);
    perm(0, 0);
}
