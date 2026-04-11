/*
 * Slip 15 - Q2 Option A: Password Security with Special Characters
 * 
 * Validates password strength.
 * 
 * Compile: gcc Slip_15_Q2_OptionA.c -o password_check
 * Run: ./password_check
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char pwd[100];
    int upper = 0, lower = 0, digit = 0, special = 0;
    
    printf("Password Security Checker\n");
    printf("=========================\n");
    printf("Enter password: ");
    scanf("%s", pwd);
    
    int len = strlen(pwd);
    
    if (len < 8) {
        printf("Error: Min 8 characters\n");
        return 1;
    }
    
    for (int i = 0; pwd[i]; i++) {
        if (isupper(pwd[i])) upper = 1;
        else if (islower(pwd[i])) lower = 1;
        else if (isdigit(pwd[i])) digit = 1;
        else if (ispunct(pwd[i])) special = 1;
    }
    
    printf("\nAnalysis:\n");
    printf("Length: %d\n", len);
    printf("Uppercase: %s\n", upper ? "Yes" : "No");
    printf("Lowercase: %s\n", lower ? "Yes" : "No");
    printf("Digit: %s\n", digit ? "Yes" : "No");
    printf("Special: %s\n", special ? "Yes" : "No");
    
    if (upper && lower && digit && special) {
        printf("\nResult: Strong!\n");
    } else {
        printf("\nResult: Weak!\n");
    }
    
    return 0;
}
