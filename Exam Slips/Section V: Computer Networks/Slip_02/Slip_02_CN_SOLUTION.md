# Slip 2 — Computer Networks Solution Guide

## Q1: Theory Questions (Answer ANY 5) — 10 Marks

---

### a) What is the functional difference between a switch and a router?

| Feature | Switch | Router |
|---------|--------|--------|
| **OSI Layer** | Layer 2 (Data Link) | Layer 3 (Network) |
| **Addressing** | Uses MAC addresses | Uses IP addresses |
| **Function** | Connects devices within same LAN | Connects different networks |
| **Broadcast Domain** | Single broadcast domain | Separates broadcast domains |
| **Packet Routing** | Forwards frames within network | Routes packets between networks |
| **Intelligence** | Limited to local segment | Path selection, NAT, filtering |

**Key Difference:**
- **Switch**: Operates within a single network, forwarding data based on MAC addresses
- **Router**: Operates between networks, forwarding data based on IP addresses and routing tables

```
[PC1]---[PC2]                    [Network A]
    \   /                             |
   [SWITCH] ← Same Network    [ROUTER] ← Between Networks
    /   \                             |
[PC3]---[PC4]                    [Network B]
```

---

### b) How many hosts are possible in a /26 subnet?

**Calculation:**
```
/26 means: 26 bits for network, 6 bits for hosts

Host bits = 32 - 26 = 6 bits

Total addresses = 2^6 = 64 addresses

Usable hosts = 64 - 2 = 62 hosts
```

**Why subtract 2?**
1. **Network Address**: First address (all host bits = 0)
2. **Broadcast Address**: Last address (all host bits = 1)

**Example with 192.168.1.0/26:**
| Component | Address |
|-----------|---------|
| Network Address | 192.168.1.0 |
| First Usable | 192.168.1.1 |
| Last Usable | 192.168.1.62 |
| Broadcast | 192.168.1.63 |
| **Usable Hosts** | **62** |

---

### c) What are the differences between Cat5e, Cat6, and Cat7 Ethernet cables?

| Feature | Cat5e | Cat6 | Cat7 |
|---------|-------|------|------|
| **Speed** | 1 Gbps | 10 Gbps | 10+ Gbps |
| **Bandwidth** | 100 MHz | 250 MHz | 600 MHz |
| **Max Distance (10G)** | Not supported | 55 meters | 100 meters |
| **Shielding** | UTP (Unshielded) | UTP or STP | STP (Shielded) |
| **Crosstalk Protection** | Basic | Improved | Excellent |
| **Connector** | RJ-45 | RJ-45 | GG45 or TERA |
| **Cost** | Lowest | Medium | Highest |
| **Use Case** | Home/Small office | Enterprise LAN | Data centers |

**Visual Comparison:**
```
Cat5e:  ════════  (Basic, 1Gbps, Budget-friendly)
Cat6:   ══▓▓══    (Better shielding, 10Gbps@55m)
Cat7:   ▓▓▓▓▓▓▓▓  (Full shielding, 10Gbps@100m)
```

---

### d) Write the steps to identify a phishing email

**Step-by-Step Detection Process:**

```
┌─────────────────────────────────────────────┐
│         PHISHING EMAIL DETECTION            │
├─────────────────────────────────────────────┤
│ 1. CHECK SENDER ADDRESS                     │
│    • Look for misspellings                  │
│    • Verify domain (amaz0n.com vs amazon)   │
│                                             │
│ 2. EXAMINE THE GREETING                     │
│    • Generic: "Dear Customer" = Suspicious  │
│    • Personal name = More likely legitimate │
│                                             │
│ 3. INSPECT LINKS (HOVER, DON'T CLICK)       │
│    • URL doesn't match displayed text       │
│    • Shortened URLs hiding destination      │
│                                             │
│ 4. LOOK FOR URGENCY/THREATS                 │
│    • "Account suspended in 24 hours!"       │
│    • "Verify immediately or lose access"    │
│                                             │
│ 5. CHECK FOR SPELLING/GRAMMAR ERRORS        │
│    • Professional companies proofread       │
│                                             │
│ 6. VERIFY ATTACHMENTS                       │
│    • Unexpected .exe, .zip, .doc files      │
│    • Don't open suspicious attachments      │
│                                             │
│ 7. CROSS-CHECK WITH OFFICIAL CHANNELS       │
│    • Contact company directly               │
│    • Don't use contact info from email      │
└─────────────────────────────────────────────┘
```

**Red Flags Summary:**
- Mismatched sender domain
- Generic greeting
- Suspicious links/URLs
- Urgent language
- Poor grammar
- Unexpected attachments
- Requests for personal info

---

### f) What are the two analysis methods used for analyzing malware?

**1. Static Analysis**
```
┌────────────────────────────────────┐
│       STATIC ANALYSIS              │
├────────────────────────────────────┤
│ • Examines code WITHOUT executing  │
│ • Analyzes file structure          │
│ • Checks signatures & patterns     │
│ • Reviews strings in binary        │
│ • Disassembles executable          │
├────────────────────────────────────┤
│ Tools: IDA Pro, Strings, PEiD      │
│ Pros: Safe, fast, no infection     │
│ Cons: Can't detect runtime behavior│
└────────────────────────────────────┘
```

**2. Dynamic Analysis**
```
┌────────────────────────────────────┐
│       DYNAMIC ANALYSIS             │
├────────────────────────────────────┤
│ • Executes malware in sandbox      │
│ • Monitors runtime behavior        │
│ • Tracks system calls              │
│ • Observes network connections     │
│ • Records file modifications       │
├────────────────────────────────────┤
│ Tools: Cuckoo, Wireshark, ProcMon  │
│ Pros: Sees actual behavior         │
│ Cons: Risk of infection, evasion   │
└────────────────────────────────────┘
```

**Comparison Table:**
| Aspect | Static Analysis | Dynamic Analysis |
|--------|----------------|------------------|
| Execution | No | Yes (in sandbox) |
| Safety | Very Safe | Controlled risk |
| Speed | Fast | Slower |
| Obfuscation | Can be fooled | Reveals true behavior |
| Environment | Any | Requires sandbox |

---

### g) What is the use of the ping command in networking?

**Purpose:** Tests connectivity between two network devices using ICMP protocol.

**Syntax:**
```bash
ping [options] <destination>
ping 192.168.1.1        # Ping IP address
ping google.com         # Ping hostname
ping -c 4 8.8.8.8       # Send 4 packets (Linux)
ping -n 4 8.8.8.8       # Send 4 packets (Windows)
```

**What Ping Tells You:**
```
$ ping google.com
PING google.com (142.250.190.78): 56 bytes
64 bytes from 142.250.190.78: icmp_seq=1 ttl=117 time=12.3 ms
64 bytes from 142.250.190.78: icmp_seq=2 ttl=117 time=11.8 ms
64 bytes from 142.250.190.78: icmp_seq=3 ttl=117 time=12.1 ms

--- google.com ping statistics ---
3 packets transmitted, 3 received, 0% packet loss
round-trip min/avg/max = 11.8/12.1/12.3 ms
```

**Key Information:**
| Metric | Meaning |
|--------|---------|
| **Reply** | Host is reachable |
| **TTL** | Time To Live (hop count) |
| **Time** | Round-trip time (latency) |
| **Packet Loss** | Network reliability |
| **icmp_seq** | Sequence number |

**Use Cases:**
1. **Test if host is online**
2. **Measure network latency**
3. **Diagnose connectivity issues**
4. **Verify DNS resolution**
5. **Check network reliability**

---

## Q2: Practical Options — 20 Marks

---

## Option A: Simple Hash Simulation (C Program)

### Concept
A **hash function** converts data of arbitrary size into a fixed-size value. Used in:
- Data integrity verification
- Password storage
- Hash tables/dictionaries

### Algorithm (Simple Additive Hash)
```
FUNCTION simpleHash(data, tableSize):
    hash = 0
    FOR each character c in data:
        hash = hash + ASCII_value(c)
    RETURN hash MOD tableSize
```

### How It Works
```
Input: "HELLO"
H = 72, E = 69, L = 76, L = 76, O = 79

Sum = 72 + 69 + 76 + 76 + 79 = 372

If tableSize = 10:
Hash = 372 % 10 = 2
```

### Collision Handling
When two keys produce same hash:
1. **Chaining**: Store multiple items in linked list
2. **Linear Probing**: Find next empty slot

### Time & Space Complexity
| Operation | Complexity |
|-----------|-----------|
| Hash Calculation | O(n) where n = string length |
| Insert (avg) | O(1) |
| Search (avg) | O(1) |
| Space | O(m) where m = table size |

> **Code:** See `Slip_02_Q2_OptionA.c`

---

## Option B: Character Count Framing (C Program)

### Concept
In data link layer, **framing** divides data into manageable units called frames.

**Character Count Method:**
- First byte of each frame indicates frame length
- Receiver uses count to determine frame boundaries

### Algorithm
```
FUNCTION frameData(data):
    frameSize = LENGTH(data) + 1  // +1 for count byte
    frame[0] = frameSize
    FOR i = 0 TO LENGTH(data)-1:
        frame[i+1] = data[i]
    RETURN frame

FUNCTION extractFrame(stream, position):
    count = stream[position]
    data = stream[position+1 TO position+count-1]
    nextPosition = position + count
    RETURN data, nextPosition
```

### Visualization
```
Data: "ABC" "DE" "FGHI"

Framed Stream:
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
│ 4 │ A │ B │ C │ 3 │ D │ E │ 5 │ F │ G │ H │ I │
└───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
  ↑               ↑           ↑
  Frame 1 (4)     Frame 2 (3) Frame 3 (5)
```

### Advantages & Disadvantages
| Advantages | Disadvantages |
|------------|---------------|
| Simple to implement | Error propagation |
| Efficient processing | Single bit error corrupts all subsequent frames |
| No special characters needed | Limited frame size (count byte) |

### Time Complexity
| Operation | Complexity |
|-----------|-----------|
| Framing | O(n) |
| Deframing | O(n) |

> **Code:** See `Slip_02_Q2_OptionB.c`

---

## Option C: Packet Tracer Configuration

### Subnetting 192.168.10.0/26

**Subnet Details:**
```
Network: 192.168.10.0/26
Subnet Mask: 255.255.255.192

Subnets Available: 4
Hosts per Subnet: 62
```

| Subnet | Network Address | Usable Range | Broadcast |
|--------|-----------------|--------------|-----------|
| 1 | 192.168.10.0 | .1 - .62 | 192.168.10.63 |
| 2 | 192.168.10.64 | .65 - .126 | 192.168.10.127 |
| 3 | 192.168.10.128 | .129 - .190 | 192.168.10.191 |
| 4 | 192.168.10.192 | .193 - .254 | 192.168.10.255 |

### PC Configuration Steps

**Configure PC with:**
- IP: 192.168.2.10
- Mask: 255.255.255.0
- Gateway: 192.168.2.1

**Steps in Packet Tracer:**
```
1. Click on PC icon
2. Go to Desktop tab → IP Configuration
3. Select "Static"
4. Enter:
   - IP Address: 192.168.2.10
   - Subnet Mask: 255.255.255.0
   - Default Gateway: 192.168.2.1
5. Close configuration window
```

**Verification Commands (on PC):**
```
C:\> ipconfig
C:\> ping 192.168.2.1    (Test gateway)
```

---

> **Solution Code:** See `Slip_02_Q2_OptionA.c` and `Slip_02_Q2_OptionB.c` in this folder.
