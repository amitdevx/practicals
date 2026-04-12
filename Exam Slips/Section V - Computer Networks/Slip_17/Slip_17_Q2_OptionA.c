/*
 * Slip 17 - Q2 Option A: Write a C program for password security with
 * Special Characters that includes special character checks along with
 * uppercase, lowercase, digit, and length rules.
 *
 * Compile: gcc Slip_17_Q2_OptionA.c -o password_check
 * Run: ./password_check
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char pwd[256];
    int upper = 0, lower = 0, digit = 0, special = 0;

    printf("Password Security Checker\n");
    printf("=========================\n");
    printf("Enter password: ");
    scanf("%255s", pwd);

    int len = (int)strlen(pwd);
    for (int i = 0; pwd[i] != '\0'; i++) {
        unsigned char ch = (unsigned char)pwd[i];
        if (isupper(ch)) upper = 1;
        else if (islower(ch)) lower = 1;
        else if (isdigit(ch)) digit = 1;
        else if (ispunct(ch)) special = 1;
    }

    printf("Length >= 8  : %s\n", len >= 8 ? "Yes" : "No");
    printf("Uppercase    : %s\n", upper ? "Yes" : "No");
    printf("Lowercase    : %s\n", lower ? "Yes" : "No");
    printf("Digit        : %s\n", digit ? "Yes" : "No");
    printf("Special char : %s\n", special ? "Yes" : "No");

    if (len >= 8 && upper && lower && digit && special) {
        printf("Result: Strong password\n");
    } else {
        printf("Result: Weak password\n");
    }

    return 0;
}
