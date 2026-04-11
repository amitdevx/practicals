/*
 * Slip 17 - Q2 Option B: Password Strength Checker
 * 
 * Validates password complexity.
 * 
 * Compile: gcc Slip_17_Q2_OptionB.c -o password
 * Run: ./password
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char password[100];
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
    
    printf("Enter password: ");
    scanf("%s", password);
    
    int length = strlen(password);
    
    if (length < 8) {
        printf("Error: Password must be at least 8 characters.\n");
        return 1;
    }
    
    for (int i = 0; password[i]; i++) {
        if (isupper(password[i])) hasUpper = 1;
        else if (islower(password[i])) hasLower = 1;
        else if (isdigit(password[i])) hasDigit = 1;
        else if (ispunct(password[i])) hasSpecial = 1;
    }
    
    printf("\n--- Security Check ---\n");
    
    if (!hasUpper) printf("[-] Missing uppercase letter\n");
    if (!hasLower) printf("[-] Missing lowercase letter\n");
    if (!hasDigit) printf("[-] Missing digit\n");
    if (!hasSpecial) printf("[-] Missing special character\n");
    
    if (hasUpper && hasLower && hasDigit && hasSpecial) {
        printf("[+] Strong Password!\n");
    } else {
        printf("\nResult: Password is weak.\n");
    }
    
    return 0;
}
