/*
 * Slip 1 - Q2 Option B: Password Strength Checker
 * 
 * Compile: gcc Slip_01_Q2_OptionB.c -o password
 * Run: ./password
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int hasUppercase(const char *pwd) {
    for (int i = 0; pwd[i]; i++) if (isupper(pwd[i])) return 1;
    return 0;
}

int hasLowercase(const char *pwd) {
    for (int i = 0; pwd[i]; i++) if (islower(pwd[i])) return 1;
    return 0;
}

int hasDigit(const char *pwd) {
    for (int i = 0; pwd[i]; i++) if (isdigit(pwd[i])) return 1;
    return 0;
}

int hasSpecial(const char *pwd) {
    const char *special = "!@#$%^&*()_+-=[]{}|;:',.<>?/`~";
    for (int i = 0; pwd[i]; i++) {
        if (strchr(special, pwd[i])) return 1;
    }
    return 0;
}

int hasSequence(const char *pwd) {
    int len = strlen(pwd);
    for (int i = 0; i < len - 2; i++) {
        if (pwd[i] + 1 == pwd[i+1] && pwd[i+1] + 1 == pwd[i+2]) return 1;
        if (pwd[i] - 1 == pwd[i+1] && pwd[i+1] - 1 == pwd[i+2]) return 1;
    }
    return 0;
}

int hasRepeating(const char *pwd) {
    int len = strlen(pwd);
    for (int i = 0; i < len - 2; i++) {
        if (pwd[i] == pwd[i+1] && pwd[i+1] == pwd[i+2]) return 1;
    }
    return 0;
}

void checkPassword(const char *pwd) {
    int len = strlen(pwd);
    int score = 0;
    
    if (len >= 8) score++;
    if (hasUppercase(pwd)) score++;
    if (hasLowercase(pwd)) score++;
    if (hasDigit(pwd)) score++;
    if (hasSpecial(pwd)) score++;
    if (!hasSequence(pwd)) score++;
    if (!hasRepeating(pwd)) score++;
    
    printf("\nPassword Analysis:\n");
    printf("Length: %d\n", len);
    printf("Uppercase: %s\n", hasUppercase(pwd) ? "Yes" : "No");
    printf("Lowercase: %s\n", hasLowercase(pwd) ? "Yes" : "No");
    printf("Digits: %s\n", hasDigit(pwd) ? "Yes" : "No");
    printf("Special: %s\n", hasSpecial(pwd) ? "Yes" : "No");
    printf("Sequential: %s\n", hasSequence(pwd) ? "Found" : "None");
    printf("Repeating: %s\n", hasRepeating(pwd) ? "Found" : "None");
    printf("Score: %d/7\n", score);
    
    if (score >= 6) printf("Strength: STRONG\n");
    else if (score >= 4) printf("Strength: MEDIUM\n");
    else printf("Strength: WEAK\n");
}

int main() {
    char pwd[100];
    
    while (1) {
        printf("\nEnter password (or 'quit'): ");
        fgets(pwd, 100, stdin);
        pwd[strcspn(pwd, "\n")] = '\0';
        
        if (strcmp(pwd, "quit") == 0) break;
        if (strlen(pwd) == 0) continue;
        
        checkPassword(pwd);
    }
    
    return 0;
}
