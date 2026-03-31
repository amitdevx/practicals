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
    
    // Display analysis header
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║              PASSWORD SECURITY ANALYSIS                       ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║ Password Length: %-4d characters                              ║\n", length);
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║ CRITERIA                              STATUS                  ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    
    // Check minimum length requirement
    if (length >= MIN_PASSWORD_LEN) {
        printf("║ [✓] Minimum length (≥8 characters)    PASSED                 ║\n");
        score++;
    } else {
        printf("║ [✗] Minimum length (≥8 characters)    FAILED (need %d more)   ║\n", 
               MIN_PASSWORD_LEN - length);
    }
    
    // Check uppercase requirement
    if (hasUppercase) {
        printf("║ [✓] Contains uppercase letter (A-Z)   PASSED                 ║\n");
        score++;
    } else {
        printf("║ [✗] Contains uppercase letter (A-Z)   FAILED                 ║\n");
    }
    
    // Check lowercase requirement
    if (hasLowercase) {
        printf("║ [✓] Contains lowercase letter (a-z)   PASSED                 ║\n");
        score++;
    } else {
        printf("║ [✗] Contains lowercase letter (a-z)   FAILED                 ║\n");
    }
    
    // Check digit requirement
    if (hasDigit) {
        printf("║ [✓] Contains digit (0-9)              PASSED                 ║\n");
        score++;
    } else {
        printf("║ [✗] Contains digit (0-9)              FAILED                 ║\n");
    }
    
    // Check special character requirement
    if (hasSpecial) {
        printf("║ [✓] Contains special character        PASSED                 ║\n");
        score++;
    } else {
        printf("║ [✗] Contains special character        FAILED                 ║\n");
    }
    
    // Display strength meter
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║ STRENGTH SCORE: %d/5                                          ║\n", score);
    printf("║                                                              ║\n");
    
    // Visual strength bar
    printf("║ Strength Meter: [");
    for (int i = 0; i < 5; i++) {
        if (i < score) {
            printf("██");
        } else {
            printf("░░");
        }
    }
    printf("]                          ║\n");
    
    printf("║                                                              ║\n");
    
    // Display overall assessment
    if (score == 5) {
        printf("║ ★★★★★ EXCELLENT - Your password is VERY STRONG!           ║\n");
        printf("║         All security criteria have been met.              ║\n");
    } else if (score == 4) {
        printf("║ ★★★★☆ GOOD - Your password is STRONG                      ║\n");
        printf("║         Consider adding missing criteria for best security║\n");
    } else if (score == 3) {
        printf("║ ★★★☆☆ FAIR - Your password is MEDIUM strength             ║\n");
        printf("║         Adding more criteria will improve security.       ║\n");
    } else if (score == 2) {
        printf("║ ★★☆☆☆ POOR - Your password is WEAK                        ║\n");
        printf("║         This password is easy to crack. Please improve it.║\n");
    } else {
        printf("║ ★☆☆☆☆ CRITICAL - Your password is VERY WEAK               ║\n");
        printf("║         This password offers minimal protection!          ║\n");
    }
    
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    
    // Provide recommendations if password is not strong
    if (score < 5) {
        printf("\n📋 RECOMMENDATIONS:\n");
        printf("───────────────────\n");
        
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

// Function to display program header
void displayHeader() {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║           PASSWORD SECURITY CHECKER v1.0                      ║\n");
    printf("║       Validates passwords for security best practices         ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
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
        
        // Analyze and display password strength
        checkPasswordStrength(password);
        
        // Ask if user wants to check another password
        printf("\n───────────────────────────────────────────────────────────────\n");
        printf("Would you like to check another password? (y/n): ");
        scanf(" %c", &choice);
        getchar();  // Clear newline from buffer
        printf("\n");
        
    } while (choice == 'y' || choice == 'Y');
    
    printf("Thank you for using Password Security Checker!\n");
    printf("Stay secure! 🔐\n\n");
    
    return 0;
}

/*
 * SAMPLE OUTPUT:
 * ==============
 * 
 * ╔══════════════════════════════════════════════════════════════╗
 * ║           PASSWORD SECURITY CHECKER v1.0                      ║
 * ║       Validates passwords for security best practices         ║
 * ╚══════════════════════════════════════════════════════════════╝
 * 
 * Enter password to check: MySecure@123
 * 
 * ╔══════════════════════════════════════════════════════════════╗
 * ║              PASSWORD SECURITY ANALYSIS                       ║
 * ╠══════════════════════════════════════════════════════════════╣
 * ║ Password Length: 12   characters                              ║
 * ╠══════════════════════════════════════════════════════════════╣
 * ║ [✓] Minimum length (≥8 characters)    PASSED                 ║
 * ║ [✓] Contains uppercase letter (A-Z)   PASSED                 ║
 * ║ [✓] Contains lowercase letter (a-z)   PASSED                 ║
 * ║ [✓] Contains digit (0-9)              PASSED                 ║
 * ║ [✓] Contains special character        PASSED                 ║
 * ╠══════════════════════════════════════════════════════════════╣
 * ║ STRENGTH SCORE: 5/5                                          ║
 * ║ Strength Meter: [██████████]                                  ║
 * ║ ★★★★★ EXCELLENT - Your password is VERY STRONG!              ║
 * ╚══════════════════════════════════════════════════════════════╝
 * 
 * ---
 * 
 * Enter password to check: password
 * 
 * ╔══════════════════════════════════════════════════════════════╗
 * ║              PASSWORD SECURITY ANALYSIS                       ║
 * ╠══════════════════════════════════════════════════════════════╣
 * ║ Password Length: 8    characters                              ║
 * ╠══════════════════════════════════════════════════════════════╣
 * ║ [✓] Minimum length (≥8 characters)    PASSED                 ║
 * ║ [✗] Contains uppercase letter (A-Z)   FAILED                 ║
 * ║ [✓] Contains lowercase letter (a-z)   PASSED                 ║
 * ║ [✗] Contains digit (0-9)              FAILED                 ║
 * ║ [✗] Contains special character        FAILED                 ║
 * ╠══════════════════════════════════════════════════════════════╣
 * ║ STRENGTH SCORE: 2/5                                          ║
 * ║ Strength Meter: [████░░░░░░]                                  ║
 * ║ ★★☆☆☆ POOR - Your password is WEAK                           ║
 * ╚══════════════════════════════════════════════════════════════╝
 * 
 * 📋 RECOMMENDATIONS:
 * ───────────────────
 *   • Include at least one UPPERCASE letter (A-Z)
 *   • Include at least one digit (0-9)
 *   • Include at least one special character (!@#$%^&*...)
 */
