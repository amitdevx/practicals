/*
 * Slip 20 - Q2 Option B (OR): Write a C program for Hash Simulation.
 *
 * Compile: gcc Slip_20_Q2_OptionB.c -o hash_sim
 * Run: ./hash_sim
 */

#include <stdio.h>

int hash_function(const char *key, int table_size) {
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = (hash + key[i]) % table_size;
    }
    return hash;
}

int main(void) {
    const char *keys[] = {"Alice", "Bob", "Charlie", "David", NULL};
    int table_size = 10;

    printf("Hash Simulation\n");
    printf("===============\n\n");
    printf("Hash Table (size: %d)\n", table_size);
    printf("------------------------------\n");
    printf("Key       | Index\n");
    printf("------------------------------\n");

    for (int i = 0; keys[i] != NULL; i++) {
        printf("%-9s | %5d\n", keys[i], hash_function(keys[i], table_size));
    }

    return 0;
}
