/*
 * Slip 16 - Q2 Option A: Caesar Cipher Encryption Program
 *
 * Description: Encrypts plaintext message to ciphertext using Caesar Cipher
 * The Caesar Cipher shifts each letter by a fixed number of positions
 *
 * Compilation: gcc -o caesar_cipher Slip_16_Q2_OptionA.c
 * Execution:   ./caesar_cipher
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_MSG_LEN 1000

/*
 * Function: caesarEncrypt
 * -----------------------
 * Encrypts a message using Caesar Cipher
 *
 * Parameters:
 *   plaintext  - Original message to encrypt
 *   ciphertext - Buffer to store encrypted message
 *   key        - Number of positions to shift (0-25)
 *
 * Algorithm:
 *   For each character:
 *     - If uppercase: shift = (char - 'A' + key) % 26 + 'A'
 *     - If lowercase: shift = (char - 'a' + key) % 26 + 'a'
 *     - Non-alphabetic characters remain unchanged
 */
void caesarEncrypt(const char *plaintext, char *ciphertext, int key) {
    int i;
    int len = strlen(plaintext);

    // Normalize key to 0-25 range
    key = ((key % 26) + 26) % 26;

    for (i = 0; i < len; i++) {
        if (isupper(plaintext[i])) {
            // Encrypt uppercase letters
            ciphertext[i] = ((plaintext[i] - 'A' + key) % 26) + 'A';
        }
        else if (islower(plaintext[i])) {
            // Encrypt lowercase letters
            ciphertext[i] = ((plaintext[i] - 'a' + key) % 26) + 'a';
        }
        else {
            // Keep non-alphabetic characters unchanged
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[len] = '\0';
}

/*
 * Function: caesarDecrypt
 * -----------------------
 * Decrypts a message encrypted with Caesar Cipher
 *
 * Parameters:
 *   ciphertext - Encrypted message
 *   plaintext  - Buffer to store decrypted message
 *   key        - Number of positions that was used to shift
 */
void caesarDecrypt(const char *ciphertext, char *plaintext, int key) {
    int i;
    int len = strlen(ciphertext);

    // Normalize key to 0-25 range
    key = ((key % 26) + 26) % 26;

    for (i = 0; i < len; i++) {
        if (isupper(ciphertext[i])) {
            // Decrypt uppercase letters
            plaintext[i] = ((ciphertext[i] - 'A' - key + 26) % 26) + 'A';
        }
        else if (islower(ciphertext[i])) {
            // Decrypt lowercase letters
            plaintext[i] = ((ciphertext[i] - 'a' - key + 26) % 26) + 'a';
        }
        else {
            // Keep non-alphabetic characters unchanged
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[len] = '\0';
}

/*
 * Function: displayShiftTable
 * ---------------------------
 * Displays the character mapping for a given shift key
 */
void displayShiftTable(int key) {
    int i;


    for (i = 0; i < 26; i++) {
        printf("%c ", 'A' + i);
    }


    for (i = 0; i < 26; i++) {
        printf("%c ", 'A' + ((i + key) % 26));
    }


}

/*
 * Function: bruteForceAttack
 * --------------------------
 * Attempts all 26 possible shifts to decrypt a message
 * Useful for cryptanalysis when key is unknown
 */
void bruteForceAttack(const char *ciphertext) {
    char decrypted[MAX_MSG_LEN];
    int key;


    for (key = 0; key < 26; key++) {
        caesarDecrypt(ciphertext, decrypted, key);

    }


}

int main() {
    char plaintext[MAX_MSG_LEN];
    char ciphertext[MAX_MSG_LEN];
    char decrypted[MAX_MSG_LEN];
    int key;
    int choice;


    while (1) {


        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                printf("\n--- ENCRYPTION ---\n");
                printf("Enter plaintext message: ");
                fgets(plaintext, MAX_MSG_LEN, stdin);
                plaintext[strcspn(plaintext, "\n")] = '\0';

                printf("Enter shift key (1-25): ");
                scanf("%d", &key);

                caesarEncrypt(plaintext, ciphertext, key);


                break;

            case 2:
                printf("\n--- DECRYPTION ---\n");
                printf("Enter ciphertext message: ");
                fgets(ciphertext, MAX_MSG_LEN, stdin);
                ciphertext[strcspn(ciphertext, "\n")] = '\0';

                printf("Enter shift key (1-25): ");
                scanf("%d", &key);

                caesarDecrypt(ciphertext, decrypted, key);


                break;

            case 3:
                printf("\nEnter shift key to display table: ");
                scanf("%d", &key);
                displayShiftTable(key);
                break;

            case 4:
                printf("\n--- BRUTE FORCE ATTACK ---\n");
                printf("Enter ciphertext to crack: ");
                fgets(ciphertext, MAX_MSG_LEN, stdin);
                ciphertext[strcspn(ciphertext, "\n")] = '\0';
                bruteForceAttack(ciphertext);
                break;

            case 5:


                // Demo 1: Simple message
                strcpy(plaintext, "HELLO WORLD");
                key = 3;
                caesarEncrypt(plaintext, ciphertext, key);
                caesarDecrypt(ciphertext, decrypted, key);

                printf("\n[Demo 1: Simple uppercase message]\n");
                printf("  Plaintext:  %s\n", plaintext);
                printf("  Key:        %d\n", key);
                printf("  Encrypted:  %s\n", ciphertext);
                printf("  Decrypted:  %s\n", decrypted);

                // Demo 2: Mixed case with punctuation
                strcpy(plaintext, "Attack at Dawn!");
                key = 5;
                caesarEncrypt(plaintext, ciphertext, key);
                caesarDecrypt(ciphertext, decrypted, key);

                printf("\n[Demo 2: Mixed case with punctuation]\n");
                printf("  Plaintext:  %s\n", plaintext);
                printf("  Key:        %d\n", key);
                printf("  Encrypted:  %s\n", ciphertext);
                printf("  Decrypted:  %s\n", decrypted);

                // Demo 3: Full alphabet
                strcpy(plaintext, "The Quick Brown Fox Jumps Over The Lazy Dog");
                key = 13;  // ROT13
                caesarEncrypt(plaintext, ciphertext, key);
                caesarDecrypt(ciphertext, decrypted, key);

                printf("\n[Demo 3: ROT13 (Key=13) - Full alphabet]\n");
                printf("  Plaintext:  %s\n", plaintext);
                printf("  Key:        %d\n", key);
                printf("  Encrypted:  %s\n", ciphertext);
                printf("  Decrypted:  %s\n", decrypted);

                displayShiftTable(13);
                break;

            case 6:
                printf("\nExiting program. Goodbye!\n");
                return 0;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}
