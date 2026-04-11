/*
 * Slip 15 - Q2 Option B: Data Encoding/Decoding
 * 
 * Simple ASCII encoding to decimal.
 * 
 * Compile: gcc Slip_15_Q2_OptionB.c -o encoding
 * Run: ./encoding
 */

#include <stdio.h>
#include <string.h>

int main() {
    char text[100];
    
    printf("Enter text: ");
    fgets(text, 100, stdin);
    text[strcspn(text, "\n")] = '\0';
    
    printf("Encoded (ASCII values):\n");
    for (int i = 0; text[i]; i++) {
        printf("%c -> %d\n", text[i], (int)text[i]);
    }
    
    return 0;
}
