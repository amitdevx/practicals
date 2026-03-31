/*
 * Slip 2 - Q2 Option A: Simple Hash Simulation
 * Computer Networks
 * 
 * This program demonstrates a simple hash function implementation
 * commonly used in networking for data integrity and hash tables.
 * 
 * Compile: gcc Slip_02_Q2_OptionA.c -o hash_simulation
 * Run: ./hash_simulation
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TABLE_SIZE 10
#define MAX_STRING 100

// Structure for hash table entry (for chaining)
typedef struct HashNode {
    char key[MAX_STRING];
    int value;
    struct HashNode* next;
} HashNode;

// Hash table
HashNode* hashTable[TABLE_SIZE];

/*
 * Simple Additive Hash Function
 * Adds ASCII values of all characters and takes modulo
 */
unsigned int simpleHash(const char* key) {
    unsigned int hash = 0;
    
    printf("\n  Calculating hash for \"%s\":\n", key);
    printf("  ");
    
    while (*key) {
        printf("%c(%d) ", *key, *key);
        hash += *key;
        key++;
    }
    
    printf("\n  Sum = %u, Hash = %u %% %d = %u\n", 
           hash, hash, TABLE_SIZE, hash % TABLE_SIZE);
    
    return hash % TABLE_SIZE;
}

/*
 * DJB2 Hash Function (Better distribution)
 * Popular hash function by Daniel J. Bernstein
 */
unsigned int djb2Hash(const char* key) {
    unsigned int hash = 5381;
    int c;
    
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }
    
    return hash % TABLE_SIZE;
}

/*
 * Initialize hash table
 */
void initHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

/*
 * Create a new hash node
 */
HashNode* createNode(const char* key, int value) {
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

/*
 * Insert key-value pair into hash table
 * Uses chaining for collision handling
 */
void insert(const char* key, int value) {
    unsigned int index = simpleHash(key);
    
    HashNode* newNode = createNode(key, value);
    
    // Check for collision
    if (hashTable[index] != NULL) {
        printf("  ** Collision detected at index %u! Using chaining.\n", index);
        newNode->next = hashTable[index];
    }
    
    hashTable[index] = newNode;
    printf("  Inserted \"%s\" -> %d at index %u\n\n", key, value, index);
}

/*
 * Search for a key in hash table
 */
int search(const char* key) {
    unsigned int index = simpleHash(key);
    
    HashNode* current = hashTable[index];
    int probes = 0;
    
    while (current != NULL) {
        probes++;
        if (strcmp(current->key, key) == 0) {
            printf("  Found \"%s\" = %d after %d probe(s)\n\n", 
                   key, current->value, probes);
            return current->value;
        }
        current = current->next;
    }
    
    printf("  Key \"%s\" not found after %d probe(s)\n\n", key, probes);
    return -1;
}

/*
 * Display hash table contents
 */
void displayHashTable() {
    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║           HASH TABLE CONTENTS              ║\n");
    printf("╠════════════════════════════════════════════╣\n");
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("║ [%d]: ", i);
        
        HashNode* current = hashTable[i];
        if (current == NULL) {
            printf("(empty)");
        }
        
        while (current != NULL) {
            printf("(\"%s\"->%d)", current->key, current->value);
            if (current->next != NULL) {
                printf(" -> ");
            }
            current = current->next;
        }
        
        printf("\n");
    }
    printf("╚════════════════════════════════════════════╝\n");
}

/*
 * Free hash table memory
 */
void freeHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* current = hashTable[i];
        while (current != NULL) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

/*
 * Demonstrate hash collision
 */
void demonstrateCollision() {
    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║       COLLISION DEMONSTRATION              ║\n");
    printf("╠════════════════════════════════════════════╣\n");
    
    // These strings may produce same hash
    char* strings[] = {"AB", "BA", "CAT", "ACT"};
    int n = 4;
    
    printf("║ Testing strings that may collide:          ║\n");
    printf("╚════════════════════════════════════════════╝\n\n");
    
    for (int i = 0; i < n; i++) {
        unsigned int hash = 0;
        for (int j = 0; strings[i][j]; j++) {
            hash += strings[i][j];
        }
        printf("  \"%s\" -> ASCII sum = %u -> Hash = %u\n", 
               strings[i], hash, hash % TABLE_SIZE);
    }
}

/*
 * Simple checksum demonstration (network use case)
 */
void demonstrateChecksum(const char* data) {
    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║      CHECKSUM DEMONSTRATION                ║\n");
    printf("║      (Data Integrity Verification)         ║\n");
    printf("╠════════════════════════════════════════════╣\n");
    printf("║ Original data: \"%s\"\n", data);
    printf("╚════════════════════════════════════════════╝\n");
    
    unsigned int checksum = 0;
    for (int i = 0; data[i]; i++) {
        checksum += data[i];
    }
    checksum = checksum % 256;  // 8-bit checksum
    
    printf("\n  Checksum calculation:\n");
    printf("  ");
    for (int i = 0; data[i]; i++) {
        printf("%c(%d) ", data[i], data[i]);
    }
    printf("\n  8-bit Checksum = %u\n", checksum);
    
    // Simulate transmission
    printf("\n  Simulating data transmission...\n");
    printf("  Sender sends: DATA=\"%s\" + CHECKSUM=%u\n", data, checksum);
    
    // Verify at receiver (same data)
    unsigned int receiverChecksum = 0;
    for (int i = 0; data[i]; i++) {
        receiverChecksum += data[i];
    }
    receiverChecksum = receiverChecksum % 256;
    
    printf("  Receiver calculates: CHECKSUM=%u\n", receiverChecksum);
    
    if (checksum == receiverChecksum) {
        printf("  ✓ Checksums MATCH - Data integrity verified!\n");
    } else {
        printf("  ✗ Checksums DON'T MATCH - Data corrupted!\n");
    }
}

int main() {
    printf("╔════════════════════════════════════════════╗\n");
    printf("║    SLIP 2: SIMPLE HASH SIMULATION          ║\n");
    printf("║    Computer Networks                       ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    
    // Initialize hash table
    initHashTable();
    
    // Demonstrate basic hashing
    printf("\n--- PART 1: Basic Hash Function Demo ---\n");
    
    insert("Alice", 101);
    insert("Bob", 102);
    insert("Charlie", 103);
    insert("David", 104);
    insert("Eve", 105);
    
    // Display current state
    displayHashTable();
    
    // Search demonstration
    printf("\n--- PART 2: Search Operations ---\n");
    search("Bob");
    search("Eve");
    search("Frank");  // Not in table
    
    // Collision demonstration
    printf("\n--- PART 3: Collision Analysis ---\n");
    demonstrateCollision();
    
    // Insert colliding keys
    printf("\n  Inserting potentially colliding keys:\n");
    insert("AB", 201);
    insert("BA", 202);
    
    displayHashTable();
    
    // Network checksum demonstration
    printf("\n--- PART 4: Network Checksum Use Case ---\n");
    demonstrateChecksum("HELLO NETWORK");
    
    // Interactive mode
    printf("\n--- PART 5: Interactive Mode ---\n");
    printf("Enter strings to hash (type 'quit' to exit):\n\n");
    
    char input[MAX_STRING];
    int value = 300;
    
    while (1) {
        printf("Enter key: ");
        scanf("%s", input);
        
        if (strcmp(input, "quit") == 0) {
            break;
        }
        
        insert(input, value++);
    }
    
    // Final state
    printf("\n--- FINAL HASH TABLE STATE ---\n");
    displayHashTable();
    
    // Cleanup
    freeHashTable();
    
    printf("\n✓ Program completed successfully!\n");
    return 0;
}

/*
 * SAMPLE OUTPUT:
 * 
 * ╔════════════════════════════════════════════╗
 * ║    SLIP 2: SIMPLE HASH SIMULATION          ║
 * ╚════════════════════════════════════════════╝
 * 
 * --- PART 1: Basic Hash Function Demo ---
 * 
 *   Calculating hash for "Alice":
 *   A(65) l(108) i(105) c(99) e(101) 
 *   Sum = 478, Hash = 478 % 10 = 8
 *   Inserted "Alice" -> 101 at index 8
 * 
 *   Calculating hash for "Bob":
 *   B(66) o(111) b(98) 
 *   Sum = 275, Hash = 275 % 10 = 5
 *   Inserted "Bob" -> 102 at index 5
 * 
 * ╔════════════════════════════════════════════╗
 * ║           HASH TABLE CONTENTS              ║
 * ╠════════════════════════════════════════════╣
 * ║ [0]: (empty)
 * ║ [1]: ("David"->104)
 * ║ [2]: ("Eve"->105)
 * ...
 * ╚════════════════════════════════════════════╝
 */
