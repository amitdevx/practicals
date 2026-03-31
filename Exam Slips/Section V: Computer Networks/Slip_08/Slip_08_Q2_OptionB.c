/*
 * Slip 08 - Q2 Option B: Dynamic Routing Protocol Simulation (RIP)
 * 
 * Program to simulate RIP (Routing Information Protocol) v2
 * - Distance Vector routing algorithm
 * - Hop count metric (max 15, 16 = unreachable)
 * - Periodic updates every 30 seconds (simulated)
 * - Split Horizon and Poison Reverse
 * 
 * Compile: gcc -o Slip_08_Q2_OptionB Slip_08_Q2_OptionB.c
 * Run: ./Slip_08_Q2_OptionB
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_ROUTERS 6
#define MAX_ROUTES 20
#define MAX_NETWORKS 15
#define MAX_NEIGHBORS 4
#define MAX_NAME_LEN 16
#define MAX_IP_LEN 20
#define INFINITY 16         /* RIP infinity (unreachable) */
#define RIP_UPDATE_TIME 30  /* Seconds between updates */
#define MAX_HOP_COUNT 15

/* ===================== Data Structures ===================== */

typedef struct {
    char network[MAX_IP_LEN];    /* Network address (e.g., "192.168.1.0/24") */
    int metric;                   /* Hop count */
    int next_hop_router;          /* Index of next hop router (-1 = direct) */
    char next_hop_ip[MAX_IP_LEN]; /* Next hop IP */
    int is_direct;                /* 1 = directly connected */
    time_t last_update;           /* Time of last update */
    int changed;                  /* Flag for triggered update */
} RIPRoute;

typedef struct {
    char name[MAX_NAME_LEN];
    char router_id[MAX_IP_LEN];
    RIPRoute routes[MAX_ROUTES];
    int num_routes;
    int neighbors[MAX_NEIGHBORS];     /* Indices of neighbor routers */
    int num_neighbors;
    char interfaces[MAX_NEIGHBORS][MAX_IP_LEN];  /* Interface IPs */
} RIPRouter;

/* Global simulation state */
RIPRouter routers[MAX_ROUTERS];
int num_routers = 0;
int simulation_time = 0;
int update_count = 0;

/* ===================== Network Topology ===================== */

/*
 * Initialize sample network topology:
 * 
 *                    172.16.0.0/24
 *                         |
 *     [R1]----10.0.0.0/30----[R2]----10.0.1.0/30----[R3]
 *      |                      |                        |
 * 192.168.1.0/24        192.168.2.0/24           192.168.3.0/24
 *      |                      |                        |
 *      +------10.0.2.0/30-----+                        |
 *             |                                        |
 *           [R4]----10.0.3.0/30----[R5]----10.0.4.0/30-+
 *            |                      |
 *      192.168.4.0/24         192.168.5.0/24
 */
void initialize_topology(void) {
    int i;
    
    num_routers = 5;
    
    /* Router R1 */
    strcpy(routers[0].name, "R1");
    strcpy(routers[0].router_id, "1.1.1.1");
    routers[0].num_routes = 3;
    routers[0].num_neighbors = 2;
    routers[0].neighbors[0] = 1;  /* R2 */
    routers[0].neighbors[1] = 3;  /* R4 */
    strcpy(routers[0].interfaces[0], "10.0.0.1");
    strcpy(routers[0].interfaces[1], "10.0.2.1");
    
    /* R1's directly connected networks */
    strcpy(routers[0].routes[0].network, "192.168.1.0/24");
    routers[0].routes[0].metric = 0;
    routers[0].routes[0].next_hop_router = -1;
    routers[0].routes[0].is_direct = 1;
    
    strcpy(routers[0].routes[1].network, "10.0.0.0/30");
    routers[0].routes[1].metric = 0;
    routers[0].routes[1].next_hop_router = -1;
    routers[0].routes[1].is_direct = 1;
    
    strcpy(routers[0].routes[2].network, "10.0.2.0/30");
    routers[0].routes[2].metric = 0;
    routers[0].routes[2].next_hop_router = -1;
    routers[0].routes[2].is_direct = 1;
    
    /* Router R2 */
    strcpy(routers[1].name, "R2");
    strcpy(routers[1].router_id, "2.2.2.2");
    routers[1].num_routes = 4;
    routers[1].num_neighbors = 3;
    routers[1].neighbors[0] = 0;  /* R1 */
    routers[1].neighbors[1] = 2;  /* R3 */
    routers[1].neighbors[2] = 3;  /* R4 */
    strcpy(routers[1].interfaces[0], "10.0.0.2");
    strcpy(routers[1].interfaces[1], "10.0.1.1");
    strcpy(routers[1].interfaces[2], "10.0.2.2");
    
    strcpy(routers[1].routes[0].network, "192.168.2.0/24");
    routers[1].routes[0].metric = 0;
    routers[1].routes[0].is_direct = 1;
    
    strcpy(routers[1].routes[1].network, "172.16.0.0/24");
    routers[1].routes[1].metric = 0;
    routers[1].routes[1].is_direct = 1;
    
    strcpy(routers[1].routes[2].network, "10.0.0.0/30");
    routers[1].routes[2].metric = 0;
    routers[1].routes[2].is_direct = 1;
    
    strcpy(routers[1].routes[3].network, "10.0.1.0/30");
    routers[1].routes[3].metric = 0;
    routers[1].routes[3].is_direct = 1;
    
    /* Router R3 */
    strcpy(routers[2].name, "R3");
    strcpy(routers[2].router_id, "3.3.3.3");
    routers[2].num_routes = 3;
    routers[2].num_neighbors = 2;
    routers[2].neighbors[0] = 1;  /* R2 */
    routers[2].neighbors[1] = 4;  /* R5 */
    strcpy(routers[2].interfaces[0], "10.0.1.2");
    strcpy(routers[2].interfaces[1], "10.0.4.1");
    
    strcpy(routers[2].routes[0].network, "192.168.3.0/24");
    routers[2].routes[0].metric = 0;
    routers[2].routes[0].is_direct = 1;
    
    strcpy(routers[2].routes[1].network, "10.0.1.0/30");
    routers[2].routes[1].metric = 0;
    routers[2].routes[1].is_direct = 1;
    
    strcpy(routers[2].routes[2].network, "10.0.4.0/30");
    routers[2].routes[2].metric = 0;
    routers[2].routes[2].is_direct = 1;
    
    /* Router R4 */
    strcpy(routers[3].name, "R4");
    strcpy(routers[3].router_id, "4.4.4.4");
    routers[3].num_routes = 3;
    routers[3].num_neighbors = 2;
    routers[3].neighbors[0] = 0;  /* R1 */
    routers[3].neighbors[1] = 4;  /* R5 */
    strcpy(routers[3].interfaces[0], "10.0.2.2");
    strcpy(routers[3].interfaces[1], "10.0.3.1");
    
    strcpy(routers[3].routes[0].network, "192.168.4.0/24");
    routers[3].routes[0].metric = 0;
    routers[3].routes[0].is_direct = 1;
    
    strcpy(routers[3].routes[1].network, "10.0.2.0/30");
    routers[3].routes[1].metric = 0;
    routers[3].routes[1].is_direct = 1;
    
    strcpy(routers[3].routes[2].network, "10.0.3.0/30");
    routers[3].routes[2].metric = 0;
    routers[3].routes[2].is_direct = 1;
    
    /* Router R5 */
    strcpy(routers[4].name, "R5");
    strcpy(routers[4].router_id, "5.5.5.5");
    routers[4].num_routes = 3;
    routers[4].num_neighbors = 2;
    routers[4].neighbors[0] = 3;  /* R4 */
    routers[4].neighbors[1] = 2;  /* R3 */
    strcpy(routers[4].interfaces[0], "10.0.3.2");
    strcpy(routers[4].interfaces[1], "10.0.4.2");
    
    strcpy(routers[4].routes[0].network, "192.168.5.0/24");
    routers[4].routes[0].metric = 0;
    routers[4].routes[0].is_direct = 1;
    
    strcpy(routers[4].routes[1].network, "10.0.3.0/30");
    routers[4].routes[1].metric = 0;
    routers[4].routes[1].is_direct = 1;
    
    strcpy(routers[4].routes[2].network, "10.0.4.0/30");
    routers[4].routes[2].metric = 0;
    routers[4].routes[2].is_direct = 1;
    
    /* Initialize timestamps */
    for (i = 0; i < num_routers; i++) {
        for (int j = 0; j < routers[i].num_routes; j++) {
            routers[i].routes[j].last_update = time(NULL);
            routers[i].routes[j].changed = 0;
        }
    }
}

/* ===================== RIP Core Functions ===================== */

/*
 * Check if a route to a network already exists in router's table
 */
int find_route(RIPRouter *router, const char *network) {
    for (int i = 0; i < router->num_routes; i++) {
        if (strcmp(router->routes[i].network, network) == 0) {
            return i;
        }
    }
    return -1;
}

/*
 * Check if router is a neighbor (for split horizon)
 */
int is_neighbor_via(int router_idx, int route_idx, int neighbor_idx) {
    return (routers[router_idx].routes[route_idx].next_hop_router == neighbor_idx);
}

/*
 * Process RIP update from a neighbor
 * Implements Bellman-Ford algorithm core:
 *   D(v) = min{ c(u,v) + D(u) } for all neighbors u
 */
int process_rip_update(int dest_router, int src_router, const char *network, int metric) {
    RIPRouter *dest = &routers[dest_router];
    int existing_route = find_route(dest, network);
    int new_metric = metric + 1;  /* Add hop count to neighbor */
    
    /* Cap at infinity */
    if (new_metric > INFINITY) {
        new_metric = INFINITY;
    }
    
    if (existing_route == -1) {
        /* New route - add it */
        if (dest->num_routes < MAX_ROUTES && new_metric < INFINITY) {
            int idx = dest->num_routes++;
            char temp_name[MAX_NAME_LEN];
            strcpy(temp_name, routers[src_router].name);
            strcpy(dest->routes[idx].network, network);
            dest->routes[idx].metric = new_metric;
            dest->routes[idx].next_hop_router = src_router;
            snprintf(dest->routes[idx].next_hop_ip, MAX_IP_LEN, "via %s", temp_name);
            dest->routes[idx].is_direct = 0;
            dest->routes[idx].last_update = time(NULL);
            dest->routes[idx].changed = 1;
            
            printf("  [%s] NEW ROUTE: %s via %s, metric %d\n",
                   dest->name, network, temp_name, new_metric);
            return 1;
        }
    } else {
        /* Existing route - check if better */
        RIPRoute *route = &dest->routes[existing_route];
        
        /* If from same next-hop, always update metric */
        if (route->next_hop_router == src_router) {
            if (route->metric != new_metric) {
                int old_metric = route->metric;
                route->metric = new_metric;
                route->last_update = time(NULL);
                route->changed = 1;
                
                printf("  [%s] UPDATE: %s metric %d -> %d (from %s)\n",
                       dest->name, network, old_metric, new_metric, 
                       routers[src_router].name);
                return 1;
            }
        } else if (new_metric < route->metric) {
            /* Better route found */
            int old_metric = route->metric;
            char temp_name[MAX_NAME_LEN];
            strcpy(temp_name, routers[src_router].name);
            route->metric = new_metric;
            route->next_hop_router = src_router;
            snprintf(route->next_hop_ip, MAX_IP_LEN, "via %s", temp_name);
            route->last_update = time(NULL);
            route->changed = 1;
            
            printf("  [%s] BETTER ROUTE: %s metric %d -> %d (via %s)\n",
                   dest->name, network, old_metric, new_metric, temp_name);
            return 1;
        }
    }
    
    return 0;
}

/*
 * Send RIP update from one router to another
 * Implements Split Horizon: don't advertise route back to where it came from
 */
void send_rip_update(int src_router, int dest_router) {
    RIPRouter *src = &routers[src_router];
    
    printf("  %s -> %s: Sending RIP update\n", 
           src->name, routers[dest_router].name);
    
    for (int i = 0; i < src->num_routes; i++) {
        int metric = src->routes[i].metric;
        
        /* Split Horizon: don't send route back to where we learned it */
        if (src->routes[i].next_hop_router == dest_router) {
            /* Poison Reverse: advertise with infinity instead */
            metric = INFINITY;
            printf("    [Split Horizon/Poison Reverse] %s -> metric %d\n",
                   src->routes[i].network, metric);
        }
        
        process_rip_update(dest_router, src_router, 
                          src->routes[i].network, metric);
    }
}

/*
 * Perform one RIP update cycle for all routers
 */
int perform_rip_update_cycle(void) {
    int changes = 0;
    
    update_count++;
    simulation_time += RIP_UPDATE_TIME;
    
    printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║  RIP UPDATE CYCLE #%d (Time: %d seconds)                        \n",
           update_count, simulation_time);
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    
    /* Each router sends updates to all neighbors */
    for (int r = 0; r < num_routers; r++) {
        for (int n = 0; n < routers[r].num_neighbors; n++) {
            int neighbor = routers[r].neighbors[n];
            send_rip_update(r, neighbor);
        }
    }
    
    /* Check for changes */
    for (int r = 0; r < num_routers; r++) {
        for (int i = 0; i < routers[r].num_routes; i++) {
            if (routers[r].routes[i].changed) {
                changes++;
                routers[r].routes[i].changed = 0;
            }
        }
    }
    
    if (changes == 0) {
        printf("\n  *** CONVERGENCE ACHIEVED - No routing table changes ***\n");
    } else {
        printf("\n  %d routing table changes in this cycle\n", changes);
    }
    
    return changes;
}

/* ===================== Display Functions ===================== */

/*
 * Display network topology diagram
 */
void display_topology(void) {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════════════╗\n");
    printf("║                         NETWORK TOPOLOGY                               ║\n");
    printf("╠═══════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                        ║\n");
    printf("║                        172.16.0.0/24                                   ║\n");
    printf("║                             |                                          ║\n");
    printf("║   [R1]----10.0.0.0/30----[R2]----10.0.1.0/30----[R3]                  ║\n");
    printf("║    |                       |                      |                    ║\n");
    printf("║ 192.168.1.0/24      192.168.2.0/24         192.168.3.0/24             ║\n");
    printf("║    |                       |                      |                    ║\n");
    printf("║    +----10.0.2.0/30--------+                      |                    ║\n");
    printf("║            |                                      |                    ║\n");
    printf("║          [R4]----10.0.3.0/30----[R5]----10.0.4.0/30                   ║\n");
    printf("║            |                      |                                    ║\n");
    printf("║     192.168.4.0/24         192.168.5.0/24                             ║\n");
    printf("║                                                                        ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════╝\n");
}

/*
 * Display routing table for a specific router
 */
void display_routing_table(int router_idx) {
    RIPRouter *r = &routers[router_idx];
    
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║  Routing Table for %s (Router ID: %s)                    \n",
           r->name, r->router_id);
    printf("╠═══════════════════════════════════════════════════════════════╣\n");
    printf("║  Network              Metric    Next Hop         Type        ║\n");
    printf("╠═══════════════════════════════════════════════════════════════╣\n");
    
    for (int i = 0; i < r->num_routes; i++) {
        char next_hop[32];
        char type[16];
        
        if (r->routes[i].is_direct) {
            strcpy(next_hop, "directly connected");
            strcpy(type, "C");
        } else if (r->routes[i].metric >= INFINITY) {
            strcpy(next_hop, "unreachable");
            strcpy(type, "R");
        } else {
            sprintf(next_hop, "via %s", routers[r->routes[i].next_hop_router].name);
            strcpy(type, "R");
        }
        
        printf("║  %-18s  %-8d  %-18s %s          ║\n",
               r->routes[i].network,
               r->routes[i].metric,
               next_hop,
               type);
    }
    
    printf("╠═══════════════════════════════════════════════════════════════╣\n");
    printf("║  C = Connected, R = RIP                                       ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
}

/*
 * Display all routing tables
 */
void display_all_routing_tables(void) {
    for (int i = 0; i < num_routers; i++) {
        display_routing_table(i);
    }
}

/*
 * Display RIP configuration (like Cisco show ip protocols)
 */
void show_ip_protocols(int router_idx) {
    RIPRouter *r = &routers[router_idx];
    
    printf("\n");
    printf("Routing Protocol is \"rip\"\n");
    printf("  Outgoing update filter list for all interfaces is not set\n");
    printf("  Incoming update filter list for all interfaces is not set\n");
    printf("  Sending updates every %d seconds, next due in %d seconds\n",
           RIP_UPDATE_TIME, RIP_UPDATE_TIME - (simulation_time % RIP_UPDATE_TIME));
    printf("  Invalid after 180 seconds, hold down 180, flushed after 240\n");
    printf("  Redistributing: rip\n");
    printf("  Default version control: send version 2, receive version 2\n");
    printf("  Automatic network summarization is not in effect\n");
    printf("  Maximum path: 4\n");
    printf("  Routing for Networks:\n");
    
    for (int i = 0; i < r->num_routes; i++) {
        if (r->routes[i].is_direct) {
            printf("    %s\n", r->routes[i].network);
        }
    }
    
    printf("  Routing Information Sources:\n");
    printf("    Gateway         Distance      Last Update\n");
    
    for (int i = 0; i < r->num_neighbors; i++) {
        printf("    %-15s  120           %d sec\n",
               routers[r->neighbors[i]].router_id,
               simulation_time % RIP_UPDATE_TIME);
    }
    
    printf("  Distance: (default is 120)\n\n");
}

/* ===================== RIP Configuration Commands ===================== */

/*
 * Display RIP configuration commands for a router
 */
void show_rip_config(int router_idx) {
    RIPRouter *r = &routers[router_idx];
    
    printf("\n");
    printf("! RIP Configuration for %s\n", r->name);
    printf("!\n");
    printf("router rip\n");
    printf(" version 2\n");
    printf(" no auto-summary\n");
    
    for (int i = 0; i < r->num_routes; i++) {
        if (r->routes[i].is_direct) {
            /* Extract network portion without CIDR */
            char network[MAX_IP_LEN];
            strcpy(network, r->routes[i].network);
            char *slash = strchr(network, '/');
            if (slash) *slash = '\0';
            
            printf(" network %s\n", network);
        }
    }
    
    printf(" passive-interface default\n");
    
    for (int i = 0; i < r->num_neighbors; i++) {
        printf(" no passive-interface GigabitEthernet0/%d\n", i);
    }
    
    printf("!\n");
}

/* ===================== Simulation Control ===================== */

/*
 * Run RIP simulation until convergence
 */
void run_simulation_to_convergence(void) {
    int max_cycles = 20;
    int cycle = 0;
    
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║           RIP SIMULATION - RUNNING TO CONVERGENCE             ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    
    while (cycle < max_cycles) {
        int changes = perform_rip_update_cycle();
        cycle++;
        
        if (changes == 0) {
            printf("\n");
            printf("╔═══════════════════════════════════════════════════════════════╗\n");
            printf("║  SIMULATION COMPLETE - Converged in %d cycles (%d seconds)    \n",
                   cycle, simulation_time);
            printf("╚═══════════════════════════════════════════════════════════════╝\n");
            break;
        }
        
        usleep(500000);  /* Pause for visibility */
    }
    
    if (cycle >= max_cycles) {
        printf("\n*** WARNING: Maximum cycles reached without convergence ***\n");
    }
}

/*
 * Simulate link failure
 */
void simulate_link_failure(int router1, int router2) {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║  LINK FAILURE: %s <--> %s                                    \n",
           routers[router1].name, routers[router2].name);
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    
    /* Remove neighbor relationship */
    for (int i = 0; i < routers[router1].num_neighbors; i++) {
        if (routers[router1].neighbors[i] == router2) {
            /* Shift remaining neighbors */
            for (int j = i; j < routers[router1].num_neighbors - 1; j++) {
                routers[router1].neighbors[j] = routers[router1].neighbors[j+1];
            }
            routers[router1].num_neighbors--;
            break;
        }
    }
    
    for (int i = 0; i < routers[router2].num_neighbors; i++) {
        if (routers[router2].neighbors[i] == router1) {
            for (int j = i; j < routers[router2].num_neighbors - 1; j++) {
                routers[router2].neighbors[j] = routers[router2].neighbors[j+1];
            }
            routers[router2].num_neighbors--;
            break;
        }
    }
    
    /* Set routes via failed link to infinity */
    for (int i = 0; i < routers[router1].num_routes; i++) {
        if (routers[router1].routes[i].next_hop_router == router2) {
            routers[router1].routes[i].metric = INFINITY;
            routers[router1].routes[i].changed = 1;
            printf("  [%s] Route to %s marked UNREACHABLE\n",
                   routers[router1].name, routers[router1].routes[i].network);
        }
    }
    
    for (int i = 0; i < routers[router2].num_routes; i++) {
        if (routers[router2].routes[i].next_hop_router == router1) {
            routers[router2].routes[i].metric = INFINITY;
            routers[router2].routes[i].changed = 1;
            printf("  [%s] Route to %s marked UNREACHABLE\n",
                   routers[router2].name, routers[router2].routes[i].network);
        }
    }
}

/* ===================== Main Menu ===================== */

void display_menu(void) {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║              RIP ROUTING PROTOCOL SIMULATOR                    ║\n");
    printf("╠═══════════════════════════════════════════════════════════════╣\n");
    printf("║  1. Display Network Topology                                   ║\n");
    printf("║  2. Run Simulation to Convergence                              ║\n");
    printf("║  3. Perform Single RIP Update Cycle                            ║\n");
    printf("║  4. Display All Routing Tables                                 ║\n");
    printf("║  5. Display Routing Table for Specific Router                  ║\n");
    printf("║  6. Show IP Protocols (RIP info)                               ║\n");
    printf("║  7. Show RIP Configuration                                     ║\n");
    printf("║  8. Simulate Link Failure (R1-R2)                              ║\n");
    printf("║  9. Reset Simulation                                           ║\n");
    printf("║  0. Exit                                                       ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    printf("Enter choice: ");
}

/* ===================== Main Function ===================== */

int main(void) {
    int choice;
    int router_choice;
    
    /* Seed random number generator */
    srand(time(NULL));
    
    /* Initialize topology */
    initialize_topology();
    
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════════╗\n");
    printf("║     DYNAMIC ROUTING PROTOCOL SIMULATOR - RIP Version 2            ║\n");
    printf("║     Slip 08 - Q2 Option B                                         ║\n");
    printf("╠═══════════════════════════════════════════════════════════════════╣\n");
    printf("║  Features:                                                         ║\n");
    printf("║  - Distance Vector Algorithm (Bellman-Ford)                        ║\n");
    printf("║  - Hop Count Metric (max 15, 16 = unreachable)                    ║\n");
    printf("║  - Split Horizon with Poison Reverse                              ║\n");
    printf("║  - Periodic Updates (30 second intervals)                         ║\n");
    printf("║  - Convergence Detection                                          ║\n");
    printf("║  - Link Failure Simulation                                        ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════╝\n");
    
    display_topology();
    
    while (1) {
        display_menu();
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');  /* Clear invalid input */
            continue;
        }
        
        switch (choice) {
            case 0:
                printf("\nExiting RIP Simulator.\n");
                return 0;
                
            case 1:
                display_topology();
                break;
                
            case 2:
                run_simulation_to_convergence();
                break;
                
            case 3:
                perform_rip_update_cycle();
                break;
                
            case 4:
                display_all_routing_tables();
                break;
                
            case 5:
                printf("Enter router number (0-%d): ", num_routers - 1);
                scanf("%d", &router_choice);
                if (router_choice >= 0 && router_choice < num_routers) {
                    display_routing_table(router_choice);
                } else {
                    printf("Invalid router number.\n");
                }
                break;
                
            case 6:
                printf("Enter router number (0-%d): ", num_routers - 1);
                scanf("%d", &router_choice);
                if (router_choice >= 0 && router_choice < num_routers) {
                    show_ip_protocols(router_choice);
                }
                break;
                
            case 7:
                printf("Enter router number (0-%d): ", num_routers - 1);
                scanf("%d", &router_choice);
                if (router_choice >= 0 && router_choice < num_routers) {
                    show_rip_config(router_choice);
                }
                break;
                
            case 8:
                simulate_link_failure(0, 1);  /* R1-R2 */
                printf("\nRun simulation again to see reconvergence.\n");
                break;
                
            case 9:
                simulation_time = 0;
                update_count = 0;
                initialize_topology();
                printf("\nSimulation reset to initial state.\n");
                break;
                
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}

/*
 * ALGORITHM EXPLANATION:
 * =====================
 * 
 * RIP (Routing Information Protocol) uses the Distance Vector algorithm
 * based on Bellman-Ford equation:
 * 
 *   D(x,y) = min{ c(x,v) + D(v,y) } for all neighbors v
 * 
 * Where:
 *   D(x,y) = cost of path from x to y
 *   c(x,v) = cost of edge from x to neighbor v
 *   D(v,y) = neighbor v's cost to y
 * 
 * RIP CHARACTERISTICS:
 * -------------------
 * 1. Metric: Hop count (number of routers to traverse)
 * 2. Maximum: 15 hops (16 = unreachable/infinity)
 * 3. Update interval: 30 seconds
 * 4. Administrative Distance: 120
 * 
 * LOOP PREVENTION:
 * ---------------
 * 1. Split Horizon: Don't advertise route back to source
 * 2. Poison Reverse: Advertise route with infinity to source
 * 3. Hold-down timer: Wait before accepting worse route
 * 4. Triggered updates: Send immediate update on change
 * 
 * CONVERGENCE:
 * -----------
 * Network converges when no routing table changes occur
 * after a complete update cycle.
 * 
 * SAMPLE OUTPUT:
 * =============
 * RIP UPDATE CYCLE #3 (Time: 90 seconds)
 *   R1 -> R2: Sending RIP update
 *     [Split Horizon/Poison Reverse] 192.168.2.0/24 -> metric 16
 *   [R2] BETTER ROUTE: 192.168.4.0/24 metric 3 -> 2 (via R1)
 * 
 * CONVERGENCE ACHIEVED - No routing table changes
 */
