#include <stdio.h>

int used[10];
int seq[10];
int n;

void perm(int now) {
    if (now == n) {
        for (int i = 0; i < n; i++) {
            printf("%d ", seq[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            used[i] = 1;
            seq[now] = i;
            perm(now + 1);
            used[i] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    perm(0);
}
