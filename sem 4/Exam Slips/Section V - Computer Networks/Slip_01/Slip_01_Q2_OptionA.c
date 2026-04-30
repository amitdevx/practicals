/*
 * Slip 1 - Q2 Option A: Write a C program to implement the data link layer
 * framing methods such as character and bit stuffing.
 *
 * Compile: gcc Slip_01_Q2_OptionA.c -o stuffing
 * Run: ./stuffing
 */

#include <stdio.h>
#include <string.h>

void character_stuffing(const char *input, char *output) {
    int j = 0;
    output[j++] = 'D';
    output[j++] = 'L';
    output[j++] = 'E';
    output[j++] = 'S';
    output[j++] = 'T';
    output[j++] = 'X';

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == 'D') {
            output[j++] = 'D';
        }
        output[j++] = input[i];
    }

    output[j++] = 'D';
    output[j++] = 'L';
    output[j++] = 'E';
    output[j++] = 'E';
    output[j++] = 'T';
    output[j++] = 'X';
    output[j] = '\0';
}

void bit_stuffing(const char *input, char *output) {
    int ones = 0, j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        output[j++] = input[i];
        if (input[i] == '1') {
            ones++;
            if (ones == 5) {
                output[j++] = '0';
                ones = 0;
            }
        } else {
            ones = 0;
        }
    }
    output[j] = '\0';
}

int main(void) {
    char text[128];
    char bits[256];
    char stuffed_text[256];
    char stuffed_bits[512];

    printf("Data Link Layer Framing\n");
    printf("=======================\n");

    printf("Enter text for character stuffing: ");
    scanf("%127s", text);

    printf("Enter bit stream for bit stuffing: ");
    scanf("%255s", bits);

    character_stuffing(text, stuffed_text);
    bit_stuffing(bits, stuffed_bits);

    printf("\nCharacter Stuffing:\n");
    printf("Original : %s\n", text);
    printf("Stuffed  : %s\n", stuffed_text);

    printf("\nBit Stuffing:\n");
    printf("Original : %s\n", bits);
    printf("Stuffed  : %s\n", stuffed_bits);

    return 0;
}
