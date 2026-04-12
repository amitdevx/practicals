/*
 * Slip 17 - Q2 Option B: Write a C program to convert plain message to cipher
 * message.
 *
 * Compile: gcc Slip_17_Q2_OptionB.c -o cipher
 * Run: ./cipher
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char msg[256], cipher[256];

    printf("Plain Message to Cipher Conversion\n");
    printf("===================================\n");
    printf("Enter message: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = '\0';

    for (int i = 0; msg[i] != '\0'; i++) {
        if (isalpha((unsigned char)msg[i])) {
            char base = isupper((unsigned char)msg[i]) ? 'A' : 'a';
            cipher[i] = (char)(base + (msg[i] - base + 13) % 26);
        } else {
            cipher[i] = msg[i];
        }
    }
    cipher[strlen(msg)] = '\0';

    printf("Original: %s\n", msg);
    printf("Cipher:   %s\n", cipher);

    return 0;
}
