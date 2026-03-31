# Slip 6 — Computer Networks Solution Guide

## Question 1 (10 Marks): Theory Questions (Answer ANY 5)

---

### a) Identify the network device from a given physical sample or image and write down its purpose and ports.

#### Common Network Devices:

| Device | Physical Appearance | Purpose | Common Ports |
|--------|---------------------|---------|--------------|
| **Router** | Box with antennas, LED indicators, multiple ports | Routes packets between different networks, connects LAN to WAN | WAN (1), LAN (4-8), Console, USB |
| **Switch** | Rack-mounted box with many ports | Connects devices within same network, forwards frames based on MAC address | 8/16/24/48 RJ-45 ports, Uplink, Console |
| **Hub** | Similar to switch, fewer LEDs | Broadcasts data to all ports (obsolete) | 4/8/16 RJ-45 ports |
| **Modem** | Small box with DSL/Cable input | Modulates/demodulates signals for internet access | DSL/Cable In, Ethernet Out, Phone |
| **Access Point** | Small device with antennas | Provides wireless connectivity to network | 1-2 Ethernet ports, Power |
| **Firewall** | Rack-mounted appliance | Network security, filters traffic | Multiple Ethernet ports, Console |

#### Port Types:
```
╔═══════════════════════════════════════════════════════════╗
║  Port Type        │  Connector    │  Speed/Use            ║
╠═══════════════════════════════════════════════════════════╣
║  Console Port     │  RJ-45/USB    │  Device configuration ║
║  Ethernet LAN     │  RJ-45        │  10/100/1000 Mbps     ║
║  WAN Port         │  RJ-45        │  Internet connection  ║
║  SFP/SFP+         │  Fiber        │  1/10/40 Gbps         ║
║  USB              │  USB-A/Micro  │  Storage/Recovery     ║
╚═══════════════════════════════════════════════════════════╝
```

---

### b) List different types of network cables and their uses

#### 1. Coaxial Cable

```
    ┌──────────────────────────────────────┐
    │         Cross-Section View           │
    │                                       │
    │    ┌─────────────────────────┐       │
    │    │ Outer Jacket (PVC)      │       │
    │    │  ┌───────────────────┐  │       │
    │    │  │ Braided Shield    │  │       │
    │    │  │  ┌─────────────┐  │  │       │
    │    │  │  │ Insulator   │  │  │       │
    │    │  │  │  ┌───────┐  │  │  │       │
    │    │  │  │  │ Core  │  │  │  │       │
    │    │  │  │  └───────┘  │  │  │       │
    │    │  │  └─────────────┘  │  │       │
    │    │  └───────────────────┘  │       │
    │    └─────────────────────────┘       │
    └──────────────────────────────────────┘
```

| Type | Impedance | Use |
|------|-----------|-----|
| RG-58 (Thinnet) | 50Ω | Older Ethernet (10Base2) |
| RG-8 (Thicknet) | 50Ω | Backbone networks (10Base5) |
| RG-59 | 75Ω | Cable TV, CCTV |
| RG-6 | 75Ω | Modern Cable TV, Internet |

**Uses:** Cable TV, CCTV systems, Cable Internet, Legacy LANs

---

#### 2. Twisted Pair Cable

**Two Types:**

| Feature | UTP (Unshielded) | STP (Shielded) |
|---------|------------------|----------------|
| **Shielding** | None | Metal foil/braid around pairs |
| **Cost** | Less expensive | More expensive |
| **Installation** | Easier, flexible | Harder, requires grounding |
| **EMI Protection** | Lower | Higher |
| **Use** | Office LANs, Home networks | Industrial, High-EMI areas |

```
UTP Cable Structure:
    ┌─────────────────────────────────┐
    │ ┌─────────────────────────────┐ │
    │ │  Pair 1: Orange/White-Orange│ │
    │ │  ╭──────╮                   │ │
    │ │  │ ╱╲╱╲ │ Twisted Wires     │ │
    │ │  ╰──────╯                   │ │
    │ │  Pair 2: Green/White-Green  │ │
    │ │  Pair 3: Blue/White-Blue    │ │
    │ │  Pair 4: Brown/White-Brown  │ │
    │ └─────────────────────────────┘ │
    │     Outer Jacket (PVC)          │
    └─────────────────────────────────┘

STP Cable Structure:
    ┌─────────────────────────────────┐
    │ ┌─────────────────────────────┐ │
    │ │▓▓▓▓ Metal Shield ▓▓▓▓▓▓▓▓▓▓│ │
    │ │  ┌─────────────────────────┐│ │
    │ │  │ 4 Twisted Pairs         ││ │
    │ │  │ (individually shielded) ││ │
    │ │  └─────────────────────────┘│ │
    │ └─────────────────────────────┘ │
    │     Outer Jacket                 │
    └─────────────────────────────────┘
```

**Category Ratings:**

| Category | Max Speed | Max Distance | Use |
|----------|-----------|--------------|-----|
| Cat 5 | 100 Mbps | 100m | Legacy Ethernet |
| Cat 5e | 1 Gbps | 100m | Home/Small office |
| Cat 6 | 10 Gbps | 55m | Enterprise networks |
| Cat 6a | 10 Gbps | 100m | Data centers |
| Cat 7 | 10 Gbps | 100m | High-performance |
| Cat 8 | 25-40 Gbps | 30m | Data centers |

---

#### 3. Fiber Optic Cable

```
Structure:
    ┌────────────────────────────────────────┐
    │  ┌────────────────────────────────┐    │
    │  │  ┌──────────────────────────┐  │    │
    │  │  │  ┌────────────────────┐  │  │    │
    │  │  │  │    Glass Core      │  │  │    │
    │  │  │  │    (Light path)    │  │  │    │
    │  │  │  └────────────────────┘  │  │    │
    │  │  │     Cladding (Glass)     │  │    │
    │  │  └──────────────────────────┘  │    │
    │  │      Buffer Coating           │    │
    │  └────────────────────────────────┘    │
    │        Outer Jacket                    │
    └────────────────────────────────────────┘
```

| Feature | Single Mode (SMF) | Multi Mode (MMF) |
|---------|-------------------|------------------|
| Core Diameter | 8-10 µm | 50-62.5 µm |
| Light Source | Laser | LED/Laser |
| Distance | Up to 100+ km | Up to 2 km |
| Cost | Higher | Lower |
| Use | Long-haul, Telecom | Campus, Data centers |

**Advantages of Fiber:**
- Very high bandwidth (Tbps)
- Immune to EMI
- Low signal attenuation
- Secure (hard to tap)

**Disadvantages:**
- Expensive equipment
- Difficult to splice/terminate
- Fragile

---

### c) What is the role of `no shutdown` in router configuration?

#### Purpose:
The `no shutdown` command **activates** a router or switch interface that is administratively disabled.

#### Key Points:
- By default, router interfaces are in **shutdown** state (administratively down)
- Switch interfaces are **enabled** by default
- Must be executed in interface configuration mode

#### States of an Interface:

```
╔════════════════════════════════════════════════════════════╗
║  Interface State Diagram                                   ║
╠════════════════════════════════════════════════════════════╣
║                                                            ║
║   ┌───────────────────┐                                   ║
║   │ Administratively  │ ◄── shutdown command              ║
║   │      Down         │                                   ║
║   └─────────┬─────────┘                                   ║
║             │                                              ║
║             │ no shutdown                                  ║
║             ▼                                              ║
║   ┌───────────────────┐                                   ║
║   │   Down/Down       │ ◄── No cable or remote end down   ║
║   │ (Protocol down)   │                                   ║
║   └─────────┬─────────┘                                   ║
║             │                                              ║
║             │ Cable connected, link established            ║
║             ▼                                              ║
║   ┌───────────────────┐                                   ║
║   │     Up/Up         │ ◄── Fully operational             ║
║   │   (Active)        │                                   ║
║   └───────────────────┘                                   ║
╚════════════════════════════════════════════════════════════╝
```

#### Configuration Example:

```
Router> enable
Router# configure terminal
Router(config)# interface GigabitEthernet0/0
Router(config-if)# ip address 192.168.1.1 255.255.255.0
Router(config-if)# no shutdown          ← Activates the interface
Router(config-if)# exit
```

#### Verification:
```
Router# show ip interface brief
Interface           IP-Address      OK? Method Status     Protocol
GigabitEthernet0/0  192.168.1.1     YES manual up         up
GigabitEthernet0/1  unassigned      YES unset  admin down down
```

| Status | Meaning |
|--------|---------|
| administratively down | `shutdown` applied |
| down/down | `no shutdown` but no link |
| up/up | Interface is operational |

---

### d) Compare the output of `ip addr` and `ifconfig`

#### Overview:
Both commands display network interface information on Linux systems.

| Feature | `ip addr` | `ifconfig` |
|---------|-----------|------------|
| Package | iproute2 (modern) | net-tools (legacy) |
| Status | Current standard | Deprecated |
| IPv6 Support | Full native support | Limited |
| Output Format | More detailed | Simpler, human-readable |
| Availability | All modern Linux | May need installation |

#### Sample Output Comparison:

**`ip addr` Output:**
```
$ ip addr
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UP
    link/ether 00:0c:29:ab:cd:ef brd ff:ff:ff:ff:ff:ff
    inet 192.168.1.100/24 brd 192.168.1.255 scope global eth0
       valid_lft forever preferred_lft forever
    inet6 fe80::20c:29ff:feab:cdef/64 scope link 
       valid_lft forever preferred_lft forever
```

**`ifconfig` Output:**
```
$ ifconfig
eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.1.100  netmask 255.255.255.0  broadcast 192.168.1.255
        inet6 fe80::20c:29ff:feab:cdef  prefixlen 64  scopeid 0x20<link>
        ether 00:0c:29:ab:cd:ef  txqueuelen 1000  (Ethernet)
        RX packets 12345  bytes 8765432 (8.3 MiB)
        TX packets 6789  bytes 1234567 (1.1 MiB)

lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        inet 127.0.0.1  netmask 255.0.0.0
        inet6 ::1  prefixlen 128  scopeid 0x10<host>
        loop  txqueuelen 1000  (Local Loopback)
        RX packets 100  bytes 10000 (9.7 KiB)
        TX packets 100  bytes 10000 (9.7 KiB)
```

#### Key Differences Table:

| Aspect | `ip addr` | `ifconfig` |
|--------|-----------|------------|
| **CIDR Notation** | Uses /24 format | Uses netmask format |
| **Interface Index** | Shows numeric index (1:, 2:) | No index shown |
| **State Info** | Shows state (UP/UNKNOWN) | Shows flags |
| **Lifetime** | Shows valid_lft, preferred_lft | Not shown |
| **Scope** | Shows scope (global/link/host) | Shows scopeid |
| **Statistics** | Use `ip -s link` | Built-in (RX/TX) |
| **All Interfaces** | `ip addr show` | `ifconfig -a` |

#### Recommendation:
Use `ip addr` as it is:
- The modern standard
- More feature-rich
- Better IPv6 support
- Actively maintained

---

### f) What command do you type to move from Router> to Router# mode?

#### Answer: **`enable`**

#### Cisco IOS Mode Hierarchy:

```
╔═══════════════════════════════════════════════════════════════════╗
║                     CISCO IOS MODE HIERARCHY                      ║
╠═══════════════════════════════════════════════════════════════════╣
║                                                                   ║
║   User EXEC Mode              Privileged EXEC Mode               ║
║   ┌───────────────┐           ┌────────────────────┐            ║
║   │   Router>     │──enable──▶│     Router#        │            ║
║   │               │◀──disable─│                    │            ║
║   │ Limited view  │           │ Full access        │            ║
║   │ commands only │           │ All show commands  │            ║
║   └───────────────┘           └──────────┬─────────┘            ║
║                                          │                       ║
║                               configure terminal                 ║
║                                          │                       ║
║                                          ▼                       ║
║                               ┌────────────────────┐            ║
║                               │  Router(config)#   │            ║
║                               │                    │            ║
║                               │ Global Config Mode │            ║
║                               └──────────┬─────────┘            ║
║                                          │                       ║
║                    ┌─────────────────────┼─────────────────┐    ║
║                    │                     │                  │    ║
║         interface eth0          line vty 0 4      router ospf 1 ║
║                    │                     │                  │    ║
║                    ▼                     ▼                  ▼    ║
║         ┌───────────────┐    ┌──────────────┐   ┌────────────┐ ║
║         │Router(config- │    │Router(config-│   │Router      │ ║
║         │if)#           │    │line)#        │   │(config-    │ ║
║         │               │    │              │   │router)#    │ ║
║         │Interface Mode │    │Line Mode     │   │Router Mode │ ║
║         └───────────────┘    └──────────────┘   └────────────┘ ║
╚═══════════════════════════════════════════════════════════════════╝
```

#### Mode Transitions:

| From | To | Command |
|------|-----|---------|
| Router> | Router# | `enable` |
| Router# | Router> | `disable` |
| Router# | Router(config)# | `configure terminal` |
| Router(config)# | Router# | `exit` or `end` |
| Router(config-if)# | Router(config)# | `exit` |
| Router(config-if)# | Router# | `end` or Ctrl+Z |

#### Mode Prompts and Capabilities:

| Mode | Prompt | Purpose |
|------|--------|---------|
| User EXEC | `Router>` | Basic monitoring, limited commands |
| Privileged EXEC | `Router#` | Full show commands, debug, copy |
| Global Config | `Router(config)#` | System-wide configuration |
| Interface Config | `Router(config-if)#` | Interface-specific settings |
| Line Config | `Router(config-line)#` | Console/VTY configuration |

#### Example Session:
```
Router> enable
Password: ********
Router# configure terminal
Router(config)# hostname MyRouter
MyRouter(config)# interface GigabitEthernet0/0
MyRouter(config-if)# ip address 192.168.1.1 255.255.255.0
MyRouter(config-if)# no shutdown
MyRouter(config-if)# end
MyRouter# copy running-config startup-config
```

---

### g) How many hexadecimal digits are needed for a 64-bit WEP key? Give any 5 examples.

#### Calculation:

```
1 Hexadecimal digit = 4 bits

For 64-bit WEP:
    64 bits ÷ 4 bits/hex digit = 16 hex digits

But Wait! WEP includes a 24-bit IV (Initialization Vector)
    Actual key = 64 - 24 = 40 bits
    40 bits ÷ 4 bits/hex digit = 10 hex digits
```

#### Answer: **10 hexadecimal digits** (for user-entered key portion)

#### WEP Key Structure:

```
╔══════════════════════════════════════════════════════════════╗
║           64-bit WEP Key Structure                           ║
╠══════════════════════════════════════════════════════════════╣
║                                                              ║
║   ┌────────────────────┬─────────────────────────────────┐  ║
║   │    IV (24 bits)    │      User Key (40 bits)         │  ║
║   │   Auto-generated   │     10 Hex Digits               │  ║
║   └────────────────────┴─────────────────────────────────┘  ║
║   │←───── 24 bits ────▶│◀────────── 40 bits ────────────▶│  ║
║   │                    │                                  │  ║
║   │←─────────────────── 64 bits total ──────────────────▶│  ║
║                                                              ║
╚══════════════════════════════════════════════════════════════╝
```

#### 5 Examples of 64-bit WEP Keys (10 hex digits each):

| # | WEP Key (10 hex digits) | ASCII Equivalent (5 chars) |
|---|-------------------------|---------------------------|
| 1 | `1A2B3C4D5E` | Not printable |
| 2 | `ABCDEF1234` | Not printable |
| 3 | `0123456789` | Not printable |
| 4 | `FEDCBA9876` | Not printable |
| 5 | `A1B2C3D4E5` | Not printable |

#### Alternative ASCII Format (5 characters = 40 bits):

| # | ASCII Key (5 chars) | Hex Equivalent |
|---|---------------------|----------------|
| 1 | `HELLO` | 48454C4C4F |
| 2 | `pass1` | 7061737331 |
| 3 | `AbCdE` | 4162436445 |
| 4 | `WEP64` | 5745503634 |
| 5 | `MyKey` | 4D794B6579 |

#### WEP Key Sizes Summary:

| WEP Type | Total Bits | IV Bits | User Key | Hex Digits | ASCII Chars |
|----------|-----------|---------|----------|------------|-------------|
| 64-bit | 64 | 24 | 40 bits | **10** | 5 |
| 128-bit | 128 | 24 | 104 bits | **26** | 13 |
| 256-bit | 256 | 24 | 232 bits | **58** | 29 |

#### Note on WEP Security:
⚠️ **WEP is considered insecure** and should not be used. Use WPA2 or WPA3 instead.
- Weak IV leads to key recovery attacks
- Can be cracked in minutes with tools like Aircrack-ng

---

## Question 2 (20 Marks): Practical Options

---

## Option A: Character Count Framing Method

### Concept
Character count framing is a method in the **Data Link Layer** where each frame begins with a count field that specifies the number of characters in the frame (including the count field itself).

### How It Works:

```
╔═══════════════════════════════════════════════════════════════╗
║            CHARACTER COUNT FRAMING                            ║
╠═══════════════════════════════════════════════════════════════╣
║                                                               ║
║  Original Data Stream:                                        ║
║  ┌─────────────────────────────────────────────────────┐     ║
║  │ H E L L O W O R L D H O W A R E Y O U             │     ║
║  └─────────────────────────────────────────────────────┘     ║
║                                                               ║
║  Frame Size = 5 characters (including count)                  ║
║                                                               ║
║  Framed Data:                                                 ║
║  ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐          ║
║  │  5  │  H  │  E  │  L  │  L  │  5  │  O  │  W  │ ...      ║
║  ├─────┼─────┴─────┴─────┴─────┼─────┼─────┴─────┴───        ║
║  │Count│    Frame 1 Data       │Count│   Frame 2 Data        ║
║  └─────┴───────────────────────┴─────┴───────────────        ║
║                                                               ║
║  Frame Structure:                                             ║
║  ┌───────────┬────────────────────────────────────────┐      ║
║  │   Count   │              Data                      │      ║
║  │  (1 byte) │         (Count - 1 bytes)              │      ║
║  └───────────┴────────────────────────────────────────┘      ║
║                                                               ║
╚═══════════════════════════════════════════════════════════════╝
```

### Algorithm

**Framing (Sender Side):**
```
FUNCTION createFrames(data, frameSize):
    frames = empty list
    i = 0
    WHILE i < length(data):
        frame = ""
        count = min(frameSize, length(data) - i + 1)
        frame = frame + count    // Add count as first character
        FOR j = 0 TO count - 2:  // Add data (count-1 characters)
            frame = frame + data[i]
            i = i + 1
        ADD frame to frames
    RETURN frames
```

**Deframing (Receiver Side):**
```
FUNCTION extractData(framedStream):
    data = ""
    i = 0
    WHILE i < length(framedStream):
        count = framedStream[i]  // Read count
        i = i + 1
        FOR j = 0 TO count - 2:  // Read count-1 data characters
            data = data + framedStream[i]
            i = i + 1
    RETURN data
```

### Worked Example

**Input Data:** `HELLOWORLD`  
**Frame Size:** 5 (including count)

```
Step 1: Create Frame 1
  - Count = 5
  - Data = "HELL" (4 characters)
  - Frame 1: [5][H][E][L][L]

Step 2: Create Frame 2  
  - Count = 5
  - Data = "OWOR" (4 characters)
  - Frame 2: [5][O][W][O][R]

Step 3: Create Frame 3
  - Count = 3 (only 2 characters left + 1 for count)
  - Data = "LD" (2 characters)
  - Frame 3: [3][L][D]

Complete Framed Stream: [5][H][E][L][L][5][O][W][O][R][3][L][D]
```

### Advantages & Disadvantages

| Advantages | Disadvantages |
|------------|---------------|
| Simple to implement | Single bit error in count corrupts all following frames |
| Low overhead (1 byte per frame) | No error recovery mechanism |
| Variable frame sizes possible | Synchronization loss is catastrophic |

### Error Scenario:

```
Original:  [5][H][E][L][L][5][O][W][O][R]
                        ↓
            Transmission error changes 5 to 7
                        ↓
Received:  [5][H][E][L][L][7][O][W][O][R]
                        
Result: Frame 2 reads 7 characters, consuming data from Frame 3!
        Entire stream becomes unsynchronized.
```

### See: `Slip_06_Q2_OptionA.c`

---

## Option B: Star Topology Display/Packet Tracer Configuration

### Concept

**Star Topology** is a network arrangement where all devices connect to a central hub or switch.

```
╔═══════════════════════════════════════════════════════════════╗
║                    STAR TOPOLOGY                              ║
╠═══════════════════════════════════════════════════════════════╣
║                                                               ║
║                         ┌─────────┐                          ║
║                    PC1  │   ○     │                          ║
║               192.168.1.1│   │     │                          ║
║                         └────┼────┘                          ║
║                              │                                ║
║        ┌─────────┐          │          ┌─────────┐           ║
║   PC5  │   ○     │──────────┼──────────│   ○     │ PC2       ║
║ .1.5   │   │     │          │          │   │     │ .1.2      ║
║        └────┼────┘     ┌────┴────┐     └────┼────┘           ║
║             │          │ SWITCH  │          │                ║
║             └──────────│  ┌───┐  │──────────┘                ║
║                        │  │ S │  │                           ║
║                        │  └───┘  │                           ║
║             ┌──────────│ 1 2 3 4 │──────────┐                ║
║             │          └────┬────┘          │                ║
║        ┌────┼────┐          │          ┌────┼────┐           ║
║   PC4  │   ○     │          │          │   ○     │ PC3       ║
║ .1.4   │   │     │──────────┘──────────│   │     │ .1.3      ║
║        └─────────┘                     └─────────┘           ║
║                                                               ║
║   Network: 192.168.1.0/24                                    ║
║   Subnet Mask: 255.255.255.0                                 ║
║                                                               ║
╚═══════════════════════════════════════════════════════════════╝
```

### Characteristics of Star Topology:

| Feature | Description |
|---------|-------------|
| **Central Device** | Switch or Hub |
| **Connection** | Each device has dedicated link to center |
| **Failure Impact** | Single device failure doesn't affect others |
| **Central Failure** | Entire network goes down |
| **Scalability** | Easy to add new devices |
| **Cost** | More cabling than bus topology |
| **Troubleshooting** | Easy to isolate problems |

### Packet Tracer Configuration (5 PCs):

#### Step-by-Step Instructions:

1. **Add Devices:**
   - Drag 1 Switch (2960) to workspace
   - Drag 5 PCs to workspace

2. **Connect Devices:**
   - Use Copper Straight-Through cables
   - Connect each PC to switch port (Fa0/1 through Fa0/5)

3. **Configure IP Addresses:**

| Device | IP Address | Subnet Mask | Gateway |
|--------|------------|-------------|---------|
| PC1 | 192.168.1.1 | 255.255.255.0 | (none needed) |
| PC2 | 192.168.1.2 | 255.255.255.0 | (none needed) |
| PC3 | 192.168.1.3 | 255.255.255.0 | (none needed) |
| PC4 | 192.168.1.4 | 255.255.255.0 | (none needed) |
| PC5 | 192.168.1.5 | 255.255.255.0 | (none needed) |

4. **IP Configuration Steps (for each PC):**
   - Click on PC → Desktop tab → IP Configuration
   - Enter IP Address and Subnet Mask
   - Leave Gateway blank (same network)

5. **Verify Connectivity:**
   - Open Command Prompt on any PC
   - Ping other PCs: `ping 192.168.1.X`

### See: `Slip_06_Q2_OptionB.c`

---

## Option C: Packet Tracer - Router Configuration (2 PCs, 1 Router)

### Network Diagram:

```
╔═══════════════════════════════════════════════════════════════════╗
║              ROUTER CONFIGURATION - TWO NETWORKS                  ║
╠═══════════════════════════════════════════════════════════════════╣
║                                                                   ║
║  Network 1: 192.168.1.0/24         Network 2: 192.168.2.0/24    ║
║                                                                   ║
║  ┌─────────────┐                           ┌─────────────┐       ║
║  │    PC1      │                           │    PC2      │       ║
║  │ 192.168.1.2 │                           │ 192.168.2.2 │       ║
║  │ GW: .1.1    │                           │ GW: .2.1    │       ║
║  └──────┬──────┘                           └──────┬──────┘       ║
║         │                                         │               ║
║         │ Fa0                                Fa0  │               ║
║         │                                         │               ║
║    ═════╪═════════════════════════════════════════╪═════         ║
║         │                                         │               ║
║         │ G0/0                               G0/1 │               ║
║         │ 192.168.1.1                 192.168.2.1 │               ║
║         │                                         │               ║
║         └────────────┐       ┌────────────────────┘               ║
║                      │       │                                    ║
║                   ┌──┴───────┴──┐                                ║
║                   │   ROUTER    │                                ║
║                   │  ┌───────┐  │                                ║
║                   │  │       │  │                                ║
║                   │  │  R1   │  │                                ║
║                   │  │       │  │                                ║
║                   │  └───────┘  │                                ║
║                   │ G0/0   G0/1 │                                ║
║                   └─────────────┘                                ║
║                                                                   ║
╚═══════════════════════════════════════════════════════════════════╝
```

### Configuration Table:

| Device | Interface | IP Address | Subnet Mask | Gateway |
|--------|-----------|------------|-------------|---------|
| PC1 | Fa0 | 192.168.1.2 | 255.255.255.0 | 192.168.1.1 |
| PC2 | Fa0 | 192.168.2.2 | 255.255.255.0 | 192.168.2.1 |
| Router | G0/0 | 192.168.1.1 | 255.255.255.0 | N/A |
| Router | G0/1 | 192.168.2.1 | 255.255.255.0 | N/A |

### Router CLI Configuration:

```cisco
! Enter Privileged EXEC Mode
Router> enable

! Enter Global Configuration Mode
Router# configure terminal

! Configure GigabitEthernet0/0 (connected to PC1)
Router(config)# interface GigabitEthernet0/0
Router(config-if)# ip address 192.168.1.1 255.255.255.0
Router(config-if)# no shutdown
Router(config-if)# exit

! Configure GigabitEthernet0/1 (connected to PC2)
Router(config)# interface GigabitEthernet0/1
Router(config-if)# ip address 192.168.2.1 255.255.255.0
Router(config-if)# no shutdown
Router(config-if)# exit

! Exit Configuration Mode
Router(config)# exit

! Save Configuration
Router# copy running-config startup-config
```

### PC Configuration (in Packet Tracer):

**PC1:**
```
Desktop → IP Configuration
IP Address: 192.168.1.2
Subnet Mask: 255.255.255.0
Default Gateway: 192.168.1.1
```

**PC2:**
```
Desktop → IP Configuration
IP Address: 192.168.2.2
Subnet Mask: 255.255.255.0
Default Gateway: 192.168.2.1
```

### Verification Commands:

**On Router:**
```cisco
Router# show ip interface brief
Router# show running-config
Router# show ip route
```

**On PCs (Command Prompt):**
```
PC1> ping 192.168.1.1     (Test gateway)
PC1> ping 192.168.2.2     (Test PC2 through router)

PC2> ping 192.168.2.1     (Test gateway)  
PC2> ping 192.168.1.2     (Test PC1 through router)
```

### Expected `show ip interface brief` Output:

```
Interface              IP-Address      OK? Method Status                Protocol
GigabitEthernet0/0     192.168.1.1     YES manual up                    up
GigabitEthernet0/1     192.168.2.1     YES manual up                    up
```

### Expected `show ip route` Output:

```
C    192.168.1.0/24 is directly connected, GigabitEthernet0/0
L    192.168.1.1/32 is directly connected, GigabitEthernet0/0
C    192.168.2.0/24 is directly connected, GigabitEthernet0/1
L    192.168.2.1/32 is directly connected, GigabitEthernet0/1
```

---

## Summary

| Option | Type | Key Concepts |
|--------|------|--------------|
| A | C Program | Character count framing, Data Link Layer |
| B | C Program / Packet Tracer | Star Topology visualization |
| C | Packet Tracer | Router interface configuration, Inter-VLAN routing |

---

## Files in this Solution:

1. **Slip_06_CN_SOLUTION.md** - This comprehensive guide
2. **Slip_06_Q2_OptionA.c** - Character count framing implementation
3. **Slip_06_Q2_OptionB.c** - Star topology display program
