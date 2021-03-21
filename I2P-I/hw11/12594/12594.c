#include "function.h"
#include <stdlib.h>

Node* createList(int *a, int size) {
    Node *root;
    Node **now = &root;
    for (int i = 0; i < size; i++) {
        *now = malloc(sizeof(Node));
        (*now)->data = a[i];
        (*now)->next = NULL;
        now = &(*now)->next;
    }
    return root;
}

void push_front(Node** head, int val) {
    Node *root = malloc(sizeof(Node));
    root->data = val;
    root->next = *head;
    *head = root;
}

void deleteElementByIdx(Node** head, int idx) {
    Node **now = head;
    while (idx--) {
        now = &(*now)->next;
        if (*now == NULL)
            return;
    }

    Node *del = *now;
    *now = del->next;
    free(del);
}

Node* copyList(Node* head) {
    Node *root;
    Node **now = &root;
    Node *onow = head;

    while (onow != NULL) {
        *now = malloc(sizeof(Node));
        (*now)->data = onow->data;
        (*now)->next = NULL;
        now = &(*now)->next;
        onow = onow->next;
    }
    return root;
}

void SwapElementByIdx(Node** head, int idx1, int idx2) {
    if (idx1 > idx2) {
        int tmp = idx1;
        idx1 = idx2;
        idx2 = tmp;
    }

    Node *now = *head;
    for (int i = 0; i < idx1; i++) {
        now = now->next;
        if (now == NULL)
            return;
    }
    
    Node *n1 = now;

    for (int i = idx1; i < idx2; i++) {
        now = now->next;
        if (now == NULL)
            return;
    }

    Node *n2 = now;

    int tmp = n1->data;
    n1->data = n2->data;
    n2->data = tmp;
}

