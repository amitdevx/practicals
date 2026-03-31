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
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║          STAR TOPOLOGY VISUALIZATION                             ║\n");
    printf("║          Slip 6 - Option B                                       ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf("║  Star Topology: All devices connect to a central switch/hub     ║\n");
    printf("║  This creates a star-like pattern in the network layout         ║\n");
    printf("╚══════════════════════════════════════════════════════════════════╝\n");
}

/*
 * Function: displayTopologyDiagram
 * Purpose:  Display visual representation of 5-PC Star Topology
 */
void displayTopologyDiagram(void) {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                       STAR TOPOLOGY DIAGRAM                            ║\n");
    printf("║                     Network: 192.168.1.0/24                            ║\n");
    printf("╠════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                        ║\n");
    printf("║                            ┌─────────────┐                             ║\n");
    printf("║                            │    PC1      │                             ║\n");
    printf("║                            │ 192.168.1.1 │                             ║\n");
    printf("║                            │   ┌───┐     │                             ║\n");
    printf("║                            │   │ ▓ │     │                             ║\n");
    printf("║                            └───┴─┬─┴─────┘                             ║\n");
    printf("║                                  │                                     ║\n");
    printf("║                                  │ Fa0/1                               ║\n");
    printf("║                                  │                                     ║\n");
    printf("║   ┌─────────────┐                │                ┌─────────────┐      ║\n");
    printf("║   │    PC5      │                │                │    PC2      │      ║\n");
    printf("║   │ 192.168.1.5 │   Fa0/5        │       Fa0/2    │ 192.168.1.2 │      ║\n");
    printf("║   │   ┌───┐     │────────────────┼────────────────│   ┌───┐     │      ║\n");
    printf("║   │   │ ▓ │     │                │                │   │ ▓ │     │      ║\n");
    printf("║   └───┴───┴─────┘           ┌────┴────┐           └───┴───┴─────┘      ║\n");
    printf("║                             │ SWITCH  │                                ║\n");
    printf("║                             │ ┌─────┐ │                                ║\n");
    printf("║                             │ │ ▓▓▓ │ │                                ║\n");
    printf("║                             │ │▓▓▓▓▓│ │                                ║\n");
    printf("║                             │ └─────┘ │                                ║\n");
    printf("║                             │1 2 3 4 5│                                ║\n");
    printf("║                             └────┬────┘                                ║\n");
    printf("║   ┌─────────────┐                │                ┌─────────────┐      ║\n");
    printf("║   │    PC4      │   Fa0/4        │       Fa0/3    │    PC3      │      ║\n");
    printf("║   │ 192.168.1.4 │────────────────┴────────────────│ 192.168.1.3 │      ║\n");
    printf("║   │   ┌───┐     │                                 │   ┌───┐     │      ║\n");
    printf("║   │   │ ▓ │     │                                 │   │ ▓ │     │      ║\n");
    printf("║   └───┴───┴─────┘                                 └───┴───┴─────┘      ║\n");
    printf("║                                                                        ║\n");
    printf("║   Legend: ┌───┐ = Computer Monitor                                     ║\n");
    printf("║           │ ▓ │ = PC                                                   ║\n");
    printf("║           └───┘                                                        ║\n");
    printf("║           ─────── = Ethernet Cable (Cat5e/Cat6)                        ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════╝\n");
}

/*
 * Function: displayTopologyAlternate
 * Purpose:  Display another visual style of Star Topology
 */
void displayTopologyAlternate(void) {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                    STAR TOPOLOGY - ALTERNATE VIEW                      ║\n");
    printf("╠════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                        ║\n");
    printf("║                              PC1                                       ║\n");
    printf("║                          192.168.1.1                                   ║\n");
    printf("║                              [█]                                       ║\n");
    printf("║                               │                                        ║\n");
    printf("║                               │                                        ║\n");
    printf("║      PC5                      │                      PC2               ║\n");
    printf("║  192.168.1.5                  │                  192.168.1.2           ║\n");
    printf("║      [█]──────────────────────┼──────────────────────[█]               ║\n");
    printf("║                               │                                        ║\n");
    printf("║                          ┌────┴────┐                                   ║\n");
    printf("║                          │ ══════  │                                   ║\n");
    printf("║                          │ SWITCH  │                                   ║\n");
    printf("║                          │ [1][2]  │                                   ║\n");
    printf("║                          │ [3][4]  │                                   ║\n");
    printf("║                          │ [5][ ]  │                                   ║\n");
    printf("║                          └────┬────┘                                   ║\n");
    printf("║                               │                                        ║\n");
    printf("║      PC4                      │                      PC3               ║\n");
    printf("║  192.168.1.4                  │                  192.168.1.3           ║\n");
    printf("║      [█]──────────────────────┴──────────────────────[█]               ║\n");
    printf("║                                                                        ║\n");
    printf("║                                                                        ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════╝\n");
}

/*
 * Function: initializeTopology
 * Purpose:  Set up the Star Topology with 5 PCs
 */
void initializeTopology(StarTopology *topology) {
    // Initialize central switch
    strcpy(topology->centralDevice.name, "Switch-1");
    topology->centralDevice.numPorts = 8;
    topology->centralDevice.usedPorts = 5;
    
    // Set network address
    strcpy(topology->networkAddress, "192.168.1.0/24");
    
    // Initialize 5 PCs
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
    printf("╔══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                          DEVICE INFORMATION                              ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════╣\n");
    printf("║  Network Address: %-20s Subnet: 255.255.255.0         ║\n", 
           topology->networkAddress);
    printf("╠════════════╦════════════════╦════════════════════╦═══════════╦══════════╣\n");
    printf("║   Device   ║   IP Address   ║    Subnet Mask     ║Switch Port║  Status  ║\n");
    printf("╠════════════╬════════════════╬════════════════════╬═══════════╬══════════╣\n");
    
    // Display central device
    printf("║ %-10s ║       --       ║         --         ║    --     ║ %-8s ║\n",
           topology->centralDevice.name, "ACTIVE");
    
    printf("╠════════════╬════════════════╬════════════════════╬═══════════╬══════════╣\n");
    
    // Display each PC
    for (int i = 0; i < topology->numDevices; i++) {
        NetworkDevice *dev = &topology->devices[i];
        printf("║ %-10s ║ %-14s ║ %-18s ║   Fa0/%d   ║ %-8s ║\n",
               dev->name,
               dev->ipAddress,
               dev->subnetMask,
               dev->portNumber,
               dev->isConnected ? "UP" : "DOWN");
    }
    
    printf("╚════════════╩════════════════╩════════════════════╩═══════════╩══════════╝\n");
}

/*
 * Function: displayConnectivityMatrix
 * Purpose:  Show which devices can communicate with each other
 */
void displayConnectivityMatrix(StarTopology *topology) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                     CONNECTIVITY MATRIX                                  ║\n");
    printf("║            (All PCs can communicate via central switch)                  ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════╣\n");
    printf("║         │   PC1   │   PC2   │   PC3   │   PC4   │   PC5   │             ║\n");
    printf("╠═════════╪═════════╪═════════╪═════════╪═════════╪═════════╣             ║\n");
    printf("║   PC1   │    -    │    ✓    │    ✓    │    ✓    │    ✓    │             ║\n");
    printf("║   PC2   │    ✓    │    -    │    ✓    │    ✓    │    ✓    │             ║\n");
    printf("║   PC3   │    ✓    │    ✓    │    -    │    ✓    │    ✓    │             ║\n");
    printf("║   PC4   │    ✓    │    ✓    │    ✓    │    -    │    ✓    │             ║\n");
    printf("║   PC5   │    ✓    │    ✓    │    ✓    │    ✓    │    -    │             ║\n");
    printf("╠═════════╧═════════╧═════════╧═════════╧═════════╧═════════╝             ║\n");
    printf("║                                                                          ║\n");
    printf("║  ✓ = Can communicate (through switch)                                   ║\n");
    printf("║  - = Same device                                                         ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════╝\n");
}

/*
 * Function: displayCharacteristics
 * Purpose:  Show advantages and disadvantages of Star Topology
 */
void displayCharacteristics(void) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                   STAR TOPOLOGY CHARACTERISTICS                          ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                          ║\n");
    printf("║  ┌─────────────────────────────┬──────────────────────────────────────┐ ║\n");
    printf("║  │        ADVANTAGES           │          DISADVANTAGES               │ ║\n");
    printf("║  ├─────────────────────────────┼──────────────────────────────────────┤ ║\n");
    printf("║  │ ✓ Easy to install & manage  │ ✗ Dependent on central device       │ ║\n");
    printf("║  │ ✓ Easy troubleshooting      │ ✗ Central failure = Network down    │ ║\n");
    printf("║  │ ✓ Easy to add new devices   │ ✗ More cable required               │ ║\n");
    printf("║  │ ✓ Single device failure     │ ✗ Higher cost (cables + switch)     │ ║\n");
    printf("║  │   doesn't affect others     │                                      │ ║\n");
    printf("║  │ ✓ Good performance          │ ✗ Limited by switch port count      │ ║\n");
    printf("║  │ ✓ Centralized management    │                                      │ ║\n");
    printf("║  └─────────────────────────────┴──────────────────────────────────────┘ ║\n");
    printf("║                                                                          ║\n");
    printf("║  Best Used For: Small to medium office networks, Home networks           ║\n");
    printf("║  Common Central Devices: Switch (modern), Hub (legacy)                   ║\n");
    printf("║  Cable Type: Cat5e/Cat6 (Twisted Pair)                                   ║\n");
    printf("║                                                                          ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════╝\n");
}

/*
 * Function: displayPacketTracerSteps
 * Purpose:  Show steps to create this topology in Packet Tracer
 */
void displayPacketTracerSteps(void) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║               PACKET TRACER CONFIGURATION STEPS                          ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                          ║\n");
    printf("║  Step 1: ADD DEVICES                                                     ║\n");
    printf("║  ────────────────────                                                    ║\n");
    printf("║  • From Network Devices → Switches → 2960 (drag to workspace)            ║\n");
    printf("║  • From End Devices → PC → Drag 5 PCs to workspace                       ║\n");
    printf("║                                                                          ║\n");
    printf("║  Step 2: CONNECT DEVICES                                                 ║\n");
    printf("║  ─────────────────────                                                   ║\n");
    printf("║  • Select Copper Straight-Through Cable                                  ║\n");
    printf("║  • Connect PC1 FastEthernet0 → Switch FastEthernet0/1                    ║\n");
    printf("║  • Connect PC2 FastEthernet0 → Switch FastEthernet0/2                    ║\n");
    printf("║  • Connect PC3 FastEthernet0 → Switch FastEthernet0/3                    ║\n");
    printf("║  • Connect PC4 FastEthernet0 → Switch FastEthernet0/4                    ║\n");
    printf("║  • Connect PC5 FastEthernet0 → Switch FastEthernet0/5                    ║\n");
    printf("║                                                                          ║\n");
    printf("║  Step 3: CONFIGURE IP ADDRESSES                                          ║\n");
    printf("║  ─────────────────────────────                                           ║\n");
    printf("║  For each PC:                                                            ║\n");
    printf("║  • Click on PC → Desktop tab → IP Configuration                          ║\n");
    printf("║  • Enter IP Address and Subnet Mask:                                     ║\n");
    printf("║                                                                          ║\n");
    printf("║    ┌────────┬────────────────┬─────────────────┬─────────────┐          ║\n");
    printf("║    │ Device │   IP Address   │   Subnet Mask   │   Gateway   │          ║\n");
    printf("║    ├────────┼────────────────┼─────────────────┼─────────────┤          ║\n");
    printf("║    │  PC1   │  192.168.1.1   │  255.255.255.0  │   (blank)   │          ║\n");
    printf("║    │  PC2   │  192.168.1.2   │  255.255.255.0  │   (blank)   │          ║\n");
    printf("║    │  PC3   │  192.168.1.3   │  255.255.255.0  │   (blank)   │          ║\n");
    printf("║    │  PC4   │  192.168.1.4   │  255.255.255.0  │   (blank)   │          ║\n");
    printf("║    │  PC5   │  192.168.1.5   │  255.255.255.0  │   (blank)   │          ║\n");
    printf("║    └────────┴────────────────┴─────────────────┴─────────────┘          ║\n");
    printf("║                                                                          ║\n");
    printf("║  Step 4: VERIFY CONNECTIVITY                                             ║\n");
    printf("║  ─────────────────────────────                                           ║\n");
    printf("║  • Click on PC1 → Desktop → Command Prompt                               ║\n");
    printf("║  • Type: ping 192.168.1.2                                                ║\n");
    printf("║  • Type: ping 192.168.1.3                                                ║\n");
    printf("║  • Verify all pings are successful (Reply from...)                       ║\n");
    printf("║                                                                          ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════╝\n");
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
    
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║  PING SIMULATION: %s → %s                                  ║\n", 
           src->name, dest->name);
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                ║\n");
    printf("║  C:\\> ping %s                                        ║\n", dest->ipAddress);
    printf("║                                                                ║\n");
    printf("║  Pinging %s with 32 bytes of data:                   ║\n", dest->ipAddress);
    printf("║                                                                ║\n");
    
    if (src->isConnected && dest->isConnected) {
        printf("║  Reply from %s: bytes=32 time<1ms TTL=128         ║\n", dest->ipAddress);
        printf("║  Reply from %s: bytes=32 time<1ms TTL=128         ║\n", dest->ipAddress);
        printf("║  Reply from %s: bytes=32 time<1ms TTL=128         ║\n", dest->ipAddress);
        printf("║  Reply from %s: bytes=32 time<1ms TTL=128         ║\n", dest->ipAddress);
        printf("║                                                                ║\n");
        printf("║  Ping statistics for %s:                          ║\n", dest->ipAddress);
        printf("║      Packets: Sent = 4, Received = 4, Lost = 0 (0%% loss)     ║\n");
        printf("║  Approximate round trip times in milli-seconds:               ║\n");
        printf("║      Minimum = 0ms, Maximum = 0ms, Average = 0ms              ║\n");
    } else {
        printf("║  Request timed out.                                            ║\n");
        printf("║  Request timed out.                                            ║\n");
        printf("║  Request timed out.                                            ║\n");
        printf("║  Request timed out.                                            ║\n");
        printf("║                                                                ║\n");
        printf("║  Ping statistics for %s:                          ║\n", dest->ipAddress);
        printf("║      Packets: Sent = 4, Received = 0, Lost = 4 (100%% loss)   ║\n");
    }
    printf("║                                                                ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
}

/*
 * Function: displayDataFlow
 * Purpose:  Show how data flows in Star Topology
 */
void displayDataFlow(void) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                    DATA FLOW IN STAR TOPOLOGY                            ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                          ║\n");
    printf("║  When PC1 sends data to PC3:                                            ║\n");
    printf("║                                                                          ║\n");
    printf("║        PC1                                         PC3                   ║\n");
    printf("║      ┌─────┐                                     ┌─────┐                ║\n");
    printf("║      │ SRC │                                     │ DST │                ║\n");
    printf("║      └──┬──┘                                     └──▲──┘                ║\n");
    printf("║         │                                           │                   ║\n");
    printf("║    (1)  │ Frame: [DST=PC3][SRC=PC1][DATA]          │ (3)               ║\n");
    printf("║         │                                           │                   ║\n");
    printf("║         ▼                                           │                   ║\n");
    printf("║      ┌──────────────────────────────────────────────┴──┐                ║\n");
    printf("║      │                    SWITCH                       │                ║\n");
    printf("║      │  ┌─────────────────────────────────────────┐   │                ║\n");
    printf("║      │  │  MAC Address Table                      │   │                ║\n");
    printf("║      │  │  ┌────────────────┬───────────────────┐ │   │                ║\n");
    printf("║      │  │  │  MAC Address   │      Port         │ │   │                ║\n");
    printf("║      │  │  ├────────────────┼───────────────────┤ │   │                ║\n");
    printf("║      │  │  │  AA:AA:AA:AA   │      Fa0/1 (PC1)  │ │   │                ║\n");
    printf("║      │  │  │  CC:CC:CC:CC   │      Fa0/3 (PC3)  │ │   │                ║\n");
    printf("║      │  │  └────────────────┴───────────────────┘ │   │                ║\n");
    printf("║      │  └─────────────────────────────────────────┘   │                ║\n");
    printf("║      │        (2) Switch forwards to correct port     │                ║\n");
    printf("║      └────────────────────────────────────────────────┘                ║\n");
    printf("║                                                                          ║\n");
    printf("║  Steps:                                                                  ║\n");
    printf("║  (1) PC1 creates frame with destination MAC (PC3)                       ║\n");
    printf("║  (2) Switch receives frame, looks up MAC in table                       ║\n");
    printf("║  (3) Switch forwards frame only to PC3's port (not broadcast)           ║\n");
    printf("║                                                                          ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════╝\n");
}

/*
 * Main function
 */
int main() {
    StarTopology topology;
    int choice;
    int src, dest;
    
    // Initialize the topology
    initializeTopology(&topology);
    
    // Display banner
    displayBanner();
    
    while (1) {
        printf("\n┌────────────────────────────────────────────┐\n");
        printf("│                  MENU                      │\n");
        printf("├────────────────────────────────────────────┤\n");
        printf("│ 1. Display Star Topology Diagram           │\n");
        printf("│ 2. Display Alternate Topology View         │\n");
        printf("│ 3. Display Device Information Table        │\n");
        printf("│ 4. Display Connectivity Matrix             │\n");
        printf("│ 5. Display Topology Characteristics        │\n");
        printf("│ 6. Display Packet Tracer Steps             │\n");
        printf("│ 7. Simulate Ping between PCs               │\n");
        printf("│ 8. Display Data Flow Explanation           │\n");
        printf("│ 9. Display All Information                 │\n");
        printf("│ 0. Exit                                    │\n");
        printf("└────────────────────────────────────────────┘\n");
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

/*
 * SAMPLE OUTPUT:
 * ═══════════════════════════════════════════════════════════════
 *
 * ╔══════════════════════════════════════════════════════════════════╗
 * ║          STAR TOPOLOGY VISUALIZATION                             ║
 * ║          Slip 6 - Option B                                       ║
 * ╠══════════════════════════════════════════════════════════════════╣
 * ║  Star Topology: All devices connect to a central switch/hub     ║
 * ║  This creates a star-like pattern in the network layout         ║
 * ╚══════════════════════════════════════════════════════════════════╝
 *
 * Enter choice: 1
 *
 * ╔════════════════════════════════════════════════════════════════════════╗
 * ║                       STAR TOPOLOGY DIAGRAM                            ║
 * ║                     Network: 192.168.1.0/24                            ║
 * ╠════════════════════════════════════════════════════════════════════════╣
 * ║                            ┌─────────────┐                             ║
 * ║                            │    PC1      │                             ║
 * ║                            │ 192.168.1.1 │                             ║
 * ...
 *
 * ═══════════════════════════════════════════════════════════════
 */
