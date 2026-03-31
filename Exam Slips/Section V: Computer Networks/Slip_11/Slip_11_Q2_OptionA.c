/*
 * Slip 11 - Q2 Option A
 * Character Count Method for Framing
 * 
 * Concept: In Character Count framing, the first byte of each frame
 * contains the count of characters in that frame (including the count byte).
 * 
 * This program demonstrates:
 * 1. Framing: Adding character count to create frames
 * 2. Deframing: Extracting original data from framed data
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DATA 1000
#define MAX_FRAME_DATA 10  // Maximum data characters per frame (excluding count)

// Structure to represent a frame
typedef struct {
    int count;              // Character count (includes this count byte)
    char data[MAX_FRAME_DATA + 1];
} Frame;

// Function prototypes
void performFraming(char *input);
void performDeframing(int *framedData, int totalLength);
void displayFramedData(int *framedData, int length);

int main() {
    int choice;
    char input[MAX_DATA];
    
    printf("╔═══════════════════════════════════════════════════════╗\n");
    printf("║     CHARACTER COUNT METHOD - FRAMING SIMULATION       ║\n");
    printf("╠═══════════════════════════════════════════════════════╣\n");
    printf("║  Data Link Layer Framing Technique                    ║\n");
    printf("║  First byte = Total count of bytes in frame           ║\n");
    printf("╚═══════════════════════════════════════════════════════╝\n\n");
    
    while (1) {
        printf("\n┌─────────────────────────────────┐\n");
        printf("│           MENU                  │\n");
        printf("├─────────────────────────────────┤\n");
        printf("│  1. Perform Framing             │\n");
        printf("│  2. Demonstrate Complete Cycle  │\n");
        printf("│  3. Show Example                │\n");
        printf("│  4. Exit                        │\n");
        printf("└─────────────────────────────────┘\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline
        
        switch (choice) {
            case 1:
                printf("\nEnter data to frame: ");
                fgets(input, MAX_DATA, stdin);
                input[strcspn(input, "\n")] = '\0'; // Remove newline
                performFraming(input);
                break;
                
            case 2: {
                printf("\nEnter data for complete framing-deframing cycle: ");
                fgets(input, MAX_DATA, stdin);
                input[strcspn(input, "\n")] = '\0';
                
                printf("\n════════════════════════════════════════\n");
                printf("       COMPLETE FRAMING CYCLE\n");
                printf("════════════════════════════════════════\n");
                
                // Framing
                printf("\n[STEP 1] FRAMING PROCESS\n");
                printf("─────────────────────────\n");
                performFraming(input);
                
                // Create framed data array for deframing demo
                int len = strlen(input);
                int framedData[MAX_DATA * 2];
                int idx = 0;
                int i = 0;
                
                while (i < len) {
                    int frameSize = (len - i > MAX_FRAME_DATA) ? MAX_FRAME_DATA : (len - i);
                    int count = frameSize + 1; // +1 for count byte
                    framedData[idx++] = count;
                    for (int j = 0; j < frameSize; j++) {
                        framedData[idx++] = input[i++];
                    }
                }
                
                // Deframing
                printf("\n[STEP 2] DEFRAMING PROCESS\n");
                printf("──────────────────────────\n");
                performDeframing(framedData, idx);
                break;
            }
                
            case 3: {
                printf("\n════════════════════════════════════════\n");
                printf("     CHARACTER COUNT - EXAMPLE\n");
                printf("════════════════════════════════════════\n");
                
                printf("\n▶ Original Data: \"HELLO WORLD\"\n");
                printf("\n▶ Framing Process (Frame size: 5 data chars):\n\n");
                
                printf("  Original: H E L L O   W O R L D\n");
                printf("            └─────┬─────┘ └─────┬─────┘\n");
                printf("             Frame 1       Frame 2 + Frame 3\n\n");
                
                printf("  Frame 1: [6] H E L L O   (count=6, includes count byte)\n");
                printf("           ─┬─ ─────┬─────\n");
                printf("            │       └── 5 data characters\n");
                printf("            └── Count byte\n\n");
                
                printf("  Frame 2: [6]   W O R L  (count=6, space is counted)\n");
                printf("  Frame 3: [2] D          (count=2, last frame)\n\n");
                
                printf("▶ Transmitted Stream:\n");
                printf("  ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐\n");
                printf("  │ 6 │ H │ E │ L │ L │ O │ 6 │ ' '│ W │ O │ R │ L │ 2 │ D │\n");
                printf("  └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘\n");
                printf("   ↑                       ↑                       ↑\n");
                printf("   Frame 1 count           Frame 2 count           Frame 3 count\n\n");
                
                printf("▶ Deframing Process:\n");
                printf("  Read 6 → Extract 5 chars (HELLO)\n");
                printf("  Read 6 → Extract 5 chars ( WORL)\n");
                printf("  Read 2 → Extract 1 char  (D)\n");
                printf("  Result: HELLO WORLD ✓\n");
                
                printf("\n▶ Problem with Character Count Method:\n");
                printf("  If count byte gets corrupted:\n");
                printf("  [6] H E L L O [7←error] W O R L D\n");
                printf("                ↑\n");
                printf("  Wrong count causes loss of synchronization!\n");
                printf("  Receiver reads 6 more chars instead of 5\n");
                break;
            }
                
            case 4:
                printf("\nExiting program. Goodbye!\n");
                exit(0);
                
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
    
    return 0;
}

/*
 * Function: performFraming
 * Divides input data into frames using character count method
 */
void performFraming(char *input) {
    int len = strlen(input);
    int frameNum = 1;
    int i = 0;
    
    printf("\nOriginal Data: \"%s\"\n", input);
    printf("Data Length: %d characters\n", len);
    printf("Max data per frame: %d characters\n", MAX_FRAME_DATA);
    printf("\n┌────────────────────────────────────────────────────┐\n");
    printf("│                 FRAMED OUTPUT                      │\n");
    printf("└────────────────────────────────────────────────────┘\n\n");
    
    int framedData[MAX_DATA * 2];
    int framedIdx = 0;
    
    while (i < len) {
        // Calculate frame data size
        int frameDataSize = (len - i > MAX_FRAME_DATA) ? MAX_FRAME_DATA : (len - i);
        int count = frameDataSize + 1; // +1 for count byte itself
        
        printf("Frame %d:\n", frameNum);
        printf("  ├── Count: %d (includes count byte)\n", count);
        printf("  ├── Data:  \"");
        
        // Store count byte
        framedData[framedIdx++] = count;
        
        // Store data bytes
        for (int j = 0; j < frameDataSize; j++) {
            printf("%c", input[i]);
            framedData[framedIdx++] = input[i++];
        }
        printf("\"\n");
        printf("  └── Frame bytes: [%d]", count);
        
        // Display frame bytes
        int startIdx = framedIdx - frameDataSize - 1;
        for (int j = 1; j <= frameDataSize; j++) {
            printf("[%c]", framedData[startIdx + j]);
        }
        printf("\n\n");
        
        frameNum++;
    }
    
    printf("────────────────────────────────────────────────────\n");
    printf("Total frames created: %d\n", frameNum - 1);
    printf("Original data size: %d bytes\n", len);
    printf("Framed data size: %d bytes\n", framedIdx);
    printf("Overhead: %d bytes (%.1f%%)\n", 
           framedIdx - len, ((float)(framedIdx - len) / len) * 100);
    
    printf("\n▶ Complete framed stream:\n   ");
    displayFramedData(framedData, framedIdx);
}

/*
 * Function: performDeframing
 * Extracts original data from framed data stream
 */
void performDeframing(int *framedData, int totalLength) {
    char extractedData[MAX_DATA];
    int dataIdx = 0;
    int i = 0;
    int frameNum = 1;
    
    printf("\nReceived framed data: ");
    displayFramedData(framedData, totalLength);
    printf("\n");
    
    printf("\n┌────────────────────────────────────────────────────┐\n");
    printf("│              DEFRAMING PROCESS                     │\n");
    printf("└────────────────────────────────────────────────────┘\n\n");
    
    while (i < totalLength) {
        int count = framedData[i];  // Read count byte
        int dataBytes = count - 1;   // Data bytes = count - 1
        
        printf("Frame %d:\n", frameNum);
        printf("  ├── Read count: %d\n", count);
        printf("  ├── Data bytes to extract: %d\n", dataBytes);
        printf("  └── Extracted: \"");
        
        i++; // Move past count byte
        
        // Extract data bytes
        for (int j = 0; j < dataBytes && i < totalLength; j++) {
            extractedData[dataIdx++] = framedData[i];
            printf("%c", framedData[i]);
            i++;
        }
        printf("\"\n\n");
        
        frameNum++;
    }
    
    extractedData[dataIdx] = '\0';
    
    printf("────────────────────────────────────────────────────\n");
    printf("▶ Extracted Original Data: \"%s\"\n", extractedData);
    printf("▶ Total bytes extracted: %d\n", dataIdx);
    printf("▶ Deframing successful! ✓\n");
}

/*
 * Function: displayFramedData
 * Displays framed data in a visual format
 */
void displayFramedData(int *framedData, int length) {
    printf("┌");
    for (int i = 0; i < length; i++) {
        printf("───");
        if (i < length - 1) printf("┬");
    }
    printf("┐\n   │");
    
    for (int i = 0; i < length; i++) {
        // Check if it's a count byte (first byte or after previous frame)
        // For simplicity, we show all numeric values differently
        if (framedData[i] >= 1 && framedData[i] <= MAX_FRAME_DATA + 1 && 
            (framedData[i] < 32 || framedData[i] > 126)) {
            printf(" %d ", framedData[i]);
        } else if (framedData[i] >= 32 && framedData[i] <= 126) {
            printf(" %c ", framedData[i]);
        } else {
            printf(" %d ", framedData[i]);
        }
        printf("│");
    }
    
    printf("\n   └");
    for (int i = 0; i < length; i++) {
        printf("───");
        if (i < length - 1) printf("┴");
    }
    printf("┘\n");
}
