/*
 * Slip 15 - Q2 Option A: Write a program to Command-Line Phishing Simulation.
 *
 * Compile: gcc Slip_15_Q2_OptionA.c -o phishing_cli
 * Run: ./phishing_cli
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int suspicious(const char *text) {
    const char *keywords[] = {"urgent", "verify", "password", "login", "click", "bank", "update"};
    char lower[512];
    int score = 0;

    strncpy(lower, text, sizeof(lower) - 1);
    lower[sizeof(lower) - 1] = '\0';
    for (int i = 0; lower[i] != '\0'; i++) {
        lower[i] = (char)tolower((unsigned char)lower[i]);
    }

    for (int i = 0; i < 7; i++) {
        if (strstr(lower, keywords[i])) {
            score++;
        }
    }
    if (strstr(lower, "http://") || strstr(lower, "https://") || strstr(lower, "bit.ly")) {
        score++;
    }

    return score >= 2;
}

int main(void) {
    char text[512];

    printf("Command-Line Phishing Simulation\n");
    printf("=================================\n");
    printf("Enter message: ");
    fgets(text, sizeof(text), stdin);

    if (suspicious(text)) {
        printf("Result: Likely PHISHING\n");
    } else {
        printf("Result: Likely SAFE\n");
    }

    return 0;
}
