/*
 * Assignment 1 - Set B - Question 1
 * 
 * Write a C program which uses Binary search tree library and implements following function
 * with recursion:
 * int copy(T) – create another BST which is exact copy of BST which is passed as parameter.
 * int compare(T1, T2) – compares two binary search trees and returns 1 if they are equal and 0
 * otherwise.
 */

#include <stdio.h>
#include "../../common/btree.h"

Node* copy(Node *root) {
    if (root == NULL) {
        return NULL;
    }
    Node *newNode = createNode(root->data);
    newNode->left = copy(root->left);
    newNode->right = copy(root->right);
    return newNode;
}

int compare(Node *tree1, Node *tree2) {
    if (tree1 == NULL && tree2 == NULL) {
        return 1;
    }
    if (tree1 == NULL || tree2 == NULL) {
        return 0;
    }
    if (tree1->data != tree2->data) {
        return 0;
    }
    return compare(tree1->left, tree2->left) && compare(tree1->right, tree2->right);
}

int main() {
    Node *tree1 = NULL;
    Node *tree2 = NULL;
    Node *copiedTree = NULL;
    int n, value, choice;

    printf("Enter number of nodes for Tree 1: ");
    scanf("%d", &n);

    printf("Enter %d values for Tree 1:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        tree1 = insert(tree1, value);
    }

    printf("\nTree 1 Inorder: ");
    inorder(tree1);
    printf("\n");

    printf("\n=== Operations ===\n");
    printf("1. Copy Tree 1\n");
    printf("2. Create Tree 2 and Compare with Tree 1\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        copiedTree = copy(tree1);
        printf("\nCopied Tree Inorder: ");
        inorder(copiedTree);
        printf("\n");

        if (compare(tree1, copiedTree)) {
            printf("Original and Copied trees are equal.\n");
        } else {
            printf("Original and Copied trees are not equal.\n");
        }
    } else if (choice == 2) {
        printf("\nEnter number of nodes for Tree 2: ");
        scanf("%d", &n);

        printf("Enter %d values for Tree 2:\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &value);
            tree2 = insert(tree2, value);
        }

        printf("\nTree 2 Inorder: ");
        inorder(tree2);
        printf("\n");

        if (compare(tree1, tree2)) {
            printf("Tree 1 and Tree 2 are equal.\n");
        } else {
            printf("Tree 1 and Tree 2 are not equal.\n");
        }
    }

    return 0;
}
