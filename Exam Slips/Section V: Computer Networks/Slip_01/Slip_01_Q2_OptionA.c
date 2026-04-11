/*
 * Slip 1 - Q2 Option A: Simple Hash Simulation
 * 
 * Simulates a hash function for data storage.
 * 
 * Compile: gcc Slip_01_Q2_OptionA.c -o hash_sim
 * Run: ./hash_sim
 */

#include <stdio.h>
#include <string.h>

int hash_function(char *key) {
    int hash = 0;
    for (int i = 0; key[i]; i++) {
        hash = (hash + key[i]) % 10;
    }
    return hash;
}

int main() {
    char keys[][20] = {"Alice", "Bob", "Charlie", "David", ""};
    
    printf("Hash Simulation\n");
    printf("===============\n\n");
    printf("Hash Table (size: 10)\n");
    printf("Key       | Hash Index\n");
    printf("──────────┼───────────\n");
    
    for (int i = 0; keys[i][0]; i++) {
        int idx = hash_function(keys[i]);
        printf("%-9s | %d\n", keys[i], idx);
    }
    
    return 0;
}
