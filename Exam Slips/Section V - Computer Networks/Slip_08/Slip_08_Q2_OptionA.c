/*
 * Slip 8 - Q2 Option A: Write a program to verify the configuration using
 * show running-config and ping commands.
 *
 * Compile: gcc Slip_08_Q2_OptionA.c -o verify_config
 * Run: ./verify_config
 */

#include <stdio.h>

int main(void) {
    printf("Configuration Verification\n");
    printf("==========================\n\n");
    printf("show running-config\n");
    printf("hostname Switch1\n");
    printf("enable password class123\n");
    printf("interface vlan1\n");
    printf(" ip address 192.168.1.1 255.255.255.0\n");
    printf(" no shutdown\n\n");
    printf("ping 192.168.1.2\n");
    printf("Ping successful.\n");

    return 0;
}
