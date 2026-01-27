/*
 * Assignment 5 - Set A - Question 2
 * 
 * Write a C program to implement a hash table using separate chaining with linked lists with
 * following operation:
 * a. Insert a key
 * b. Search a key
 * c. Delete a key
 * d. Display the hash table
 */

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

typedef struct Node {
    int key;
    struct Node* next;
} Node;

Node* hashTable[TABLE_SIZE];

void initHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

int hashFunction(int key) {
    return key % TABLE_SIZE;
}

void insert(int key) {
    int index = hashFunction(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
    printf("Key %d inserted at index %d\n", key, index);
}

int search(int key) {
    int index = hashFunction(key);
    Node* temp = hashTable[index];
    
    while (temp != NULL) {
        if (temp->key == key) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void deleteKey(int key) {
    int index = hashFunction(key);
    Node* temp = hashTable[index];
    Node* prev = NULL;
    
    while (temp != NULL && temp->key != key) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Key %d not found\n", key);
        return;
    }
    
    if (prev == NULL) {
        hashTable[index] = temp->next;
    } else {
        prev->next = temp->next;
    }
    
    free(temp);
    printf("Key %d deleted\n", key);
}

void display() {
    printf("\nHash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: ", i);
        Node* temp = hashTable[i];
        while (temp != NULL) {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    initHashTable();
    int choice, key;
    
    while (1) {
        printf("\n=== Hash Table Menu ===\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(key);
                break;
                
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                if (search(key)) {
                    printf("Key %d found\n", key);
                } else {
                    printf("Key %d not found\n", key);
                }
                break;
                
            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                deleteKey(key);
                break;
                
            case 4:
                display();
                break;
                
            case 5:
                printf("Exiting...\n");
                return 0;
                
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
