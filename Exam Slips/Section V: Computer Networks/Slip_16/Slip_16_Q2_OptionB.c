/*
 * Slip 16 - Q2 Option B: Convert Plain Message to Cipher
 * 
 * ROT13 cipher transformation.
 * 
 * Compile: gcc Slip_16_Q2_OptionB.c -o cipher
 * Run: ./cipher
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char message[256], cipher[256];
    
    printf("Plain Message to Cipher Conversion (ROT13)\n");
    printf("==========================================\n");
    printf("Enter message: ");
    fgets(message, 256, stdin);
    message[strcspn(message, "\n")] = '\0';
    
    for (int i = 0; message[i]; i++) {
        if (isalpha(message[i])) {
            char base = isupper(message[i]) ? 'A' : 'a';
            cipher[i] = base + (message[i] - base + 13) % 26;
        } else {
            cipher[i] = message[i];
        }
    }
    cipher[strlen(message)] = '\0';
    
    printf("\nConversion Result:\n");
    printf("Original: %s\n", message);
    printf("Cipher:   %s\n", cipher);
    printf("Method: ROT13 (Rotate 13 positions)\n");
    
    return 0;
}
