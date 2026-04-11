/*
 * Slip 10 - Q2 Option A: Framing using Character Count Method
 * 
 * Implements character count method.
 * 
 * Compile: gcc Slip_10_Q2_OptionA.c -o char_count_framing
 * Run: ./char_count_framing
 */

#include <stdio.h>
#include <string.h>

int main() {
    char frame[100];
    
    printf("Character Count Framing Method\n");
    printf("==============================\n");
    printf("Enter data to frame: ");
    fgets(frame, 100, stdin);
    frame[strcspn(frame, "\n")] = '\0';
    
    int len = strlen(frame);
    
    printf("\nFrame Format:\n");
    printf("┌─────┬──────────────────┐\n");
    printf("│Cnt  │ Data             │\n");
    printf("├─────┼──────────────────┤\n");
    printf("│ %2d │ %-16s │\n", len, frame);
    printf("└─────┴──────────────────┘\n");
    printf("\nTotal frame size: %d bytes\n", len + 1);
    
    return 0;
}
