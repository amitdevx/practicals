/*
 * Slip 13 - Q2 Option B: Write a program to version that saves an Initial
 * Switch Configuration into a text file.
 *
 * Compile: gcc Slip_13_Q2_OptionB.c -o switch_config
 * Run: ./switch_config
 */

#include <stdio.h>

int main(void) {
    FILE *file = fopen("switch_config.txt", "w");

    if (file == NULL) {
        printf("Unable to create switch_config.txt\n");
        return 1;
    }

    fprintf(file, "Initial Switch Configuration\n");
    fprintf(file, "Hostname: Switch1\n");
    fprintf(file, "Enable Password: class\n");
    fprintf(file, "Enable Secret: encrypted\n");
    fclose(file);

    printf("Initial switch configuration saved to switch_config.txt\n");
    return 0;
}
