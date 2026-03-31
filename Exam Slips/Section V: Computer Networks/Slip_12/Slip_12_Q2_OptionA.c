/*
 * Slip 12 - Q2 Option A: Star Topology Display Program
 * 
 * Concept: Star topology has a central hub/switch connected to all nodes.
 *          All communication passes through the central device.
 * 
 * Characteristics:
 *   - Central point of connection (hub/switch)
 *   - Easy to add/remove nodes
 *   - Single point of failure (central device)
 *   - Better performance with switches (no collisions)
 * 
 * Compile: gcc -o star_topology Slip_12_Q2_OptionA.c
 * Run:     ./star_topology
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 10
#define MAX_NAME_LEN 30

// Structure to represent a node in star topology
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    char ip_address[16];
    int is_active;
} Node;

// Structure to represent the star topology
typedef struct {
    char hub_name[MAX_NAME_LEN];
    int hub_type; // 0 = Hub, 1 = Switch
    Node nodes[MAX_NODES];
    int node_count;
} StarTopology;

// Function prototypes
void initialize_topology(StarTopology *topology);
void add_node(StarTopology *topology, const char *name, const char *ip);
void display_star_topology(StarTopology *topology);
void display_ascii_star(StarTopology *topology);
void display_connection_table(StarTopology *topology);
void simulate_communication(StarTopology *topology, int src, int dest);
void display_topology_info(void);

int main() {
    StarTopology network;
    int choice;
    char name[MAX_NAME_LEN];
    char ip[16];
    int src, dest;
    
    // Initialize with default configuration
    initialize_topology(&network);
    
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║         STAR TOPOLOGY VISUALIZATION PROGRAM                  ║\n");
    printf("║                   Slip 12 - Option A                         ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    
    while (1) {
        printf("\n┌─────────────────────────────────────┐\n");
        printf("│            MENU OPTIONS             │\n");
        printf("├─────────────────────────────────────┤\n");
        printf("│  1. Display Star Topology (ASCII)   │\n");
        printf("│  2. Display Connection Table        │\n");
        printf("│  3. Add New Node                    │\n");
        printf("│  4. Simulate Communication          │\n");
        printf("│  5. Display Topology Info           │\n");
        printf("│  6. Reset to Default                │\n");
        printf("│  7. Exit                            │\n");
        printf("└─────────────────────────────────────┘\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline
        
        switch (choice) {
            case 1:
                display_ascii_star(&network);
                break;
                
            case 2:
                display_connection_table(&network);
                break;
                
            case 3:
                if (network.node_count >= MAX_NODES) {
                    printf("\n[ERROR] Maximum nodes (%d) reached!\n", MAX_NODES);
                } else {
                    printf("Enter node name: ");
                    fgets(name, MAX_NAME_LEN, stdin);
                    name[strcspn(name, "\n")] = 0;
                    
                    printf("Enter IP address (e.g., 192.168.1.%d): ", 
                           network.node_count + 1);
                    fgets(ip, 16, stdin);
                    ip[strcspn(ip, "\n")] = 0;
                    
                    add_node(&network, name, ip);
                    printf("\n[SUCCESS] Node '%s' added to topology!\n", name);
                }
                break;
                
            case 4:
                printf("Enter source node ID (1-%d): ", network.node_count);
                scanf("%d", &src);
                printf("Enter destination node ID (1-%d): ", network.node_count);
                scanf("%d", &dest);
                simulate_communication(&network, src, dest);
                break;
                
            case 5:
                display_topology_info();
                break;
                
            case 6:
                initialize_topology(&network);
                printf("\n[SUCCESS] Topology reset to default configuration!\n");
                break;
                
            case 7:
                printf("\n╔══════════════════════════════════════╗\n");
                printf("║  Thank you for using Star Topology   ║\n");
                printf("║         Visualization Tool           ║\n");
                printf("╚══════════════════════════════════════╝\n\n");
                exit(0);
                
            default:
                printf("\n[ERROR] Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}

void initialize_topology(StarTopology *topology) {
    strcpy(topology->hub_name, "Central Switch");
    topology->hub_type = 1; // Switch
    topology->node_count = 0;
    
    // Add default 5 nodes
    add_node(topology, "PC-1", "192.168.10.1");
    add_node(topology, "PC-2", "192.168.10.2");
    add_node(topology, "PC-3", "192.168.10.3");
    add_node(topology, "PC-4", "192.168.10.4");
    add_node(topology, "PC-5", "192.168.10.5");
}

void add_node(StarTopology *topology, const char *name, const char *ip) {
    if (topology->node_count >= MAX_NODES) return;
    
    Node *node = &topology->nodes[topology->node_count];
    node->id = topology->node_count + 1;
    strncpy(node->name, name, MAX_NAME_LEN - 1);
    node->name[MAX_NAME_LEN - 1] = '\0';
    strncpy(node->ip_address, ip, 15);
    node->ip_address[15] = '\0';
    node->is_active = 1;
    
    topology->node_count++;
}

void display_ascii_star(StarTopology *topology) {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════════════╗\n");
    printf("║                    STAR TOPOLOGY VISUALIZATION                        ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    
    // Display topology based on node count
    int n = topology->node_count;
    
    if (n >= 5) {
        // Top nodes
        printf("                           [%s]                          \n", 
               topology->nodes[0].name);
        printf("                           %s                        \n",
               topology->nodes[0].ip_address);
        printf("                              │                              \n");
        printf("                              │                              \n");
    }
    
    if (n >= 4) {
        printf("        [%s]                │                [%s]       \n",
               topology->nodes[1].name, topology->nodes[2].name);
        printf("        %s              │              %s     \n",
               topology->nodes[1].ip_address, topology->nodes[2].ip_address);
        printf("             \\                │               /             \n");
        printf("              \\               │              /              \n");
    }
    
    // Central Hub/Switch
    printf("               \\              │             /               \n");
    printf("                \\             │            /                \n");
    printf("                 ╔═══════════════════════╗                  \n");
    printf("                 ║   %s   ║                  \n", topology->hub_name);
    printf("                 ║     [%s]     ║                  \n", 
           topology->hub_type ? "SWITCH" : "HUB   ");
    printf("                 ╚═══════════════════════╝                  \n");
    printf("                /             │            \\                \n");
    printf("               /              │             \\               \n");
    
    if (n >= 2) {
        printf("              /               │              \\              \n");
        printf("             /                │               \\             \n");
        printf("        [%s]                │                [%s]       \n",
               topology->nodes[3].name, topology->nodes[4].name);
        printf("        %s              │              %s     \n",
               topology->nodes[3].ip_address, topology->nodes[4].ip_address);
    }
    
    // Additional nodes if any
    if (n > 5) {
        printf("\n         Additional connected nodes:\n");
        for (int i = 5; i < n; i++) {
            printf("         [%s] - %s\n", 
                   topology->nodes[i].name, topology->nodes[i].ip_address);
        }
    }
    
    printf("\n");
    printf("  ┌─────────────────────────────────────────────────────────────┐\n");
    printf("  │ Legend:                                                     │\n");
    printf("  │   [Node]    = Computer/Device                               │\n");
    printf("  │   [SWITCH]  = Central connecting device                     │\n");
    printf("  │   │ \\ /     = Physical cable connections                    │\n");
    printf("  └─────────────────────────────────────────────────────────────┘\n");
}

void display_connection_table(StarTopology *topology) {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════════════╗\n");
    printf("║                      CONNECTION TABLE                                 ║\n");
    printf("╠═══════╦══════════════╦═══════════════════╦════════════╦═══════════════╣\n");
    printf("║ Port  ║    Node      ║    IP Address     ║   Status   ║  MAC Address  ║\n");
    printf("╠═══════╬══════════════╬═══════════════════╬════════════╬═══════════════╣\n");
    
    for (int i = 0; i < topology->node_count; i++) {
        printf("║ Fa0/%-2d║ %-12s ║ %-17s ║ %-10s ║ AA:BB:CC:00:%02X ║\n",
               i + 1,
               topology->nodes[i].name,
               topology->nodes[i].ip_address,
               topology->nodes[i].is_active ? "ACTIVE" : "INACTIVE",
               i + 1);
    }
    
    printf("╚═══════╩══════════════╩═══════════════════╩════════════╩═══════════════╝\n");
    printf("\n");
    printf("  Central Device: %s (%s)\n", 
           topology->hub_name,
           topology->hub_type ? "Layer 2 Switch" : "Layer 1 Hub");
    printf("  Total Nodes: %d\n", topology->node_count);
    printf("  Subnet: 192.168.10.0/24 (255.255.255.0)\n");
}

void simulate_communication(StarTopology *topology, int src, int dest) {
    if (src < 1 || src > topology->node_count || 
        dest < 1 || dest > topology->node_count) {
        printf("\n[ERROR] Invalid node ID!\n");
        return;
    }
    
    if (src == dest) {
        printf("\n[ERROR] Source and destination cannot be same!\n");
        return;
    }
    
    Node *source = &topology->nodes[src - 1];
    Node *destination = &topology->nodes[dest - 1];
    
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════════════╗\n");
    printf("║              COMMUNICATION SIMULATION (Star Topology)                 ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("  Source:      %s (%s)\n", source->name, source->ip_address);
    printf("  Destination: %s (%s)\n", destination->name, destination->ip_address);
    printf("\n");
    printf("  ┌─────────────────────────────────────────────────────────────────┐\n");
    printf("  │                    DATA FLOW PATH                               │\n");
    printf("  ├─────────────────────────────────────────────────────────────────┤\n");
    printf("  │                                                                 │\n");
    printf("  │   Step 1: [%s] sends frame to central switch            │\n", source->name);
    printf("  │           Frame contains destination MAC address                │\n");
    printf("  │                                                                 │\n");
    printf("  │                      ↓                                          │\n");
    printf("  │                                                                 │\n");
    printf("  │   Step 2: [Switch] receives frame on port Fa0/%d                │\n", src);
    printf("  │           Learns source MAC, checks MAC address table           │\n");
    printf("  │                                                                 │\n");
    printf("  │                      ↓                                          │\n");
    printf("  │                                                                 │\n");
    printf("  │   Step 3: [Switch] forwards frame to port Fa0/%d                │\n", dest);
    printf("  │           (Intelligent forwarding - only to destination)        │\n");
    printf("  │                                                                 │\n");
    printf("  │                      ↓                                          │\n");
    printf("  │                                                                 │\n");
    printf("  │   Step 4: [%s] receives the frame                       │\n", destination->name);
    printf("  │           Communication successful!                             │\n");
    printf("  │                                                                 │\n");
    printf("  └─────────────────────────────────────────────────────────────────┘\n");
    printf("\n");
    printf("  Visual Path:\n");
    printf("  ┌──────────┐      ┌───────────────┐      ┌──────────┐\n");
    printf("  │  %-6s  │ ───► │    SWITCH     │ ───► │  %-6s  │\n", 
           source->name, destination->name);
    printf("  │  %-6s  │      │   Fa0/%d→Fa0/%d │      │  %-6s  │\n",
           source->ip_address, src, dest, destination->ip_address);
    printf("  └──────────┘      └───────────────┘      └──────────┘\n");
    printf("\n");
    printf("  [NOTE] In star topology, ALL traffic passes through central switch.\n");
}

void display_topology_info(void) {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════════════╗\n");
    printf("║                    STAR TOPOLOGY INFORMATION                          ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("  ┌─────────────────────────────────────────────────────────────────┐\n");
    printf("  │ DEFINITION:                                                     │\n");
    printf("  │ Star topology is a network configuration where all nodes are    │\n");
    printf("  │ connected to a central hub or switch. All data passes through   │\n");
    printf("  │ this central point.                                             │\n");
    printf("  └─────────────────────────────────────────────────────────────────┘\n");
    printf("\n");
    printf("  ADVANTAGES:\n");
    printf("  ───────────\n");
    printf("  ✓ Easy to install and manage\n");
    printf("  ✓ Easy to detect and isolate faults\n");
    printf("  ✓ No disruption when adding/removing nodes\n");
    printf("  ✓ Better performance (with switches)\n");
    printf("  ✓ Centralized management\n");
    printf("\n");
    printf("  DISADVANTAGES:\n");
    printf("  ──────────────\n");
    printf("  ✗ Single point of failure (central device)\n");
    printf("  ✗ Requires more cable than bus topology\n");
    printf("  ✗ Hub/switch failure brings down entire network\n");
    printf("  ✗ Cost of central device and cabling\n");
    printf("\n");
    printf("  COMPONENTS:\n");
    printf("  ───────────\n");
    printf("  • Central Device: Hub (Layer 1) or Switch (Layer 2)\n");
    printf("  • End Devices: Computers, printers, servers\n");
    printf("  • Cables: Twisted pair (Cat5e/Cat6)\n");
    printf("  • Connectors: RJ-45\n");
    printf("\n");
    printf("  REAL-WORLD USAGE:\n");
    printf("  ─────────────────\n");
    printf("  • Office LANs\n");
    printf("  • Home networks\n");
    printf("  • School computer labs\n");
    printf("  • Small to medium businesses\n");
    printf("\n");
}
