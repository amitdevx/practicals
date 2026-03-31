# Slip 3 — Computer Networks Solution Guide

## Q1: Theory Questions (10 marks - Answer any 5)

---

### a) What does the command tracert or traceroute do?

**Definition:**
`traceroute` (Linux/Mac) or `tracert` (Windows) is a network diagnostic tool that traces the path packets take from source to destination.

**How It Works:**
| Step | TTL Value | Action |
|------|-----------|--------|
| 1 | TTL = 1 | First router decrements TTL to 0, sends ICMP "Time Exceeded" |
| 2 | TTL = 2 | Second router responds |
| 3 | TTL = n | Continues until destination reached |

**Output Information:**
- Hop number (sequence)
- Router IP address/hostname
- Round Trip Time (RTT) for each probe (usually 3 probes)

**Syntax:**
```bash
# Linux/Mac
traceroute www.google.com

# Windows
tracert www.google.com
```

**Sample Output:**
```
traceroute to google.com (142.250.183.46), 30 hops max
 1  192.168.1.1    1.234 ms   1.123 ms   1.089 ms
 2  10.0.0.1       5.432 ms   5.123 ms   5.234 ms
 3  72.14.215.85   15.234 ms  14.567 ms  14.890 ms
 4  142.250.183.46 20.123 ms  19.876 ms  20.234 ms
```

**Applications:**
1. Diagnose network connectivity issues
2. Identify network bottlenecks
3. Map network paths
4. Detect routing loops

---

### b) Differentiate between ip addr and ifconfig commands in Linux

| Feature | `ifconfig` | `ip addr` |
|---------|-----------|-----------|
| **Package** | net-tools (legacy) | iproute2 (modern) |
| **Status** | Deprecated | Current standard |
| **IPv6 Support** | Limited | Full support |
| **Syntax** | `ifconfig eth0` | `ip addr show eth0` |
| **Output Format** | Human-readable | Structured, scriptable |
| **Features** | Basic network config | Advanced routing, tunneling |
| **Performance** | Slower | Faster |

**Example Commands:**

```bash
# Show all interfaces
ifconfig -a              # Old way
ip addr show             # New way (or: ip a)

# Assign IP address
ifconfig eth0 192.168.1.10 netmask 255.255.255.0    # Old
ip addr add 192.168.1.10/24 dev eth0                 # New

# Enable/Disable interface
ifconfig eth0 up         # Old
ip link set eth0 up      # New

# Show specific interface
ifconfig eth0            # Old
ip addr show dev eth0    # New
```

**Key Differences:**
1. `ip` command is more powerful with consistent syntax
2. `ip` supports network namespaces
3. `ifconfig` may not be pre-installed on modern systems
4. `ip` provides more detailed information

---

### c) What does nslookup do?

**Definition:**
`nslookup` (Name Server Lookup) is a command-line tool for querying DNS (Domain Name System) to obtain domain name or IP address mapping.

**Primary Functions:**
| Function | Description |
|----------|-------------|
| Forward Lookup | Domain name → IP address |
| Reverse Lookup | IP address → Domain name |
| Query DNS Records | A, MX, NS, CNAME, TXT, etc. |

**Syntax:**
```bash
# Basic lookup
nslookup www.google.com

# Reverse lookup
nslookup 8.8.8.8

# Query specific DNS server
nslookup www.google.com 8.8.8.8

# Query specific record type
nslookup -type=MX gmail.com
```

**Sample Output:**
```
$ nslookup www.google.com
Server:     192.168.1.1
Address:    192.168.1.1#53

Non-authoritative answer:
Name:   www.google.com
Address: 142.250.183.68
```

**DNS Record Types:**
| Record | Purpose |
|--------|---------|
| A | IPv4 address |
| AAAA | IPv6 address |
| MX | Mail exchange server |
| NS | Name server |
| CNAME | Canonical name (alias) |
| TXT | Text records (SPF, etc.) |
| PTR | Pointer for reverse DNS |

**Applications:**
1. Troubleshoot DNS resolution problems
2. Verify DNS configuration
3. Check mail server records
4. Investigate domain information

---

### d) Two Advantages and Two Disadvantages of Dynamic IP Configuration

**Dynamic IP Configuration (DHCP):**
IP addresses are automatically assigned by a DHCP server rather than manually configured.

**Advantages:**

| Advantage | Explanation |
|-----------|-------------|
| **1. Simplified Administration** | No manual configuration needed. DHCP server automatically assigns IP, subnet mask, gateway, and DNS. Reduces human error. |
| **2. Efficient IP Utilization** | IPs are leased temporarily. When a device disconnects, its IP can be reassigned to another device. Ideal for large networks with many transient users. |

**Additional Advantages:**
- Centralized management of network settings
- Easy to change network configuration
- Prevents IP conflicts automatically

**Disadvantages:**

| Disadvantage | Explanation |
|--------------|-------------|
| **1. Dependency on DHCP Server** | If DHCP server fails, new devices cannot obtain IP addresses. Existing devices may lose connectivity when lease expires. |
| **2. Unsuitable for Servers** | Servers need consistent IPs for DNS records and client connections. Dynamic IPs change, breaking these services. |

**Additional Disadvantages:**
- Slight delay in obtaining IP address
- Less control over specific IP assignments
- Security concerns (rogue DHCP servers)

**When to Use:**
```
Dynamic IP: Workstations, laptops, mobile devices, guest networks
Static IP:  Servers, printers, routers, network infrastructure
```

---

### f) What is the function of a switch in a computer network?

**Definition:**
A switch is a Layer 2 (Data Link Layer) network device that connects multiple devices on a LAN and uses MAC addresses to forward data to the correct destination port.

**Key Functions:**

| Function | Description |
|----------|-------------|
| **Frame Forwarding** | Sends frames only to the intended recipient port |
| **MAC Learning** | Builds MAC address table from incoming frames |
| **Collision Domain Segmentation** | Each port is a separate collision domain |
| **Full-Duplex Communication** | Enables simultaneous send/receive |

**How a Switch Works:**

```
Step 1: Device A sends frame to switch
        Frame contains: Source MAC = AA:AA:AA:AA:AA:AA
                       Dest MAC = BB:BB:BB:BB:BB:BB

Step 2: Switch learns Source MAC on Port 1
        MAC Table: AA:AA:AA:AA:AA:AA → Port 1

Step 3: Switch looks up Destination MAC
        If found → Forward to specific port
        If not found → Flood to all ports (except source)

Step 4: When B replies, switch learns B's MAC
        MAC Table: BB:BB:BB:BB:BB:BB → Port 3
```

**Switch vs Hub:**

| Feature | Switch | Hub |
|---------|--------|-----|
| Layer | Layer 2 | Layer 1 |
| Intelligence | Smart (MAC-based) | Dumb (broadcasts all) |
| Collision Domain | Per port | Single shared |
| Bandwidth | Dedicated per port | Shared |
| Security | Better | Poor |

**Types of Switches:**
1. **Unmanaged Switch** - Plug and play, no configuration
2. **Managed Switch** - Configurable, VLANs, QoS support
3. **Layer 3 Switch** - Can perform routing functions

**Diagram:**
```
      [Switch MAC Table]
      MAC Address → Port
      ─────────────────
      AA:AA → Port 1
      BB:BB → Port 2
      CC:CC → Port 3

   [PC-A]     [PC-B]     [PC-C]
   Port 1     Port 2     Port 3
      │          │          │
      └────┬─────┴────┬─────┘
           │ [SWITCH] │
           └──────────┘
```

---

### g) What is network topology? What are its applications?

**Definition:**
Network topology refers to the arrangement or layout of different elements (nodes, links) in a computer network. It can be physical (actual layout) or logical (data flow pattern).

**Types of Network Topologies:**

| Topology | Description | Diagram |
|----------|-------------|---------|
| **Bus** | All devices share single cable | `─●─●─●─●─` |
| **Star** | All devices connect to central hub/switch | Hub at center |
| **Ring** | Devices form closed loop | `●─●─●─●─●` (circle) |
| **Mesh** | Every device connects to every other | Complex interconnections |
| **Tree** | Hierarchical combination of star | Root with branches |
| **Hybrid** | Combination of multiple topologies | Mixed |

**Comparison Table:**

| Topology | Cost | Reliability | Scalability | Complexity |
|----------|------|-------------|-------------|------------|
| Bus | Low | Low | Limited | Low |
| Star | Medium | Medium | Good | Medium |
| Ring | Medium | Medium | Limited | Medium |
| Mesh | High | High | Complex | High |
| Tree | Medium | Medium | Good | Medium |

**Applications:**

| Topology | Best Used In |
|----------|--------------|
| **Bus** | Small LANs, temporary networks, legacy Ethernet |
| **Star** | Office networks, home networks, most modern LANs |
| **Ring** | Token Ring networks, FDDI, some industrial networks |
| **Mesh** | WANs, Internet backbone, military networks, critical systems |
| **Tree** | Large organizations, campus networks, hierarchical structures |
| **Hybrid** | Enterprise networks, data centers |

**Factors for Choosing Topology:**
1. Cost and budget constraints
2. Network size and scalability needs
3. Fault tolerance requirements
4. Security considerations
5. Ease of installation and maintenance
6. Performance requirements

---

## Q2: Practical Questions (20 marks)

---

## Option A: Bus Topology Display Program

### Concept
Bus topology connects all devices to a single backbone cable. Data travels in both directions and all devices receive the data, but only the intended recipient processes it.

**Characteristics:**
- Single cable (backbone/trunk)
- Terminators at both ends to prevent signal reflection
- Devices use T-connectors to tap into bus
- CSMA/CD for collision handling

### Data Structure
```c
#define MAX_DEVICES 10
char devices[MAX_DEVICES][30];  // Device names
int device_count;               // Number of devices
```

### Algorithm
1. Accept number of devices from user
2. Accept name of each device
3. Display bus topology visualization:
   - Draw top boundary of bus
   - Draw connection points for each device
   - Draw device labels below
   - Draw terminators at both ends

### Pseudocode
```
FUNCTION displayBusTopology():
    INPUT number_of_devices
    FOR i = 0 TO number_of_devices - 1:
        INPUT device_name[i]
    
    PRINT "TERMINATOR"
    PRINT horizontal_bus_line with connection_points
    FOR each device:
        PRINT vertical_connector
    PRINT device_labels
    PRINT "TERMINATOR"
```

### Program: `Slip_03_Q2_OptionA.c`

---

## Option B: Even Parity Error Detection

### Concept
**Parity Check** is a simple error detection method that adds an extra bit (parity bit) to ensure the total number of 1s in the data is even (even parity) or odd (odd parity).

**Even Parity Rule:**
- Count number of 1s in data
- If count is odd → parity bit = 1
- If count is even → parity bit = 0
- Total 1s (data + parity) must be **even**

### Data Structure
```c
int data_bits[8];     // Original data bits
int parity_bit;       // Calculated parity bit
int received_bits[9]; // Data + parity for checking
```

### Algorithm

**Generating Parity Bit:**
```
1. Count number of 1s in data
2. If count is odd: parity_bit = 1
3. If count is even: parity_bit = 0
4. Append parity_bit to data
```

**Checking for Errors:**
```
1. Count total 1s in received data (including parity)
2. If count is even: No error detected
3. If count is odd: Error detected
```

### Pseudocode
```
FUNCTION generateEvenParity(data[], n):
    count = 0
    FOR i = 0 TO n-1:
        IF data[i] == 1:
            count = count + 1
    IF count MOD 2 == 1:
        RETURN 1
    ELSE:
        RETURN 0

FUNCTION checkEvenParity(data[], n):
    count = 0
    FOR i = 0 TO n-1:
        IF data[i] == 1:
            count = count + 1
    IF count MOD 2 == 0:
        PRINT "No error detected"
    ELSE:
        PRINT "Error detected!"
```

### Worked Example

**Generating Even Parity for Data: 1011001**
```
Data bits:    1  0  1  1  0  0  1
Count of 1s:  1     2  3        4  → 4 (even)
Parity bit:   0 (since count is already even)
Transmitted:  1  0  1  1  0  0  1  [0]
```

**Checking Received Data: 10110010 (No Error)**
```
Received:     1  0  1  1  0  0  1  0
Count of 1s:  1     2  3        4     → 4 (even)
Result:       NO ERROR (even count)
```

**Checking Received Data: 10110110 (With Error)**
```
Received:     1  0  1  1  0  1  1  0
Count of 1s:  1     2  3     4  5     → 5 (odd)
Result:       ERROR DETECTED (odd count)
```

### Limitations
| Limitation | Explanation |
|------------|-------------|
| Single-bit errors only | Detects odd number of bit errors |
| No error correction | Can only detect, not fix errors |
| Even-bit errors missed | 2-bit errors go undetected |

### Program: `Slip_03_Q2_OptionB.c`

---

## Option C: Packet Tracer Configuration

### CIDR Values for IP Address Classes

**CIDR (Classless Inter-Domain Routing)** notation specifies network prefix length.

| Class | Default Subnet Mask | CIDR Notation | Network Bits | Host Bits | Usable Hosts |
|-------|---------------------|---------------|--------------|-----------|--------------|
| **A** | 255.0.0.0 | /8 | 8 | 24 | 16,777,214 |
| **B** | 255.255.0.0 | /16 | 16 | 16 | 65,534 |
| **C** | 255.255.255.0 | /24 | 24 | 8 | 254 |

**Class A Example:**
```
IP: 10.0.0.0/8
Network:   10.0.0.0
Broadcast: 10.255.255.255
Range:     10.0.0.1 - 10.255.255.254
Hosts:     2^24 - 2 = 16,777,214
```

**Class C Example:**
```
IP: 192.168.1.0/24
Network:   192.168.1.0
Broadcast: 192.168.1.255
Range:     192.168.1.1 - 192.168.1.254
Hosts:     2^8 - 2 = 254
```

### Network Diagram

```
                    ROUTER 2911
                   ┌──────────┐
                   │          │
         G0/0      │          │      G0/1
      10.0.0.4/8   │          │   192.168.1.4/24
           ┌──────┤          ├──────┐
           │      └──────────┘      │
           │                        │
      ┌────┴────┐              ┌────┴────┐
      │ SWITCH 1│              │ SWITCH 2│
      └────┬────┘              └────┬────┘
        ┌──┼──┐                  ┌──┼──┐
        │  │  │                  │  │  │
      PC1 PC2 PC3              PC4 PC5 PC6
      
   LAN 1: 10.0.0.0/8       LAN 2: 192.168.1.0/24
```

### IP Address Configuration

**LAN 1 (Class A Network: 10.0.0.0/8)**

| Device | IP Address | Subnet Mask | Default Gateway |
|--------|------------|-------------|-----------------|
| PC1 | 10.0.0.1 | 255.0.0.0 | 10.0.0.4 |
| PC2 | 10.0.0.2 | 255.0.0.0 | 10.0.0.4 |
| PC3 | 10.0.0.3 | 255.0.0.0 | 10.0.0.4 |
| Router G0/0 | 10.0.0.4 | 255.0.0.0 | - |

**LAN 2 (Class C Network: 192.168.1.0/24)**

| Device | IP Address | Subnet Mask | Default Gateway |
|--------|------------|-------------|-----------------|
| PC4 | 192.168.1.1 | 255.255.255.0 | 192.168.1.4 |
| PC5 | 192.168.1.2 | 255.255.255.0 | 192.168.1.4 |
| PC6 | 192.168.1.3 | 255.255.255.0 | 192.168.1.4 |
| Router G0/1 | 192.168.1.4 | 255.255.255.0 | - |

### Packet Tracer Configuration Steps

**Step 1: Add Devices**
```
1. Drag Router 2911 to workspace
2. Drag 2 Switches (2960) to workspace
3. Drag 6 PCs (3 for each LAN)
```

**Step 2: Connect Devices**
```
Use Copper Straight-Through cables:
- Switch1 to Router G0/0
- Switch2 to Router G0/1
- PC1, PC2, PC3 to Switch1
- PC4, PC5, PC6 to Switch2
```

**Step 3: Configure Router**
```
Router> enable
Router# configure terminal

! Configure G0/0 for LAN 1
Router(config)# interface GigabitEthernet0/0
Router(config-if)# ip address 10.0.0.4 255.0.0.0
Router(config-if)# no shutdown
Router(config-if)# exit

! Configure G0/1 for LAN 2
Router(config)# interface GigabitEthernet0/1
Router(config-if)# ip address 192.168.1.4 255.255.255.0
Router(config-if)# no shutdown
Router(config-if)# exit
Router(config)# exit
Router# write memory
```

**Step 4: Configure PCs**

For PC1 (and similarly PC2, PC3):
```
Desktop → IP Configuration
IP Address:      10.0.0.1
Subnet Mask:     255.0.0.0
Default Gateway: 10.0.0.4
```

For PC4 (and similarly PC5, PC6):
```
Desktop → IP Configuration
IP Address:      192.168.1.1
Subnet Mask:     255.255.255.0
Default Gateway: 192.168.1.4
```

**Step 5: Verify Connectivity**

```bash
# From PC1 - Test local connectivity
ping 10.0.0.2
ping 10.0.0.3
ping 10.0.0.4

# From PC1 - Test inter-LAN connectivity
ping 192.168.1.1
ping 192.168.1.4

# From Router - Test both interfaces
Router# ping 10.0.0.1
Router# ping 192.168.1.1
```

### Expected Results
```
C:\> ping 192.168.1.1

Pinging 192.168.1.1 with 32 bytes of data:

Reply from 192.168.1.1: bytes=32 time<1ms TTL=127
Reply from 192.168.1.1: bytes=32 time<1ms TTL=127
Reply from 192.168.1.1: bytes=32 time<1ms TTL=127
Reply from 192.168.1.1: bytes=32 time<1ms TTL=127

Ping statistics for 192.168.1.1:
    Packets: Sent = 4, Received = 4, Lost = 0 (0% loss)
```

---

## Summary Table

| Question | Topic | Key Points |
|----------|-------|------------|
| Q1a | traceroute | Traces packet path, shows hops and RTT |
| Q1b | ip addr vs ifconfig | Modern vs legacy, ip is preferred |
| Q1c | nslookup | DNS query tool for name resolution |
| Q1d | Dynamic IP | DHCP pros/cons, server dependency |
| Q1f | Switch | Layer 2, MAC learning, frame forwarding |
| Q1g | Topology | Physical/logical layout, types and uses |
| Q2A | Bus Topology | Single backbone, all devices share cable |
| Q2B | Even Parity | Error detection using parity bit |
| Q2C | Packet Tracer | Router connecting two LANs, CIDR |

---

## Quick Revision Points

1. **traceroute** uses TTL manipulation to discover path
2. **ip addr** is the modern replacement for ifconfig
3. **nslookup** queries DNS for domain/IP mapping
4. **Dynamic IP** simplifies management but creates dependencies
5. **Switch** uses MAC table for intelligent forwarding
6. **Topology** defines network physical/logical structure
7. **Even Parity** detects odd number of bit errors
8. **CIDR /8** = Class A, **/16** = Class B, **/24** = Class C
