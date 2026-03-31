/*
 * Slip 1 - Q2 Option A: Data Link Layer Framing
 * Character Stuffing and Bit Stuffing Implementation
 * 
 * Compile: gcc Slip_01_Q2_OptionA.c -o framing
 * Run: ./framing
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 256

/* ==================== CHARACTER STUFFING ==================== */

/*
 * Character Stuffing:
 * - Frame delimiters: DLE STX (start) and DLE ETX (end)
 * - If data contains DLE, insert extra DLE before it
 * - DLE = Data Link Escape, STX = Start of Text, ETX = End of Text
 */

void characterStuffing(char data[], char stuffed[]) {
    int i, j = 0;
    
    // Add start delimiter: DLE STX
    stuffed[j++] = 'D';
    stuffed[j++] = 'L';
    stuffed[j++] = 'E';
    stuffed[j++] = ' ';
    stuffed[j++] = 'S';
    stuffed[j++] = 'T';
    stuffed[j++] = 'X';
    stuffed[j++] = ' ';
    
    // Process each character in data
    for (i = 0; data[i] != '\0'; i++) {
        // Check for DLE in data (simplified: check for 'D' as DLE marker)
        if (data[i] == 'D' && data[i+1] == 'L' && data[i+2] == 'E') {
            // Stuff extra DLE
            stuffed[j++] = 'D';
            stuffed[j++] = 'L';
            stuffed[j++] = 'E';
            stuffed[j++] = ' ';
            stuffed[j++] = 'D';
            stuffed[j++] = 'L';
            stuffed[j++] = 'E';
            stuffed[j++] = ' ';
            i += 2; // Skip "LE" as we've processed "DLE"
        } else {
            stuffed[j++] = data[i];
            if (data[i] != ' ' && data[i+1] != '\0') {
                stuffed[j++] = ' ';
            }
        }
    }
    
    // Add end delimiter: DLE ETX
    if (stuffed[j-1] != ' ') stuffed[j++] = ' ';
    stuffed[j++] = 'D';
    stuffed[j++] = 'L';
    stuffed[j++] = 'E';
    stuffed[j++] = ' ';
    stuffed[j++] = 'E';
    stuffed[j++] = 'T';
    stuffed[j++] = 'X';
    stuffed[j] = '\0';
}

void characterDestuffing(char stuffed[], char destuffed[]) {
    int i, j = 0;
    int len = strlen(stuffed);
    int dataStart = 0, dataEnd = len;
    
    // Find start of data (after "DLE STX ")
    for (i = 0; i < len - 7; i++) {
        if (strncmp(&stuffed[i], "DLE STX", 7) == 0) {
            dataStart = i + 8;
            break;
        }
    }
    
    // Find end of data (before " DLE ETX")
    for (i = len - 1; i >= 7; i--) {
        if (strncmp(&stuffed[i-6], "DLE ETX", 7) == 0) {
            dataEnd = i - 7;
            break;
        }
    }
    
    // Process data between delimiters
    for (i = dataStart; i <= dataEnd && stuffed[i] != '\0'; i++) {
        // Check for stuffed DLE (DLE DLE)
        if (strncmp(&stuffed[i], "DLE DLE", 7) == 0) {
            destuffed[j++] = 'D';
            destuffed[j++] = 'L';
            destuffed[j++] = 'E';
            i += 7; // Skip "DLE DLE"
        } else if (stuffed[i] != ' ') {
            destuffed[j++] = stuffed[i];
        }
    }
    destuffed[j] = '\0';
}

/* ==================== BIT STUFFING ==================== */

/*
 * Bit Stuffing:
 * - Frame flag: 01111110
 * - After 5 consecutive 1s in data, insert a 0
 * - Prevents data from mimicking the flag pattern
 */

void bitStuffing(char data[], char stuffed[]) {
    int i, j = 0;
    int oneCount = 0;
    
    // Add start flag: 01111110
    strcpy(stuffed, "01111110");
    j = 8;
    
    // Process each bit in data
    for (i = 0; data[i] != '\0'; i++) {
        if (data[i] == '1') {
            stuffed[j++] = '1';
            oneCount++;
            
            // After 5 consecutive 1s, stuff a 0
            if (oneCount == 5) {
                stuffed[j++] = '0';
                oneCount = 0;
            }
        } else if (data[i] == '0') {
            stuffed[j++] = '0';
            oneCount = 0;
        }
        // Ignore spaces and other characters
    }
    
    // Add end flag: 01111110
    strcpy(&stuffed[j], "01111110");
    j += 8;
    stuffed[j] = '\0';
}

void bitDestuffing(char stuffed[], char destuffed[]) {
    int i, j = 0;
    int oneCount = 0;
    int len = strlen(stuffed);
    
    // Skip start flag (first 8 bits) and end flag (last 8 bits)
    for (i = 8; i < len - 8; i++) {
        if (stuffed[i] == '1') {
            destuffed[j++] = '1';
            oneCount++;
            
            // After 5 consecutive 1s, skip the stuffed 0
            if (oneCount == 5) {
                i++; // Skip the stuffed '0'
                oneCount = 0;
            }
        } else if (stuffed[i] == '0') {
            destuffed[j++] = '0';
            oneCount = 0;
        }
    }
    destuffed[j] = '\0';
}

/* ==================== DISPLAY FUNCTIONS ==================== */

void printSeparator() {
    printf("\n========================================\n");
}

void displayCharacterStuffingDemo() {
    char data[MAX_SIZE], stuffed[MAX_SIZE * 2], destuffed[MAX_SIZE];
    
    printSeparator();
    printf("       CHARACTER STUFFING DEMO\n");
    printSeparator();
    
    printf("\nEnter data (use 'DLE' where needed): ");
    fgets(data, MAX_SIZE, stdin);
    data[strcspn(data, "\n")] = '\0'; // Remove newline
    
    printf("\n--- Original Data ---\n");
    printf("Data: %s\n", data);
    
    characterStuffing(data, stuffed);
    printf("\n--- After Character Stuffing ---\n");
    printf("Frame: %s\n", stuffed);
    
    characterDestuffing(stuffed, destuffed);
    printf("\n--- After Character Destuffing ---\n");
    printf("Data: %s\n", destuffed);
}

void displayBitStuffingDemo() {
    char data[MAX_SIZE], stuffed[MAX_SIZE * 2], destuffed[MAX_SIZE];
    
    printSeparator();
    printf("         BIT STUFFING DEMO\n");
    printSeparator();
    
    printf("\nEnter binary data (0s and 1s only): ");
    fgets(data, MAX_SIZE, stdin);
    data[strcspn(data, "\n")] = '\0';
    
    printf("\n--- Original Data ---\n");
    printf("Data: %s\n", data);
    
    bitStuffing(data, stuffed);
    printf("\n--- After Bit Stuffing ---\n");
    printf("Frame: %s\n", stuffed);
    printf("       ");
    // Mark the flags
    printf("^^^^^^^^");
    for (int i = 8; i < strlen(stuffed) - 8; i++) printf(" ");
    printf("^^^^^^^^\n");
    printf("       Start    Data (with stuffed bits)     End\n");
    printf("       Flag                                  Flag\n");
    
    bitDestuffing(stuffed, destuffed);
    printf("\n--- After Bit Destuffing ---\n");
    printf("Data: %s\n", destuffed);
}

void displayPredefinedExamples() {
    char stuffed[MAX_SIZE * 2], destuffed[MAX_SIZE];
    
    printSeparator();
    printf("       PREDEFINED EXAMPLES\n");
    printSeparator();
    
    // Character Stuffing Example
    printf("\n=== Character Stuffing Example ===\n");
    char charData[] = "HELLO DLE WORLD";
    printf("Original: %s\n", charData);
    characterStuffing(charData, stuffed);
    printf("Stuffed:  %s\n", stuffed);
    characterDestuffing(stuffed, destuffed);
    printf("Destuffed: %s\n", destuffed);
    
    // Bit Stuffing Example
    printf("\n=== Bit Stuffing Example ===\n");
    char bitData[] = "01111111100";
    printf("Original: %s\n", bitData);
    printf("          01111|11|1100\n");
    printf("               ^5 consecutive 1s, stuff 0 after\n");
    
    bitStuffing(bitData, stuffed);
    printf("Stuffed:  %s\n", stuffed);
    printf("          01111110|011111|0|1|0|1100|01111110\n");
    printf("          ^^^^^^^^ flag   ^ stuffed bit  ^^^^^^^^ flag\n");
    
    bitDestuffing(stuffed, destuffed);
    printf("Destuffed: %s\n", destuffed);
    
    // Another bit stuffing example
    printf("\n=== Bit Stuffing Example 2 ===\n");
    char bitData2[] = "1111110111111";
    printf("Original: %s\n", bitData2);
    bitStuffing(bitData2, stuffed);
    printf("Stuffed:  %s\n", stuffed);
    bitDestuffing(stuffed, destuffed);
    printf("Destuffed: %s\n", destuffed);
}

/* ==================== MAIN FUNCTION ==================== */

int main() {
    int choice;
    
    printf("\n╔══════════════════════════════════════════╗\n");
    printf("║   DATA LINK LAYER FRAMING METHODS        ║\n");
    printf("║   Character Stuffing & Bit Stuffing      ║\n");
    printf("╚══════════════════════════════════════════╝\n");
    
    while (1) {
        printf("\n┌──────────────────────────────────────┐\n");
        printf("│            MAIN MENU                 │\n");
        printf("├──────────────────────────────────────┤\n");
        printf("│  1. Character Stuffing Demo          │\n");
        printf("│  2. Bit Stuffing Demo                │\n");
        printf("│  3. Show Predefined Examples         │\n");
        printf("│  4. Exit                             │\n");
        printf("└──────────────────────────────────────┘\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline
        
        switch (choice) {
            case 1:
                displayCharacterStuffingDemo();
                break;
            case 2:
                displayBitStuffingDemo();
                break;
            case 3:
                displayPredefinedExamples();
                break;
            case 4:
                printf("\nExiting program. Goodbye!\n");
                return 0;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
    
    return 0;
}

/*
 * ==================== EXPLANATION ====================
 * 
 * CHARACTER STUFFING:
 * - Used in byte-oriented protocols (like BISYNC)
 * - Frame format: DLE STX <data> DLE ETX
 * - If data contains DLE, insert an extra DLE before it
 * - Receiver removes extra DLE during destuffing
 * 
 * Example:
 *   Data:    A B DLE C D
 *   Stuffed: DLE STX A B DLE DLE C D DLE ETX
 *                        ^^^^^^^^ doubled
 * 
 * BIT STUFFING:
 * - Used in bit-oriented protocols (like HDLC)
 * - Frame flag: 01111110 (marks start and end)
 * - After 5 consecutive 1s in data, insert a 0
 * - Prevents data from containing the flag pattern
 * 
 * Example:
 *   Data:    01111111100
 *            5 ones + more
 *   Stuffed: 01111110 + 011111|0|1|0|1100 + 01111110
 *                            ^ stuffed 0
 * 
 * TIME COMPLEXITY: O(n) where n is input length
 * SPACE COMPLEXITY: O(n) for the output buffer
 *                   Worst case doubles the size
 */
