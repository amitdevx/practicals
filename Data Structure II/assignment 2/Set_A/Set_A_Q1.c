/*
 * Assignment 2 - Set A - Question 1
 * 
 * Write a C program which uses Binary search tree library and display the following:
 * i. Node value at each level
 * ii. Count of node at each level
 * iii. Total levels in the tree.
 */

#include <stdio.h>
#include "../btree.h"

int height(Node *root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void printLevel(Node *root, int level, int *count) {
    if (root == NULL) {
        return;
    }
    if (level == 1) {
        printf("%d ", root->data);
        (*count)++;
    } else if (level > 1) {
        printLevel(root->left, level - 1, count);
        printLevel(root->right, level - 1, count);
    }
}

void displayLevelInfo(Node *root) {
    int h = height(root);
    printf("\nTotal levels in the tree: %d\n", h);
    
    for (int i = 1; i <= h; i++) {
        int count = 0;
        printf("\nLevel %d: ", i);
        printLevel(root, i, &count);
        printf("\nCount of nodes at level %d: %d\n", i, count);
    }
}

int main() {
    Node *root = NULL;
    int n, value;

    printf("Enter number of nodes to insert: ");
    scanf("%d", &n);

    printf("Enter %d values:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insert(root, value);
    }

    printf("\nInorder Traversal: ");
    inorder(root);
    printf("\n");

    displayLevelInfo(root);

    return 0;
}
