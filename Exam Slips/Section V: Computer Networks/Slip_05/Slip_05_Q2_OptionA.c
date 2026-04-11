/*
 * Slip 5 - Q2 Option A: Framing using Character Count
 * 
 * Implements character count method for data link layer framing.
 * 
 * Compile: gcc Slip_05_Q2_OptionA.c -o char_count_framing
 * Run: ./char_count_framing
 */

#include <stdio.h>
#include <string.h>

int main() {
    char frame[100];
    int count;
    
    printf("Character Count Framing\n");
    printf("=======================\n");
    printf("Enter data: ");
    fgets(frame, 100, stdin);
    frame[strcspn(frame, "\n")] = '\0';
    
    count = strlen(frame);
    
    printf("\nFrame Structure:\n");
    printf("┌──────┬────────────────┐\n");
    printf("│Count │      Data      │\n");
    printf("├──────┼────────────────┤\n");
    printf("│ %2d  │ %s\n", count, frame);
    printf("└──────┴────────────────┘\n");
    
    printf("\nFrame Details:\n");
    printf("Count Value: %d bytes\n", count);
    printf("Data: %s\n", frame);
    printf("Total Frame Size: %d bytes\n", count + 1);
    
    return 0;
}
