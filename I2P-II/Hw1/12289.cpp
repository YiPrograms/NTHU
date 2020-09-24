//#include "function.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct Node {
    struct Node *next, *prev;
    char* color;
};

typedef struct Node Node;

void show(Node **head) {
	Node *now = (*head)->next;
	while(now != NULL) {
		printf("%s ", now->color);
        now = now->next;
	}
	puts("");
}

void insert(Node** head, char* color, int dest) {
	Node *now = (*head)->next; // May be NULL
    Node *prev = *head; // Insert between
    int i = 1;
	while(i < dest + 1 && now != NULL) {
        prev = now;
        now = now->next;
        i++;
    }

	Node* ins = (Node*)malloc(sizeof(Node)); // create an empty node
    ins->color = (char*)malloc(10 * sizeof(char));
    strcpy(ins->color, color);

    prev->next = ins;
    ins->prev = prev;
    ins->next = now;
    if (now != NULL) {
        now->prev = ins;
    }
}

void erase1(Node** head, int dest) {
	Node *now = (*head)->next; // May be NULL
    Node *prev = *head; // To delete
    Node *pprev = NULL;
    int i = 1;
	while(i < dest + 1 && now != NULL) {
        pprev = prev;
        prev = now;
        now = now->next;
        i++;
    }
    pprev->next = now;
    if (now != NULL) {
        now->prev = pprev;
    }
    free(prev->color);
    free(prev);
}

void erase2(Node** head, char* color) {
	Node *now = (*head)->next;
    Node *prev = *head;
	while(now != NULL) {
        if (strcmp(now->color, color) == 0) {
            prev->next = now->next;
            if (now->next !=  NULL) {
                now->next->prev = prev;
            }
            free(now->color);
            free(now);
            now = prev->next;
        } else {
            prev = now;
            now = now->next;
        }
    }
}

void reverse(Node** head, int start, int end) {
	Node *now = (*head)->next; // May be NULL
    Node *prev = *head; // Target
    Node *pprev = NULL;
    if (start > end) {
        int tmp = start;
        start = end;
        end = tmp;
    }
    
    int i = 1;
	while(i < start + 1 && now != NULL) {
        pprev = prev;
        prev = now;
        now = now->next;
        i++;
    }

    Node* st_prev = pprev;
    Node* st = prev;
    st->prev = st->next;

	while(i < end + 1 && now != NULL) {
        pprev = prev;
        prev = now;
        now = now->next;
        i++;

        Node* tmp = prev->next;
        prev->next = prev->prev;
        prev->prev = tmp;
    }

    prev->prev = st_prev;
    st_prev->next = prev;
    st->next = now;
    if (now != NULL) {
        now->prev = st;
    }
}


int n;
char buf[100];
int num1, num2;
Node *head;

int main()
{
	head = (Node*)malloc(sizeof(Node)); // create an empty node
	head->next = NULL;
    head->prev = NULL;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%s",buf);
		if(!strcmp(buf,"insert"))
		{
			scanf("%s%d",buf,&num1);
			insert(&head, buf, num1); // insert <color> <dest>
		}
		else if(!strcmp(buf,"erase1"))
		{
			scanf("%d",&num1);
			erase1(&head, num1); // erase1 <dest>
		}
		else if(!strcmp(buf,"erase2"))
		{
			scanf("%s",buf);
			erase2(&head, buf); // erase2 <color>
		}
		else if(!strcmp(buf,"reverse"))
		{
			scanf("%d%d",&num1,&num2);
			reverse(&head, num1, num2); // reverse <dest1> <dest2>
		}
		else if(!strcmp(buf,"show"))
		{
			show(&head);
		}
	}
	return 0;
}


























