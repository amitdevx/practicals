/*
 * Slip 6 - Option B: Star Topology Display Program
 * Network Topology Visualization
 *
 * This program displays a Star Topology with a central switch
 * and 5 PCs with their IP addresses.
 *
 * Compilation: gcc -o star_topology Slip_06_Q2_OptionB.c
 * Execution:   ./star_topology
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DEVICES 10
#define MAX_NAME_LEN 20
#define MAX_IP_LEN 20

/* Structure to represent a network device */
typedef struct {
    char name[MAX_NAME_LEN];
    char ipAddress[MAX_IP_LEN];
    char subnetMask[MAX_IP_LEN];
    int portNumber;          // Port on central switch
    int isConnected;         // Connection status
} NetworkDevice;

/* Structure for the central device (Switch/Hub) */
typedef struct {
    char name[MAX_NAME_LEN];
    int numPorts;
    int usedPorts;
} CentralDevice;

/* Structure for Star Topology Network */
typedef struct {
    CentralDevice centralDevice;
    NetworkDevice devices[MAX_DEVICES];
    int numDevices;
    char networkAddress[MAX_IP_LEN];
} StarTopology;

/*
 * Function: displayBanner
 * Purpose:  Show program title and description
 */
void displayBanner(void) {
    printf("\n");


}

/*
 * Function: displayTopologyDiagram
 * Purpose:  Display visual representation of 5-PC Star Topology
 */
void displayTopologyDiagram(void) {
    printf("\n");


}

/*
 * Function: displayTopologyAlternate
 * Purpose:  Display another visual style of Star Topology
 */
void displayTopologyAlternate(void) {
    printf("\n");


}

/*
 * Function: initializeTopology
 * Purpose:  Set up the Star Topology with 5 PCs
 */
void initializeTopology(StarTopology *topology) {
    strcpy(topology->centralDevice.name, "Switch-1");
    topology->centralDevice.numPorts = 8;
    topology->centralDevice.usedPorts = 5;

    // Set network address
    strcpy(topology->networkAddress, "192.168.1.0/24");

    topology->numDevices = 5;

    for (int i = 0; i < 5; i++) {
        sprintf(topology->devices[i].name, "PC%d", i + 1);
        sprintf(topology->devices[i].ipAddress, "192.168.1.%d", i + 1);
        strcpy(topology->devices[i].subnetMask, "255.255.255.0");
        topology->devices[i].portNumber = i + 1;  // Fa0/1 through Fa0/5
        topology->devices[i].isConnected = 1;     // All connected
    }
}

/*
 * Function: displayDeviceTable
 * Purpose:  Show detailed information about all devices
 */
void displayDeviceTable(StarTopology *topology) {
    printf("\n");


    // Display central device


    for (int i = 0; i < topology->numDevices; i++) {
        printf("Device %d: %s\n", i, topology->devices[i].name);
    }


}

/*
 * Function: displayConnectivityMatrix
 * Purpose:  Show which devices can communicate with each other
 */
void displayConnectivityMatrix(StarTopology *topology) {
    printf("\n");


}

/*
 * Function: displayCharacteristics
 * Purpose:  Show advantages and disadvantages of Star Topology
 */
void displayCharacteristics(void) {
    printf("\n");


}

/*
 * Function: displayPacketTracerSteps
 * Purpose:  Show steps to create this topology in Packet Tracer
 */
void displayPacketTracerSteps(void) {
    printf("\n");


}

/*
 * Function: simulatePing
 * Purpose:  Simulate ping command between two devices
 */
void simulatePing(StarTopology *topology, int srcIdx, int destIdx) {
    if (srcIdx < 0 || srcIdx >= topology->numDevices ||
        destIdx < 0 || destIdx >= topology->numDevices) {
        printf("Invalid device index!\n");
        return;
    }

    if (srcIdx == destIdx) {
        printf("Cannot ping self!\n");
        return;
    }

    NetworkDevice *src = &topology->devices[srcIdx];
    NetworkDevice *dest = &topology->devices[destIdx];


    if (src->isConnected && dest->isConnected) {


    } else {


    }


}

/*
 * Function: displayDataFlow
 * Purpose:  Show how data flows in Star Topology
 */
void displayDataFlow(void) {
    printf("\n");


}

/*
 * Main function
 */
int main() {
    StarTopology topology;
    int choice;
    int src, dest;

    initializeTopology(&topology);

    displayBanner();

    while (1) {


        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayTopologyDiagram();
                break;

            case 2:
                displayTopologyAlternate();
                break;

            case 3:
                displayDeviceTable(&topology);
                break;

            case 4:
                displayConnectivityMatrix(&topology);
                break;

            case 5:
                displayCharacteristics();
                break;

            case 6:
                displayPacketTracerSteps();
                break;

            case 7:
                printf("\nEnter source PC number (1-5): ");
                scanf("%d", &src);
                printf("Enter destination PC number (1-5): ");
                scanf("%d", &dest);
                simulatePing(&topology, src - 1, dest - 1);
                break;

            case 8:
                displayDataFlow();
                break;

            case 9:
                displayTopologyDiagram();
                displayTopologyAlternate();
                displayDeviceTable(&topology);
                displayConnectivityMatrix(&topology);
                displayCharacteristics();
                displayPacketTracerSteps();
                displayDataFlow();
                break;

            case 0:
                printf("\nExiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
