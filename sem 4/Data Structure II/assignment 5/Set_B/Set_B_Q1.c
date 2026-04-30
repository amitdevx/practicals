/*
 * Assignment 5 - Set B - Question 1
 * 
 * Write a C program to implement a hash table using open addressing with linear probing. Perform
 * the following operations (Assume all keys are positive integers):
 * a. Insert
 * b. Search
 * c. Delete
 * d. Display
 */

#include <stdio.h>

#define TABLE_SIZE 10
#define EMPTY -1
#define DELETED -2

int hashTable[TABLE_SIZE];

void initHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = EMPTY;
    }
}

int hashFunction(int key) {
    return key % TABLE_SIZE;
}

void insert(int key) {
    int index = hashFunction(key);
    int i = 0;
    
    while (i < TABLE_SIZE) {
        int newIndex = (index + i) % TABLE_SIZE;
        
        if (hashTable[newIndex] == EMPTY || hashTable[newIndex] == DELETED) {
            hashTable[newIndex] = key;
            printf("Key %d inserted at index %d\n", key, newIndex);
            return;
        }
        i++;
    }
    
    printf("Hash table is full! Cannot insert %d\n", key);
}

int search(int key) {
    int index = hashFunction(key);
    int i = 0;
    
    while (i < TABLE_SIZE) {
        int newIndex = (index + i) % TABLE_SIZE;
        
        if (hashTable[newIndex] == EMPTY) {
            return -1;
        }
        if (hashTable[newIndex] == key) {
            return newIndex;
        }
        i++;
    }
    
    return -1;
}

void deleteKey(int key) {
    int index = search(key);
    
    if (index == -1) {
        printf("Key %d not found\n", key);
        return;
    }
    
    hashTable[index] = DELETED;
    printf("Key %d deleted from index %d\n", key, index);
}

void display() {
    printf("\nHash Table:\n");
    printf("Index\tKey\n");
    printf("-----\t---\n");
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%d\t", i);
        if (hashTable[i] == EMPTY) {
            printf("EMPTY\n");
        } else if (hashTable[i] == DELETED) {
            printf("DELETED\n");
        } else {
            printf("%d\n", hashTable[i]);
        }
    }
}

int main() {
    initHashTable();
    int choice, key;
    
    while (1) {
        printf("\n=== Linear Probing Hash Table ===\n");
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
                int index = search(key);
                if (index != -1) {
                    printf("Key %d found at index %d\n", key, index);
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
