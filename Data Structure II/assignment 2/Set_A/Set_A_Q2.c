/*
 * Assignment 2 - Set A - Question 2
 * 
 * Write a C program to find the minimum and maximum values in a Binary Search Tree.
 */

#include <stdio.h>
#include "../btree.h"

int findMin(Node *root) {
    if (root == NULL) {
        printf("Tree is empty!\n");
        return -1;
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root->data;
}

int findMax(Node *root) {
    if (root == NULL) {
        printf("Tree is empty!\n");
        return -1;
    }
    while (root->right != NULL) {
        root = root->right;
    }
    return root->data;
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

    printf("\nMinimum value in BST: %d\n", findMin(root));
    printf("Maximum value in BST: %d\n", findMax(root));

    return 0;
}
