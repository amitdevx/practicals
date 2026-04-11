/*
 * ============================================================================
 * Slip 14 - Q2 Option A: Static Routing Simulation Program
 * ============================================================================
 *
 * This program simulates a static routing network where routers have
 * pre-configured routing tables. It demonstrates:
 * - Routing table structure and lookup
 * - Longest prefix matching
 * - Packet forwarding between networks
 * - Route management (add, delete, display)
 *
 * Compile: gcc -o static_routing Slip_14_Q2_OptionA.c
 * Run:     ./static_routing
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ROUTES 100
#define MAX_ROUTERS 10
#define MAX_INTERFACES 4
#define IP_ADDR_LEN 16

/* Structure to represent an IP address */
typedef struct {
    unsigned char octets[4];
} IPAddress;

/* Structure for a routing table entry */
typedef struct {
    IPAddress network;          /* Destination network */
    IPAddress subnet_mask;      /* Subnet mask */
    IPAddress next_hop;         /* Next hop IP address */
    char interface_name[20];    /* Outgoing interface */
    int metric;                 /* Route metric (cost) */
    bool is_active;             /* Is route active */
    char route_type;            /* C=Connected, S=Static */
} RouteEntry;

/* Structure for a router interface */
typedef struct {
    char name[20];              /* Interface name (e.g., Gig0/0) */
    IPAddress ip_address;       /* Interface IP address */
    IPAddress subnet_mask;      /* Interface subnet mask */
    bool is_up;                 /* Interface status */
} Interface;

/* Structure for a router */
typedef struct {
    char hostname[50];          /* Router hostname */
    RouteEntry routing_table[MAX_ROUTES];
    int route_count;
    Interface interfaces[MAX_INTERFACES];
    int interface_count;
} Router;

/* Convert string IP to IPAddress structure */
void string_to_ip(const char *str, IPAddress *ip) {
    sscanf(str, "%hhu.%hhu.%hhu.%hhu",
           &ip->octets[0], &ip->octets[1], &ip->octets[2], &ip->octets[3]);
}

/* Convert IPAddress to string */
void ip_to_string(const IPAddress *ip, char *str) {
    sprintf(str, "%d.%d.%d.%d",
            ip->octets[0], ip->octets[1], ip->octets[2], ip->octets[3]);
}

/* Compare two IP addresses */
bool ip_equals(const IPAddress *ip1, const IPAddress *ip2) {
    return memcmp(ip1->octets, ip2->octets, 4) == 0;
}

/* Apply subnet mask to IP address */
void apply_mask(const IPAddress *ip, const IPAddress *mask, IPAddress *result) {
    for (int i = 0; i < 4; i++) {
        result->octets[i] = ip->octets[i] & mask->octets[i];
    }
}

/* Count prefix length from subnet mask */
int get_prefix_length(const IPAddress *mask) {
    int prefix = 0;
    for (int i = 0; i < 4; i++) {
        unsigned char byte = mask->octets[i];
        while (byte) {
            prefix += byte & 1;
            byte >>= 1;
        }
    }
    return prefix;
}

/* Check if IP belongs to a network */
bool ip_in_network(const IPAddress *ip, const IPAddress *network, const IPAddress *mask) {
    IPAddress masked_ip;
    apply_mask(ip, mask, &masked_ip);
    return ip_equals(&masked_ip, network);
}

/* Initialize a router */
void init_router(Router *router, const char *hostname) {
    strncpy(router->hostname, hostname, sizeof(router->hostname) - 1);
    router->route_count = 0;
    router->interface_count = 0;
    printf("\n[INIT] Router '%s' initialized.\n", hostname);
}

/* Add an interface to a router */
void add_interface(Router *router, const char *name, const char *ip, const char *mask) {
    if (router->interface_count >= MAX_INTERFACES) {
        printf("[ERROR] Maximum interfaces reached.\n");
        return;
    }

    Interface *iface = &router->interfaces[router->interface_count];
    strncpy(iface->name, name, sizeof(iface->name) - 1);
    string_to_ip(ip, &iface->ip_address);
    string_to_ip(mask, &iface->subnet_mask);
    iface->is_up = true;

    router->interface_count++;
    printf("[CONFIG] Added interface %s with IP %s/%s\n", name, ip, mask);

    /* Automatically add connected route */
    IPAddress network;
    apply_mask(&iface->ip_address, &iface->subnet_mask, &network);
    char net_str[IP_ADDR_LEN];
    ip_to_string(&network, net_str);

    /* Add connected route (metric = 0) */
    RouteEntry *route = &router->routing_table[router->route_count];
    route->network = network;
    route->subnet_mask = iface->subnet_mask;
    string_to_ip("0.0.0.0", &route->next_hop);  /* Directly connected */
    strncpy(route->interface_name, name, sizeof(route->interface_name) - 1);
    route->metric = 0;
    route->is_active = true;
    route->route_type = 'C';

    router->route_count++;
    printf("[ROUTE] Added connected route for network %s\n", net_str);
}

/* Add a static route */
void add_static_route(Router *router, const char *network, const char *mask,
                      const char *next_hop, const char *interface, int metric) {
    if (router->route_count >= MAX_ROUTES) {
        printf("[ERROR] Maximum routes reached.\n");
        return;
    }

    RouteEntry *route = &router->routing_table[router->route_count];
    string_to_ip(network, &route->network);
    string_to_ip(mask, &route->subnet_mask);
    string_to_ip(next_hop, &route->next_hop);
    strncpy(route->interface_name, interface, sizeof(route->interface_name) - 1);
    route->metric = metric;
    route->is_active = true;
    route->route_type = 'S';

    router->route_count++;

    printf("[STATIC] Added route: %s/%s via %s (%s), metric %d\n",
           network, mask, next_hop, interface, metric);
}

/* Delete a route by network */
bool delete_route(Router *router, const char *network, const char *mask) {
    IPAddress net, msk;
    string_to_ip(network, &net);
    string_to_ip(mask, &msk);

    for (int i = 0; i < router->route_count; i++) {
        if (ip_equals(&router->routing_table[i].network, &net) &&
            ip_equals(&router->routing_table[i].subnet_mask, &msk)) {

            /* Shift remaining routes */
            for (int j = i; j < router->route_count - 1; j++) {
                router->routing_table[j] = router->routing_table[j + 1];
            }
            router->route_count--;
            printf("[DELETE] Route %s/%s removed.\n", network, mask);
            return true;
        }
    }
    printf("[ERROR] Route not found.\n");
    return false;
}

void show_routing_table(const Router *router) {
    printf("\n");


    for (int i = 0; i < router->route_count; i++) {
        const RouteEntry *route = &router->routing_table[i];
        if (!route->is_active) continue;

        char net_str[IP_ADDR_LEN], hop_str[IP_ADDR_LEN];
        ip_to_string(&route->network, net_str);
        ip_to_string(&route->next_hop, hop_str);
        int prefix = get_prefix_length(&route->subnet_mask);

        char network_prefix[25];
        sprintf(network_prefix, "%s/%d", net_str, prefix);

               route->route_type, network_prefix,
               (route->route_type == 'C') ? "Directly" : hop_str,
               route->interface_name, route->metric);
    }


}

/* Find the best route for a destination (longest prefix match) */
RouteEntry* route_lookup(Router *router, const IPAddress *destination) {
    RouteEntry *best_route = NULL;
    int best_prefix_length = -1;

    printf("\n[LOOKUP] Searching route for destination...\n");

    for (int i = 0; i < router->route_count; i++) {
        RouteEntry *route = &router->routing_table[i];
        if (!route->is_active) continue;

        /* Check if destination matches this route */
        if (ip_in_network(destination, &route->network, &route->subnet_mask)) {
            int prefix_len = get_prefix_length(&route->subnet_mask);

            char net_str[IP_ADDR_LEN];
            ip_to_string(&route->network, net_str);
            printf("  [MATCH] Route %s/%d matches (prefix length: %d)\n",
                   net_str, prefix_len, prefix_len);

            /* Longest prefix match wins */
            if (prefix_len > best_prefix_length) {
                best_route = route;
                best_prefix_length = prefix_len;
            }
        }
    }

    return best_route;
}

/* Structure to represent a packet */
typedef struct {
    IPAddress source;
    IPAddress destination;
    int ttl;
    char payload[100];
} Packet;

/* Simulate packet forwarding */
void forward_packet(Router *router, Packet *packet) {
    char src_str[IP_ADDR_LEN], dst_str[IP_ADDR_LEN];
    ip_to_string(&packet->source, src_str);
    ip_to_string(&packet->destination, dst_str);


    /* Check TTL */
    if (packet->ttl <= 0) {
        printf("\n[DROPPED] Packet TTL expired. Sending ICMP Time Exceeded.\n");
        return;
    }

    /* Decrement TTL */
    packet->ttl--;

    /* Perform route lookup */
    RouteEntry *route = route_lookup(router, &packet->destination);

    if (route == NULL) {
        printf("\n[DROPPED] No route to destination. Sending ICMP Destination Unreachable.\n");
        return;
    }

    char net_str[IP_ADDR_LEN], hop_str[IP_ADDR_LEN];
    ip_to_string(&route->network, net_str);
    ip_to_string(&route->next_hop, hop_str);
    int prefix = get_prefix_length(&route->subnet_mask);

    printf("\n[FORWARD] Best route found:\n");
    printf("  Network:   %s/%d\n", net_str, prefix);
    printf("  Next Hop:  %s\n", (route->route_type == 'C') ? "Directly Connected" : hop_str);
    printf("  Interface: %s\n", route->interface_name);
    printf("  New TTL:   %d\n", packet->ttl);

    if (route->route_type == 'C') {
        printf("\n[DELIVERED] Packet delivered directly to %s via %s\n",
               dst_str, route->interface_name);
    } else {
        printf("\n[FORWARDED] Packet forwarded to next hop %s via %s\n",
               hop_str, route->interface_name);
    }
}

void simulate_traceroute(Router *routers[], int router_count,
                         const char *source, const char *destination) {


    IPAddress src_ip, dst_ip, current_ip;
    string_to_ip(source, &src_ip);
    string_to_ip(destination, &dst_ip);
    current_ip = src_ip;

    int hop = 1;
    int max_hops = 30;

    while (hop <= max_hops) {
        bool found = false;

        /* Find router that owns current_ip or has route to it */
        for (int r = 0; r < router_count; r++) {
            Router *router = routers[r];

            /* Check if this router has an interface with current_ip */
            for (int i = 0; i < router->interface_count; i++) {
                if (ip_equals(&router->interfaces[i].ip_address, &current_ip) ||
                    ip_in_network(&current_ip,
                                 &router->routing_table[0].network,
                                 &router->routing_table[0].subnet_mask)) {

                    char curr_str[IP_ADDR_LEN];
                    ip_to_string(&current_ip, curr_str);
                    printf("  %2d  %-15s  %s\n", hop, curr_str, router->hostname);

                    /* Check if we reached destination */
                    if (ip_equals(&current_ip, &dst_ip)) {
                        printf("\n[COMPLETE] Traceroute complete. Destination reached.\n");
                        return;
                    }

                    /* Find next hop */
                    RouteEntry *route = route_lookup(router, &dst_ip);
                    if (route && route->route_type == 'S') {
                        current_ip = route->next_hop;
                    } else {
                        current_ip = dst_ip;  /* Direct delivery */
                    }

                    found = true;
                    break;
                }
            }
            if (found) break;
        }

        if (!found) {
            printf("  %2d  * * * Request timed out.\n", hop);
            if (hop > 5) {
                printf("\n[FAILED] Destination unreachable.\n");
                return;
            }
        }

        hop++;
    }

    printf("\n[FAILED] Maximum hops exceeded.\n");
}

void print_menu() {
    printf("\n");


    printf("Enter choice: ");
}

void show_topology() {
    printf("\n");


}

int main() {
    printf("\n");


    /* Create routers */
    Router router1, router2, router3, router4;
    Router *routers[4] = {&router1, &router2, &router3, &router4};
    Router *current_router;

    /* Initialize Router 1 */
    init_router(&router1, "Router1");
    add_interface(&router1, "Gig0/0", "192.168.1.1", "255.255.255.0");
    add_interface(&router1, "Gig0/1", "192.168.2.1", "255.255.255.0");
    add_static_route(&router1, "192.168.3.0", "255.255.255.0", "192.168.2.2", "Gig0/1", 1);
    add_static_route(&router1, "192.168.4.0", "255.255.255.0", "192.168.2.2", "Gig0/1", 2);

    /* Initialize Router 2 */
    init_router(&router2, "Router2");
    add_interface(&router2, "Gig0/0", "192.168.2.2", "255.255.255.0");
    add_interface(&router2, "Gig0/1", "192.168.3.1", "255.255.255.0");
    add_static_route(&router2, "192.168.1.0", "255.255.255.0", "192.168.2.1", "Gig0/0", 1);
    add_static_route(&router2, "192.168.4.0", "255.255.255.0", "192.168.3.2", "Gig0/1", 1);

    /* Initialize Router 3 */
    init_router(&router3, "Router3");
    add_interface(&router3, "Gig0/0", "192.168.3.2", "255.255.255.0");
    add_interface(&router3, "Gig0/1", "192.168.4.1", "255.255.255.0");
    add_static_route(&router3, "192.168.1.0", "255.255.255.0", "192.168.3.1", "Gig0/0", 2);
    add_static_route(&router3, "192.168.2.0", "255.255.255.0", "192.168.3.1", "Gig0/0", 1);

    /* Initialize Router 4 */
    init_router(&router4, "Router4");
    add_interface(&router4, "Gig0/0", "192.168.4.2", "255.255.255.0");
    add_static_route(&router4, "192.168.1.0", "255.255.255.0", "192.168.4.1", "Gig0/0", 3);
    add_static_route(&router4, "192.168.2.0", "255.255.255.0", "192.168.4.1", "Gig0/0", 2);
    add_static_route(&router4, "192.168.3.0", "255.255.255.0", "192.168.4.1", "Gig0/0", 1);
    add_static_route(&router4, "0.0.0.0", "0.0.0.0", "192.168.4.1", "Gig0/0", 255);  /* Default route */

    current_router = &router1;
    int choice;

    show_topology();

    /* Interactive menu */
    while (1) {
        print_menu();
        scanf("%d", &choice);
        getchar();  /* Consume newline */

        switch (choice) {
            case 1:
                show_routing_table(current_router);
                break;

            case 2: {
                char network[IP_ADDR_LEN], mask[IP_ADDR_LEN];
                char next_hop[IP_ADDR_LEN], interface[20];
                int metric;

                printf("Enter destination network: ");
                scanf("%s", network);
                printf("Enter subnet mask: ");
                scanf("%s", mask);
                printf("Enter next hop IP: ");
                scanf("%s", next_hop);
                printf("Enter outgoing interface: ");
                scanf("%s", interface);
                printf("Enter metric: ");
                scanf("%d", &metric);

                add_static_route(current_router, network, mask, next_hop, interface, metric);
                break;
            }

            case 3: {
                char network[IP_ADDR_LEN], mask[IP_ADDR_LEN];
                printf("Enter network to delete: ");
                scanf("%s", network);
                printf("Enter subnet mask: ");
                scanf("%s", mask);
                delete_route(current_router, network, mask);
                break;
            }

            case 4: {
                Packet pkt;
                char src[IP_ADDR_LEN], dst[IP_ADDR_LEN];

                printf("Enter source IP: ");
                scanf("%s", src);
                printf("Enter destination IP: ");
                scanf("%s", dst);
                printf("Enter TTL (default 64): ");
                scanf("%d", &pkt.ttl);

                string_to_ip(src, &pkt.source);
                string_to_ip(dst, &pkt.destination);
                strcpy(pkt.payload, "Test Packet");

                forward_packet(current_router, &pkt);
                break;
            }

            case 5: {
                char src[IP_ADDR_LEN], dst[IP_ADDR_LEN];
                printf("Enter source IP: ");
                scanf("%s", src);
                printf("Enter destination IP: ");
                scanf("%s", dst);
                simulate_traceroute(routers, 4, src, dst);
                break;
            }

            case 6:
                show_topology();
                break;

            case 7: {
                int r;
                printf("Select router (1-4): ");
                scanf("%d", &r);
                if (r >= 1 && r <= 4) {
                    current_router = routers[r - 1];
                    printf("[SWITCH] Now working on %s\n", current_router->hostname);
                } else {
                    printf("[ERROR] Invalid router number.\n");
                }
                break;
            }

            case 8:
                printf("\n[EXIT] Thank you for using Static Routing Simulator!\n\n");
                return 0;

            default:
                printf("[ERROR] Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
