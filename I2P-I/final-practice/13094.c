#include "function.h"
#include <stdlib.h>

Node* Partial_sort(Node* head, int x) {
    Node *vroot = malloc(sizeof(Node));
    vroot->next = head;
    Node **fnow = &vroot->next;

    Node **now = &head;
    while (*now != NULL) {
        if ((*now)->data < x) {
            *fnow = *now;
            *now = (*now)->next;
            fnow = &(*fnow)->next;
        } else {
            now = &(*now)->next;
        }
    }
    *fnow = head;
    Node *res = vroot->next;
    free(vroot);
    return res;
}

Node* Split_and_Swap(Node* root, int a, int b) {
    Node *now = root;
    for (int i = 0; i < a; i++)
        now = now->next;
    Node *pa = now;
    for (int i = a; i < b - 1; i++)
        now = now->next;
    Node *pbp = now;
    Node *pb = now->next;
    while (now->next != NULL)
        now = now->next;
    Node *tail = now;
    
    if (pa->next == pb) {
        tail->next = root;
        pa->next = NULL;
    } else {
        tail->next = pa->next;
        pbp->next = root;
        pa->next = NULL;
    }

    return pb;
}
