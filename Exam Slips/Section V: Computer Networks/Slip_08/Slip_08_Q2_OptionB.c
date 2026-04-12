/*
 * Slip 8 - Q2 Option B: Write a program to set up dynamic routing protocols
 * such as RIP, EIGRP or OSPF.
 *
 * Compile: gcc Slip_08_Q2_OptionB.c -o routing
 * Run: ./routing
 */

#include <stdio.h>

int main(void) {
    printf("Dynamic Routing Protocol Setup\n");
    printf("==============================\n\n");
    printf("Example RIP configuration:\n");
    printf("router rip\n");
    printf("version 2\n");
    printf("network 192.168.1.0\n");
    printf("network 10.0.0.0\n");
    printf("no auto-summary\n\n");
    printf("This can also be adapted for EIGRP or OSPF as required.\n");

    return 0;
}
