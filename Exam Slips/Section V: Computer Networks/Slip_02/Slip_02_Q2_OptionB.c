/*
 * Slip 2 - Q2 Option B: Character Count Framing
 * Computer Networks - Data Link Layer
 * 
 * This program implements the character count method for framing
 * in the data link layer. Each frame starts with a count indicating
 * the total number of bytes in that frame.
 * 
 * Compile: gcc Slip_02_Q2_OptionB.c -o char_count_framing
 * Run: ./char_count_framing
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FRAME_SIZE 256
#define MAX_STREAM_SIZE 1024
#define MAX_FRAMES 20

// Structure to hold a frame
typedef struct {
    int count;                    // Frame size (including count byte)
    char data[MAX_FRAME_SIZE];    // Frame data
    int dataLength;               // Actual data length
} Frame;

// Structure for framed stream
typedef struct {
    unsigned char stream[MAX_STREAM_SIZE];
    int totalLength;
} FramedStream;

/*
 * Create a frame from data using character count method
 * Returns: Frame structure with count and data
 */
Frame createFrame(const char* data) {
    Frame frame;
    frame.dataLength = strlen(data);
    frame.count = frame.dataLength + 1;  // +1 for the count byte itself
    strcpy(frame.data, data);
    return frame;
}

/*
 * Add a frame to the framed stream
 */
void addFrameToStream(FramedStream* stream, Frame* frame) {
    // Add count byte
    stream->stream[stream->totalLength++] = (unsigned char)frame->count;
    
    // Add data bytes
    for (int i = 0; i < frame->dataLength; i++) {
        stream->stream[stream->totalLength++] = frame->data[i];
    }
}

/*
 * Display framing process visually
 */
void displayFramingProcess(const char* data[], int numFrames) {
    printf("\n╔════════════════════════════════════════════════════════╗\n");
    printf("║           CHARACTER COUNT FRAMING PROCESS              ║\n");
    printf("╠════════════════════════════════════════════════════════╣\n");
    printf("║ Method: First byte of each frame = Total frame length  ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n\n");
    
    printf("Input Data Packets:\n");
    printf("───────────────────\n");
    for (int i = 0; i < numFrames; i++) {
        printf("  Packet %d: \"%s\" (length: %lu)\n", i + 1, data[i], strlen(data[i]));
    }
    
    printf("\nFraming Each Packet:\n");
    printf("────────────────────\n");
    
    for (int i = 0; i < numFrames; i++) {
        int dataLen = strlen(data[i]);
        int frameLen = dataLen + 1;  // +1 for count byte
        
        printf("\n  Frame %d: \"%s\"\n", i + 1, data[i]);
        printf("  ┌─────────────────────────────────────────┐\n");
        printf("  │ Data length: %d bytes                    │\n", dataLen);
        printf("  │ Frame length: %d + 1 = %d bytes          │\n", dataLen, frameLen);
        printf("  │                                         │\n");
        printf("  │ Frame structure:                        │\n");
        printf("  │ ┌───────┬");
        for (int j = 0; j < dataLen && j < 10; j++) printf("───────┬");
        printf("┐\n");
        
        printf("  │ │  %2d   │", frameLen);
        for (int j = 0; j < dataLen && j < 10; j++) {
            printf("  '%c'  │", data[i][j]);
        }
        if (dataLen > 10) printf("...");
        printf("\n");
        
        printf("  │ └───────┴");
        for (int j = 0; j < dataLen && j < 10; j++) printf("───────┴");
        printf("┘\n");
        
        printf("  │   ↑count   ↑data bytes                  │\n");
        printf("  └─────────────────────────────────────────┘\n");
    }
}

/*
 * Display the complete framed stream
 */
void displayFramedStream(FramedStream* stream, int numFrames) {
    printf("\n╔════════════════════════════════════════════════════════╗\n");
    printf("║              COMPLETE FRAMED STREAM                    ║\n");
    printf("╠════════════════════════════════════════════════════════╣\n");
    
    printf("║ Byte Stream: ");
    for (int i = 0; i < stream->totalLength && i < 40; i++) {
        if (stream->stream[i] < 32 || stream->stream[i] > 126) {
            printf("[%d]", stream->stream[i]);
        } else {
            printf("[%c]", stream->stream[i]);
        }
    }
    if (stream->totalLength > 40) printf("...");
    printf("\n");
    
    printf("╠════════════════════════════════════════════════════════╣\n");
    printf("║ Numeric representation:                                ║\n");
    printf("║ ");
    for (int i = 0; i < stream->totalLength && i < 20; i++) {
        printf("%3d ", stream->stream[i]);
    }
    if (stream->totalLength > 20) printf("...");
    printf("\n");
    
    printf("║ Total stream length: %d bytes                          ║\n", stream->totalLength);
    printf("╚════════════════════════════════════════════════════════╝\n");
}

/*
 * Extract frames from the stream (deframing)
 */
int extractFrames(FramedStream* stream, Frame frames[], int maxFrames) {
    int position = 0;
    int frameCount = 0;
    
    printf("\n╔════════════════════════════════════════════════════════╗\n");
    printf("║              DEFRAMING PROCESS                         ║\n");
    printf("╠════════════════════════════════════════════════════════╣\n");
    printf("║ Reading stream and extracting frames...                ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n\n");
    
    while (position < stream->totalLength && frameCount < maxFrames) {
        // Read count byte
        int count = stream->stream[position];
        
        printf("  Position %d: Read count byte = %d\n", position, count);
        printf("  → Frame %d contains %d bytes (including count)\n", 
               frameCount + 1, count);
        
        // Extract data (count - 1 bytes after count byte)
        int dataLen = count - 1;
        frames[frameCount].count = count;
        frames[frameCount].dataLength = dataLen;
        
        printf("  → Extracting %d data bytes: \"", dataLen);
        for (int i = 0; i < dataLen; i++) {
            frames[frameCount].data[i] = stream->stream[position + 1 + i];
            printf("%c", frames[frameCount].data[i]);
        }
        frames[frameCount].data[dataLen] = '\0';
        printf("\"\n");
        
        // Move to next frame
        position += count;
        frameCount++;
        printf("  → Next frame starts at position %d\n\n", position);
    }
    
    return frameCount;
}

/*
 * Display extracted frames
 */
void displayExtractedFrames(Frame frames[], int numFrames) {
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║              EXTRACTED FRAMES                          ║\n");
    printf("╠════════════════════════════════════════════════════════╣\n");
    
    for (int i = 0; i < numFrames; i++) {
        printf("║ Frame %d: Count=%d, Data=\"%s\"\n", 
               i + 1, frames[i].count, frames[i].data);
    }
    
    printf("╠════════════════════════════════════════════════════════╣\n");
    printf("║ Total frames extracted: %d                             ║\n", numFrames);
    printf("╚════════════════════════════════════════════════════════╝\n");
}

/*
 * Demonstrate error propagation problem
 */
void demonstrateErrorPropagation() {
    printf("\n╔════════════════════════════════════════════════════════╗\n");
    printf("║     ERROR PROPAGATION DEMONSTRATION                    ║\n");
    printf("╠════════════════════════════════════════════════════════╣\n");
    printf("║ Problem: If count byte is corrupted, all subsequent    ║\n");
    printf("║ frames become unreadable.                              ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n\n");
    
    // Original stream: [4][A][B][C][3][D][E][5][F][G][H][I]
    unsigned char original[] = {4, 'A', 'B', 'C', 3, 'D', 'E', 5, 'F', 'G', 'H', 'I'};
    unsigned char corrupted[] = {4, 'A', 'B', 'C', 5, 'D', 'E', 5, 'F', 'G', 'H', 'I'};
    //                                          ^ Error: 3 changed to 5
    
    printf("  Original stream:  ");
    for (int i = 0; i < 12; i++) {
        if (original[i] < 32) printf("[%d]", original[i]);
        else printf("[%c]", original[i]);
    }
    printf("\n");
    
    printf("  Corrupted stream: ");
    for (int i = 0; i < 12; i++) {
        if (corrupted[i] < 32) printf("[%d]", corrupted[i]);
        else printf("[%c]", corrupted[i]);
    }
    printf("\n");
    printf("                           ↑ Count byte corrupted (3→5)\n\n");
    
    // Parse original
    printf("  PARSING ORIGINAL STREAM:\n");
    printf("  ────────────────────────\n");
    int pos = 0;
    int frame = 1;
    while (pos < 12) {
        int count = original[pos];
        printf("  Frame %d: count=%d, data=\"", frame, count);
        for (int i = 1; i < count; i++) {
            printf("%c", original[pos + i]);
        }
        printf("\"\n");
        pos += count;
        frame++;
    }
    
    // Parse corrupted
    printf("\n  PARSING CORRUPTED STREAM:\n");
    printf("  ─────────────────────────\n");
    pos = 0;
    frame = 1;
    while (pos < 12) {
        int count = corrupted[pos];
        printf("  Frame %d: count=%d, data=\"", frame, count);
        for (int i = 1; i < count && (pos + i) < 12; i++) {
            printf("%c", corrupted[pos + i]);
        }
        printf("\" ");
        if (frame == 2) {
            printf("← INCORRECT! (includes wrong bytes)");
        }
        printf("\n");
        pos += count;
        frame++;
        if (frame > 4) {
            printf("  ... remaining frames are misaligned!\n");
            break;
        }
    }
    
    printf("\n  ⚠ Conclusion: Single error corrupts ALL subsequent frames!\n");
}

/*
 * Compare with other framing methods
 */
void compareFramingMethods() {
    printf("\n╔════════════════════════════════════════════════════════╗\n");
    printf("║        COMPARISON OF FRAMING METHODS                   ║\n");
    printf("╠════════════════════════════════════════════════════════╣\n");
    printf("║ Method              │ Pros           │ Cons            ║\n");
    printf("╠─────────────────────┼────────────────┼─────────────────╣\n");
    printf("║ Character Count     │ Simple, fast   │ Error propagates║\n");
    printf("║ Byte Stuffing       │ Error isolated │ Overhead varies ║\n");
    printf("║ Bit Stuffing        │ Efficient      │ Complex         ║\n");
    printf("║ Physical Layer      │ No overhead    │ Hardware depend ║\n");
    printf("╚═════════════════════╧════════════════╧═════════════════╝\n");
}

int main() {
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║  SLIP 2: CHARACTER COUNT FRAMING - DATA LINK LAYER    ║\n");
    printf("║  Computer Networks                                     ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    
    // Sample data packets to frame
    const char* packets[] = {"ABC", "DE", "FGHI", "JK"};
    int numPackets = 4;
    
    // PART 1: Display framing process
    displayFramingProcess(packets, numPackets);
    
    // PART 2: Create framed stream
    FramedStream stream = {.totalLength = 0};
    
    printf("\n--- Creating Framed Stream ---\n");
    for (int i = 0; i < numPackets; i++) {
        Frame frame = createFrame(packets[i]);
        addFrameToStream(&stream, &frame);
        printf("  Added frame %d: count=%d, data=\"%s\"\n", 
               i + 1, frame.count, frame.data);
    }
    
    // PART 3: Display complete stream
    displayFramedStream(&stream, numPackets);
    
    // PART 4: Extract frames (deframing)
    Frame extractedFrames[MAX_FRAMES];
    int extractedCount = extractFrames(&stream, extractedFrames, MAX_FRAMES);
    
    // PART 5: Display extracted frames
    displayExtractedFrames(extractedFrames, extractedCount);
    
    // PART 6: Verify extraction
    printf("\n╔════════════════════════════════════════════════════════╗\n");
    printf("║              VERIFICATION                              ║\n");
    printf("╠════════════════════════════════════════════════════════╣\n");
    
    int allMatch = 1;
    for (int i = 0; i < numPackets; i++) {
        int match = (strcmp(packets[i], extractedFrames[i].data) == 0);
        printf("║ Original: \"%s\" == Extracted: \"%s\" → %s\n",
               packets[i], extractedFrames[i].data,
               match ? "✓ MATCH" : "✗ MISMATCH");
        if (!match) allMatch = 0;
    }
    
    printf("╠════════════════════════════════════════════════════════╣\n");
    printf("║ Framing/Deframing: %s                         ║\n",
           allMatch ? "SUCCESSFUL ✓" : "FAILED ✗    ");
    printf("╚════════════════════════════════════════════════════════╝\n");
    
    // PART 7: Demonstrate error propagation
    demonstrateErrorPropagation();
    
    // PART 8: Compare methods
    compareFramingMethods();
    
    // PART 9: Interactive mode
    printf("\n╔════════════════════════════════════════════════════════╗\n");
    printf("║              INTERACTIVE MODE                          ║\n");
    printf("╠════════════════════════════════════════════════════════╣\n");
    printf("║ Enter your own data to frame (type 'quit' to exit)    ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n\n");
    
    FramedStream userStream = {.totalLength = 0};
    char input[MAX_FRAME_SIZE];
    int userFrameCount = 0;
    
    while (1) {
        printf("Enter data for frame %d (or 'quit' to finish): ", userFrameCount + 1);
        scanf("%s", input);
        
        if (strcmp(input, "quit") == 0) {
            break;
        }
        
        Frame frame = createFrame(input);
        addFrameToStream(&userStream, &frame);
        printf("  → Created frame: [%d]", frame.count);
        for (int i = 0; i < frame.dataLength; i++) {
            printf("[%c]", frame.data[i]);
        }
        printf("\n\n");
        userFrameCount++;
    }
    
    if (userFrameCount > 0) {
        printf("\n--- Your Framed Stream ---\n");
        displayFramedStream(&userStream, userFrameCount);
        
        Frame userExtracted[MAX_FRAMES];
        int userExtractedCount = extractFrames(&userStream, userExtracted, MAX_FRAMES);
        displayExtractedFrames(userExtracted, userExtractedCount);
    }
    
    printf("\n✓ Program completed successfully!\n");
    return 0;
}

/*
 * SAMPLE OUTPUT:
 * 
 * ╔════════════════════════════════════════════════════════╗
 * ║  SLIP 2: CHARACTER COUNT FRAMING - DATA LINK LAYER    ║
 * ╚════════════════════════════════════════════════════════╝
 * 
 * ╔════════════════════════════════════════════════════════╗
 * ║           CHARACTER COUNT FRAMING PROCESS              ║
 * ╚════════════════════════════════════════════════════════╝
 * 
 * Input Data Packets:
 * ───────────────────
 *   Packet 1: "ABC" (length: 3)
 *   Packet 2: "DE" (length: 2)
 *   Packet 3: "FGHI" (length: 4)
 *   Packet 4: "JK" (length: 2)
 * 
 * Framing Each Packet:
 * ────────────────────
 * 
 *   Frame 1: "ABC"
 *   ┌─────────────────────────────────────────┐
 *   │ Data length: 3 bytes                    │
 *   │ Frame length: 3 + 1 = 4 bytes           │
 *   │ Frame structure:                        │
 *   │ ┌───────┬───────┬───────┬───────┬┐
 *   │ │   4   │  'A'  │  'B'  │  'C'  │
 *   │ └───────┴───────┴───────┴───────┴┘
 *   │   ↑count   ↑data bytes                  │
 *   └─────────────────────────────────────────┘
 * 
 * ╔════════════════════════════════════════════════════════╗
 * ║              COMPLETE FRAMED STREAM                    ║
 * ║ Byte Stream: [4][A][B][C][3][D][E][5][F][G][H][I][3][J][K]
 * ║ Total stream length: 15 bytes                          
 * ╚════════════════════════════════════════════════════════╝
 */
