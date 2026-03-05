/* Q1) Write a C program to implement a hash table using separate chaining with linked lists
   with following operation: a. Insert a key  b. Search a key  c. Display the hash table */

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

typedef struct Node {
    int key;
    struct Node* next;
} Node;

Node* hashTable[TABLE_SIZE];

int hashFunction(int key) { return key % TABLE_SIZE; }

void initTable() {
    int i;
    for (i = 0; i < TABLE_SIZE; i++) hashTable[i] = NULL;
}

void insertKey(int key) {
    int index = hashFunction(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
    printf("Key %d inserted at index %d\n", key, index);
}

int searchKey(int key) {
    int index = hashFunction(key);
    Node* temp = hashTable[index];
    while (temp != NULL) {
        if (temp->key == key) return 1;
        temp = temp->next;
    }
    return 0;
}

void display() {
    int i;
    printf("\nHash Table:\n");
    for (i = 0; i < TABLE_SIZE; i++) {
        Node* temp = hashTable[i];
        printf("[%d]: ", i);
        while (temp != NULL) {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int choice, key;
    initTable();

    while (1) {
        printf("\n1. Insert\n2. Search\n3. Display\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insertKey(key);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                if (searchKey(key)) printf("Key %d found\n", key);
                else printf("Key %d not found\n", key);
                break;
            case 3: display(); break;
            case 4: return 0;
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
