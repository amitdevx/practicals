/* Q1) Write a C program to implement a hash table using Open Addressing with Quadratic Probing.
   Perform the following operations (Assume all keys are positive integers):
   a. Insert  b. Delete  c. Display */

#include <stdio.h>

#define TABLE_SIZE 10
#define EMPTY -1
#define DELETED -2

int hashTable[TABLE_SIZE];

int hashFunction(int key) { return key % TABLE_SIZE; }

void initTable() {
    int i;
    for (i = 0; i < TABLE_SIZE; i++) hashTable[i] = EMPTY;
}

void insertKey(int key) {
    int index = hashFunction(key), i;
    for (i = 0; i < TABLE_SIZE; i++) {
        int newIndex = (index + i * i) % TABLE_SIZE;
        if (hashTable[newIndex] == EMPTY || hashTable[newIndex] == DELETED) {
            hashTable[newIndex] = key;
            printf("Key %d inserted at index %d\n", key, newIndex);
            return;
        }
    }
    printf("Hash table is full! Cannot insert %d\n", key);
}

int searchKey(int key) {
    int index = hashFunction(key), i;
    for (i = 0; i < TABLE_SIZE; i++) {
        int newIndex = (index + i * i) % TABLE_SIZE;
        if (hashTable[newIndex] == EMPTY) return -1;
        if (hashTable[newIndex] == key) return newIndex;
    }
    return -1;
}

void deleteKey(int key) {
    int index = searchKey(key);
    if (index == -1) { printf("Key %d not found\n", key); return; }
    hashTable[index] = DELETED;
    printf("Key %d deleted from index %d\n", key, index);
}

void display() {
    int i;
    printf("\nHash Table:\nIndex\tKey\n");
    for (i = 0; i < TABLE_SIZE; i++) {
        printf("%d\t", i);
        if (hashTable[i] == EMPTY) printf("EMPTY\n");
        else if (hashTable[i] == DELETED) printf("DELETED\n");
        else printf("%d\n", hashTable[i]);
    }
}

int main() {
    int choice, key;
    initTable();

    while (1) {
        printf("\n1. Insert\n2. Delete\n3. Display\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insertKey(key);
                break;
            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                deleteKey(key);
                break;
            case 3: display(); break;
            case 4: return 0;
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
