/*
 * Slip 9 - Q2 Option A: IP Address Class Determination Program
 *
 * This program determines the class of an IP address based on its first octet.
 * It also provides additional information like default subnet mask, network type,
 * and validates the IP address format.
 *
 * IP Address Classes:
 *   Class A: 1-126     (Large networks)
 *   Class B: 128-191   (Medium networks)
 *   Class C: 192-223   (Small networks)
 *   Class D: 224-239   (Multicast)
 *   Class E: 240-255   (Reserved/Experimental)
 *   Loopback: 127      (Local testing)
 *
 * Compile: gcc -o ip_class Slip_09_Q2_OptionA.c
 * Run:     ./ip_class
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Structure to hold IP class information */
typedef struct {
    char class_name[20];
    char subnet_mask[20];
    char description[100];
    int network_bits;
    int host_bits;
} IPClassInfo;

/* Function prototypes */
int validate_ip_address(const char *ip, int octets[4]);
void determine_ip_class(int first_octet, IPClassInfo *info);
void check_private_address(int octets[4]);
void print_binary(int octet);
void display_ip_info(int octets[4], IPClassInfo *info);

int main() {
    char ip_address[50];
    int octets[4];
    IPClassInfo class_info;
    char choice;


    do {


        scanf("%s", ip_address);


        /* Validate IP address */
        if (!validate_ip_address(ip_address, octets)) {
            printf("❌ ERROR: Invalid IP address format!\n");
            printf("   Valid format: X.X.X.X where X is 0-255\n\n");
        } else {
            /* Determine IP class */
            determine_ip_class(octets[0], &class_info);

            display_ip_info(octets, &class_info);

            /* Check if private address */
            check_private_address(octets);
        }


        scanf(" %c", &choice);


    } while (choice == 'y' || choice == 'Y');

    printf("Thank you for using IP Class Determination Program!\n");
    return 0;
}

/*
 * Validates IP address format and extracts octets
 * Returns 1 if valid, 0 if invalid
 */
int validate_ip_address(const char *ip, int octets[4]) {
    int i, j, octet_count = 0;
    char temp[4];
    int temp_idx = 0;
    int len = strlen(ip);

    /* Check for empty string */
    if (len == 0 || len > 15) {
        return 0;
    }

    /* Parse IP address */
    for (i = 0; i <= len; i++) {
        if (ip[i] == '.' || ip[i] == '\0') {
            if (temp_idx == 0) {
                return 0;  /* Empty octet */
            }
            temp[temp_idx] = '\0';

            /* Convert to integer */
            octets[octet_count] = atoi(temp);

            /* Validate range */
            if (octets[octet_count] < 0 || octets[octet_count] > 255) {
                return 0;
            }

            /* Check for leading zeros (except "0" itself) */
            if (temp_idx > 1 && temp[0] == '0') {
                return 0;
            }

            octet_count++;
            temp_idx = 0;
        } else if (isdigit(ip[i])) {
            if (temp_idx >= 3) {
                return 0;  /* Octet too long */
            }
            temp[temp_idx++] = ip[i];
        } else {
            return 0;  /* Invalid character */
        }
    }

    /* Must have exactly 4 octets */
    return (octet_count == 4);
}

/*
 * Determines IP class based on first octet
 */
void determine_ip_class(int first_octet, IPClassInfo *info) {
    if (first_octet >= 1 && first_octet <= 126) {
        strcpy(info->class_name, "Class A");
        strcpy(info->subnet_mask, "255.0.0.0");
        strcpy(info->description, "Large networks (Govt, Large Corps)");
        info->network_bits = 8;
        info->host_bits = 24;
    }
    else if (first_octet == 127) {
        strcpy(info->class_name, "Loopback");
        strcpy(info->subnet_mask, "255.0.0.0");
        strcpy(info->description, "Reserved for loopback/localhost testing");
        info->network_bits = 8;
        info->host_bits = 24;
    }
    else if (first_octet >= 128 && first_octet <= 191) {
        strcpy(info->class_name, "Class B");
        strcpy(info->subnet_mask, "255.255.0.0");
        strcpy(info->description, "Medium networks (Universities, Companies)");
        info->network_bits = 16;
        info->host_bits = 16;
    }
    else if (first_octet >= 192 && first_octet <= 223) {
        strcpy(info->class_name, "Class C");
        strcpy(info->subnet_mask, "255.255.255.0");
        strcpy(info->description, "Small networks (Small business, Home)");
        info->network_bits = 24;
        info->host_bits = 8;
    }
    else if (first_octet >= 224 && first_octet <= 239) {
        strcpy(info->class_name, "Class D");
        strcpy(info->subnet_mask, "N/A");
        strcpy(info->description, "Multicast addresses (One-to-Many)");
        info->network_bits = 0;
        info->host_bits = 0;
    }
    else if (first_octet >= 240 && first_octet <= 255) {
        strcpy(info->class_name, "Class E");
        strcpy(info->subnet_mask, "N/A");
        strcpy(info->description, "Reserved for experimental/future use");
        info->network_bits = 0;
        info->host_bits = 0;
    }
    else {
        strcpy(info->class_name, "Invalid");
        strcpy(info->subnet_mask, "N/A");
        strcpy(info->description, "Invalid first octet (0 not allowed)");
        info->network_bits = 0;
        info->host_bits = 0;
    }
}

/*
 * Checks if the IP address is a private address
 */
void check_private_address(int octets[4]) {
    int is_private = 0;
    char private_range[50] = "";

    /* Class A Private: 10.0.0.0 - 10.255.255.255 */
    if (octets[0] == 10) {
        is_private = 1;
        strcpy(private_range, "10.0.0.0 - 10.255.255.255 (Class A Private)");
    }
    /* Class B Private: 172.16.0.0 - 172.31.255.255 */
    else if (octets[0] == 172 && octets[1] >= 16 && octets[1] <= 31) {
        is_private = 1;
        strcpy(private_range, "172.16.0.0 - 172.31.255.255 (Class B Private)");
    }
    /* Class C Private: 192.168.0.0 - 192.168.255.255 */
    else if (octets[0] == 192 && octets[1] == 168) {
        is_private = 1;
        strcpy(private_range, "192.168.0.0 - 192.168.255.255 (Class C Private)");
    }
    /* APIPA: 169.254.0.0 - 169.254.255.255 */
    else if (octets[0] == 169 && octets[1] == 254) {
        is_private = 1;
        strcpy(private_range, "169.254.0.0 - 169.254.255.255 (APIPA/Link-Local)");
    }


    if (is_private) {
        printf("🔒 PRIVATE (Non-routable on Internet)\n");

    } else if (octets[0] == 127) {
        printf("🔄 LOOPBACK (localhost)\n");
    } else if (octets[0] >= 224 && octets[0] <= 239) {
        printf("📡 MULTICAST\n");
    } else if (octets[0] >= 240) {
        printf("🧪 RESERVED/EXPERIMENTAL\n");
    } else {
        printf("🌐 PUBLIC (Routable on Internet)\n");
    }

}

/*
 * Prints a number in binary format (8 bits)
 */
void print_binary(int octet) {
    int i;
    for (i = 7; i >= 0; i--) {
        printf("%d", (octet >> i) & 1);
    }
}

/*
 * Displays all IP address information
 */
void display_ip_info(int octets[4], IPClassInfo *info) {
    unsigned long max_hosts;


    print_binary(octets[0]); printf(".");
    print_binary(octets[1]); printf(".");
    print_binary(octets[2]); printf(".");
    print_binary(octets[3]); printf("\n");


    if (info->host_bits > 0) {
        max_hosts = (1UL << info->host_bits) - 2;  /* 2^n - 2 */

    }


}
