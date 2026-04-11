/* Q2) Write a C program for Hash Simulation.
   Implements hash table with linear probing collision resolution. */

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10
#define EMPTY -1
#define DELETED -2

int hashTable[TABLE_SIZE];
int collisionCount = 0;

void initializeTable() {
    int i;
    for (i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = EMPTY;
    }
    collisionCount = 0;
}

int hashFunction(int key) {
    return key % TABLE_SIZE;
}

int insert(int key) {
    int index = hashFunction(key);
    int originalIndex = index;
    int probeCount = 0;

    if (hashTable[index] == key) {
        printf("  Key %d already exists at index %d\n", key, index);
        return -1;
    }

    while (hashTable[index] != EMPTY && hashTable[index] != DELETED) {
        if (hashTable[index] == key) {
            printf("  Key %d already exists at index %d\n", key, index);
            return -1;
        }

        collisionCount++;
        probeCount++;
        printf("  Collision at index %d! Probing next slot...\n", index);

        index = (index + 1) % TABLE_SIZE;

        if (index == originalIndex) {
            printf("  ERROR: Hash table is full!\n");
            return -1;
        }
    }

    hashTable[index] = key;

    if (probeCount > 0) {
        printf("  Inserted %d at index %d after %d probe(s)\n", key, index, probeCount);
    } else {
        printf("  Inserted %d at index %d (no collision)\n", key, index);
    }

    return index;
}

int search(int key) {
    int index = hashFunction(key);
    int originalIndex = index;
    int probeCount = 0;

    while (hashTable[index] != EMPTY) {
        if (hashTable[index] == key) {
            printf("  Key %d found at index %d", key, index);
            if (probeCount > 0) {
                printf(" after %d probe(s)", probeCount);
            }
            printf("\n");
            return index;
        }

        probeCount++;
        index = (index + 1) % TABLE_SIZE;

        if (index == originalIndex) {
            break;
        }
    }

    printf("  Key %d not found in hash table\n", key);
    return -1;
}

int deleteKey(int key) {
    int index = hashFunction(key);
    int originalIndex = index;

    while (hashTable[index] != EMPTY) {
        if (hashTable[index] == key) {
            hashTable[index] = DELETED;
            printf("  Key %d deleted from index %d\n", key, index);
            return index;
        }

        index = (index + 1) % TABLE_SIZE;

        if (index == originalIndex) {
            break;
        }
    }

    printf("  Key %d not found, cannot delete\n", key);
    return -1;
}

void displayTable() {
    int i, count = 0;

    printf("\n  +-------+--------+--------+\n");
    printf("  | Index |  Key   | Status |\n");
    printf("  +-------+--------+--------+\n");

    for (i = 0; i < TABLE_SIZE; i++) {
        printf("  |   %d   |", i);
        if (hashTable[i] == EMPTY) {
            printf("   --   |  Empty |\n");
        } else if (hashTable[i] == DELETED) {
            printf("   --   | Delete |\n");
        } else {
            printf("  %4d  | Filled |\n", hashTable[i]);
            count++;
        }
    }

    printf("  +-------+--------+--------+\n");
    printf("  Load Factor: %.2f (%d/%d slots filled)\n",
           (float)count / TABLE_SIZE, count, TABLE_SIZE);
    printf("  Total Collisions: %d\n", collisionCount);
}

void displayHashFunction() {
    printf("\n  ========================================\n");
    printf("         HASH FUNCTION DETAILS\n");
    printf("  ========================================\n\n");

    printf("  Hash Function: h(key) = key %% %d\n\n", TABLE_SIZE);

    printf("  Example calculations:\n");
    printf("  h(25) = 25 %% %d = %d\n", TABLE_SIZE, 25 % TABLE_SIZE);
    printf("  h(35) = 35 %% %d = %d\n", TABLE_SIZE, 35 % TABLE_SIZE);
    printf("  h(45) = 45 %% %d = %d\n", TABLE_SIZE, 45 % TABLE_SIZE);
    printf("  h(12) = 12 %% %d = %d\n", TABLE_SIZE, 12 % TABLE_SIZE);
    printf("  h(99) = 99 %% %d = %d\n", TABLE_SIZE, 99 % TABLE_SIZE);

    printf("\n  Collision Resolution: Linear Probing\n");
    printf("  If h(key) occupied, try h(key)+1, h(key)+2, ...\n");
}

void runDemo() {
    int demoKeys[] = {25, 35, 45, 15, 55, 12, 22, 32};
    int searchKeys[] = {35, 55, 100};
    int i, n;

    printf("\n  ========================================\n");
    printf("            HASH SIMULATION DEMO\n");
    printf("  ========================================\n");

    initializeTable();

    printf("\n  --- Inserting Keys ---\n\n");
    n = sizeof(demoKeys) / sizeof(demoKeys[0]);
    for (i = 0; i < n; i++) {
        printf("  hash(%d) = %d %% %d = %d\n",
               demoKeys[i], demoKeys[i], TABLE_SIZE, hashFunction(demoKeys[i]));
        insert(demoKeys[i]);
        printf("\n");
    }

    printf("\n  --- Current Hash Table ---");
    displayTable();

    printf("\n  --- Searching Keys ---\n\n");
    n = sizeof(searchKeys) / sizeof(searchKeys[0]);
    for (i = 0; i < n; i++) {
        printf("  Searching for %d: ", searchKeys[i]);
        search(searchKeys[i]);
    }

    printf("\n  --- Deleting Key 35 ---\n");
    deleteKey(35);

    printf("\n  --- Searching for deleted key ---\n");
    printf("  Searching for 35: ");
    search(35);

    printf("\n  --- Final Hash Table ---");
    displayTable();
}

int main() {
    int choice, key;

    printf("========================================\n");
    printf("       HASH TABLE SIMULATION\n");
    printf("       (Linear Probing Method)\n");
    printf("========================================\n");

    displayHashFunction();

    initializeTable();

    while (1) {
        printf("\n  ========================================\n");
        printf("               MENU\n");
        printf("  ========================================\n");
        printf("  1. Insert a key\n");
        printf("  2. Search for a key\n");
        printf("  3. Delete a key\n");
        printf("  4. Display hash table\n");
        printf("  5. Run demo simulation\n");
        printf("  6. Reset table\n");
        printf("  7. Exit\n");
        printf("  ========================================\n");
        printf("  Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n  Enter key to insert: ");
                scanf("%d", &key);
                if (key < 0) {
                    printf("  Error: Please enter positive integers only\n");
                } else {
                    insert(key);
                }
                break;

            case 2:
                printf("\n  Enter key to search: ");
                scanf("%d", &key);
                search(key);
                break;

            case 3:
                printf("\n  Enter key to delete: ");
                scanf("%d", &key);
                deleteKey(key);
                break;

            case 4:
                displayTable();
                break;

            case 5:
                runDemo();
                break;

            case 6:
                initializeTable();
                printf("\n  Hash table reset successfully!\n");
                break;

            case 7:
                printf("\n  ========================================\n");
                printf("        PROGRAM TERMINATED\n");
                printf("  ========================================\n\n");
                return 0;

            default:
                printf("\n  Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
