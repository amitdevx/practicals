/* Q1) Write a C program which uses Binary search tree library and implements following function
   with recursion:
   int copy(T) - create another BST which is exact copy of BST which is passed as parameter.
   int compare(T1, T2) - compares two binary search trees and returns 1 if they are equal and 0 otherwise. */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node *root, int data) {
    if (root == NULL) return createNode(data);
    if (data < root->data) root->left = insert(root->left, data);
    else if (data > root->data) root->right = insert(root->right, data);
    return root;
}

Node* search(Node *root, int key) {
    if (root == NULL || root->data == key) return root;
    if (key < root->data) return search(root->left, key);
    return search(root->right, key);
}

void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int count(Node *root) {
    if (root == NULL) return 0;
    return 1 + count(root->left) + count(root->right);
}

int countLeaf(Node *root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeaf(root->left) + countLeaf(root->right);
}

void freeTree(Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

Node* copyTree(Node *root) {
    Node *newNode;
    if (root == NULL) return NULL;
    newNode = createNode(root->data);
    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);
    return newNode;
}

int compareTrees(Node *t1, Node *t2) {
    if (t1 == NULL && t2 == NULL) return 1;
    if (t1 == NULL || t2 == NULL) return 0;
    return (t1->data == t2->data) && compareTrees(t1->left, t2->left) && compareTrees(t1->right, t2->right);
}

int main() {
    Node *root = NULL, *copy1 = NULL;
    int n, value, i;

    printf("Enter number of nodes to insert: ");
    scanf("%d", &n);
    printf("Enter %d values:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insert(root, value);
    }

    printf("Original tree (Inorder): ");
    inorder(root);
    printf("\n");

    copy1 = copyTree(root);
    printf("Copied tree (Inorder): ");
    inorder(copy1);
    printf("\n");

    if (compareTrees(root, copy1))
        printf("Both trees are equal.\n");
    else
        printf("Trees are not equal.\n");

    freeTree(root);
    freeTree(copy1);
    return 0;
}
