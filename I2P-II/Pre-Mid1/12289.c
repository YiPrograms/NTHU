#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

void insert(Node** head, char* color, int dest) {
    int i = 0;
    while (*head != NULL && i <= dest) {
        head = &((*head)->next);
        i++;
    }
    Node* tmp = *head;
    *head = malloc(sizeof(Node));
    strcpy((*head)->color, color);
    (*head)->next = tmp;
}

void erase1(Node** head, int dest) {
    int i = 0;
    for (i = 0; (*head)->next != NULL && i < dest; i++) {
        head = &((*head)->next);
    }
    if (i != 0) {
        Node* tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
}

void erase2(Node** head, char* color) {
    while (*head != NULL) {
        if (strcmp((*head)->color, color) == 0) {
            Node* tmp = *head;
            *head = (*head)->next;
            free(tmp);
        } else {
            head = &((*head)->next);
        }
    }
}

void reverse(Node** head, int dest1, int dest2) {
    Node* now = (*head)->next;
    Node* prev = *head;
    Node* pprev = NULL;
    int i = 1;
    if (dest1 > dest2) {
        int tmp = dest1;
        dest1 = dest2;
        dest2 = tmp;
    }
    while (i < dest1 + 1 && now != NULL) {
        pprev = prev;
        prev = now;
        now = now->next;
        i++;
    }

    Node* pre_dest1 = pprev;
    Node* dest1_p = prev;
    while (i < dest2 + 1 && now != NULL) {
        pprev = prev;
        prev = now;
        now = now->next;
        i++;

        prev->next = pprev;
    }
    if (pre_dest1 != NULL)
        pre_dest1->next = prev;
    dest1_p->next = now;
}

