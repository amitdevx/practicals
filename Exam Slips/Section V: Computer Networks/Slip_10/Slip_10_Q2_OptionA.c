/*
 * Slip 10 - Q2 Option A: Even Parity Error Detection
 * 
 * CONCEPT:
 * --------
 * Parity bit is a simple error detection mechanism that adds an extra bit
 * to data to make the total number of 1s either even (even parity) or 
 * odd (odd parity).
 * 
 * EVEN PARITY: Total number of 1s (including parity bit) should be EVEN
 * - If data has odd number of 1s  -> parity bit = 1
 * - If data has even number of 1s -> parity bit = 0
 * 
 * ALGORITHM:
 * ----------
 * Sender Side:
 * 1. Count number of 1s in data
 * 2. If count is odd, set parity bit = 1
 * 3. If count is even, set parity bit = 0
 * 4. Append parity bit to data
 * 
 * Receiver Side:
 * 1. Count total number of 1s (data + parity)
 * 2. If count is even -> No error detected
 * 3. If count is odd  -> Error detected
 * 
 * LIMITATIONS:
 * - Cannot detect even number of bit errors
 * - Cannot correct errors
 * - Cannot detect which bit is erroneous
 * 
 * EXAMPLE:
 * Data: 1011001 (4 ones - even)
 * Parity bit: 0
 * Transmitted: 10110010
 * 
 * Data: 1011101 (5 ones - odd)
 * Parity bit: 1
 * Transmitted: 10111011
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BITS 64

// Function prototypes
int countOnes(const char *bits, int length);
void generateParityBit(const char *data, char *dataWithParity);
int checkParity(const char *receivedData);
void simulateTransmission(const char *data, int introduceError, int errorPosition);
void demonstrateParityMatrix(void);
int validateBinaryInput(const char *input);

/*
 * Count the number of 1s in a binary string
 */
int countOnes(const char *bits, int length) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (bits[i] == '1') {
            count++;
        }
    }
    return count;
}

/*
 * Generate parity bit and append to data
 * For even parity: parity bit makes total 1s even
 */
void generateParityBit(const char *data, char *dataWithParity) {
    int length = strlen(data);
    int ones = countOnes(data, length);
    
    // Copy original data
    strcpy(dataWithParity, data);
    
    // Calculate and append parity bit
    // If ones is odd, parity = 1 (to make total even)
    // If ones is even, parity = 0 (already even)
    if (ones % 2 == 1) {
        dataWithParity[length] = '1';  // Odd ones, add 1
    } else {
        dataWithParity[length] = '0';  // Even ones, add 0
    }
    dataWithParity[length + 1] = '\0';
    
    printf("\n=== SENDER SIDE ===\n");
    printf("Original Data    : %s\n", data);
    printf("Number of 1s     : %d (%s)\n", ones, (ones % 2 == 0) ? "Even" : "Odd");
    printf("Parity Bit (Even): %c\n", dataWithParity[length]);
    printf("Transmitted Data : %s\n", dataWithParity);
    printf("Total 1s now     : %d (Even)\n", countOnes(dataWithParity, length + 1));
}

/*
 * Check if received data has valid even parity
 * Returns: 0 = No error, 1 = Error detected
 */
int checkParity(const char *receivedData) {
    int length = strlen(receivedData);
    int ones = countOnes(receivedData, length);
    
    printf("\n=== RECEIVER SIDE ===\n");
    printf("Received Data    : %s\n", receivedData);
    printf("Total 1s counted : %d\n", ones);
    
    if (ones % 2 == 0) {
        printf("Parity Check     : PASSED (Even count - No error detected)\n");
        return 0;  // No error
    } else {
        printf("Parity Check     : FAILED (Odd count - Error detected!)\n");
        return 1;  // Error detected
    }
}

/*
 * Simulate complete transmission with optional error introduction
 */
void simulateTransmission(const char *data, int introduceError, int errorPosition) {
    char transmitted[MAX_BITS];
    char received[MAX_BITS];
    
    printf("\n%s\n", "═══════════════════════════════════════════════════════");
    printf("    TRANSMISSION SIMULATION %s\n", 
           introduceError ? "(WITH ERROR)" : "(NO ERROR)");
    printf("%s\n", "═══════════════════════════════════════════════════════");
    
    // Sender generates parity
    generateParityBit(data, transmitted);
    
    // Copy to received data
    strcpy(received, transmitted);
    
    // Introduce error if requested
    if (introduceError) {
        int len = strlen(received);
        if (errorPosition >= 0 && errorPosition < len) {
            printf("\n=== CHANNEL (Introducing Error) ===\n");
            printf("Error at position: %d\n", errorPosition);
            printf("Original bit     : %c\n", received[errorPosition]);
            
            // Flip the bit
            received[errorPosition] = (received[errorPosition] == '0') ? '1' : '0';
            
            printf("Flipped to       : %c\n", received[errorPosition]);
            printf("Corrupted Data   : %s\n", received);
        }
    } else {
        printf("\n=== CHANNEL (No Error) ===\n");
        printf("Data transmitted successfully.\n");
    }
    
    // Receiver checks parity
    checkParity(received);
}

/*
 * Validate that input contains only 0s and 1s
 */
int validateBinaryInput(const char *input) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] != '0' && input[i] != '1') {
            return 0;  // Invalid
        }
    }
    return 1;  // Valid
}

/*
 * Demonstrate limitation: Even number of errors go undetected
 */
void demonstrateLimitation(void) {
    char data[] = "1010101";
    char transmitted[MAX_BITS];
    char corrupted[MAX_BITS];
    
    printf("\n%s\n", "═══════════════════════════════════════════════════════");
    printf("    DEMONSTRATING PARITY LIMITATION\n");
    printf("    (Even number of errors go undetected)\n");
    printf("%s\n", "═══════════════════════════════════════════════════════");
    
    generateParityBit(data, transmitted);
    strcpy(corrupted, transmitted);
    
    // Introduce TWO errors
    printf("\n=== INTRODUCING 2 ERRORS ===\n");
    printf("Original transmitted: %s\n", transmitted);
    
    // Flip bit at position 0 and 1
    corrupted[0] = (corrupted[0] == '0') ? '1' : '0';
    corrupted[1] = (corrupted[1] == '0') ? '1' : '0';
    
    printf("After 2 bit flips   : %s\n", corrupted);
    printf("Errors at positions : 0 and 1\n");
    
    int error = checkParity(corrupted);
    
    if (error == 0) {
        printf("\n*** LIMITATION: 2 errors went UNDETECTED! ***\n");
        printf("This is because flipping 2 bits maintains even parity.\n");
    }
}

/*
 * Interactive mode for user input
 */
void interactiveMode(void) {
    char data[MAX_BITS];
    char choice;
    int errorPos;
    
    printf("\n%s\n", "═══════════════════════════════════════════════════════");
    printf("    INTERACTIVE MODE\n");
    printf("%s\n", "═══════════════════════════════════════════════════════");
    
    printf("\nEnter binary data (e.g., 1011001): ");
    if (scanf("%63s", data) != 1) {
        printf("Error reading input.\n");
        return;
    }
    
    // Validate input
    if (!validateBinaryInput(data)) {
        printf("Error: Input must contain only 0s and 1s.\n");
        return;
    }
    
    if (strlen(data) == 0) {
        printf("Error: Empty input.\n");
        return;
    }
    
    printf("Introduce error? (y/n): ");
    scanf(" %c", &choice);
    
    if (choice == 'y' || choice == 'Y') {
        printf("Enter error position (0 to %lu): ", strlen(data));
        scanf("%d", &errorPos);
        simulateTransmission(data, 1, errorPos);
    } else {
        simulateTransmission(data, 0, -1);
    }
}

/*
 * Display parity truth table
 */
void displayParityTable(void) {
    printf("\n%s\n", "═══════════════════════════════════════════════════════");
    printf("    EVEN PARITY TRUTH TABLE (3-bit data)\n");
    printf("%s\n", "═══════════════════════════════════════════════════════");
    
    printf("\n┌──────┬────────┬────────┬────────────┐\n");
    printf("│ Data │ #Ones  │ Parity │ Transmitted│\n");
    printf("├──────┼────────┼────────┼────────────┤\n");
    
    for (int i = 0; i < 8; i++) {
        char data[4];
        data[0] = ((i >> 2) & 1) + '0';
        data[1] = ((i >> 1) & 1) + '0';
        data[2] = (i & 1) + '0';
        data[3] = '\0';
        
        int ones = countOnes(data, 3);
        char parity = (ones % 2 == 1) ? '1' : '0';
        
        printf("│ %s  │   %d    │   %c    │   %s%c     │\n", 
               data, ones, parity, data, parity);
    }
    printf("└──────┴────────┴────────┴────────────┘\n");
}

/*
 * Main function with menu
 */
int main(void) {
    int choice;
    
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════╗\n");
    printf("║     EVEN PARITY ERROR DETECTION PROGRAM               ║\n");
    printf("║     Slip 10 - Computer Networks                       ║\n");
    printf("╚═══════════════════════════════════════════════════════╝\n");
    
    // Display theory
    displayParityTable();
    
    do {
        printf("\n┌─────────────────────────────────────┐\n");
        printf("│            MAIN MENU                │\n");
        printf("├─────────────────────────────────────┤\n");
        printf("│ 1. Demo: Transmission without error │\n");
        printf("│ 2. Demo: Transmission with error    │\n");
        printf("│ 3. Demo: Parity limitation (2 errs) │\n");
        printf("│ 4. Interactive mode                 │\n");
        printf("│ 5. Show parity table                │\n");
        printf("│ 0. Exit                             │\n");
        printf("└─────────────────────────────────────┘\n");
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) {
            // Clear invalid input
            while (getchar() != '\n');
            choice = -1;
        }
        
        switch (choice) {
            case 1:
                simulateTransmission("1011001", 0, -1);
                break;
            case 2:
                simulateTransmission("1011001", 1, 3);
                break;
            case 3:
                demonstrateLimitation();
                break;
            case 4:
                interactiveMode();
                break;
            case 5:
                displayParityTable();
                break;
            case 0:
                printf("\nExiting program. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 0);
    
    return 0;
}

/*
 * PSEUDOCODE:
 * ===========
 * 
 * FUNCTION generateEvenParity(data[]):
 *     count = 0
 *     FOR each bit in data:
 *         IF bit == 1:
 *             count = count + 1
 *     
 *     IF count is ODD:
 *         parityBit = 1
 *     ELSE:
 *         parityBit = 0
 *     
 *     RETURN data + parityBit
 * 
 * 
 * FUNCTION checkEvenParity(receivedData[]):
 *     count = 0
 *     FOR each bit in receivedData (including parity):
 *         IF bit == 1:
 *             count = count + 1
 *     
 *     IF count is EVEN:
 *         RETURN "No Error Detected"
 *     ELSE:
 *         RETURN "Error Detected"
 * 
 * 
 * SAMPLE OUTPUT:
 * ==============
 * 
 * ═══════════════════════════════════════════════════════
 *     TRANSMISSION SIMULATION (NO ERROR)
 * ═══════════════════════════════════════════════════════
 * 
 * === SENDER SIDE ===
 * Original Data    : 1011001
 * Number of 1s     : 4 (Even)
 * Parity Bit (Even): 0
 * Transmitted Data : 10110010
 * Total 1s now     : 4 (Even)
 * 
 * === CHANNEL (No Error) ===
 * Data transmitted successfully.
 * 
 * === RECEIVER SIDE ===
 * Received Data    : 10110010
 * Total 1s counted : 4
 * Parity Check     : PASSED (Even count - No error detected)
 * 
 * 
 * ═══════════════════════════════════════════════════════
 *     TRANSMISSION SIMULATION (WITH ERROR)
 * ═══════════════════════════════════════════════════════
 * 
 * === SENDER SIDE ===
 * Original Data    : 1011001
 * Number of 1s     : 4 (Even)
 * Parity Bit (Even): 0
 * Transmitted Data : 10110010
 * 
 * === CHANNEL (Introducing Error) ===
 * Error at position: 3
 * Original bit     : 1
 * Flipped to       : 0
 * Corrupted Data   : 10100010
 * 
 * === RECEIVER SIDE ===
 * Received Data    : 10100010
 * Total 1s counted : 3
 * Parity Check     : FAILED (Odd count - Error detected!)
 */
