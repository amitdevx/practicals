/*
 * Slip 5 - Q2 Option B: Odd Parity Error Detection Program
 * Computer Networks
 * 
 * Description: Implements odd parity bit generation and error detection
 *              - Sender: Calculates and appends odd parity bit
 *              - Receiver: Verifies parity and detects single-bit errors
 * 
 * Odd Parity Rule: Total number of 1s (including parity bit) should be ODD
 * 
 * Compile: gcc -o odd_parity Slip_05_Q2_OptionB.c
 * Run:     ./odd_parity
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA_SIZE 32

// Count number of 1s in binary data
int countOnes(int data[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (data[i] == 1) {
            count++;
        }
    }
    return count;
}

// Calculate odd parity bit for given data
int calculateOddParityBit(int data[], int size) {
    int ones = countOnes(data, size);
    // If even number of 1s, parity bit = 1 (to make total odd)
    // If odd number of 1s, parity bit = 0 (already odd)
    return (ones % 2 == 0) ? 1 : 0;
}

// Display binary data
void displayData(int data[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d", data[i]);
        if ((i + 1) % 4 == 0 && i != size - 1) {
            printf(" ");
        }
    }
}

// Sender side: Add parity bit to data
void senderSide() {
    int data[MAX_DATA_SIZE];
    int size;
    char input[MAX_DATA_SIZE + 1];
    
    
    printf("Enter binary data (e.g., 1010011): ");
    scanf("%s", input);
    
    // Validate and convert input
    size = strlen(input);
    if (size > MAX_DATA_SIZE - 1) {
        printf("Error: Data too long! Maximum %d bits allowed.\n", MAX_DATA_SIZE - 1);
        return;
    }
    
    int valid = 1;
    for (int i = 0; i < size; i++) {
        if (input[i] != '0' && input[i] != '1') {
            valid = 0;
            break;
        }
        data[i] = input[i] - '0';
    }
    
    if (!valid) {
        printf("Error: Invalid input! Only 0s and 1s allowed.\n");
        return;
    }
    
    // Calculate parity
    int ones = countOnes(data, size);
    int parityBit = calculateOddParityBit(data, size);
    
    // Display results
    printf("\n┌────────────────────────────────────────────────┐\n");
    printf("│              TRANSMISSION DETAILS              │\n");
    printf("├────────────────────────────────────────────────┤\n");
    printf("│ Original Data:       ");
    displayData(data, size);
    printf("%*s│\n", 26 - size - (size/4), "");
    printf("│ Number of bits:      %-25d │\n", size);
    printf("│ Count of 1s:         %-25d │\n", ones);
    printf("│ 1s count is:         %-25s │\n", ones % 2 == 0 ? "EVEN" : "ODD");
    printf("│ Odd Parity Bit:      %-25d │\n", parityBit);
    printf("├────────────────────────────────────────────────┤\n");
    printf("│ Data + Parity Bit:   ");
    displayData(data, size);
    printf(" | %d", parityBit);
    printf("%*s│\n", 21 - size - (size/4), "");
    printf("│ Total 1s (with parity): %-22d │\n", ones + parityBit);
    printf("│ Total is ODD:        %-25s │\n", 
           (ones + parityBit) % 2 == 1 ? "✓ YES (Valid)" : "✗ NO (Invalid)");
    printf("└────────────────────────────────────────────────┘\n");
    
    // Show transmitted frame
    printf("\n  ➜ Transmitted Frame: ");
    displayData(data, size);
    printf("%d\n", parityBit);
    printf("                       ");
    for (int i = 0; i < size; i++) printf("-");
    printf("-\n");
    printf("                       ");
    for (int i = 0; i < size; i++) printf("D");
    printf("P\n");
    printf("                       (D=Data, P=Parity)\n");
}

// Receiver side: Check parity and detect errors
void receiverSide() {
    int received[MAX_DATA_SIZE + 1];
    int size;
    char input[MAX_DATA_SIZE + 2];
    
    
    printf("Enter received data (including parity bit): ");
    scanf("%s", input);
    
    // Validate and convert input
    size = strlen(input);
    if (size < 2) {
        printf("Error: Need at least 1 data bit + 1 parity bit!\n");
        return;
    }
    
    int valid = 1;
    for (int i = 0; i < size; i++) {
        if (input[i] != '0' && input[i] != '1') {
            valid = 0;
            break;
        }
        received[i] = input[i] - '0';
    }
    
    if (!valid) {
        printf("Error: Invalid input! Only 0s and 1s allowed.\n");
        return;
    }
    
    // Check parity
    int totalOnes = countOnes(received, size);
    int parityOK = (totalOnes % 2 == 1);  // Should be odd for odd parity
    
    // Display results
    printf("\n┌────────────────────────────────────────────────┐\n");
    printf("│              VERIFICATION RESULTS              │\n");
    printf("├────────────────────────────────────────────────┤\n");
    printf("│ Received Data:       ");
    displayData(received, size - 1);
    printf("%*s│\n", 26 - (size-1) - ((size-1)/4), "");
    printf("│ Received Parity:     %-25d │\n", received[size - 1]);
    printf("│ Total bits received: %-25d │\n", size);
    printf("│ Count of all 1s:     %-25d │\n", totalOnes);
    printf("│ 1s count is:         %-25s │\n", totalOnes % 2 == 1 ? "ODD" : "EVEN");
    printf("├────────────────────────────────────────────────┤\n");
    
    if (parityOK) {
        printf("│ ✓ STATUS: NO ERROR DETECTED                   │\n");
        printf("│   Data appears to be received correctly       │\n");
    } else {
        printf("│ ✗ STATUS: ERROR DETECTED!                     │\n");
        printf("│   Data has been corrupted during transmission │\n");
    }
    printf("└────────────────────────────────────────────────┘\n");
    
    // Additional info
    printf("\n  Note: Odd parity can only detect ODD number of bit errors.\n");
    printf("        Even number of errors (2, 4, 6...) cannot be detected.\n");
}

// Simulate transmission with error injection
void simulateWithError() {
    int data[MAX_DATA_SIZE];
    int transmitted[MAX_DATA_SIZE + 1];
    int size;
    char input[MAX_DATA_SIZE + 1];
    
    
    printf("Enter original binary data: ");
    scanf("%s", input);
    
    size = strlen(input);
    for (int i = 0; i < size; i++) {
        data[i] = input[i] - '0';
        transmitted[i] = data[i];
    }
    
    // Calculate and append parity
    int parityBit = calculateOddParityBit(data, size);
    transmitted[size] = parityBit;
    int transmittedSize = size + 1;
    
    printf("\n  Original Data:     ");
    displayData(data, size);
    printf("\n  Parity Bit:        %d\n", parityBit);
    printf("  Transmitted:       ");
    displayData(transmitted, transmittedSize);
    printf("\n");
    
    // Ask for error injection
    int errorCount;
    printf("\n  How many bit errors to inject? (0-3): ");
    scanf("%d", &errorCount);
    
    if (errorCount > transmittedSize) errorCount = transmittedSize;
    
    printf("\n  Injecting errors...\n");
    for (int i = 0; i < errorCount; i++) {
        int pos;
        printf("  Enter bit position to flip (0 to %d): ", transmittedSize - 1);
        scanf("%d", &pos);
        if (pos >= 0 && pos < transmittedSize) {
            transmitted[pos] = 1 - transmitted[pos];  // Flip the bit
            printf("    Bit %d flipped: %d → %d\n", pos, 1 - transmitted[pos], transmitted[pos]);
        }
    }
    
    // Show received data
    printf("\n  Received Data:     ");
    displayData(transmitted, transmittedSize);
    printf("\n");
    
    // Check parity
    int totalOnes = countOnes(transmitted, transmittedSize);
    int parityOK = (totalOnes % 2 == 1);
    
    printf("\n┌────────────────────────────────────────────────┐\n");
    printf("│              DETECTION RESULT                  │\n");
    printf("├────────────────────────────────────────────────┤\n");
    printf("│ Errors injected:     %-25d │\n", errorCount);
    printf("│ Total 1s in received:%-25d │\n", totalOnes);
    printf("│ Parity check:        %-25s │\n", parityOK ? "PASSED (ODD)" : "FAILED (EVEN)");
    printf("├────────────────────────────────────────────────┤\n");
    
    if (errorCount == 0) {
        printf("│ ✓ No errors - Correctly detected as valid     │\n");
    } else if (errorCount % 2 == 1) {
        // Odd number of errors
        if (!parityOK) {
            printf("│ ✓ Odd error(s) - Correctly DETECTED!          │\n");
        } else {
            printf("│ ✗ Detection FAILED (unexpected)               │\n");
        }
    } else {
        // Even number of errors
        if (parityOK) {
            printf("│ ⚠ Even error(s) - UNDETECTED! (Limitation)    │\n");
            printf("│   Parity check cannot detect even # of errors │\n");
        } else {
            printf("│ ✗ Detection behavior unexpected               │\n");
        }
    }
    printf("└────────────────────────────────────────────────┘\n");
}

// Display educational information about parity
void displayInfo() {
    
    printf("  WHAT IS ODD PARITY?\n");
    printf("  ───────────────────\n");
    printf("  A parity bit is added to data so that the total number of\n");
    printf("  1-bits (including the parity bit) is always ODD.\n\n");
    
    printf("  HOW IT WORKS:\n");
    printf("  ─────────────\n");
    printf("  ┌──────────────────────────────────────────────────────┐\n");
    printf("  │ Data        │ Count of 1s │ Parity Bit │ Total 1s   │\n");
    printf("  ├──────────────────────────────────────────────────────┤\n");
    printf("  │ 1010001     │ 3 (odd)     │ 0          │ 3 (odd) ✓  │\n");
    printf("  │ 1010101     │ 4 (even)    │ 1          │ 5 (odd) ✓  │\n");
    printf("  │ 1111111     │ 7 (odd)     │ 0          │ 7 (odd) ✓  │\n");
    printf("  │ 0000000     │ 0 (even)    │ 1          │ 1 (odd) ✓  │\n");
    printf("  └──────────────────────────────────────────────────────┘\n\n");
    
    printf("  ERROR DETECTION:\n");
    printf("  ────────────────\n");
    printf("  At receiver: Count all 1s including parity bit\n");
    printf("    • If count is ODD → No error detected ✓\n");
    printf("    • If count is EVEN → Error detected! ✗\n\n");
    
    printf("  LIMITATIONS:\n");
    printf("  ────────────\n");
    printf("  ┌──────────────────────────────────────────────────────┐\n");
    printf("  │ # of Errors │ Detection │ Reason                    │\n");
    printf("  ├──────────────────────────────────────────────────────┤\n");
    printf("  │ 1 (odd)     │ ✓ Yes     │ Changes odd/even count    │\n");
    printf("  │ 2 (even)    │ ✗ No      │ Two flips cancel out      │\n");
    printf("  │ 3 (odd)     │ ✓ Yes     │ Net effect: 1 flip        │\n");
    printf("  │ 4 (even)    │ ✗ No      │ Four flips cancel out     │\n");
    printf("  └──────────────────────────────────────────────────────┘\n\n");
    
    printf("  KEY POINTS:\n");
    printf("  ───────────\n");
    printf("  • Simple and fast to implement\n");
    printf("  • Detects all single-bit errors\n");
    printf("  • Cannot detect even number of errors\n");
    printf("  • Cannot correct errors (only detect)\n");
    printf("  • Used in UART, memory systems, simple protocols\n");
}

// Compare odd vs even parity
void compareParities() {
    char input[MAX_DATA_SIZE + 1];
    int data[MAX_DATA_SIZE];
    int size;
    
    
    printf("Enter binary data: ");
    scanf("%s", input);
    
    size = strlen(input);
    for (int i = 0; i < size; i++) {
        data[i] = input[i] - '0';
    }
    
    int ones = countOnes(data, size);
    int oddParity = (ones % 2 == 0) ? 1 : 0;   // Make total ODD
    int evenParity = (ones % 2 == 0) ? 0 : 1;  // Make total EVEN
    
    printf("\n┌────────────────────────────────────────────────┐\n");
    printf("│              PARITY COMPARISON                 │\n");
    printf("├────────────────────────────────────────────────┤\n");
    printf("│ Data:                ");
    displayData(data, size);
    printf("%*s│\n", 26 - size - (size/4), "");
    printf("│ Count of 1s:         %-25d │\n", ones);
    printf("├────────────────────────────────────────────────┤\n");
    printf("│ ODD Parity Bit:      %-25d │\n", oddParity);
    printf("│ With ODD parity:     ");
    displayData(data, size);
    printf("%d", oddParity);
    printf("%*s│\n", 24 - size - (size/4), "");
    printf("│ Total 1s (odd):      %-25d │\n", ones + oddParity);
    printf("├────────────────────────────────────────────────┤\n");
    printf("│ EVEN Parity Bit:     %-25d │\n", evenParity);
    printf("│ With EVEN parity:    ");
    displayData(data, size);
    printf("%d", evenParity);
    printf("%*s│\n", 24 - size - (size/4), "");
    printf("│ Total 1s (even):     %-25d │\n", ones + evenParity);
    printf("└────────────────────────────────────────────────┘\n");
}

// Display menu
void displayMenu() {
    printf("Enter your choice: ");
}

int main() {
    int choice;
    
    printf("\n");
    
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                senderSide();
                break;
            case 2:
                receiverSide();
                break;
            case 3:
                simulateWithError();
                break;
            case 4:
                compareParities();
                break;
            case 5:
                displayInfo();
                break;
            case 6:
                printf("\nExiting Odd Parity Program...\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    } while (choice != 6);
    
    return 0;
}

/*
 * SAMPLE OUTPUT:
 * ==============
 * 
 * ╔══════════════════════════════════════════════════════╗
 * ║     ODD PARITY ERROR DETECTION PROGRAM               ║
 * ║     Computer Networks - Slip 5                       ║
 * ╚══════════════════════════════════════════════════════╝
 * 
 * Enter your choice: 1
 * 
 * ╔════════════════════════════════════════════════════╗
 * ║              SENDER SIDE                           ║
 * ╚════════════════════════════════════════════════════╝
 * 
 * Enter binary data (e.g., 1010011): 1010011
 * 
 * ┌────────────────────────────────────────────────────┐
 * │              TRANSMISSION DETAILS                  │
 * ├────────────────────────────────────────────────────┤
 * │ Original Data:       1010 011                      │
 * │ Number of bits:      7                             │
 * │ Count of 1s:         4                             │
 * │ 1s count is:         EVEN                          │
 * │ Odd Parity Bit:      1                             │
 * ├────────────────────────────────────────────────────┤
 * │ Data + Parity Bit:   1010 011 | 1                  │
 * │ Total 1s (with parity): 5                          │
 * │ Total is ODD:        ✓ YES (Valid)                 │
 * └────────────────────────────────────────────────────┘
 * 
 *   ➜ Transmitted Frame: 1010 0111
 * 
 * Enter your choice: 2
 * 
 * ╔════════════════════════════════════════════════════╗
 * ║             RECEIVER SIDE                          ║
 * ╚════════════════════════════════════════════════════╝
 * 
 * Enter received data (including parity bit): 10100111
 * 
 * ┌────────────────────────────────────────────────────┐
 * │              VERIFICATION RESULTS                  │
 * ├────────────────────────────────────────────────────┤
 * │ Received Data:       1010 011                      │
 * │ Received Parity:     1                             │
 * │ Total bits received: 8                             │
 * │ Count of all 1s:     5                             │
 * │ 1s count is:         ODD                           │
 * ├────────────────────────────────────────────────────┤
 * │ ✓ STATUS: NO ERROR DETECTED                        │
 * │   Data appears to be received correctly            │
 * └────────────────────────────────────────────────────┘
 * 
 * Enter your choice: 2
 * Enter received data (including parity bit): 10100011
 * 
 * ┌────────────────────────────────────────────────────┐
 * │              VERIFICATION RESULTS                  │
 * ├────────────────────────────────────────────────────┤
 * │ Received Data:       1010 001                      │
 * │ Received Parity:     1                             │
 * │ Total bits received: 8                             │
 * │ Count of all 1s:     4                             │
 * │ 1s count is:         EVEN                          │
 * ├────────────────────────────────────────────────────┤
 * │ ✗ STATUS: ERROR DETECTED!                          │
 * │   Data has been corrupted during transmission      │
 * └────────────────────────────────────────────────────┘
 */
