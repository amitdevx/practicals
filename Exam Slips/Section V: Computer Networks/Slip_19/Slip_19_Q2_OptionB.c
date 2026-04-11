/*
 * Slip 19 - Q2 Option B: NAT Translation Verification Program
 *
 * This program simulates Network Address Translation (NAT) and demonstrates
 * how to verify NAT translations similar to Cisco's "show ip nat translations"
 *
 * Compile: gcc -o nat_verify Slip_19_Q2_OptionB.c
 * Run: ./nat_verify
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRANSLATIONS 100
#define IP_LENGTH 48
#define PROTO_LENGTH 10

// NAT Translation Entry Structure
typedef struct {
    char protocol[PROTO_LENGTH];      // TCP, UDP, ICMP, ---
    char inside_local[IP_LENGTH];     // Private IP:Port
    char inside_global[IP_LENGTH];    // Public IP:Port (NAT)
    char outside_local[IP_LENGTH];    // Destination IP:Port
    char outside_global[IP_LENGTH];   // Destination IP:Port
    int port_inside;
    int port_outside;
    time_t created_time;
    time_t timeout;
    int active;
} NATEntry;

// NAT Statistics Structure
typedef struct {
    int total_translations;
    int active_translations;
    int expired_translations;
    int static_translations;
    int dynamic_translations;
    long packets_translated;
    time_t start_time;
} NATStatistics;

// Global NAT table and statistics
NATEntry nat_table[MAX_TRANSLATIONS];
NATStatistics nat_stats = {0, 0, 0, 0, 0, 0, 0};
int nat_count = 0;

// Public IP pool simulation
char public_ip_pool[][IP_LENGTH] = {
    "203.0.113.1",
    "203.0.113.2",
    "203.0.113.3",
    "203.0.113.4",
    "203.0.113.5"
};
int pool_size = 5;
int current_port = 1024;

// Function prototypes
void display_banner(void);
void display_menu(void);
void initialize_nat(void);
void add_static_nat(void);
void add_dynamic_nat(void);
void add_pat_entry(void);
void show_nat_translations(void);
void show_nat_statistics(void);
void verify_nat_translation(void);
void clear_nat_translations(void);
void simulate_traffic(void);
void demonstrate_nat_types(void);
void add_nat_entry(const char *proto, const char *inside_local,
                   const char *inside_global, const char *outside_local,
                   const char *outside_global, int is_static);
char* get_next_public_ip(void);
int get_next_port(void);

int main() {
    int choice;

    srand(time(NULL));
    display_banner();
    initialize_nat();

    while (1) {
        display_menu();
        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input! Please enter a number.\n");
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                add_static_nat();
                break;
            case 2:
                add_dynamic_nat();
                break;
            case 3:
                add_pat_entry();
                break;
            case 4:
                show_nat_translations();
                break;
            case 5:
                show_nat_statistics();
                break;
            case 6:
                verify_nat_translation();
                break;
            case 7:
                clear_nat_translations();
                break;
            case 8:
                simulate_traffic();
                break;
            case 9:
                demonstrate_nat_types();
                break;
            case 10:
                printf("\nExiting NAT Simulation. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Please select 1-10.\n");
        }
    }

    return 0;
}

void display_banner(void) {
    printf("\n");


}

void display_menu(void) {
    printf("\n");


}

void initialize_nat(void) {
    nat_stats.start_time = time(NULL);
    nat_stats.total_translations = 0;
    nat_stats.active_translations = 0;

    // Add some sample translations for demonstration
    add_nat_entry("TCP", "192.168.1.10:80", "203.0.113.1:1024",
                  "8.8.8.8:443", "8.8.8.8:443", 0);
    add_nat_entry("---", "192.168.1.100", "203.0.113.10",
                  "---", "---", 1);
    add_nat_entry("UDP", "192.168.1.11:53", "203.0.113.1:1025",
                  "1.1.1.1:53", "1.1.1.1:53", 0);

    printf("\n✓ NAT system initialized with sample entries.\n");
}

void add_nat_entry(const char *proto, const char *inside_local,
                   const char *inside_global, const char *outside_local,
                   const char *outside_global, int is_static) {
    if (nat_count >= MAX_TRANSLATIONS) {
        printf("Error: NAT table is full!\n");
        return;
    }

    NATEntry *entry = &nat_table[nat_count];

    strncpy(entry->protocol, proto, PROTO_LENGTH - 1);
    strncpy(entry->inside_local, inside_local, IP_LENGTH - 1);
    strncpy(entry->inside_global, inside_global, IP_LENGTH - 1);
    strncpy(entry->outside_local, outside_local, IP_LENGTH - 1);
    strncpy(entry->outside_global, outside_global, IP_LENGTH - 1);
    entry->created_time = time(NULL);
    entry->timeout = time(NULL) + 300;  // 5 minute timeout
    entry->active = 1;

    nat_count++;
    nat_stats.total_translations++;
    nat_stats.active_translations++;

    if (is_static) {
        nat_stats.static_translations++;
    } else {
        nat_stats.dynamic_translations++;
    }
}

void add_static_nat(void) {
    char inside_local[IP_LENGTH];
    char inside_global[IP_LENGTH];

    printf("\n=== ADD STATIC NAT ENTRY ===\n");
    printf("Static NAT: One-to-one mapping (e.g., web server)\n\n");

    printf("Enter Inside Local IP (private): ");
    fgets(inside_local, sizeof(inside_local), stdin);
    inside_local[strcspn(inside_local, "\n")] = '\0';

    printf("Enter Inside Global IP (public): ");
    fgets(inside_global, sizeof(inside_global), stdin);
    inside_global[strcspn(inside_global, "\n")] = '\0';

    add_nat_entry("---", inside_local, inside_global, "---", "---", 1);

    printf("\n✓ Static NAT added successfully!\n");
    printf("  Cisco command equivalent:\n");
    printf("  Router(config)# ip nat inside source static %s %s\n",
           inside_local, inside_global);
}

void add_dynamic_nat(void) {
    char inside_local[IP_LENGTH];
    char inside_global[IP_LENGTH];

    printf("\n=== ADD DYNAMIC NAT ENTRY ===\n");
    printf("Dynamic NAT: Maps from a pool of public IPs\n\n");

    printf("Enter Inside Local IP (private): ");
    fgets(inside_local, sizeof(inside_local), stdin);
    inside_local[strcspn(inside_local, "\n")] = '\0';

    // Automatically assign from pool
    strcpy(inside_global, get_next_public_ip());

    add_nat_entry("---", inside_local, inside_global, "---", "---", 0);

    printf("\n✓ Dynamic NAT added successfully!\n");
    printf("  Private IP %s mapped to Public IP %s\n", inside_local, inside_global);
}

void add_pat_entry(void) {
    char inside_local[IP_LENGTH];
    char inside_global[IP_LENGTH];
    char outside[IP_LENGTH];
    char protocol[PROTO_LENGTH];
    char temp[IP_LENGTH];
    int inside_port, outside_port;

    printf("\n=== ADD PAT (Port Address Translation) ENTRY ===\n");
    printf("PAT/Overload: Many-to-one using port numbers\n\n");

    printf("Enter Protocol (TCP/UDP/ICMP): ");
    fgets(protocol, sizeof(protocol), stdin);
    protocol[strcspn(protocol, "\n")] = '\0';

    printf("Enter Inside Local IP: ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';

    printf("Enter Inside Local Port: ");
    scanf("%d", &inside_port);
    while (getchar() != '\n');

    snprintf(inside_local, sizeof(inside_local), "%s:%d", temp, inside_port);

    // Assign global IP:port
    outside_port = get_next_port();
    snprintf(inside_global, sizeof(inside_global), "203.0.113.1:%d", outside_port);

    printf("Enter Destination IP: ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';

    printf("Enter Destination Port: ");
    scanf("%d", &inside_port);
    while (getchar() != '\n');

    snprintf(outside, sizeof(outside), "%s:%d", temp, inside_port);

    add_nat_entry(protocol, inside_local, inside_global, outside, outside, 0);

    printf("\n✓ PAT entry added successfully!\n");
    printf("  %s %s -> %s (Dest: %s)\n", protocol, inside_local, inside_global, outside);
}

void show_nat_translations(void) {
    printf("\n");
    printf("Router# show ip nat translations\n");

    printf("%-5s %-20s %-20s %-20s %-20s\n",
           "Pro", "Inside global", "Inside local", "Outside local", "Outside global");


    if (nat_count == 0) {
        printf("No NAT translations found.\n");
    } else {
        for (int i = 0; i < nat_count; i++) {
            if (nat_table[i].active) {
                printf("%-5s %-20s %-20s %-20s %-20s\n",
                       nat_table[i].protocol,
                       nat_table[i].inside_global,
                       nat_table[i].inside_local,
                       nat_table[i].outside_local,
                       nat_table[i].outside_global);
            }
        }
    }

    printf("Total entries: %d\n", nat_stats.active_translations);
}

void show_nat_statistics(void) {
    time_t now = time(NULL);
    int uptime = (int)(now - nat_stats.start_time);

    printf("\n");
    printf("Router# show ip nat statistics\n");

    printf("Total active translations: %d (Static: %d, Dynamic: %d)\n",
           nat_stats.active_translations,
           nat_stats.static_translations,
           nat_stats.dynamic_translations);
    printf("Peak translations: %d, Missed translations: 0\n", nat_stats.total_translations);
    printf("\n");
    printf("Outside interfaces:\n");
    printf("  GigabitEthernet0/1\n");
    printf("\n");
    printf("Inside interfaces:\n");
    printf("  GigabitEthernet0/0\n");
    printf("\n");
    printf("Hits: %ld  Misses: 0\n", nat_stats.packets_translated);
    printf("\n");
    printf("CEF Translated packets: %ld, CEF Punted packets: 0\n",
           nat_stats.packets_translated);
    printf("\n");
    printf("Expired translations: %d\n", nat_stats.expired_translations);
    printf("Pool stats drop: 0  Mapping stats drop: 0\n");
    printf("\n");
    printf("NAT uptime: %d seconds\n", uptime);

}

void verify_nat_translation(void) {
    char search_ip[IP_LENGTH];
    int found = 0;

    printf("\n=== VERIFY NAT TRANSLATION ===\n");
    printf("Enter IP address to search (private or public): ");
    fgets(search_ip, sizeof(search_ip), stdin);
    search_ip[strcspn(search_ip, "\n")] = '\0';

    printf("\nRouter# show ip nat translations | include %s\n", search_ip);

    printf("%-5s %-20s %-20s %-20s %-20s\n",
           "Pro", "Inside global", "Inside local", "Outside local", "Outside global");


    for (int i = 0; i < nat_count; i++) {
        if (nat_table[i].active) {
            if (strstr(nat_table[i].inside_local, search_ip) ||
                strstr(nat_table[i].inside_global, search_ip) ||
                strstr(nat_table[i].outside_local, search_ip) ||
                strstr(nat_table[i].outside_global, search_ip)) {

                printf("%-5s %-20s %-20s %-20s %-20s\n",
                       nat_table[i].protocol,
                       nat_table[i].inside_global,
                       nat_table[i].inside_local,
                       nat_table[i].outside_local,
                       nat_table[i].outside_global);
                found++;
            }
        }
    }


    if (found == 0) {
        printf("\n✗ No NAT translation found for IP: %s\n", search_ip);
        printf("  Possible reasons:\n");
        printf("  - The IP is not configured for NAT\n");
        printf("  - Translation has expired\n");
        printf("  - NAT is not enabled on the interface\n");
    } else {
        printf("\n✓ Found %d translation(s) for IP: %s\n", found, search_ip);
        printf("  NAT is working correctly for this address.\n");
    }
}

void clear_nat_translations(void) {
    char confirm;

    printf("\n⚠️  WARNING: This will clear all dynamic NAT translations.\n");
    printf("Confirm clear? (y/n): ");
    scanf("%c", &confirm);
    while (getchar() != '\n');

    if (confirm == 'y' || confirm == 'Y') {
        int cleared = 0;
        for (int i = 0; i < nat_count; i++) {
            // Only clear dynamic entries (static ones are preserved)
            if (nat_table[i].active && strcmp(nat_table[i].protocol, "---") != 0) {
                nat_table[i].active = 0;
                nat_stats.active_translations--;
                nat_stats.expired_translations++;
                cleared++;
            }
        }

        printf("\nRouter# clear ip nat translation *\n");
        printf("✓ Cleared %d dynamic NAT translation(s).\n", cleared);
        printf("  (Static translations preserved)\n");
    } else {
        printf("Clear operation cancelled.\n");
    }
}

void simulate_traffic(void) {
    char private_ips[][IP_LENGTH] = {
        "192.168.1.20",
        "192.168.1.21",
        "192.168.1.22",
        "192.168.1.23"
    };
    char dest_ips[][IP_LENGTH] = {
        "8.8.8.8",
        "1.1.1.1",
        "142.250.185.206",  // Google
        "157.240.1.35"      // Facebook
    };
    char protocols[][PROTO_LENGTH] = {"TCP", "UDP", "TCP", "TCP"};
    int src_ports[] = {45123, 33456, 52789, 41234};
    int dst_ports[] = {443, 53, 80, 443};

    printf("\n=== SIMULATING NETWORK TRAFFIC ===\n");
    printf("Generating NAT translations for outbound traffic...\n\n");

    for (int i = 0; i < 4; i++) {
        char inside_local[IP_LENGTH];
        char inside_global[IP_LENGTH];
        char outside[IP_LENGTH];
        int nat_port = get_next_port();

        snprintf(inside_local, sizeof(inside_local), "%s:%d", private_ips[i], src_ports[i]);
        snprintf(inside_global, sizeof(inside_global), "203.0.113.1:%d", nat_port);
        snprintf(outside, sizeof(outside), "%s:%d", dest_ips[i], dst_ports[i]);

        add_nat_entry(protocols[i], inside_local, inside_global, outside, outside, 0);
        nat_stats.packets_translated += rand() % 100 + 10;

        printf("  [%s] %s -> %s -> %s\n",
               protocols[i], inside_local, inside_global, outside);
    }

    printf("\n✓ Traffic simulation complete. %d new translations created.\n", 4);
    printf("  Use option 4 to view all translations.\n");
}

void demonstrate_nat_types(void) {
    printf("\n");


}

char* get_next_public_ip(void) {
    static int pool_index = 0;
    char *ip = public_ip_pool[pool_index % pool_size];
    pool_index++;
    return ip;
}

int get_next_port(void) {
    current_port++;
    if (current_port > 65535) {
        current_port = 1024;
    }
    return current_port;
}
