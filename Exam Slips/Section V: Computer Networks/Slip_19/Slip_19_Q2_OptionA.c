/*
 * Slip 19 - Q2 Option A: Hash Simulation
 * 
 * Simulates hash function for data storage.
 * 
 * Compile: gcc Slip_19_Q2_OptionA.c -o hash_sim
 * Run: ./hash_sim
 */

#include <stdio.h>
#include <string.h>

int hash_function(char *key, int table_size) {
    int hash = 0;
    for (int i = 0; key[i]; i++) {
        hash = (hash + key[i]) % table_size;
    }
    return hash;
}

int main() {
    printf("Hash Simulation\n");
    printf("===============\n\n");
    
    int table_size = 10;
    char *keys[] = {"Alice", "Bob", "Charlie", "David"};
    
    printf("Hash Table (size: %d)\n", table_size);
    printf("─────────────────────────────────\n");
    printf("Key       | Hash Value | Index\n");
    printf("─────────────────────────────────\n");
    
    for (int i = 0; keys[i]; i++) {
        int hash = hash_function(keys[i], table_size);
        printf("%-9s | %10s | %5d\n", keys[i], keys[i], hash);
    }
    
    printf("\nHash Distribution:\n");
    for (int i = 0; i < table_size; i++) {
        printf("Index %d: ", i);
        for (int j = 0; keys[j]; j++) {
            if (hash_function(keys[j], table_size) == i) {
                printf("%s ", keys[j]);
            }
        }
        printf("\n");
    }
    
    return 0;
}
