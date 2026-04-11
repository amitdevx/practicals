/*
 * Slip 19 - Q2 Option B: Latency Analysis
 * 
 * Calculates network latency and delay.
 * 
 * Compile: gcc Slip_19_Q2_OptionB.c -o latency
 * Run: ./latency
 */

#include <stdio.h>

int main() {
    double distance = 100, speed = 200000;
    double propagation_delay = distance / speed;
    
    double transmission_rate = 1000000;
    int packet_size = 1000;
    double transmission_delay = (packet_size * 8) / transmission_rate;
    
    double processing_delay = 0.001;
    double queueing_delay = 0.002;
    
    double total = propagation_delay + transmission_delay + processing_delay + queueing_delay;
    
    printf("Latency Analysis\n");
    printf("================\n");
    printf("Propagation delay: %.6lf ms\n", propagation_delay * 1000);
    printf("Transmission delay: %.6lf ms\n", transmission_delay * 1000);
    printf("Processing delay: %.3lf ms\n", processing_delay * 1000);
    printf("Queueing delay: %.3lf ms\n", queueing_delay * 1000);
    printf("Total latency: %.6lf ms\n", total * 1000);
    
    return 0;
}
