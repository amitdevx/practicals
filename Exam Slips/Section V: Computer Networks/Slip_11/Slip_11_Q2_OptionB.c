/*
 * Slip 11 - Q2 Option B (OR): Configure Hostname & Passwords
 * 
 * Simulates switch password configuration.
 * 
 * Compile: gcc Slip_11_Q2_OptionB.c -o config
 * Run: ./config
 */

#include <stdio.h>
#include <string.h>

int main() {
    char host[50], enable[50], secret[50];
    
    printf("Switch Configuration\n");
    printf("====================\n\n");
    
    printf("hostname: ");
    fgets(host, 50, stdin);
    host[strcspn(host, "\n")] = '\0';
    
    printf("enable password: ");
    fgets(enable, 50, stdin);
    enable[strcspn(enable, "\n")] = '\0';
    
    printf("secret password: ");
    fgets(secret, 50, stdin);
    secret[strcspn(secret, "\n")] = '\0';
    
    printf("\nApplied Configuration:\n");
    printf("hostname %s\n", host);
    printf("enable password [set]\n");
    printf("enable secret [encrypted]\n");
    
    return 0;
}
