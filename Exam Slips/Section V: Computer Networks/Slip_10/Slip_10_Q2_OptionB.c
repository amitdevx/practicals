/*
 * Slip 10 - Q2 Option B: Subnetting and Supernetting Calculations
 *
 * Compile: gcc Slip_10_Q2_OptionB.c -o subnet_supernet
 * Run: ./subnet_supernet
 */

#include <stdio.h>

int main(void) {
    int prefix = 25;
    int base_class_c_prefix = 24;
    int network_bits = prefix;
    int host_bits = 32 - prefix;
    int networks = 1 << (prefix - base_class_c_prefix);
    int total_per_network = 1 << host_bits;
    int usable_per_network = total_per_network - 2;

    printf("Subnetting and Supernetting Report\n");
    printf("==================================\n\n");

    printf("Given network: 192.168.10.0/25 (Class C)\n");
    printf("Network bits: %d\n", network_bits);
    printf("Host bits: %d\n", host_bits);
    printf("Host bits available: %d\n", host_bits);
    printf("Number of networks: %d\n", networks);
    printf("Addresses per network: %d\n", total_per_network);
    printf("Assignable (usable) IPs per network: %d\n\n", usable_per_network);

    printf("Subnet table:\n");
    printf("1) 192.168.10.0/25   -> usable 192.168.10.1 to 192.168.10.126, broadcast 192.168.10.127\n");
    printf("2) 192.168.10.128/25 -> usable 192.168.10.129 to 192.168.10.254, broadcast 192.168.10.255\n\n");

    printf("Supernetting example:\n");
    printf("Combining the above two /25 networks gives one /24 supernet: 192.168.10.0/24\n");

    return 0;
}
