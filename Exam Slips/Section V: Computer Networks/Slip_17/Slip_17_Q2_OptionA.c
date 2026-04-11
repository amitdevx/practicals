/*
 * Slip 17 - Option A: Password Security Checker with Special Characters
 *
 * This program validates password strength by checking:
 * 1. Minimum length (8+ characters)
 * 2. Uppercase letters (A-Z)
 * 3. Lowercase letters (a-z)
 * 4. Digits (0-9)
 * 5. Special characters (!@#$%^&*... etc.)
 *
 * Compile: gcc Slip_17_Q2_OptionA.c -o password_checker
 * Run: ./password_checker
 */

#include <stdio.h>
#include <string.h>

#define MAX_PASSWORD_LEN 100
#define MIN_PASSWORD_LEN 8

// Function to check if character is a special character
int isSpecialChar(char ch) {
    const char *specialChars = "!@#$%^&*()-_=+[]{}|;:',.<>?/`~\\\"";

    while (*specialChars) {
        if (ch == *specialChars) {
            return 1;  // Found special character
        }
        specialChars++;
    }
    return 0;  // Not a special character
}

// Function to check password strength
void checkPasswordStrength(const char *password) {
    int length = 0;
    int hasUppercase = 0;
    int hasLowercase = 0;
    int hasDigit = 0;
    int hasSpecial = 0;
    int score = 0;

    // Analyze each character in the password
    for (int i = 0; password[i] != '\0'; i++) {
        char ch = password[i];
        length++;

        // Check for uppercase letter
        if (ch >= 'A' && ch <= 'Z') {
            hasUppercase = 1;
        }
        // Check for lowercase letter
        else if (ch >= 'a' && ch <= 'z') {
            hasLowercase = 1;
        }
        // Check for digit
        else if (ch >= '0' && ch <= '9') {
            hasDigit = 1;
        }
        // Check for special character
        else if (isSpecialChar(ch)) {
            hasSpecial = 1;
        }
    }

    printf("\n");


    // Check minimum length requirement
    if (length >= MIN_PASSWORD_LEN) {

        score++;
    } else {

    }

    // Check uppercase requirement
    if (hasUppercase) {

        score++;
    } else {

    }

    // Check lowercase requirement
    if (hasLowercase) {

        score++;
    } else {

    }

    // Check digit requirement
    if (hasDigit) {

        score++;
    } else {

    }

    // Check special character requirement
    if (hasSpecial) {

        score++;
    } else {

    }

    // Display strength meter


    // Visual strength bar

    for (int i = 0; i < 5; i++) {
        if (i < score) {
            printf("██");
        } else {
            printf("░░");
        }
    }


    if (score == 5) {


    } else if (score == 4) {


    } else if (score == 3) {


    } else if (score == 2) {


    } else {


    }


    // Provide recommendations if password is not strong
    if (score < 5) {
        printf("\n📋 RECOMMENDATIONS:\n");


        if (length < MIN_PASSWORD_LEN) {
            printf("  • Add %d more character(s) to meet minimum length\n",
                   MIN_PASSWORD_LEN - length);
        }
        if (!hasUppercase) {
            printf("  • Include at least one UPPERCASE letter (A-Z)\n");
        }
        if (!hasLowercase) {
            printf("  • Include at least one lowercase letter (a-z)\n");
        }
        if (!hasDigit) {
            printf("  • Include at least one digit (0-9)\n");
        }
        if (!hasSpecial) {
            printf("  • Include at least one special character (!@#$%%^&*...)\n");
        }

        printf("\n💡 TIP: A strong password like 'MyP@ss123!' is easier to\n");
        printf("   remember and provides excellent security.\n");
    }
}

void displayHeader() {
    printf("\n");


    printf("\n");
    printf("Requirements for a STRONG password:\n");
    printf("  • Minimum 8 characters\n");
    printf("  • At least one uppercase letter (A-Z)\n");
    printf("  • At least one lowercase letter (a-z)\n");
    printf("  • At least one digit (0-9)\n");
    printf("  • At least one special character (!@#$%%^&*...)\n");
    printf("\n");
}

int main() {
    char password[MAX_PASSWORD_LEN];
    char choice;

    displayHeader();

    do {
        // Get password from user
        printf("Enter password to check: ");

        // Read password (including spaces)
        if (fgets(password, MAX_PASSWORD_LEN, stdin) != NULL) {
            // Remove trailing newline
            size_t len = strlen(password);
            if (len > 0 && password[len - 1] == '\n') {
                password[len - 1] = '\0';
            }
        }

        // Check if password is empty
        if (strlen(password) == 0) {
            printf("\n⚠️  Password cannot be empty. Please try again.\n\n");
            continue;
        }

        checkPasswordStrength(password);

        // Ask if user wants to check another password

        printf("Would you like to check another password? (y/n): ");
        scanf(" %c", &choice);
        getchar();  // Clear newline from buffer
        printf("\n");

    } while (choice == 'y' || choice == 'Y');

    printf("Thank you for using Password Security Checker!\n");
    printf("Stay secure! 🔐\n\n");

    return 0;
}
