/*
 * Slip 1 - Q2 Option B (OR): Framing using Character Count Method
 * 
 * Implements character count method for data link layer framing.
 * 
 * Compile: gcc Slip_01_Q2_OptionB.c -o char_count
 * Run: ./char_count
 */

#include <stdio.h>
#include <string.h>

int main() {
    char data[100];
    
    printf("Character Count Framing\n");
    printf("======================\n");
    printf("Enter data: ");
    fgets(data, 100, stdin);
    data[strcspn(data, "\n")] = '\0';
    
    int count = strlen(data);
    
    printf("\nFrame:\n");
    printf("Count | Data\n");
    printf("──────┼─────\n");
    printf("  %d  | %s\n", count, data);
    printf("\nFrame size: %d + %d = %d bytes\n", 1, count, count + 1);
    
    return 0;
}
