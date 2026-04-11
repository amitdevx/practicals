# Slip 5 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) Explain the OSI Model with 7 layers.

**OSI (Open Systems Interconnection) Model** is a conceptual framework that standardizes network communication into 7 layers, each with specific functions.

**7 OSI Layers:**

| Layer | Name | Function | Examples |
|-------|------|----------|----------|
| **7** | Application | User services, applications | HTTP, SMTP, FTP, DNS, SSH |
| **6** | Presentation | Data encryption, compression, formatting | SSL/TLS, JPEG, MPEG, ASCII |
| **5** | Session | Session management, dialog control | NetBIOS, NFS, RPC |
| **4** | Transport | End-to-end communication, reliability | TCP, UDP, SCTP |
| **3** | Network | Routing, IP addressing | IP, ICMP, IGMP, Routing protocols |
| **2** | Data Link | MAC addressing, frame delivery | Ethernet, PPP, WiFi, MAC |
| **1** | Physical | Physical transmission, cables, signals | USB, Ethernet cable, Fiber optic |

**Layer Responsibilities:**

**Layer 7 - Application:**
- User interface and applications
- Web browsers, email, file transfer
- User authentication and data privacy

**Layer 6 - Presentation:**
- Data formatting and encryption
- Compression algorithms
- Character encoding (ASCII, Unicode)

**Layer 5 - Session:**
- Establish, maintain, terminate connections
- Manages dialogs between hosts
- Synchronization and flow control

**Layer 4 - Transport:**
- Reliable data delivery (TCP)
- Connectionless delivery (UDP)
- Error checking and sequencing

**Layer 3 - Network:**
- Logical addressing (IP addresses)
- Routing decisions
- Determines best path to destination

**Layer 2 - Data Link:**
- Physical addressing (MAC addresses)
- Error detection at frame level
- Media access control

**Layer 1 - Physical:**
- Actual transmission of raw bits
- Cables, connectors, signal levels
- Voltage, frequency specifications

---

### b) What is a MAC address and how is it different from an IP address?

**MAC Address (Media Access Control):**
- Unique hardware identifier (48 bits)
- Format: XX:XX:XX:XX:XX:XX (hexadecimal)
- First 3 octets: Manufacturer ID (OUI)
- Last 3 octets: Device-specific
- Physical/permanent address (can be spoofed)
- Operates at Layer 2 (Data Link)
- Used for local network communication
- Example: 00:1A:2B:3C:4D:5E

**IP Address (Internet Protocol):**
- Logical network address (32 bits IPv4, 128 bits IPv6)
- Format: XXX.XXX.XXX.XXX (dotted decimal)
- Assigned by network administrator or DHCP
- Can be changed dynamically
- Logical/software address
- Operates at Layer 3 (Network)
- Used for routing across networks
- Example: 192.168.1.100

**Key Differences:**

| Aspect | MAC Address | IP Address |
|--------|-------------|-----------|
| **Layer** | L2 (Data Link) | L3 (Network) |
| **Type** | Physical/Hardware | Logical/Software |
| **Assignment** | Manufacturer | Network Admin/DHCP |
| **Scope** | Local network only | Global (routable) |
| **Uniqueness** | Globally unique | Unique within network |
| **Format** | 48-bit (hex) | 32-bit IPv4 / 128-bit IPv6 |
| **Changeability** | Permanent (spoofable) | Dynamic/Changeable |
| **Range** | Local | Entire Internet |
| **Purpose** | Local delivery | Inter-network routing |

---

### c) Provide subnetting examples with calculations.

**Subnetting** divides a network into smaller sub-networks by using some host bits as network bits.

**Example 1: Class C Network Subnetting**

**Given:** 192.168.1.0/24 (Original network)
**Requirement:** Divide into 4 subnets (/26)

**Calculation:**
- Original: /24 (8 host bits)
- Need 4 subnets: 2^2 = 4 subnets
- Borrow 2 bits: /24 + 2 = /26
- Host bits remaining: 6 bits = 2^6 = 64 addresses per subnet
- Usable hosts: 64 - 2 = 62

**Subnet Table:**

| Subnet | Network | First Host | Last Host | Broadcast |
|--------|---------|-----------|-----------|-----------|
| 1 | 192.168.1.0/26 | 192.168.1.1 | 192.168.1.62 | 192.168.1.63 |
| 2 | 192.168.1.64/26 | 192.168.1.65 | 192.168.1.126 | 192.168.1.127 |
| 3 | 192.168.1.128/26 | 192.168.1.129 | 192.168.1.190 | 192.168.1.191 |
| 4 | 192.168.1.192/26 | 192.168.1.193 | 192.168.1.254 | 192.168.1.255 |

**Example 2: Class B Network Variable-Length Subnetting**

**Given:** 172.16.0.0/16
**Requirement:** Different subnet sizes

- Subnet A: 100 hosts → /25 (126 hosts)
- Subnet B: 50 hosts → /26 (62 hosts)
- Subnet C: 200 hosts → /24 (254 hosts)

**Allocation:**
```
172.16.0.0/24     (Subnet A - 172.16.0.0 to 172.16.0.255)
172.16.1.0/25     (Subnet B - 172.16.1.0 to 172.16.1.127)
172.16.1.128/26   (Subnet C - 172.16.1.128 to 172.16.1.191)
```

---

### d) What is a firewall? How does it protect networks?

**Firewall** is a network security device/software that monitors and controls incoming and outgoing network traffic based on predetermined security rules.

**How Firewalls Protect:**

1. **Packet Filtering**
   - Examines packet headers (source/destination IP, port)
   - Allows or blocks based on rules
   - Stateless or stateful inspection

2. **Access Control**
   - Blocks unauthorized access
   - Allows only approved traffic
   - Implements security policies

3. **Network Segmentation**
   - Separates internal from external networks
   - Creates DMZs for public services
   - Limits lateral movement

4. **Intrusion Prevention**
   - Detects attack patterns
   - Blocks suspicious traffic
   - Prevents known exploits

5. **VPN Support**
   - Encrypts remote connections
   - Authenticates users
   - Secure data transmission

**Types of Firewalls:**

- **Packet-filtering**: Checks headers
- **Stateful**: Tracks connection states
- **Application gateway**: Inspects application data
- **Next-Gen**: ML-based threat detection

---

### f) What is network simulation?

**Network Simulation** is creating a virtual model of a network to test, analyze, and troubleshoot network behavior without affecting real networks.

**Purpose:**
- Test configurations safely
- Design before implementation
- Understand network behavior
- Train network administrators

**Tools:** Cisco Packet Tracer, GNS3, Mininet

---

### g) What is ICMP? What are ICMP message types?

**ICMP (Internet Control Message Protocol):**
- Network layer protocol for error reporting
- Used for ping and traceroute
- Diagnostic and control messages
- Unreliable (no guaranteed delivery)

**Common ICMP Types:**
- Type 0: Echo Reply
- Type 3: Destination Unreachable
- Type 8: Echo Request
- Type 11: Time Exceeded

---

## Q2: Practical Questions (20 Marks)

### OPTION A: Star Topology

Star topology connects all devices to a central hub or switch.

**Characteristics:**
- All devices connected to central device
- Hub/switch at center
- Point-to-point links to center
- Break in one link doesn't affect others
- Central device is single point of failure

**Advantages:**
- Easy to add/remove nodes
- Good fault isolation
- Centralized management
- Higher performance

**Disadvantages:**
- Central device failure breaks network
- Higher cabling cost
- More complex than bus

---

### OPTION B: Mesh Topology

Full mesh topology connects every device to every other device.

**Characteristics:**
- Multiple paths between devices
- Excellent fault tolerance
- High redundancy
- Complex and expensive

---

