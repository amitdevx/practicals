/*
 * Slip 8 - Q2 Option A: Determine IP Address Class
 * 
 * Classifies IP addresses into classes A-E.
 * 
 * Compile: gcc Slip_08_Q2_OptionA.c -o ip_class
 * Run: ./ip_class
 */

#include <stdio.h>

int main() {
    int a, b, c, d;
    
    printf("IP Address Class Determination\n");
    printf("==============================\n");
    printf("Enter IP (e.g., 192.168.1.1): ");
    scanf("%d.%d.%d.%d", &a, &b, &c, &d);
    
    char *class;
    if (a >= 1 && a <= 126) class = "A";
    else if (a >= 128 && a <= 191) class = "B";
    else if (a >= 192 && a <= 223) class = "C";
    else if (a >= 224 && a <= 239) class = "D";
    else class = "E";
    
    printf("\nIP: %d.%d.%d.%d\n", a, b, c, d);
    printf("Class: %s\n", class);
    
    return 0;
}
