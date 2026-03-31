/* Q2) Write a C program to represent Mesh Topology.
   Displays adjacency matrix and all connections in a full mesh network. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 20

int adjMatrix[MAX_NODES][MAX_NODES];
char nodeNames[MAX_NODES][20];

void initializeMatrix(int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            adjMatrix[i][j] = 0;
        }
    }
}

void createMeshTopology(int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i != j) {
                adjMatrix[i][j] = 1;
            }
        }
    }
}

void displayAdjacencyMatrix(int n) {
    int i, j;
    
    printf("\n========================================\n");
    printf("       MESH TOPOLOGY ADJACENCY MATRIX\n");
    printf("========================================\n\n");
    
    printf("     ");
    for (i = 0; i < n; i++) {
        printf("%6s", nodeNames[i]);
    }
    printf("\n");
    
    printf("     ");
    for (i = 0; i < n; i++) {
        printf("------");
    }
    printf("\n");
    
    for (i = 0; i < n; i++) {
        printf("%5s|", nodeNames[i]);
        for (j = 0; j < n; j++) {
            printf("%5d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

void displayConnections(int n) {
    int i, j, count = 0;
    int totalConnections = n * (n - 1) / 2;
    
    printf("\n========================================\n");
    printf("         MESH TOPOLOGY CONNECTIONS\n");
    printf("========================================\n\n");
    
    printf("All Direct Connections:\n");
    printf("------------------------\n");
    
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (adjMatrix[i][j] == 1) {
                count++;
                printf("  %d. %s <-----> %s\n", count, nodeNames[i], nodeNames[j]);
            }
        }
    }
    
    printf("\n------------------------\n");
    printf("Total Connections: %d\n", count);
    printf("Formula: n(n-1)/2 = %d(%d-1)/2 = %d\n", n, n, totalConnections);
}

void displayTopologyDiagram(int n) {
    printf("\n========================================\n");
    printf("       MESH TOPOLOGY VISUALIZATION\n");
    printf("========================================\n\n");
    
    if (n == 4) {
        printf("           %s\n", nodeNames[0]);
        printf("          / | \\\n");
        printf("         /  |  \\\n");
        printf("        /   |   \\\n");
        printf("       /    |    \\\n");
        printf("    %s-+----+----+-%s\n", nodeNames[1], nodeNames[3]);
        printf("       \\    |    /\n");
        printf("        \\   |   /\n");
        printf("         \\  |  /\n");
        printf("          \\ | /\n");
        printf("           %s\n", nodeNames[2]);
        printf("\n  (Every node connects to every other node)\n");
    } else if (n == 3) {
        printf("           %s\n", nodeNames[0]);
        printf("          /   \\\n");
        printf("         /     \\\n");
        printf("        /       \\\n");
        printf("    %s---------+%s\n", nodeNames[1], nodeNames[2]);
        printf("\n  (Triangle - 3 connections)\n");
    } else if (n == 5) {
        printf("              %s\n", nodeNames[0]);
        printf("            / | \\\n");
        printf("           /  |  \\\n");
        printf("          /   |   \\\n");
        printf("      %s--+---+---+--%s\n", nodeNames[1], nodeNames[4]);
        printf("        \\  \\ | /  /\n");
        printf("         \\  \\|/  /\n");
        printf("          \\  X  /\n");
        printf("           \\/ \\/\n");
        printf("      %s---------+%s\n", nodeNames[2], nodeNames[3]);
        printf("\n  (Pentagon - 10 connections)\n");
    } else {
        printf("  Full Mesh with %d nodes\n", n);
        printf("  Each node has %d direct connections\n", n - 1);
        printf("  Total connections: %d\n", n * (n - 1) / 2);
    }
}

void displayStatistics(int n) {
    int totalConnections = n * (n - 1) / 2;
    int cablesPerNode = n - 1;
    int totalPorts = n * (n - 1);
    
    printf("\n========================================\n");
    printf("         MESH TOPOLOGY STATISTICS\n");
    printf("========================================\n\n");
    
    printf("  Number of Nodes       : %d\n", n);
    printf("  Connections per Node  : %d\n", cablesPerNode);
    printf("  Total Connections     : %d\n", totalConnections);
    printf("  Total Ports Required  : %d\n", totalPorts);
    printf("\n");
    printf("  Advantages:\n");
    printf("  - High redundancy and fault tolerance\n");
    printf("  - Multiple paths for data transmission\n");
    printf("  - No traffic congestion\n");
    printf("\n");
    printf("  Disadvantages:\n");
    printf("  - Expensive (many cables and ports)\n");
    printf("  - Complex to set up and maintain\n");
    printf("  - Scalability issues as n grows\n");
}

int getDegree(int node, int n) {
    int i, degree = 0;
    for (i = 0; i < n; i++) {
        if (adjMatrix[node][i] == 1) {
            degree++;
        }
    }
    return degree;
}

void displayNodeDetails(int n) {
    int i;
    
    printf("\n========================================\n");
    printf("            NODE DETAILS\n");
    printf("========================================\n\n");
    
    printf("  %-10s  %-10s  %-15s\n", "Node", "Degree", "Connected To");
    printf("  %-10s  %-10s  %-15s\n", "----", "------", "------------");
    
    for (i = 0; i < n; i++) {
        int j, first = 1;
        printf("  %-10s  %-10d  ", nodeNames[i], getDegree(i, n));
        for (j = 0; j < n; j++) {
            if (adjMatrix[i][j] == 1) {
                if (!first) printf(", ");
                printf("%s", nodeNames[j]);
                first = 0;
            }
        }
        printf("\n");
    }
}

int main() {
    int n, i, choice;
    
    printf("========================================\n");
    printf("     MESH TOPOLOGY REPRESENTATION\n");
    printf("========================================\n\n");
    
    printf("Enter number of nodes (2-%d): ", MAX_NODES);
    scanf("%d", &n);
    
    if (n < 2 || n > MAX_NODES) {
        printf("Error: Invalid number of nodes!\n");
        return 1;
    }
    
    printf("\nNode Naming Options:\n");
    printf("1. Default names (PC0, PC1, ...)\n");
    printf("2. Custom names\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    if (choice == 2) {
        printf("\nEnter names for %d nodes:\n", n);
        for (i = 0; i < n; i++) {
            printf("  Node %d name: ", i);
            scanf("%s", nodeNames[i]);
        }
    } else {
        for (i = 0; i < n; i++) {
            sprintf(nodeNames[i], "PC%d", i);
        }
    }
    
    initializeMatrix(n);
    createMeshTopology(n);
    
    displayAdjacencyMatrix(n);
    displayConnections(n);
    displayTopologyDiagram(n);
    displayNodeDetails(n);
    displayStatistics(n);
    
    printf("\n========================================\n");
    printf("       PROGRAM COMPLETED\n");
    printf("========================================\n");
    
    return 0;
}
