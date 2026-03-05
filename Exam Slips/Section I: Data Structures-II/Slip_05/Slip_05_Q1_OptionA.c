/* Q1) Write a C program which uses Binary search tree library and display the following
   i. Node value at each level
   ii. Count of node at each level
   iii. Total levels in the tree. */

#include <stdio.h>
#include "btree.h"

int height(Node *root) {
    int lh, rh;
    if (root == NULL) return 0;
    lh = height(root->left);
    rh = height(root->right);
    return (lh > rh ? lh : rh) + 1;
}

void printLevel(Node *root, int level, int *count) {
    if (root == NULL) return;
    if (level == 1) {
        printf("%d ", root->data);
        (*count)++;
    } else if (level > 1) {
        printLevel(root->left, level - 1, count);
        printLevel(root->right, level - 1, count);
    }
}

int main() {
    Node *root = NULL;
    int n, value, i, h;

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

    h = height(root);
    printf("\nTotal levels in the tree: %d\n", h);

    for (i = 1; i <= h; i++) {
        int cnt = 0;
        printf("\nLevel %d: ", i);
        printLevel(root, i, &cnt);
        printf("\nCount of nodes at level %d: %d\n", i, cnt);
    }

    freeTree(root);
    return 0;
}
