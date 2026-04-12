/*
 * Slip 12 - Q2 Option B: Write a program to configure hostname, enable
 * password and encrypted secret password.
 *
 * Compile: gcc Slip_12_Q2_OptionB.c -o switch_config
 * Run: ./switch_config
 */

#include <stdio.h>
#include <string.h>

int main(void) {
    char hostname[50], enable_password[50], secret_password[50];

    printf("Switch Configuration\n");
    printf("====================\n");
    printf("Enter hostname: ");
    fgets(hostname, sizeof(hostname), stdin);
    hostname[strcspn(hostname, "\n")] = '\0';

    printf("Enter enable password: ");
    fgets(enable_password, sizeof(enable_password), stdin);
    enable_password[strcspn(enable_password, "\n")] = '\0';

    printf("Enter encrypted secret password: ");
    fgets(secret_password, sizeof(secret_password), stdin);
    secret_password[strcspn(secret_password, "\n")] = '\0';

    printf("\nhostname %s\n", hostname);
    printf("enable password %s\n", enable_password);
    printf("enable secret %s\n", secret_password);
    printf("Configuration verified successfully.\n");

    return 0;
}
