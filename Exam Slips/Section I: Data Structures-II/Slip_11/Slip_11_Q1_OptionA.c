/* Q1) Write a program which uses binary search tree library and counts the total nodes and total
   leaf nodes in the tree.
   int count(T) - returns the total number of nodes from BST
   int countLeaf(T) - returns the total number of leaf nodes from BST */

#include <stdio.h>
#include "btree.h"

int main() {
    Node *root = NULL;
    int n, value, i;

    printf("Enter number of nodes to insert: ");
    scanf("%d", &n);
    printf("Enter %d values:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insert(root, value);
    }

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    printf("Total number of nodes: %d\n", count(root));
    printf("Total number of leaf nodes: %d\n", countLeaf(root));

    freeTree(root);
    return 0;
}
