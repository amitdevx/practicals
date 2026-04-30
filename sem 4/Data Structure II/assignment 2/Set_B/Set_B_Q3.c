/*
 * Assignment 2 - Set B - Question 3
 * 
 * Write a C program to find the height of the tree and check whether given tree is balanced or not.
 */

#include <stdio.h>
#include "../../common/btree.h"

int height(Node *root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int isBalanced(Node *root) {
    if (root == NULL) {
        return 1;
    }
    
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    int diff = leftHeight - rightHeight;
    if (diff < 0) diff = -diff;
    
    if (diff <= 1 && isBalanced(root->left) && isBalanced(root->right)) {
        return 1;
    }
    
    return 0;
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

    int h = height(root);
    printf("\nHeight of the tree: %d\n", h);

    if (isBalanced(root)) {
        printf("The tree is balanced.\n");
    } else {
        printf("The tree is not balanced.\n");
    }

    return 0;
}
