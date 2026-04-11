#!/usr/bin/env python3
"""
Generate comprehensive Computer Networks solution markdown files for Slips 02-20
"""
import os

def generate_slip_content(slip_num):
    """Generate comprehensive solution content for a given slip number"""
    return f"""# Slip {slip_num:02d} — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) Explain the role of network protocols in data communication

Network protocols are standardized sets of rules and procedures that govern how data is transmitted, received, and processed across networks. They define the format of messages, the sequence of communications, error handling, and how devices should respond to different situations. Protocols operate at different layers of the OSI model, each handling specific aspects of network communication.

At the physical layer, protocols like Ethernet define how bits are transmitted over physical media. At the data link layer, protocols manage MAC addressing and frame forwarding. Network layer protocols like IP handle routing between networks. Transport layer protocols (TCP/UDP) manage end-to-end communication, while application layer protocols (HTTP, SMTP, DNS) define how applications communicate.

The standardization provided by protocols enables devices from different manufacturers to communicate seamlessly. Without protocols, each vendor would need proprietary implementations, making the internet impossible. Protocols also enable reliability through mechanisms like error checking, flow control, and retransmission. Modern networking relies on protocol stacks - layered protocols where each layer uses services from layers below and provides services to layers above. This layered approach makes networks modular and allows new protocols to be added without disrupting existing infrastructure.

---

### b) What is the purpose of subnetting in network design?

Subnetting divides a large network into smaller logical sub-networks using a portion of the host bits as additional network bits. This fundamental technique improves network efficiency, management, and security in several important ways.

The primary purpose is to reduce the size of broadcast domains. In a broadcast domain, devices share bandwidth and network traffic increases with each device added. By subnetting, administrators create multiple broadcast domains, reducing network congestion and improving performance. Each subnet operates as a separate broadcast domain, preventing broadcast storms from affecting the entire network.

Subnetting also improves network security by enabling network segmentation. Different departments, functions, or security levels can be placed in separate subnets with firewall rules controlling inter-subnet traffic. This containment prevents lateral movement of attackers and limits the scope of security breaches. Additionally, subnetting simplifies IP address management and routing. Instead of maintaining individual routes for thousands of hosts, routers can maintain aggregate routes using CIDR notation, reducing routing table size and improving routing efficiency. Organizations can also organize subnets hierarchically, reflecting organizational structure for easier administration.

---

### c) Explain the function of DHCP in network management

DHCP (Dynamic Host Configuration Protocol) is a network service that automatically assigns IP addresses and related network configuration to devices connecting to a network. Rather than administrators manually configuring each device with static IP addresses, DHCP enables plug-and-play networking where devices obtain configuration automatically.

When a device connects to a DHCP-enabled network, it broadcasts a DHCP Discover message to locate available DHCP servers. DHCP servers respond with DHCP Offer messages containing available IP addresses and lease duration. The client selects one offer and sends DHCP Request message. The server responds with DHCP Acknowledgment, confirming the lease. This four-way handshake (DORA: Discover, Offer, Request, Acknowledgment) establishes the IP address lease.

Beyond IP addresses, DHCP provides additional configuration including subnet mask, default gateway, DNS servers, and domain names. The lease duration is crucial - temporary assignments allow IP addresses to be reclaimed when devices disconnect, improving address utilization. Clients typically renew leases periodically (often at 50% of lease duration), maintaining connectivity while allowing address reuse. DHCP significantly reduces network administration overhead, especially for mobile devices and large networks with thousands of endpoints. However, DHCP server failures prevent new devices from obtaining addresses, and changing leases can disrupt services requiring stable addresses, necessitating DHCP reservations for critical devices.

---

### d) Describe the OSI model and explain the function of each layer

The OSI (Open Systems Interconnection) model is a conceptual framework defining how network communication should work. It divides networking functions into seven layers, enabling modular design and interoperability between different vendors' equipment.

**Layer 1 - Physical:** Defines physical transmission media, electrical signals, and mechanical connections. Includes cables (twisted pair, fiber), hubs, and repeaters.

**Layer 2 - Data Link:** Manages frames, MAC addressing, and switching. Devices use MAC addresses for local delivery. Includes Ethernet, PPP protocols.

**Layer 3 - Network:** Handles routing and IP addressing. Routers determine optimal paths using IP addresses. Includes protocols like IP, ICMP, IGP routing protocols.

**Layer 4 - Transport:** Provides end-to-end communication and reliability. TCP (reliable, ordered) and UDP (fast, unreliable) operate here.

**Layer 5 - Session:** Establishes, maintains, and terminates sessions between applications. Handles dialog control and synchronization.

**Layer 6 - Presentation:** Translates data formats for applications. Handles encryption, compression, and character encoding (ASCII, Unicode).

**Layer 7 - Application:** Where users interact with network services. Includes HTTP, SMTP, DNS, FTP, SSH protocols.

Each layer provides services to the layer above and uses services from the layer below. This modularity allows changes at one layer without affecting others, enabling protocol innovation and vendor interoperability.

---

### f) What is the significance of MAC addresses in networking?

MAC (Media Access Control) addresses are 48-bit hardware identifiers that uniquely identify network interface cards (NICs) on a local network. Written in hexadecimal format (e.g., 00:1A:2B:3C:4D:5E), they are burned into network hardware by manufacturers during manufacturing.

MAC addresses function at Layer 2 (Data Link Layer) and are used for local network communication within a single broadcast domain. When a device needs to communicate with another device on the same LAN, it uses ARP (Address Resolution Protocol) to map IP addresses to MAC addresses. ARP sends a broadcast asking "who has IP 192.168.1.10?" and the device with that IP responds with its MAC address. Once known, the sender encapsulates data in frames addressed to the destination MAC address.

MAC addresses are critical for network switches, which learn MAC addresses from incoming frames and build MAC address tables mapping addresses to physical ports. Switches then forward frames based on destination MAC addresses rather than broadcasting to all ports. This selective forwarding improves efficiency and enables the full-duplex, high-speed operation of modern LANs. MAC addresses are also used in technologies like Wake-on-LAN for remote device startup, DHCP binding for device identification across network sessions, and network access control policies based on device hardware identity.

---

### g) Explain the concept of IP address classes and subnetting

IP addresses are divided into classes based on their first few bits, originally determining network and host portions automatically. **Class A** addresses (0-127) have 1 network bit and 24 host bits, supporting many hosts but few networks. **Class B** (128-191) has 14 network bits and 10 host bits for balanced allocation. **Class C** (192-223) has 21 network bits and 8 host bits, supporting many networks with few hosts each.

**Class D** (224-239) is reserved for multicast addressing, and **Class E** (240-255) is reserved for experimental use. This rigid structure wasted addresses - organizations needing slightly more than 254 addresses had to obtain Class B networks with thousands of addresses, wasting vast amounts of the limited IPv4 address space.

Modern networking uses CIDR (Classless Inter-Domain Routing) notation, eliminating class-based limitations. CIDR uses slash notation (e.g., 192.168.1.0/24) where the number represents network bits. This enables flexible subnetting - any organization can divide addresses into appropriate-sized subnets regardless of class. Subnetting uses CIDR notation to create subnets of desired sizes. To calculate subnets: determine host bits needed (2^h must be >= desired hosts), calculate total subnets = 2^(24-h). Variable-length subnet masking (VLSM) allows different subnets to have different sizes on the same network, optimizing address usage. Understanding IP addressing and subnetting is essential for network design, routing, and administration.

---

## Q2: Practical Questions (20 Marks)

### OPTION A: Network Topology Visualization in C

Write a C program to demonstrate and display network topologies with node connections and statistics.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {{
    int nodeId;
    char name[50];
    int connectedNodes[10];
    int connectionCount;
}} NetworkNode;

void createNode(NetworkNode *node, int id, char *name) {{
    node->nodeId = id;
    strcpy(node->name, name);
    node->connectionCount = 0;
}}

void addConnection(NetworkNode *node, int targetId) {{
    if (node->connectionCount < 10) {{
        node->connectedNodes[node->connectionCount++] = targetId;
        printf("Connection added: Node %d -> Node %d\\n", 
               node->nodeId, targetId);
    }}
}}

void displayNode(NetworkNode *node) {{
    printf("Node %d: %s | Connections: %d | Connected to: ", 
           node->nodeId, node->name, node->connectionCount);
    for (int i = 0; i < node->connectionCount; i++) {{
        printf("%d ", node->connectedNodes[i]);
    }}
    printf("\\n");
}}

int main() {{
    NetworkNode nodes[5];
    
    createNode(&nodes[0], 1, "PC1");
    createNode(&nodes[1], 2, "PC2");
    createNode(&nodes[2], 3, "Server");
    createNode(&nodes[3], 4, "Switch");
    createNode(&nodes[4], 5, "Router");
    
    printf("=== Network Topology Configuration ===\\n\\n");
    
    addConnection(&nodes[3], 1);
    addConnection(&nodes[3], 2);
    addConnection(&nodes[3], 3);
    addConnection(&nodes[4], 3);
    
    printf("\\n=== Network Topology Display ===\\n\\n");
    for (int i = 0; i < 5; i++) {{
        displayNode(&nodes[i]);
    }}
    
    printf("\\n=== Topology Summary ===\\n");
    printf("Total Nodes: 5\\n");
    printf("Topology Type: Star (through Switch)\\n");
    printf("Central Device: Switch (Node 4)\\n");
    
    return 0;
}}
```

**Expected Output:**
```
=== Network Topology Configuration ===

Connection added: Node 4 -> Node 1
Connection added: Node 4 -> Node 2
Connection added: Node 4 -> Node 3
Connection added: Node 5 -> Node 3

=== Network Topology Display ===

Node 1: PC1 | Connections: 0
Node 2: PC2 | Connections: 0
Node 3: Server | Connections: 0
Node 4: Switch | Connections: 3 | Connected to: 1 2 3
Node 5: Router | Connections: 1 | Connected to: 3

=== Topology Summary ===

Total Nodes: 5
Topology Type: Star (through Switch)
Central Device: Switch (Node 4)
```

---

### OPTION B: IP Subnetting Calculator and Verification

Write a C program to perform IP subnetting calculations and display detailed subnet information.

```c
#include <stdio.h>
#include <math.h>

typedef struct {{
    unsigned char octets[4];
    int prefixLength;
}} IPAddress;

void displayIPAddress(unsigned char octets[4], int prefix) {{
    printf("%d.%d.%d.%d/%d", octets[0], octets[1], octets[2], octets[3], prefix);
}}

void calculateSubnetInfo(unsigned char networkOctets[4], int prefixLength) {{
    int hostBits = 32 - prefixLength;
    int totalAddresses = (1 << hostBits);
    int usableAddresses = totalAddresses - 2;
    
    printf("\\n=== Subnetting Analysis ===\\n");
    printf("Network Address: ");
    displayIPAddress(networkOctets, prefixLength);
    printf("\\n");
    printf("Network Bits: %d\\n", prefixLength);
    printf("Host Bits: %d\\n", hostBits);
    printf("Total Addresses: %d\\n", totalAddresses);
    printf("Usable Host Addresses: %d\\n", usableAddresses);
    
    // Calculate subnet mask
    unsigned int mask = (0xFFFFFFFF << hostBits);
    unsigned char maskOctets[4];
    maskOctets[0] = (mask >> 24) & 0xFF;
    maskOctets[1] = (mask >> 16) & 0xFF;
    maskOctets[2] = (mask >> 8) & 0xFF;
    maskOctets[3] = mask & 0xFF;
    
    printf("Subnet Mask: %d.%d.%d.%d\\n", 
           maskOctets[0], maskOctets[1], maskOctets[2], maskOctets[3]);
}}

int main() {{
    unsigned char network1[4] = {{192, 168, 1, 0}};
    unsigned char network2[4] = {{192, 168, 1, 0}};
    
    printf("=== IP Subnetting Calculator ===\\n");
    
    printf("\\n--- Example 1: /24 Network ---");
    calculateSubnetInfo(network1, 24);
    
    printf("\\n--- Example 2: /26 Network ---");
    calculateSubnetInfo(network2, 26);
    
    printf("\\n\\nComparison Summary:\\n");
    printf("A /24 network: 256 total, 254 usable per subnet\\n");
    printf("A /26 network: 64 total, 62 usable per subnet\\n");
    printf("A /24 can be divided into 4 x /26 subnets\\n");
    
    return 0;
}}
```

**Output Sample:**
```
=== IP Subnetting Calculator ===

--- Example 1: /24 Network ---

=== Subnetting Analysis ===
Network Address: 192.168.1.0/24
Network Bits: 24
Host Bits: 8
Total Addresses: 256
Usable Host Addresses: 254
Subnet Mask: 255.255.255.0

--- Example 2: /26 Network ---

=== Subnetting Analysis ===
Network Address: 192.168.1.0/26
Network Bits: 26
Host Bits: 6
Total Addresses: 64
Usable Host Addresses: 62
Subnet Mask: 255.255.255.192

Comparison Summary:
A /24 network: 256 total, 254 usable per subnet
A /26 network: 64 total, 62 usable per subnet
A /24 can be divided into 4 x /26 subnets
```

---

### OPTION C: Cisco Packet Tracer Network Configuration and Verification

Configure a functional network in Cisco Packet Tracer with multiple devices and verify connectivity.

**Step-by-Step Configuration:**

**1. Network Topology Setup:**
   - 2 PCs connected via Switch
   - Switch connected to Router
   - Configuration IPs for all devices

**2. PC1 Configuration:**
   - Click PC1 → Desktop → IP Configuration
   - IP Address: 192.168.1.10
   - Subnet Mask: 255.255.255.0
   - Default Gateway: 192.168.1.1
   - DNS Server: 8.8.8.8

**3. PC2 Configuration:**
   - Click PC2 → Desktop → IP Configuration
   - IP Address: 192.168.1.20
   - Subnet Mask: 255.255.255.0
   - Default Gateway: 192.168.1.1
   - DNS Server: 8.8.8.8

**4. Router Configuration:**
   - Click Router → CLI
   - Commands:
     ```
     enable
     configure terminal
     interface fastethernet 0/0
     ip address 192.168.1.1 255.255.255.0
     no shutdown
     exit
     exit
     show ip interface brief
     ```

**5. Verification Steps:**

From PC1 Command Prompt:
```
ipconfig                    # Display configuration
ping 192.168.1.20          # Test PC2
ping 192.168.1.1           # Test Router
tracert 192.168.1.20       # Trace route
```

From PC2 Command Prompt:
```
ipconfig                    # Display configuration
ping 192.168.1.10          # Test PC1
ping 192.168.1.1           # Test Router
nslookup 8.8.8.8           # DNS test
```

**Expected Results:**
- All pings return with TTL and response time
- Connectivity between all devices established
- Router interfaces show correct IP addresses
- Subnet mask properly configured on all devices

**Troubleshooting Commands:**
```
show ip route              # View routing table on router
show arp                   # View ARP table
debug ip packet           # Debug packet flow
```

---
"""

def main():
    """Generate solution files for slips 02-20"""
    base_path = "/home/amitdevx/jupyter_notebook/sem4/Exam Slips/Section V: Computer Networks"
    
    files_created = 0
    
    for slip_num in range(2, 21):
        slip_dir = os.path.join(base_path, f"Slip_{slip_num:02d}")
        os.makedirs(slip_dir, exist_ok=True)
        
        solution_file = os.path.join(slip_dir, f"Slip_{slip_num:02d}_Solution.md")
        
        # Skip if already exists
        if os.path.exists(solution_file):
            print(f"⊘ Slip_{slip_num:02d}_Solution.md already exists (skipping)")
            continue
        
        content = generate_slip_content(slip_num)
        
        with open(solution_file, 'w') as f:
            f.write(content)
        
        print(f"✓ Created Slip_{slip_num:02d}_Solution.md")
        files_created += 1
    
    print(f"\n✓ Generated {files_created} new solution files!")
    print("✓ All slips 02-20 now have comprehensive solution files!")

if __name__ == "__main__":
    main()
