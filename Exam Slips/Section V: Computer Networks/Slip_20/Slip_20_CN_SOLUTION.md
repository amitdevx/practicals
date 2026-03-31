# Slip 20 — Computer Networks Solution Guide

## Q1: Theory Questions (10 Marks - Answer ANY 5)

---

### a) What is the primary purpose of a banner MOTD?

#### Concept
A **Banner MOTD (Message of the Day)** is a text message displayed to users when they connect to a network device (router, switch, server) via console, Telnet, or SSH.

#### Primary Purposes

1. **Legal Warning/Disclaimer**: Warns unauthorized users about legal consequences of unauthorized access
2. **Usage Policy Notice**: Informs users about acceptable use policies
3. **Identification**: Identifies the device or system being accessed
4. **Security Deterrent**: Discourages hackers by displaying warnings
5. **Administrative Information**: Communicates system status, maintenance schedules

#### Why MOTD is Important
```
+---------------------------------------------------------+
|  AUTHORIZED ACCESS ONLY!                                |
|  This system is for authorized users only.              |
|  All activities are monitored and logged.               |
|  Unauthorized access will be prosecuted.                |
+---------------------------------------------------------+
```

#### Cisco Router MOTD Configuration
```
Router> enable
Router# configure terminal
Router(config)# banner motd #
Enter TEXT message. End with the character '#'.
WARNING: Unauthorized access is prohibited!
All connections are monitored and logged.
#
Router(config)# exit
```

#### Key Points
| Aspect | Description |
|--------|-------------|
| **Legal Protection** | Provides evidence of warning in case of prosecution |
| **Compliance** | Required for many security standards (PCI-DSS, HIPAA) |
| **Displayed** | Shown BEFORE login prompt appears |
| **Delimiter** | Uses special character (#, %) to mark start/end |

---

### b) How many hexadecimal digits are needed for a 64-bit WEP key? Give any 5 examples

#### Concept
**WEP (Wired Equivalent Privacy)** is an older wireless security protocol that uses hexadecimal keys for encryption.

#### Calculation
```
1 hexadecimal digit = 4 bits
64-bit WEP key = 64 / 4 = 16 hexadecimal digits

However, WEP actually uses:
- 64-bit WEP = 40-bit actual key + 24-bit IV (Initialization Vector)
- For the key portion: 40 / 4 = 10 hex digits
```

#### Standard 64-bit WEP Key
- **10 hexadecimal digits** (for the 40-bit secret key)
- Valid characters: 0-9 and A-F

#### 5 Examples of 64-bit WEP Keys
| # | WEP Key (10 hex digits) | Description |
|---|-------------------------|-------------|
| 1 | `1234567890` | Numeric only |
| 2 | `ABCDEF1234` | Mixed alphanumeric |
| 3 | `A1B2C3D4E5` | Alternating pattern |
| 4 | `FF00FF00FF` | Repeating pattern |
| 5 | `1A2B3C4D5E` | Sequential pattern |

#### WEP Key Types Comparison
| WEP Type | Actual Key | IV | Total Bits | Hex Digits Needed |
|----------|------------|-----|------------|-------------------|
| 64-bit | 40-bit | 24-bit | 64-bit | **10 hex digits** |
| 128-bit | 104-bit | 24-bit | 128-bit | **26 hex digits** |
| 256-bit | 232-bit | 24-bit | 256-bit | **58 hex digits** |

#### Important Notes
- WEP is **deprecated** due to serious security vulnerabilities
- Modern networks use **WPA2** or **WPA3** instead
- 64-bit WEP can be cracked in minutes with modern tools

---

### c) List types of Cyber Threats. Describe any two.

#### Types of Cyber Threats

| Category | Examples |
|----------|----------|
| **Malware** | Viruses, Worms, Trojans, Ransomware, Spyware |
| **Network Attacks** | DDoS, Man-in-the-Middle, Packet Sniffing |
| **Social Engineering** | Phishing, Pretexting, Baiting, Tailgating |
| **Authentication Attacks** | Brute Force, Dictionary Attack, Credential Stuffing |
| **Injection Attacks** | SQL Injection, XSS, Command Injection |
| **Advanced Threats** | APT, Zero-day Exploits, Rootkits |

---

#### Threat 1: Phishing Attack

**Definition**: A social engineering attack where attackers impersonate legitimate entities to steal sensitive information like passwords, credit card numbers, or personal data.

**How It Works**:
```
1. Attacker creates fake website/email resembling legitimate source
2. Victim receives email/message with malicious link
3. Victim clicks link and enters credentials
4. Attacker captures the credentials
5. Attacker uses credentials for malicious purposes
```

**Types of Phishing**:
| Type | Description |
|------|-------------|
| Email Phishing | Mass emails impersonating banks, services |
| Spear Phishing | Targeted attack on specific individuals |
| Whaling | Targets high-level executives (CEO, CFO) |
| Smishing | Phishing via SMS messages |
| Vishing | Phishing via voice calls |

**Prevention**:
- Verify sender email addresses
- Don't click suspicious links
- Use multi-factor authentication
- Check URL before entering credentials

---

#### Threat 2: Distributed Denial of Service (DDoS) Attack

**Definition**: An attack that overwhelms a target server, network, or service with massive amounts of traffic from multiple distributed sources, making it unavailable to legitimate users.

**How It Works**:
```
                    [Attacker]
                         |
                    [C&C Server]
                    /    |    \
           [Bot1]  [Bot2]  [Bot3]  ... [BotN]
               \     |      |       /
                v    v      v      v
               +-----------------+
               |   Target Server |
               |   (Overwhelmed) |
               +-----------------+
```

**Types of DDoS Attacks**:
| Type | Layer | Method |
|------|-------|--------|
| Volumetric | Network (L3) | UDP Flood, ICMP Flood |
| Protocol | Transport (L4) | SYN Flood, Ping of Death |
| Application | Application (L7) | HTTP Flood, Slowloris |

**Attack Characteristics**:
- Uses botnets (thousands of compromised computers)
- Traffic volume can exceed 100 Gbps
- Difficult to distinguish from legitimate traffic
- Can last hours to days

**Prevention**:
- Use DDoS protection services (Cloudflare, AWS Shield)
- Implement rate limiting
- Configure firewalls and IPS
- Have redundant network resources
- Develop incident response plan

---

### d) Differentiate between Static and Dynamic routing.

#### Concept
**Routing** is the process of selecting paths in a network for sending traffic. It can be configured manually (static) or automatically (dynamic).

#### Comparison Table

| Feature | Static Routing | Dynamic Routing |
|---------|---------------|-----------------|
| **Configuration** | Manually configured by admin | Automatically learned via protocols |
| **Adaptability** | Does not adapt to changes | Adapts to network changes |
| **Protocols** | None (manual entries) | RIP, OSPF, EIGRP, BGP |
| **CPU/Memory** | Low overhead | Higher resource usage |
| **Bandwidth** | No protocol overhead | Uses bandwidth for updates |
| **Scalability** | Poor (impractical for large networks) | Excellent (handles large networks) |
| **Security** | More secure (no advertisements) | Less secure (route announcements) |
| **Complexity** | Simple to implement | More complex setup |
| **Convergence** | Instant (no convergence needed) | Takes time to converge |
| **Admin Effort** | High maintenance | Low maintenance |
| **Use Case** | Small networks, stub networks | Medium to large networks |

#### Static Routing
```
Router(config)# ip route 192.168.2.0 255.255.255.0 10.0.0.2
                         [dest network]  [mask]    [next-hop]
```

**Advantages**:
- Predictable path selection
- No routing protocol overhead
- Enhanced security
- No bandwidth consumed by routing updates

**Disadvantages**:
- Manual configuration required for every route
- Does not adapt to link failures
- Administrative burden increases with network size

#### Dynamic Routing
```
Router(config)# router ospf 1
Router(config-router)# network 192.168.1.0 0.0.0.255 area 0
Router(config-router)# network 192.168.2.0 0.0.0.255 area 0
```

**Advantages**:
- Automatic route discovery
- Adapts to topology changes
- Easier to manage large networks
- Provides redundancy and load balancing

**Disadvantages**:
- Consumes CPU, memory, and bandwidth
- More complex to configure and troubleshoot
- Security vulnerabilities (route poisoning)

#### Visual Comparison
```
STATIC ROUTING:                    DYNAMIC ROUTING:
                                   
Admin manually configures          Routers exchange routing
each route                         information automatically
                                   
[R1]----[R2]----[R3]              [R1]<==[R2]<==[R3]
  |       |       |                  ↑      ↑      ↑
  Admin   Admin   Admin              OSPF exchanges updates
  adds    adds    adds               automatically
  routes  routes  routes
```

---

### f) What is the function of a switch in a computer network?

#### Concept
A **Network Switch** is a Layer 2 (Data Link Layer) device that connects devices within a Local Area Network (LAN) and forwards data frames based on MAC addresses.

#### Primary Functions

| Function | Description |
|----------|-------------|
| **Frame Forwarding** | Forwards frames to specific ports based on MAC address |
| **MAC Address Learning** | Builds and maintains MAC address table |
| **Loop Prevention** | Uses STP to prevent broadcast storms |
| **Collision Domain Separation** | Each port is separate collision domain |
| **Bandwidth Optimization** | Dedicated bandwidth per port |

#### How a Switch Works
```
Step 1: Frame arrives at port
         │
Step 2: Switch reads source MAC address
         │
Step 3: Adds source MAC to MAC table with port number
         │
Step 4: Switch reads destination MAC address
         │
Step 5: Looks up destination MAC in MAC table
         │
Step 6a: If found → Forward to specific port
Step 6b: If not found → Flood to all ports (except source)
```

#### Switch vs Hub Comparison

| Feature | Switch | Hub |
|---------|--------|-----|
| **Layer** | Layer 2 (Data Link) | Layer 1 (Physical) |
| **Intelligence** | Uses MAC addresses | No intelligence |
| **Forwarding** | To specific port | To all ports |
| **Collision Domain** | Per-port (no collisions) | Single shared |
| **Bandwidth** | Dedicated per port | Shared |
| **Efficiency** | High | Low |

#### MAC Address Table Example
```
MAC Address Table
----------------------------
VLAN    MAC Address       Port
----    -----------       ----
1       AA:BB:CC:DD:EE:01  Fa0/1
1       AA:BB:CC:DD:EE:02  Fa0/2
1       AA:BB:CC:DD:EE:03  Fa0/3
1       AA:BB:CC:DD:EE:04  Fa0/4
```

#### Types of Switches
| Type | Description |
|------|-------------|
| **Unmanaged** | Plug-and-play, no configuration needed |
| **Managed** | Full configuration, VLANs, SNMP support |
| **Smart/Web-managed** | Limited management via web interface |
| **PoE Switch** | Power over Ethernet support |
| **Layer 3 Switch** | Routing capability (multilayer) |

#### View MAC Table Command (Cisco)
```
Switch# show mac address-table
```

---

### g) Describe any two network topologies.

#### Network Topology
**Network Topology** is the arrangement of nodes (computers, switches, routers) and connections in a network. It can be physical (actual layout) or logical (data flow path).

---

#### Topology 1: Star Topology

**Description**: All devices connect to a central hub or switch. All communication passes through this central device.

```
           [PC1]
             |
    [PC2]----[SWITCH]----[PC3]
             |
           [PC4]
```

**Characteristics**:
| Aspect | Description |
|--------|-------------|
| **Central Device** | Hub or Switch |
| **Connections** | Point-to-point from each node to center |
| **Failure Impact** | Central device failure affects entire network |
| **Scalability** | Easy to add/remove devices |

**Advantages**:
- Easy to install and configure
- Easy to troubleshoot (isolate faulty node)
- Single node failure doesn't affect others
- Centralized management
- Good performance (dedicated connection)

**Disadvantages**:
- Single point of failure (central device)
- Requires more cabling than bus topology
- Central device cost can be high
- Limited by central device port count

**Use Cases**:
- Home networks
- Small office networks
- Most modern LANs

---

#### Topology 2: Mesh Topology

**Description**: Every device connects to every other device in the network. Provides maximum redundancy and fault tolerance.

**Full Mesh**:
```
    [PC1]-------[PC2]
      |\         /|
      | \       / |
      |  \     /  |
      |   \   /   |
      |    \ /    |
      |     X     |
      |    / \    |
      |   /   \   |
      |  /     \  |
      | /       \ |
      |/         \|
    [PC4]-------[PC3]
```

**Characteristics**:
| Aspect | Description |
|--------|-------------|
| **Connections** | n(n-1)/2 links for n nodes (full mesh) |
| **Redundancy** | Multiple paths between nodes |
| **Failure Impact** | Network continues with node/link failure |
| **Cost** | High (many connections needed) |

**Formula for Full Mesh**:
```
Number of connections = n(n-1)/2

For 4 nodes: 4(4-1)/2 = 6 connections
For 5 nodes: 5(5-1)/2 = 10 connections
For 10 nodes: 10(10-1)/2 = 45 connections
```

**Advantages**:
- High fault tolerance and reliability
- No traffic congestion (multiple paths)
- Easy to identify and isolate faults
- Data can be transmitted simultaneously
- Privacy/security (dedicated links)

**Disadvantages**:
- Very expensive (cabling and ports)
- Complex installation and configuration
- Difficult to manage as network grows
- Redundant connections may be underutilized

**Use Cases**:
- Backbone networks (partial mesh)
- WANs connecting major sites
- Military and critical infrastructure
- Data centers (between core switches)

---

#### Topology Comparison Summary

| Topology | Cost | Redundancy | Scalability | Complexity |
|----------|------|------------|-------------|------------|
| Star | Medium | Low | High | Low |
| Mesh | High | High | Low | High |
| Bus | Low | None | Low | Low |
| Ring | Medium | Medium | Medium | Medium |
| Tree | Medium | Low | High | Medium |

---

## Q2: Practical Questions (20 Marks)

---

## Option A: Mesh Topology Representation in C

### Concept
Mesh topology connects every device to every other device. We can represent this using:
1. **Adjacency Matrix**: 2D array where matrix[i][j] = 1 if node i connects to node j
2. **Connection Count**: Full mesh with n nodes has n(n-1)/2 connections

### Algorithm
```
FUNCTION createMeshTopology(n):
    // Create n×n adjacency matrix
    FOR i = 0 to n-1:
        FOR j = 0 to n-1:
            IF i != j:
                matrix[i][j] = 1  // Connected
            ELSE:
                matrix[i][j] = 0  // No self-loop
    
    // Calculate total connections
    connections = n * (n - 1) / 2
    
    RETURN matrix, connections

FUNCTION displayTopology(matrix, n):
    PRINT "Adjacency Matrix:"
    FOR each row in matrix:
        PRINT row values
    
    PRINT "Connections:"
    FOR i = 0 to n-1:
        FOR j = i+1 to n-1:
            PRINT "Node i <--> Node j"
```

### Time & Space Complexity
| Operation | Time | Space |
|-----------|------|-------|
| Create Mesh | O(n²) | O(n²) |
| Display | O(n²) | O(1) |
| Total Connections | O(1) | O(1) |

### Worked Example
```
For 4 nodes (PC0, PC1, PC2, PC3):

Adjacency Matrix:
     PC0  PC1  PC2  PC3
PC0   0    1    1    1
PC1   1    0    1    1
PC2   1    1    0    1
PC3   1    1    1    0

Total Connections = 4 × 3 / 2 = 6

Connections:
PC0 <--> PC1
PC0 <--> PC2
PC0 <--> PC3
PC1 <--> PC2
PC1 <--> PC3
PC2 <--> PC3
```

---

## Option B: Hash Simulation in C

### Concept
**Hashing** is a technique to map data of arbitrary size to fixed-size values. A **Hash Table** uses a hash function to compute an index for storing/retrieving data.

### Hash Function
```
hash(key) = key % TABLE_SIZE
```

### Collision Resolution Methods
1. **Chaining**: Use linked list at each index
2. **Linear Probing**: Find next available slot
3. **Quadratic Probing**: Find slot using quadratic function
4. **Double Hashing**: Use second hash function

### Algorithm (Linear Probing)
```
FUNCTION insert(table, key):
    index = hash(key)
    original_index = index
    
    WHILE table[index] is not empty:
        index = (index + 1) % TABLE_SIZE
        IF index == original_index:
            PRINT "Table is full"
            RETURN
    
    table[index] = key

FUNCTION search(table, key):
    index = hash(key)
    original_index = index
    
    WHILE table[index] != key:
        IF table[index] is empty:
            RETURN -1  // Not found
        index = (index + 1) % TABLE_SIZE
        IF index == original_index:
            RETURN -1  // Not found (full cycle)
    
    RETURN index
```

### Time & Space Complexity
| Operation | Average | Worst Case |
|-----------|---------|------------|
| Insert | O(1) | O(n) |
| Search | O(1) | O(n) |
| Delete | O(1) | O(n) |
| Space | O(n) | O(n) |

### Worked Example
```
Table Size = 10
Keys to insert: 25, 35, 45, 15, 55

hash(25) = 25 % 10 = 5 → table[5] = 25
hash(35) = 35 % 10 = 5 → collision! → table[6] = 35
hash(45) = 45 % 10 = 5 → collision! → table[7] = 45
hash(15) = 15 % 10 = 5 → collision! → table[8] = 15
hash(55) = 55 % 10 = 5 → collision! → table[9] = 55

Final Table:
Index:  0  1  2  3  4  5   6   7   8   9
Value: -  -  -  -  -  25  35  45  15  55
```

---

## Option C: Mesh Topology in Packet Tracer

### Given Information
- **4 PCs**: PC0, PC1, PC2, PC3
- **IP Range**: 172.16.1.1 to 172.16.1.4
- **Subnet Mask**: 255.255.0.0 (/16)

### PC Configuration Table

| Device | Interface | IP Address | Subnet Mask | Gateway |
|--------|-----------|------------|-------------|---------|
| PC0 | Fa0 | 172.16.1.1 | 255.255.0.0 | - |
| PC1 | Fa0 | 172.16.1.2 | 255.255.0.0 | - |
| PC2 | Fa0 | 172.16.1.3 | 255.255.0.0 | - |
| PC3 | Fa0 | 172.16.1.4 | 255.255.0.0 | - |

### Packet Tracer Steps

#### Step 1: Add Devices
1. Open Cisco Packet Tracer
2. Add 4 PCs from End Devices
3. Add a Switch (2960) from Network Devices

**Note**: True mesh topology requires multiple NICs per PC. For simulation, we use a switch-based star topology that logically behaves like a mesh at Layer 3.

#### Step 2: Connect Devices
```
PC0 --[Copper Straight-Through]--> Switch Fa0/1
PC1 --[Copper Straight-Through]--> Switch Fa0/2
PC2 --[Copper Straight-Through]--> Switch Fa0/3
PC3 --[Copper Straight-Through]--> Switch Fa0/4
```

#### Step 3: Configure IP Addresses

**PC0 Configuration**:
1. Click PC0 → Desktop → IP Configuration
2. Select Static
3. IP Address: `172.16.1.1`
4. Subnet Mask: `255.255.0.0`

**PC1 Configuration**:
1. Click PC1 → Desktop → IP Configuration
2. IP Address: `172.16.1.2`
3. Subnet Mask: `255.255.0.0`

**PC2 Configuration**:
1. Click PC2 → Desktop → IP Configuration
2. IP Address: `172.16.1.3`
3. Subnet Mask: `255.255.0.0`

**PC3 Configuration**:
1. Click PC3 → Desktop → IP Configuration
2. IP Address: `172.16.1.4`
3. Subnet Mask: `255.255.0.0`

#### Step 4: Verify Connectivity

From PC0 Command Prompt:
```
C:\> ping 172.16.1.2
C:\> ping 172.16.1.3
C:\> ping 172.16.1.4
```

Expected output for each:
```
Pinging 172.16.1.2 with 32 bytes of data:
Reply from 172.16.1.2: bytes=32 time<1ms TTL=128
Reply from 172.16.1.2: bytes=32 time<1ms TTL=128
Reply from 172.16.1.2: bytes=32 time<1ms TTL=128
Reply from 172.16.1.2: bytes=32 time<1ms TTL=128

Ping statistics for 172.16.1.2:
    Packets: Sent = 4, Received = 4, Lost = 0 (0% loss)
```

### True Mesh Topology Implementation

For actual mesh topology with direct connections:

```
Required NICs per PC: 3 (to connect to other 3 PCs)

Connections (6 total):
PC0-Fa0 <--> PC1-Fa0
PC0-Fa1 <--> PC2-Fa0  
PC0-Fa2 <--> PC3-Fa0
PC1-Fa1 <--> PC2-Fa1
PC1-Fa2 <--> PC3-Fa1
PC2-Fa2 <--> PC3-Fa2
```

### Network Diagram
```
                    172.16.1.1
                      [PC0]
                     /  |  \
                    /   |   \
                   /    |    \
          172.16.1.2    |     172.16.1.4
            [PC1]-------|-------[PC3]
                \       |       /
                 \      |      /
                  \     |     /
                   172.16.1.3
                     [PC2]
```

### Subnetting Information
```
Network Address: 172.16.0.0
Subnet Mask: 255.255.0.0 (/16)
Network Class: Class B (Private)
Usable Host Range: 172.16.0.1 - 172.16.255.254
Broadcast Address: 172.16.255.255
Total Usable Hosts: 65,534
```

---

> **Solution Code:** See `Slip_20_Q2_OptionA.c` (Mesh Topology) and `Slip_20_Q2_OptionB.c` (Hash Simulation) in this folder.
