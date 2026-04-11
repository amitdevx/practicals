/*
 * Slip 3 - Q2 Option A: Phishing Email Detection
 * 
 * Compile: gcc Slip_03_Q2_OptionA.c -o phishing
 * Run: ./phishing
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isPhishing(const char *email) {
    const char *keywords[] = {"verify", "urgent", "confirm", "click", "login", "update", "action"};
    int count = 0, suspicion = 0;
    char lower[500];
    
    strcpy(lower, email);
    for (int i = 0; lower[i]; i++) lower[i] = tolower(lower[i]);
    
    for (int i = 0; i < 7; i++) {
        if (strstr(lower, keywords[i])) count++;
    }
    
    if (strstr(lower, "http://")) suspicion++;
    if (strstr(lower, "click here")) suspicion++;
    
    return (count >= 2 || suspicion >= 1);
}

int main() {
    FILE *fp;
    char line[500], filename[100];
    int choice;
    
    while (1) {
        printf("\n1. Check Email File  2. Manual Entry  3. Exit\nChoice: ");
        scanf("%d", &choice);
        getchar();
        
        if (choice == 3) break;
        
        if (choice == 1) {
            printf("Filename: ");
            fgets(filename, 100, stdin);
            filename[strcspn(filename, "\n")] = '\0';
            fp = fopen(filename, "r");
            if (fp) {
                while (fgets(line, 500, fp)) {
                    if (isPhishing(line)) {
                        printf("PHISHING: %s", line);
                    }
                }
                fclose(fp);
            } else {
                printf("File not found\n");
            }
        } else {
            printf("Enter email text: ");
            fgets(line, 500, stdin);
            printf("Result: %s\n", isPhishing(line) ? "LIKELY PHISHING" : "LIKELY SAFE");
        }
    }
    return 0;
}
