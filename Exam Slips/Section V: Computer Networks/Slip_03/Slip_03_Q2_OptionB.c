/*
 * Slip 3 - Q2 Option B: Private IP Range Checker
 * 
 * Compile: gcc Slip_03_Q2_OptionB.c -o private_ip
 * Run: ./private_ip
 */

#include <stdio.h>
#include <string.h>

int isPrivateIP(const char *ip) {
    int a, b, c, d;
    if (sscanf(ip, "%d.%d.%d.%d", &a, &b, &c, &d) != 4) return 0;
    if (a < 0 || a > 255 || b < 0 || b > 255 || c < 0 || c > 255 || d < 0 || d > 255) return 0;
    
    if (a == 10) return 1;
    if (a == 172 && b >= 16 && b <= 31) return 1;
    if (a == 192 && b == 168) return 1;
    if (a == 127) return 1;
    
    return 0;
}

int main() {
    char ip[50];
    int choice;
    
    while (1) {
        printf("\n1. Check IP  2. Show Ranges  3. Exit\nChoice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                printf("Enter IP: ");
                fgets(ip, 50, stdin);
                ip[strcspn(ip, "\n")] = '\0';
                printf("IP %s is %s\n", ip, isPrivateIP(ip) ? "PRIVATE" : "PUBLIC");
                break;
            case 2:
                printf("\nPrivate IP Ranges:\n");
                printf("10.0.0.0 to 10.255.255.255\n");
                printf("172.16.0.0 to 172.31.255.255\n");
                printf("192.168.0.0 to 192.168.255.255\n");
                printf("127.0.0.0 to 127.255.255.255 (Loopback)\n");
                break;
            case 3:
                return 0;
        }
    }
}
