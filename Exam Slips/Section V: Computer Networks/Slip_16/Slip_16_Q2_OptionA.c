/*
 * Slip 16 - Q2 Option A: Password Security with Special Characters
 * 
 * Checks password strength including special characters.
 * 
 * Compile: gcc Slip_16_Q2_OptionA.c -o password_security
 * Run: ./password_security
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char password[100];
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
    
    printf("Password Security Checker with Special Characters\n");
    printf("=================================================\n");
    printf("Requirements:\n");
    printf("- Minimum 8 characters\n");
    printf("- At least one uppercase letter (A-Z)\n");
    printf("- At least one lowercase letter (a-z)\n");
    printf("- At least one digit (0-9)\n");
    printf("- At least one special character (!@#$%%^&*...)\n\n");
    
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
    
    printf("\nPassword Analysis:\n");
    printf("─────────────────\n");
    printf("Length: %d characters\n", length);
    printf("Uppercase: %s\n", hasUpper ? "Yes" : "No");
    printf("Lowercase: %s\n", hasLower ? "Yes" : "No");
    printf("Digit: %s\n", hasDigit ? "Yes" : "No");
    printf("Special: %s\n", hasSpecial ? "Yes" : "No");
    
    printf("\nResult:\n");
    if (hasUpper && hasLower && hasDigit && hasSpecial) {
        printf("✓ Strong Password!\n");
    } else {
        printf("✗ Weak Password - Missing:\n");
        if (!hasUpper) printf("  • Uppercase letter\n");
        if (!hasLower) printf("  • Lowercase letter\n");
        if (!hasDigit) printf("  • Digit\n");
        if (!hasSpecial) printf("  • Special character\n");
    }
    
    return 0;
}
