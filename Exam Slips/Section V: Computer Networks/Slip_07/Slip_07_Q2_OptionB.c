/*
 * Slip 07 - Q2 Option B: Router Configuration Simulation
 * 
 * Program simulates Cisco IOS router configuration:
 * - Configure hostname
 * - Set enable password (plaintext)
 * - Set encrypted secret password (MD5 hash simulation)
 * 
 * Compile: gcc Slip_07_Q2_OptionB.c -o router_config
 * Run: ./router_config
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 50
#define HASH_LEN 32

// Structure to hold router configuration
typedef struct {
    char hostname[MAX_LEN];
    char enable_password[MAX_LEN];
    char secret_password[MAX_LEN];       // Original secret
    char secret_hash[HASH_LEN + 1];      // Hashed secret
    int hostname_set;
    int enable_password_set;
    int secret_password_set;
} RouterConfig;

// Global router configuration
RouterConfig router = {"Router", "", "", "", 0, 0, 0};

// Simple hash function to simulate MD5 (educational purposes)
void simpleHash(const char *input, char *output) {
    unsigned long hash = 5381;
    int c;
    const char *str = input;
    
    // DJB2 hash algorithm (simulates MD5-like behavior)
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    
    // Convert to hex string (32 characters like MD5)
    sprintf(output, "%08lx%08lx%08lx%08lx", 
            hash, hash ^ 0xDEADBEEF, hash ^ 0xCAFEBABE, hash ^ 0x12345678);
}

// Display colored output (ANSI escape codes)
void printPrompt(const char *mode) {
    if (strcmp(mode, "user") == 0) {
        printf("\033[1;32m%s>\033[0m ", router.hostname);
    } else if (strcmp(mode, "privileged") == 0) {
        printf("\033[1;32m%s#\033[0m ", router.hostname);
    } else if (strcmp(mode, "config") == 0) {
        printf("\033[1;32m%s(config)#\033[0m ", router.hostname);
    }
}

// Display header
void displayHeader() {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║       CISCO IOS ROUTER CONFIGURATION SIMULATOR                ║\n");
    printf("║     Configure Hostname, Enable Password, Secret Password      ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n\n");
}

// Display help menu
void displayHelp() {
    printf("\n");
    printf("┌─────────────────────────────────────────────────────────────────┐\n");
    printf("│                    AVAILABLE COMMANDS                           │\n");
    printf("├─────────────────────────────────────────────────────────────────┤\n");
    printf("│  User EXEC Mode (Router>):                                      │\n");
    printf("│    enable          - Enter privileged EXEC mode                 │\n");
    printf("│    exit            - Exit the simulation                        │\n");
    printf("│                                                                 │\n");
    printf("│  Privileged EXEC Mode (Router#):                                │\n");
    printf("│    configure terminal - Enter global configuration mode         │\n");
    printf("│    show running-config - Display current configuration          │\n");
    printf("│    disable         - Return to user EXEC mode                   │\n");
    printf("│    exit            - Exit the simulation                        │\n");
    printf("│                                                                 │\n");
    printf("│  Global Configuration Mode (Router(config)#):                   │\n");
    printf("│    hostname <name>     - Set device hostname                    │\n");
    printf("│    enable password <pwd> - Set enable password (plaintext)      │\n");
    printf("│    enable secret <pwd>   - Set secret password (encrypted)      │\n");
    printf("│    exit               - Return to privileged EXEC mode          │\n");
    printf("│                                                                 │\n");
    printf("│  General:                                                       │\n");
    printf("│    ?              - Display this help menu                      │\n");
    printf("└─────────────────────────────────────────────────────────────────┘\n\n");
}

// Display running configuration
void showRunningConfig() {
    printf("\n");
    printf("Building configuration...\n\n");
    printf("Current configuration : %d bytes\n", 
           (int)(strlen(router.hostname) + strlen(router.enable_password) + strlen(router.secret_hash) + 100));
    printf("!\n");
    printf("version 15.1\n");
    printf("!\n");
    printf("hostname %s\n", router.hostname);
    printf("!\n");
    
    if (router.enable_password_set) {
        printf("enable password %s\n", router.enable_password);
    }
    
    if (router.secret_password_set) {
        printf("enable secret 5 $1$%s\n", router.secret_hash);
    }
    
    printf("!\n");
    printf("interface FastEthernet0/0\n");
    printf(" no ip address\n");
    printf(" shutdown\n");
    printf("!\n");
    printf("interface FastEthernet0/1\n");
    printf(" no ip address\n");
    printf(" shutdown\n");
    printf("!\n");
    printf("line con 0\n");
    printf("line aux 0\n");
    printf("line vty 0 4\n");
    printf(" login\n");
    printf("!\n");
    printf("end\n\n");
}

// User EXEC mode
int userExecMode() {
    char command[MAX_LEN];
    
    printf("\n%s console is now available.\n", router.hostname);
    printf("Press RETURN to get started.\n\n");
    
    while (1) {
        printPrompt("user");
        fgets(command, MAX_LEN, stdin);
        command[strcspn(command, "\n")] = 0;  // Remove newline
        
        if (strlen(command) == 0) continue;
        
        if (strcmp(command, "enable") == 0) {
            return 1;  // Go to privileged mode
        } else if (strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0) {
            return -1;  // Exit simulation
        } else if (strcmp(command, "?") == 0) {
            displayHelp();
        } else {
            printf("%% Unknown command or computer name, or unable to find computer address\n");
        }
    }
}

// Privileged EXEC mode
int privilegedExecMode() {
    char command[MAX_LEN];
    
    while (1) {
        printPrompt("privileged");
        fgets(command, MAX_LEN, stdin);
        command[strcspn(command, "\n")] = 0;
        
        if (strlen(command) == 0) continue;
        
        if (strcmp(command, "configure terminal") == 0 || 
            strcmp(command, "conf t") == 0) {
            printf("Enter configuration commands, one per line. End with CNTL/Z.\n");
            return 1;  // Go to config mode
        } else if (strcmp(command, "show running-config") == 0 ||
                   strcmp(command, "sh run") == 0) {
            showRunningConfig();
        } else if (strcmp(command, "disable") == 0) {
            return 0;  // Back to user mode
        } else if (strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0) {
            return -1;  // Exit simulation
        } else if (strcmp(command, "?") == 0) {
            displayHelp();
        } else {
            printf("%% Invalid input detected\n");
        }
    }
}

// Global Configuration mode
int globalConfigMode() {
    char command[MAX_LEN];
    char param[MAX_LEN];
    
    while (1) {
        printPrompt("config");
        fgets(command, MAX_LEN, stdin);
        command[strcspn(command, "\n")] = 0;
        
        if (strlen(command) == 0) continue;
        
        // Parse hostname command
        if (strncmp(command, "hostname ", 9) == 0) {
            strcpy(param, command + 9);
            if (strlen(param) > 0) {
                strcpy(router.hostname, param);
                router.hostname_set = 1;
                printf("\n  ✓ Hostname changed to: %s\n\n", router.hostname);
            } else {
                printf("%% Incomplete command.\n");
            }
        }
        // Parse enable password command
        else if (strncmp(command, "enable password ", 16) == 0) {
            strcpy(param, command + 16);
            if (strlen(param) > 0) {
                strcpy(router.enable_password, param);
                router.enable_password_set = 1;
                printf("\n  ✓ Enable password set (stored as plaintext)\n");
                printf("  ⚠ WARNING: This password is NOT encrypted!\n\n");
            } else {
                printf("%% Incomplete command.\n");
            }
        }
        // Parse enable secret command
        else if (strncmp(command, "enable secret ", 14) == 0) {
            strcpy(param, command + 14);
            if (strlen(param) > 0) {
                strcpy(router.secret_password, param);
                simpleHash(param, router.secret_hash);
                router.secret_password_set = 1;
                printf("\n  ✓ Secret password set (stored as MD5 hash)\n");
                printf("  ✓ Hash: $1$%s\n", router.secret_hash);
                printf("  ℹ Note: Secret password takes precedence over enable password\n\n");
            } else {
                printf("%% Incomplete command.\n");
            }
        }
        // Exit config mode
        else if (strcmp(command, "exit") == 0 || strcmp(command, "end") == 0) {
            return 0;  // Back to privileged mode
        }
        // Help
        else if (strcmp(command, "?") == 0) {
            displayHelp();
        }
        else {
            printf("%% Invalid input detected at '^' marker.\n");
        }
    }
}

// Interactive configuration wizard
void configurationWizard() {
    char input[MAX_LEN];
    
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║              QUICK CONFIGURATION WIZARD                       ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n\n");
    
    // Hostname
    printf("┌─────────────────────────────────────────────────────────────────┐\n");
    printf("│ Step 1: Configure Hostname                                      │\n");
    printf("│ The hostname identifies this device on the network              │\n");
    printf("└─────────────────────────────────────────────────────────────────┘\n");
    printf("  Enter hostname [Router]: ");
    fgets(input, MAX_LEN, stdin);
    input[strcspn(input, "\n")] = 0;
    if (strlen(input) > 0) {
        strcpy(router.hostname, input);
        router.hostname_set = 1;
    }
    printf("  ✓ Hostname set to: %s\n\n", router.hostname);
    
    // Enable Password
    printf("┌─────────────────────────────────────────────────────────────────┐\n");
    printf("│ Step 2: Configure Enable Password                               │\n");
    printf("│ Basic password (stored in PLAINTEXT - not secure!)              │\n");
    printf("└─────────────────────────────────────────────────────────────────┘\n");
    printf("  Enter enable password: ");
    fgets(input, MAX_LEN, stdin);
    input[strcspn(input, "\n")] = 0;
    if (strlen(input) > 0) {
        strcpy(router.enable_password, input);
        router.enable_password_set = 1;
        printf("  ✓ Enable password set: %s\n", router.enable_password);
        printf("  ⚠ WARNING: Stored as plaintext!\n\n");
    } else {
        printf("  ⊘ Enable password skipped\n\n");
    }
    
    // Secret Password
    printf("┌─────────────────────────────────────────────────────────────────┐\n");
    printf("│ Step 3: Configure Secret Password                               │\n");
    printf("│ Secure password (stored as MD5 hash - RECOMMENDED)              │\n");
    printf("└─────────────────────────────────────────────────────────────────┘\n");
    printf("  Enter secret password: ");
    fgets(input, MAX_LEN, stdin);
    input[strcspn(input, "\n")] = 0;
    if (strlen(input) > 0) {
        strcpy(router.secret_password, input);
        simpleHash(input, router.secret_hash);
        router.secret_password_set = 1;
        printf("  ✓ Secret password configured\n");
        printf("  ✓ MD5 Hash: $1$%s\n\n", router.secret_hash);
    } else {
        printf("  ⊘ Secret password skipped\n\n");
    }
    
    // Summary
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║              CONFIGURATION SUMMARY                            ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n\n");
    
    printf("  Equivalent Cisco IOS Commands:\n");
    printf("  ──────────────────────────────────────────────────────────────\n");
    printf("  Router> enable\n");
    printf("  Router# configure terminal\n");
    printf("  Router(config)# hostname %s\n", router.hostname);
    if (router.enable_password_set) {
        printf("  %s(config)# enable password %s\n", router.hostname, router.enable_password);
    }
    if (router.secret_password_set) {
        printf("  %s(config)# enable secret %s\n", router.hostname, router.secret_password);
    }
    printf("  %s(config)# exit\n", router.hostname);
    printf("  %s# copy running-config startup-config\n", router.hostname);
    printf("  ──────────────────────────────────────────────────────────────\n\n");
    
    showRunningConfig();
}

// Display password security information
void displayPasswordInfo() {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║           PASSWORD SECURITY INFORMATION                       ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n\n");
    
    printf("┌─────────────────────────────────────────────────────────────────┐\n");
    printf("│ Enable Password vs Secret Password                              │\n");
    printf("├─────────────────────────────────────────────────────────────────┤\n");
    printf("│                                                                 │\n");
    printf("│  ENABLE PASSWORD:                                               │\n");
    printf("│    • Command: enable password <password>                        │\n");
    printf("│    • Storage: PLAINTEXT (visible in config)                     │\n");
    printf("│    • Security: WEAK - easily readable                           │\n");
    printf("│    • Type 0 encryption                                          │\n");
    printf("│                                                                 │\n");
    printf("│  ENABLE SECRET:                                                 │\n");
    printf("│    • Command: enable secret <password>                          │\n");
    printf("│    • Storage: MD5 HASH (encrypted)                              │\n");
    printf("│    • Security: STRONG - cannot be reversed                      │\n");
    printf("│    • Type 5 encryption                                          │\n");
    printf("│                                                                 │\n");
    printf("│  PRIORITY: If both are set, SECRET takes precedence!            │\n");
    printf("│                                                                 │\n");
    printf("└─────────────────────────────────────────────────────────────────┘\n\n");
    
    printf("  Example in running-config:\n");
    printf("  ──────────────────────────────────────────────────────────────\n");
    printf("  enable password cisco123              <- Visible plaintext!\n");
    printf("  enable secret 5 $1$abc123xyz...       <- MD5 hash (secure)\n");
    printf("  ──────────────────────────────────────────────────────────────\n\n");
}

// Main menu
void displayMenu() {
    printf("\n");
    printf("┌─────────────────────────────────────────────────────────────────┐\n");
    printf("│                      MAIN MENU                                  │\n");
    printf("├─────────────────────────────────────────────────────────────────┤\n");
    printf("│   1. Quick Configuration Wizard (Guided Setup)                  │\n");
    printf("│   2. Interactive CLI Mode (Cisco IOS Simulation)                │\n");
    printf("│   3. View Password Security Information                         │\n");
    printf("│   4. Exit                                                       │\n");
    printf("└─────────────────────────────────────────────────────────────────┘\n");
    printf("  Enter choice (1-4): ");
}

// Interactive CLI mode
void interactiveCLI() {
    int mode = 0;  // 0=user, 1=privileged, 2=config
    int result;
    
    printf("\n");
    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("        Entering Cisco IOS Router Simulation Mode\n");
    printf("        Type '?' for help, 'exit' to quit\n");
    printf("═══════════════════════════════════════════════════════════════════\n");
    
    while (1) {
        switch (mode) {
            case 0:  // User EXEC
                result = userExecMode();
                if (result == -1) return;
                if (result == 1) mode = 1;
                break;
                
            case 1:  // Privileged EXEC
                result = privilegedExecMode();
                if (result == -1) return;
                if (result == 0) mode = 0;
                if (result == 1) mode = 2;
                break;
                
            case 2:  // Global Config
                result = globalConfigMode();
                if (result == 0) mode = 1;
                break;
        }
    }
}

// Main function
int main() {
    int choice;
    char input[10];
    
    displayHeader();
    displayPasswordInfo();
    
    while (1) {
        displayMenu();
        fgets(input, 10, stdin);
        choice = atoi(input);
        
        switch (choice) {
            case 1:
                // Reset configuration
                strcpy(router.hostname, "Router");
                router.enable_password[0] = '\0';
                router.secret_password[0] = '\0';
                router.secret_hash[0] = '\0';
                router.hostname_set = 0;
                router.enable_password_set = 0;
                router.secret_password_set = 0;
                
                configurationWizard();
                break;
                
            case 2:
                interactiveCLI();
                break;
                
            case 3:
                displayPasswordInfo();
                break;
                
            case 4:
                printf("\n  Thank you for using Router Configuration Simulator!\n\n");
                return 0;
                
            default:
                printf("\n  ⚠ Invalid choice. Please enter 1-4.\n");
        }
    }
    
    return 0;
}

/*
 * SAMPLE OUTPUT (Wizard Mode):
 * 
 * ╔═══════════════════════════════════════════════════════════════╗
 * ║              QUICK CONFIGURATION WIZARD                       ║
 * ╚═══════════════════════════════════════════════════════════════╝
 * 
 * Step 1: Configure Hostname
 *   Enter hostname [Router]: MyRouter
 *   ✓ Hostname set to: MyRouter
 * 
 * Step 2: Configure Enable Password
 *   Enter enable password: cisco123
 *   ✓ Enable password set: cisco123
 *   ⚠ WARNING: Stored as plaintext!
 * 
 * Step 3: Configure Secret Password
 *   Enter secret password: class456
 *   ✓ Secret password configured
 *   ✓ MD5 Hash: $1$8f14e45f...
 * 
 * CONFIGURATION SUMMARY:
 *   Equivalent Cisco IOS Commands:
 *   Router> enable
 *   Router# configure terminal
 *   Router(config)# hostname MyRouter
 *   MyRouter(config)# enable password cisco123
 *   MyRouter(config)# enable secret class456
 *   MyRouter(config)# exit
 * 
 * Running Configuration:
 * hostname MyRouter
 * enable password cisco123
 * enable secret 5 $1$8f14e45f...
 * 
 * 
 * SAMPLE OUTPUT (Interactive Mode):
 * 
 * MyRouter> enable
 * MyRouter# configure terminal
 * MyRouter(config)# hostname CoreRouter
 *   ✓ Hostname changed to: CoreRouter
 * CoreRouter(config)# enable password cisco
 *   ✓ Enable password set (stored as plaintext)
 * CoreRouter(config)# enable secret secret123
 *   ✓ Secret password set (stored as MD5 hash)
 * CoreRouter(config)# exit
 * CoreRouter# show running-config
 */
