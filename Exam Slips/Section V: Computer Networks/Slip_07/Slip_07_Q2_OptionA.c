/*
 * Slip 07 - Q2 Option A: Mesh Topology Display Program
 * 
 * Program displays a Mesh Topology with:
 * - Visual representation of connections
 * - Adjacency matrix
 * - Connection list
 * - Statistics (total connections)
 * 
 * Compile: gcc Slip_07_Q2_OptionA.c -o mesh_topology
 * Run: ./mesh_topology
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 10

// Function to display the header
void displayHeader() {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════╗\n");
    printf("║           MESH TOPOLOGY DISPLAY PROGRAM                   ║\n");
    printf("║    Every node connects to every other node                ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n\n");
}

// Function to calculate total connections in mesh topology
int calculateConnections(int n) {
    return (n * (n - 1)) / 2;
}

// Function to display visual mesh topology
void displayVisualMesh(int n) {
    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│               MESH TOPOLOGY VISUALIZATION                   │\n");
    printf("└─────────────────────────────────────────────────────────────┘\n\n");
    
    if (n == 3) {
        printf("                    [A]\n");
        printf("                   /   \\\n");
        printf("                  /     \\\n");
        printf("                 /       \\\n");
        printf("               [B]───────[C]\n");
        printf("\n");
    } else if (n == 4) {
        printf("             [A]─────────────[B]\n");
        printf("              |\\             /|\n");
        printf("              | \\           / |\n");
        printf("              |  \\         /  |\n");
        printf("              |   \\       /   |\n");
        printf("              |    \\     /    |\n");
        printf("              |     \\   /     |\n");
        printf("              |      \\ /      |\n");
        printf("              |       X       |\n");
        printf("              |      / \\      |\n");
        printf("              |     /   \\     |\n");
        printf("              |    /     \\    |\n");
        printf("              |   /       \\   |\n");
        printf("              |  /         \\  |\n");
        printf("              | /           \\ |\n");
        printf("              |/             \\|\n");
        printf("             [D]─────────────[C]\n");
        printf("\n");
    } else if (n == 5) {
        printf("                    [A]\n");
        printf("                   /|\\ \\\n");
        printf("                  / | \\ \\\n");
        printf("                 /  |  \\ \\\n");
        printf("               [B]──┼───[E]\n");
        printf("                |\\  |  /|\n");
        printf("                | \\ | / |\n");
        printf("                |  \\|/  |\n");
        printf("               [C]─────[D]\n");
        printf("\n");
    } else if (n == 6) {
        printf("                [A]───────[B]\n");
        printf("               /|\\       /|\\\n");
        printf("              / | \\     / | \\\n");
        printf("             /  |  \\   /  |  \\\n");
        printf("           [F]──┼───\\─/───┼──[C]\n");
        printf("             \\  |    X    |  /\n");
        printf("              \\ |   / \\   | /\n");
        printf("               \\|  /   \\  |/\n");
        printf("                [E]─────[D]\n");
        printf("\n");
    } else {
        // Generic representation for other sizes
        printf("           Full Mesh with %d nodes\n", n);
        printf("           Nodes: ");
        for (int i = 0; i < n; i++) {
            printf("%c ", 'A' + i);
        }
        printf("\n\n");
        printf("           Each node connects to all others\n");
        printf("           (Visual diagram available for 3-6 nodes)\n\n");
    }
}

// Function to display adjacency matrix
void displayAdjacencyMatrix(int n) {
    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│                   ADJACENCY MATRIX                          │\n");
    printf("│         (1 = Connected, 0 = Not Connected)                  │\n");
    printf("└─────────────────────────────────────────────────────────────┘\n\n");
    
    // Print header row
    printf("      ");
    for (int i = 0; i < n; i++) {
        printf("  %c ", 'A' + i);
    }
    printf("\n");
    
    // Print separator
    printf("      ");
    for (int i = 0; i < n; i++) {
        printf("────");
    }
    printf("\n");
    
    // Print matrix
    for (int i = 0; i < n; i++) {
        printf("  %c │ ", 'A' + i);
        for (int j = 0; j < n; j++) {
            if (i == j) {
                printf(" 0  ");  // No self-loop
            } else {
                printf(" 1  ");  // Connected to all others
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Function to display all connections
void displayConnections(int n) {
    int connectionNum = 1;
    
    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│                   CONNECTION LIST                           │\n");
    printf("│              (All node-to-node links)                       │\n");
    printf("└─────────────────────────────────────────────────────────────┘\n\n");
    
    printf("  ┌────────┬──────────────────────────────────┐\n");
    printf("  │  No.   │         Connection               │\n");
    printf("  ├────────┼──────────────────────────────────┤\n");
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            printf("  │   %2d   │    Node %c  <──────>  Node %c    │\n", 
                   connectionNum++, 'A' + i, 'A' + j);
        }
    }
    
    printf("  └────────┴──────────────────────────────────┘\n\n");
}

// Function to display statistics
void displayStatistics(int n) {
    int connections = calculateConnections(n);
    
    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│                 TOPOLOGY STATISTICS                         │\n");
    printf("└─────────────────────────────────────────────────────────────┘\n\n");
    
    printf("  ╔════════════════════════════════════════════════════════╗\n");
    printf("  ║  Parameter                        Value                ║\n");
    printf("  ╠════════════════════════════════════════════════════════╣\n");
    printf("  ║  Number of Nodes                  %-5d                ║\n", n);
    printf("  ║  Total Connections                %-5d                ║\n", connections);
    printf("  ║  Connections per Node             %-5d                ║\n", n - 1);
    printf("  ║  Formula: n(n-1)/2 = %d(%d-1)/2  = %-5d                ║\n", n, n, connections);
    printf("  ╠════════════════════════════════════════════════════════╣\n");
    printf("  ║  Topology Type: FULL MESH                              ║\n");
    printf("  ║  Redundancy: MAXIMUM (Multiple paths available)        ║\n");
    printf("  ║  Fault Tolerance: EXCELLENT                            ║\n");
    printf("  ╚════════════════════════════════════════════════════════╝\n\n");
}

// Function to display mesh topology advantages/disadvantages
void displayMeshInfo() {
    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│                MESH TOPOLOGY INFORMATION                    │\n");
    printf("└─────────────────────────────────────────────────────────────┘\n\n");
    
    printf("  ADVANTAGES:\n");
    printf("  ✓ High fault tolerance - if one link fails, others available\n");
    printf("  ✓ No traffic congestion - dedicated links\n");
    printf("  ✓ Easy troubleshooting - isolation of faults\n");
    printf("  ✓ Secure - data travels on dedicated links\n");
    printf("  ✓ No single point of failure\n\n");
    
    printf("  DISADVANTAGES:\n");
    printf("  ✗ Expensive - requires many cables and ports\n");
    printf("  ✗ Complex installation and configuration\n");
    printf("  ✗ Cabling becomes impractical for large networks\n");
    printf("  ✗ High maintenance overhead\n\n");
    
    printf("  COMMON USES:\n");
    printf("  → Backbone networks\n");
    printf("  → Data centers\n");
    printf("  → Critical infrastructure\n");
    printf("  → Military/aerospace systems\n\n");
}

// Function to display IP configuration example
void displayIPConfig(int n) {
    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│              SAMPLE IP CONFIGURATION                        │\n");
    printf("│            (Subnet: 192.168.1.0/24)                        │\n");
    printf("└─────────────────────────────────────────────────────────────┘\n\n");
    
    printf("  ┌──────────┬────────────────┬─────────────────┐\n");
    printf("  │   Node   │   IP Address   │   Subnet Mask   │\n");
    printf("  ├──────────┼────────────────┼─────────────────┤\n");
    
    for (int i = 0; i < n && i < 10; i++) {
        printf("  │    %c     │  192.168.1.%-3d │  255.255.255.0  │\n", 
               'A' + i, i + 1);
    }
    
    printf("  └──────────┴────────────────┴─────────────────┘\n\n");
}

// Main function
int main() {
    int n;
    char choice;
    
    do {
        // Clear screen (works on most terminals)
        printf("\033[2J\033[H");
        
        displayHeader();
        
        // Get number of nodes
        printf("  Enter number of nodes (2-10): ");
        scanf("%d", &n);
        
        // Validate input
        if (n < 2 || n > MAX_NODES) {
            printf("\n  ⚠ Error: Please enter a number between 2 and 10.\n");
            printf("\n  Press Enter to continue...");
            getchar();  // Clear buffer
            getchar();  // Wait for Enter
            continue;
        }
        
        printf("\n");
        
        // Display all information
        displayVisualMesh(n);
        displayAdjacencyMatrix(n);
        displayConnections(n);
        displayStatistics(n);
        displayIPConfig(n);
        displayMeshInfo();
        
        // Ask to continue
        printf("══════════════════════════════════════════════════════════════\n");
        printf("  Do you want to create another topology? (y/n): ");
        scanf(" %c", &choice);
        
    } while (choice == 'y' || choice == 'Y');
    
    printf("\n  Thank you for using Mesh Topology Display Program!\n\n");
    
    return 0;
}

/*
 * SAMPLE OUTPUT:
 * 
 * ╔═══════════════════════════════════════════════════════════╗
 * ║           MESH TOPOLOGY DISPLAY PROGRAM                   ║
 * ║    Every node connects to every other node                ║
 * ╚═══════════════════════════════════════════════════════════╝
 * 
 *   Enter number of nodes (2-10): 4
 * 
 *              [A]─────────────[B]
 *               |\             /|
 *               | \           / |
 *               |  \         /  |
 *               |   \       /   |
 *               |    \     /    |
 *               |     \   /     |
 *               |      \ /      |
 *               |       X       |
 *               |      / \      |
 *               |     /   \     |
 *               |    /     \    |
 *               |   /       \   |
 *               |  /         \  |
 *               | /           \ |
 *               |/             \|
 *              [D]─────────────[C]
 * 
 * ADJACENCY MATRIX:
 *         A   B   C   D
 *       ────────────────
 *   A │  0   1   1   1
 *   B │  1   0   1   1
 *   C │  1   1   0   1
 *   D │  1   1   1   0
 * 
 * CONNECTION LIST:
 *   1: Node A <──────> Node B
 *   2: Node A <──────> Node C
 *   3: Node A <──────> Node D
 *   4: Node B <──────> Node C
 *   5: Node B <──────> Node D
 *   6: Node C <──────> Node D
 * 
 * STATISTICS:
 *   Number of Nodes:       4
 *   Total Connections:     6
 *   Formula: 4(4-1)/2 = 6
 */
