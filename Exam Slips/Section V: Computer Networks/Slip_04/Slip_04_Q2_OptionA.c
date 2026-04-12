/*
 * Slip 4 - Q2 Option A: Write a C program that reads an email from a file
 * and performs phishing pattern detection.
 *
 * Compile: gcc Slip_04_Q2_OptionA.c -o phishing_detection
 * Run: ./phishing_detection
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int suspicious(const char *line) {
    const char *keywords[] = {"urgent", "verify", "password", "login", "click", "bank", "update"};
    char lower[512];
    int score = 0;

    strncpy(lower, line, sizeof(lower) - 1);
    lower[sizeof(lower) - 1] = '\0';
    for (int i = 0; lower[i] != '\0'; i++) {
        lower[i] = (char)tolower((unsigned char)lower[i]);
    }

    for (int i = 0; i < 7; i++) {
        if (strstr(lower, keywords[i])) {
            score++;
        }
    }
    if (strstr(lower, "http://") || strstr(lower, "bit.ly") || strstr(lower, "tinyurl")) {
        score++;
    }

    return score >= 2;
}

int main(void) {
    char filename[128];
    char line[512];
    FILE *fp;
    int found = 0;

    printf("Phishing Pattern Detection\n");
    printf("==========================\n");
    printf("Enter email file name: ");
    scanf("%127s", filename);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Cannot open file.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (suspicious(line)) {
            printf("Suspicious line: %s", line);
            found = 1;
        }
    }

    fclose(fp);

    if (found) {
        printf("\nResult: Potential phishing content detected.\n");
    } else {
        printf("\nResult: No phishing pattern detected.\n");
    }

    return 0;
}
