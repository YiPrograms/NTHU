#include "function.h"
#include <stdlib.h>
#include <stdio.h>

#define right ptr_to_right_node
#define left ptr_to_left_node
#define num number

Node* buildTree(int* inorder, int* preorder, int inorder_start, int inorder_end) {
    if (inorder_start > inorder_end)
        return NULL;
    Node* root = malloc(sizeof(Node));
    root->num = preorder[0];
    int sep = inorder_start;
    while (inorder[sep] != root->num)
        sep++;
    root->left = buildTree(inorder, preorder + 1, inorder_start, sep - 1);
    root->right = buildTree(inorder, preorder + sep - inorder_start + 1, sep + 1, inorder_end);
    return root;
}

void showPostorder(Node* root) {
    if (!root)
        return;
    showPostorder(root->left);
    showPostorder(root->right);
    printf("%d ", root->num);
}

void freeTree(Node *root) {
    if (!root)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

