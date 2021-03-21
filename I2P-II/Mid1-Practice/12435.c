#include <stdio.h>
#include <stdlib.h>

const int M = 1000000007;

typedef struct NODE {
    int id;
    int val;
    struct NODE *l, *r;
} Node;

void insert(Node** root, int i, int v) {
    if (*root == NULL) {
        *root = malloc(sizeof(Node));
        (*root)->id = i;
        (*root)->val = v;
        (*root)->l = (*root)->r = NULL;
        return;
    }
    if (v > (*root)->val)
        return insert(&((*root)->r), i, v);
    if (v < (*root)->val)
        return insert(&((*root)->l), i, v);
    return;
}

int find(Node* now, int v) {
    if (now == NULL)
        return -1;
    if (now->val == v)
        return now->id;
    if (v > now->val)
        return find(now->r, v);
    return find(now->l, v);
}

void freeNode(Node* root) {
    if (root == NULL)
        return;
    freeNode(root->l);
    freeNode(root->r);
    free(root);
}

int main() {
    int n, q;
    while (~scanf("%d %d", &n, &q)) {
        Node* root = NULL;
        for (int i = 1; i <= n; i++) {
            int ai;
            scanf("%d(/`A`)/ ~I__I", &ai);

            int res = 1, base = 2;
            if (ai & 1)
                res = 0;
            else {
                ai >>= 1;
                while (ai) {
                    if (ai & 1)
                        res = (res * 1LL * base) % M;
                    base = (base * 1LL * base) % M;
                    ai >>= 1;
                }
            }
            insert(&root, i, res);
        }
        while (q--) {
            int k;
            scanf("%d", &k);
            int res = find(root, k);
            if (res == -1)
                printf("Go Down Chicken 404\n");
            else
                printf("%d\n", res);
        }
        freeNode(root);
    }
}
