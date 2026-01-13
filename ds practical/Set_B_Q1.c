// Assignment 1: Set B - Question (a)
// Program to implement BST copy and compare functions
// copy(T) - create another BST which is exact copy of BST
// compare(T1, T2) - compares two binary search trees and returns 1 if equal, 0 otherwise

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

void inorder(struct node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

struct node* copy(struct node* root) {
    if (root == NULL)
        return NULL;
    
    struct node* newRoot = createNode(root->data);
    newRoot->left = copy(root->left);
    newRoot->right = copy(root->right);
    return newRoot;
}

int compare(struct node* root1, struct node* root2) {
    if (root1 == NULL && root2 == NULL)
        return 1;
    
    if (root1 == NULL || root2 == NULL)
        return 0;
    
    if (root1->data != root2->data)
        return 0;
    
    return compare(root1->left, root2->left) && 
           compare(root1->right, root2->right);
}

int main() {
    struct node* root1 = NULL;
    struct node* root2 = NULL;
    int n, value, i;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter value: ");
        scanf("%d", &value);
        root1 = insert(root1, value);
    }

    root2 = copy(root1);

    printf("\nInorder of Original BST: ");
    inorder(root1);
    printf("\nInorder of Copied BST: ");
    inorder(root2);

    if (compare(root1, root2))
        printf("\n\nBoth BSTs are equal\n");
    else
        printf("\n\nBSTs are not equal\n");

    return 0;
}
