#include <stdio.h>
#include <stdlib.h>

typedef struct cell {
    struct cell* p[4];
    int num;
} Cell;

const int rd[] = {2, 3, 0, 1};

Cell* dp;

int main() {
    int q;
    scanf("%d", &q);
    Cell* now = malloc(sizeof(Cell));
    now->num = 0;
    dp = now;

    while (q--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int dir, val;
            scanf("%d %d", &dir, &val);
            Cell* nc = malloc(sizeof(Cell));
            nc->num = val;
            now->p[dir] = nc;
            nc->p[rd[dir]] = now;
        } else if (op == 2) {
            int dir;
            scanf("%d", &dir);
            now = now->p[dir];
        } else if (op == 3) {
            int val;
            scanf("%d", &val);
            now->num = val;
        } else if (op == 4) {
            printf("%d\n", now->num);
        } else if (op == 5) {
            dp = now;
        } else if (op == 6) {
            now = dp;
        }
    }
}
