/*
 * Slip 4 - Q2 Option B: Private IP Range Checker
 *
 * This program checks whether an IP address belongs to a private range
 * as defined by RFC 1918 (IPv4) and RFC 4193 (IPv6 ULA).
 *
 * Compile: gcc -o ip_checker Slip_04_Q2_OptionB.c
 * Run: ./ip_checker [ip_address]
 *
 * Author: Computer Networks Lab
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 256

/* IP Address Classification */
typedef enum {
    IP_INVALID,
    IP_PRIVATE_CLASS_A,      /* 10.0.0.0/8 */
    IP_PRIVATE_CLASS_B,      /* 172.16.0.0/12 */
    IP_PRIVATE_CLASS_C,      /* 192.168.0.0/16 */
    IP_LOOPBACK,             /* 127.0.0.0/8 */
    IP_LINK_LOCAL,           /* 169.254.0.0/16 */
    IP_MULTICAST,            /* 224.0.0.0/4 */
    IP_RESERVED,             /* 240.0.0.0/4 */
    IP_PUBLIC                /* All other routable addresses */
} IPClassification;

/* Structure to hold parsed IP address */
typedef struct {
    unsigned char octets[4];
    unsigned int as_integer;
    int is_valid;
} IPv4Address;

/* Structure for IP range definition */
typedef struct {
    unsigned int network;
    unsigned int mask;
    const char *name;
    const char *range_str;
    const char *description;
} IPRange;

/* Private and special IP ranges */
const IPRange IP_RANGES[] = {
    {0x0A000000, 0xFF000000, "Private Class A", "10.0.0.0/8",
     "Large private networks (16M hosts)"},
    {0xAC100000, 0xFFF00000, "Private Class B", "172.16.0.0/12",
     "Medium private networks (1M hosts)"},
    {0xC0A80000, 0xFFFF0000, "Private Class C", "192.168.0.0/16",
     "Small private networks (65K hosts)"},
    {0x7F000000, 0xFF000000, "Loopback", "127.0.0.0/8",
     "Local host testing"},
    {0xA9FE0000, 0xFFFF0000, "Link-Local (APIPA)", "169.254.0.0/16",
     "Auto-assigned when DHCP unavailable"},
    {0xE0000000, 0xF0000000, "Multicast", "224.0.0.0/4",
     "Group communication"},
    {0xF0000000, 0xF0000000, "Reserved", "240.0.0.0/4",
     "Future use/Experimental"},
    {0x00000000, 0xFF000000, "Current Network", "0.0.0.0/8",
     "This network (used in routing)"},
    {0xFFFFFFFF, 0xFFFFFFFF, "Broadcast", "255.255.255.255/32",
     "Limited broadcast address"},
    {0, 0, NULL, NULL, NULL}  /* Terminator */
};

/* Function prototypes */
int parse_ipv4(const char *ip_str, IPv4Address *addr);
IPClassification classify_ip(const IPv4Address *addr);
const char* classification_name(IPClassification class);
int is_private(IPClassification class);
void print_ip_details(const IPv4Address *addr, IPClassification class);
void print_all_ranges(void);
void print_binary(unsigned int num, int bits);
int interactive_mode(void);
int validate_octet(const char *str);

int main(int argc, char *argv[]) {
    IPv4Address addr;
    IPClassification class;


    if (argc == 2) {
        /* Single IP provided as argument */
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            printf("Usage: %s [ip_address]\n", argv[0]);
            printf("       %s              (interactive mode)\n", argv[0]);
            printf("       %s -r           (show all ranges)\n", argv[0]);
            return 0;
        }

        if (strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "--ranges") == 0) {
            print_all_ranges();
            return 0;
        }

        if (parse_ipv4(argv[1], &addr)) {
            class = classify_ip(&addr);
            print_ip_details(&addr, class);
        } else {
            printf("Error: Invalid IP address format '%s'\n", argv[1]);
            return 1;
        }
    } else {
        /* Interactive mode */
        return interactive_mode();
    }

    return 0;
}

/*
 * Parse IPv4 address string into structure
 * Returns 1 on success, 0 on failure
 */
int parse_ipv4(const char *ip_str, IPv4Address *addr) {
    int octets[4];
    char temp[MAX_INPUT];
    char *token;
    int count = 0;

    /* Make a copy to tokenize */
    strncpy(temp, ip_str, MAX_INPUT - 1);
    temp[MAX_INPUT - 1] = '\0';

    /* Remove leading/trailing whitespace */
    char *start = temp;
    while (*start && isspace(*start)) start++;
    char *end = start + strlen(start) - 1;
    while (end > start && isspace(*end)) *end-- = '\0';

    /* Parse octets */
    token = strtok(start, ".");
    while (token != NULL && count < 4) {
        if (!validate_octet(token)) {
            addr->is_valid = 0;
            return 0;
        }
        octets[count] = atoi(token);
        if (octets[count] < 0 || octets[count] > 255) {
            addr->is_valid = 0;
            return 0;
        }
        count++;
        token = strtok(NULL, ".");
    }

    if (count != 4) {
        addr->is_valid = 0;
        return 0;
    }

    /* Store octets */
    for (int i = 0; i < 4; i++) {
        addr->octets[i] = (unsigned char)octets[i];
    }

    /* Convert to 32-bit integer */
    addr->as_integer = (addr->octets[0] << 24) |
                       (addr->octets[1] << 16) |
                       (addr->octets[2] << 8)  |
                       addr->octets[3];

    addr->is_valid = 1;
    return 1;
}

/*
 * Validate octet string (only digits allowed)
 */
int validate_octet(const char *str) {
    if (str == NULL || *str == '\0') return 0;
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

/*
 * Classify IP address
 */
IPClassification classify_ip(const IPv4Address *addr) {
    if (!addr->is_valid) {
        return IP_INVALID;
    }

    unsigned int ip = addr->as_integer;

    /* Check private ranges first (RFC 1918) */

    /* Class A Private: 10.0.0.0/8 */
    if ((ip & 0xFF000000) == 0x0A000000) {
        return IP_PRIVATE_CLASS_A;
    }

    /* Class B Private: 172.16.0.0/12 (172.16.0.0 - 172.31.255.255) */
    if ((ip & 0xFFF00000) == 0xAC100000) {
        return IP_PRIVATE_CLASS_B;
    }

    /* Class C Private: 192.168.0.0/16 */
    if ((ip & 0xFFFF0000) == 0xC0A80000) {
        return IP_PRIVATE_CLASS_C;
    }

    /* Loopback: 127.0.0.0/8 */
    if ((ip & 0xFF000000) == 0x7F000000) {
        return IP_LOOPBACK;
    }

    /* Link-Local: 169.254.0.0/16 */
    if ((ip & 0xFFFF0000) == 0xA9FE0000) {
        return IP_LINK_LOCAL;
    }

    /* Multicast: 224.0.0.0/4 */
    if ((ip & 0xF0000000) == 0xE0000000) {
        return IP_MULTICAST;
    }

    /* Reserved: 240.0.0.0/4 */
    if ((ip & 0xF0000000) == 0xF0000000) {
        return IP_RESERVED;
    }

    return IP_PUBLIC;
}

/*
 * Get human-readable classification name
 */
const char* classification_name(IPClassification class) {
    switch (class) {
        case IP_PRIVATE_CLASS_A: return "Private (Class A)";
        case IP_PRIVATE_CLASS_B: return "Private (Class B)";
        case IP_PRIVATE_CLASS_C: return "Private (Class C)";
        case IP_LOOPBACK:        return "Loopback";
        case IP_LINK_LOCAL:      return "Link-Local (APIPA)";
        case IP_MULTICAST:       return "Multicast";
        case IP_RESERVED:        return "Reserved";
        case IP_PUBLIC:          return "Public (Routable)";
        case IP_INVALID:
        default:                 return "Invalid";
    }
}

/*
 * Check if IP is in private range
 */
int is_private(IPClassification class) {
    return (class == IP_PRIVATE_CLASS_A ||
            class == IP_PRIVATE_CLASS_B ||
            class == IP_PRIVATE_CLASS_C);
}

/*
 * Print binary representation
 */
void print_binary(unsigned int num, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i > 0 && i % 8 == 0) printf(".");
    }
}

/*
 * Print detailed information about IP address
 */
void print_ip_details(const IPv4Address *addr, IPClassification class) {

    printf("IP ADDRESS ANALYSIS\n");


    printf("IP Address:      %d.%d.%d.%d\n",
           addr->octets[0], addr->octets[1],
           addr->octets[2], addr->octets[3]);

    printf("Binary:          ");
    print_binary(addr->as_integer, 32);
    printf("\n");

    printf("Hexadecimal:     0x%08X\n", addr->as_integer);
    printf("Decimal:         %u\n\n", addr->as_integer);


    printf("CLASSIFICATION RESULT\n");


    printf("Type:            %s\n", classification_name(class));

    /* Private status with visual indicator */
    if (is_private(class)) {
        printf("Private Range:   ✓ YES (Cannot be routed on Internet)\n");
    } else if (class == IP_LOOPBACK || class == IP_LINK_LOCAL) {
        printf("Private Range:   ✓ YES (Special use - not routable)\n");
    } else if (class == IP_MULTICAST || class == IP_RESERVED) {
        printf("Private Range:   ✗ NO (Special purpose address)\n");
    } else {
        printf("Private Range:   ✗ NO (Publicly routable)\n");
    }

    /* Provide range details */
    printf("\n");
    switch (class) {
        case IP_PRIVATE_CLASS_A:
            printf("Range:           10.0.0.0 - 10.255.255.255\n");
            printf("CIDR:            10.0.0.0/8\n");
            printf("Subnet Mask:     255.0.0.0\n");
            printf("Total Hosts:     16,777,214\n");
            printf("Typical Use:     Large enterprise networks\n");
            break;

        case IP_PRIVATE_CLASS_B:
            printf("Range:           172.16.0.0 - 172.31.255.255\n");
            printf("CIDR:            172.16.0.0/12\n");
            printf("Subnet Mask:     255.240.0.0\n");
            printf("Total Hosts:     1,048,574\n");
            printf("Typical Use:     Medium-sized organizations\n");
            break;

        case IP_PRIVATE_CLASS_C:
            printf("Range:           192.168.0.0 - 192.168.255.255\n");
            printf("CIDR:            192.168.0.0/16\n");
            printf("Subnet Mask:     255.255.0.0\n");
            printf("Total Hosts:     65,534\n");
            printf("Typical Use:     Home/small office networks\n");
            break;

        case IP_LOOPBACK:
            printf("Range:           127.0.0.0 - 127.255.255.255\n");
            printf("CIDR:            127.0.0.0/8\n");
            printf("Typical Use:     Local testing, localhost\n");
            break;

        case IP_LINK_LOCAL:
            printf("Range:           169.254.0.0 - 169.254.255.255\n");
            printf("CIDR:            169.254.0.0/16\n");
            printf("Typical Use:     Auto-configuration (APIPA)\n");
            printf("Note:            Assigned when DHCP fails\n");
            break;

        case IP_MULTICAST:
            printf("Range:           224.0.0.0 - 239.255.255.255\n");
            printf("CIDR:            224.0.0.0/4\n");
            printf("Typical Use:     Group communication\n");
            break;

        case IP_RESERVED:
            printf("Range:           240.0.0.0 - 255.255.255.255\n");
            printf("CIDR:            240.0.0.0/4\n");
            printf("Typical Use:     Reserved for future use\n");
            break;

        case IP_PUBLIC:
            printf("Note:            This IP can be routed on the Internet\n");
            /* Determine class */
            if (addr->octets[0] >= 1 && addr->octets[0] <= 126) {
                printf("IP Class:        Class A (1.0.0.0 - 126.255.255.255)\n");
            } else if (addr->octets[0] >= 128 && addr->octets[0] <= 191) {
                printf("IP Class:        Class B (128.0.0.0 - 191.255.255.255)\n");
            } else if (addr->octets[0] >= 192 && addr->octets[0] <= 223) {
                printf("IP Class:        Class C (192.0.0.0 - 223.255.255.255)\n");
            }
            break;

        default:
            break;
    }


}

/*
 * Print all IP ranges
 */
void print_all_ranges(void) {

    printf("                    IP ADDRESS RANGES                          \n");


}

/*
 * Interactive mode - check multiple IPs
 */
int interactive_mode(void) {
    char input[MAX_INPUT];
    IPv4Address addr;
    IPClassification class;

    printf("Enter IP addresses to check (type 'quit' to exit, 'ranges' to show all ranges)\n\n");

    while (1) {
        printf("Enter IP address: ");

        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            break;
        }

        /* Remove newline */
        input[strcspn(input, "\n")] = '\0';

        /* Check for exit */
        if (strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0 ||
            strcmp(input, "q") == 0) {
            printf("\nGoodbye!\n");
            break;
        }

        /* Check for ranges command */
        if (strcmp(input, "ranges") == 0 || strcmp(input, "r") == 0) {
            print_all_ranges();
            continue;
        }

        /* Skip empty input */
        if (strlen(input) == 0) {
            continue;
        }

        /* Parse and classify */
        if (parse_ipv4(input, &addr)) {
            class = classify_ip(&addr);
            print_ip_details(&addr, class);
        } else {
            printf("Error: Invalid IP address format. Use format: x.x.x.x\n\n");
        }
    }

    return 0;
}

/*
 * ALGORITHM SUMMARY:
 *
 * 1. Parse Input:
 *    - Tokenize IP string by '.'
 *    - Validate each octet (0-255)
 *    - Convert to 32-bit integer for efficient comparison
 *
 * 2. Classification Logic:
 *    - Apply network mask using bitwise AND
 *    - Compare result with known network addresses
 *    - Check in order: Private A → Private B → Private C → Special → Public
 *
 * 3. Private Range Checks:
 *    Class A: (IP & 0xFF000000) == 0x0A000000  [10.x.x.x]
 *    Class B: (IP & 0xFFF00000) == 0xAC100000  [172.16-31.x.x]
 *    Class C: (IP & 0xFFFF0000) == 0xC0A80000  [192.168.x.x]
 *
 * TIME COMPLEXITY: O(1) - Fixed number of comparisons
 * SPACE COMPLEXITY: O(1) - Constant space usage
 *
 * EXAMPLE:
 * Input: 192.168.1.100
 * Binary: 11000000.10101000.00000001.01100100
 * Hex: 0xC0A80164
 * Mask 192.168.0.0/16: 0xFFFF0000
 * Result: 0xC0A80164 & 0xFFFF0000 = 0xC0A80000 ✓
 * Output: Private Class C
 */
