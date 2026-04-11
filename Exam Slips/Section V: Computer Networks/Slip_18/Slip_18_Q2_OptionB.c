/*
 * Slip 18 - Q2 Option B: NAT (Network Address Translation) System Simulation
 * 
 * This program simulates a NAT system that translates private IP addresses
 * to public IP addresses, demonstrating how home/office routers allow
 * multiple devices to share a single public IP address.
 * 
 * Features:
 * - Static NAT (1:1 mapping)
 * - Dynamic NAT (pool-based)
 * - PAT/NAT Overload (port-based, many:1)
 * - Translation table management
 * - Packet simulation
 * 
 * Compile: gcc Slip_18_Q2_OptionB.c -o nat_sim
 * Run: ./nat_sim
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAT_ENTRIES 100
#define MAX_IP_LEN 16
#define MAX_STATIC_MAPPINGS 10
#define PUBLIC_IP "203.0.113.1"
#define STARTING_PORT 10000
#define MAX_PORT 65535

/* NAT entry types */
typedef enum {
    NAT_STATIC,
    NAT_DYNAMIC,
    NAT_PAT
} NATType;

/* Protocol types */
typedef enum {
    PROTO_TCP,
    PROTO_UDP,
    PROTO_ICMP
} Protocol;

/* NAT table entry structure */
typedef struct {
    int active;                     /* Entry is in use */
    char private_ip[MAX_IP_LEN];    /* Internal private IP */
    int private_port;               /* Internal port */
    char public_ip[MAX_IP_LEN];     /* External public IP */
    int public_port;                /* External port */
    char dest_ip[MAX_IP_LEN];       /* Destination IP */
    int dest_port;                  /* Destination port */
    Protocol protocol;              /* TCP/UDP/ICMP */
    NATType nat_type;               /* Static/Dynamic/PAT */
    time_t timestamp;               /* Entry creation time */
    time_t last_used;               /* Last activity time */
    unsigned long packets_in;       /* Inbound packet count */
    unsigned long packets_out;      /* Outbound packet count */
} NATEntry;

/* Static NAT mapping */
typedef struct {
    int active;
    char private_ip[MAX_IP_LEN];
    char public_ip[MAX_IP_LEN];
} StaticMapping;

/* Packet structure for simulation */
typedef struct {
    char src_ip[MAX_IP_LEN];
    int src_port;
    char dst_ip[MAX_IP_LEN];
    int dst_port;
    Protocol protocol;
    char data[64];
    int is_outbound;    /* 1 = outbound, 0 = inbound */
} Packet;

/* Global NAT table and state */
NATEntry nat_table[MAX_NAT_ENTRIES];
StaticMapping static_mappings[MAX_STATIC_MAPPINGS];
int nat_entry_count = 0;
int static_mapping_count = 0;
int next_available_port = STARTING_PORT;
char router_public_ip[MAX_IP_LEN] = PUBLIC_IP;
unsigned long total_packets_translated = 0;

/* Function prototypes */
void init_nat_system(void);
int add_static_nat(const char *private_ip, const char *public_ip);
int find_nat_entry(const char *private_ip, int private_port, Protocol proto);
int find_nat_entry_by_public(int public_port, Protocol proto);
int create_pat_entry(const char *private_ip, int private_port,
                     const char *dest_ip, int dest_port, Protocol proto);
int translate_outbound(Packet *packet);
int translate_inbound(Packet *packet);
void display_nat_table(void);
void display_static_mappings(void);
void display_statistics(void);
void cleanup_expired_entries(void);
void simulate_traffic(void);
void interactive_mode(void);
const char* protocol_to_string(Protocol proto);
const char* nat_type_to_string(NATType type);
void print_packet(const Packet *pkt, const char *direction);

/* Protocol to string conversion */
const char* protocol_to_string(Protocol proto) {
    switch (proto) {
        case PROTO_TCP: return "TCP";
        case PROTO_UDP: return "UDP";
        case PROTO_ICMP: return "ICMP";
        default: return "UNKNOWN";
    }
}

/* NAT type to string conversion */
const char* nat_type_to_string(NATType type) {
    switch (type) {
        case NAT_STATIC: return "Static";
        case NAT_DYNAMIC: return "Dynamic";
        case NAT_PAT: return "PAT/Overload";
        default: return "Unknown";
    }
}

/* Initialize NAT system */
void init_nat_system(void) {
    memset(nat_table, 0, sizeof(nat_table));
    memset(static_mappings, 0, sizeof(static_mappings));
    nat_entry_count = 0;
    static_mapping_count = 0;
    next_available_port = STARTING_PORT;
    total_packets_translated = 0;
    
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║           NAT System Initialized Successfully                 ║\n");
    printf("╠═══════════════════════════════════════════════════════════════╣\n");
    printf("║  Public IP (Outside Interface): %-28s  ║\n", router_public_ip);
    printf("║  Private Network: 192.168.1.0/24                              ║\n");
    printf("║  PAT Port Range: %d - %d                             ║\n", STARTING_PORT, MAX_PORT);
    printf("╚═══════════════════════════════════════════════════════════════╝\n\n");
}

/* Add static NAT mapping (1:1) */
int add_static_nat(const char *private_ip, const char *public_ip) {
    if (static_mapping_count >= MAX_STATIC_MAPPINGS) {
        printf("Error: Maximum static NAT mappings reached\n");
        return -1;
    }
    
    /* Check for duplicate */
    for (int i = 0; i < MAX_STATIC_MAPPINGS; i++) {
        if (static_mappings[i].active &&
            strcmp(static_mappings[i].private_ip, private_ip) == 0) {
            printf("Error: Static mapping already exists for %s\n", private_ip);
            return -1;
        }
    }
    
    /* Find empty slot */
    for (int i = 0; i < MAX_STATIC_MAPPINGS; i++) {
        if (!static_mappings[i].active) {
            static_mappings[i].active = 1;
            strncpy(static_mappings[i].private_ip, private_ip, MAX_IP_LEN - 1);
            strncpy(static_mappings[i].public_ip, public_ip, MAX_IP_LEN - 1);
            static_mapping_count++;
            
            printf("✓ Static NAT added: %s <-> %s\n", private_ip, public_ip);
            return i;
        }
    }
    
    return -1;
}

/* Find existing NAT entry by private IP/port */
int find_nat_entry(const char *private_ip, int private_port, Protocol proto) {
    for (int i = 0; i < MAX_NAT_ENTRIES; i++) {
        if (nat_table[i].active &&
            strcmp(nat_table[i].private_ip, private_ip) == 0 &&
            nat_table[i].private_port == private_port &&
            nat_table[i].protocol == proto) {
            return i;
        }
    }
    return -1;
}

/* Find NAT entry by public port (for inbound translation) */
int find_nat_entry_by_public(int public_port, Protocol proto) {
    for (int i = 0; i < MAX_NAT_ENTRIES; i++) {
        if (nat_table[i].active &&
            nat_table[i].public_port == public_port &&
            nat_table[i].protocol == proto) {
            return i;
        }
    }
    return -1;
}

/* Create new PAT (Port Address Translation) entry */
int create_pat_entry(const char *private_ip, int private_port,
                     const char *dest_ip, int dest_port, Protocol proto) {
    if (nat_entry_count >= MAX_NAT_ENTRIES) {
        printf("Error: NAT table full\n");
        return -1;
    }
    
    /* Find empty slot */
    int slot = -1;
    for (int i = 0; i < MAX_NAT_ENTRIES; i++) {
        if (!nat_table[i].active) {
            slot = i;
            break;
        }
    }
    
    if (slot == -1) {
        printf("Error: No available NAT table slots\n");
        return -1;
    }
    
    /* Check port availability */
    if (next_available_port > MAX_PORT) {
        printf("Error: Port pool exhausted\n");
        return -1;
    }
    
    /* Create entry */
    nat_table[slot].active = 1;
    strncpy(nat_table[slot].private_ip, private_ip, MAX_IP_LEN - 1);
    nat_table[slot].private_port = private_port;
    strncpy(nat_table[slot].public_ip, router_public_ip, MAX_IP_LEN - 1);
    nat_table[slot].public_port = next_available_port++;
    strncpy(nat_table[slot].dest_ip, dest_ip, MAX_IP_LEN - 1);
    nat_table[slot].dest_port = dest_port;
    nat_table[slot].protocol = proto;
    nat_table[slot].nat_type = NAT_PAT;
    nat_table[slot].timestamp = time(NULL);
    nat_table[slot].last_used = time(NULL);
    nat_table[slot].packets_in = 0;
    nat_table[slot].packets_out = 0;
    
    nat_entry_count++;
    
    return slot;
}

/* Translate outbound packet (private -> public) */
int translate_outbound(Packet *packet) {
    printf("\n┌─ OUTBOUND TRANSLATION ─────────────────────────────────────────┐\n");
    print_packet(packet, "ORIGINAL");
    
    /* Check for static NAT mapping first */
    for (int i = 0; i < MAX_STATIC_MAPPINGS; i++) {
        if (static_mappings[i].active &&
            strcmp(static_mappings[i].private_ip, packet->src_ip) == 0) {
            /* Static NAT - translate IP only */
            printf("│ Using Static NAT mapping                                      │\n");
            strncpy(packet->src_ip, static_mappings[i].public_ip, MAX_IP_LEN - 1);
            print_packet(packet, "TRANSLATED");
            printf("└────────────────────────────────────────────────────────────────┘\n");
            total_packets_translated++;
            return 0;
        }
    }
    
    /* PAT - Check for existing translation */
    int entry = find_nat_entry(packet->src_ip, packet->src_port, packet->protocol);
    
    if (entry == -1) {
        /* Create new PAT entry */
        entry = create_pat_entry(packet->src_ip, packet->src_port,
                                packet->dst_ip, packet->dst_port, packet->protocol);
        if (entry == -1) {
            printf("│ ERROR: Failed to create NAT entry                             │\n");
            printf("└────────────────────────────────────────────────────────────────┘\n");
            return -1;
        }
        printf("│ Created new PAT entry (index: %d)                              │\n", entry);
    } else {
        printf("│ Using existing PAT entry (index: %d)                           │\n", entry);
    }
    
    /* Perform translation */
    strncpy(packet->src_ip, nat_table[entry].public_ip, MAX_IP_LEN - 1);
    packet->src_port = nat_table[entry].public_port;
    nat_table[entry].packets_out++;
    nat_table[entry].last_used = time(NULL);
    
    print_packet(packet, "TRANSLATED");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    
    total_packets_translated++;
    return 0;
}

/* Translate inbound packet (public -> private) */
int translate_inbound(Packet *packet) {
    printf("\n┌─ INBOUND TRANSLATION ──────────────────────────────────────────┐\n");
    print_packet(packet, "ORIGINAL");
    
    /* Check for static NAT mapping first */
    for (int i = 0; i < MAX_STATIC_MAPPINGS; i++) {
        if (static_mappings[i].active &&
            strcmp(static_mappings[i].public_ip, packet->dst_ip) == 0) {
            /* Static NAT - translate IP only */
            printf("│ Using Static NAT mapping                                      │\n");
            strncpy(packet->dst_ip, static_mappings[i].private_ip, MAX_IP_LEN - 1);
            print_packet(packet, "TRANSLATED");
            printf("└────────────────────────────────────────────────────────────────┘\n");
            total_packets_translated++;
            return 0;
        }
    }
    
    /* PAT - Find translation by public port */
    int entry = find_nat_entry_by_public(packet->dst_port, packet->protocol);
    
    if (entry == -1) {
        printf("│ ERROR: No NAT entry found for port %d                         │\n", packet->dst_port);
        printf("│ Packet dropped - no translation available                     │\n");
        printf("└────────────────────────────────────────────────────────────────┘\n");
        return -1;
    }
    
    printf("│ Found PAT entry (index: %d)                                    │\n", entry);
    
    /* Perform translation */
    strncpy(packet->dst_ip, nat_table[entry].private_ip, MAX_IP_LEN - 1);
    packet->dst_port = nat_table[entry].private_port;
    nat_table[entry].packets_in++;
    nat_table[entry].last_used = time(NULL);
    
    print_packet(packet, "TRANSLATED");
    printf("└────────────────────────────────────────────────────────────────┘\n");
    
    total_packets_translated++;
    return 0;
}

/* Print packet information */
void print_packet(const Packet *pkt, const char *direction) {
    printf("│ %-10s: %s:%d -> %s:%d [%s]         \n",
           direction, pkt->src_ip, pkt->src_port,
           pkt->dst_ip, pkt->dst_port, protocol_to_string(pkt->protocol));
}

/* Display NAT translation table */
void display_nat_table(void) {
    printf("\n╔═══════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              NAT TRANSLATION TABLE (PAT Entries)                          ║\n");
    printf("╠═══════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║ Idx │ Private IP:Port      │ Public IP:Port        │ Dest IP:Port         │ Proto │ Pkts  ║\n");
    printf("╠═══════════════════════════════════════════════════════════════════════════════════════════╣\n");
    
    int displayed = 0;
    for (int i = 0; i < MAX_NAT_ENTRIES; i++) {
        if (nat_table[i].active) {
            char priv_addr[32], pub_addr[32], dest_addr[32];
            sprintf(priv_addr, "%s:%d", nat_table[i].private_ip, nat_table[i].private_port);
            sprintf(pub_addr, "%s:%d", nat_table[i].public_ip, nat_table[i].public_port);
            sprintf(dest_addr, "%s:%d", nat_table[i].dest_ip, nat_table[i].dest_port);
            
            printf("║ %3d │ %-20s │ %-21s │ %-20s │ %-5s │ %-5lu ║\n",
                   i, priv_addr, pub_addr, dest_addr,
                   protocol_to_string(nat_table[i].protocol),
                   nat_table[i].packets_in + nat_table[i].packets_out);
            displayed++;
        }
    }
    
    if (displayed == 0) {
        printf("║                          No active translations                                           ║\n");
    }
    
    printf("╚═══════════════════════════════════════════════════════════════════════════════════════════╝\n");
}

/* Display static NAT mappings */
void display_static_mappings(void) {
    printf("\n╔═════════════════════════════════════════════════════════════════╗\n");
    printf("║                 STATIC NAT MAPPINGS (1:1)                       ║\n");
    printf("╠═════════════════════════════════════════════════════════════════╣\n");
    printf("║   Private IP           │          Public IP                    ║\n");
    printf("╠═════════════════════════════════════════════════════════════════╣\n");
    
    int displayed = 0;
    for (int i = 0; i < MAX_STATIC_MAPPINGS; i++) {
        if (static_mappings[i].active) {
            printf("║   %-20s │          %-20s         ║\n",
                   static_mappings[i].private_ip,
                   static_mappings[i].public_ip);
            displayed++;
        }
    }
    
    if (displayed == 0) {
        printf("║              No static NAT mappings configured                ║\n");
    }
    
    printf("╚═════════════════════════════════════════════════════════════════╝\n");
}

/* Display NAT statistics */
void display_statistics(void) {
    printf("\n╔═════════════════════════════════════════════════════════════════╗\n");
    printf("║                      NAT STATISTICS                             ║\n");
    printf("╠═════════════════════════════════════════════════════════════════╣\n");
    printf("║  Router Public IP:     %-38s  ║\n", router_public_ip);
    printf("║  Active PAT Entries:   %-38d  ║\n", nat_entry_count);
    printf("║  Static Mappings:      %-38d  ║\n", static_mapping_count);
    printf("║  Next Available Port:  %-38d  ║\n", next_available_port);
    printf("║  Total Packets:        %-38lu  ║\n", total_packets_translated);
    printf("╚═════════════════════════════════════════════════════════════════╝\n");
}

/* Clean up expired NAT entries (timeout: 5 minutes for demo) */
void cleanup_expired_entries(void) {
    time_t now = time(NULL);
    int cleaned = 0;
    
    for (int i = 0; i < MAX_NAT_ENTRIES; i++) {
        if (nat_table[i].active) {
            /* 5 minute timeout for demo */
            if (now - nat_table[i].last_used > 300) {
                nat_table[i].active = 0;
                nat_entry_count--;
                cleaned++;
            }
        }
    }
    
    if (cleaned > 0) {
        printf("Cleaned %d expired NAT entries\n", cleaned);
    }
}

/* Simulate network traffic */
void simulate_traffic(void) {
    Packet packets[] = {
        /* Outbound packets from internal network */
        {"192.168.1.10", 45001, "8.8.8.8", 53, PROTO_UDP, "DNS Query", 1},
        {"192.168.1.10", 45002, "93.184.216.34", 80, PROTO_TCP, "HTTP GET", 1},
        {"192.168.1.20", 50001, "93.184.216.34", 443, PROTO_TCP, "HTTPS", 1},
        {"192.168.1.30", 55001, "1.1.1.1", 53, PROTO_UDP, "DNS Query", 1},
        {"192.168.1.10", 45003, "142.250.190.46", 443, PROTO_TCP, "Google", 1},
    };
    
    int num_packets = sizeof(packets) / sizeof(packets[0]);
    
    printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║             SIMULATING OUTBOUND TRAFFIC                       ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    
    for (int i = 0; i < num_packets; i++) {
        translate_outbound(&packets[i]);
    }
    
    display_nat_table();
    
    /* Simulate inbound responses */
    printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║             SIMULATING INBOUND RESPONSES                      ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    
    /* Response to first DNS query */
    Packet response1 = {"8.8.8.8", 53, "203.0.113.1", STARTING_PORT, PROTO_UDP, "DNS Response", 0};
    translate_inbound(&response1);
    
    /* Response to HTTP request */
    Packet response2 = {"93.184.216.34", 80, "203.0.113.1", STARTING_PORT + 1, PROTO_TCP, "HTTP 200", 0};
    translate_inbound(&response2);
    
    display_statistics();
}

/* Interactive mode */
void interactive_mode(void) {
    int choice;
    char priv_ip[MAX_IP_LEN], pub_ip[MAX_IP_LEN];
    int proto;
    Packet pkt;
    
    while (1) {
        printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
        printf("║                  NAT SIMULATOR - MENU                         ║\n");
        printf("╠═══════════════════════════════════════════════════════════════╣\n");
        printf("║  [1] Add Static NAT Mapping                                   ║\n");
        printf("║  [2] Simulate Outbound Packet                                 ║\n");
        printf("║  [3] Simulate Inbound Packet                                  ║\n");
        printf("║  [4] View NAT Translation Table                               ║\n");
        printf("║  [5] View Static Mappings                                     ║\n");
        printf("║  [6] View Statistics                                          ║\n");
        printf("║  [7] Run Traffic Simulation                                   ║\n");
        printf("║  [8] Clear NAT Table                                          ║\n");
        printf("║  [0] Exit                                                     ║\n");
        printf("╚═══════════════════════════════════════════════════════════════╝\n");
        printf("\nEnter choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        
        switch (choice) {
            case 1:
                printf("Enter private IP (e.g., 192.168.1.100): ");
                scanf("%15s", priv_ip);
                printf("Enter public IP (e.g., 203.0.113.100): ");
                scanf("%15s", pub_ip);
                add_static_nat(priv_ip, pub_ip);
                break;
                
            case 2:
                printf("Enter source private IP: ");
                scanf("%15s", pkt.src_ip);
                printf("Enter source port: ");
                scanf("%d", &pkt.src_port);
                printf("Enter destination IP: ");
                scanf("%15s", pkt.dst_ip);
                printf("Enter destination port: ");
                scanf("%d", &pkt.dst_port);
                printf("Protocol (1=TCP, 2=UDP): ");
                scanf("%d", &proto);
                pkt.protocol = (proto == 2) ? PROTO_UDP : PROTO_TCP;
                pkt.is_outbound = 1;
                translate_outbound(&pkt);
                break;
                
            case 3:
                printf("Enter source IP: ");
                scanf("%15s", pkt.src_ip);
                printf("Enter source port: ");
                scanf("%d", &pkt.src_port);
                printf("Enter destination port (NAT public port): ");
                scanf("%d", &pkt.dst_port);
                strcpy(pkt.dst_ip, router_public_ip);
                printf("Protocol (1=TCP, 2=UDP): ");
                scanf("%d", &proto);
                pkt.protocol = (proto == 2) ? PROTO_UDP : PROTO_TCP;
                pkt.is_outbound = 0;
                translate_inbound(&pkt);
                break;
                
            case 4:
                display_nat_table();
                break;
                
            case 5:
                display_static_mappings();
                break;
                
            case 6:
                display_statistics();
                break;
                
            case 7:
                simulate_traffic();
                break;
                
            case 8:
                memset(nat_table, 0, sizeof(nat_table));
                nat_entry_count = 0;
                next_available_port = STARTING_PORT;
                printf("NAT table cleared.\n");
                break;
                
            case 0:
                printf("Exiting NAT Simulator. Goodbye!\n");
                return;
                
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

/* Main function */
int main(void) {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════════╗\n");
    printf("║     NETWORK ADDRESS TRANSLATION (NAT) SYSTEM SIMULATION          ║\n");
    printf("║                                                                   ║\n");
    printf("║   This program demonstrates how NAT translates IP addresses      ║\n");
    printf("║   allowing multiple private hosts to share public IP(s).         ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════╝\n\n");
    
    /* Initialize NAT system */
    init_nat_system();
    
    /* Add some default static NAT mappings */
    add_static_nat("192.168.1.100", "203.0.113.100");  /* Web server */
    add_static_nat("192.168.1.101", "203.0.113.101");  /* Mail server */
    
    display_static_mappings();
    
    /* Start interactive mode */
    interactive_mode();
    
    return 0;
}

/*
 * Sample Output:
 * 
 * ╔═══════════════════════════════════════════════════════════════════╗
 * ║     NETWORK ADDRESS TRANSLATION (NAT) SYSTEM SIMULATION          ║
 * ╚═══════════════════════════════════════════════════════════════════╝
 * 
 * ╔═══════════════════════════════════════════════════════════════╗
 * ║           NAT System Initialized Successfully                 ║
 * ╠═══════════════════════════════════════════════════════════════╣
 * ║  Public IP (Outside Interface): 203.0.113.1                   ║
 * ║  Private Network: 192.168.1.0/24                              ║
 * ║  PAT Port Range: 10000 - 65535                                ║
 * ╚═══════════════════════════════════════════════════════════════╝
 * 
 * ✓ Static NAT added: 192.168.1.100 <-> 203.0.113.100
 * ✓ Static NAT added: 192.168.1.101 <-> 203.0.113.101
 * 
 * ┌─ OUTBOUND TRANSLATION ─────────────────────────────────────────┐
 * │ ORIGINAL  : 192.168.1.10:45001 -> 8.8.8.8:53 [UDP]             │
 * │ Created new PAT entry (index: 0)                               │
 * │ TRANSLATED: 203.0.113.1:10000 -> 8.8.8.8:53 [UDP]              │
 * └────────────────────────────────────────────────────────────────┘
 * 
 * ╔═══════════════════════════════════════════════════════════════════════════════════════════╗
 * ║                              NAT TRANSLATION TABLE (PAT Entries)                          ║
 * ╠═══════════════════════════════════════════════════════════════════════════════════════════╣
 * ║ Idx │ Private IP:Port      │ Public IP:Port        │ Dest IP:Port         │ Proto │ Pkts  ║
 * ╠═══════════════════════════════════════════════════════════════════════════════════════════╣
 * ║   0 │ 192.168.1.10:45001   │ 203.0.113.1:10000     │ 8.8.8.8:53           │ UDP   │ 1     ║
 * ║   1 │ 192.168.1.10:45002   │ 203.0.113.1:10001     │ 93.184.216.34:80     │ TCP   │ 1     ║
 * ╚═══════════════════════════════════════════════════════════════════════════════════════════╝
 */
