/*
 * Slip 16 - Q2 Option B: Data Link Layer Framing - Character Stuffing
 *
 * Description: Implements character stuffing/destuffing for data link layer framing
 * Uses DLE (Data Link Escape), STX (Start of Text), and ETX (End of Text) characters
 *
 * Compilation: gcc -o char_stuffing Slip_16_Q2_OptionB.c
 * Execution:   ./char_stuffing
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DATA_LEN 500
#define MAX_FRAME_LEN 1500

// Define special characters for framing
#define DLE '#'   // Data Link Escape (using # for visibility)
#define STX '{'   // Start of Text
#define ETX '}'   // End of Text

// For actual protocol simulation, we can use ASCII values
#define ASCII_DLE 16  // Actual DLE character
#define ASCII_STX 2   // Actual STX character
#define ASCII_ETX 3   // Actual ETX character

/*
 * Function: characterStuff
 * ------------------------
 * Adds frame delimiters and stuffs DLE characters in the data
 *
 * Parameters:
 *   data        - Original data to be framed
 *   frame       - Buffer to store the stuffed frame
 *
 * Framing Format: DLE STX <data with stuffed DLEs> DLE ETX
 *
 * Algorithm:
 *   1. Add start delimiter (DLE STX)
 *   2. For each character in data:
 *      - If character is DLE, add DLE DLE (stuff extra DLE)
 *      - Otherwise, add character as-is
 *   3. Add end delimiter (DLE ETX)
 */
void characterStuff(const char *data, char *frame) {
    int i, j = 0;
    int len = strlen(data);

    // Add start delimiter: DLE STX
    frame[j++] = DLE;
    frame[j++] = STX;

    // Process each character in data
    for (i = 0; i < len; i++) {
        if (data[i] == DLE) {
            // Stuff: replace DLE with DLE DLE
            frame[j++] = DLE;
            frame[j++] = DLE;
        } else {
            frame[j++] = data[i];
        }
    }

    // Add end delimiter: DLE ETX
    frame[j++] = DLE;
    frame[j++] = ETX;
    frame[j] = '\0';
}

/*
 * Function: characterDestuff
 * --------------------------
 * Removes frame delimiters and destuffs DLE characters
 *
 * Parameters:
 *   frame       - Stuffed frame with delimiters
 *   data        - Buffer to store the extracted data
 *
 * Returns:
 *   1 if successful, 0 if frame format is invalid
 */
int characterDestuff(const char *frame, char *data) {
    int i, j = 0;
    int len = strlen(frame);

    // Verify start delimiter
    if (len < 4 || frame[0] != DLE || frame[1] != STX) {
        printf("Error: Invalid frame start delimiter!\n");
        return 0;
    }

    // Verify end delimiter
    if (frame[len-2] != DLE || frame[len-1] != ETX) {
        printf("Error: Invalid frame end delimiter!\n");
        return 0;
    }

    // Extract data (skip start delimiter, stop before end delimiter)
    i = 2;  // Start after DLE STX
    while (i < len - 2) {
        if (frame[i] == DLE) {
            if (i + 1 < len - 2 && frame[i + 1] == DLE) {
                // Destuff: DLE DLE becomes DLE
                data[j++] = DLE;
                i += 2;
            } else {
                // Single DLE near end (part of end delimiter)
                break;
            }
        } else {
            data[j++] = frame[i++];
        }
    }

    data[j] = '\0';
    return 1;
}

/*
 * Function: displayFrameDetails
 * -----------------------------
 * Shows detailed breakdown of the stuffed frame
 */
void displayFrameDetails(const char *frame) {
    int i;
    int len = strlen(frame);


    for (i = 0; i < len && i < 50; i++) {
        if (frame[i] == DLE) printf("[DLE]");
        else if (frame[i] == STX) printf("[STX]");
        else if (frame[i] == ETX) printf("[ETX]");
        else printf("%c", frame[i]);
    }
    if (len > 50) printf("...");
    printf("\n");


}

/*
 * Function: bitStuff
 * ------------------
 * Implements bit stuffing (HDLC-style)
 * After 5 consecutive 1s, insert a 0
 *
 * Parameters:
 *   data  - Binary data string (e.g., "01111110101")
 *   frame - Buffer for stuffed frame
 */
void bitStuff(const char *data, char *frame) {
    int i, j = 0;
    int consecutiveOnes = 0;
    int len = strlen(data);

    // Add start flag: 01111110
    strcpy(frame, "01111110");
    j = 8;

    // Process each bit
    for (i = 0; i < len; i++) {
        frame[j++] = data[i];

        if (data[i] == '1') {
            consecutiveOnes++;
            if (consecutiveOnes == 5) {
                // Stuff a 0 after 5 consecutive 1s
                frame[j++] = '0';
                consecutiveOnes = 0;
            }
        } else {
            consecutiveOnes = 0;
        }
    }

    // Add end flag: 01111110
    strcpy(&frame[j], "01111110");
}

/*
 * Function: bitDestuff
 * --------------------
 * Removes bit stuffing
 *
 * Parameters:
 *   frame - Stuffed frame with flags
 *   data  - Buffer for extracted data
 */
int bitDestuff(const char *frame, char *data) {
    int i, j = 0;
    int consecutiveOnes = 0;
    int len = strlen(frame);

    // Skip start flag (first 8 bits) and stop before end flag (last 8 bits)
    if (len < 16) {
        printf("Error: Frame too short!\n");
        return 0;
    }

    // Verify flags
    if (strncmp(frame, "01111110", 8) != 0 ||
        strncmp(&frame[len-8], "01111110", 8) != 0) {
        printf("Error: Invalid frame flags!\n");
        return 0;
    }

    // Process data portion
    for (i = 8; i < len - 8; i++) {
        data[j++] = frame[i];

        if (frame[i] == '1') {
            consecutiveOnes++;
            if (consecutiveOnes == 5) {
                // Skip the stuffed 0
                i++;
                consecutiveOnes = 0;
            }
        } else {
            consecutiveOnes = 0;
        }
    }

    data[j] = '\0';
    return 1;
}

/*
 * Function: displayMenu
 * ---------------------
 * Displays the main menu
 */
void displayMenu() {


    printf("Enter your choice: ");
}

int main() {
    char data[MAX_DATA_LEN];
    char frame[MAX_FRAME_LEN];
    char extracted[MAX_DATA_LEN];
    int choice;


    while (1) {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                printf("\n--- CHARACTER STUFFING (Sender Side) ---\n");
                printf("Enter data to transmit (use '%c' to test stuffing): ", DLE);
                fgets(data, MAX_DATA_LEN, stdin);
                data[strcspn(data, "\n")] = '\0';

                characterStuff(data, frame);


                displayFrameDetails(frame);
                break;

            case 2:
                printf("\n--- CHARACTER DESTUFFING (Receiver Side) ---\n");
                printf("Enter stuffed frame: ");
                fgets(frame, MAX_FRAME_LEN, stdin);
                frame[strcspn(frame, "\n")] = '\0';

                if (characterDestuff(frame, extracted)) {


                }
                break;

            case 3:
                printf("\n--- BIT STUFFING (Sender Side) ---\n");
                printf("Enter binary data (e.g., 011111100): ");
                fgets(data, MAX_DATA_LEN, stdin);
                data[strcspn(data, "\n")] = '\0';

                bitStuff(data, frame);


                break;

            case 4:
                printf("\n--- BIT DESTUFFING (Receiver Side) ---\n");
                printf("Enter stuffed frame: ");
                fgets(frame, MAX_FRAME_LEN, stdin);
                frame[strcspn(frame, "\n")] = '\0';

                if (bitDestuff(frame, extracted)) {


                }
                break;

            case 5:


                // Demo 1: Simple message without DLE
                printf("\n[Demo 1: Simple message without DLE character]\n");
                strcpy(data, "HELLO WORLD");
                characterStuff(data, frame);
                characterDestuff(frame, extracted);

                printf("  Original Data:   '%s'\n", data);
                printf("  Stuffed Frame:   '%s'\n", frame);
                printf("  Extracted Data:  '%s'\n", extracted);
                printf("  Verification:    %s\n", strcmp(data, extracted) == 0 ? "✓ PASS" : "✗ FAIL");

                // Demo 2: Message with DLE character
                printf("\n[Demo 2: Message containing DLE character '%c']\n", DLE);
                sprintf(data, "DATA%cLINK%cESCAPE", DLE, DLE);
                characterStuff(data, frame);
                characterDestuff(frame, extracted);

                printf("  Original Data:   '%s'\n", data);
                printf("  Stuffed Frame:   '%s'\n", frame);
                printf("  Extracted Data:  '%s'\n", extracted);
                printf("  Note: Each '%c' in data becomes '%c%c' in frame\n", DLE, DLE, DLE);
                printf("  Verification:    %s\n", strcmp(data, extracted) == 0 ? "✓ PASS" : "✗ FAIL");

                // Demo 3: Multiple DLEs
                printf("\n[Demo 3: Multiple consecutive DLE characters]\n");
                sprintf(data, "A%c%c%cB", DLE, DLE, DLE);
                characterStuff(data, frame);
                characterDestuff(frame, extracted);

                printf("  Original Data:   '%s' (3 DLEs between A and B)\n", data);
                printf("  Stuffed Frame:   '%s'\n", frame);
                printf("  Extracted Data:  '%s'\n", extracted);
                printf("  Verification:    %s\n", strcmp(data, extracted) == 0 ? "✓ PASS" : "✗ FAIL");

                displayFrameDetails(frame);
                break;

            case 6:


                // Demo 1: No stuffing needed
                printf("\n[Demo 1: Data without 5 consecutive 1s]\n");
                strcpy(data, "01100101");
                bitStuff(data, frame);
                bitDestuff(frame, extracted);

                printf("  Original:    %s\n", data);
                printf("  Frame:       %s\n", frame);
                printf("  Extracted:   %s\n", extracted);
                printf("  Stuffed 0s:  0 (no stuffing needed)\n");
                printf("  Verification: %s\n", strcmp(data, extracted) == 0 ? "✓ PASS" : "✗ FAIL");

                // Demo 2: Single stuffing
                printf("\n[Demo 2: Data with exactly 5 consecutive 1s]\n");
                strcpy(data, "0111110");
                bitStuff(data, frame);
                bitDestuff(frame, extracted);

                printf("  Original:    %s\n", data);
                printf("  Frame:       %s\n", frame);
                printf("  Extracted:   %s\n", extracted);
                printf("  Note: 11111 becomes 111110 (0 stuffed after 5 ones)\n");
                printf("  Verification: %s\n", strcmp(data, extracted) == 0 ? "✓ PASS" : "✗ FAIL");

                // Demo 3: Flag-like pattern
                printf("\n[Demo 3: Data containing flag pattern 01111110]\n");
                strcpy(data, "01111110");
                bitStuff(data, frame);
                bitDestuff(frame, extracted);

                printf("  Original:    %s (looks like flag!)\n", data);
                printf("  Frame:       %s\n", frame);
                printf("  Extracted:   %s\n", extracted);
                printf("  Note: 111111 becomes 1111101 (prevents false flag)\n");
                printf("  Verification: %s\n", strcmp(data, extracted) == 0 ? "✓ PASS" : "✗ FAIL");

                // Demo 4: Multiple stuffings
                printf("\n[Demo 4: Data requiring multiple stuffings]\n");
                strcpy(data, "11111111110");
                bitStuff(data, frame);
                bitDestuff(frame, extracted);

                printf("  Original:    %s (10 consecutive 1s)\n", data);
                printf("  Frame:       %s\n", frame);
                printf("  Extracted:   %s\n", extracted);
                printf("  Note: After every 5 ones, a 0 is stuffed\n");
                printf("  Verification: %s\n", strcmp(data, extracted) == 0 ? "✓ PASS" : "✗ FAIL");
                break;

            case 7:
                printf("\nExiting program. Goodbye!\n");
                return 0;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}
