/*
 * Slip 17 - Q2 Option A: NAT (Network Address Translation) System
 * 
 * Simulates NAT translation table.
 * 
 * Compile: gcc Slip_17_Q2_OptionA.c -o nat_system
 * Run: ./nat_system
 */

#include <stdio.h>
#include <string.h>

typedef struct {
    char private_ip[20];
    char public_ip[20];
    int port;
} NATEntry;

int main() {
    printf("NAT (Network Address Translation) System\n");
    printf("========================================\n\n");
    
    NATEntry nat_table[3];
    
    strcpy(nat_table[0].private_ip, "192.168.1.100");
    strcpy(nat_table[0].public_ip, "203.0.113.50");
    nat_table[0].port = 8080;
    
    strcpy(nat_table[1].private_ip, "192.168.1.101");
    strcpy(nat_table[1].public_ip, "203.0.113.51");
    nat_table[1].port = 8081;
    
    strcpy(nat_table[2].private_ip, "192.168.1.102");
    strcpy(nat_table[2].public_ip, "203.0.113.52");
    nat_table[2].port = 8082;
    
    printf("NAT Translation Table:\n");
    printf("─────────────────────────────────────────\n");
    printf("Private IP      | Public IP       | Port\n");
    printf("─────────────────────────────────────────\n");
    
    for (int i = 0; i < 3; i++) {
        printf("%-15s | %-15s | %d\n",
            nat_table[i].private_ip,
            nat_table[i].public_ip,
            nat_table[i].port);
    }
    
    printf("\nNAT Function:\n");
    printf("Private network 192.168.1.0/24\n");
    printf("Translated to public IP 203.0.113.0/24\n");
    printf("Allows multiple internal IPs using single public IP\n");
    
    return 0;
}
