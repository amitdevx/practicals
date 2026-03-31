/*
 * Slip 15 - Q2 Option B: Mesh Topology Display Program
 * 
 * Concepts:
 * - Mesh Topology: Every device connects to every other device
 * - Full Mesh: n(n-1)/2 connections for n nodes
 * - Adjacency Matrix representation
 * - High fault tolerance and redundancy
 * 
 * Compile: gcc -o mesh_topology Slip_15_Q2_OptionB.c
 * Run: ./mesh_topology
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 20
#define CLEAR_SCREEN printf("\033[2J\033[H")

/* Structure to represent a node in mesh topology */
typedef struct {
    int id;
    char name[20];
    char ip_address[16];
} Node;

/* Structure for mesh topology */
typedef struct {
    int num_nodes;
    int adjacency_matrix[MAX_NODES][MAX_NODES];
    Node nodes[MAX_NODES];
    int total_connections;
} MeshTopology;

/* Initialize mesh topology */
void init_mesh(MeshTopology *mesh, int n) {
    mesh->num_nodes = n;
    mesh->total_connections = n * (n - 1) / 2;
    
    /* Initialize all connections to 0 */
    for (int i = 0; i < MAX_NODES; i++) {
        for (int j = 0; j < MAX_NODES; j++) {
            mesh->adjacency_matrix[i][j] = 0;
        }
    }
    
    /* Create full mesh - every node connects to every other node */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                mesh->adjacency_matrix[i][j] = 1;
            }
        }
    }
    
    /* Initialize node information */
    for (int i = 0; i < n; i++) {
        mesh->nodes[i].id = i;
        sprintf(mesh->nodes[i].name, "Node%d", i);
        sprintf(mesh->nodes[i].ip_address, "192.168.1.%d", i + 1);
    }
}

/* Display header banner */
void display_header(void) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                                                              ║\n");
    printf("║               MESH TOPOLOGY VISUALIZATION                    ║\n");
    printf("║                                                              ║\n");
    printf("║     Full Mesh: Every node connects to every other node       ║\n");
    printf("║                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf("\n");
}

/* Display mesh topology information */
void display_mesh_info(MeshTopology *mesh) {
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                    TOPOLOGY INFORMATION                      ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║                                                              ║\n");
    printf("║   Number of Nodes:        %-4d                               ║\n", mesh->num_nodes);
    printf("║   Total Connections:      %-4d  [n(n-1)/2 = %d(%d-1)/2]      ║\n", 
           mesh->total_connections, mesh->num_nodes, mesh->num_nodes);
    printf("║   Topology Type:          Full Mesh                          ║\n");
    printf("║   Fault Tolerance:        High                               ║\n");
    printf("║   Redundancy Level:       Maximum                            ║\n");
    printf("║                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf("\n");
}

/* Display adjacency matrix */
void display_adjacency_matrix(MeshTopology *mesh) {
    int n = mesh->num_nodes;
    
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                    ADJACENCY MATRIX                          ║\n");
    printf("║                                                              ║\n");
    printf("║   1 = Connected, 0 = Not Connected (diagonal = self)         ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    
    /* Print column headers */
    printf("       ");
    for (int i = 0; i < n; i++) {
        printf(" N%-2d", i);
    }
    printf("\n");
    
    /* Print separator */
    printf("      ┌");
    for (int i = 0; i < n; i++) {
        printf("────");
    }
    printf("┐\n");
    
    /* Print matrix rows */
    for (int i = 0; i < n; i++) {
        printf("  N%-2d │", i);
        for (int j = 0; j < n; j++) {
            if (i == j) {
                printf("  - ");  /* Diagonal - no self-loop */
            } else {
                printf("  %d ", mesh->adjacency_matrix[i][j]);
            }
        }
        printf("│\n");
    }
    
    /* Print bottom border */
    printf("      └");
    for (int i = 0; i < n; i++) {
        printf("────");
    }
    printf("┘\n\n");
}

/* Display all connections in list format */
void display_connections_list(MeshTopology *mesh) {
    int n = mesh->num_nodes;
    int count = 0;
    
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                    CONNECTION LIST                           ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    
    printf("  ┌────────────────────────────────────────────────────────────┐\n");
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (mesh->adjacency_matrix[i][j] == 1) {
                count++;
                printf("  │  Connection %2d:  %-8s (%s) <══════> %-8s (%s)  │\n",
                       count,
                       mesh->nodes[i].name, mesh->nodes[i].ip_address,
                       mesh->nodes[j].name, mesh->nodes[j].ip_address);
            }
        }
    }
    
    printf("  └────────────────────────────────────────────────────────────┘\n");
    printf("\n  Total: %d bidirectional connections\n\n", count);
}

/* Display visual representation of mesh topology */
void display_visual_mesh(MeshTopology *mesh) {
    int n = mesh->num_nodes;
    
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                VISUAL REPRESENTATION                         ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    
    if (n == 3) {
        printf("                         [Node0]\n");
        printf("                        /       \\\n");
        printf("                       /         \\\n");
        printf("                      /           \\\n");
        printf("                     /             \\\n");
        printf("                [Node1]─────────[Node2]\n");
        printf("\n");
        printf("       3 nodes, 3 connections (full mesh)\n");
    }
    else if (n == 4) {
        printf("               [Node0]══════════════[Node1]\n");
        printf("                 ║  \\              /  ║\n");
        printf("                 ║    \\          /    ║\n");
        printf("                 ║      \\      /      ║\n");
        printf("                 ║        \\  /        ║\n");
        printf("                 ║         \\/         ║\n");
        printf("                 ║         /\\         ║\n");
        printf("                 ║       /    \\       ║\n");
        printf("                 ║     /        \\     ║\n");
        printf("                 ║   /            \\   ║\n");
        printf("               [Node3]══════════════[Node2]\n");
        printf("\n");
        printf("       4 nodes, 6 connections (full mesh)\n");
        printf("\n");
        printf("       Packet Tracer IPs:\n");
        printf("       Node0: 172.16.1.1/16\n");
        printf("       Node1: 172.16.1.2/16\n");
        printf("       Node2: 172.16.1.3/16\n");
        printf("       Node3: 172.16.1.4/16\n");
    }
    else if (n == 5) {
        printf("                        [Node0]\n");
        printf("                       /   |   \\\n");
        printf("                      /    |    \\\n");
        printf("                     /     |     \\\n");
        printf("                [Node1]────┼────[Node4]\n");
        printf("                   |\\      |      /|\n");
        printf("                   | \\     |     / |\n");
        printf("                   |  \\    |    /  |\n");
        printf("                   |   \\   |   /   |\n");
        printf("                   |    \\  |  /    |\n");
        printf("                   |     \\ | /     |\n");
        printf("                [Node2]────┼────[Node3]\n");
        printf("                        \\  |  /\n");
        printf("                         \\ | /\n");
        printf("                          \\|/\n");
        printf("\n");
        printf("       5 nodes, 10 connections (full mesh)\n");
    }
    else if (n == 6) {
        printf("                    [Node0]════════[Node1]\n");
        printf("                   /  |  \\        /  |  \\\n");
        printf("                  /   |   \\      /   |   \\\n");
        printf("                 /    |    \\    /    |    \\\n");
        printf("            [Node5]  |     \\  /     |  [Node2]\n");
        printf("                 \\    |      \\/      |    /\n");
        printf("                  \\   |      /\\      |   /\n");
        printf("                   \\  |     /  \\     |  /\n");
        printf("                    \\ |    /    \\    | /\n");
        printf("                    [Node4]════════[Node3]\n");
        printf("\n");
        printf("       6 nodes, 15 connections (full mesh)\n");
    }
    else {
        printf("       Visual representation for %d nodes:\n\n", n);
        printf("       [N0]──[N1]──[N2]──...──[N%d]\n", n-1);
        printf("         \\    /\\    /\\        /\n");
        printf("          \\  /  \\  /  \\      /\n");
        printf("           \\/    \\/    \\    /\n");
        printf("           /\\    /\\     \\  /\n");
        printf("          /  \\  /  \\     \\/\n");
        printf("         /    \\/    \\    /\\\n");
        printf("       All nodes interconnected in mesh pattern\n");
        printf("\n");
        printf("       %d nodes, %d connections\n", n, n*(n-1)/2);
    }
    printf("\n");
}

/* Display node table with IP addresses */
void display_node_table(MeshTopology *mesh) {
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                      NODE DETAILS                            ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║   ID   │   Name     │   IP Address    │  Connections        ║\n");
    printf("╠════════╪════════════╪═════════════════╪═════════════════════╣\n");
    
    for (int i = 0; i < mesh->num_nodes; i++) {
        printf("║   %2d   │  %-8s  │  %-14s │  %d (to all others)  ║\n",
               mesh->nodes[i].id,
               mesh->nodes[i].name,
               mesh->nodes[i].ip_address,
               mesh->num_nodes - 1);
    }
    
    printf("╚════════╧════════════╧═════════════════╧═════════════════════╝\n\n");
}

/* Display mesh topology properties */
void display_properties(void) {
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║              MESH TOPOLOGY PROPERTIES                        ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║                                                              ║\n");
    printf("║  ADVANTAGES:                                                 ║\n");
    printf("║  ✓ High fault tolerance - multiple paths available           ║\n");
    printf("║  ✓ No traffic congestion - dedicated links                   ║\n");
    printf("║  ✓ High security - data travels on dedicated links           ║\n");
    printf("║  ✓ Easy fault detection and isolation                        ║\n");
    printf("║  ✓ No single point of failure                                ║\n");
    printf("║                                                              ║\n");
    printf("║  DISADVANTAGES:                                              ║\n");
    printf("║  ✗ High cost - requires n(n-1)/2 cables                      ║\n");
    printf("║  ✗ Complex installation and configuration                    ║\n");
    printf("║  ✗ Each device needs n-1 I/O ports                           ║\n");
    printf("║  ✗ Difficult to manage as network grows                      ║\n");
    printf("║                                                              ║\n");
    printf("║  FORMULAS:                                                   ║\n");
    printf("║  • Number of connections (undirected): n(n-1)/2              ║\n");
    printf("║  • Number of links (directed): n(n-1)                        ║\n");
    printf("║  • Ports per device: n-1                                     ║\n");
    printf("║                                                              ║\n");
    printf("║  USE CASES:                                                  ║\n");
    printf("║  • Military networks                                         ║\n");
    printf("║  • Financial institutions                                    ║\n");
    printf("║  • Critical infrastructure                                   ║\n");
    printf("║  • Backbone networks                                         ║\n");
    printf("║                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n\n");
}

/* Display connection formula table */
void display_formula_table(void) {
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║              MESH CONNECTIONS FORMULA TABLE                  ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║   Nodes (n)  │  Formula n(n-1)/2  │  Total Connections      ║\n");
    printf("╠══════════════╪════════════════════╪═════════════════════════╣\n");
    printf("║      2       │    2(2-1)/2 = 1    │          1              ║\n");
    printf("║      3       │    3(3-1)/2 = 3    │          3              ║\n");
    printf("║      4       │    4(4-1)/2 = 6    │          6              ║\n");
    printf("║      5       │    5(5-1)/2 = 10   │         10              ║\n");
    printf("║      6       │    6(6-1)/2 = 15   │         15              ║\n");
    printf("║      7       │    7(7-1)/2 = 21   │         21              ║\n");
    printf("║      8       │    8(8-1)/2 = 28   │         28              ║\n");
    printf("║      9       │    9(9-1)/2 = 36   │         36              ║\n");
    printf("║     10       │   10(10-1)/2 = 45  │         45              ║\n");
    printf("╚══════════════╧════════════════════╧═════════════════════════╝\n\n");
}

/* Display menu */
void display_menu(void) {
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                         MENU                                 ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║                                                              ║\n");
    printf("║     1. Create New Mesh Topology                              ║\n");
    printf("║     2. Display Adjacency Matrix                              ║\n");
    printf("║     3. Display Connection List                               ║\n");
    printf("║     4. Display Visual Representation                         ║\n");
    printf("║     5. Display Node Details                                  ║\n");
    printf("║     6. Display Mesh Properties                               ║\n");
    printf("║     7. Display Formula Table                                 ║\n");
    printf("║     8. Display All Information                               ║\n");
    printf("║     9. Exit                                                  ║\n");
    printf("║                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf("\n  Enter your choice (1-9): ");
}

/* Main function */
int main(void) {
    MeshTopology mesh;
    int choice, num_nodes;
    int mesh_created = 0;
    char input[10];
    
    /* Initialize default mesh with 4 nodes (as per Packet Tracer question) */
    init_mesh(&mesh, 4);
    mesh_created = 1;
    
    /* Update IPs for Packet Tracer specification */
    sprintf(mesh.nodes[0].ip_address, "172.16.1.1");
    sprintf(mesh.nodes[1].ip_address, "172.16.1.2");
    sprintf(mesh.nodes[2].ip_address, "172.16.1.3");
    sprintf(mesh.nodes[3].ip_address, "172.16.1.4");
    sprintf(mesh.nodes[0].name, "PC0");
    sprintf(mesh.nodes[1].name, "PC1");
    sprintf(mesh.nodes[2].name, "PC2");
    sprintf(mesh.nodes[3].name, "PC3");
    
    while (1) {
        CLEAR_SCREEN;
        display_header();
        
        if (mesh_created) {
            display_mesh_info(&mesh);
        }
        
        display_menu();
        
        fgets(input, sizeof(input), stdin);
        choice = atoi(input);
        
        CLEAR_SCREEN;
        display_header();
        
        switch (choice) {
            case 1:
                printf("  Enter number of nodes (2-%d): ", MAX_NODES);
                fgets(input, sizeof(input), stdin);
                num_nodes = atoi(input);
                
                if (num_nodes >= 2 && num_nodes <= MAX_NODES) {
                    init_mesh(&mesh, num_nodes);
                    mesh_created = 1;
                    printf("\n  ✓ Mesh topology created with %d nodes!\n", num_nodes);
                    printf("    Total connections: %d\n", mesh.total_connections);
                } else {
                    printf("\n  ✗ Invalid number of nodes! Must be between 2 and %d.\n", MAX_NODES);
                }
                break;
                
            case 2:
                if (mesh_created) {
                    display_adjacency_matrix(&mesh);
                } else {
                    printf("  Please create a mesh topology first!\n");
                }
                break;
                
            case 3:
                if (mesh_created) {
                    display_connections_list(&mesh);
                } else {
                    printf("  Please create a mesh topology first!\n");
                }
                break;
                
            case 4:
                if (mesh_created) {
                    display_visual_mesh(&mesh);
                } else {
                    printf("  Please create a mesh topology first!\n");
                }
                break;
                
            case 5:
                if (mesh_created) {
                    display_node_table(&mesh);
                } else {
                    printf("  Please create a mesh topology first!\n");
                }
                break;
                
            case 6:
                display_properties();
                break;
                
            case 7:
                display_formula_table();
                break;
                
            case 8:
                if (mesh_created) {
                    display_mesh_info(&mesh);
                    display_adjacency_matrix(&mesh);
                    display_connections_list(&mesh);
                    display_visual_mesh(&mesh);
                    display_node_table(&mesh);
                    display_properties();
                    display_formula_table();
                } else {
                    printf("  Please create a mesh topology first!\n");
                }
                break;
                
            case 9:
                CLEAR_SCREEN;
                printf("\n  Thank you for using Mesh Topology Visualization!\n\n");
                return 0;
                
            default:
                printf("  Invalid choice! Please enter 1-9.\n");
        }
        
        printf("\n  Press Enter to continue...");
        getchar();
    }
    
    return 0;
}

/*
 * Sample Output:
 * 
 * ╔══════════════════════════════════════════════════════════════╗
 * ║                                                              ║
 * ║               MESH TOPOLOGY VISUALIZATION                    ║
 * ║                                                              ║
 * ╚══════════════════════════════════════════════════════════════╝
 * 
 * ╔══════════════════════════════════════════════════════════════╗
 * ║                    TOPOLOGY INFORMATION                      ║
 * ╠══════════════════════════════════════════════════════════════╣
 * ║   Number of Nodes:        4                                  ║
 * ║   Total Connections:      6   [n(n-1)/2 = 4(4-1)/2]         ║
 * ║   Topology Type:          Full Mesh                          ║
 * ╚══════════════════════════════════════════════════════════════╝
 * 
 * ADJACENCY MATRIX:
 *        N0  N1  N2  N3
 *       ┌────────────────┐
 *   N0  │  -   1   1   1 │
 *   N1  │  1   -   1   1 │
 *   N2  │  1   1   -   1 │
 *   N3  │  1   1   1   - │
 *       └────────────────┘
 * 
 * VISUAL (4 nodes):
 *            [PC0]══════════════[PC1]
 *              ║  \            /  ║
 *              ║    \        /    ║
 *              ║      \    /      ║
 *              ║        \/        ║
 *              ║        /\        ║
 *              ║      /    \      ║
 *              ║    /        \    ║
 *            [PC3]══════════════[PC2]
 * 
 * CONNECTION LIST:
 *   Connection 1: PC0 <══════> PC1
 *   Connection 2: PC0 <══════> PC2
 *   Connection 3: PC0 <══════> PC3
 *   Connection 4: PC1 <══════> PC2
 *   Connection 5: PC1 <══════> PC3
 *   Connection 6: PC2 <══════> PC3
 */
