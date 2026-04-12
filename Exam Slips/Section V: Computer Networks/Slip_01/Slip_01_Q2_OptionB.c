/*
 * Slip 1 - Q2 Option B: Write a C program to check password is strong or weak.
 *
 * Compile: gcc Slip_01_Q2_OptionB.c -o password_check
 * Run: ./password_check
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char pwd[256];
    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;

    printf("Password Strength Checker\n");
    printf("=========================\n");
    printf("Enter password: ");
    scanf("%255s", pwd);

    int len = (int)strlen(pwd);
    for (int i = 0; pwd[i] != '\0'; i++) {
        unsigned char ch = (unsigned char)pwd[i];
        if (isupper(ch)) {
            has_upper = 1;
        } else if (islower(ch)) {
            has_lower = 1;
        } else if (isdigit(ch)) {
            has_digit = 1;
        } else if (ispunct(ch)) {
            has_special = 1;
        }
    }

    printf("\nChecks:\n");
    printf("Length >= 8  : %s\n", len >= 8 ? "Yes" : "No");
    printf("Uppercase    : %s\n", has_upper ? "Yes" : "No");
    printf("Lowercase    : %s\n", has_lower ? "Yes" : "No");
    printf("Digit        : %s\n", has_digit ? "Yes" : "No");
    printf("Special char : %s\n", has_special ? "Yes" : "No");

    if (len >= 8 && has_upper && has_lower && has_digit && has_special) {
        printf("\nResult: Strong password\n");
    } else {
        printf("\nResult: Weak password\n");
    }

    return 0;
}
