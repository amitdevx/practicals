/*
 * Slip 13 - Q2 Option B: Save Initial Switch Configuration to Text File
 *
 * Description: This program generates and saves an initial Cisco switch
 *              configuration to a text file for documentation/backup.
 *
 * Features:
 * - Generates complete switch configuration
 * - Includes hostname, passwords, interfaces, VLANs
 * - Saves configuration with timestamp
 * - User can customize basic parameters
 *
 * Compile: gcc -o switch_config Slip_13_Q2_OptionB.c
 * Run:     ./switch_config
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_VLANS 10
#define MAX_INTERFACES 24
#define CONFIG_FILE "switch_config.txt"

// Structure for VLAN configuration
typedef struct {
    int vlanId;
    char name[50];
    char description[100];
} VLAN;

// Structure for Interface configuration
typedef struct {
    char name[20];
    char description[100];
    int vlanId;
    int isEnabled;
    char mode[20]; // access or trunk
} Interface;

// Structure for Switch configuration
typedef struct {
    char hostname[50];
    char enableSecret[50];
    char consolePassword[50];
    char vtyPassword[50];
    char bannerMotd[200];
    char domainName[50];
    char managementIP[20];
    char subnetMask[20];
    char defaultGateway[20];
    VLAN vlans[MAX_VLANS];
    int vlanCount;
    Interface interfaces[MAX_INTERFACES];
    int interfaceCount;
} SwitchConfig;

// Function prototypes
void initializeSwitchConfig(SwitchConfig *config);
void getUserInput(SwitchConfig *config);
int saveConfigToFile(SwitchConfig *config, const char *filename);
void writeConfigHeader(FILE *fp, SwitchConfig *config);
void writeBasicConfig(FILE *fp, SwitchConfig *config);
void writeVLANConfig(FILE *fp, SwitchConfig *config);
void writeInterfaceConfig(FILE *fp, SwitchConfig *config);
void writeLineConfig(FILE *fp, SwitchConfig *config);
void writeSecurityConfig(FILE *fp, SwitchConfig *config);
void displayConfigSummary(SwitchConfig *config);
void printBanner(void);
char* getCurrentTimestamp(void);

int main() {
    SwitchConfig switchConfig;
    int choice;

    printBanner();

    initializeSwitchConfig(&switchConfig);

    printf("\n>>> Configuration Options:\n");
    printf("    1. Use Default Configuration\n");
    printf("    2. Enter Custom Configuration\n");
    printf("    Enter choice (1-2): ");
    scanf("%d", &choice);
    getchar(); // Clear newline

    if (choice == 2) {
        getUserInput(&switchConfig);
    }

    displayConfigSummary(&switchConfig);

    // Save configuration to file
    if (saveConfigToFile(&switchConfig, CONFIG_FILE)) {
        printf("\n>>> Configuration saved successfully to: %s\n", CONFIG_FILE);
    } else {
        printf("\n>>> Error: Failed to save configuration!\n");
        return 1;
    }

    printf("\n>>> Press Enter to exit...");
    getchar();

    return 0;
}

void printBanner(void) {
    printf("\n");
    printf("====================================================================\n");
    printf("       CISCO SWITCH INITIAL CONFIGURATION GENERATOR\n");
    printf("              Save Configuration to Text File\n");
    printf("====================================================================\n");
}

// Get current timestamp
char* getCurrentTimestamp(void) {
    static char timestamp[100];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", t);
    return timestamp;
}

void initializeSwitchConfig(SwitchConfig *config) {
    // Basic settings
    strcpy(config->hostname, "Switch1");
    strcpy(config->enableSecret, "cisco123");
    strcpy(config->consolePassword, "console123");
    strcpy(config->vtyPassword, "vty123");
    strcpy(config->bannerMotd, "Authorized Access Only!");
    strcpy(config->domainName, "local.network");
    strcpy(config->managementIP, "192.168.1.254");
    strcpy(config->subnetMask, "255.255.255.0");
    strcpy(config->defaultGateway, "192.168.1.1");

    config->vlanCount = 3;

    config->vlans[0].vlanId = 10;
    strcpy(config->vlans[0].name, "ENGINEERING");
    strcpy(config->vlans[0].description, "Engineering Department");

    config->vlans[1].vlanId = 20;
    strcpy(config->vlans[1].name, "SALES");
    strcpy(config->vlans[1].description, "Sales Department");

    config->vlans[2].vlanId = 30;
    strcpy(config->vlans[2].name, "MANAGEMENT");
    strcpy(config->vlans[2].description, "Network Management");

    config->interfaceCount = 8;

    // FastEthernet interfaces
    for (int i = 0; i < 8; i++) {
        sprintf(config->interfaces[i].name, "FastEthernet0/%d", i + 1);
        config->interfaces[i].isEnabled = 1;
        strcpy(config->interfaces[i].mode, "access");

        if (i < 3) {
            config->interfaces[i].vlanId = 10;
            sprintf(config->interfaces[i].description, "Engineering PC %d", i + 1);
        } else if (i < 6) {
            config->interfaces[i].vlanId = 20;
            sprintf(config->interfaces[i].description, "Sales PC %d", i - 2);
        } else {
            config->interfaces[i].vlanId = 30;
            sprintf(config->interfaces[i].description, "Management Device %d", i - 5);
        }
    }
}

// Get user input for custom configuration
void getUserInput(SwitchConfig *config) {
    printf("\n>>> Enter Custom Configuration:\n");
    printf("-----------------------------------\n");

    printf("Hostname [%s]: ", config->hostname);
    fgets(config->hostname, sizeof(config->hostname), stdin);
    config->hostname[strcspn(config->hostname, "\n")] = 0;
    if (strlen(config->hostname) == 0) strcpy(config->hostname, "Switch1");

    printf("Enable Secret [%s]: ", config->enableSecret);
    fgets(config->enableSecret, sizeof(config->enableSecret), stdin);
    config->enableSecret[strcspn(config->enableSecret, "\n")] = 0;
    if (strlen(config->enableSecret) == 0) strcpy(config->enableSecret, "cisco123");

    printf("Management IP [%s]: ", config->managementIP);
    fgets(config->managementIP, sizeof(config->managementIP), stdin);
    config->managementIP[strcspn(config->managementIP, "\n")] = 0;
    if (strlen(config->managementIP) == 0) strcpy(config->managementIP, "192.168.1.254");

    printf("Default Gateway [%s]: ", config->defaultGateway);
    fgets(config->defaultGateway, sizeof(config->defaultGateway), stdin);
    config->defaultGateway[strcspn(config->defaultGateway, "\n")] = 0;
    if (strlen(config->defaultGateway) == 0) strcpy(config->defaultGateway, "192.168.1.1");

    printf("\n>>> Using default VLANs and interfaces.\n");
}

void displayConfigSummary(SwitchConfig *config) {
    printf("\n");
    printf("====================================================================\n");
    printf("                  CONFIGURATION SUMMARY\n");
    printf("====================================================================\n");
    printf("\n");
    printf("    Hostname:           %s\n", config->hostname);
    printf("    Management IP:      %s\n", config->managementIP);
    printf("    Subnet Mask:        %s\n", config->subnetMask);
    printf("    Default Gateway:    %s\n", config->defaultGateway);
    printf("    Domain Name:        %s\n", config->domainName);
    printf("    VLANs Configured:   %d\n", config->vlanCount);
    printf("    Interfaces:         %d\n", config->interfaceCount);
    printf("\n");
    printf("    VLANs:\n");
    for (int i = 0; i < config->vlanCount; i++) {
        printf("      - VLAN %d: %s\n", config->vlans[i].vlanId, config->vlans[i].name);
    }
    printf("\n");
    printf("====================================================================\n");
}

// Save configuration to file
int saveConfigToFile(SwitchConfig *config, const char *filename) {
    FILE *fp = fopen(filename, "w");

    if (fp == NULL) {
        perror("Error opening file");
        return 0;
    }

    writeConfigHeader(fp, config);
    writeBasicConfig(fp, config);
    writeSecurityConfig(fp, config);
    writeVLANConfig(fp, config);
    writeInterfaceConfig(fp, config);
    writeLineConfig(fp, config);

    // End of configuration
    fprintf(fp, "!\n");
    fprintf(fp, "!--------------------------------------------------------------\n");
    fprintf(fp, "! END OF CONFIGURATION\n");
    fprintf(fp, "!--------------------------------------------------------------\n");
    fprintf(fp, "end\n");

    fclose(fp);
    return 1;
}

// Write configuration header
void writeConfigHeader(FILE *fp, SwitchConfig *config) {
    fprintf(fp, "!==============================================================\n");
    fprintf(fp, "! CISCO SWITCH INITIAL CONFIGURATION\n");
    fprintf(fp, "! Hostname: %s\n", config->hostname);
    fprintf(fp, "! Generated: %s\n", getCurrentTimestamp());
    fprintf(fp, "! Generator: Switch Configuration Utility v1.0\n");
    fprintf(fp, "!==============================================================\n");
    fprintf(fp, "!\n");
    fprintf(fp, "! This configuration file contains the initial setup for a\n");
    fprintf(fp, "! Cisco Catalyst switch. Copy and paste into switch console.\n");
    fprintf(fp, "!\n");
    fprintf(fp, "!==============================================================\n");
    fprintf(fp, "!\n");
}

// Write basic configuration
void writeBasicConfig(FILE *fp, SwitchConfig *config) {
    fprintf(fp, "!--------------------------------------------------------------\n");
    fprintf(fp, "! BASIC CONFIGURATION\n");
    fprintf(fp, "!--------------------------------------------------------------\n");
    fprintf(fp, "!\n");
    fprintf(fp, "! Enter privileged mode\n");
    fprintf(fp, "enable\n");
    fprintf(fp, "!\n");
    fprintf(fp, "! Enter configuration mode\n");
    fprintf(fp, "configure terminal\n");
    fprintf(fp, "!\n");
    fprintf(fp, "! Set hostname\n");
    fprintf(fp, "hostname %s\n", config->hostname);
    fprintf(fp, "!\n");
    fprintf(fp, "! Set domain name\n");
    fprintf(fp, "ip domain-name %s\n", config->domainName);
    fprintf(fp, "!\n");
    fprintf(fp, "! Set banner message\n");
    fprintf(fp, "banner motd # %s #\n", config->bannerMotd);
    fprintf(fp, "!\n");
    fprintf(fp, "! Disable DNS lookup to prevent delays\n");
    fprintf(fp, "no ip domain-lookup\n");
    fprintf(fp, "!\n");
    fprintf(fp, "! Set default gateway for management access\n");
    fprintf(fp, "ip default-gateway %s\n", config->defaultGateway);
    fprintf(fp, "!\n");
}

// Write security configuration
void writeSecurityConfig(FILE *fp, SwitchConfig *config) {
    fprintf(fp, "!--------------------------------------------------------------\n");
    fprintf(fp, "! SECURITY CONFIGURATION\n");
    fprintf(fp, "!--------------------------------------------------------------\n");
    fprintf(fp, "!\n");
    fprintf(fp, "! Set enable secret (encrypted)\n");
    fprintf(fp, "enable secret %s\n", config->enableSecret);
    fprintf(fp, "!\n");
    fprintf(fp, "! Enable password encryption\n");
    fprintf(fp, "service password-encryption\n");
    fprintf(fp, "!\n");
    fprintf(fp, "! Set minimum password length\n");
    fprintf(fp, "security passwords min-length 8\n");
    fprintf(fp, "!\n");
    fprintf(fp, "! Block login after failed attempts\n");
    fprintf(fp, "login block-for 120 attempts 3 within 60\n");
    fprintf(fp, "!\n");
}

// Write VLAN configuration
void writeVLANConfig(FILE *fp, SwitchConfig *config) {
    fprintf(fp, "!--------------------------------------------------------------\n");
    fprintf(fp, "! VLAN CONFIGURATION\n");
    fprintf(fp, "!--------------------------------------------------------------\n");
    fprintf(fp, "!\n");

    for (int i = 0; i < config->vlanCount; i++) {
        fprintf(fp, "! Create VLAN %d\n", config->vlans[i].vlanId);
        fprintf(fp, "vlan %d\n", config->vlans[i].vlanId);
        fprintf(fp, " name %s\n", config->vlans[i].name);
        fprintf(fp, "exit\n");
        fprintf(fp, "!\n");
    }

    fprintf(fp, "! Configure management VLAN interface (VLAN 1)\n");
    fprintf(fp, "interface vlan 1\n");
    fprintf(fp, " description Management Interface\n");
    fprintf(fp, " ip address %s %s\n", config->managementIP, config->subnetMask);
    fprintf(fp, " no shutdown\n");
    fprintf(fp, "exit\n");
    fprintf(fp, "!\n");
}

// Write interface configuration
void writeInterfaceConfig(FILE *fp, SwitchConfig *config) {
    fprintf(fp, "!--------------------------------------------------------------\n");
    fprintf(fp, "! INTERFACE CONFIGURATION\n");
    fprintf(fp, "!--------------------------------------------------------------\n");
    fprintf(fp, "!\n");

    for (int i = 0; i < config->interfaceCount; i++) {
        fprintf(fp, "interface %s\n", config->interfaces[i].name);
        fprintf(fp, " description %s\n", config->interfaces[i].description);
        fprintf(fp, " switchport mode %s\n", config->interfaces[i].mode);

        if (strcmp(config->interfaces[i].mode, "access") == 0) {
            fprintf(fp, " switchport access vlan %d\n", config->interfaces[i].vlanId);
        }

        fprintf(fp, " spanning-tree portfast\n");

        if (config->interfaces[i].isEnabled) {
            fprintf(fp, " no shutdown\n");
        } else {
            fprintf(fp, " shutdown\n");
        }

        fprintf(fp, "exit\n");
        fprintf(fp, "!\n");
    }

    // Configure trunk port
    fprintf(fp, "! Configure trunk port for uplink\n");
    fprintf(fp, "interface GigabitEthernet0/1\n");
    fprintf(fp, " description Uplink to Core Switch\n");
    fprintf(fp, " switchport mode trunk\n");
    fprintf(fp, " switchport trunk allowed vlan all\n");
    fprintf(fp, " no shutdown\n");
    fprintf(fp, "exit\n");
    fprintf(fp, "!\n");
}

// Write line configuration (console and VTY)
void writeLineConfig(FILE *fp, SwitchConfig *config) {
    fprintf(fp, "!--------------------------------------------------------------\n");
    fprintf(fp, "! LINE CONFIGURATION (Console and VTY)\n");
    fprintf(fp, "!--------------------------------------------------------------\n");
    fprintf(fp, "!\n");

    // Console configuration
    fprintf(fp, "! Console line configuration\n");
    fprintf(fp, "line console 0\n");
    fprintf(fp, " password %s\n", config->consolePassword);
    fprintf(fp, " login\n");
    fprintf(fp, " logging synchronous\n");
    fprintf(fp, " exec-timeout 5 0\n");
    fprintf(fp, "exit\n");
    fprintf(fp, "!\n");

    // VTY configuration
    fprintf(fp, "! VTY (Telnet/SSH) line configuration\n");
    fprintf(fp, "line vty 0 4\n");
    fprintf(fp, " password %s\n", config->vtyPassword);
    fprintf(fp, " login\n");
    fprintf(fp, " transport input ssh telnet\n");
    fprintf(fp, " exec-timeout 5 0\n");
    fprintf(fp, "exit\n");
    fprintf(fp, "!\n");
    fprintf(fp, "line vty 5 15\n");
    fprintf(fp, " password %s\n", config->vtyPassword);
    fprintf(fp, " login\n");
    fprintf(fp, " transport input ssh telnet\n");
    fprintf(fp, " exec-timeout 5 0\n");
    fprintf(fp, "exit\n");
    fprintf(fp, "!\n");

    // SSH configuration
    fprintf(fp, "! Generate RSA key for SSH (run in privileged mode)\n");
    fprintf(fp, "! crypto key generate rsa modulus 2048\n");
    fprintf(fp, "!\n");

    // Save configuration
    fprintf(fp, "! Save configuration to startup-config\n");
    fprintf(fp, "exit\n");
    fprintf(fp, "write memory\n");
    fprintf(fp, "!\n");
    fprintf(fp, "! OR use: copy running-config startup-config\n");
    fprintf(fp, "!\n");
}
