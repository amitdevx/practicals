/*
 * Slip 6 - Q2 Option A: Write a program to implement framing using character
 * count method in the data link layer.
 *
 * Compile: gcc Slip_06_Q2_OptionA.c -o char_count
 * Run: ./char_count
 */

#include <stdio.h>
#include <string.h>

int main(void) {
    char data[256];
    size_t len;

    printf("Character Count Framing\n");
    printf("=======================\n");
    printf("Enter data: ");
    fgets(data, sizeof(data), stdin);

    len = strlen(data);
    if (len > 0 && data[len - 1] == '\n') {
        data[len - 1] = '\0';
        len--;
    }

    printf("\nFramed output:\n");
    printf("[%zu]%s\n", len, data);
    printf("Total frame size (count + data): %zu\n", len + 1);

    return 0;
}
