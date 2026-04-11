/*
 * Slip 12 - Q2 Option B: Router Password Configuration Simulator
 *
 * Concept: Simulates Cisco IOS commands for basic router security:
 *   - hostname: Sets device identification name
 *   - enable password: Sets plaintext password (visible in config)
 *   - enable secret: Sets MD5-encrypted password (secure)
 *
 * Cisco IOS Command Reference:
 *   Router> enable                    (Enter privileged mode)
 *   Router# configure terminal        (Enter config mode)
 *   Router(config)# hostname MyRouter (Set hostname)
 *   Router(config)# enable password X (Set plaintext password)
 *   Router(config)# enable secret Y   (Set encrypted password)
 *
 * Compile: gcc -o router_config Slip_12_Q2_OptionB.c
 * Run:     ./router_config
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 64
#define MAX_INTERFACES 4

// Router configuration structure
typedef struct {
    char hostname[MAX_LEN];
    char enable_password[MAX_LEN];     // Plaintext password
    char enable_secret[MAX_LEN];       // Encrypted password
    char secret_hash[MAX_LEN];         // MD5-like hash representation
    int password_encryption;           // service password-encryption
    int is_configured;
} RouterConfig;

// Interface configuration
typedef struct {
    char name[32];
    char ip_address[16];
    char subnet_mask[16];
    int is_up;
} Interface;

// Router structure
typedef struct {
    RouterConfig config;
    Interface interfaces[MAX_INTERFACES];
    int interface_count;
    int current_mode;  // 0=user, 1=privileged, 2=config
} Router;

// Function prototypes
void initialize_router(Router *router);
void display_banner(void);
void display_menu(Router *router);
void configure_hostname(Router *router);
void configure_enable_password(Router *router);
void configure_enable_secret(Router *router);
void show_running_config(Router *router);
void show_startup_config(Router *router);
void simulate_ios_cli(Router *router);
void simple_hash(const char *input, char *output);
void display_password_info(void);
void configure_interface(Router *router);
void enable_password_encryption(Router *router);
char* get_mode_prompt(Router *router);
void encrypt_password(const char *plain, char *encrypted);

int main() {
    Router router;
    int choice;

    initialize_router(&router);
    display_banner();

    while (1) {
        display_menu(&router);
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice) {
            case 1:
                configure_hostname(&router);
                break;
            case 2:
                configure_enable_password(&router);
                break;
            case 3:
                configure_enable_secret(&router);
                break;
            case 4:
                show_running_config(&router);
                break;
            case 5:
                simulate_ios_cli(&router);
                break;
            case 6:
                display_password_info();
                break;
            case 7:
                configure_interface(&router);
                break;
            case 8:
                enable_password_encryption(&router);
                break;
            case 9:
                printf("\n");


                exit(0);
            default:
                printf("\n[ERROR] Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

void initialize_router(Router *router) {
    strcpy(router->config.hostname, "Router");
    strcpy(router->config.enable_password, "");
    strcpy(router->config.enable_secret, "");
    strcpy(router->config.secret_hash, "");
    router->config.password_encryption = 0;
    router->config.is_configured = 0;
    router->current_mode = 0;

    router->interface_count = 2;

    strcpy(router->interfaces[0].name, "FastEthernet0/0");
    strcpy(router->interfaces[0].ip_address, "unassigned");
    strcpy(router->interfaces[0].subnet_mask, "unassigned");
    router->interfaces[0].is_up = 0;

    strcpy(router->interfaces[1].name, "FastEthernet0/1");
    strcpy(router->interfaces[1].ip_address, "unassigned");
    strcpy(router->interfaces[1].subnet_mask, "unassigned");
    router->interfaces[1].is_up = 0;
}

void display_banner(void) {
    printf("\n");


}

void display_menu(Router *router) {
    printf("\n");


}

void configure_hostname(Router *router) {
    char new_hostname[MAX_LEN];

    printf("\n");


    printf("\n");

    printf("Current hostname: %s\n", router->config.hostname);
    printf("Enter new hostname: ");
    fgets(new_hostname, MAX_LEN, stdin);
    new_hostname[strcspn(new_hostname, "\n")] = 0;

    if (strlen(new_hostname) > 0) {
        printf("\n");
        printf("  %s(config)# hostname %s\n", router->config.hostname, new_hostname);
        strcpy(router->config.hostname, new_hostname);
        printf("  %s(config)#\n", router->config.hostname);
        printf("\n[SUCCESS] Hostname changed to '%s'\n", router->config.hostname);
        router->config.is_configured = 1;
    } else {
        printf("[ERROR] Invalid hostname!\n");
    }
}

void configure_enable_password(Router *router) {
    char password[MAX_LEN];
    char encrypted[MAX_LEN];

    printf("\n");


    printf("\n");

    printf("Enter enable password: ");
    fgets(password, MAX_LEN, stdin);
    password[strcspn(password, "\n")] = 0;

    if (strlen(password) > 0) {
        strcpy(router->config.enable_password, password);

        printf("\n");
        printf("  %s(config)# enable password %s\n",
               router->config.hostname, password);
        printf("  %s(config)#\n", router->config.hostname);

        if (router->config.password_encryption) {
            encrypt_password(password, encrypted);
            printf("\n[SUCCESS] Enable password set (will be encrypted in config)\n");
        } else {
            printf("\n[SUCCESS] Enable password set to '%s'\n", password);
            printf("[WARNING] Password stored in plaintext! Consider using 'enable secret'\n");
        }
        router->config.is_configured = 1;
    } else {
        printf("[ERROR] Invalid password!\n");
    }
}

void configure_enable_secret(Router *router) {
    char password[MAX_LEN];

    printf("\n");


    printf("\n");

    printf("Enter enable secret: ");
    fgets(password, MAX_LEN, stdin);
    password[strcspn(password, "\n")] = 0;

    if (strlen(password) > 0) {
        strcpy(router->config.enable_secret, password);
        simple_hash(password, router->config.secret_hash);

        printf("\n");
        printf("  %s(config)# enable secret %s\n",
               router->config.hostname, password);
        printf("  %s(config)#\n", router->config.hostname);
        printf("\n[SUCCESS] Enable secret configured!\n");
        printf("  Original:  %s\n", password);
        printf("  MD5 Hash:  $1$%s\n", router->config.secret_hash);
        printf("\n[INFO] Enable secret takes priority over enable password\n");
        router->config.is_configured = 1;
    } else {
        printf("[ERROR] Invalid password!\n");
    }
}

void simple_hash(const char *input, char *output) {
    // Simple hash simulation (not real MD5)
    unsigned long hash = 5381;
    int c;

    while ((c = *input++)) {
        hash = ((hash << 5) + hash) + c;
    }

    // Format as pseudo-MD5 hash
    sprintf(output, "mERs$%.4lx$%.8lx%.8lx",
            (hash >> 16) & 0xFFFF,
            hash & 0xFFFFFFFF,
            (hash * 31) & 0xFFFFFFFF);
}

void encrypt_password(const char *plain, char *encrypted) {
    // Simple Type 7 encryption simulation
    int i;
    for (i = 0; plain[i] != '\0' && i < MAX_LEN - 3; i++) {
        sprintf(encrypted + (i * 2), "%02X", plain[i] ^ 0x17);
    }
    encrypted[i * 2] = '\0';
}

void show_running_config(Router *router) {
    char encrypted_pass[MAX_LEN];

    printf("\n");


    printf("\n");
    printf("Building configuration...\n\n");
    printf("Current configuration : 1024 bytes\n");
    printf("!\n");
    printf("version 15.1\n");
    printf("service timestamps debug datetime msec\n");
    printf("service timestamps log datetime msec\n");

    if (router->config.password_encryption) {
        printf("service password-encryption\n");
    } else {
        printf("no service password-encryption\n");
    }

    printf("!\n");
    printf("hostname %s\n", router->config.hostname);
    printf("!\n");
    printf("boot-start-marker\n");
    printf("boot-end-marker\n");
    printf("!\n");

    // Enable secret (always MD5 hashed)
    if (strlen(router->config.enable_secret) > 0) {
        printf("enable secret 5 $1$%s\n", router->config.secret_hash);
    }

    // Enable password (plaintext or encrypted based on service)
    if (strlen(router->config.enable_password) > 0) {
        if (router->config.password_encryption) {
            encrypt_password(router->config.enable_password, encrypted_pass);
            printf("enable password 7 %s\n", encrypted_pass);
        } else {
            printf("enable password %s\n", router->config.enable_password);
        }
    }

    printf("!\n");
    printf("no aaa new-model\n");
    printf("!\n");

    // Interface configurations
    for (int i = 0; i < router->interface_count; i++) {
        printf("interface %s\n", router->interfaces[i].name);
        if (strcmp(router->interfaces[i].ip_address, "unassigned") != 0) {
            printf(" ip address %s %s\n",
                   router->interfaces[i].ip_address,
                   router->interfaces[i].subnet_mask);
        } else {
            printf(" no ip address\n");
        }
        if (router->interfaces[i].is_up) {
            printf(" no shutdown\n");
        } else {
            printf(" shutdown\n");
        }
        printf("!\n");
    }

    printf("ip forward-protocol nd\n");
    printf("!\n");
    printf("no ip http server\n");
    printf("no ip http secure-server\n");
    printf("!\n");
    printf("line con 0\n");
    printf("line aux 0\n");
    printf("line vty 0 4\n");
    printf(" login\n");
    printf("!\n");
    printf("end\n");
    printf("\n");

    // Security analysis


    if (strlen(router->config.enable_secret) > 0) {

    } else {

    }

    if (strlen(router->config.enable_password) > 0) {
        if (router->config.password_encryption) {

        } else {

        }
    }

    if (router->config.password_encryption) {

    } else {

    }


}

void simulate_ios_cli(Router *router) {
    char command[256];
    int in_config_mode = 0;
    int in_interface_mode = 0;

    printf("\n");


    printf("\n");
    printf("%s>", router->config.hostname);

    while (1) {
        fgets(command, 256, stdin);
        command[strcspn(command, "\n")] = 0;

        // Empty command
        if (strlen(command) == 0) {
            if (in_interface_mode) {
                printf("%s(config-if)#", router->config.hostname);
            } else if (in_config_mode) {
                printf("%s(config)#", router->config.hostname);
            } else if (router->current_mode == 1) {
                printf("%s#", router->config.hostname);
            } else {
                printf("%s>", router->config.hostname);
            }
            continue;
        }

        // Parse command
        if (strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0) {
            if (in_interface_mode) {
                in_interface_mode = 0;
                printf("%s(config)#", router->config.hostname);
            } else if (in_config_mode) {
                in_config_mode = 0;
                printf("%s#", router->config.hostname);
            } else if (router->current_mode == 1) {
                router->current_mode = 0;
                printf("%s>", router->config.hostname);
            } else {
                printf("\n[Returning to main menu]\n");
                return;
            }
        }
        else if (strcmp(command, "help") == 0 || strcmp(command, "?") == 0) {
            printf("\nAvailable commands:\n");
            printf("  enable              - Enter privileged EXEC mode\n");
            printf("  configure terminal  - Enter configuration mode\n");
            printf("  hostname <name>     - Set device hostname\n");
            printf("  enable password <p> - Set plaintext password\n");
            printf("  enable secret <p>   - Set MD5 encrypted password\n");
            printf("  show running-config - Display running configuration\n");
            printf("  interface <name>    - Configure interface\n");
            printf("  end                 - Return to privileged mode\n");
            printf("  exit                - Exit current mode\n");
            printf("\n");

            if (in_interface_mode) {
                printf("%s(config-if)#", router->config.hostname);
            } else if (in_config_mode) {
                printf("%s(config)#", router->config.hostname);
            } else if (router->current_mode == 1) {
                printf("%s#", router->config.hostname);
            } else {
                printf("%s>", router->config.hostname);
            }
        }
        else if (strcmp(command, "enable") == 0) {
            if (router->current_mode == 0) {
                // Check if password is set
                if (strlen(router->config.enable_secret) > 0 ||
                    strlen(router->config.enable_password) > 0) {
                    char pass[MAX_LEN];
                    printf("Password: ");
                    fgets(pass, MAX_LEN, stdin);
                    pass[strcspn(pass, "\n")] = 0;

                    // Secret takes priority
                    const char *correct = strlen(router->config.enable_secret) > 0
                        ? router->config.enable_secret
                        : router->config.enable_password;

                    if (strcmp(pass, correct) == 0) {
                        router->current_mode = 1;
                        printf("%s#", router->config.hostname);
                    } else {
                        printf("Bad password\n");
                        printf("%s>", router->config.hostname);
                    }
                } else {
                    router->current_mode = 1;
                    printf("%s#", router->config.hostname);
                }
            } else {
                printf("%s#", router->config.hostname);
            }
        }
        else if (strcmp(command, "configure terminal") == 0 ||
                 strcmp(command, "conf t") == 0) {
            if (router->current_mode == 1) {
                in_config_mode = 1;
                printf("Enter configuration commands, one per line. End with CNTL/Z.\n");
                printf("%s(config)#", router->config.hostname);
            } else {
                printf("%%  Invalid input detected\n");
                printf("%s>", router->config.hostname);
            }
        }
        else if (strncmp(command, "hostname ", 9) == 0) {
            if (in_config_mode) {
                char *new_name = command + 9;
                if (strlen(new_name) > 0) {
                    strcpy(router->config.hostname, new_name);
                    router->config.is_configured = 1;
                }
                printf("%s(config)#", router->config.hostname);
            } else {
                printf("%%  Invalid input detected\n");
                printf("%s>", router->config.hostname);
            }
        }
        else if (strncmp(command, "enable password ", 16) == 0) {
            if (in_config_mode) {
                char *pass = command + 16;
                if (strlen(pass) > 0) {
                    strcpy(router->config.enable_password, pass);
                    router->config.is_configured = 1;
                }
                printf("%s(config)#", router->config.hostname);
            } else {
                printf("%%  Invalid input detected\n");
                printf("%s>", router->config.hostname);
            }
        }
        else if (strncmp(command, "enable secret ", 14) == 0) {
            if (in_config_mode) {
                char *pass = command + 14;
                if (strlen(pass) > 0) {
                    strcpy(router->config.enable_secret, pass);
                    simple_hash(pass, router->config.secret_hash);
                    router->config.is_configured = 1;
                }
                printf("%s(config)#", router->config.hostname);
            } else {
                printf("%%  Invalid input detected\n");
                printf("%s>", router->config.hostname);
            }
        }
        else if (strcmp(command, "service password-encryption") == 0) {
            if (in_config_mode) {
                router->config.password_encryption = 1;
                printf("%s(config)#", router->config.hostname);
            } else {
                printf("%%  Invalid input detected\n");
                printf("%s>", router->config.hostname);
            }
        }
        else if (strcmp(command, "show running-config") == 0 ||
                 strcmp(command, "sh run") == 0) {
            if (router->current_mode == 1 || in_config_mode) {
                show_running_config(router);
            } else {
                printf("%%  Invalid input detected\n");
            }

            if (in_interface_mode) {
                printf("%s(config-if)#", router->config.hostname);
            } else if (in_config_mode) {
                printf("%s(config)#", router->config.hostname);
            } else if (router->current_mode == 1) {
                printf("%s#", router->config.hostname);
            } else {
                printf("%s>", router->config.hostname);
            }
        }
        else if (strcmp(command, "end") == 0) {
            in_config_mode = 0;
            in_interface_mode = 0;
            if (router->current_mode == 1) {
                printf("%s#", router->config.hostname);
            } else {
                printf("%s>", router->config.hostname);
            }
        }
        else {
            printf("%% Unrecognized command\n");
            if (in_interface_mode) {
                printf("%s(config-if)#", router->config.hostname);
            } else if (in_config_mode) {
                printf("%s(config)#", router->config.hostname);
            } else if (router->current_mode == 1) {
                printf("%s#", router->config.hostname);
            } else {
                printf("%s>", router->config.hostname);
            }
        }
    }
}

void display_password_info(void) {
    printf("\n");


    printf("\n");


    printf("\n");


    printf("\n");
    printf("  BEST PRACTICES:\n");

    printf("  1. Always use 'enable secret' instead of 'enable password'\n");
    printf("  2. Enable 'service password-encryption' for legacy passwords\n");
    printf("  3. Use strong passwords (mix of letters, numbers, symbols)\n");
    printf("  4. Minimum 8 characters recommended\n");
    printf("  5. Change passwords regularly\n");
    printf("\n");
}

void configure_interface(Router *router) {
    int choice;
    char ip[16], mask[16];

    printf("\n");


    printf("\n");
    printf("Available interfaces:\n");

    for (int i = 0; i < router->interface_count; i++) {
        printf("  %d. %s - %s/%s [%s]\n",
               i + 1,
               router->interfaces[i].name,
               router->interfaces[i].ip_address,
               router->interfaces[i].subnet_mask,
               router->interfaces[i].is_up ? "UP" : "DOWN");
    }

    printf("\nSelect interface (1-%d): ", router->interface_count);
    scanf("%d", &choice);
    getchar();

    if (choice < 1 || choice > router->interface_count) {
        printf("[ERROR] Invalid selection!\n");
        return;
    }

    Interface *iface = &router->interfaces[choice - 1];

    printf("Enter IP address (e.g., 192.168.1.1): ");
    fgets(ip, 16, stdin);
    ip[strcspn(ip, "\n")] = 0;

    printf("Enter subnet mask (e.g., 255.255.255.0): ");
    fgets(mask, 16, stdin);
    mask[strcspn(mask, "\n")] = 0;

    strcpy(iface->ip_address, ip);
    strcpy(iface->subnet_mask, mask);
    iface->is_up = 1;

    printf("\n");
    printf("  %s(config)# interface %s\n", router->config.hostname, iface->name);
    printf("  %s(config-if)# ip address %s %s\n", router->config.hostname, ip, mask);
    printf("  %s(config-if)# no shutdown\n", router->config.hostname);
    printf("  %s(config-if)# exit\n", router->config.hostname);
    printf("\n[SUCCESS] Interface %s configured with IP %s\n", iface->name, ip);
}

void enable_password_encryption(Router *router) {
    printf("\n");


    printf("\n");

    printf("  %s(config)# service password-encryption\n", router->config.hostname);
    router->config.password_encryption = 1;
    printf("\n[SUCCESS] Password encryption service enabled!\n");
    printf("[INFO] All Type 0 passwords will now appear as Type 7 in config.\n");
}
