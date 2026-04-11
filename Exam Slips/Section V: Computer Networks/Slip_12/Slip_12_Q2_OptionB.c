/*
 * Slip 12 - Q2 Option B: Initial Switch Configuration
 * 
 * Saves switch configuration to a text file.
 * 
 * Compile: gcc Slip_12_Q2_OptionB.c -o switch_config
 * Run: ./switch_config
 */

#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp = fopen("switch_config.txt", "w");
    
    if (!fp) {
        printf("Error: Cannot create file\n");
        return 1;
    }
    
    fprintf(fp, "=== INITIAL SWITCH CONFIGURATION ===\n\n");
    fprintf(fp, "Hostname: Switch1\n");
    fprintf(fp, "Enable Password: enabled\n");
    fprintf(fp, "Secret Password: configured\n\n");
    
    fprintf(fp, "VLAN Configuration:\n");
    fprintf(fp, "VLAN 1: default\n");
    fprintf(fp, "VLAN 10: Management\n");
    fprintf(fp, "VLAN 20: Users\n\n");
    
    fprintf(fp, "Port Configuration:\n");
    fprintf(fp, "Fa0/1-4: Access VLAN 20\n");
    fprintf(fp, "Fa0/5-8: Access VLAN 10\n");
    fprintf(fp, "Gi0/1: Trunk (VLAN all)\n\n");
    
    fprintf(fp, "Banner MOTD:\n");
    fprintf(fp, "Welcome to Network Lab\n");
    fprintf(fp, "Authorized access only\n\n");
    
    fprintf(fp, "IP Configuration:\n");
    fprintf(fp, "VLAN 1 IP: 192.168.1.1\n");
    fprintf(fp, "Subnet Mask: 255.255.255.0\n");
    fprintf(fp, "Default Gateway: 192.168.1.254\n");
    
    fclose(fp);
    
    printf("Configuration saved to switch_config.txt\n");
    printf("File contents:\n");
    printf("=======================================\n");
    
    fp = fopen("switch_config.txt", "r");
    char line[256];
    while (fgets(line, 256, fp)) {
        printf("%s", line);
    }
    fclose(fp);
    
    return 0;
}
