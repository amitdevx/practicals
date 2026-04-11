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

void display_header(void) {
    printf("\n");


    printf("\n");
}

void display_mesh_info(MeshTopology *mesh) {


    printf("\n");
}

void display_adjacency_matrix(MeshTopology *mesh) {
    int n = mesh->num_nodes;


    printf("\n");

    /* Print column headers */    for (int i = 0; i < n; i++) {
        printf(" N%-2d", i);
    }
    printf("\n");


    for (int i = 0; i < n; i++) {

    }


    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {
            if (i == j) {
                printf("  - ");  /* Diagonal - no self-loop */
            } else {
                printf("  %d ", mesh->adjacency_matrix[i][j]);
            }
        }

    }

    printf("      └");
    for (int i = 0; i < n; i++) {

    }

}

void display_connections_list(MeshTopology *mesh) {
    int n = mesh->num_nodes;
    int count = 0;


    printf("\n");


    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (mesh->adjacency_matrix[i][j] == 1) {
                count++;

            }
        }
    }


    printf("\n  Total: %d bidirectional connections\n\n", count);
}

void display_visual_mesh(MeshTopology *mesh) {
    int n = mesh->num_nodes;


    printf("\n");

    if (n == 3) {
        printf("                         [Node0]\n");
        printf("                        /       \\\n");
        printf("                       /         \\\n");
        printf("                      /           \\\n");
        printf("                     /             \\\n");

        printf("\n");
        printf("       3 nodes, 3 connections (full mesh)\n");
    }
    else if (n == 4) {


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

        printf("                   |\\      |      /|\n");
        printf("                   | \\     |     / |\n");
        printf("                   |  \\    |    /  |\n");
        printf("                   |   \\   |   /   |\n");
        printf("                   |    \\  |  /    |\n");
        printf("                   |     \\ | /     |\n");

        printf("                        \\  |  /\n");
        printf("                         \\ | /\n");
        printf("                          \\|/\n");
        printf("\n");
        printf("       5 nodes, 10 connections (full mesh)\n");
    }
    else if (n == 6) {

        printf("                   /  |  \\        /  |  \\\n");
        printf("                  /   |   \\      /   |   \\\n");
        printf("                 /    |    \\    /    |    \\\n");
        printf("            [Node5]  |     \\  /     |  [Node2]\n");
        printf("                 \\    |      \\/      |    /\n");
        printf("                  \\   |      /\\      |   /\n");
        printf("                   \\  |     /  \\     |  /\n");
        printf("                    \\ |    /    \\    | /\n");

        printf("\n");
        printf("       6 nodes, 15 connections (full mesh)\n");
    }
    else {
        printf("       Visual representation for %d nodes:\n\n", n);

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

void display_node_table(MeshTopology *mesh) {


    for (int i = 0; i < mesh->num_nodes; i++) {

    }


}

void display_properties(void) {


}

void display_formula_table(void) {


}

void display_menu(void) {


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
