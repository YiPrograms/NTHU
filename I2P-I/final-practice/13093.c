#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
    int val;
    struct NODE *p, *n;
} Node;

int main() {
    int n;
    scanf("%d", &n);
    Node *root = calloc(0, sizeof(Node));
    scanf("%d", &root->val);
    Node *now = root;
    Node *mid = root;
    const int midid = (n & 1)? n/2: n/2 - 1;  
    for (int i = 1; i < n; i++) {
        now->n = calloc(0, sizeof(Node));
        now->n->p = now;
        now = now->n;
        scanf("%d", &now->val);
        if (i == midid)
            mid = now;
    }
    now = root;
    int q;
    scanf("%d", &q);
    while (q--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int d;
            scanf("%d", &d);
            if (d == 1)
                now = now->n;
            else if (d == -1)
                now = now->p;
        } else if (op == 2) {
            printf("%d\n", now->val);
        } else {
            if (now == mid)
                now = now->n;

            Node *tmp = mid;
            if (n & 1)
                mid = mid->p;
            else
                mid = mid->n;
            if (tmp->p)
                tmp->p->n = tmp->n;
            if (tmp->n)
                tmp->n->p = tmp->p;
            free(tmp);
            n--;
        }
        
    }
}
