# Slip 12 — Computer Networks Solution Guide

## Q1: Theory Questions (Any 5) — 10 Marks

---

### a) What is the function of a switch in a computer network?

#### Concept
A **switch** is a Layer 2 (Data Link Layer) network device that connects multiple devices in a LAN and intelligently forwards data frames based on MAC addresses.

#### Key Functions

| Function | Description |
|----------|-------------|
| **Frame Forwarding** | Forwards frames only to the destination port using MAC address table |
| **MAC Address Learning** | Builds a MAC address table by learning source addresses |
| **Collision Domain Separation** | Each port is a separate collision domain |
| **Full-Duplex Communication** | Allows simultaneous send/receive on each port |
| **Broadcast Domain** | All ports share the same broadcast domain (unless VLANs used) |

#### How Switch Works
```
1. Device A sends frame → Switch receives on Port 1
2. Switch learns: MAC-A is on Port 1 (stores in CAM table)
3. Switch checks destination MAC in CAM table
4. If found → Forward to specific port
   If not found → Flood to all ports (except source)
```

#### Switch vs Hub
| Feature | Switch | Hub |
|---------|--------|-----|
| Intelligence | MAC-based forwarding | Broadcasts to all |
| Collision | Per-port isolation | Single collision domain |
| Speed | Better performance | Shared bandwidth |

---

### b) Write the command to assign a static IP in Linux

#### Using `ip` Command (Modern Method)
```bash
# Assign IP address with subnet mask
sudo ip addr add 192.168.1.100/24 dev eth0

# Bring interface up
sudo ip link set eth0 up

# Add default gateway
sudo ip route add default via 192.168.1.1
```

#### Using `ifconfig` Command (Legacy)
```bash
# Assign IP and netmask
sudo ifconfig eth0 192.168.1.100 netmask 255.255.255.0 up

# Add default gateway
sudo route add default gw 192.168.1.1
```

#### Permanent Configuration (Ubuntu/Debian - Netplan)
```yaml
# /etc/netplan/01-config.yaml
network:
  version: 2
  ethernets:
    eth0:
      addresses:
        - 192.168.1.100/24
      gateway4: 192.168.1.1
      nameservers:
        addresses: [8.8.8.8, 8.8.4.4]
```
```bash
sudo netplan apply
```

#### Permanent Configuration (RHEL/CentOS)
```bash
# /etc/sysconfig/network-scripts/ifcfg-eth0
DEVICE=eth0
BOOTPROTO=static
IPADDR=192.168.1.100
NETMASK=255.255.255.0
GATEWAY=192.168.1.1
ONBOOT=yes
```

---

### c) What does the `ip link set eth0 up` command do?

#### Function
This command **activates (enables)** the network interface `eth0`, bringing it to the **UP** state.

#### Breakdown
| Part | Meaning |
|------|---------|
| `ip` | Modern Linux networking utility |
| `link` | Operate on network link/interface |
| `set` | Modify interface properties |
| `eth0` | Interface name (first Ethernet interface) |
| `up` | Enable/activate the interface |

#### Related Commands
```bash
# Disable interface
ip link set eth0 down

# Check interface status
ip link show eth0

# View all interfaces
ip link show

# Enable interface with promiscuous mode
ip link set eth0 up promisc on
```

#### Output Example
```bash
$ ip link show eth0
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP
    link/ether 00:11:22:33:44:55 brd ff:ff:ff:ff:ff:ff
```
The `UP` flag indicates the interface is active.

---

### d) Explain the difference between ping and traceroute

#### Concept Overview

| Feature | ping | traceroute |
|---------|------|------------|
| **Purpose** | Test connectivity & measure RTT | Trace path packets take to destination |
| **Protocol** | ICMP Echo Request/Reply | ICMP Time Exceeded / UDP (Linux) |
| **Output** | Response time, packet loss | Each hop along the route |
| **Layer** | Network Layer (L3) | Network Layer (L3) |

#### ping Command
```bash
ping 8.8.8.8
```
**What it does:**
1. Sends ICMP Echo Request to destination
2. Waits for ICMP Echo Reply
3. Measures Round Trip Time (RTT)
4. Reports packet loss statistics

**Output:**
```
PING 8.8.8.8 (8.8.8.8) 56(84) bytes of data.
64 bytes from 8.8.8.8: icmp_seq=1 ttl=117 time=12.5 ms
64 bytes from 8.8.8.8: icmp_seq=2 ttl=117 time=11.8 ms
--- 8.8.8.8 ping statistics ---
2 packets transmitted, 2 received, 0% packet loss
```

#### traceroute Command
```bash
traceroute 8.8.8.8
```
**What it does:**
1. Sends packets with incrementing TTL (1, 2, 3...)
2. Each router decrements TTL; when TTL=0, sends "Time Exceeded"
3. Discovers each hop to destination
4. Shows path and latency per hop

**Output:**
```
traceroute to 8.8.8.8, 30 hops max
 1  192.168.1.1 (192.168.1.1)  1.234 ms
 2  10.0.0.1 (10.0.0.1)  5.678 ms
 3  * * *  (no response)
 4  8.8.8.8 (8.8.8.8)  15.432 ms
```

#### Visual Comparison
```
ping:         [PC] ---------> [Server]
              Check: Is server reachable? How fast?

traceroute:   [PC] --> [R1] --> [R2] --> [R3] --> [Server]
              Discover: What path do packets take?
```

---

### f) What does the `ip route show` command display?

#### Function
Displays the **kernel routing table**, showing how packets are routed to different networks.

#### Output Fields
```bash
$ ip route show
default via 192.168.1.1 dev eth0 proto static metric 100
192.168.1.0/24 dev eth0 proto kernel scope link src 192.168.1.100
10.0.0.0/8 via 192.168.1.254 dev eth0
```

| Field | Description |
|-------|-------------|
| `default` | Default route (0.0.0.0/0) |
| `via 192.168.1.1` | Next-hop gateway |
| `dev eth0` | Outgoing interface |
| `proto kernel` | Route added by kernel |
| `proto static` | Manually configured route |
| `scope link` | Valid only on this link |
| `src 192.168.1.100` | Source IP for this route |
| `metric 100` | Route priority (lower = preferred) |

#### Route Types Explained
```
+------------------+-------------------------------------------+
| Route Entry      | Meaning                                   |
+------------------+-------------------------------------------+
| default via X    | All unmatched traffic goes to gateway X   |
| 192.168.1.0/24   | Directly connected network                |
| 10.0.0.0/8 via Y | Network 10.x.x.x reachable via gateway Y  |
+------------------+-------------------------------------------+
```

#### Related Commands
```bash
# Show specific route
ip route get 8.8.8.8

# Add static route
ip route add 10.10.0.0/16 via 192.168.1.254

# Delete route
ip route del 10.10.0.0/16

# Show detailed routing
ip route show table all
```

---

### g) Why should two connected systems be in the same subnet?

#### Concept
For **direct communication** without routing, two systems must share the same network prefix (subnet).

#### Reasons

| Reason | Explanation |
|--------|-------------|
| **Direct Communication** | Systems in same subnet use ARP to find MAC addresses and communicate directly |
| **No Router Needed** | Traffic stays local; doesn't need gateway |
| **Broadcast Domain** | ARP requests reach all hosts in subnet |
| **Efficiency** | Lower latency, reduced network overhead |
| **IP Addressing** | Subnet mask determines network boundary |

#### How Subnet Communication Works
```
Same Subnet (192.168.1.0/24):
┌──────────────────┐        ┌──────────────────┐
│   PC1            │        │   PC2            │
│   192.168.1.10   │◄──────►│   192.168.1.20   │
│   /24            │  ARP   │   /24            │
└──────────────────┘  MAC   └──────────────────┘
Direct communication using MAC addresses

Different Subnets:
┌──────────────────┐        ┌──────────────────┐
│   PC1            │        │   PC2            │
│   192.168.1.10   │   ✗    │   192.168.2.20   │
│   /24            │        │   /24            │
└──────────────────┘        └──────────────────┘
Cannot communicate directly - needs router!
```

#### Subnet Calculation Example
```
IP:      192.168.1.100
Mask:    255.255.255.0 (/24)
Network: 192.168.1.0

IP:      192.168.1.200  → Same subnet ✓ (Can communicate)
IP:      192.168.2.100  → Different subnet ✗ (Needs router)
```

#### What Happens Without Same Subnet?
1. PC1 checks: Is destination in my subnet?
2. If NO → Send to default gateway
3. If no gateway configured → Communication fails
4. ARP won't work across subnets

---

## Q2: Practical Solutions — 20 Marks

---

### Option A: C Program to Display Star Topology

**File:** `Slip_12_Q2_OptionA.c`

#### Concept
Star topology has a **central hub/switch** connected to all nodes. All communication passes through the central device.

#### Characteristics
| Feature | Description |
|---------|-------------|
| Structure | Central hub + peripheral nodes |
| Failure Impact | Hub failure = network down; node failure = isolated |
| Performance | No collisions (with switch); dedicated bandwidth |
| Scalability | Easy to add/remove nodes |
| Cost | More cabling than bus topology |

#### Visual Representation
```
        [Node 1]
            │
    [Node 2]│
        \   │   /
         \  │  /
      [Central Hub/Switch]
         /  │  \
        /   │   \
    [Node 3]│
            │
        [Node 4]
```

---

### Option B: Router Password Configuration Program

**File:** `Slip_12_Q2_OptionB.c`

#### Concept
Simulates Cisco IOS commands for router security configuration:
- **hostname**: Device identification
- **enable password**: Plain-text password (visible in config)
- **enable secret**: MD5-encrypted password (secure)

#### Cisco IOS Commands
```
Router> enable
Router# configure terminal
Router(config)# hostname MyRouter
MyRouter(config)# enable password cisco123
MyRouter(config)# enable secret class456
MyRouter(config)# end
MyRouter# show running-config
```

#### Password Comparison
| Type | Storage | Security | Priority |
|------|---------|----------|----------|
| enable password | Plain text | Low | Lower |
| enable secret | MD5 hash | High | Higher |

---

### Option C: Packet Tracer - Star Topology Configuration

#### Step-by-Step Instructions

**1. Add Devices**
- Open Cisco Packet Tracer
- Add 1 Switch (2960)
- Add 5 PCs

**2. Connect Devices**
| Device | Switch Port | Cable Type |
|--------|-------------|------------|
| PC0 | FastEthernet0/1 | Copper Straight-Through |
| PC1 | FastEthernet0/2 | Copper Straight-Through |
| PC2 | FastEthernet0/3 | Copper Straight-Through |
| PC3 | FastEthernet0/4 | Copper Straight-Through |
| PC4 | FastEthernet0/5 | Copper Straight-Through |

**3. Configure IP Addresses**
| PC | IP Address | Subnet Mask |
|----|------------|-------------|
| PC0 | 192.168.10.1 | 255.255.255.0 |
| PC1 | 192.168.10.2 | 255.255.255.0 |
| PC2 | 192.168.10.3 | 255.255.255.0 |
| PC3 | 192.168.10.4 | 255.255.255.0 |
| PC4 | 192.168.10.5 | 255.255.255.0 |

**Configuration Steps for Each PC:**
```
1. Click PC → Desktop tab → IP Configuration
2. Select "Static"
3. Enter IP Address: 192.168.10.X
4. Enter Subnet Mask: 255.255.255.0
5. Leave Gateway blank (same subnet)
```

**4. Verify Connectivity**
```
PC0> ping 192.168.10.2
PC0> ping 192.168.10.5
```

**Topology Diagram:**
```
                    Switch (2960)
                   ┌───────────┐
                   │ Fa0/1-0/5 │
                   └─────┬─────┘
          ┌──────┬───────┼───────┬──────┐
          │      │       │       │      │
        [PC0] [PC1]   [PC2]   [PC3]  [PC4]
      .10.1  .10.2   .10.3   .10.4  .10.5
```

---

## Quick Reference Card

### Linux Network Commands
```bash
# IP Configuration
ip addr show                    # Show all IP addresses
ip addr add 192.168.1.10/24 dev eth0   # Add IP
ip link set eth0 up/down        # Enable/disable interface

# Routing
ip route show                   # Show routing table
ip route add default via 192.168.1.1   # Add default gateway

# Troubleshooting
ping <ip>                       # Test connectivity
traceroute <ip>                 # Trace path
netstat -rn                     # Show routes (legacy)
```

### Cisco IOS Password Commands
```
hostname <name>                 # Set device name
enable password <pass>          # Set plaintext password
enable secret <pass>            # Set encrypted password
service password-encryption     # Encrypt all passwords
show running-config             # View configuration
```

---

## Files Included

| File | Description |
|------|-------------|
| `Slip_12_CN_SOLUTION.md` | This complete solution guide |
| `Slip_12_Q2_OptionA.c` | Star Topology visualization program |
| `Slip_12_Q2_OptionB.c` | Router password configuration simulator |
