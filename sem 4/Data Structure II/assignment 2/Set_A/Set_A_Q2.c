/*
 * Assignment 2 - Set A - Question 2
 * 
 * Write a C program to find the minimum and maximum values in a Binary Search Tree.
 */

#include <stdio.h>
#include "../../common/btree.h"

int findMin(Node *root, int *found) {
    *found = 0;
    if (root == NULL) {
        printf("Tree is empty!\n");
        return 0;
    }
    *found = 1;
    while (root->left != NULL) {
        root = root->left;
    }
    return root->data;
}

int findMax(Node *root, int *found) {
    *found = 0;
    if (root == NULL) {
        printf("Tree is empty!\n");
        return 0;
    }
    *found = 1;
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

    int found;
    int minVal = findMin(root, &found);
    if (found) printf("\nMinimum value in BST: %d\n", minVal);
    
    int maxVal = findMax(root, &found);
    if (found) printf("Maximum value in BST: %d\n", maxVal);

    return 0;
}
