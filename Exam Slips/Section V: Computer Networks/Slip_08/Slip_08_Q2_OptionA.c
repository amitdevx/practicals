/*
 * Slip 08 - Q2 Option A: Network Configuration Verification Simulation
 * 
 * Program to verify network configuration using:
 * - show running-config command simulation
 * - ping command simulation
 * 
 * This simulates Cisco IOS-like commands for educational purposes.
 * 
 * Compile: gcc -o Slip_08_Q2_OptionA Slip_08_Q2_OptionA.c
 * Run: ./Slip_08_Q2_OptionA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_INTERFACES 4
#define MAX_HOSTNAME 64
#define MAX_IP_LEN 16
#define MAX_ROUTES 10
#define MAX_CMD_LEN 256

/* ===================== Data Structures ===================== */

typedef struct {
    char name[32];
    char ip_address[MAX_IP_LEN];
    char subnet_mask[MAX_IP_LEN];
    int is_up;
    char description[64];
    int bandwidth;          /* in Kbps */
    char duplex[16];
    int mtu;
} Interface;

typedef struct {
    char network[MAX_IP_LEN];
    char mask[MAX_IP_LEN];
    char next_hop[MAX_IP_LEN];
    char out_interface[32];
    int metric;
} Route;

typedef struct {
    char hostname[MAX_HOSTNAME];
    char enable_secret[64];
    char console_password[64];
    char vty_password[64];
    char banner_motd[256];
    Interface interfaces[MAX_INTERFACES];
    int num_interfaces;
    Route routes[MAX_ROUTES];
    int num_routes;
    int service_password_encryption;
    char domain_name[64];
} RouterConfig;

/* Global router configuration */
RouterConfig router;

/* ===================== Initialization ===================== */

/*
 * Initialize router with sample configuration
 */
void initialize_router_config(void) {
    /* Set hostname and passwords */
    strcpy(router.hostname, "ROUTER-01");
    strcpy(router.enable_secret, "5 $1$mERr$hx5rVt7rPNoS4wqbXKX7m0");  /* Encrypted */
    strcpy(router.console_password, "7 0822455D0A16");                  /* Type 7 */
    strcpy(router.vty_password, "7 0822455D0A16");
    strcpy(router.banner_motd, "Authorized Access Only - Violators Will Be Prosecuted!");
    strcpy(router.domain_name, "example.local");
    router.service_password_encryption = 1;
    
    /* Configure interfaces */
    router.num_interfaces = 4;
    
    /* GigabitEthernet0/0 - Inside interface */
    strcpy(router.interfaces[0].name, "GigabitEthernet0/0");
    strcpy(router.interfaces[0].ip_address, "192.168.1.1");
    strcpy(router.interfaces[0].subnet_mask, "255.255.255.0");
    strcpy(router.interfaces[0].description, "LAN Interface - Inside");
    router.interfaces[0].is_up = 1;
    router.interfaces[0].bandwidth = 1000000;
    strcpy(router.interfaces[0].duplex, "full");
    router.interfaces[0].mtu = 1500;
    
    /* GigabitEthernet0/1 - Outside interface */
    strcpy(router.interfaces[1].name, "GigabitEthernet0/1");
    strcpy(router.interfaces[1].ip_address, "203.0.113.1");
    strcpy(router.interfaces[1].subnet_mask, "255.255.255.0");
    strcpy(router.interfaces[1].description, "WAN Interface - Outside");
    router.interfaces[1].is_up = 1;
    router.interfaces[1].bandwidth = 1000000;
    strcpy(router.interfaces[1].duplex, "full");
    router.interfaces[1].mtu = 1500;
    
    /* Serial0/0/0 */
    strcpy(router.interfaces[2].name, "Serial0/0/0");
    strcpy(router.interfaces[2].ip_address, "10.0.0.1");
    strcpy(router.interfaces[2].subnet_mask, "255.255.255.252");
    strcpy(router.interfaces[2].description, "WAN Link to Branch");
    router.interfaces[2].is_up = 1;
    router.interfaces[2].bandwidth = 1544;
    strcpy(router.interfaces[2].duplex, "N/A");
    router.interfaces[2].mtu = 1500;
    
    /* Loopback0 */
    strcpy(router.interfaces[3].name, "Loopback0");
    strcpy(router.interfaces[3].ip_address, "1.1.1.1");
    strcpy(router.interfaces[3].subnet_mask, "255.255.255.255");
    strcpy(router.interfaces[3].description, "Router ID");
    router.interfaces[3].is_up = 1;
    router.interfaces[3].bandwidth = 8000000;
    strcpy(router.interfaces[3].duplex, "N/A");
    router.interfaces[3].mtu = 1514;
    
    /* Configure static routes */
    router.num_routes = 3;
    
    strcpy(router.routes[0].network, "0.0.0.0");
    strcpy(router.routes[0].mask, "0.0.0.0");
    strcpy(router.routes[0].next_hop, "203.0.113.254");
    strcpy(router.routes[0].out_interface, "GigabitEthernet0/1");
    router.routes[0].metric = 1;
    
    strcpy(router.routes[1].network, "172.16.0.0");
    strcpy(router.routes[1].mask, "255.255.0.0");
    strcpy(router.routes[1].next_hop, "10.0.0.2");
    strcpy(router.routes[1].out_interface, "Serial0/0/0");
    router.routes[1].metric = 1;
    
    strcpy(router.routes[2].network, "192.168.2.0");
    strcpy(router.routes[2].mask, "255.255.255.0");
    strcpy(router.routes[2].next_hop, "10.0.0.2");
    strcpy(router.routes[2].out_interface, "Serial0/0/0");
    router.routes[2].metric = 1;
}

/* ===================== Show Running-Config ===================== */

/*
 * Display the running configuration (like Cisco IOS)
 */
void show_running_config(void) {
    int i;
    time_t now;
    
    time(&now);
    
    printf("\n");
    printf("Building configuration...\n\n");
    usleep(500000);  /* Simulate processing time */
    
    printf("Current configuration : 1847 bytes\n");
    printf("!\n");
    printf("! Last configuration change at %s", ctime(&now));
    printf("!\n");
    printf("version 15.4\n");
    printf("service timestamps debug datetime msec\n");
    printf("service timestamps log datetime msec\n");
    
    if (router.service_password_encryption) {
        printf("service password-encryption\n");
    }
    
    printf("!\n");
    printf("hostname %s\n", router.hostname);
    printf("!\n");
    printf("boot-start-marker\n");
    printf("boot-end-marker\n");
    printf("!\n");
    printf("enable secret %s\n", router.enable_secret);
    printf("!\n");
    printf("no aaa new-model\n");
    printf("!\n");
    printf("ip domain name %s\n", router.domain_name);
    printf("ip cef\n");
    printf("no ipv6 cef\n");
    printf("!\n");
    
    /* Display interface configurations */
    for (i = 0; i < router.num_interfaces; i++) {
        printf("interface %s\n", router.interfaces[i].name);
        printf(" description %s\n", router.interfaces[i].description);
        printf(" ip address %s %s\n", 
               router.interfaces[i].ip_address, 
               router.interfaces[i].subnet_mask);
        
        if (strstr(router.interfaces[i].name, "GigabitEthernet") != NULL) {
            printf(" duplex %s\n", router.interfaces[i].duplex);
            printf(" speed auto\n");
        }
        
        if (router.interfaces[i].is_up) {
            printf(" no shutdown\n");
        } else {
            printf(" shutdown\n");
        }
        printf("!\n");
    }
    
    /* Display routing configuration */
    printf("ip forward-protocol nd\n");
    printf("!\n");
    printf("no ip http server\n");
    printf("no ip http secure-server\n");
    printf("!\n");
    
    /* Static routes */
    for (i = 0; i < router.num_routes; i++) {
        printf("ip route %s %s %s\n",
               router.routes[i].network,
               router.routes[i].mask,
               router.routes[i].next_hop);
    }
    printf("!\n");
    
    /* Access lists (sample) */
    printf("access-list 1 permit 192.168.1.0 0.0.0.255\n");
    printf("!\n");
    
    /* NAT configuration */
    printf("ip nat inside source list 1 interface GigabitEthernet0/1 overload\n");
    printf("!\n");
    
    /* Console and VTY lines */
    printf("line con 0\n");
    printf(" password %s\n", router.console_password);
    printf(" login\n");
    printf(" logging synchronous\n");
    printf("line aux 0\n");
    printf("line vty 0 4\n");
    printf(" password %s\n", router.vty_password);
    printf(" login\n");
    printf(" transport input ssh telnet\n");
    printf("line vty 5 15\n");
    printf(" password %s\n", router.vty_password);
    printf(" login\n");
    printf(" transport input ssh telnet\n");
    printf("!\n");
    
    /* Banner */
    printf("banner motd ^C\n");
    printf("  *******************************************\n");
    printf("  *  %s  *\n", router.banner_motd);
    printf("  *******************************************\n");
    printf("^C\n");
    printf("!\n");
    printf("end\n\n");
}

/* ===================== Show IP Interface Brief ===================== */

/*
 * Display brief interface status
 */
void show_ip_interface_brief(void) {
    int i;
    
    printf("\n");
    printf("%-24s %-15s %-6s %-10s %-22s\n",
           "Interface", "IP-Address", "OK?", "Method", "Status                Protocol");
    
    for (i = 0; i < router.num_interfaces; i++) {
        printf("%-24s %-15s YES    manual     %-10s %-10s\n",
               router.interfaces[i].name,
               router.interfaces[i].ip_address,
               router.interfaces[i].is_up ? "up" : "administratively down",
               router.interfaces[i].is_up ? "up" : "down");
    }
    printf("\n");
}

/* ===================== Show IP Route ===================== */

/*
 * Display IP routing table
 */
void show_ip_route(void) {
    int i;
    
    printf("\n");
    printf("Codes: L - local, C - connected, S - static, R - RIP, M - mobile, B - BGP\n");
    printf("       D - EIGRP, EX - EIGRP external, O - OSPF, IA - OSPF inter area\n");
    printf("       N1 - OSPF NSSA external type 1, N2 - OSPF NSSA external type 2\n");
    printf("       E1 - OSPF external type 1, E2 - OSPF external type 2\n");
    printf("       i - IS-IS, su - IS-IS summary, L1 - IS-IS level-1, L2 - IS-IS level-2\n");
    printf("       ia - IS-IS inter area, * - candidate default, U - per-user static route\n");
    printf("       o - ODR, P - periodic downloaded static route, H - NHRP, l - LISP\n");
    printf("       + - replicated route, %% - next hop override\n\n");
    printf("Gateway of last resort is 203.0.113.254 to network 0.0.0.0\n\n");
    
    /* Display static routes */
    for (i = 0; i < router.num_routes; i++) {
        if (strcmp(router.routes[i].network, "0.0.0.0") == 0) {
            printf("S*   0.0.0.0/0 [1/0] via %s\n", router.routes[i].next_hop);
        } else {
            printf("S    %s/%d [1/0] via %s\n",
                   router.routes[i].network,
                   (strcmp(router.routes[i].mask, "255.255.255.0") == 0) ? 24 :
                   (strcmp(router.routes[i].mask, "255.255.0.0") == 0) ? 16 : 8,
                   router.routes[i].next_hop);
        }
    }
    
    /* Display connected routes */
    printf("C    192.168.1.0/24 is directly connected, GigabitEthernet0/0\n");
    printf("L    192.168.1.1/32 is directly connected, GigabitEthernet0/0\n");
    printf("C    203.0.113.0/24 is directly connected, GigabitEthernet0/1\n");
    printf("L    203.0.113.1/32 is directly connected, GigabitEthernet0/1\n");
    printf("C    10.0.0.0/30 is directly connected, Serial0/0/0\n");
    printf("L    10.0.0.1/32 is directly connected, Serial0/0/0\n");
    printf("\n");
}

/* ===================== Ping Simulation ===================== */

/*
 * Parse IP address string to array of octets
 */
int parse_ip(const char *ip_str, int octets[4]) {
    return sscanf(ip_str, "%d.%d.%d.%d", 
                  &octets[0], &octets[1], &octets[2], &octets[3]) == 4;
}

/*
 * Check if IP is in same network as an interface
 */
int is_reachable(const char *target_ip) {
    int target[4], iface[4], mask[4];
    int i, j;
    
    if (!parse_ip(target_ip, target)) {
        return 0;
    }
    
    /* Check if target is one of our interfaces (loopback ping) */
    for (i = 0; i < router.num_interfaces; i++) {
        if (strcmp(target_ip, router.interfaces[i].ip_address) == 0 && 
            router.interfaces[i].is_up) {
            return 1;
        }
    }
    
    /* Check if target is in a directly connected network */
    for (i = 0; i < router.num_interfaces; i++) {
        if (!router.interfaces[i].is_up) continue;
        
        if (!parse_ip(router.interfaces[i].ip_address, iface)) continue;
        if (!parse_ip(router.interfaces[i].subnet_mask, mask)) continue;
        
        int match = 1;
        for (j = 0; j < 4; j++) {
            if ((target[j] & mask[j]) != (iface[j] & mask[j])) {
                match = 0;
                break;
            }
        }
        
        if (match) {
            /* Simulate some hosts being unreachable */
            if (target[3] > 250) return 0;  /* .251-.255 unreachable */
            return 1;
        }
    }
    
    /* Check static routes - assume reachable via route */
    for (i = 0; i < router.num_routes; i++) {
        if (strcmp(router.routes[i].network, "0.0.0.0") == 0) {
            /* Default route - assume 50% reachable */
            return (rand() % 100 < 50);
        }
    }
    
    return 0;
}

/*
 * Simulate ping command
 */
void ping_host(const char *target_ip, int count) {
    int i;
    int success = 0, failed = 0;
    int rtt_min = 1000, rtt_max = 0, rtt_sum = 0;
    int rtt;
    
    printf("\nType escape sequence to abort.\n");
    printf("Sending %d, 100-byte ICMP Echos to %s, timeout is 2 seconds:\n",
           count, target_ip);
    
    for (i = 0; i < count; i++) {
        usleep(200000);  /* Simulate delay between pings */
        
        if (is_reachable(target_ip)) {
            rtt = 1 + (rand() % 50);  /* Random RTT 1-50ms */
            printf("!");
            fflush(stdout);
            success++;
            rtt_sum += rtt;
            if (rtt < rtt_min) rtt_min = rtt;
            if (rtt > rtt_max) rtt_max = rtt;
        } else {
            printf(".");
            fflush(stdout);
            failed++;
        }
    }
    
    printf("\n");
    printf("Success rate is %d percent (%d/%d)",
           (success * 100) / count, success, count);
    
    if (success > 0) {
        printf(", round-trip min/avg/max = %d/%d/%d ms",
               rtt_min, rtt_sum / success, rtt_max);
    }
    printf("\n\n");
}

/*
 * Extended ping with options
 */
void extended_ping(const char *target_ip) {
    int count = 5;
    char input[32];
    
    printf("\nProtocol [ip]: ");
    fgets(input, sizeof(input), stdin);
    
    printf("Target IP address: %s\n", target_ip);
    
    printf("Repeat count [5]: ");
    fgets(input, sizeof(input), stdin);
    if (strlen(input) > 1) {
        count = atoi(input);
        if (count < 1) count = 5;
        if (count > 100) count = 100;
    }
    
    printf("Datagram size [100]: ");
    fgets(input, sizeof(input), stdin);
    /* Size is displayed for realism but not used in simulation */
    
    printf("Timeout in seconds [2]: ");
    fgets(input, sizeof(input), stdin);
    /* Timeout is displayed for realism but not used in simulation */
    
    printf("Extended commands [n]: ");
    fgets(input, sizeof(input), stdin);
    
    printf("Sweep range of sizes [n]: ");
    fgets(input, sizeof(input), stdin);
    
    ping_host(target_ip, count);
}

/* ===================== Verification Summary ===================== */

/*
 * Display configuration verification summary
 */
void verify_configuration(void) {
    int i;
    int issues = 0;
    
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║           CONFIGURATION VERIFICATION REPORT                       ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    
    /* Check hostname */
    printf("║ [%s] Hostname configured: %-40s║\n",
           strlen(router.hostname) > 0 ? "✓" : "✗",
           router.hostname);
    
    /* Check enable secret */
    printf("║ [%s] Enable secret configured                                     ║\n",
           strlen(router.enable_secret) > 0 ? "✓" : "✗");
    
    /* Check password encryption */
    printf("║ [%s] Password encryption enabled                                  ║\n",
           router.service_password_encryption ? "✓" : "✗");
    
    /* Check interfaces */
    for (i = 0; i < router.num_interfaces; i++) {
        if (!router.interfaces[i].is_up) {
            printf("║ [!] Interface %s is DOWN                    ║\n",
                   router.interfaces[i].name);
            issues++;
        }
    }
    
    /* Check default route */
    int has_default = 0;
    for (i = 0; i < router.num_routes; i++) {
        if (strcmp(router.routes[i].network, "0.0.0.0") == 0) {
            has_default = 1;
            break;
        }
    }
    printf("║ [%s] Default route configured                                     ║\n",
           has_default ? "✓" : "✗");
    
    /* Check console password */
    printf("║ [%s] Console password configured                                  ║\n",
           strlen(router.console_password) > 0 ? "✓" : "✗");
    
    /* Check VTY password */
    printf("║ [%s] VTY password configured                                      ║\n",
           strlen(router.vty_password) > 0 ? "✓" : "✗");
    
    /* Check banner */
    printf("║ [%s] MOTD banner configured                                       ║\n",
           strlen(router.banner_motd) > 0 ? "✓" : "✗");
    
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    
    if (issues == 0) {
        printf("║  STATUS: All configuration checks PASSED                         ║\n");
    } else {
        printf("║  STATUS: %d issue(s) found - review recommended                   ║\n",
               issues);
    }
    
    printf("╚══════════════════════════════════════════════════════════════════╝\n\n");
}

/* ===================== Main CLI Interface ===================== */

/*
 * Display help menu
 */
void show_help(void) {
    printf("\n");
    printf("Available Commands:\n");
    printf("  show running-config      - Display current configuration\n");
    printf("  show ip interface brief  - Display interface summary\n");
    printf("  show ip route            - Display routing table\n");
    printf("  ping <ip-address>        - Ping a host\n");
    printf("  ping                     - Extended ping\n");
    printf("  verify config            - Run configuration verification\n");
    printf("  help                     - Show this help\n");
    printf("  exit                     - Exit the program\n");
    printf("\n");
}

/*
 * Process command input
 */
int process_command(char *cmd) {
    char *token;
    char cmd_copy[MAX_CMD_LEN];
    char ip_addr[MAX_IP_LEN] = "";
    
    /* Remove trailing newline */
    cmd[strcspn(cmd, "\n")] = 0;
    
    /* Skip empty commands */
    if (strlen(cmd) == 0) return 1;
    
    /* Make a copy for tokenization */
    strcpy(cmd_copy, cmd);
    
    /* Get first token */
    token = strtok(cmd_copy, " ");
    if (token == NULL) return 1;
    
    /* Process commands */
    if (strcmp(token, "show") == 0) {
        token = strtok(NULL, " ");
        if (token == NULL) {
            printf("%% Incomplete command.\n");
        } else if (strcmp(token, "running-config") == 0) {
            show_running_config();
        } else if (strcmp(token, "ip") == 0) {
            token = strtok(NULL, " ");
            if (token == NULL) {
                printf("%% Incomplete command.\n");
            } else if (strcmp(token, "interface") == 0) {
                token = strtok(NULL, " ");
                if (token && strcmp(token, "brief") == 0) {
                    show_ip_interface_brief();
                }
            } else if (strcmp(token, "route") == 0) {
                show_ip_route();
            }
        } else {
            printf("%% Invalid input detected.\n");
        }
    } else if (strcmp(token, "ping") == 0) {
        token = strtok(NULL, " ");
        if (token != NULL) {
            strcpy(ip_addr, token);
            ping_host(ip_addr, 5);
        } else {
            printf("Protocol [ip]: \n");
            printf("Target IP address: ");
            scanf("%15s", ip_addr);
            getchar();  /* Consume newline */
            extended_ping(ip_addr);
        }
    } else if (strcmp(token, "verify") == 0) {
        token = strtok(NULL, " ");
        if (token && strcmp(token, "config") == 0) {
            verify_configuration();
        }
    } else if (strcmp(token, "help") == 0 || strcmp(token, "?") == 0) {
        show_help();
    } else if (strcmp(token, "exit") == 0 || strcmp(token, "quit") == 0) {
        return 0;
    } else {
        printf("%% Unknown command: %s\n", token);
    }
    
    return 1;
}

/* ===================== Main Function ===================== */

int main(void) {
    char command[MAX_CMD_LEN];
    
    /* Seed random number generator */
    srand(time(NULL));
    
    /* Initialize router configuration */
    initialize_router_config();
    
    /* Display banner */
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║     NETWORK CONFIGURATION VERIFICATION SIMULATOR                  ║\n");
    printf("║     Slip 08 - Q2 Option A: show running-config & ping             ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf("║  Simulates Cisco IOS commands for configuration verification      ║\n");
    printf("║  Type 'help' for available commands                               ║\n");
    printf("╚══════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    
    /* Display MOTD banner */
    printf("  *******************************************\n");
    printf("  *  %s  *\n", router.banner_motd);
    printf("  *******************************************\n\n");
    
    /* Main command loop */
    while (1) {
        printf("%s# ", router.hostname);
        fflush(stdout);
        
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }
        
        if (!process_command(command)) {
            break;
        }
    }
    
    printf("\nExiting configuration verification simulator.\n");
    return 0;
}

/*
 * ALGORITHM EXPLANATION:
 * ====================
 * 
 * 1. SHOW RUNNING-CONFIG SIMULATION:
 *    - Maintains a RouterConfig structure with all configuration elements
 *    - Displays configuration in Cisco IOS format
 *    - Includes: hostname, passwords, interfaces, routes, ACLs, NAT
 * 
 * 2. PING SIMULATION:
 *    - Parses target IP address
 *    - Checks reachability:
 *      a) Is it one of our own interfaces? (loopback)
 *      b) Is it in a directly connected network?
 *      c) Is there a route to it?
 *    - Simulates ICMP echo request/reply with random RTT
 *    - Displays statistics like real ping
 * 
 * 3. CONFIGURATION VERIFICATION:
 *    - Checks all security settings
 *    - Verifies interface status
 *    - Confirms routing configuration
 *    - Reports issues found
 * 
 * SAMPLE OUTPUT:
 * =============
 * ROUTER-01# show ip interface brief
 * Interface                IP-Address      OK?    Method     Status                Protocol
 * GigabitEthernet0/0       192.168.1.1     YES    manual     up         up
 * GigabitEthernet0/1       203.0.113.1     YES    manual     up         up
 * 
 * ROUTER-01# ping 192.168.1.10
 * Sending 5, 100-byte ICMP Echos to 192.168.1.10, timeout is 2 seconds:
 * !!!!!
 * Success rate is 100 percent (5/5), round-trip min/avg/max = 2/15/34 ms
 */
