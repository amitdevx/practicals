/*
 * Slip 11 - Q2 Option B: Write a C program to simulate the Stop-and-Wait
 * ARQ protocol.
 *
 * Compile: gcc Slip_11_Q2_OptionB.c -o stop_and_wait
 * Run: ./stop_and_wait
 */

#include <stdio.h>

int main(void) {
    int frames;

    printf("Stop-and-Wait ARQ Simulation\n");
    printf("=============================\n");
    printf("Enter number of frames to transmit: ");
    scanf("%d", &frames);

    for (int i = 1; i <= frames; i++) {
        printf("Frame %d sent\n", i);
        printf("ACK %d received\n", i);
    }

    printf("All frames transmitted successfully.\n");
    return 0;
}
