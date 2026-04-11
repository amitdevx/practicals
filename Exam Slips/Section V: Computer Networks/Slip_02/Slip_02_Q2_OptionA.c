/*
 * Slip 2 - Q2 Option A: Simple Hash Simulation
 *
 * Compile: gcc Slip_02_Q2_OptionA.c -o hash
 * Run: ./hash
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TABLE_SIZE 10

typedef struct {
    char key[50];
    int value;
} HashEntry;

HashEntry table[TABLE_SIZE];
int count = 0;

unsigned int hash(const char *key) {
    unsigned int h = 0;
    for (int i = 0; key[i]; i++) {
        h = h * 31 + key[i];
    }
    return h % TABLE_SIZE;
}

void insert(const char *key, int val) {
    unsigned int idx = hash(key);
    strcpy(table[idx].key, key);
    table[idx].value = val;
    printf("Inserted %s -> %d at index %d\n", key, val, idx);
}

int lookup(const char *key) {
    unsigned int idx = hash(key);
    if (strcmp(table[idx].key, key) == 0) {
        return table[idx].value;
    }
    return -1;
}

void display() {
    printf("\nHash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].key[0] != '\0') {
            printf("Index %d: %s -> %d\n", i, table[i].key, table[i].value);
        }
    }
}

int main() {
    char key[50];
    int value, choice;

    while (1) {
        printf("\n1. Insert  2. Lookup  3. Display  4. Exit\nChoice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Key: ");
                fgets(key, 50, stdin);
                key[strcspn(key, "\n")] = '\0';
                printf("Value: ");
                scanf("%d", &value);
                insert(key, value);
                break;
            case 2:
                printf("Key to search: ");
                fgets(key, 50, stdin);
                key[strcspn(key, "\n")] = '\0';
                value = lookup(key);
                printf("Result: %d\n", value);
                break;
            case 3:
                display();
                break;
            case 4:
                return 0;
        }
    }
}
