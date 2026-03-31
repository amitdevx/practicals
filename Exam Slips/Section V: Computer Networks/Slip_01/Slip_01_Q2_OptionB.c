/*
 * Slip 1 - Q2 Option B: Password Strength Checker
 * Checks if a password is Strong or Weak based on multiple criteria
 * 
 * Compile: gcc Slip_01_Q2_OptionB.c -o password_check
 * Run: ./password_check
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PASSWORD_LENGTH 100

/* ==================== STRENGTH CRITERIA ==================== */

/*
 * Password Strength Criteria:
 * 1. Length >= 8 characters (minimum requirement)
 * 2. Contains uppercase letters (A-Z)
 * 3. Contains lowercase letters (a-z)
 * 4. Contains digits (0-9)
 * 5. Contains special characters (!@#$%^&*...)
 * 6. No common patterns (sequences, repeated chars)
 */

/* ==================== HELPER FUNCTIONS ==================== */

// Check if password contains uppercase letter
int hasUppercase(const char *password) {
    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) {
            return 1;
        }
    }
    return 0;
}

// Check if password contains lowercase letter
int hasLowercase(const char *password) {
    for (int i = 0; password[i] != '\0'; i++) {
        if (islower(password[i])) {
            return 1;
        }
    }
    return 0;
}

// Check if password contains digit
int hasDigit(const char *password) {
    for (int i = 0; password[i] != '\0'; i++) {
        if (isdigit(password[i])) {
            return 1;
        }
    }
    return 0;
}

// Check if password contains special character
int hasSpecialChar(const char *password) {
    const char *specialChars = "!@#$%^&*()_+-=[]{}|;':\",./<>?`~";
    for (int i = 0; password[i] != '\0'; i++) {
        if (strchr(specialChars, password[i]) != NULL) {
            return 1;
        }
    }
    return 0;
}

// Check for sequential characters (abc, 123)
int hasSequence(const char *password) {
    int len = strlen(password);
    for (int i = 0; i < len - 2; i++) {
        // Check for ascending sequence
        if (password[i] + 1 == password[i + 1] && 
            password[i + 1] + 1 == password[i + 2]) {
            return 1;
        }
        // Check for descending sequence
        if (password[i] - 1 == password[i + 1] && 
            password[i + 1] - 1 == password[i + 2]) {
            return 1;
        }
    }
    return 0;
}

// Check for repeated characters (aaa, 111)
int hasRepeating(const char *password) {
    int len = strlen(password);
    for (int i = 0; i < len - 2; i++) {
        if (password[i] == password[i + 1] && 
            password[i + 1] == password[i + 2]) {
            return 1;
        }
    }
    return 0;
}

// Count character types present
int countCharTypes(const char *password) {
    int types = 0;
    if (hasUppercase(password)) types++;
    if (hasLowercase(password)) types++;
    if (hasDigit(password)) types++;
    if (hasSpecialChar(password)) types++;
    return types;
}

/* ==================== MAIN STRENGTH CHECK ==================== */

typedef struct {
    int score;
    char strength[20];
    int length;
    int hasUpper;
    int hasLower;
    int hasNum;
    int hasSpecial;
    int hasSeq;
    int hasRepeat;
} PasswordAnalysis;

PasswordAnalysis analyzePassword(const char *password) {
    PasswordAnalysis result;
    
    result.length = strlen(password);
    result.hasUpper = hasUppercase(password);
    result.hasLower = hasLowercase(password);
    result.hasNum = hasDigit(password);
    result.hasSpecial = hasSpecialChar(password);
    result.hasSeq = hasSequence(password);
    result.hasRepeat = hasRepeating(password);
    
    // Calculate score
    result.score = 0;
    
    // Length scoring (up to 3 points)
    if (result.length >= 8) result.score++;
    if (result.length >= 12) result.score++;
    if (result.length >= 16) result.score++;
    
    // Character type scoring (up to 4 points)
    if (result.hasUpper) result.score++;
    if (result.hasLower) result.score++;
    if (result.hasNum) result.score++;
    if (result.hasSpecial) result.score++;
    
    // Penalties for weak patterns
    if (result.hasSeq) result.score--;
    if (result.hasRepeat) result.score--;
    
    // Determine strength level
    if (result.length < 6) {
        strcpy(result.strength, "VERY WEAK");
    } else if (result.score <= 2) {
        strcpy(result.strength, "WEAK");
    } else if (result.score <= 4) {
        strcpy(result.strength, "MEDIUM");
    } else if (result.score <= 5) {
        strcpy(result.strength, "STRONG");
    } else {
        strcpy(result.strength, "VERY STRONG");
    }
    
    return result;
}

/* ==================== SIMPLE CHECK (Strong/Weak) ==================== */

void checkPasswordSimple(const char *password) {
    int len = strlen(password);
    int upper = hasUppercase(password);
    int lower = hasLowercase(password);
    int digit = hasDigit(password);
    int special = hasSpecialChar(password);
    
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║         PASSWORD STRENGTH CHECK        ║\n");
    printf("╚════════════════════════════════════════╝\n");
    
    printf("\nPassword: ");
    // Print masked password
    for (int i = 0; i < len; i++) {
        printf("*");
    }
    printf(" (%d characters)\n", len);
    
    // Criteria check
    printf("\n┌─────────────────────────────────────────┐\n");
    printf("│ Criteria                      Status    │\n");
    printf("├─────────────────────────────────────────┤\n");
    printf("│ Length >= 8 characters        %s      │\n", len >= 8 ? "✓ PASS" : "✗ FAIL");
    printf("│ Contains uppercase (A-Z)      %s      │\n", upper ? "✓ PASS" : "✗ FAIL");
    printf("│ Contains lowercase (a-z)      %s      │\n", lower ? "✓ PASS" : "✗ FAIL");
    printf("│ Contains digit (0-9)          %s      │\n", digit ? "✓ PASS" : "✗ FAIL");
    printf("│ Contains special char         %s      │\n", special ? "✓ PASS" : "✗ FAIL");
    printf("└─────────────────────────────────────────┘\n");
    
    // Simple Strong/Weak determination
    // Strong if: length >= 8 AND at least 3 character types
    int typeCount = upper + lower + digit + special;
    
    printf("\n═══════════════════════════════════════════\n");
    if (len >= 8 && typeCount >= 3) {
        printf("        Result: ★★★ STRONG PASSWORD ★★★\n");
    } else {
        printf("        Result: ⚠  WEAK PASSWORD ⚠\n");
    }
    printf("═══════════════════════════════════════════\n");
    
    // Recommendations
    if (len < 8 || typeCount < 3) {
        printf("\n📝 Recommendations to strengthen password:\n");
        if (len < 8) printf("   • Increase length to at least 8 characters\n");
        if (!upper) printf("   • Add uppercase letters (A-Z)\n");
        if (!lower) printf("   • Add lowercase letters (a-z)\n");
        if (!digit) printf("   • Add numbers (0-9)\n");
        if (!special) printf("   • Add special characters (!@#$%%^&*)\n");
    }
}

/* ==================== DETAILED CHECK ==================== */

void checkPasswordDetailed(const char *password) {
    PasswordAnalysis analysis = analyzePassword(password);
    
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║       DETAILED PASSWORD ANALYSIS       ║\n");
    printf("╚════════════════════════════════════════╝\n");
    
    printf("\nPassword Length: %d characters\n", analysis.length);
    printf("Strength Score: %d/7\n", analysis.score > 0 ? analysis.score : 0);
    
    printf("\n┌─────────────────────────────────────────┐\n");
    printf("│ Analysis Results                        │\n");
    printf("├─────────────────────────────────────────┤\n");
    printf("│ Uppercase Letters:    %s               │\n", analysis.hasUpper ? "Yes ✓" : "No  ✗");
    printf("│ Lowercase Letters:    %s               │\n", analysis.hasLower ? "Yes ✓" : "No  ✗");
    printf("│ Numbers:              %s               │\n", analysis.hasNum ? "Yes ✓" : "No  ✗");
    printf("│ Special Characters:   %s               │\n", analysis.hasSpecial ? "Yes ✓" : "No  ✗");
    printf("│ Sequential Pattern:   %s               │\n", analysis.hasSeq ? "Yes ⚠" : "No  ✓");
    printf("│ Repeated Characters:  %s               │\n", analysis.hasRepeat ? "Yes ⚠" : "No  ✓");
    printf("└─────────────────────────────────────────┘\n");
    
    // Visual strength meter
    printf("\nStrength Meter: [");
    int meterLength = 20;
    int filled = (analysis.score > 0 ? analysis.score : 0) * meterLength / 7;
    for (int i = 0; i < meterLength; i++) {
        if (i < filled) printf("█");
        else printf("░");
    }
    printf("] %s\n", analysis.strength);
    
    // Color-coded result (using text representation)
    printf("\n═══════════════════════════════════════════\n");
    printf("        Overall Strength: %s\n", analysis.strength);
    printf("═══════════════════════════════════════════\n");
}

/* ==================== TEST EXAMPLES ==================== */

void runTestExamples() {
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║         TEST EXAMPLES                  ║\n");
    printf("╚════════════════════════════════════════╝\n");
    
    const char *testPasswords[] = {
        "abc",
        "password",
        "Password1",
        "P@ssw0rd",
        "MyStr0ng!Pass",
        "Tr0ub4dor&3Horse",
        "aaaaaa",
        "123456",
        "abcdefgh"
    };
    
    int numTests = sizeof(testPasswords) / sizeof(testPasswords[0]);
    
    printf("\n%-20s %-8s %-15s\n", "Password", "Length", "Strength");
    printf("─────────────────────────────────────────────\n");
    
    for (int i = 0; i < numTests; i++) {
        PasswordAnalysis result = analyzePassword(testPasswords[i]);
        printf("%-20s %-8d %-15s\n", 
               testPasswords[i], 
               result.length, 
               result.strength);
    }
    
    printf("\n─────────────────────────────────────────────\n");
    printf("Note: Passwords shown in plain text for demo only.\n");
    printf("Never store or display real passwords in plain text!\n");
}

/* ==================== MAIN FUNCTION ==================== */

int main() {
    int choice;
    char password[MAX_PASSWORD_LENGTH];
    
    printf("\n╔══════════════════════════════════════════╗\n");
    printf("║     PASSWORD STRENGTH CHECKER            ║\n");
    printf("║     Check if password is Strong/Weak     ║\n");
    printf("╚══════════════════════════════════════════╝\n");
    
    while (1) {
        printf("\n┌──────────────────────────────────────┐\n");
        printf("│            MAIN MENU                 │\n");
        printf("├──────────────────────────────────────┤\n");
        printf("│  1. Check Password (Simple)          │\n");
        printf("│  2. Check Password (Detailed)        │\n");
        printf("│  3. Run Test Examples                │\n");
        printf("│  4. Exit                             │\n");
        printf("└──────────────────────────────────────┘\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline
        
        switch (choice) {
            case 1:
                printf("\nEnter password to check: ");
                fgets(password, MAX_PASSWORD_LENGTH, stdin);
                password[strcspn(password, "\n")] = '\0';
                checkPasswordSimple(password);
                break;
                
            case 2:
                printf("\nEnter password to check: ");
                fgets(password, MAX_PASSWORD_LENGTH, stdin);
                password[strcspn(password, "\n")] = '\0';
                checkPasswordDetailed(password);
                break;
                
            case 3:
                runTestExamples();
                break;
                
            case 4:
                printf("\nExiting program. Stay secure!\n");
                return 0;
                
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
    
    return 0;
}

/*
 * ==================== EXPLANATION ====================
 * 
 * PASSWORD STRENGTH CRITERIA:
 * 
 * A strong password should have:
 * 1. Minimum length of 8 characters (12-16 recommended)
 * 2. Mix of uppercase and lowercase letters
 * 3. At least one digit
 * 4. At least one special character
 * 5. No common patterns (sequences, repeated chars)
 * 
 * SCORING SYSTEM:
 * - Length >= 8:  +1 point
 * - Length >= 12: +1 point
 * - Length >= 16: +1 point
 * - Has uppercase: +1 point
 * - Has lowercase: +1 point
 * - Has digit:     +1 point
 * - Has special:   +1 point
 * - Has sequence:  -1 point (penalty)
 * - Has repeating: -1 point (penalty)
 * 
 * Maximum score: 7 points
 * 
 * STRENGTH LEVELS:
 * - Very Weak:   < 6 characters
 * - Weak:        score <= 2
 * - Medium:      score 3-4
 * - Strong:      score 5
 * - Very Strong: score 6-7
 * 
 * SIMPLE CHECK (Strong/Weak):
 * - STRONG: length >= 8 AND at least 3 character types
 * - WEAK:   otherwise
 * 
 * TIME COMPLEXITY: O(n) where n is password length
 * SPACE COMPLEXITY: O(1) - constant space for analysis
 * 
 * SECURITY NOTE:
 * This is a basic strength checker for educational purposes.
 * Real-world applications should also check against:
 * - Dictionary words
 * - Common passwords database
 * - Personal information
 * - Password breach databases
 */
