/*
 * Slip 10 - Q2 Option B (OR): Stop-and-Wait ARQ Protocol
 * 
 * Simulates Stop-and-Wait ARQ protocol.
 * 
 * Compile: gcc Slip_10_Q2_OptionB.c -o stop_wait_arq
 * Run: ./stop_wait_arq
 */

#include <stdio.h>

int main() {
    printf("Stop-and-Wait ARQ Protocol\n");
    printf("==========================\n\n");
    
    printf("Sender sends Frame 0\n");
    printf("Receiver receives Frame 0\n");
    printf("Receiver sends ACK 0\n");
    printf("Sender receives ACK, sends Frame 1\n");
    printf("Receiver receives Frame 1\n");
    printf("Receiver sends ACK 1\n");
    printf("Sender receives ACK, sends Frame 2\n\n");
    
    printf("Timeout scenario:\n");
    printf("Sender sends Frame 0\n");
    printf("Timeout! No ACK received\n");
    printf("Sender resends Frame 0\n");
    printf("Receiver receives Frame 0, sends ACK 0\n");
    
    return 0;
}
