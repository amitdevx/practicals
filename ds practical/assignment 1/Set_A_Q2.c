// Assignment 1: Set A - Question (b)
// Program to count total nodes and total leaf nodes in BST
// count(T) - returns the total number of nodes from BST
// countLeaf(T) - returns the total number of leaf nodes from BST

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node* createNode(int value) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct node* insert(struct node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    return root;
}

int count(struct node* root) {
    if (root == NULL)
        return 0;
    return 1 + count(root->left) + count(root->right);
}

int countLeaf(struct node* root) {
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    return countLeaf(root->left) + countLeaf(root->right);
}

int main() {
    struct node* root = NULL;
    int n, value, i;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter value: ");
        scanf("%d", &value);
        root = insert(root, value);
    }

    printf("\nTotal nodes: %d\n", count(root));
    printf("Total leaf nodes: %d\n", countLeaf(root));

    return 0;
}
