#include "function.h"
#include <stdlib.h>
#include <stdio.h>

#define lc left_child
#define rc right_child

void build_tree(Node **now, int *arr, int l, int r) {
    if (l > r)
        return;
    int m = (l + r) / 2;
    *now = malloc(sizeof(Node));
    (*now)->level = arr[m];
    (*now)->lc = NULL;
    (*now)->rc = NULL;
    build_tree(&((*now)->lc), arr, l, m - 1);
    build_tree(&((*now)->rc), arr, m + 1, r);
}


int query_heatstroke(Node *now, int x) {
    if (now == NULL)
        return 0;
    if (x < now->level)
        return query_heatstroke(now->lc, x);
    if (x > now->level)
        return query_heatstroke(now->rc, x);
    return 1;
}

void print_tree(Node* now) {
    if (now == NULL)
        return;
    print_tree(now->lc);
    printf("%d ", now->level);
    print_tree(now->rc);
}

void eat_rat(Node **root, int x) {
    if (x > (*root)->level)
        return eat_rat(&((*root)->rc), x);
    if (x < (*root)->level)
        return eat_rat(&((*root)->lc), x);
    
    if ((*root)->lc == NULL && (*root)->rc == NULL) {
        free(*root);
        *root = NULL;
    } else if ((*root)->lc != NULL && (*root)->rc != NULL) {
        Node** now = &((*root)->rc);
        while ((*now)->lc != NULL)
            now = &((*now)->lc);
        (*root)->level = (*now)->level;
        eat_rat(now, (*now)->level);
    } else {
        Node* now = (*root)->rc;
        if (now == NULL)
            now = (*root)->lc;
        free(*root);
        *root = now;
    }
}
