/*
 * Slip 14 - Q2 Option A: Write a program to implements Static Routing
 * Simulation.
 *
 * Compile: gcc Slip_14_Q2_OptionA.c -o static_routing
 * Run: ./static_routing
 */

#include <stdio.h>

int main(void) {
    printf("Static Routing Simulation\n");
    printf("========================\n\n");
    printf("Route 192.168.1.0/24 via 10.0.0.1\n");
    printf("Route 172.16.0.0/16 via 10.0.0.2\n");
    printf("Default route 0.0.0.0/0 via 10.0.0.254\n");

    return 0;
}
