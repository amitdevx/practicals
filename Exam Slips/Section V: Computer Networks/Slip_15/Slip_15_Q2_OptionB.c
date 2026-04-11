/*
 * Slip 15 - Q2 Option B: Any Data Link Layer Framing Method
 * 
 * Implements flag-based framing with stuffing.
 * 
 * Compile: gcc Slip_15_Q2_OptionB.c -o framing
 * Run: ./framing
 */

#include <stdio.h>
#include <string.h>

int main() {
    char data[100], frame[200];
    int data_len, frame_len = 0;
    int flag = 0x7E;
    
    printf("Data Link Layer Framing\n");
    printf("=======================\n");
    printf("Enter data: ");
    fgets(data, 100, stdin);
    data[strcspn(data, "\n")] = '\0';
    
    data_len = strlen(data);
    
    frame[frame_len++] = flag;
    
    for (int i = 0; i < data_len; i++) {
        if ((unsigned char)data[i] == flag) {
            frame[frame_len++] = 0x7D;
            frame[frame_len++] = 0x5E;
        } else if ((unsigned char)data[i] == 0x7D) {
            frame[frame_len++] = 0x7D;
            frame[frame_len++] = 0x5D;
        } else {
            frame[frame_len++] = data[i];
        }
    }
    
    frame[frame_len++] = flag;
    
    printf("\nFrame Structure:\n");
    printf("Flag | Data (stuffed) | Flag\n");
    printf("%-4d | ", flag);
    for (int i = 1; i < frame_len - 1; i++) {
        printf("%02X ", (unsigned char)frame[i]);
    }
    printf("| %-4d\n", flag);
    
    printf("\nOriginal: %d bytes\n", data_len);
    printf("Framed: %d bytes\n", frame_len);
    
    return 0;
}
