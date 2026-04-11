/*
 * Slip 7 - Q2 Option A: Verify Configuration using show running-config & ping
 * 
 * Simulates configuration verification.
 * 
 * Compile: gcc Slip_07_Q2_OptionA.c -o verify_config
 * Run: ./verify_config
 */

#include <stdio.h>

int main() {
    printf("Configuration Verification\n");
    printf("==========================\n\n");
    
    printf("show running-config\n");
    printf("───────────────────\n");
    printf("hostname Switch1\n");
    printf("enable password pass123\n");
    printf("interface FastEthernet 0/1\n");
    printf(" ip address 192.168.1.1 255.255.255.0\n");
    printf(" no shutdown\n\n");
    
    printf("ping 192.168.1.2\n");
    printf("─────────────────\n");
    printf("Reply from 192.168.1.2: bytes=32 time=2ms TTL=64\n");
    printf("Reply from 192.168.1.2: bytes=32 time=1ms TTL=64\n");
    printf("Ping successful!\n");
    
    return 0;
}
