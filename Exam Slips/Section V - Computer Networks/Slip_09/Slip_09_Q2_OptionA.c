/*
 * Slip 9 - Q2 Option A: Write a program to determine IP address class.
 *
 * Compile: gcc Slip_09_Q2_OptionA.c -o ip_class
 * Run: ./ip_class
 */

#include <stdio.h>

int main(void) {
    int a, b, c, d;

    printf("IP Address Class Determination\n");
    printf("==============================\n");
    printf("Enter IP address (a.b.c.d): ");

    if (scanf("%d.%d.%d.%d", &a, &b, &c, &d) != 4) {
        printf("Invalid input.\n");
        return 1;
    }

    if (a >= 1 && a <= 126) {
        printf("Class A\n");
    } else if (a >= 128 && a <= 191) {
        printf("Class B\n");
    } else if (a >= 192 && a <= 223) {
        printf("Class C\n");
    } else if (a >= 224 && a <= 239) {
        printf("Class D\n");
    } else {
        printf("Class E\n");
    }

    return 0;
}
