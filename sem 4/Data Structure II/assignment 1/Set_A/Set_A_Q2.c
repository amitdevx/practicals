/*
 * Assignment 1 - Set A - Question 2
 * 
 * Write a program which uses binary search tree library and counts the total nodes and total
 * leaf nodes in the tree.
 * int count(T) – returns the total number of nodes from BST
 * int countLeaf(T) – returns the total number of leaf nodes from BST
 */

#include <stdio.h>
#include "../../common/btree.h"

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

    printf("\nTotal number of nodes: %d\n", count(root));
    printf("Total number of leaf nodes: %d\n", countLeaf(root));

    return 0;
}
