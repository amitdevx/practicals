/*
 * Slip 4 - Q2 Option B: Write a C program that checks private IP ranges.
 *
 * Compile: gcc Slip_04_Q2_OptionB.c -o private_ip
 * Run: ./private_ip
 */

#include <stdio.h>

int is_private_ip(int a, int b, int c, int d) {
    if (a == 10) return 1;
    if (a == 172 && b >= 16 && b <= 31) return 1;
    if (a == 192 && b == 168) return 1;
    return 0;
}

int main(void) {
    int a, b, c, d;

    printf("Private IP Range Checker\n");
    printf("========================\n");
    printf("Enter IP address (a.b.c.d): ");

    if (scanf("%d.%d.%d.%d", &a, &b, &c, &d) != 4) {
        printf("Invalid input.\n");
        return 1;
    }

    if (a < 0 || a > 255 || b < 0 || b > 255 || c < 0 || c > 255 || d < 0 || d > 255) {
        printf("Invalid IP address.\n");
        return 1;
    }

    if (is_private_ip(a, b, c, d)) {
        printf("The IP address is PRIVATE.\n");
    } else {
        printf("The IP address is PUBLIC.\n");
    }

    return 0;
}
