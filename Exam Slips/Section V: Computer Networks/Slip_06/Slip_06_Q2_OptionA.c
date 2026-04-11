/*
 * Slip 6 - Q2 Option A: Configure Hostname & Passwords
 * 
 * Simulates switch configuration with security settings.
 * 
 * Compile: gcc Slip_06_Q2_OptionA.c -o switch_config
 * Run: ./switch_config
 */

#include <stdio.h>
#include <string.h>

int main() {
    char hostname[50], enable_pwd[50], secret_pwd[50];
    
    printf("Switch Configuration\n");
    printf("====================\n\n");
    
    printf("Enter hostname: ");
    fgets(hostname, 50, stdin);
    hostname[strcspn(hostname, "\n")] = '\0';
    
    printf("Enter enable password: ");
    fgets(enable_pwd, 50, stdin);
    enable_pwd[strcspn(enable_pwd, "\n")] = '\0';
    
    printf("Enter secret password: ");
    fgets(secret_pwd, 50, stdin);
    secret_pwd[strcspn(secret_pwd, "\n")] = '\0';
    
    printf("\nConfiguration:\n");
    printf("──────────────\n");
    printf("hostname %s\n", hostname);
    printf("enable password [%s]\n", enable_pwd);
    printf("enable secret [encrypted]\n");
    printf("\nStatus: Configured\n");
    
    return 0;
}
