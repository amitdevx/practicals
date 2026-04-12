/*
 * Slip 2 - Q2 Option B: Character Count Framing
 *
 * Compile: gcc Slip_02_Q2_OptionB.c -o char_count
 * Run: ./char_count
 */

#include <stdio.h>
#include <string.h>

int main(void) {
    char data[256];

    printf("Character Count Framing\n");
    printf("=======================\n");
    printf("Enter data: ");
    fgets(data, sizeof(data), stdin);

    size_t len = strlen(data);
    if (len > 0 && data[len - 1] == '\n') {
        data[len - 1] = '\0';
        len--;
    }

    printf("\nFramed output:\n");
    printf("[%zu]%s\n", len, data);
    printf("Total frame size (count + data): %zu\n", len + 1);

    return 0;
}
