/*
 * Slip 16 - Q2 Option B: Write a C program to implement the any data link
 * layer framing method.
 *
 * Compile: gcc Slip_16_Q2_OptionB.c -o framing
 * Run: ./framing
 */

#include <stdio.h>
#include <string.h>

int main(void) {
    char data[256];
    size_t len;

    printf("Data Link Layer Framing\n");
    printf("=======================\n");
    printf("Enter data: ");
    fgets(data, sizeof(data), stdin);

    len = strlen(data);
    if (len > 0 && data[len - 1] == '\n') {
        data[len - 1] = '\0';
        len--;
    }

    printf("Framed output: [%zu]%s\n", len, data);
    return 0;
}
