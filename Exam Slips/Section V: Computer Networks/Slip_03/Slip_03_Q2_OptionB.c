/*
 * Slip 3 - Q2 Option B: Even Parity Error Detection Program
 * 
 * Description: This program implements even parity error detection mechanism
 *              for data transmission in computer networks.
 * 
 * Even Parity:
 * - Add a parity bit so total number of 1s is EVEN
 * - If data has odd 1s, parity bit = 1
 * - If data has even 1s, parity bit = 0
 * 
 * Compile: gcc Slip_03_Q2_OptionB.c -o even_parity
 * Run: ./even_parity
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BITS 16

// Function prototypes
int countOnes(int bits[], int n);
int generateEvenParity(int bits[], int n);
int checkEvenParity(int bits[], int n);
void displayBits(int bits[], int n);
void getBinaryInput(int bits[], int n);
void demonstrateErrorDetection();
void interactiveMode();

int main() {
    int choice;
    
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║         EVEN PARITY ERROR DETECTION PROGRAM              ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    printf("┌─────────────────────────────────────────────────────────┐\n");
    printf("│              EVEN PARITY CONCEPT                        │\n");
    printf("├─────────────────────────────────────────────────────────┤\n");
    printf("│  • Parity bit is added to make total 1s EVEN           │\n");
    printf("│  • Used for error detection in data transmission       │\n");
    printf("│  • Can detect single-bit errors (odd number of errors) │\n");
    printf("│  • Cannot detect even number of bit errors             │\n");
    printf("└─────────────────────────────────────────────────────────┘\n\n");
    
    while (1) {
        printf("\n═══════════════════════════════════════════════════════════\n");
        printf("                      MAIN MENU                             \n");
        printf("═══════════════════════════════════════════════════════════\n");
        printf("  1. Generate Even Parity Bit\n");
        printf("  2. Check Even Parity (Error Detection)\n");
        printf("  3. Demonstrate Error Detection with Examples\n");
        printf("  4. Interactive Transmission Simulation\n");
        printf("  5. Exit\n");
        printf("═══════════════════════════════════════════════════════════\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                // Generate Even Parity
                int n, i;
                int data[MAX_BITS];
                
                printf("\n─────────────────────────────────────────────────────────────\n");
                printf("              GENERATE EVEN PARITY BIT                        \n");
                printf("─────────────────────────────────────────────────────────────\n\n");
                
                printf("Enter number of data bits (1-%d): ", MAX_BITS - 1);
                scanf("%d", &n);
                
                if (n < 1 || n >= MAX_BITS) {
                    printf("Invalid number of bits!\n");
                    break;
                }
                
                printf("Enter %d data bits (0 or 1, space-separated):\n", n);
                getBinaryInput(data, n);
                
                int parityBit = generateEvenParity(data, n);
                int ones = countOnes(data, n);
                
                printf("\n┌─────────────────────────────────────────────────────────┐\n");
                printf("│                    RESULT                               │\n");
                printf("├─────────────────────────────────────────────────────────┤\n");
                printf("│  Original Data:    ");
                displayBits(data, n);
                printf("  │\n");
                printf("│  Number of 1s:     %d (%s)                              │\n", 
                       ones, ones % 2 == 0 ? "even" : "odd");
                printf("│  Parity Bit:       %d                                    │\n", parityBit);
                printf("│  Transmitted Data: ");
                displayBits(data, n);
                printf(" [%d]", parityBit);
                printf("│\n");
                printf("│  Total 1s:         %d (even)                             │\n", ones + parityBit);
                printf("└─────────────────────────────────────────────────────────┘\n");
                break;
            }
            
            case 2: {
                // Check Even Parity
                int n, i;
                int data[MAX_BITS];
                
                printf("\n─────────────────────────────────────────────────────────────\n");
                printf("           CHECK EVEN PARITY (ERROR DETECTION)               \n");
                printf("─────────────────────────────────────────────────────────────\n\n");
                
                printf("Enter total number of bits (including parity bit): ");
                scanf("%d", &n);
                
                if (n < 2 || n > MAX_BITS) {
                    printf("Invalid number of bits!\n");
                    break;
                }
                
                printf("Enter %d bits (data + parity, space-separated):\n", n);
                getBinaryInput(data, n);
                
                int totalOnes = countOnes(data, n);
                int errorDetected = checkEvenParity(data, n);
                
                printf("\n┌─────────────────────────────────────────────────────────┐\n");
                printf("│                    RESULT                               │\n");
                printf("├─────────────────────────────────────────────────────────┤\n");
                printf("│  Received Data:  ");
                displayBits(data, n);
                printf("  │\n");
                printf("│  Total 1s:       %d (%s)                                │\n", 
                       totalOnes, totalOnes % 2 == 0 ? "even" : "odd");
                printf("│                                                         │\n");
                
                if (errorDetected) {
                    printf("│  ╔═════════════════════════════════════════════════╗   │\n");
                    printf("│  ║  ⚠  ERROR DETECTED! (Odd number of 1s)         ║   │\n");
                    printf("│  ║     Data may be corrupted during transmission  ║   │\n");
                    printf("│  ╚═════════════════════════════════════════════════╝   │\n");
                } else {
                    printf("│  ╔═════════════════════════════════════════════════╗   │\n");
                    printf("│  ║  ✓  NO ERROR DETECTED (Even number of 1s)      ║   │\n");
                    printf("│  ║     Data appears to be intact                  ║   │\n");
                    printf("│  ╚═════════════════════════════════════════════════╝   │\n");
                }
                printf("└─────────────────────────────────────────────────────────┘\n");
                break;
            }
            
            case 3:
                demonstrateErrorDetection();
                break;
                
            case 4:
                interactiveMode();
                break;
                
            case 5:
                printf("\nThank you for using Even Parity Error Detection Program!\n\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}

/*
 * Function: countOnes
 * Purpose: Count number of 1s in a binary array
 * Returns: Count of 1s
 */
int countOnes(int bits[], int n) {
    int count = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (bits[i] == 1) {
            count++;
        }
    }
    return count;
}

/*
 * Function: generateEvenParity
 * Purpose: Generate even parity bit for given data
 * Returns: 0 if count of 1s is even, 1 if odd
 */
int generateEvenParity(int bits[], int n) {
    int ones = countOnes(bits, n);
    // If odd number of 1s, parity bit = 1 (to make total even)
    // If even number of 1s, parity bit = 0
    return (ones % 2 == 1) ? 1 : 0;
}

/*
 * Function: checkEvenParity
 * Purpose: Check if received data has even parity
 * Returns: 0 if no error (even 1s), 1 if error detected (odd 1s)
 */
int checkEvenParity(int bits[], int n) {
    int ones = countOnes(bits, n);
    // Error if odd number of 1s
    return (ones % 2 == 1) ? 1 : 0;
}

/*
 * Function: displayBits
 * Purpose: Display binary array
 */
void displayBits(int bits[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", bits[i]);
    }
}

/*
 * Function: getBinaryInput
 * Purpose: Get binary input from user with validation
 */
void getBinaryInput(int bits[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        scanf("%d", &bits[i]);
        // Validate: only 0 or 1
        if (bits[i] != 0 && bits[i] != 1) {
            printf("Warning: Bit %d is not 0 or 1, treating as %d\n", 
                   i + 1, bits[i] != 0 ? 1 : 0);
            bits[i] = (bits[i] != 0) ? 1 : 0;
        }
    }
}

/*
 * Function: demonstrateErrorDetection
 * Purpose: Demonstrate error detection with predefined examples
 */
void demonstrateErrorDetection() {
    printf("\n═══════════════════════════════════════════════════════════\n");
    printf("        EVEN PARITY ERROR DETECTION - DEMONSTRATION         \n");
    printf("═══════════════════════════════════════════════════════════\n\n");
    
    // Example 1: Generating parity
    printf("┌─────────────────────────────────────────────────────────┐\n");
    printf("│ EXAMPLE 1: Generating Even Parity                       │\n");
    printf("├─────────────────────────────────────────────────────────┤\n");
    printf("│                                                         │\n");
    printf("│ Original Data: 1 0 1 1 0 0 1                           │\n");
    printf("│ Count of 1s:   1   2 3     4  →  4 ones (EVEN)         │\n");
    printf("│ Parity Bit:    0 (already even)                        │\n");
    printf("│ Transmitted:   1 0 1 1 0 0 1 [0]                       │\n");
    printf("│                                                         │\n");
    printf("└─────────────────────────────────────────────────────────┘\n\n");
    
    // Example 2: Another generation example
    printf("┌─────────────────────────────────────────────────────────┐\n");
    printf("│ EXAMPLE 2: Generating Even Parity                       │\n");
    printf("├─────────────────────────────────────────────────────────┤\n");
    printf("│                                                         │\n");
    printf("│ Original Data: 1 0 1 0 0 0 1                           │\n");
    printf("│ Count of 1s:   1   2       3  →  3 ones (ODD)          │\n");
    printf("│ Parity Bit:    1 (to make even)                        │\n");
    printf("│ Transmitted:   1 0 1 0 0 0 1 [1]                       │\n");
    printf("│                                                         │\n");
    printf("└─────────────────────────────────────────────────────────┘\n\n");
    
    // Example 3: No error scenario
    printf("┌─────────────────────────────────────────────────────────┐\n");
    printf("│ EXAMPLE 3: Checking Parity - No Error                   │\n");
    printf("├─────────────────────────────────────────────────────────┤\n");
    printf("│                                                         │\n");
    printf("│ Received:    1 0 1 1 0 0 1 0                           │\n");
    printf("│ Count of 1s: 1   2 3     4    →  4 ones (EVEN)         │\n");
    printf("│ Result:      ✓ NO ERROR DETECTED                       │\n");
    printf("│                                                         │\n");
    printf("└─────────────────────────────────────────────────────────┘\n\n");
    
    // Example 4: Error detected scenario
    printf("┌─────────────────────────────────────────────────────────┐\n");
    printf("│ EXAMPLE 4: Checking Parity - Error Detected             │\n");
    printf("├─────────────────────────────────────────────────────────┤\n");
    printf("│                                                         │\n");
    printf("│ Sent:        1 0 1 1 0 0 1 0                           │\n");
    printf("│ Received:    1 0 1 1 0 1 1 0  (bit 6 flipped!)         │\n");
    printf("│                       ↑                                 │\n");
    printf("│                    ERROR                                │\n");
    printf("│ Count of 1s: 1   2 3   4 5    →  5 ones (ODD)          │\n");
    printf("│ Result:      ⚠ ERROR DETECTED!                         │\n");
    printf("│                                                         │\n");
    printf("└─────────────────────────────────────────────────────────┘\n\n");
    
    // Example 5: Limitation - double bit error
    printf("┌─────────────────────────────────────────────────────────┐\n");
    printf("│ EXAMPLE 5: LIMITATION - Double Bit Error (Undetected)   │\n");
    printf("├─────────────────────────────────────────────────────────┤\n");
    printf("│                                                         │\n");
    printf("│ Sent:        1 0 1 1 0 0 1 0                           │\n");
    printf("│ Received:    1 0 0 1 0 1 1 0  (2 bits flipped!)        │\n");
    printf("│                  ↑     ↑                                │\n");
    printf("│                ERRORS                                   │\n");
    printf("│ Count of 1s: 1     2   3 4    →  4 ones (EVEN)         │\n");
    printf("│ Result:      ✓ NO ERROR DETECTED (FALSE NEGATIVE!)     │\n");
    printf("│                                                         │\n");
    printf("│ ⚠ WARNING: Even parity cannot detect even number of    │\n");
    printf("│            bit errors! This is a known limitation.      │\n");
    printf("│                                                         │\n");
    printf("└─────────────────────────────────────────────────────────┘\n\n");
    
    // Summary table
    printf("═══════════════════════════════════════════════════════════\n");
    printf("                    SUMMARY TABLE                          \n");
    printf("═══════════════════════════════════════════════════════════\n");
    printf("┌──────────────────┬───────────────┬──────────────────────┐\n");
    printf("│ Bits Flipped     │ Total 1s      │ Detection Result     │\n");
    printf("├──────────────────┼───────────────┼──────────────────────┤\n");
    printf("│ 0 (no error)     │ Even          │ ✓ Correct (No error) │\n");
    printf("│ 1 (odd errors)   │ Odd           │ ✓ Error Detected     │\n");
    printf("│ 2 (even errors)  │ Even          │ ✗ Missed (False neg) │\n");
    printf("│ 3 (odd errors)   │ Odd           │ ✓ Error Detected     │\n");
    printf("└──────────────────┴───────────────┴──────────────────────┘\n\n");
}

/*
 * Function: interactiveMode
 * Purpose: Simulate data transmission with optional error injection
 */
void interactiveMode() {
    int data[MAX_BITS];
    int transmitted[MAX_BITS];
    int n, i;
    char inject;
    int errorPos;
    
    printf("\n═══════════════════════════════════════════════════════════\n");
    printf("        INTERACTIVE TRANSMISSION SIMULATION                 \n");
    printf("═══════════════════════════════════════════════════════════\n\n");
    
    printf("Enter number of data bits (1-%d): ", MAX_BITS - 1);
    scanf("%d", &n);
    
    if (n < 1 || n >= MAX_BITS) {
        printf("Invalid number of bits!\n");
        return;
    }
    
    printf("Enter %d data bits (space-separated): ", n);
    getBinaryInput(data, n);
    
    // Generate parity
    int parityBit = generateEvenParity(data, n);
    
    // Copy data + parity to transmitted array
    for (i = 0; i < n; i++) {
        transmitted[i] = data[i];
    }
    transmitted[n] = parityBit;
    
    printf("\n─────────────────────────────────────────────────────────────\n");
    printf("                     SENDER SIDE                             \n");
    printf("─────────────────────────────────────────────────────────────\n");
    printf("Original Data:     ");
    displayBits(data, n);
    printf("\n");
    printf("Generated Parity:  %d\n", parityBit);
    printf("Data to Transmit:  ");
    displayBits(transmitted, n + 1);
    printf("\n");
    
    // Ask if user wants to simulate error
    printf("\n─────────────────────────────────────────────────────────────\n");
    printf("                  TRANSMISSION CHANNEL                       \n");
    printf("─────────────────────────────────────────────────────────────\n");
    printf("Simulate transmission error? (y/n): ");
    scanf(" %c", &inject);
    
    if (inject == 'y' || inject == 'Y') {
        printf("Enter bit position to flip (1 to %d): ", n + 1);
        scanf("%d", &errorPos);
        
        if (errorPos >= 1 && errorPos <= n + 1) {
            transmitted[errorPos - 1] = 1 - transmitted[errorPos - 1];  // Flip bit
            printf("Bit %d flipped: %d → %d\n", errorPos, 
                   1 - transmitted[errorPos - 1], transmitted[errorPos - 1]);
        } else {
            printf("Invalid position! No error injected.\n");
        }
    }
    
    printf("\n─────────────────────────────────────────────────────────────\n");
    printf("                     RECEIVER SIDE                           \n");
    printf("─────────────────────────────────────────────────────────────\n");
    printf("Received Data:     ");
    displayBits(transmitted, n + 1);
    printf("\n");
    
    int totalOnes = countOnes(transmitted, n + 1);
    int errorDetected = checkEvenParity(transmitted, n + 1);
    
    printf("Count of 1s:       %d (%s)\n", totalOnes, 
           totalOnes % 2 == 0 ? "even" : "odd");
    
    printf("\n");
    if (errorDetected) {
        printf("╔═════════════════════════════════════════════════════════╗\n");
        printf("║  ⚠  ERROR DETECTED!                                     ║\n");
        printf("║  The received data has been corrupted.                  ║\n");
        printf("║  Request retransmission from sender.                    ║\n");
        printf("╚═════════════════════════════════════════════════════════╝\n");
    } else {
        printf("╔═════════════════════════════════════════════════════════╗\n");
        printf("║  ✓  NO ERROR DETECTED                                   ║\n");
        printf("║  Data appears to be intact.                             ║\n");
        printf("║  Proceed with data processing.                          ║\n");
        printf("╚═════════════════════════════════════════════════════════╝\n");
        
        if (inject == 'y' || inject == 'Y') {
            printf("\n⚠ Note: If an error was injected and not detected,\n");
            printf("  it demonstrates the limitation of even parity.\n");
        }
    }
}

/*
 * Sample Output:
 * 
 * ╔══════════════════════════════════════════════════════════╗
 * ║         EVEN PARITY ERROR DETECTION PROGRAM              ║
 * ╚══════════════════════════════════════════════════════════╝
 * 
 * ═══════════════════════════════════════════════════════════
 *                       MAIN MENU                             
 * ═══════════════════════════════════════════════════════════
 *   1. Generate Even Parity Bit
 *   2. Check Even Parity (Error Detection)
 *   3. Demonstrate Error Detection with Examples
 *   4. Interactive Transmission Simulation
 *   5. Exit
 * ═══════════════════════════════════════════════════════════
 * Enter your choice: 1
 * 
 * Enter number of data bits (1-15): 7
 * Enter 7 data bits (0 or 1, space-separated):
 * 1 0 1 1 0 0 1
 * 
 * ┌─────────────────────────────────────────────────────────┐
 * │                    RESULT                               │
 * ├─────────────────────────────────────────────────────────┤
 * │  Original Data:    1 0 1 1 0 0 1                       │
 * │  Number of 1s:     4 (even)                            │
 * │  Parity Bit:       0                                    │
 * │  Transmitted Data: 1 0 1 1 0 0 1 [0]                   │
 * │  Total 1s:         4 (even)                             │
 * └─────────────────────────────────────────────────────────┘
 */
