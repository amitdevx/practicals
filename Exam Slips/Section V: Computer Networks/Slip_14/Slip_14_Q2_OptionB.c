/*
 * Slip 14 - Q2 Option B: Bandwidth Calculator
 * 
 * Uses Shannon capacity formula: C = B * log2(1 + SNR)
 * 
 * Compile: gcc Slip_14_Q2_OptionB.c -o bandwidth -lm
 * Run: ./bandwidth
 */

#include <stdio.h>
#include <math.h>

int main() {
    double bandwidth, snr;
    
    printf("Enter bandwidth (Hz): ");
    scanf("%lf", &bandwidth);
    printf("Enter Signal-to-Noise ratio: ");
    scanf("%lf", &snr);
    
    double capacity = bandwidth * log2(1 + snr);
    
    printf("Channel capacity: %.2lf bps\n", capacity);
    printf("Kilobits/sec: %.2lf\n", capacity / 1000);
    
    return 0;
}
