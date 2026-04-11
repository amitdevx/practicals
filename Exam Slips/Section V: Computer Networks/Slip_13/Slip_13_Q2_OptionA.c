/*
 * Slip 13 - Q2 Option A: Hybrid Topology Display Program
 *
 * Description: This program displays a Hybrid Network Topology
 *              combining Star and Bus topologies.
 *
 * Hybrid Topology: Combines multiple topology types
 * - Bus backbone connecting switches
 * - Star topology at each switch with connected PCs
 *
 * Compile: gcc -o hybrid_topology Slip_13_Q2_OptionA.c
 * Run:     ./hybrid_topology
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEVICES 10
#define MAX_NAME_LEN 30

// Structure to represent a network device
typedef struct {
    char name[MAX_NAME_LEN];
    char ipAddress[20];
    char macAddress[20];
    int isActive;
} Device;

// Structure to represent a Star segment
typedef struct {
    char hubName[MAX_NAME_LEN];
    Device devices[MAX_DEVICES];
    int deviceCount;
} StarSegment;

// Structure for Hybrid Topology
typedef struct {
    char backboneName[MAX_NAME_LEN];
    StarSegment segments[MAX_DEVICES];
    int segmentCount;
} HybridTopology;

// Function prototypes
void initializeTopology(HybridTopology *topology);
void displayHeader(void);
void displayBusBackbone(HybridTopology *topology);
void displayStarSegment(StarSegment *segment, int segmentNum);
void displayFullTopology(HybridTopology *topology);
void displayASCIITopology(HybridTopology *topology);
void displayTopologyStats(HybridTopology *topology);
void printSeparator(char ch, int length);
void printCentered(const char *text, int width);

int main() {
    HybridTopology network;

    initializeTopology(&network);

    displayFullTopology(&network);

    return 0;
}

void initializeTopology(HybridTopology *topology) {
    strcpy(topology->backboneName, "Main Bus Backbone (Cat6)");
    topology->segmentCount = 3;

    // Star Segment 1 - Engineering Department
    strcpy(topology->segments[0].hubName, "Switch-1 (Engineering)");
    topology->segments[0].deviceCount = 3;

    strcpy(topology->segments[0].devices[0].name, "PC-ENG-01");
    strcpy(topology->segments[0].devices[0].ipAddress, "192.168.1.10");
    strcpy(topology->segments[0].devices[0].macAddress, "AA:BB:CC:01:01:01");
    topology->segments[0].devices[0].isActive = 1;

    strcpy(topology->segments[0].devices[1].name, "PC-ENG-02");
    strcpy(topology->segments[0].devices[1].ipAddress, "192.168.1.11");
    strcpy(topology->segments[0].devices[1].macAddress, "AA:BB:CC:01:01:02");
    topology->segments[0].devices[1].isActive = 1;

    strcpy(topology->segments[0].devices[2].name, "PC-ENG-03");
    strcpy(topology->segments[0].devices[2].ipAddress, "192.168.1.12");
    strcpy(topology->segments[0].devices[2].macAddress, "AA:BB:CC:01:01:03");
    topology->segments[0].devices[2].isActive = 0;

    // Star Segment 2 - Sales Department
    strcpy(topology->segments[1].hubName, "Switch-2 (Sales)");
    topology->segments[1].deviceCount = 3;

    strcpy(topology->segments[1].devices[0].name, "PC-SALES-01");
    strcpy(topology->segments[1].devices[0].ipAddress, "192.168.1.20");
    strcpy(topology->segments[1].devices[0].macAddress, "AA:BB:CC:02:01:01");
    topology->segments[1].devices[0].isActive = 1;

    strcpy(topology->segments[1].devices[1].name, "PC-SALES-02");
    strcpy(topology->segments[1].devices[1].ipAddress, "192.168.1.21");
    strcpy(topology->segments[1].devices[1].macAddress, "AA:BB:CC:02:01:02");
    topology->segments[1].devices[1].isActive = 1;

    strcpy(topology->segments[1].devices[2].name, "PC-SALES-03");
    strcpy(topology->segments[1].devices[2].ipAddress, "192.168.1.22");
    strcpy(topology->segments[1].devices[2].macAddress, "AA:BB:CC:02:01:03");
    topology->segments[1].devices[2].isActive = 1;

    // Star Segment 3 - HR Department
    strcpy(topology->segments[2].hubName, "Switch-3 (HR)");
    topology->segments[2].deviceCount = 2;

    strcpy(topology->segments[2].devices[0].name, "PC-HR-01");
    strcpy(topology->segments[2].devices[0].ipAddress, "192.168.1.30");
    strcpy(topology->segments[2].devices[0].macAddress, "AA:BB:CC:03:01:01");
    topology->segments[2].devices[0].isActive = 1;

    strcpy(topology->segments[2].devices[1].name, "PC-HR-02");
    strcpy(topology->segments[2].devices[1].ipAddress, "192.168.1.31");
    strcpy(topology->segments[2].devices[1].macAddress, "AA:BB:CC:03:01:02");
    topology->segments[2].devices[1].isActive = 1;
}

void displayHeader(void) {
    printf("\n");
    printSeparator('=', 70);
    printCentered("HYBRID NETWORK TOPOLOGY DISPLAY", 70);
    printCentered("(Star + Bus Combination)", 70);
    printSeparator('=', 70);
    printf("\n");
}

void printSeparator(char ch, int length) {
    for (int i = 0; i < length; i++) {
        printf("%c", ch);
    }
    printf("\n");
}

void printCentered(const char *text, int width) {
    int len = strlen(text);
    int padding = (width - len) / 2;
    for (int i = 0; i < padding; i++)    printf("%s\n", text);
}

void displayBusBackbone(HybridTopology *topology) {
    printf("\n>>> BUS BACKBONE: %s\n", topology->backboneName);
    printSeparator('-', 50);
    printf("    Connected Segments: %d\n", topology->segmentCount);
    printf("    Backbone Type: Ethernet (IEEE 802.3)\n");
    printf("    Speed: 1 Gbps\n");
    printSeparator('-', 50);
}

void displayStarSegment(StarSegment *segment, int segmentNum) {
    printf("\n*** STAR SEGMENT %d: %s ***\n", segmentNum, segment->hubName);
    printSeparator('-', 50);

    printf("    Central Hub: %s\n", segment->hubName);
    printf("    Connected Devices: %d\n", segment->deviceCount);
    printf("\n    %-15s %-16s %-20s %s\n", "Device", "IP Address", "MAC Address", "Status");
    printSeparator('.', 70);

    for (int i = 0; i < segment->deviceCount; i++) {
        printf("    %-15s %-16s %-20s %s\n",
               segment->devices[i].name,
               segment->devices[i].ipAddress,
               segment->devices[i].macAddress,
               segment->devices[i].isActive ? "[ACTIVE]" : "[INACTIVE]");
    }
    printSeparator('-', 50);
}

void displayASCIITopology(HybridTopology *topology) {
    printf("\n");
    printSeparator('=', 70);
    printCentered("ASCII TOPOLOGY DIAGRAM", 70);
    printSeparator('=', 70);

    printf("\n");
    printf("                        HYBRID TOPOLOGY\n");
    printf("                    (Star + Bus Combination)\n");
    printf("\n");
    printf("    ============ BUS BACKBONE (Main Trunk) ============\n");
    printf("    ||                    ||                    ||\n");
    printf("    ||                    ||                    ||\n");
    printf("    \\/                    \\/                    \\/\n");
    printf("+----------+        +----------+        +----------+\n");
    printf("| Switch-1 |        | Switch-2 |        | Switch-3 |\n");
    printf("|  (HUB)   |        |  (HUB)   |        |  (HUB)   |\n");
    printf("+----------+        +----------+        +----------+\n");
    printf("  /  |  \\             /  |  \\             /  |\n");
    printf(" /   |   \\           /   |   \\           /   |\n");
    printf("[PC] [PC] [PC]      [PC] [PC] [PC]      [PC] [PC]\n");
    printf(" |    |    |         |    |    |         |    |\n");
    printf(".10  .11  .12       .20  .21  .22       .30  .31\n");
    printf("\n");
    printf("    STAR SEGMENT 1   STAR SEGMENT 2   STAR SEGMENT 3\n");
    printf("    (Engineering)      (Sales)           (HR)\n");
    printf("\n");
    printf("    Network: 192.168.1.0/24\n");
    printf("    Subnet Mask: 255.255.255.0\n");
    printf("    Default Gateway: 192.168.1.1\n");
    printf("\n");
}

void displayTopologyStats(HybridTopology *topology) {
    int totalDevices = 0;
    int activeDevices = 0;

    for (int i = 0; i < topology->segmentCount; i++) {
        totalDevices += topology->segments[i].deviceCount;
        for (int j = 0; j < topology->segments[i].deviceCount; j++) {
            if (topology->segments[i].devices[j].isActive) {
                activeDevices++;
            }
        }
    }

    printf("\n");
    printSeparator('=', 70);
    printCentered("TOPOLOGY STATISTICS", 70);
    printSeparator('=', 70);

    printf("\n");
    printf("    +--------------------------------+----------------+\n");
    printf("    | Metric                         | Value          |\n");
    printf("    +--------------------------------+----------------+\n");
    printf("    | Topology Type                  | Hybrid         |\n");
    printf("    | Backbone Type                  | Bus            |\n");
    printf("    | Segment Type                   | Star           |\n");
    printf("    | Total Segments                 | %-14d |\n", topology->segmentCount);
    printf("    | Total End Devices              | %-14d |\n", totalDevices);
    printf("    | Active Devices                 | %-14d |\n", activeDevices);
    printf("    | Inactive Devices               | %-14d |\n", totalDevices - activeDevices);
    printf("    | Network Address                | 192.168.1.0/24 |\n");
    printf("    +--------------------------------+----------------+\n");
    printf("\n");
}

void displayFullTopology(HybridTopology *topology) {
    displayHeader();

    printf("\n>>> TOPOLOGY DESCRIPTION:\n");
    printf("    A Hybrid Topology combines multiple network topologies.\n");
    printf("    This implementation uses:\n");
    printf("    - BUS topology as the backbone connecting switches\n");
    printf("    - STAR topology at each segment with PCs connected to switch\n");
    printf("\n>>> ADVANTAGES:\n");
    printf("    - Flexibility in network design\n");
    printf("    - Easy to add new segments\n");
    printf("    - Fault isolation between segments\n");
    printf("    - Scalable architecture\n");

    displayBusBackbone(topology);

    for (int i = 0; i < topology->segmentCount; i++) {
        displayStarSegment(&topology->segments[i], i + 1);
    }

    displayASCIITopology(topology);

    displayTopologyStats(topology);

    printSeparator('=', 70);
    printCentered("END OF HYBRID TOPOLOGY DISPLAY", 70);
    printSeparator('=', 70);
    printf("\n");
}
