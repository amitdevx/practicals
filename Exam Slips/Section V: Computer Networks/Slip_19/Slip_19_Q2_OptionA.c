/*
 * Slip 19 - Q2 Option A: Bandwidth Allocation
 * 
 * Allocates bandwidth among multiple users.
 * 
 * Compile: gcc Slip_19_Q2_OptionA.c -o bandwidth_alloc
 * Run: ./bandwidth_alloc
 */

#include <stdio.h>

int main() {
    int total_bw = 1000, users = 4;
    int per_user = total_bw / users;
    
    printf("Bandwidth Allocation\n");
    printf("====================\n");
    printf("Total Bandwidth: %d Mbps\n", total_bw);
    printf("Number of users: %d\n", users);
    printf("Per-user allocation: %d Mbps\n", per_user);
    
    printf("\nUser Allocations:\n");
    for (int i = 1; i <= users; i++) {
        printf("User %d: %d Mbps\n", i, per_user);
    }
    
    return 0;
}
