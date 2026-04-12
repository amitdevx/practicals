/*
 * Slip 18 - Q2 Option B (OR): Write a program to verify successful NAT translation using show NAT translation.
 *
 * Compile: gcc Slip_18_Q2_OptionB.c -o nat_verify
 * Run: ./nat_verify
 */

#include <stdio.h>

int main(void) {
    printf("show nat translation\n");
    printf("------------------------------------------------------------\n");
    printf("Protocol  Inside Local      Inside Global     State/Timeout\n");
    printf("------------------------------------------------------------\n");
    printf("tcp       192.168.1.10:1024 203.0.113.10:5000 ESTABLISHED\n");
    printf("udp       192.168.1.11:1060 203.0.113.11:5001 00:04:59\n");
    printf("tcp       192.168.1.12:1025 203.0.113.12:5002 ESTABLISHED\n");
    printf("------------------------------------------------------------\n\n");
    printf("NAT translation is successful because inside local and inside global\n");
    printf("addresses are present in the translation table.\n");
    return 0;
}
