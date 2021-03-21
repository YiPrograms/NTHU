#include <stdio.h>
#include <stdlib.h>


int ans[100005];

typedef struct NODE {
    int v;
    struct NODE *next;
} Node;

Node *e[100005];
Node *end[100005];

void dfs(int x) {
    Node *now = e[x];
    ans[x] = 1;
    while (now != NULL) {
        const int v = now->v;
        if (ans[v] == 0)
            dfs(v);
        ans[x] += ans[v];
        now = now->next;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int st;
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (i == 1)
            st = x;
        if (end[x] == NULL) {
            e[x] = end[x] = calloc(0, sizeof(Node));
        } else {
            end[x]->next = calloc(0, sizeof(Node));
            end[x] = end[x]->next;
        }
        end[x]->v = y;
    }
    dfs(st);
    for (int i = 1; i <= n; i++) {
        printf("%d", ans[i] - 1);
        if (i == n)
            printf("\n");
        else
            printf(" ");
    }
}
