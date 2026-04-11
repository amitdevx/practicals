/*
 * Slip 15 - Q2 Option A: Encryption (Plain to Cipher Message)
 * 
 * Simple Caesar cipher encryption.
 * 
 * Compile: gcc Slip_15_Q2_OptionA.c -o encryption
 * Run: ./encryption
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char plain[256], cipher[256];
    int shift = 3;
    
    printf("Encryption: Plain Message to Cipher Message\n");
    printf("==========================================\n");
    printf("Shift value: %d\n", shift);
    printf("Enter plain text: ");
    fgets(plain, 256, stdin);
    plain[strcspn(plain, "\n")] = '\0';
    
    for (int i = 0; plain[i]; i++) {
        if (isalpha(plain[i])) {
            char base = isupper(plain[i]) ? 'A' : 'a';
            cipher[i] = base + (plain[i] - base + shift) % 26;
        } else {
            cipher[i] = plain[i];
        }
    }
    cipher[strlen(plain)] = '\0';
    
    printf("\nEncryption Result:\n");
    printf("Plain:  %s\n", plain);
    printf("Cipher: %s\n", cipher);
    printf("Method: Caesar Cipher (Shift %d)\n", shift);
    
    return 0;
}
