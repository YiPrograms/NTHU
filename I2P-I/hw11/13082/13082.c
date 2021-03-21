#include "function.h"
#include <stdlib.h>

Node* Merge_lists(Node* a, Node* b) {
    Node *root;
    Node **now = &root;

    Node *na = a, *nb = b;
    
    int last = -1;
    while (na != NULL && nb != NULL) {
        if (na->data < nb->data) {
            if (na->data == last) {
                na = na->next;
                continue;
            }
            *now = malloc(sizeof(Node));
            last = (*now)->data = na->data;
            (*now)->next = NULL;
            now = &(*now)->next;
            na = na->next;
        } else {
            if (nb->data == last) {
                nb = nb->next;
                continue;
            }
            *now = malloc(sizeof(Node));
            last = (*now)->data = nb->data;
            (*now)->next = NULL;
            now = &(*now)->next;
            nb = nb->next;
        }
    }

    while (na != NULL) {
        if (na->data == last) {
            na = na->next;
            continue;
        }
        *now = malloc(sizeof(Node));
        last = (*now)->data = na->data;
        (*now)->next = NULL;
        now = &(*now)->next;
        na = na->next;
    }

    while (nb != NULL) {
        if (nb->data == last) {
            nb = nb->next;
            continue;
        }
        *now = malloc(sizeof(Node));
        last = (*now)->data = nb->data;
        (*now)->next = NULL;
        now = &(*now)->next;
        nb = nb->next;
    }
    return root;
}
