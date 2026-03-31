/*
 * Slip 10 - Q2 Option B: Subnetting and Supernetting Calculator
 * 
 * CONCEPTS:
 * =========
 * 
 * SUBNETTING:
 * -----------
 * Dividing a large network into smaller sub-networks.
 * - Borrows bits from host portion for network
 * - Increases number of networks
 * - Decreases hosts per network
 * - Example: 192.168.1.0/24 → 192.168.1.0/26 (4 subnets)
 * 
 * SUPERNETTING (CIDR):
 * --------------------
 * Combining multiple smaller networks into one larger network.
 * - Borrows bits from network portion for host
 * - Decreases number of networks
 * - Increases hosts per network
 * - Example: 192.168.0.0/24 + 192.168.1.0/24 → 192.168.0.0/23
 * 
 * KEY FORMULAS:
 * -------------
 * Total Hosts = 2^(32 - prefix) = 2^host_bits
 * Usable Hosts = 2^host_bits - 2
 * Number of Subnets = 2^borrowed_bits
 * Subnet Size (Block Size) = 2^remaining_host_bits
 * 
 * ALGORITHM:
 * ----------
 * For Subnetting:
 * 1. Parse IP address and original prefix
 * 2. Calculate new prefix based on required subnets/hosts
 * 3. Compute subnet mask, network, broadcast addresses
 * 4. List all subnet ranges
 * 
 * For Supernetting:
 * 1. Parse base IP and number of networks to combine
 * 2. Calculate new prefix (reduce prefix length)
 * 3. Verify networks are contiguous and aligned
 * 4. Output aggregated network
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Structure to hold IP address
typedef struct {
    unsigned char octet[4];
} IPAddress;

// Structure to hold subnet information
typedef struct {
    IPAddress network;
    IPAddress broadcast;
    IPAddress firstHost;
    IPAddress lastHost;
    IPAddress subnetMask;
    int prefix;
    unsigned int totalHosts;
    unsigned int usableHosts;
} SubnetInfo;

// Function prototypes
void parseIP(const char *ipStr, IPAddress *ip);
void ipToString(IPAddress ip, char *buffer);
unsigned int ipToInt(IPAddress ip);
IPAddress intToIP(unsigned int value);
IPAddress calculateSubnetMask(int prefix);
IPAddress calculateNetworkAddress(IPAddress ip, IPAddress mask);
IPAddress calculateBroadcastAddress(IPAddress network, int prefix);
void calculateSubnetInfo(IPAddress ip, int prefix, SubnetInfo *info);
void displaySubnetInfo(SubnetInfo *info);
void performSubnetting(IPAddress baseIP, int originalPrefix, int newPrefix);
void performSupernetting(IPAddress baseIP, int prefix, int numNetworks);
int validateIP(const char *ipStr);
void displaySubnetTable(int prefix);
void interactiveSubnetting(void);
void interactiveSupernetting(void);
void displayCIDRTable(void);

/*
 * Parse IP address string to IPAddress structure
 */
void parseIP(const char *ipStr, IPAddress *ip) {
    int octets[4];
    sscanf(ipStr, "%d.%d.%d.%d", &octets[0], &octets[1], &octets[2], &octets[3]);
    for (int i = 0; i < 4; i++) {
        ip->octet[i] = (unsigned char)octets[i];
    }
}

/*
 * Convert IPAddress to string
 */
void ipToString(IPAddress ip, char *buffer) {
    sprintf(buffer, "%d.%d.%d.%d", ip.octet[0], ip.octet[1], ip.octet[2], ip.octet[3]);
}

/*
 * Convert IPAddress to 32-bit unsigned integer
 */
unsigned int ipToInt(IPAddress ip) {
    return ((unsigned int)ip.octet[0] << 24) |
           ((unsigned int)ip.octet[1] << 16) |
           ((unsigned int)ip.octet[2] << 8) |
           ((unsigned int)ip.octet[3]);
}

/*
 * Convert 32-bit integer to IPAddress
 */
IPAddress intToIP(unsigned int value) {
    IPAddress ip;
    ip.octet[0] = (value >> 24) & 0xFF;
    ip.octet[1] = (value >> 16) & 0xFF;
    ip.octet[2] = (value >> 8) & 0xFF;
    ip.octet[3] = value & 0xFF;
    return ip;
}

/*
 * Calculate subnet mask from prefix length
 */
IPAddress calculateSubnetMask(int prefix) {
    unsigned int mask = 0;
    if (prefix > 0) {
        mask = ~((1U << (32 - prefix)) - 1);
    }
    return intToIP(mask);
}

/*
 * Calculate network address (IP AND Mask)
 */
IPAddress calculateNetworkAddress(IPAddress ip, IPAddress mask) {
    IPAddress network;
    for (int i = 0; i < 4; i++) {
        network.octet[i] = ip.octet[i] & mask.octet[i];
    }
    return network;
}

/*
 * Calculate broadcast address
 */
IPAddress calculateBroadcastAddress(IPAddress network, int prefix) {
    unsigned int netInt = ipToInt(network);
    unsigned int hostBits = 32 - prefix;
    unsigned int broadcastInt = netInt | ((1U << hostBits) - 1);
    return intToIP(broadcastInt);
}

/*
 * Calculate complete subnet information
 */
void calculateSubnetInfo(IPAddress ip, int prefix, SubnetInfo *info) {
    info->prefix = prefix;
    info->subnetMask = calculateSubnetMask(prefix);
    info->network = calculateNetworkAddress(ip, info->subnetMask);
    info->broadcast = calculateBroadcastAddress(info->network, prefix);
    
    // Calculate host addresses
    unsigned int networkInt = ipToInt(info->network);
    unsigned int broadcastInt = ipToInt(info->broadcast);
    
    info->firstHost = intToIP(networkInt + 1);
    info->lastHost = intToIP(broadcastInt - 1);
    
    // Calculate host counts
    int hostBits = 32 - prefix;
    info->totalHosts = (1U << hostBits);
    info->usableHosts = (hostBits >= 2) ? (info->totalHosts - 2) : 0;
}

/*
 * Display subnet information
 */
void displaySubnetInfo(SubnetInfo *info) {
    char buffer[20];
    
    printf("\n┌────────────────────────────────────────────┐\n");
    printf("│           SUBNET INFORMATION               │\n");
    printf("├────────────────────────────────────────────┤\n");
    
    ipToString(info->network, buffer);
    printf("│ Network Address    : %-20s │\n", buffer);
    
    ipToString(info->subnetMask, buffer);
    printf("│ Subnet Mask        : %-20s │\n", buffer);
    
    printf("│ CIDR Notation      : /%-19d │\n", info->prefix);
    
    ipToString(info->broadcast, buffer);
    printf("│ Broadcast Address  : %-20s │\n", buffer);
    
    ipToString(info->firstHost, buffer);
    printf("│ First Usable Host  : %-20s │\n", buffer);
    
    ipToString(info->lastHost, buffer);
    printf("│ Last Usable Host   : %-20s │\n", buffer);
    
    printf("│ Total Addresses    : %-20u │\n", info->totalHosts);
    printf("│ Usable Hosts       : %-20u │\n", info->usableHosts);
    
    printf("└────────────────────────────────────────────┘\n");
}

/*
 * Perform subnetting and list all subnets
 */
void performSubnetting(IPAddress baseIP, int originalPrefix, int newPrefix) {
    char buffer[20];
    
    if (newPrefix <= originalPrefix) {
        printf("Error: New prefix must be greater than original prefix.\n");
        return;
    }
    
    if (newPrefix > 30) {
        printf("Error: Prefix cannot exceed 30 for usable subnets.\n");
        return;
    }
    
    int borrowedBits = newPrefix - originalPrefix;
    int numSubnets = 1 << borrowedBits;  // 2^borrowed_bits
    int hostsPerSubnet = (1 << (32 - newPrefix)) - 2;  // 2^host_bits - 2
    int subnetSize = 1 << (32 - newPrefix);  // Block size
    
    printf("\n%s\n", "═══════════════════════════════════════════════════════════════════");
    printf("                    SUBNETTING CALCULATION\n");
    printf("%s\n", "═══════════════════════════════════════════════════════════════════");
    
    ipToString(baseIP, buffer);
    printf("\n Original Network  : %s/%d\n", buffer, originalPrefix);
    printf(" New Prefix        : /%d\n", newPrefix);
    printf(" Bits Borrowed     : %d\n", borrowedBits);
    printf(" Number of Subnets : %d\n", numSubnets);
    printf(" Hosts per Subnet  : %d (usable)\n", hostsPerSubnet);
    printf(" Subnet Block Size : %d addresses\n", subnetSize);
    
    // Calculate and display subnet mask
    IPAddress newMask = calculateSubnetMask(newPrefix);
    ipToString(newMask, buffer);
    printf(" New Subnet Mask   : %s\n", buffer);
    
    // List all subnets
    printf("\n┌─────┬───────────────────────┬───────────────────────┬───────────────────────┐\n");
    printf("│ #   │ Network Address       │ Host Range            │ Broadcast Address     │\n");
    printf("├─────┼───────────────────────┼───────────────────────┼───────────────────────┤\n");
    
    IPAddress baseMask = calculateSubnetMask(originalPrefix);
    IPAddress networkBase = calculateNetworkAddress(baseIP, baseMask);
    unsigned int baseInt = ipToInt(networkBase);
    
    for (int i = 0; i < numSubnets && i < 16; i++) {  // Limit display to 16 subnets
        SubnetInfo info;
        IPAddress subnetIP = intToIP(baseInt + (i * subnetSize));
        calculateSubnetInfo(subnetIP, newPrefix, &info);
        
        char netStr[20], firstStr[20], lastStr[20], broadStr[20];
        ipToString(info.network, netStr);
        ipToString(info.firstHost, firstStr);
        ipToString(info.lastHost, lastStr);
        ipToString(info.broadcast, broadStr);
        
        char rangeStr[45];
        sprintf(rangeStr, "%s - %s", firstStr, lastStr);
        
        printf("│ %-3d │ %-21s │ %-21s │ %-21s │\n", 
               i + 1, netStr, rangeStr, broadStr);
    }
    
    if (numSubnets > 16) {
        printf("│ ... │ ... (showing first 16 of %d subnets)                              │\n", numSubnets);
    }
    
    printf("└─────┴───────────────────────┴───────────────────────┴───────────────────────┘\n");
}

/*
 * Perform supernetting (route aggregation)
 */
void performSupernetting(IPAddress baseIP, int prefix, int numNetworks) {
    char buffer[20];
    
    // Check if numNetworks is power of 2
    if ((numNetworks & (numNetworks - 1)) != 0) {
        printf("Error: Number of networks must be a power of 2.\n");
        return;
    }
    
    // Calculate bits needed
    int bitsNeeded = 0;
    int temp = numNetworks;
    while (temp > 1) {
        bitsNeeded++;
        temp >>= 1;
    }
    
    int newPrefix = prefix - bitsNeeded;
    
    if (newPrefix < 0) {
        printf("Error: Cannot aggregate that many networks.\n");
        return;
    }
    
    // Verify alignment - base network must be aligned to new boundary
    unsigned int baseInt = ipToInt(baseIP);
    unsigned int supernetSize = 1U << (32 - newPrefix);
    unsigned int alignedBase = baseInt & ~(supernetSize - 1);
    
    printf("\n%s\n", "═══════════════════════════════════════════════════════════════════");
    printf("                    SUPERNETTING CALCULATION\n");
    printf("%s\n", "═══════════════════════════════════════════════════════════════════");
    
    ipToString(baseIP, buffer);
    printf("\n Base Network      : %s/%d\n", buffer, prefix);
    printf(" Networks to Merge : %d\n", numNetworks);
    printf(" Bits Released     : %d\n", bitsNeeded);
    printf(" New Prefix        : /%d\n", newPrefix);
    
    // Show networks being combined
    printf("\n Networks being combined:\n");
    printf(" ┌────┬───────────────────────┐\n");
    printf(" │ #  │ Network Address       │\n");
    printf(" ├────┼───────────────────────┤\n");
    
    unsigned int originalSize = 1U << (32 - prefix);
    for (int i = 0; i < numNetworks && i < 8; i++) {
        IPAddress net = intToIP(alignedBase + (i * originalSize));
        char netStr[20];
        ipToString(net, netStr);
        printf(" │ %-2d │ %-21s │\n", i + 1, netStr);
    }
    if (numNetworks > 8) {
        printf(" │ ...│ (showing first 8)     │\n");
    }
    printf(" └────┴───────────────────────┘\n");
    
    // Calculate and display supernet info
    SubnetInfo supernetInfo;
    calculateSubnetInfo(intToIP(alignedBase), newPrefix, &supernetInfo);
    
    printf("\n Result (Supernet):\n");
    displaySubnetInfo(&supernetInfo);
    
    // Show routing advantage
    printf("\n Routing Benefit:\n");
    printf(" Before: %d routes in routing table\n", numNetworks);
    printf(" After:  1 aggregated route\n");
    ipToString(intToIP(alignedBase), buffer);
    printf(" Aggregated Route: %s/%d\n", buffer, newPrefix);
}

/*
 * Display CIDR reference table
 */
void displayCIDRTable(void) {
    printf("\n%s\n", "═══════════════════════════════════════════════════════════════════");
    printf("                    CIDR REFERENCE TABLE\n");
    printf("%s\n", "═══════════════════════════════════════════════════════════════════");
    
    printf("\n┌────────┬─────────────────────┬────────────────┬────────────────┐\n");
    printf("│ Prefix │ Subnet Mask         │ Total Hosts    │ Usable Hosts   │\n");
    printf("├────────┼─────────────────────┼────────────────┼────────────────┤\n");
    
    for (int prefix = 24; prefix <= 30; prefix++) {
        IPAddress mask = calculateSubnetMask(prefix);
        char maskStr[20];
        ipToString(mask, maskStr);
        
        unsigned int total = 1U << (32 - prefix);
        unsigned int usable = (prefix <= 30) ? total - 2 : 0;
        
        printf("│ /%-5d │ %-19s │ %-14u │ %-14u │\n", 
               prefix, maskStr, total, usable);
    }
    printf("└────────┴─────────────────────┴────────────────┴────────────────┘\n");
    
    printf("\n Common Class-based Subnetting:\n");
    printf(" ┌─────────┬─────────────────────┬──────────────────────┐\n");
    printf(" │ Class   │ Default Mask        │ Default Prefix       │\n");
    printf(" ├─────────┼─────────────────────┼──────────────────────┤\n");
    printf(" │ Class A │ 255.0.0.0           │ /8                   │\n");
    printf(" │ Class B │ 255.255.0.0         │ /16                  │\n");
    printf(" │ Class C │ 255.255.255.0       │ /24                  │\n");
    printf(" └─────────┴─────────────────────┴──────────────────────┘\n");
}

/*
 * Interactive subnetting mode
 */
void interactiveSubnetting(void) {
    char ipStr[20];
    int originalPrefix, newPrefix;
    
    printf("\n=== SUBNETTING MODE ===\n");
    printf("Enter IP address (e.g., 192.168.1.0): ");
    scanf("%19s", ipStr);
    
    printf("Enter original prefix (e.g., 24): ");
    scanf("%d", &originalPrefix);
    
    printf("Enter new prefix for subnetting (e.g., 26): ");
    scanf("%d", &newPrefix);
    
    IPAddress ip;
    parseIP(ipStr, &ip);
    performSubnetting(ip, originalPrefix, newPrefix);
}

/*
 * Interactive supernetting mode
 */
void interactiveSupernetting(void) {
    char ipStr[20];
    int prefix, numNetworks;
    
    printf("\n=== SUPERNETTING MODE ===\n");
    printf("Enter base IP address (e.g., 192.168.0.0): ");
    scanf("%19s", ipStr);
    
    printf("Enter current prefix (e.g., 24): ");
    scanf("%d", &prefix);
    
    printf("Enter number of networks to combine (power of 2, e.g., 2, 4, 8): ");
    scanf("%d", &numNetworks);
    
    IPAddress ip;
    parseIP(ipStr, &ip);
    performSupernetting(ip, prefix, numNetworks);
}

/*
 * Calculate subnet from IP and prefix
 */
void calculateSubnet(void) {
    char ipStr[20];
    int prefix;
    
    printf("\n=== SUBNET CALCULATOR ===\n");
    printf("Enter IP address (e.g., 192.168.10.50): ");
    scanf("%19s", ipStr);
    
    printf("Enter prefix length (e.g., 24): ");
    scanf("%d", &prefix);
    
    if (prefix < 0 || prefix > 32) {
        printf("Error: Invalid prefix. Must be 0-32.\n");
        return;
    }
    
    IPAddress ip;
    parseIP(ipStr, &ip);
    
    SubnetInfo info;
    calculateSubnetInfo(ip, prefix, &info);
    
    printf("\n Input: %s/%d\n", ipStr, prefix);
    displaySubnetInfo(&info);
}

/*
 * Demonstrate subnetting example
 */
void demonstrateExample(void) {
    printf("\n%s\n", "═══════════════════════════════════════════════════════════════════");
    printf("            EXAMPLE: Subnetting 192.168.10.0/24 into /26\n");
    printf("%s\n", "═══════════════════════════════════════════════════════════════════");
    
    IPAddress ip;
    parseIP("192.168.10.0", &ip);
    
    // First show original network
    printf("\n ORIGINAL NETWORK:\n");
    SubnetInfo originalInfo;
    calculateSubnetInfo(ip, 24, &originalInfo);
    displaySubnetInfo(&originalInfo);
    
    // Then subnet
    performSubnetting(ip, 24, 26);
    
    printf("\n%s\n", "═══════════════════════════════════════════════════════════════════");
    printf("            EXAMPLE: Supernetting 4 x /24 into /22\n");
    printf("%s\n", "═══════════════════════════════════════════════════════════════════");
    
    parseIP("192.168.0.0", &ip);
    performSupernetting(ip, 24, 4);
}

/*
 * Main function with menu
 */
int main(void) {
    int choice;
    
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════════╗\n");
    printf("║       SUBNETTING AND SUPERNETTING CALCULATOR                      ║\n");
    printf("║       Slip 10 - Computer Networks                                 ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════╝\n");
    
    do {
        printf("\n┌─────────────────────────────────────────┐\n");
        printf("│              MAIN MENU                  │\n");
        printf("├─────────────────────────────────────────┤\n");
        printf("│ 1. Calculate subnet info from IP/Prefix │\n");
        printf("│ 2. Perform Subnetting                   │\n");
        printf("│ 3. Perform Supernetting                 │\n");
        printf("│ 4. Show CIDR Reference Table            │\n");
        printf("│ 5. Run Demonstration Examples           │\n");
        printf("│ 0. Exit                                 │\n");
        printf("└─────────────────────────────────────────┘\n");
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
        }
        
        switch (choice) {
            case 1:
                calculateSubnet();
                break;
            case 2:
                interactiveSubnetting();
                break;
            case 3:
                interactiveSupernetting();
                break;
            case 4:
                displayCIDRTable();
                break;
            case 5:
                demonstrateExample();
                break;
            case 0:
                printf("\nExiting program. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 0);
    
    return 0;
}

/*
 * PSEUDOCODE:
 * ===========
 * 
 * FUNCTION calculateSubnetMask(prefix):
 *     mask = 0xFFFFFFFF << (32 - prefix)
 *     RETURN mask as IP address
 * 
 * 
 * FUNCTION calculateNetworkAddress(ip, mask):
 *     network = ip AND mask
 *     RETURN network
 * 
 * 
 * FUNCTION calculateBroadcastAddress(network, prefix):
 *     hostBits = 32 - prefix
 *     broadcast = network OR ((2^hostBits) - 1)
 *     RETURN broadcast
 * 
 * 
 * FUNCTION subnetting(baseNetwork, originalPrefix, newPrefix):
 *     borrowedBits = newPrefix - originalPrefix
 *     numSubnets = 2^borrowedBits
 *     subnetSize = 2^(32 - newPrefix)
 *     
 *     FOR i = 0 TO numSubnets - 1:
 *         subnetNetwork = baseNetwork + (i * subnetSize)
 *         subnetBroadcast = subnetNetwork + subnetSize - 1
 *         firstHost = subnetNetwork + 1
 *         lastHost = subnetBroadcast - 1
 *         PRINT subnet details
 * 
 * 
 * FUNCTION supernetting(baseNetwork, prefix, numNetworks):
 *     bitsReleased = log2(numNetworks)
 *     newPrefix = prefix - bitsReleased
 *     supernetMask = calculateSubnetMask(newPrefix)
 *     supernetNetwork = baseNetwork AND supernetMask
 *     PRINT aggregated route details
 * 
 * 
 * SAMPLE OUTPUT:
 * ==============
 * 
 * ═══════════════════════════════════════════════════════════════════
 *                     SUBNETTING CALCULATION
 * ═══════════════════════════════════════════════════════════════════
 * 
 *  Original Network  : 192.168.10.0/24
 *  New Prefix        : /26
 *  Bits Borrowed     : 2
 *  Number of Subnets : 4
 *  Hosts per Subnet  : 62 (usable)
 *  Subnet Block Size : 64 addresses
 *  New Subnet Mask   : 255.255.255.192
 * 
 * ┌─────┬───────────────────────┬───────────────────────┬───────────────────────┐
 * │ #   │ Network Address       │ Host Range            │ Broadcast Address     │
 * ├─────┼───────────────────────┼───────────────────────┼───────────────────────┤
 * │ 1   │ 192.168.10.0          │ 192.168.10.1 - .62    │ 192.168.10.63         │
 * │ 2   │ 192.168.10.64         │ 192.168.10.65 - .126  │ 192.168.10.127        │
 * │ 3   │ 192.168.10.128        │ 192.168.10.129 - .190 │ 192.168.10.191        │
 * │ 4   │ 192.168.10.192        │ 192.168.10.193 - .254 │ 192.168.10.255        │
 * └─────┴───────────────────────┴───────────────────────┴───────────────────────┘
 * 
 * 
 * ═══════════════════════════════════════════════════════════════════
 *                     SUPERNETTING CALCULATION
 * ═══════════════════════════════════════════════════════════════════
 * 
 *  Base Network      : 192.168.0.0/24
 *  Networks to Merge : 4
 *  Bits Released     : 2
 *  New Prefix        : /22
 * 
 *  Networks being combined:
 *  ┌────┬───────────────────────┐
 *  │ #  │ Network Address       │
 *  ├────┼───────────────────────┤
 *  │ 1  │ 192.168.0.0           │
 *  │ 2  │ 192.168.1.0           │
 *  │ 3  │ 192.168.2.0           │
 *  │ 4  │ 192.168.3.0           │
 *  └────┴───────────────────────┘
 * 
 *  Result (Supernet):
 *  Network Address    : 192.168.0.0
 *  Subnet Mask        : 255.255.252.0
 *  Usable Hosts       : 1022
 * 
 *  Routing Benefit:
 *  Before: 4 routes in routing table
 *  After:  1 aggregated route
 *  Aggregated Route: 192.168.0.0/22
 */
