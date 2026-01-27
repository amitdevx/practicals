/*
 * Assignment 2 - Set B - Question 2
 * 
 * Write a C program to maintain a phonebook using Binary Search Tree by name where each node
 * contain contact name and phone number.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PhoneNode {
    char name[50];
    char phone[15];
    struct PhoneNode *left;
    struct PhoneNode *right;
} PhoneNode;

PhoneNode* createPhoneNode(char name[], char phone[]) {
    PhoneNode *newNode = (PhoneNode*)malloc(sizeof(PhoneNode));
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

PhoneNode* insertContact(PhoneNode *root, char name[], char phone[]) {
    if (root == NULL) {
        return createPhoneNode(name, phone);
    }
    if (strcmp(name, root->name) < 0) {
        root->left = insertContact(root->left, name, phone);
    } else if (strcmp(name, root->name) > 0) {
        root->right = insertContact(root->right, name, phone);
    }
    return root;
}

PhoneNode* searchContact(PhoneNode *root, char name[]) {
    if (root == NULL || strcmp(root->name, name) == 0) {
        return root;
    }
    if (strcmp(name, root->name) < 0) {
        return searchContact(root->left, name);
    }
    return searchContact(root->right, name);
}

void displayContacts(PhoneNode *root) {
    if (root != NULL) {
        displayContacts(root->left);
        printf("Name: %s, Phone: %s\n", root->name, root->phone);
        displayContacts(root->right);
    }
}

int main() {
    PhoneNode *phonebook = NULL;
    int choice;
    char name[50], phone[15];

    while (1) {
        printf("\n=== Phonebook Menu ===\n");
        printf("1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Display All Contacts\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter phone number: ");
                scanf("%s", phone);
                phonebook = insertContact(phonebook, name, phone);
                printf("Contact added successfully.\n");
                break;

            case 2:
                printf("Enter name to search: ");
                scanf("%s", name);
                PhoneNode *result = searchContact(phonebook, name);
                if (result != NULL) {
                    printf("Contact found - Name: %s, Phone: %s\n", result->name, result->phone);
                } else {
                    printf("Contact not found.\n");
                }
                break;

            case 3:
                printf("\nAll Contacts:\n");
                displayContacts(phonebook);
                break;

            case 4:
                printf("Exiting phonebook.\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
