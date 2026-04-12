/*
 * Slip 2 - Q2 Option A: Simple Hash Simulation
 *
 * Compile: gcc Slip_02_Q2_OptionA.c -o hash_sim
 * Run: ./hash_sim
 */

#include <stdio.h>
#include <string.h>

int hash_function(const char *s, int table_size) {
    int h = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        h = (h + s[i]) % table_size;
    }
    return h;
}

int main(void) {
    const char *keys[] = {"PC1", "PC2", "SWITCH", "ROUTER", "SERVER", NULL};
    int table_size = 10;

    printf("Simple Hash Simulation\n");
    printf("======================\n");
    printf("Hash table size: %d\n\n", table_size);

    printf("Key      -> Hash Index\n");
    printf("-----------------------\n");
    for (int i = 0; keys[i] != NULL; i++) {
        printf("%-8s -> %d\n", keys[i], hash_function(keys[i], table_size));
    }

    return 0;
}
