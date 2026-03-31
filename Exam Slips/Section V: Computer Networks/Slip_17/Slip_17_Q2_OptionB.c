/*
 * Slip 17 - Option B: Plain Message to Cipher Message Converter
 * 
 * This program implements the Caesar Cipher encryption algorithm
 * to convert plaintext messages into ciphertext.
 * 
 * Features:
 * - Encrypt plaintext to ciphertext
 * - Decrypt ciphertext back to plaintext
 * - Handles uppercase and lowercase letters
 * - Preserves spaces and special characters
 * - Customizable shift key (1-25)
 * 
 * Compile: gcc Slip_17_Q2_OptionB.c -o cipher
 * Run: ./cipher
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_MESSAGE_LEN 500

// Function to encrypt plaintext using Caesar Cipher
void encrypt(const char *plaintext, char *ciphertext, int key) {
    int i = 0;
    
    // Normalize key to 0-25 range
    key = ((key % 26) + 26) % 26;
    
    while (plaintext[i] != '\0') {
        char ch = plaintext[i];
        
        if (ch >= 'A' && ch <= 'Z') {
            // Encrypt uppercase letter
            ciphertext[i] = ((ch - 'A' + key) % 26) + 'A';
        }
        else if (ch >= 'a' && ch <= 'z') {
            // Encrypt lowercase letter
            ciphertext[i] = ((ch - 'a' + key) % 26) + 'a';
        }
        else {
            // Keep non-alphabetic characters unchanged
            ciphertext[i] = ch;
        }
        i++;
    }
    ciphertext[i] = '\0';  // Null terminate
}

// Function to decrypt ciphertext using Caesar Cipher
void decrypt(const char *ciphertext, char *plaintext, int key) {
    // Decryption is encryption with negative key (or 26 - key)
    int decryptKey = (26 - (key % 26)) % 26;
    encrypt(ciphertext, plaintext, decryptKey);
}

// Function to display the cipher alphabet mapping
void displayCipherAlphabet(int key) {
    printf("\n┌─────────────────────────────────────────────────────────────┐\n");
    printf("│              CIPHER ALPHABET (Key = %2d)                      │\n", key);
    printf("├─────────────────────────────────────────────────────────────┤\n");
    
    printf("│ Plain:  ");
    for (char c = 'A'; c <= 'Z'; c++) {
        printf("%c ", c);
    }
    printf("│\n");
    
    printf("│ Cipher: ");
    for (char c = 'A'; c <= 'Z'; c++) {
        char encrypted = ((c - 'A' + key) % 26) + 'A';
        printf("%c ", encrypted);
    }
    printf("│\n");
    
    printf("└─────────────────────────────────────────────────────────────┘\n");
}

// Function to show step-by-step encryption
void showEncryptionSteps(const char *plaintext, int key) {
    printf("\n📝 STEP-BY-STEP ENCRYPTION:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("Formula: E(x) = (x + key) mod 26\n");
    printf("Key = %d\n\n", key);
    
    printf("%-6s  %-10s  %-15s  %-6s\n", "Char", "Position", "Calculation", "Result");
    printf("━━━━━━  ━━━━━━━━━━  ━━━━━━━━━━━━━━━  ━━━━━━\n");
    
    int count = 0;
    for (int i = 0; plaintext[i] != '\0' && count < 10; i++) {
        char ch = plaintext[i];
        
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            int pos, newPos;
            char base, encrypted;
            
            if (ch >= 'A' && ch <= 'Z') {
                base = 'A';
            } else {
                base = 'a';
            }
            
            pos = ch - base;
            newPos = (pos + key) % 26;
            encrypted = newPos + base;
            
            printf("'%c'     %-10d  (%d + %d) mod 26 = %-2d  '%c'\n", 
                   ch, pos, pos, key, newPos, encrypted);
            count++;
        } else if (ch == ' ') {
            printf("' '     (space)     Unchanged          ' '\n");
            count++;
        }
    }
    
    if (count >= 10) {
        printf("... (showing first 10 characters)\n");
    }
    printf("\n");
}

// Function to display program header
void displayHeader() {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║          CAESAR CIPHER - ENCRYPTION PROGRAM v1.0              ║\n");
    printf("║       Convert Plain Messages to Cipher Messages               ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│ ABOUT CAESAR CIPHER:                                        │\n");
    printf("│ • Named after Julius Caesar who used it for secret messages │\n");
    printf("│ • Each letter is shifted by a fixed number (key) positions  │\n");
    printf("│ • Example: With key=3, A→D, B→E, C→F, ..., Z→C              │\n");
    printf("└─────────────────────────────────────────────────────────────┘\n");
    printf("\n");
}

// Function to display menu
void displayMenu() {
    printf("\n┌─────────────────────────────────────────┐\n");
    printf("│           MENU OPTIONS                   │\n");
    printf("├─────────────────────────────────────────┤\n");
    printf("│  1. Encrypt a message                   │\n");
    printf("│  2. Decrypt a message                   │\n");
    printf("│  3. Show cipher alphabet                │\n");
    printf("│  4. Encrypt with step-by-step details   │\n");
    printf("│  5. Brute force decrypt (try all keys)  │\n");
    printf("│  6. Exit                                │\n");
    printf("└─────────────────────────────────────────┘\n");
    printf("Enter your choice (1-6): ");
}

// Function to brute force decrypt (try all possible keys)
void bruteForceDecrypt(const char *ciphertext) {
    char plaintext[MAX_MESSAGE_LEN];
    
    printf("\n🔓 BRUTE FORCE DECRYPTION - All Possible Keys:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("%-4s  %-50s\n", "Key", "Decrypted Message");
    printf("━━━━  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    for (int key = 1; key <= 25; key++) {
        decrypt(ciphertext, plaintext, key);
        
        // Only show first 45 characters if message is long
        if (strlen(plaintext) > 45) {
            char truncated[50];
            strncpy(truncated, plaintext, 45);
            truncated[45] = '\0';
            printf("%-4d  %s...\n", key, truncated);
        } else {
            printf("%-4d  %s\n", key, plaintext);
        }
    }
    printf("\n💡 Look for the key that produces readable text!\n");
}

int main() {
    char message[MAX_MESSAGE_LEN];
    char result[MAX_MESSAGE_LEN];
    int key;
    int choice;
    
    displayHeader();
    
    do {
        displayMenu();
        scanf("%d", &choice);
        getchar();  // Clear newline from buffer
        
        switch (choice) {
            case 1:  // Encrypt
                printf("\n📥 ENCRYPTION MODE\n");
                printf("━━━━━━━━━━━━━━━━━━\n");
                printf("Enter the plaintext message: ");
                fgets(message, MAX_MESSAGE_LEN, stdin);
                message[strcspn(message, "\n")] = '\0';  // Remove newline
                
                printf("Enter the shift key (1-25): ");
                scanf("%d", &key);
                getchar();
                
                if (key < 1 || key > 25) {
                    printf("⚠️  Invalid key! Using key = %d (normalized)\n", ((key % 26) + 26) % 26);
                }
                
                encrypt(message, result, key);
                
                printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
                printf("║                   ENCRYPTION RESULTS                          ║\n");
                printf("╠═══════════════════════════════════════════════════════════════╣\n");
                printf("║ Plaintext:  %-50s║\n", message);
                printf("║ Key:        %-50d║\n", ((key % 26) + 26) % 26);
                printf("║ Ciphertext: %-50s║\n", result);
                printf("╚═══════════════════════════════════════════════════════════════╝\n");
                break;
                
            case 2:  // Decrypt
                printf("\n📤 DECRYPTION MODE\n");
                printf("━━━━━━━━━━━━━━━━━━\n");
                printf("Enter the ciphertext message: ");
                fgets(message, MAX_MESSAGE_LEN, stdin);
                message[strcspn(message, "\n")] = '\0';
                
                printf("Enter the shift key used for encryption (1-25): ");
                scanf("%d", &key);
                getchar();
                
                decrypt(message, result, key);
                
                printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
                printf("║                   DECRYPTION RESULTS                          ║\n");
                printf("╠═══════════════════════════════════════════════════════════════╣\n");
                printf("║ Ciphertext: %-50s║\n", message);
                printf("║ Key:        %-50d║\n", ((key % 26) + 26) % 26);
                printf("║ Plaintext:  %-50s║\n", result);
                printf("╚═══════════════════════════════════════════════════════════════╝\n");
                break;
                
            case 3:  // Show cipher alphabet
                printf("\nEnter the shift key to display cipher alphabet (1-25): ");
                scanf("%d", &key);
                getchar();
                displayCipherAlphabet(((key % 26) + 26) % 26);
                break;
                
            case 4:  // Encrypt with steps
                printf("\n📝 DETAILED ENCRYPTION MODE\n");
                printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                printf("Enter the plaintext message: ");
                fgets(message, MAX_MESSAGE_LEN, stdin);
                message[strcspn(message, "\n")] = '\0';
                
                printf("Enter the shift key (1-25): ");
                scanf("%d", &key);
                getchar();
                
                key = ((key % 26) + 26) % 26;
                
                displayCipherAlphabet(key);
                showEncryptionSteps(message, key);
                
                encrypt(message, result, key);
                
                printf("╔═══════════════════════════════════════════════════════════════╗\n");
                printf("║                   FINAL RESULT                                ║\n");
                printf("╠═══════════════════════════════════════════════════════════════╣\n");
                printf("║ Plaintext:  %-50s║\n", message);
                printf("║ Ciphertext: %-50s║\n", result);
                printf("╚═══════════════════════════════════════════════════════════════╝\n");
                break;
                
            case 5:  // Brute force
                printf("\n🔓 BRUTE FORCE DECRYPTION MODE\n");
                printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                printf("Enter the ciphertext message: ");
                fgets(message, MAX_MESSAGE_LEN, stdin);
                message[strcspn(message, "\n")] = '\0';
                
                bruteForceDecrypt(message);
                break;
                
            case 6:  // Exit
                printf("\nThank you for using the Caesar Cipher Program!\n");
                printf("🔐 Keep your messages secure!\n\n");
                break;
                
            default:
                printf("\n⚠️  Invalid choice! Please enter a number between 1-6.\n");
        }
        
    } while (choice != 6);
    
    return 0;
}

/*
 * SAMPLE OUTPUT:
 * ==============
 * 
 * ╔═══════════════════════════════════════════════════════════════╗
 * ║          CAESAR CIPHER - ENCRYPTION PROGRAM v1.0              ║
 * ║       Convert Plain Messages to Cipher Messages               ║
 * ╚═══════════════════════════════════════════════════════════════╝
 * 
 * ┌─────────────────────────────────────────┐
 * │           MENU OPTIONS                   │
 * ├─────────────────────────────────────────┤
 * │  1. Encrypt a message                   │
 * │  2. Decrypt a message                   │
 * │  3. Show cipher alphabet                │
 * │  4. Encrypt with step-by-step details   │
 * │  5. Brute force decrypt (try all keys)  │
 * │  6. Exit                                │
 * └─────────────────────────────────────────┘
 * Enter your choice (1-6): 1
 * 
 * 📥 ENCRYPTION MODE
 * ━━━━━━━━━━━━━━━━━━
 * Enter the plaintext message: HELLO WORLD
 * Enter the shift key (1-25): 3
 * 
 * ╔═══════════════════════════════════════════════════════════════╗
 * ║                   ENCRYPTION RESULTS                          ║
 * ╠═══════════════════════════════════════════════════════════════╣
 * ║ Plaintext:  HELLO WORLD                                       ║
 * ║ Key:        3                                                  ║
 * ║ Ciphertext: KHOOR ZRUOG                                       ║
 * ╚═══════════════════════════════════════════════════════════════╝
 * 
 * ---
 * 
 * Enter your choice (1-6): 4
 * 
 * 📝 DETAILED ENCRYPTION MODE
 * ━━━━━━━━━━━━━━━━━━━━━━━━━━━
 * Enter the plaintext message: ATTACK AT DAWN
 * Enter the shift key (1-25): 5
 * 
 * ┌─────────────────────────────────────────────────────────────┐
 * │              CIPHER ALPHABET (Key =  5)                      │
 * ├─────────────────────────────────────────────────────────────┤
 * │ Plain:  A B C D E F G H I J K L M N O P Q R S T U V W X Y Z │
 * │ Cipher: F G H I J K L M N O P Q R S T U V W X Y Z A B C D E │
 * └─────────────────────────────────────────────────────────────┘
 * 
 * 📝 STEP-BY-STEP ENCRYPTION:
 * ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 * Formula: E(x) = (x + key) mod 26
 * Key = 5
 * 
 * Char    Position    Calculation       Result
 * ━━━━━━  ━━━━━━━━━━  ━━━━━━━━━━━━━━━  ━━━━━━
 * 'A'     0           (0 + 5) mod 26 = 5   'F'
 * 'T'     19          (19 + 5) mod 26 = 24 'Y'
 * 'T'     19          (19 + 5) mod 26 = 24 'Y'
 * 'A'     0           (0 + 5) mod 26 = 5   'F'
 * 'C'     2           (2 + 5) mod 26 = 7   'H'
 * 'K'     10          (10 + 5) mod 26 = 15 'P'
 * ' '     (space)     Unchanged          ' '
 * 'A'     0           (0 + 5) mod 26 = 5   'F'
 * 'T'     19          (19 + 5) mod 26 = 24 'Y'
 * ' '     (space)     Unchanged          ' '
 * 
 * ╔═══════════════════════════════════════════════════════════════╗
 * ║                   FINAL RESULT                                ║
 * ╠═══════════════════════════════════════════════════════════════╣
 * ║ Plaintext:  ATTACK AT DAWN                                    ║
 * ║ Ciphertext: FYYFHP FY IFBS                                    ║
 * ╚═══════════════════════════════════════════════════════════════╝
 */
