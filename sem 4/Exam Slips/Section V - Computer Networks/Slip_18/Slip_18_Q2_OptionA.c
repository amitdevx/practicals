/*
 * Slip 18 - Q2 Option A (OR): Write a C program for Phishing Simulation.
 *
 * Compile: gcc Slip_18_Q2_OptionA.c -o phishing_sim
 * Run: ./phishing_sim
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int suspicious(const char *text) {
    const char *keywords[] = {"verify", "urgent", "password", "login", "click", "account", "bank", "update"};
    char lower[512];
    strncpy(lower, text, sizeof(lower) - 1);
    lower[sizeof(lower) - 1] = '\0';
    for (int i = 0; lower[i]; i++) {
        lower[i] = (char)tolower((unsigned char)lower[i]);
    }
    int score = 0;
    for (int i = 0; i < 8; i++) {
        if (strstr(lower, keywords[i])) score++;
    }
    if (strstr(lower, "http://") || strstr(lower, "bit.ly")) score++;
    return score >= 2;
}

int main(void) {
    char mail[512];
    printf("Phishing Simulation\n");
    printf("===================\n");
    printf("Enter email/message text: ");
    fgets(mail, sizeof(mail), stdin);
    printf("Result: %s\n", suspicious(mail) ? "Likely PHISHING" : "Likely SAFE");
    return 0;
}
