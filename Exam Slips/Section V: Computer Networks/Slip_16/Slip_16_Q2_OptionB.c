/*
 * Slip 16 - Q2 Option B (OR): Convert Plain to Cipher Message
 * 
 * Performs ROT13 cipher conversion.
 * 
 * Compile: gcc Slip_15_Q2_OptionB.c -o cipher
 * Run: ./cipher
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char msg[256], cipher[256];
    
    printf("Plain Message to Cipher Conversion\n");
    printf("===================================\n");
    printf("Enter message: ");
    fgets(msg, 256, stdin);
    msg[strcspn(msg, "\n")] = '\0';
    
    for (int i = 0; msg[i]; i++) {
        if (isalpha(msg[i])) {
            char base = isupper(msg[i]) ? 'A' : 'a';
            cipher[i] = base + (msg[i] - base + 13) % 26;
        } else {
            cipher[i] = msg[i];
        }
    }
    cipher[strlen(msg)] = '\0';
    
    printf("\nOriginal: %s\n", msg);
    printf("Cipher:   %s\n", cipher);
    
    return 0;
}
