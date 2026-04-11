/*
 * Slip 6 - Option A: Character Count Framing Method
 * Data Link Layer Framing Implementation
 *
 * Concept: Each frame starts with a count field indicating
 *          the total number of characters in the frame
 *          (including the count itself).
 *
 * Compilation: gcc -o framing Slip_06_Q2_OptionA.c
 * Execution:   ./framing
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DATA 1000
#define MAX_FRAMES 100
#define DEFAULT_FRAME_SIZE 5  // Including count byte

/* Structure to hold a single frame */
typedef struct {
    int count;                 // Character count
    char data[MAX_DATA];       // Frame data (excluding count)
    int dataLength;            // Actual data length
} Frame;

/* Structure to hold all frames */
typedef struct {
    Frame frames[MAX_FRAMES];
    int numFrames;
} FrameCollection;

/*
 * Function: createFrames
 * Purpose:  Apply character count framing to input data
 *
 * Algorithm:
 * 1. Divide data into frames of specified size
 * 2. Each frame starts with count (total chars in frame)
 * 3. Data portion = frameSize - 1 characters
 */
FrameCollection createFrames(const char *data, int frameSize) {
    FrameCollection fc;
    fc.numFrames = 0;

    int dataLen = strlen(data);
    int dataPerFrame = frameSize - 1;  // Reserve 1 for count
    int i = 0;


    while (i < dataLen && fc.numFrames < MAX_FRAMES) {
        Frame *f = &fc.frames[fc.numFrames];

        // Calculate how many data chars fit in this frame
        int remaining = dataLen - i;
        int charsToTake = (remaining < dataPerFrame) ? remaining : dataPerFrame;

        // Set count (data chars + 1 for count itself)
        f->count = charsToTake + 1;
        f->dataLength = charsToTake;

        // Copy data portion
        strncpy(f->data, data + i, charsToTake);
        f->data[charsToTake] = '\0';

        printf("Frame %d: Count = %d, Data = \"", fc.numFrames + 1, f->count);
        for (int j = 0; j < charsToTake; j++) {
            printf("%c", f->data[j]);
        }
        printf("\"\n");
        printf("         Binary: [%d]", f->count);
        for (int j = 0; j < charsToTake; j++) {
            printf("[%c]", f->data[j]);
        }
        printf("\n\n");

        i += charsToTake;
        fc.numFrames++;
    }

    return fc;
}

/*
 * Function: displayFramedStream
 * Purpose:  Show the complete framed data stream
 */
void displayFramedStream(FrameCollection *fc) {


    for (int i = 0; i < fc->numFrames; i++) {
        printf("[%d]", fc->frames[i].count);
        for (int j = 0; j < fc->frames[i].dataLength; j++) {
            printf("[%c]", fc->frames[i].data[j]);
        }
        if (i < fc->numFrames - 1)    }
    printf("\n");

}

/*
 * Function: extractData
 * Purpose:  Deframe data using character count method (receiver side)
 *
 * Algorithm:
 * 1. Read count from beginning of frame
 * 2. Extract (count - 1) data characters
 * 3. Move to next frame
 * 4. Repeat until end of stream
 */
void extractData(FrameCollection *fc, char *output) {
    int outIdx = 0;


    for (int i = 0; i < fc->numFrames; i++) {
        Frame *f = &fc->frames[i];


        for (int j = 0; j < f->dataLength; j++) {
            output[outIdx++] = f->data[j];
            printf("%c", f->data[j]);
        }
        printf("\"");

        // Padding for alignment
        for (int k = f->dataLength; k < 6; k++)    }

    output[outIdx] = '\0';

}

/*
 * Function: simulateTransmission
 * Purpose:  Convert frames to transmission stream and back
 */
void simulateTransmission(FrameCollection *fc) {
    char transmissionStream[MAX_DATA * 2];
    int idx = 0;


    // Create transmission stream

    for (int i = 0; i < fc->numFrames; i++) {
        transmissionStream[idx++] = '0' + fc->frames[i].count;
        printf("%d", fc->frames[i].count);

        for (int j = 0; j < fc->frames[i].dataLength; j++) {
            transmissionStream[idx++] = fc->frames[i].data[j];
            printf("%c", fc->frames[i].data[j]);
        }
    }
    transmissionStream[idx] = '\0';


    // Parse transmission stream (receiver side simulation)


    int pos = 0;
    int frameNum = 1;
    char extractedData[MAX_DATA];
    int dataIdx = 0;

    while (pos < idx) {
        int count = transmissionStream[pos] - '0';

        pos++;

        for (int i = 0; i < count - 1 && pos < idx; i++) {
            extractedData[dataIdx++] = transmissionStream[pos];
            printf("%c", transmissionStream[pos]);
            pos++;
        }
        printf("\"");
        for (int k = count - 1; k < 6; k++)        frameNum++;
    }
    extractedData[dataIdx] = '\0';


}

/*
 * Function: demonstrateErrorScenario
 * Purpose:  Show what happens when count field gets corrupted
 */
void demonstrateErrorScenario(void) {


}

/*
 * Function: displayDiagram
 * Purpose:  Show visual representation of the framing concept
 */
void displayDiagram(void) {
    printf("\n");


}

/*
 * Main function demonstrating character count framing
 */
int main() {
    char inputData[MAX_DATA];
    char extractedData[MAX_DATA];
    int frameSize;
    int choice;

    printf("\n");


    displayDiagram();

    while (1) {


        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();  // Clear newline

        switch (choice) {
            case 1:
                printf("\nEnter data to frame: ");
                fgets(inputData, MAX_DATA, stdin);
                inputData[strcspn(inputData, "\n")] = '\0';  // Remove newline

                printf("Enter frame size (including count, min 2): ");
                scanf("%d", &frameSize);

                if (frameSize < 2) {
                    printf("Frame size must be at least 2!\n");
                    break;
                }

                if (strlen(inputData) == 0) {
                    printf("No data entered!\n");
                    break;
                }


                printf("Original Data: \"%s\"\n", inputData);
                printf("Data Length: %lu characters\n", strlen(inputData));


                FrameCollection fc = createFrames(inputData, frameSize);
                displayFramedStream(&fc);
                extractData(&fc, extractedData);


                       strcmp(inputData, extractedData) == 0 ? "YES ✓" : "NO ✗ ");

                break;

            case 2:
                strcpy(inputData, "HELLOWORLD");
                frameSize = DEFAULT_FRAME_SIZE;


                printf("DEMONSTRATION with Sample Data\n");

                printf("Data: \"%s\"\n", inputData);
                printf("Frame Size: %d\n", frameSize);


                FrameCollection fc2 = createFrames(inputData, frameSize);
                displayFramedStream(&fc2);
                simulateTransmission(&fc2);
                extractData(&fc2, extractedData);


                       strcmp(inputData, extractedData) == 0 ? "YES ✓" : "NO ✗ ");

                break;

            case 3:
                demonstrateErrorScenario();
                break;

            case 4:
                printf("\nExiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
