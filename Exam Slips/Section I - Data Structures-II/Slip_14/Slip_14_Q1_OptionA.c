/* Q1) Write a C program to maintain a phonebook using Binary Search Tree by name where each node
   contains contact name and phone number. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PhoneNode {
    char name[50];
    char phone[15];
    struct PhoneNode *left, *right;
} PhoneNode;

PhoneNode* createPhoneNode(char name[], char phone[]) {
    PhoneNode *newNode = (PhoneNode*)malloc(sizeof(PhoneNode));
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->left = newNode->right = NULL;
    return newNode;
}

PhoneNode* insertContact(PhoneNode *root, char name[], char phone[]) {
    if (root == NULL) return createPhoneNode(name, phone);
    if (strcmp(name, root->name) < 0) root->left = insertContact(root->left, name, phone);
    else if (strcmp(name, root->name) > 0) root->right = insertContact(root->right, name, phone);
    return root;
}

PhoneNode* searchContact(PhoneNode *root, char name[]) {
    if (root == NULL || strcmp(root->name, name) == 0) return root;
    if (strcmp(name, root->name) < 0) return searchContact(root->left, name);
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
    PhoneNode *result;

    while (1) {
        printf("\n=== Phonebook Menu ===\n");
        printf("1. Add Contact\n2. Search Contact\n3. Display All\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter name: "); scanf("%s", name);
                printf("Enter phone: "); scanf("%s", phone);
                phonebook = insertContact(phonebook, name, phone);
                printf("Contact added.\n");
                break;
            case 2:
                printf("Enter name to search: "); scanf("%s", name);
                result = searchContact(phonebook, name);
                if (result) printf("Found - Name: %s, Phone: %s\n", result->name, result->phone);
                else printf("Contact not found.\n");
                break;
            case 3:
                printf("\nAll Contacts:\n");
                displayContacts(phonebook);
                break;
            case 4: return 0;
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
