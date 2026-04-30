/* Q1) Write a C program which uses Binary search tree library and display the following
   i. Node value at each level
   ii. Count of node at each level
   iii. Total levels in the tree. */

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
