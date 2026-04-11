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

void displayData(int data[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d", data[i]);
        if ((i + 1) % 4 == 0 && i != size - 1) {        }
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


    displayData(data, size);


    displayData(data, size);
    printf(" | %d", parityBit);

           (ones + parityBit) % 2 == 1 ? "✓ YES (Valid)" : "✗ NO (Invalid)");


    printf("\n  ➜ Transmitted Frame: ");
    displayData(data, size);
    printf("%d\n", parityBit);    for (int i = 0; i < size; i++) printf("-");
    printf("-\n");    for (int i = 0; i < size; i++) printf("D");
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


    displayData(received, size - 1);


    if (parityOK) {


    } else {


    }


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

    printf("\n  Received Data:     ");
    displayData(transmitted, transmittedSize);
    printf("\n");

    // Check parity
    int totalOnes = countOnes(transmitted, transmittedSize);
    int parityOK = (totalOnes % 2 == 1);


    if (errorCount == 0) {

    } else if (errorCount % 2 == 1) {
        // Odd number of errors
        if (!parityOK) {

        } else {

        }
    } else {
        // Even number of errors
        if (parityOK) {


        } else {

        }
    }

}

void displayInfo() {


    printf("  WHAT IS ODD PARITY?\n");

    printf("  A parity bit is added to data so that the total number of\n");
    printf("  1-bits (including the parity bit) is always ODD.\n\n");

    printf("  HOW IT WORKS:\n");


    printf("  ERROR DETECTION:\n");

    printf("  At receiver: Count all 1s including parity bit\n");
    printf("    • If count is ODD → No error detected ✓\n");
    printf("    • If count is EVEN → Error detected! ✗\n\n");

    printf("  LIMITATIONS:\n");


    printf("  KEY POINTS:\n");

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


    displayData(data, size);


    displayData(data, size);
    printf("%d", oddParity);


    displayData(data, size);
    printf("%d", evenParity);


}

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
