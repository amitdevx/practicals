/*
 * Slip 3 - Q2 Option A: Bus Topology Display Program
 * 
 * Description: This program creates a visual representation of Bus Topology
 *              where all devices are connected to a single backbone cable.
 * 
 * Bus Topology Characteristics:
 * - All devices share a single communication line (bus/backbone)
 * - Data travels in both directions
 * - Terminators at both ends prevent signal reflection
 * - Uses CSMA/CD for collision handling
 * 
 * Compile: gcc Slip_03_Q2_OptionA.c -o bus_topology
 * Run: ./bus_topology
 */

#include <stdio.h>
#include <string.h>

#define MAX_DEVICES 10
#define NAME_LENGTH 15

// Function prototypes
void displayBusTopology(char devices[][NAME_LENGTH], int count);
void printHorizontalLine(int length, char ch);
void centerText(char *text, int width);

int main() {
    char devices[MAX_DEVICES][NAME_LENGTH];
    int n, i;
    
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║           BUS TOPOLOGY DISPLAY PROGRAM                   ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    // Get number of devices
    printf("Enter the number of devices (2-%d): ", MAX_DEVICES);
    scanf("%d", &n);
    
    // Validate input
    if (n < 2 || n > MAX_DEVICES) {
        printf("Error: Number of devices must be between 2 and %d\n", MAX_DEVICES);
        return 1;
    }
    
    // Get device names
    printf("\nEnter device names:\n");
    for (i = 0; i < n; i++) {
        printf("Device %d: ", i + 1);
        scanf("%s", devices[i]);
        
        // Truncate if name is too long
        if (strlen(devices[i]) > NAME_LENGTH - 1) {
            devices[i][NAME_LENGTH - 1] = '\0';
        }
    }
    
    // Display the bus topology
    displayBusTopology(devices, n);
    
    // Display topology information
    printf("\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║                 BUS TOPOLOGY INFORMATION                 ║\n");
    printf("╠══════════════════════════════════════════════════════════╣\n");
    printf("║  Total Devices Connected: %-3d                           ║\n", n);
    printf("║  Backbone Cable: Single Shared Medium                    ║\n");
    printf("║  Terminators: 2 (at both ends)                          ║\n");
    printf("║  Data Flow: Bidirectional                               ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    
    // Display advantages and disadvantages
    printf("\n┌─────────────────────────────────────────────────────────┐\n");
    printf("│ ADVANTAGES:                                             │\n");
    printf("│  • Easy to install and extend                          │\n");
    printf("│  • Less cabling required                               │\n");
    printf("│  • Cost-effective for small networks                   │\n");
    printf("├─────────────────────────────────────────────────────────┤\n");
    printf("│ DISADVANTAGES:                                          │\n");
    printf("│  • Single point of failure (backbone)                  │\n");
    printf("│  • Performance degrades with more devices              │\n");
    printf("│  • Difficult to troubleshoot                           │\n");
    printf("│  • Limited cable length and devices                    │\n");
    printf("└─────────────────────────────────────────────────────────┘\n");
    
    return 0;
}

/*
 * Function: displayBusTopology
 * Purpose: Displays visual representation of bus topology
 * Parameters:
 *   - devices: Array of device names
 *   - count: Number of devices
 */
void displayBusTopology(char devices[][NAME_LENGTH], int count) {
    int i, j;
    int spacing = 12;  // Space between devices
    int totalWidth = (count * spacing) + 20;
    
    printf("\n");
    printf("═══════════════════════════════════════════════════════════\n");
    printf("                   BUS TOPOLOGY DIAGRAM                     \n");
    printf("═══════════════════════════════════════════════════════════\n\n");
    
    // Display device labels (top)
    printf("      ");
    for (i = 0; i < count; i++) {
        printf("   [%s]   ", devices[i]);
    }
    printf("\n");
    
    // Display vertical connectors (device to bus)
    printf("      ");
    for (i = 0; i < count; i++) {
        printf("      │      ");
    }
    printf("\n");
    
    // Display T-connectors
    printf("      ");
    for (i = 0; i < count; i++) {
        printf("      ┬      ");
    }
    printf("\n");
    
    // Display the main bus (backbone cable)
    printf(" [T]══");
    for (i = 0; i < count; i++) {
        printf("══════╪══════");
    }
    printf("══[T]\n");
    
    // Display terminator labels
    printf(" TERM ");
    for (i = 0; i < count; i++) {
        printf("             ");
    }
    printf(" TERM\n");
    
    // Alternative detailed view
    printf("\n");
    printf("─────────────────────────────────────────────────────────────\n");
    printf("                  DETAILED CONNECTION VIEW                    \n");
    printf("─────────────────────────────────────────────────────────────\n\n");
    
    printf("    ┌────────────────────────────────────────────────────────┐\n");
    printf("    │                    BACKBONE CABLE                      │\n");
    printf("    │ ═══════════════════════════════════════════════════════│\n");
    printf("    │           │        │        │        │                 │\n");
    
    // Show devices connected
    printf("    │ Devices: ");
    for (i = 0; i < count; i++) {
        if (i > 0) printf(", ");
        printf("%s", devices[i]);
    }
    printf("\n");
    
    printf("    │                                                        │\n");
    printf("    │ [TERMINATOR]                            [TERMINATOR]   │\n");
    printf("    └────────────────────────────────────────────────────────┘\n");
    
    // Display data flow visualization
    printf("\n");
    printf("─────────────────────────────────────────────────────────────\n");
    printf("                    DATA FLOW EXAMPLE                         \n");
    printf("─────────────────────────────────────────────────────────────\n\n");
    
    printf("    When %s sends data to %s:\n\n", devices[0], devices[count-1]);
    printf("    %s ──► ════════════════════════════════ ──► %s\n", 
           devices[0], devices[count-1]);
    printf("              Data travels along the bus\n");
    printf("              All devices receive the data\n");
    printf("              Only %s processes it (matching MAC)\n", devices[count-1]);
    
    printf("\n");
}

/*
 * Function: printHorizontalLine
 * Purpose: Prints a horizontal line of specified length
 */
void printHorizontalLine(int length, char ch) {
    int i;
    for (i = 0; i < length; i++) {
        printf("%c", ch);
    }
    printf("\n");
}

/*
 * Sample Output:
 * 
 * ╔══════════════════════════════════════════════════════════╗
 * ║           BUS TOPOLOGY DISPLAY PROGRAM                   ║
 * ╚══════════════════════════════════════════════════════════╝
 * 
 * Enter the number of devices (2-10): 4
 * 
 * Enter device names:
 * Device 1: PC1
 * Device 2: PC2
 * Device 3: Server
 * Device 4: Printer
 * 
 * ═══════════════════════════════════════════════════════════
 *                    BUS TOPOLOGY DIAGRAM                     
 * ═══════════════════════════════════════════════════════════
 * 
 *          [PC1]      [PC2]     [Server]   [Printer]
 *            │          │          │          │
 *            ┬          ┬          ┬          ┬
 * [T]════════╪══════════╪══════════╪══════════╪════════[T]
 * TERM                                                 TERM
 */
