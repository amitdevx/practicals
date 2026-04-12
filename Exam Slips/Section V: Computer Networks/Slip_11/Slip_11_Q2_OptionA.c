/*
 * Slip 11 - Q2 Option A: Write a C program to implement framing using the
 * Character Count Method.
 *
 * Compile: gcc Slip_11_Q2_OptionA.c -o char_count
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

    printf("\nFramed output: [%zu]%s\n", len, data);
    printf("Count field value: %zu\n", len);

    return 0;
}
