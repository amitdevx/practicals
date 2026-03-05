/* Q1) Write a C program to find the height of the tree and check whether given tree is balanced or not. */

#include <stdio.h>
#include "btree.h"

int height(Node *root) {
    int lh, rh;
    if (root == NULL) return 0;
    lh = height(root->left);
    rh = height(root->right);
    return (lh > rh ? lh : rh) + 1;
}

int isBalanced(Node *root) {
    int lh, rh, diff;
    if (root == NULL) return 1;
    lh = height(root->left);
    rh = height(root->right);
    diff = lh - rh;
    if (diff < 0) diff = -diff;
    if (diff <= 1 && isBalanced(root->left) && isBalanced(root->right))
        return 1;
    return 0;
}

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

    printf("Height of the tree: %d\n", height(root));

    if (isBalanced(root))
        printf("The tree is balanced.\n");
    else
        printf("The tree is not balanced.\n");

    freeTree(root);
    return 0;
}
