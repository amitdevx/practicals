/*
 * Assignment 1 - Set A - Question 1
 * 
 * Implement a Binary search tree (BST) library (btree.h) with operations – create, search,
 * insert, inorder, preorder and postorder. Write a menu driven program that performs the above
 * operations.
 */

#include <stdio.h>
#include "../btree.h"

int main() {
    Node *root = NULL;
    int choice, value;

    while (1) {
        printf("\n=== Binary Search Tree Operations ===\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Inorder Traversal\n");
        printf("4. Preorder Traversal\n");
        printf("5. Postorder Traversal\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                printf("Value %d inserted successfully.\n", value);
                break;

            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (search(root, value) != NULL) {
                    printf("Value %d found in the tree.\n", value);
                } else {
                    printf("Value %d not found in the tree.\n", value);
                }
                break;

            case 3:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 4:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;

            case 5:
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;

            case 6:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
