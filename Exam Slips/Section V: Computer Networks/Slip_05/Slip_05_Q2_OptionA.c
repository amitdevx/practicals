/*
 * Slip 5 - Q2 Option A: Ring Topology Display Program
 * Computer Networks
 *
 * Description: Creates and displays a Ring Topology network structure
 *              showing node connections using adjacency matrix
 *
 * Ring Topology Characteristics:
 * - Each node connects to exactly 2 neighbors (left and right)
 * - Data travels in one or both directions around the ring
 * - Forms a closed loop structure
 *
 * Compile: gcc -o ring_topology Slip_05_Q2_OptionA.c
 * Run:     ./ring_topology
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 20

// Adjacency matrix for the ring topology
int adjacencyMatrix[MAX_NODES][MAX_NODES];
int numNodes;

void initializeMatrix() {
    for (int i = 0; i < MAX_NODES; i++) {
        for (int j = 0; j < MAX_NODES; j++) {
            adjacencyMatrix[i][j] = 0;
        }
    }
}

// Create ring topology connections
void createRingTopology() {
    for (int i = 0; i < numNodes; i++) {
        // Connect to next node (clockwise)
        int next = (i + 1) % numNodes;
        adjacencyMatrix[i][next] = 1;
        adjacencyMatrix[next][i] = 1;  // Bidirectional connection
    }
}

void displayAdjacencyMatrix() {


        printf("N%-3d", i);
    }
    printf("\n");

    }
    printf("\n");

    for (int i = 0; i < numNodes; i++) {
        printf("N%-3d| ", i);
        for (int j = 0; j < numNodes; j++) {
            printf("%-4d", adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

void displayConnections() {


    for (int i = 0; i < numNodes; i++) {
        printf("Node %d is connected to: ", i);
        int first = 1;
        for (int j = 0; j < numNodes; j++) {
            if (adjacencyMatrix[i][j] == 1) {
                if (!first) printf(", ");
                printf("Node %d", j);
                first = 0;
            }
        }
        printf("\n");
    }
}

// Visualize ring topology (ASCII art)
void visualizeRing() {


    if (numNodes <= 4) {
        // Small ring visualization
        switch(numNodes) {
            case 2:
                printf("       [Node 0] ←→ [Node 1]\n");
                printf("           ↑_________↑\n");
                break;
            case 3:
                printf("            [Node 0]\n");
                printf("           ↗        ↘\n");
                printf("          ↑          ↓\n");
                printf("      [Node 2] ←→ [Node 1]\n");
                break;
            case 4:
                printf("      [Node 0] ←→ [Node 1]\n");
                printf("          ↑          ↓\n");
                printf("          ↑          ↓\n");
                printf("      [Node 3] ←→ [Node 2]\n");
                break;
        }
    } else {
        // General ring visualization
        printf("                    [Node 0]\n");
        printf("                   ↗        ↘\n");
        printf("           [Node %d]          [Node 1]\n", numNodes - 1);
        printf("              ↑                  ↓\n");
        printf("              .                  .\n");
        printf("              .    RING          .\n");
        printf("              .   NETWORK        .\n");
        printf("              .                  .\n");
        printf("              ↑                  ↓\n");

        int mid = numNodes / 2;
        if (numNodes % 2 == 0) {
            printf("           [Node %d] ←→ [Node %d]\n", mid + 1, mid);
        } else {
            printf("                  [Node %d]\n", mid);
        }
    }

    printf("\n  → Data Flow Direction: Bidirectional (clockwise & counter-clockwise)\n");
}

void displayProperties() {


    int totalEdges = numNodes;  // In a ring, edges = nodes


    printf("\n  Characteristics:\n");
    printf("  • Each node has exactly 2 connections\n");
    printf("  • Data travels in circular path\n");
    printf("  • Token passing used for access control\n");
    printf("  • Single point of failure affects entire ring\n");
    printf("  • Easy to add/remove nodes\n");
}

// Simulate data transmission in ring
void simulateDataTransmission() {
    int source, destination;


    printf("Enter source node (0 to %d): ", numNodes - 1);
    scanf("%d", &source);
    printf("Enter destination node (0 to %d): ", numNodes - 1);
    scanf("%d", &destination);

    if (source < 0 || source >= numNodes || destination < 0 || destination >= numNodes) {
        printf("Invalid node numbers!\n");
        return;
    }

    if (source == destination) {
        printf("\nSource and destination are the same node.\n");
        return;
    }

    // Calculate clockwise and counter-clockwise distances
    int clockwise = (destination - source + numNodes) % numNodes;
    int counterClockwise = (source - destination + numNodes) % numNodes;

    printf("\n  Transmission Path Analysis:\n");


    // Clockwise path
    printf("\n  Clockwise Path (→): ");
    int current = source;
    printf("Node %d", current);
    while (current != destination) {
        current = (current + 1) % numNodes;
        printf(" → Node %d", current);
    }
    printf("\n  Hops: %d\n", clockwise);

    // Counter-clockwise path
    printf("\n  Counter-clockwise Path (←): ");
    current = source;
    printf("Node %d", current);
    while (current != destination) {
        current = (current - 1 + numNodes) % numNodes;
        printf(" → Node %d", current);
    }
    printf("\n  Hops: %d\n", counterClockwise);

    // Optimal path
    printf("\n  Optimal Path: %s (%d hops)\n",
           clockwise <= counterClockwise ? "Clockwise" : "Counter-clockwise",
           clockwise <= counterClockwise ? clockwise : counterClockwise);
}

void displayMenu() {


    printf("Enter your choice: ");
}

int main() {
    int choice;

    printf("\n");


    // Get number of nodes
    do {
        printf("Enter number of nodes in ring (2 to %d): ", MAX_NODES);
        scanf("%d", &numNodes);
        if (numNodes < 2 || numNodes > MAX_NODES) {
            printf("Invalid! Please enter between 2 and %d.\n", MAX_NODES);
        }
    } while (numNodes < 2 || numNodes > MAX_NODES);

    initializeMatrix();
    createRingTopology();

    printf("\n✓ Ring topology created with %d nodes!\n", numNodes);

    // Main menu loop
    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayAdjacencyMatrix();
                break;
            case 2:
                displayConnections();
                break;
            case 3:
                visualizeRing();
                break;
            case 4:
                displayProperties();
                break;
            case 5:
                simulateDataTransmission();
                break;
            case 6:
                do {
                    printf("\nEnter number of nodes (2 to %d): ", MAX_NODES);
                    scanf("%d", &numNodes);
                } while (numNodes < 2 || numNodes > MAX_NODES);
                initializeMatrix();
                createRingTopology();
                printf("✓ New ring created with %d nodes!\n", numNodes);
                break;
            case 7:
                printf("\nExiting Ring Topology Simulation...\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}
