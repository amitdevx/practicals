/*
 * Slip 9 - Q2 Option B: Static Routing Simulation Program
 * 
 * This program simulates static routing by maintaining a routing table
 * and determining the best route for destination IP addresses using
 * longest prefix matching algorithm.
 *
 * Key Concepts:
 *   - Routing Table: Contains network, mask, next-hop, interface
 *   - Longest Prefix Match: Most specific route wins
 *   - Default Route: 0.0.0.0/0 used when no specific match
 *   - Static Routes: Manually configured, don't change automatically
 *
 * Compile: gcc -o static_routing Slip_09_Q2_OptionB.c
 * Run:     ./static_routing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROUTES 20
#define MAX_INTERFACES 10

/* Structure for a routing table entry */
typedef struct {
    unsigned int network;      /* Network address (32-bit) */
    unsigned int mask;         /* Subnet mask (32-bit) */
    unsigned int next_hop;     /* Next hop IP address */
    char interface[20];        /* Outgoing interface name */
    int prefix_length;         /* CIDR prefix length */
    int metric;                /* Route metric (lower = preferred) */
    int active;                /* Is route active? */
} Route;

/* Structure for the router */
typedef struct {
    Route table[MAX_ROUTES];
    int route_count;
    char hostname[50];
} Router;

/* Function prototypes */
unsigned int ip_to_int(const char *ip);
void int_to_ip(unsigned int ip, char *buffer);
void init_router(Router *router, const char *hostname);
void add_route(Router *router, const char *network, const char *mask, 
               const char *next_hop, const char *interface, int metric);
void add_default_route(Router *router, const char *next_hop, const char *interface);
Route* find_best_route(Router *router, unsigned int dest_ip);
void display_routing_table(Router *router);
void simulate_packet_forwarding(Router *router, const char *dest_ip);
int mask_to_prefix(unsigned int mask);
unsigned int prefix_to_mask(int prefix);
void display_route_lookup_process(Router *router, unsigned int dest_ip);

int main() {
    Router router;
    char dest_ip[20];
    int choice;

    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║            STATIC ROUTING SIMULATION PROGRAM                     ║\n");
    printf("║                     Slip 9 - Option B                            ║\n");
    printf("╚══════════════════════════════════════════════════════════════════╝\n\n");

    /* Initialize router */
    init_router(&router, "Router1");

    /* Add sample static routes */
    printf("📡 Configuring static routes...\n\n");
    
    /* Local networks (directly connected) */
    add_route(&router, "192.168.1.0", "255.255.255.0", "0.0.0.0", "eth0", 0);
    add_route(&router, "192.168.2.0", "255.255.255.0", "0.0.0.0", "eth1", 0);
    add_route(&router, "10.0.0.0", "255.255.255.0", "0.0.0.0", "eth2", 0);
    
    /* Remote networks (via next-hop) */
    add_route(&router, "172.16.0.0", "255.255.0.0", "192.168.1.254", "eth0", 10);
    add_route(&router, "172.16.10.0", "255.255.255.0", "192.168.1.253", "eth0", 5);
    add_route(&router, "10.10.0.0", "255.255.0.0", "10.0.0.254", "eth2", 10);
    add_route(&router, "8.8.8.0", "255.255.255.0", "192.168.2.1", "eth1", 20);
    
    /* Default route (gateway of last resort) */
    add_default_route(&router, "192.168.2.1", "eth1");

    /* Display routing table */
    display_routing_table(&router);

    /* Main menu loop */
    do {
        printf("\n┌────────────────────────────────────────────────────────────────┐\n");
        printf("│                         MAIN MENU                              │\n");
        printf("├────────────────────────────────────────────────────────────────┤\n");
        printf("│  1. Simulate Packet Forwarding                                 │\n");
        printf("│  2. Display Routing Table                                      │\n");
        printf("│  3. Add New Static Route                                       │\n");
        printf("│  4. Show Route Lookup Process (Detailed)                       │\n");
        printf("│  5. Exit                                                       │\n");
        printf("└────────────────────────────────────────────────────────────────┘\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter destination IP address: ");
                scanf("%s", dest_ip);
                simulate_packet_forwarding(&router, dest_ip);
                break;
                
            case 2:
                display_routing_table(&router);
                break;
                
            case 3: {
                char network[20], mask[20], next_hop[20], interface[20];
                int metric;
                printf("\nEnter network address: ");
                scanf("%s", network);
                printf("Enter subnet mask: ");
                scanf("%s", mask);
                printf("Enter next-hop IP (0.0.0.0 for directly connected): ");
                scanf("%s", next_hop);
                printf("Enter interface name: ");
                scanf("%s", interface);
                printf("Enter metric: ");
                scanf("%d", &metric);
                add_route(&router, network, mask, next_hop, interface, metric);
                printf("✅ Route added successfully!\n");
                break;
            }
            
            case 4:
                printf("\nEnter destination IP address: ");
                scanf("%s", dest_ip);
                display_route_lookup_process(&router, ip_to_int(dest_ip));
                break;
                
            case 5:
                printf("\nExiting Static Routing Simulation. Goodbye!\n");
                break;
                
            default:
                printf("❌ Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

/*
 * Converts IP address string to 32-bit integer
 */
unsigned int ip_to_int(const char *ip) {
    unsigned int octets[4];
    sscanf(ip, "%u.%u.%u.%u", &octets[0], &octets[1], &octets[2], &octets[3]);
    return (octets[0] << 24) | (octets[1] << 16) | (octets[2] << 8) | octets[3];
}

/*
 * Converts 32-bit integer to IP address string
 */
void int_to_ip(unsigned int ip, char *buffer) {
    sprintf(buffer, "%u.%u.%u.%u",
            (ip >> 24) & 0xFF,
            (ip >> 16) & 0xFF,
            (ip >> 8) & 0xFF,
            ip & 0xFF);
}

/*
 * Converts subnet mask to CIDR prefix length
 */
int mask_to_prefix(unsigned int mask) {
    int prefix = 0;
    while (mask) {
        prefix += mask & 1;
        mask >>= 1;
    }
    return prefix;
}

/*
 * Converts CIDR prefix length to subnet mask
 */
unsigned int prefix_to_mask(int prefix) {
    if (prefix == 0) return 0;
    return ~((1U << (32 - prefix)) - 1);
}

/*
 * Initializes the router structure
 */
void init_router(Router *router, const char *hostname) {
    strcpy(router->hostname, hostname);
    router->route_count = 0;
    memset(router->table, 0, sizeof(router->table));
}

/*
 * Adds a static route to the routing table
 */
void add_route(Router *router, const char *network, const char *mask,
               const char *next_hop, const char *interface, int metric) {
    if (router->route_count >= MAX_ROUTES) {
        printf("❌ Error: Routing table full!\n");
        return;
    }

    Route *route = &router->table[router->route_count];
    route->network = ip_to_int(network);
    route->mask = ip_to_int(mask);
    route->next_hop = ip_to_int(next_hop);
    strcpy(route->interface, interface);
    route->prefix_length = mask_to_prefix(route->mask);
    route->metric = metric;
    route->active = 1;

    router->route_count++;
}

/*
 * Adds a default route (0.0.0.0/0)
 */
void add_default_route(Router *router, const char *next_hop, const char *interface) {
    add_route(router, "0.0.0.0", "0.0.0.0", next_hop, interface, 100);
}

/*
 * Finds the best matching route using longest prefix match
 */
Route* find_best_route(Router *router, unsigned int dest_ip) {
    Route *best_route = NULL;
    int longest_prefix = -1;
    int i;

    for (i = 0; i < router->route_count; i++) {
        Route *route = &router->table[i];
        
        if (!route->active) continue;
        
        /* Apply mask to destination and compare with network */
        unsigned int masked_dest = dest_ip & route->mask;
        
        if (masked_dest == route->network) {
            /* Longest prefix match wins */
            if (route->prefix_length > longest_prefix) {
                longest_prefix = route->prefix_length;
                best_route = route;
            }
            /* If same prefix, lower metric wins */
            else if (route->prefix_length == longest_prefix && best_route != NULL) {
                if (route->metric < best_route->metric) {
                    best_route = route;
                }
            }
        }
    }

    return best_route;
}

/*
 * Displays the routing table in a formatted manner
 */
void display_routing_table(Router *router) {
    char network_str[20], mask_str[20], next_hop_str[20];
    int i;

    printf("\n╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                    ROUTING TABLE - %s                              ║\n", router->hostname);
    printf("╠══════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║  Network           Mask              Next-Hop         Interface   Metric    ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════╣\n");

    for (i = 0; i < router->route_count; i++) {
        Route *route = &router->table[i];
        
        int_to_ip(route->network, network_str);
        int_to_ip(route->mask, mask_str);
        int_to_ip(route->next_hop, next_hop_str);

        printf("║  %-17s %-17s %-16s %-10s %-8d ║\n",
               network_str, mask_str, 
               route->next_hop == 0 ? "Directly Conn." : next_hop_str,
               route->interface, route->metric);
    }

    printf("╚══════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Total routes: %d\n", router->route_count);
}

/*
 * Simulates packet forwarding for a destination IP
 */
void simulate_packet_forwarding(Router *router, const char *dest_ip) {
    unsigned int dest = ip_to_int(dest_ip);
    char next_hop_str[20], network_str[20], mask_str[20];

    printf("\n┌──────────────────────────────────────────────────────────────────┐\n");
    printf("│                   PACKET FORWARDING SIMULATION                   │\n");
    printf("├──────────────────────────────────────────────────────────────────┤\n");
    printf("│ Destination IP: %-48s │\n", dest_ip);
    printf("└──────────────────────────────────────────────────────────────────┘\n\n");

    /* Find best route */
    Route *best_route = find_best_route(router, dest);

    if (best_route == NULL) {
        printf("❌ NO ROUTE TO HOST!\n");
        printf("   Packet would be dropped (ICMP Destination Unreachable)\n");
        return;
    }

    int_to_ip(best_route->network, network_str);
    int_to_ip(best_route->mask, mask_str);
    int_to_ip(best_route->next_hop, next_hop_str);

    printf("✅ ROUTE FOUND!\n\n");
    printf("┌──────────────────────────────────────────────────────────────────┐\n");
    printf("│ Routing Decision:                                                │\n");
    printf("├──────────────────────────────────────────────────────────────────┤\n");
    printf("│ Matched Network:  %s/%d\n", network_str, best_route->prefix_length);
    printf("│ Subnet Mask:      %s\n", mask_str);
    
    if (best_route->next_hop == 0) {
        printf("│ Action:           DELIVER DIRECTLY (Connected Network)\n");
        printf("│ Interface:        %s\n", best_route->interface);
    } else {
        printf("│ Next-Hop:         %s\n", next_hop_str);
        printf("│ Interface:        %s\n", best_route->interface);
    }
    printf("│ Metric:           %d\n", best_route->metric);
    printf("└──────────────────────────────────────────────────────────────────┘\n");

    /* Visual representation */
    printf("\n📦 Packet Flow:\n");
    if (best_route->next_hop == 0) {
        printf("   [Packet] ──► [%s] ──► [%s] (Direct Delivery)\n",
               router->hostname, dest_ip);
    } else {
        printf("   [Packet] ──► [%s] ──► [%s] ──► [%s] ──► ... ──► [%s]\n",
               router->hostname, best_route->interface, next_hop_str, dest_ip);
    }
}

/*
 * Displays detailed route lookup process
 */
void display_route_lookup_process(Router *router, unsigned int dest_ip) {
    char dest_str[20], network_str[20], mask_str[20], masked_str[20];
    int i;
    
    int_to_ip(dest_ip, dest_str);
    
    printf("\n╔════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║              ROUTE LOOKUP PROCESS (Longest Prefix Match)                   ║\n");
    printf("╠════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║ Destination: %-63s ║\n", dest_str);
    printf("╚════════════════════════════════════════════════════════════════════════════╝\n\n");
    
    printf("Checking each route in table:\n");
    printf("────────────────────────────────────────────────────────────────────────────\n");
    
    Route *best_route = NULL;
    int longest_prefix = -1;
    
    for (i = 0; i < router->route_count; i++) {
        Route *route = &router->table[i];
        
        int_to_ip(route->network, network_str);
        int_to_ip(route->mask, mask_str);
        
        unsigned int masked_dest = dest_ip & route->mask;
        int_to_ip(masked_dest, masked_str);
        
        printf("\nRoute %d: %s/%d\n", i + 1, network_str, route->prefix_length);
        printf("  ├─ Mask applied:  %s AND %s = %s\n", dest_str, mask_str, masked_str);
        printf("  ├─ Compare with:  %s\n", network_str);
        
        if (masked_dest == route->network) {
            printf("  └─ Result: ✅ MATCH (prefix length: %d)\n", route->prefix_length);
            
            if (route->prefix_length > longest_prefix) {
                longest_prefix = route->prefix_length;
                best_route = route;
                printf("     └─ 🎯 New best match!\n");
            } else if (best_route != NULL && route->prefix_length == longest_prefix) {
                if (route->metric < best_route->metric) {
                    best_route = route;
                    printf("     └─ 🎯 Better metric, new best match!\n");
                } else {
                    printf("     └─ ❌ Same prefix but higher/equal metric, skipped\n");
                }
            }
        } else {
            printf("  └─ Result: ❌ NO MATCH\n");
        }
    }
    
    printf("\n────────────────────────────────────────────────────────────────────────────\n");
    
    if (best_route != NULL) {
        int_to_ip(best_route->network, network_str);
        char next_hop_str[20];
        int_to_ip(best_route->next_hop, next_hop_str);
        
        printf("\n🏆 BEST ROUTE SELECTED:\n");
        printf("   Network: %s/%d\n", network_str, best_route->prefix_length);
        printf("   Next-Hop: %s\n", best_route->next_hop == 0 ? "Direct" : next_hop_str);
        printf("   Interface: %s\n", best_route->interface);
    } else {
        printf("\n❌ NO MATCHING ROUTE FOUND - Packet dropped!\n");
    }
}

/*
 * SAMPLE OUTPUT:
 * ════════════════════════════════════════════════════════════════════════════════
 * 
 * ╔══════════════════════════════════════════════════════════════════╗
 * ║            STATIC ROUTING SIMULATION PROGRAM                     ║
 * ║                     Slip 9 - Option B                            ║
 * ╚══════════════════════════════════════════════════════════════════╝
 * 
 * 📡 Configuring static routes...
 * 
 * ╔══════════════════════════════════════════════════════════════════════════════╗
 * ║                    ROUTING TABLE - Router1                              ║
 * ╠══════════════════════════════════════════════════════════════════════════════╣
 * ║  Network           Mask              Next-Hop         Interface   Metric    ║
 * ╠══════════════════════════════════════════════════════════════════════════════╣
 * ║  192.168.1.0       255.255.255.0     Directly Conn.   eth0       0         ║
 * ║  192.168.2.0       255.255.255.0     Directly Conn.   eth1       0         ║
 * ║  10.0.0.0          255.255.255.0     Directly Conn.   eth2       0         ║
 * ║  172.16.0.0        255.255.0.0       192.168.1.254    eth0       10        ║
 * ║  172.16.10.0       255.255.255.0     192.168.1.253    eth0       5         ║
 * ║  10.10.0.0         255.255.0.0       10.0.0.254       eth2       10        ║
 * ║  8.8.8.0           255.255.255.0     192.168.2.1      eth1       20        ║
 * ║  0.0.0.0           0.0.0.0           192.168.2.1      eth1       100       ║
 * ╚══════════════════════════════════════════════════════════════════════════════╝
 * Total routes: 8
 * 
 * Enter destination IP address: 172.16.10.50
 * 
 * ┌──────────────────────────────────────────────────────────────────┐
 * │                   PACKET FORWARDING SIMULATION                   │
 * ├──────────────────────────────────────────────────────────────────┤
 * │ Destination IP: 172.16.10.50                                     │
 * └──────────────────────────────────────────────────────────────────┘
 * 
 * ✅ ROUTE FOUND!
 * 
 * ┌──────────────────────────────────────────────────────────────────┐
 * │ Routing Decision:                                                │
 * ├──────────────────────────────────────────────────────────────────┤
 * │ Matched Network:  172.16.10.0/24
 * │ Subnet Mask:      255.255.255.0
 * │ Next-Hop:         192.168.1.253
 * │ Interface:        eth0
 * │ Metric:           5
 * └──────────────────────────────────────────────────────────────────┘
 * 
 * 📦 Packet Flow:
 *    [Packet] ──► [Router1] ──► [eth0] ──► [192.168.1.253] ──► ... ──► [172.16.10.50]
 */
