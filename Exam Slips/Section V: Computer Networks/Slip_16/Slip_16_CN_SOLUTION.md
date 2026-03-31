# Slip 16 — Computer Networks Solution Guide

## Q1: Theory Questions (10 Marks - Answer ANY 5)

---

### a) Compare and contrast the functionalities of a switch and a router

#### Concept

Both **switches** and **routers** are networking devices used to connect devices, but they operate at different OSI layers and serve different purposes.

#### Switch

A **switch** is a Layer 2 (Data Link) device that connects devices within the **same network (LAN)**.

**Key Functions:**
1. **MAC Address Learning**: Builds a MAC address table
2. **Frame Forwarding**: Sends frames only to destination port
3. **Collision Domain Separation**: Each port is a separate collision domain
4. **Broadcast Domain**: All ports share one broadcast domain

#### Router

A **router** is a Layer 3 (Network) device that connects **different networks** and makes routing decisions.

**Key Functions:**
1. **IP Routing**: Forwards packets between networks using IP addresses
2. **Routing Table Management**: Maintains paths to destination networks
3. **Broadcast Domain Separation**: Each interface is a separate broadcast domain
4. **NAT/PAT**: Network Address Translation for private-to-public IP

#### Comparison Table

| Feature | Switch | Router |
|---------|--------|--------|
| **OSI Layer** | Layer 2 (Data Link) | Layer 3 (Network) |
| **Address Used** | MAC Address | IP Address |
| **Connects** | Devices in same LAN | Different networks (LAN to WAN) |
| **Broadcast Domain** | Single (all ports) | Separate per interface |
| **Collision Domain** | Separate per port | Separate per interface |
| **Speed** | Fast (hardware-based) | Slower (software routing) |
| **Routing Table** | MAC Table | Routing Table (IP-based) |
| **NAT Support** | No | Yes |
| **Cost** | Lower | Higher |
| **Intelligence** | Less intelligent | More intelligent |
| **Packet Inspection** | Frame header only | Full packet header |

#### Visual Comparison

```
Switch (Layer 2):
[PC1]─┬─[Switch]─┬─[PC2]
      │          │
[PC3]─┘          └─[PC4]
      Same Network (LAN)

Router (Layer 3):
[LAN 1: 192.168.1.x]──[Router]──[LAN 2: 192.168.2.x]
                         │
                    [Internet]
      Connects Different Networks
```

---

### b) What is a MAC address and how is it different from an IP address?

#### MAC Address (Media Access Control)

A **MAC address** is a unique hardware identifier assigned to the Network Interface Card (NIC) by the manufacturer.

**Format**: 48-bit (6 bytes), written as `XX:XX:XX:XX:XX:XX` (hexadecimal)
**Example**: `00:1A:2B:3C:4D:5E`

**Structure**:
```
┌─────────────────┬─────────────────┐
│   First 3 bytes │   Last 3 bytes  │
│       OUI       │       NIC       │
│ (Manufacturer)  │ (Device Unique) │
└─────────────────┴─────────────────┘
Example: 00:1A:2B : 3C:4D:5E
         Intel     : Unique ID
```

#### IP Address (Internet Protocol)

A **logical address** assigned to devices for network identification and location addressing.

**IPv4 Format**: 32-bit, written as `X.X.X.X` (dotted decimal)
**Example**: `192.168.1.100`

#### Key Differences

| Feature | MAC Address | IP Address |
|---------|-------------|------------|
| **OSI Layer** | Data Link (Layer 2) | Network (Layer 3) |
| **Type** | Physical/Hardware | Logical/Software |
| **Assigned by** | Manufacturer (burned-in) | Network Admin/DHCP |
| **Uniqueness** | Globally unique | Unique within network |
| **Format** | 48-bit hexadecimal | 32-bit (IPv4) / 128-bit (IPv6) |
| **Change** | Permanent (can be spoofed) | Can be changed/reassigned |
| **Scope** | Local network only | Global (routable) |
| **Used for** | Local delivery | End-to-end routing |
| **Example** | `00:1A:2B:3C:4D:5E` | `192.168.1.10` |

#### How They Work Together

```
PC A (192.168.1.10, MAC: AA:AA:AA:AA:AA:AA)
       ↓
       │ "Send to 192.168.1.20"
       ↓
    ARP Request: "Who has 192.168.1.20?"
       ↓
    ARP Reply: "192.168.1.20 is at BB:BB:BB:BB:BB:BB"
       ↓
Frame sent to MAC: BB:BB:BB:BB:BB:BB
       ↓
PC B (192.168.1.20, MAC: BB:BB:BB:BB:BB:BB)
```

#### Commands to View

```bash
# Linux
ip link show           # MAC address
ip addr show           # IP address
arp -a                 # ARP table

# Windows
ipconfig /all          # Both MAC and IP
arp -a                 # ARP table
```

---

### c) Perform subnetting on 192.168.1.0/26 and list all 4 subnet ranges with usable host IPs

#### Given Information
- **Network Address**: 192.168.1.0
- **CIDR Notation**: /26
- **Required**: List all 4 subnets with usable host ranges

#### Step 1: Calculate Network Parameters

```
Total IPv4 bits: 32
Network bits (/26): 26
Host bits: 32 - 26 = 6

Subnet Mask (binary): 11111111.11111111.11111111.11000000
Subnet Mask (decimal): 255.255.255.192
```

#### Step 2: Calculate Subnets and Hosts

```
Number of subnets from /24 = 2^(26-24) = 2^2 = 4 subnets
Hosts per subnet = 2^6 = 64 total addresses
Usable hosts = 64 - 2 = 62 hosts per subnet
Block size = 256 - 192 = 64
```

#### Step 3: Four Subnet Ranges

| Subnet | Network Address | First Usable | Last Usable | Broadcast |
|--------|-----------------|--------------|-------------|-----------|
| **Subnet 1** | 192.168.1.0 | 192.168.1.1 | 192.168.1.62 | 192.168.1.63 |
| **Subnet 2** | 192.168.1.64 | 192.168.1.65 | 192.168.1.126 | 192.168.1.127 |
| **Subnet 3** | 192.168.1.128 | 192.168.1.129 | 192.168.1.190 | 192.168.1.191 |
| **Subnet 4** | 192.168.1.192 | 192.168.1.193 | 192.168.1.254 | 192.168.1.255 |

#### Detailed Subnet Breakdown

**Subnet 1: 192.168.1.0/26**
```
Network Address:  192.168.1.0
Usable Range:     192.168.1.1 - 192.168.1.62
Broadcast:        192.168.1.63
Default Gateway:  192.168.1.1 (typically)
Usable Hosts:     62
```

**Subnet 2: 192.168.1.64/26**
```
Network Address:  192.168.1.64
Usable Range:     192.168.1.65 - 192.168.1.126
Broadcast:        192.168.1.127
Default Gateway:  192.168.1.65 (typically)
Usable Hosts:     62
```

**Subnet 3: 192.168.1.128/26**
```
Network Address:  192.168.1.128
Usable Range:     192.168.1.129 - 192.168.1.190
Broadcast:        192.168.1.191
Default Gateway:  192.168.1.129 (typically)
Usable Hosts:     62
```

**Subnet 4: 192.168.1.192/26**
```
Network Address:  192.168.1.192
Usable Range:     192.168.1.193 - 192.168.1.254
Broadcast:        192.168.1.255
Default Gateway:  192.168.1.193 (typically)
Usable Hosts:     62
```

#### Visual Representation

```
192.168.1.0/24 (Original Class C Network)
├── 192.168.1.0/26   [0-63]     Subnet 1 (62 usable hosts)
├── 192.168.1.64/26  [64-127]   Subnet 2 (62 usable hosts)
├── 192.168.1.128/26 [128-191]  Subnet 3 (62 usable hosts)
└── 192.168.1.192/26 [192-255]  Subnet 4 (62 usable hosts)
```

#### Summary Table

| Parameter | Value |
|-----------|-------|
| Original Network | 192.168.1.0/24 |
| Subnet Mask | 255.255.255.192 (/26) |
| Number of Subnets | 4 |
| Block Size | 64 |
| Usable Hosts per Subnet | 62 |
| Total Usable Hosts | 248 (62 × 4) |

---

### d) List and explain all five IP address classes with examples

#### Concept

IPv4 addresses are divided into **five classes (A, B, C, D, E)** based on the first few bits of the address. Classes A, B, and C are used for host addressing.

#### IP Address Classes Overview

| Class | First Octet Range | Leading Bits | Default Mask | Networks | Hosts per Network |
|-------|-------------------|--------------|--------------|----------|-------------------|
| **A** | 1 - 126 | 0 | 255.0.0.0 (/8) | 126 | 16,777,214 |
| **B** | 128 - 191 | 10 | 255.255.0.0 (/16) | 16,384 | 65,534 |
| **C** | 192 - 223 | 110 | 255.255.255.0 (/24) | 2,097,152 | 254 |
| **D** | 224 - 239 | 1110 | N/A | Multicast | N/A |
| **E** | 240 - 255 | 1111 | N/A | Reserved | N/A |

#### Class A

**Purpose**: Large organizations (governments, large enterprises)

```
First Octet: 1 - 126 (0 is reserved, 127 is loopback)
Format: N.H.H.H (Network.Host.Host.Host)
Default Mask: 255.0.0.0 (/8)
Networks: 2^7 - 2 = 126
Hosts: 2^24 - 2 = 16,777,214 per network

Example: 10.0.0.1
         ↑Network ↑Host portion
         
Binary: 0xxxxxxx.xxxxxxxx.xxxxxxxx.xxxxxxxx
        ↑Leading bit is 0
```

**Examples**: 
- `10.0.0.1` (Private)
- `45.33.32.156` (Public)
- `100.64.0.1` (Carrier-grade NAT)

#### Class B

**Purpose**: Medium-sized organizations (universities, mid-size companies)

```
First Octet: 128 - 191
Format: N.N.H.H (Network.Network.Host.Host)
Default Mask: 255.255.0.0 (/16)
Networks: 2^14 = 16,384
Hosts: 2^16 - 2 = 65,534 per network

Example: 172.16.0.1
         ↑Network ↑Host

Binary: 10xxxxxx.xxxxxxxx.xxxxxxxx.xxxxxxxx
        ↑Leading bits are 10
```

**Examples**:
- `172.16.0.1` (Private)
- `172.31.255.254` (Private)
- `150.100.50.25` (Public)

#### Class C

**Purpose**: Small organizations (small businesses, home networks)

```
First Octet: 192 - 223
Format: N.N.N.H (Network.Network.Network.Host)
Default Mask: 255.255.255.0 (/24)
Networks: 2^21 = 2,097,152
Hosts: 2^8 - 2 = 254 per network

Example: 192.168.1.100
         ↑Network      ↑Host

Binary: 110xxxxx.xxxxxxxx.xxxxxxxx.xxxxxxxx
        ↑Leading bits are 110
```

**Examples**:
- `192.168.1.1` (Private)
- `192.168.0.100` (Private)
- `200.50.100.5` (Public)

#### Class D (Multicast)

**Purpose**: One-to-many communication (streaming, routing protocols)

```
First Octet: 224 - 239
Usage: Multicast groups (not assigned to hosts)
No default mask (not used for host addressing)

Binary: 1110xxxx.xxxxxxxx.xxxxxxxx.xxxxxxxx
        ↑Leading bits are 1110
```

**Examples**:
- `224.0.0.1` (All hosts on segment)
- `224.0.0.2` (All routers on segment)
- `239.255.255.255` (Administratively scoped)

#### Class E (Reserved)

**Purpose**: Experimental/Future use (not for public use)

```
First Octet: 240 - 255
Usage: Reserved for research and development

Binary: 1111xxxx.xxxxxxxx.xxxxxxxx.xxxxxxxx
        ↑Leading bits are 1111
```

**Examples**:
- `240.0.0.1`
- `255.255.255.254`
- `250.100.50.25`

#### Special Addresses

| Address | Purpose |
|---------|---------|
| `0.0.0.0` | Default route / "this network" |
| `127.0.0.0/8` | Loopback (localhost) |
| `255.255.255.255` | Limited broadcast |
| `169.254.0.0/16` | Link-local (APIPA) |

#### Private IP Ranges (RFC 1918)

| Class | Private Range | Networks |
|-------|---------------|----------|
| A | 10.0.0.0 - 10.255.255.255 | 1 network |
| B | 172.16.0.0 - 172.31.255.255 | 16 networks |
| C | 192.168.0.0 - 192.168.255.255 | 256 networks |

---

### f) How many hexadecimal digits are needed for a 64-bit WEP key? Give any 5 examples

#### Concept

**WEP (Wired Equivalent Privacy)** is an older wireless security protocol that uses encryption keys of various lengths.

#### WEP Key Lengths

| WEP Version | Key Bits | + IV (24 bits) | Total Bits | Hex Digits |
|-------------|----------|----------------|------------|------------|
| 64-bit WEP | 40 | 24 | 64 | **10** |
| 128-bit WEP | 104 | 24 | 128 | **26** |
| 256-bit WEP | 232 | 24 | 256 | **58** |

#### Calculation for 64-bit WEP Key

```
64-bit WEP = 40-bit key + 24-bit IV (Initialization Vector)

User-entered key = 40 bits
1 hexadecimal digit = 4 bits
Hex digits needed = 40 / 4 = 10 hexadecimal digits
```

**Answer**: **10 hexadecimal digits** are needed for a 64-bit WEP key.

#### Valid Hexadecimal Characters

```
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F
(or lowercase: a, b, c, d, e, f)
```

#### 5 Examples of 64-bit WEP Keys (10 hex digits)

| # | WEP Key (Hex) | Notes |
|---|---------------|-------|
| 1 | `1234567890` | Numeric only |
| 2 | `ABCDEF1234` | Mixed alphanumeric |
| 3 | `A1B2C3D4E5` | Alternating pattern |
| 4 | `DEADBEEF00` | Common debug value |
| 5 | `CAFE123456` | Readable hex word |

#### Additional Examples

```
Example 6:  0F0F0F0F0F
Example 7:  AAAAAAAAAA
Example 8:  1A2B3C4D5E
Example 9:  F00DBABE12
Example 10: 9876543210
```

#### ASCII vs Hex Format

| Format | Length | Example |
|--------|--------|---------|
| Hexadecimal | 10 characters | `1234567890` |
| ASCII | 5 characters | `hello` |

Note: 5 ASCII characters × 8 bits = 40 bits = 10 hex digits

#### WEP Key Structure

```
┌─────────────────────────────────────────────────────────────────┐
│                        64-bit WEP Frame                         │
├────────────────────────────┬────────────────────────────────────┤
│    IV (24 bits)            │    Secret Key (40 bits)            │
│   (Generated by device)    │   (User-configured: 10 hex digits) │
└────────────────────────────┴────────────────────────────────────┘
```

#### ⚠️ Security Note

WEP is **obsolete and insecure**. It can be cracked in minutes using tools like Aircrack-ng. Use WPA2 or WPA3 instead.

---

### g) What are two more secure wireless encryption standards that should be used instead of WEP in a real-world scenario?

#### Why WEP is Insecure

| Vulnerability | Description |
|---------------|-------------|
| Short IV | 24-bit IV repeats frequently (birthday attack) |
| Weak RC4 | Flawed key scheduling algorithm |
| No Integrity | CRC-32 is not cryptographically secure |
| Static Keys | Same key used indefinitely |

#### Two Secure Alternatives

---

#### 1. WPA2 (Wi-Fi Protected Access 2)

**Released**: 2004
**Encryption**: AES-CCMP (128-bit)
**Standard**: IEEE 802.11i

**Features**:
- **AES Encryption**: Strong 128-bit block cipher
- **CCMP Protocol**: Counter Mode with CBC-MAC Protocol
- **4-Way Handshake**: Secure key exchange
- **Dynamic Keys**: Per-session encryption keys

**Modes**:
| Mode | Authentication | Use Case |
|------|----------------|----------|
| WPA2-Personal (PSK) | Pre-shared Key | Home/Small office |
| WPA2-Enterprise | 802.1X/RADIUS | Corporate networks |

**Security Level**: Strong (but vulnerable to KRACK attacks if unpatched)

```
WPA2-PSK Key Requirements:
- Minimum: 8 characters
- Maximum: 63 characters
- Recommended: 20+ characters (passphrase)
```

---

#### 2. WPA3 (Wi-Fi Protected Access 3)

**Released**: 2018
**Encryption**: AES-GCMP-256 (192-bit in Enterprise)
**Standard**: Latest Wi-Fi security standard

**Features**:
- **SAE (Simultaneous Authentication of Equals)**: Replaces 4-way handshake
- **Forward Secrecy**: Past sessions can't be decrypted if key is compromised
- **Protected Management Frames**: Prevents deauthentication attacks
- **Enhanced Open (OWE)**: Encryption even on open networks

**Modes**:
| Mode | Authentication | Encryption |
|------|----------------|------------|
| WPA3-Personal | SAE (Dragonfly) | AES-128/256 |
| WPA3-Enterprise | 802.1X/EAP | AES-256-GCMP |

**Key Improvements Over WPA2**:
| Feature | WPA2 | WPA3 |
|---------|------|------|
| Key Exchange | 4-Way Handshake | SAE (Dragonfly) |
| Offline Dictionary Attack | Vulnerable | Protected |
| Forward Secrecy | No | Yes |
| Min Encryption | 128-bit | 128/192/256-bit |
| Open Network Security | None | OWE (encrypted) |

---

#### Comparison Table

| Feature | WEP | WPA2 | WPA3 |
|---------|-----|------|------|
| **Year** | 1999 | 2004 | 2018 |
| **Encryption** | RC4 (40/104-bit) | AES-CCMP (128-bit) | AES-GCMP (128/256-bit) |
| **Key Exchange** | None (static) | 4-Way Handshake | SAE |
| **Security** | Broken | Strong | Strongest |
| **Forward Secrecy** | No | No | Yes |
| **Offline Attack Protection** | No | No | Yes |
| **Recommendation** | **Never use** | Good | Best |

---

#### Recommendation Summary

```
┌─────────────────────────────────────────────────────────┐
│              Wireless Security Recommendation           │
├─────────────────────────────────────────────────────────┤
│ ❌ WEP      - NEVER use (cracked in minutes)           │
│ ⚠️  WPA      - Avoid if possible (TKIP vulnerable)      │
│ ✓ WPA2     - Good for most cases (use long password)   │
│ ✓✓ WPA3     - Best choice (use if devices support it)  │
└─────────────────────────────────────────────────────────┘
```

**Best Practice**: Use **WPA3** if all devices support it, otherwise use **WPA2-AES** with a strong, long passphrase (16+ characters).

---

## Q2: Practical Questions (20 Marks)

---

## Option A: Caesar Cipher Encryption Program

### Concept

The **Caesar Cipher** is one of the oldest and simplest encryption techniques. It encrypts text by shifting each letter by a fixed number of positions in the alphabet.

#### How It Works

```
Plaintext:  HELLO
Shift (key): 3
Ciphertext: KHOOR

H → K (H + 3)
E → H (E + 3)
L → O (L + 3)
L → O (L + 3)
O → R (O + 3)
```

#### Encryption Formula

```
For uppercase letters:
    Cipher = (Plain - 'A' + key) % 26 + 'A'

For lowercase letters:
    Cipher = (Plain - 'a' + key) % 26 + 'a'
```

#### Decryption Formula

```
Plain = (Cipher - 'A' - key + 26) % 26 + 'A'
```

### Algorithm

```
FUNCTION caesarEncrypt(message, key):
    result = ""
    FOR each character c in message:
        IF c is uppercase letter:
            shifted = (c - 'A' + key) % 26
            result += (shifted + 'A')
        ELSE IF c is lowercase letter:
            shifted = (c - 'a' + key) % 26
            result += (shifted + 'a')
        ELSE:
            result += c  // Keep non-alphabetic characters unchanged
    RETURN result
```

### Time & Space Complexity

| Operation | Time | Space |
|-----------|------|-------|
| Encryption | O(n) | O(n) |
| Decryption | O(n) | O(n) |

Where n = length of message

### Worked Example

```
Plaintext:  "Attack at Dawn!"
Key:        5

Encryption:
A(0)  + 5 = F(5)
t(19) + 5 = y(24)
t(19) + 5 = y(24)
a(0)  + 5 = f(5)
c(2)  + 5 = h(7)
k(10) + 5 = p(15)
' '        = ' '
a(0)  + 5 = f(5)
t(19) + 5 = y(24)
' '        = ' '
D(3)  + 5 = I(8)
a(0)  + 5 = f(5)
w(22) + 5 = b(1)  [wrap: (22+5)%26 = 1]
n(13) + 5 = s(18)
!          = !

Ciphertext: "Fyyfhp fy Ifbs!"
```

---

## Option B: Data Link Layer Framing - Character Stuffing

### Concept

**Framing** is the process of organizing data into manageable units (frames) at the Data Link Layer. The receiver must identify where frames begin and end.

#### Character Stuffing (Byte Stuffing)

Used when frames are delimited by special flag characters.

**Common Delimiters**:
- **DLE** (Data Link Escape): Control character
- **STX** (Start of Text): Frame start marker
- **ETX** (End of Text): Frame end marker

**Problem**: What if the data contains the delimiter character (DLE)?

**Solution**: "Stuff" an extra DLE before any DLE in the data.

```
Original Data:  A B DLE C
Frame Format:   DLE STX <data> DLE ETX

Stuffed Frame:  DLE STX A B DLE DLE C DLE ETX
                          ↑stuffed
```

### Algorithm

```
FUNCTION characterStuff(data):
    frame = "DLE STX "
    FOR each character c in data:
        IF c == DLE:
            frame += "DLE DLE "  // Stuff extra DLE
        ELSE:
            frame += c + " "
    frame += "DLE ETX"
    RETURN frame

FUNCTION characterDestuff(frame):
    Remove "DLE STX" from beginning
    Remove "DLE ETX" from end
    result = ""
    i = 0
    WHILE i < length(frame):
        IF frame[i] == DLE AND frame[i+1] == DLE:
            result += DLE
            i += 2  // Skip stuffed DLE
        ELSE:
            result += frame[i]
            i += 1
    RETURN result
```

### Time & Space Complexity

| Operation | Time | Space |
|-----------|------|-------|
| Stuffing | O(n) | O(n) - worst case 2n |
| Destuffing | O(n) | O(n) |

### Worked Example

```
Original Data: "HELLO DLE WORLD"

Stuffing Process:
H     → H
E     → E
L     → L
L     → L
O     → O
(space) → (space)
DLE   → DLE DLE  (stuffed!)
(space) → (space)
W     → W
O     → O
R     → R
L     → L
D     → D

Stuffed Frame: [DLE STX] H E L L O   DLE DLE   W O R L D [DLE ETX]
                                    ↑ stuffed
```

---

## Option C: Star Topology in Packet Tracer

### Given Requirements

- **Topology**: Star
- **Number of PCs**: 5
- **IP Range**: 172.16.1.1 to 172.16.1.5
- **Subnet Mask**: 255.255.0.0 (/16)

### Network Design

```
                    [Switch]
                       │
        ┌──────┬───────┼───────┬──────┐
        │      │       │       │      │
      [PC0]  [PC1]   [PC2]   [PC3]  [PC4]
      .1     .2      .3      .4     .5
```

### IP Addressing Table

| Device | IP Address | Subnet Mask | Default Gateway |
|--------|------------|-------------|-----------------|
| PC0 | 172.16.1.1 | 255.255.0.0 | 172.16.1.254 |
| PC1 | 172.16.1.2 | 255.255.0.0 | 172.16.1.254 |
| PC2 | 172.16.1.3 | 255.255.0.0 | 172.16.1.254 |
| PC3 | 172.16.1.4 | 255.255.0.0 | 172.16.1.254 |
| PC4 | 172.16.1.5 | 255.255.0.0 | 172.16.1.254 |

### Packet Tracer Configuration Steps

#### Step 1: Add Devices

1. Open Cisco Packet Tracer
2. From **Network Devices** → **Switches**, drag a **2960 Switch**
3. From **End Devices**, drag **5 PCs** around the switch

#### Step 2: Connect Devices

1. Select **Connections** → **Copper Straight-Through** cable
2. Connect each PC's **FastEthernet0** port to switch ports:
   - PC0 → Switch Fa0/1
   - PC1 → Switch Fa0/2
   - PC2 → Switch Fa0/3
   - PC3 → Switch Fa0/4
   - PC4 → Switch Fa0/5

#### Step 3: Configure PC IP Addresses

For each PC (PC0 to PC4):

1. Click on PC
2. Go to **Desktop** tab
3. Click **IP Configuration**
4. Select **Static**
5. Enter IP configuration:

**PC0:**
```
IP Address:      172.16.1.1
Subnet Mask:     255.255.0.0
Default Gateway: 172.16.1.254
```

**PC1:**
```
IP Address:      172.16.1.2
Subnet Mask:     255.255.0.0
Default Gateway: 172.16.1.254
```

**PC2:**
```
IP Address:      172.16.1.3
Subnet Mask:     255.255.0.0
Default Gateway: 172.16.1.254
```

**PC3:**
```
IP Address:      172.16.1.4
Subnet Mask:     255.255.0.0
Default Gateway: 172.16.1.254
```

**PC4:**
```
IP Address:      172.16.1.5
Subnet Mask:     255.255.0.0
Default Gateway: 172.16.1.254
```

#### Step 4: Verify Configuration

1. Click on any PC
2. Go to **Desktop** → **Command Prompt**
3. Test connectivity:

```
C:\> ipconfig

IP Address:      172.16.1.1
Subnet Mask:     255.255.0.0
Default Gateway: 172.16.1.254

C:\> ping 172.16.1.2
Pinging 172.16.1.2 with 32 bytes of data:
Reply from 172.16.1.2: bytes=32 time<1ms TTL=128
Reply from 172.16.1.2: bytes=32 time<1ms TTL=128
...

C:\> ping 172.16.1.5
Pinging 172.16.1.5 with 32 bytes of data:
Reply from 172.16.1.5: bytes=32 time<1ms TTL=128
...
```

### Network Information

| Parameter | Value |
|-----------|-------|
| Network Address | 172.16.0.0 |
| Subnet Mask | 255.255.0.0 (/16) |
| Network Class | Class B (Private) |
| Total Hosts | 65,534 usable |
| Broadcast Address | 172.16.255.255 |
| IP Range Used | 172.16.1.1 - 172.16.1.5 |

---

> **Solution Code:** See `Slip_16_Q2_OptionA.c` (Caesar Cipher) and `Slip_16_Q2_OptionB.c` (Character Stuffing) in this folder.
