# Slip 11 — Computer Networks Solution Guide

## Q1: Theory Questions (10 Marks - Answer ANY 5)

---

### a) Compare and Contrast Switch vs Router

| Feature | Switch | Router |
|---------|--------|--------|
| **OSI Layer** | Layer 2 (Data Link) | Layer 3 (Network) |
| **Address Used** | MAC Address | IP Address |
| **Function** | Connects devices in same LAN | Connects different networks |
| **Broadcast Domain** | Single domain (all ports) | Separates broadcast domains |
| **Decision Basis** | MAC address table | Routing table |
| **Intelligence** | Less intelligent | More intelligent |
| **Speed** | Faster (hardware-based) | Slower (software-based) |
| **Cost** | Cheaper | More expensive |

**Key Differences:**
```
+--------+                    +--------+
| Switch |  Same Network      | Router |  Different Networks
+--------+  (LAN to LAN)      +--------+  (LAN to WAN)
    |                              |
  [MAC]                          [IP]
```

- **Switch**: Forwards frames based on MAC addresses within a single network
- **Router**: Forwards packets based on IP addresses between different networks
- Switches create collision domains; Routers create both collision and broadcast domains

---

### b) Purpose of Modem - Can We Connect Without It?

**What is a Modem?**
- **MO**dulator-**DEM**odulator
- Converts digital signals (computer) ↔ analog signals (telephone/cable line)

```
Computer ──[Digital]──> MODEM ──[Analog]──> ISP ──> Internet
           (0s and 1s)        (waves)
```

**Purpose:**
1. **Signal Conversion**: Translates digital computer data to analog signals for transmission
2. **Interface**: Acts as bridge between home network and ISP
3. **Synchronization**: Maintains timing between sender and receiver

**Can We Connect Without Modem?**

| Scenario | Modem Required? |
|----------|-----------------|
| DSL/Cable Internet | Yes |
| Fiber Optic (ONT provided) | No (ONT replaces modem) |
| Direct Ethernet from ISP | No |
| Mobile/4G/5G Data | No (phone has built-in modem) |
| Leased Line | No |

**Note**: With fiber optic, an ONT (Optical Network Terminal) performs similar function but for light signals.

---

### c) Types of Network Cables and Their Uses

| Cable Type | Category | Max Speed | Max Distance | Use Case |
|------------|----------|-----------|--------------|----------|
| **Coaxial** | RG-6, RG-59 | 10 Mbps | 500m | Cable TV, old Ethernet |
| **Twisted Pair (UTP)** | Cat5 | 100 Mbps | 100m | Basic networking |
| | Cat5e | 1 Gbps | 100m | Home/Office LAN |
| | Cat6 | 10 Gbps | 55m | High-speed LAN |
| | Cat6a | 10 Gbps | 100m | Data centers |
| | Cat7 | 10 Gbps | 100m | Enterprise networks |
| **Fiber Optic** | Single-mode | 100+ Gbps | 100+ km | Long distance, WAN |
| | Multi-mode | 10+ Gbps | 2 km | Data centers |

**Cable Diagrams:**
```
Twisted Pair (UTP/STP):          Coaxial:              Fiber Optic:
   ___/\/\/\___                  =========             ┌─────────┐
  /  insulation \                |  Core  |            │  Core   │
 |   conductor   |               | Dielec |            │ Cladding│
  \__/\/\/\____/                 | Shield |            │ Buffer  │
   pair twisted                  | Jacket |            │ Jacket  │
```

**Connector Types:**
- **RJ-45**: Twisted pair cables
- **BNC**: Coaxial cables  
- **SC/LC/ST**: Fiber optic cables

---

### d) IPv4 vs IPv6 - Definition and Key Differences

**IPv4 (Internet Protocol version 4)**
- 32-bit address scheme
- Format: Dotted decimal (192.168.1.1)
- Total addresses: ~4.3 billion (2³²)

**IPv6 (Internet Protocol version 6)**
- 128-bit address scheme
- Format: Hexadecimal (2001:0db8:85a3:0000:0000:8a2e:0370:7334)
- Total addresses: 3.4 × 10³⁸ (2¹²⁸)

| Feature | IPv4 | IPv6 |
|---------|------|------|
| **Address Length** | 32 bits | 128 bits |
| **Address Format** | Decimal (dotted) | Hexadecimal (colon) |
| **Address Space** | ~4.3 billion | 3.4 × 10³⁸ |
| **Header Size** | 20-60 bytes | 40 bytes (fixed) |
| **Checksum** | Yes | No (removed for efficiency) |
| **Security** | Optional (IPSec) | Built-in (IPSec mandatory) |
| **NAT Required** | Yes (due to shortage) | No |
| **Broadcast** | Supported | Replaced by multicast |
| **Configuration** | Manual/DHCP | Auto-configuration (SLAAC) |

**Address Examples:**
```
IPv4: 192.168.1.100
      └─┬─┘ └┬┘ └┬┘ └┬┘
      Network  .  Host

IPv6: 2001:0db8:85a3:0000:0000:8a2e:0370:7334
      └────────┬────────┘ └─────────┬─────────┘
         Network Prefix        Interface ID
```

---

### f) Subnetting - Hosts in /26 Subnet

**What is Subnetting?**
- Process of dividing a large network into smaller sub-networks (subnets)
- Improves network efficiency, security, and management
- Uses subnet mask to determine network and host portions

**Benefits:**
1. Reduces broadcast traffic
2. Improves network security
3. Better IP address management
4. Isolates network problems

**Calculating Hosts in /26 Subnet:**

```
/26 means 26 bits for network, 6 bits for hosts

Subnet Mask: 255.255.255.192
Binary:      11111111.11111111.11111111.11000000
             └────────── 26 bits ──────────┘└ 6 ┘
                    Network              Host

Host bits = 32 - 26 = 6 bits

Total addresses = 2⁶ = 64
Usable hosts = 2⁶ - 2 = 62 hosts
```

**Why subtract 2?**
- 1 address for **Network ID** (all host bits = 0)
- 1 address for **Broadcast** (all host bits = 1)

| Subnet Size | Host Bits | Total Addresses | Usable Hosts |
|-------------|-----------|-----------------|--------------|
| /24 | 8 | 256 | 254 |
| /25 | 7 | 128 | 126 |
| /26 | 6 | 64 | **62** |
| /27 | 5 | 32 | 30 |
| /28 | 4 | 16 | 14 |

---

### g) Purpose of Assigning Hostname to a Switch

**What is a Hostname?**
- Unique identifier/name assigned to a network device
- Default hostname on Cisco switches is "Switch"

**Purposes:**
1. **Device Identification**: Easily identify devices in large networks
2. **Management**: Simplifies administration and troubleshooting
3. **Documentation**: Clear network documentation
4. **Security**: Part of security best practices
5. **Command Prompt Display**: Shows in CLI prompt for clarity

**Configuration Example (Cisco IOS):**
```
Switch> enable
Switch# configure terminal
Switch(config)# hostname LAB-SWITCH-01
LAB-SWITCH-01(config)#
```

**Naming Convention Best Practices:**
```
Format: LOCATION-TYPE-NUMBER
Example: NYC-SW-01

NYC     = Location (New York City)
SW      = Device Type (Switch)
01      = Sequential Number
```

**Benefits in Large Networks:**
```
Without Hostname:              With Hostname:
Switch#                        FLOOR1-SWITCH-01#
Switch#                        FLOOR2-SWITCH-01#
Switch#                        SERVER-ROOM-SW#
(Which is which?)              (Clear identification!)
```

---

## Q2: Practical Options (20 Marks)

---

## Option A: Character Count Method (Framing)

### Concept
**Framing** is the process of dividing a stream of bits into manageable frames at the Data Link Layer.

**Character Count Method:**
- First byte of each frame contains the count of characters in the frame
- Count includes the count byte itself
- Simple but vulnerable to count field errors

### How It Works
```
Original Data: HELLO WORLD

Frame 1: [6] H E L L O    (6 characters including count)
Frame 2: [6] W O R L D    (6 characters including count)
         ↑
    Character Count
```

### Diagram
```
Before Framing:
┌─────────────────────────────────────┐
│ H E L L O   W O R L D               │ (Raw data stream)
└─────────────────────────────────────┘

After Framing (Character Count):
┌───┬───────────┐ ┌───┬───────────┐
│ 6 │ H E L L O │ │ 6 │ W O R L D │
└───┴───────────┘ └───┴───────────┘
  ↑ Count Field     ↑ Count Field
```

### Algorithm
```
FRAMING:
1. Read input data
2. Set frame size (e.g., 5 data chars + 1 count = 6)
3. For each frame:
   a. Calculate total count (data + 1)
   b. Insert count as first byte
   c. Copy data bytes
4. Transmit framed data

DEFRAMING:
1. Read count byte
2. Extract (count - 1) data bytes
3. Repeat until end of transmission
```

### Advantages & Disadvantages
| Advantages | Disadvantages |
|------------|---------------|
| Simple implementation | Single bit error in count corrupts synchronization |
| Low overhead | Hard to resynchronize after error |
| No special characters needed | Receiver loses frame boundaries |

### See: `Slip_11_Q2_OptionA.c`

---

## Option B: Stop-and-Wait ARQ Protocol

### Concept
**ARQ (Automatic Repeat reQuest)** is an error control method using acknowledgments and timeouts.

**Stop-and-Wait ARQ:**
- Sender transmits ONE frame and WAITS for acknowledgment
- If ACK received → send next frame
- If timeout → retransmit same frame
- Simplest form of ARQ

### Protocol Operation
```
Sender                              Receiver
  |                                    |
  |-------- Frame 0 ------------------>|
  |                                    | ✓ Receive
  |<-------- ACK 0 --------------------|
  |                                    |
  |-------- Frame 1 ------------------>|
  |              X (Lost)              |
  |         [TIMEOUT]                  |
  |-------- Frame 1 ------------------>| (Retransmit)
  |                                    | ✓ Receive
  |<-------- ACK 1 --------------------|
```

### State Diagram
```
        ┌─────────────────────────────────┐
        │                                 │
        ▼                                 │
  ┌──────────┐    Send Frame     ┌────────────┐
  │   IDLE   │ ───────────────→  │  WAITING   │
  └──────────┘                   └────────────┘
        ▲                              │
        │         ACK Received         │
        │          (Success)           │
        └──────────────────────────────┘
                      │
              Timeout │
              (Retry) │
                      ▼
                ┌──────────┐
                │ RETRANS  │
                └──────────┘
```

### Algorithm
```
SENDER:
1. seq_num = 0
2. While data to send:
   a. Create frame with seq_num
   b. Send frame, start timer
   c. Wait for ACK or timeout:
      - If ACK received with correct seq:
        * Stop timer
        * seq_num = 1 - seq_num (toggle)
        * Get next data
      - If timeout:
        * Retransmit same frame
3. End transmission

RECEIVER:
1. expected_seq = 0
2. While receiving:
   a. Receive frame
   b. If seq_num matches expected:
      * Process data
      * Send ACK with seq_num
      * expected_seq = 1 - expected_seq
   c. Else:
      * Discard duplicate
      * Resend previous ACK
```

### Sequence Number Handling
```
Only 2 sequence numbers needed: 0 and 1

Frame 0 → ACK 0 → Frame 1 → ACK 1 → Frame 0 → ACK 0 → ...
```

### Efficiency Calculation
```
Efficiency = Transmission Time / (Transmission Time + 2 × Propagation Delay)

η = Tt / (Tt + 2Tp) = 1 / (1 + 2a)

where a = Tp/Tt (propagation to transmission ratio)
```

### Advantages & Disadvantages
| Advantages | Disadvantages |
|------------|---------------|
| Simple to implement | Low efficiency (especially for high-latency links) |
| Low buffer requirements | Link utilization poor |
| Reliable delivery | One frame at a time |
| Error detection & recovery | Long delays in high-latency networks |

### See: `Slip_11_Q2_OptionB.c`

---

## Option C: Cisco Switch Initial Configuration (Packet Tracer)

### Configuration Steps

**1. Access Switch CLI:**
```
Switch>
```

**2. Enter Privileged EXEC Mode:**
```
Switch> enable
Switch#
```

**3. Enter Global Configuration Mode:**
```
Switch# configure terminal
Switch(config)#
```

**4. Set Hostname:**
```
Switch(config)# hostname LAB-SWITCH
LAB-SWITCH(config)#
```

**5. Configure Privileged EXEC Mode Password:**
```
LAB-SWITCH(config)# enable secret MySecretPass123
```
Note: `enable secret` encrypts the password using MD5

**6. Configure VTY Lines (Virtual Terminal for Telnet/SSH):**
```
LAB-SWITCH(config)# line vty 0 15
LAB-SWITCH(config-line)# password VTYPass123
LAB-SWITCH(config-line)# login
LAB-SWITCH(config-line)# exit
```

**7. (Optional) Encrypt All Passwords:**
```
LAB-SWITCH(config)# service password-encryption
```

**8. Save Configuration:**
```
LAB-SWITCH(config)# exit
LAB-SWITCH# copy running-config startup-config
```

### Complete Configuration Script:
```cisco
enable
configure terminal
hostname LAB-SWITCH
enable secret PrivExecPass123
line vty 0 15
password VTYLinePass456
login
exit
service password-encryption
banner motd # Unauthorized Access Prohibited! #
exit
copy running-config startup-config
```

### Verification Commands:
```
LAB-SWITCH# show running-config
LAB-SWITCH# show startup-config
```

### Configuration Diagram:
```
┌─────────────────────────────────────────────┐
│              SWITCH SECURITY                │
├─────────────────────────────────────────────┤
│                                             │
│  Console ──→ [ Console Password ]           │
│                                             │
│  Telnet/SSH ──→ [ VTY Password ]            │
│  (Remote)       (line vty 0 15)             │
│                                             │
│  Privileged Mode ──→ [ Enable Secret ]      │
│  (Switch# prompt)                           │
│                                             │
└─────────────────────────────────────────────┘
```

---

## Summary of Concepts

| Topic | Key Point |
|-------|-----------|
| Switch vs Router | Layer 2 vs Layer 3, MAC vs IP |
| Modem | Digital ↔ Analog conversion |
| Network Cables | UTP, Coaxial, Fiber - various speeds/distances |
| IPv4 vs IPv6 | 32-bit vs 128-bit, address exhaustion solution |
| Subnetting | Divide networks, /26 = 62 usable hosts |
| Hostname | Device identification in network |
| Character Count | Frame size in first byte |
| Stop-and-Wait ARQ | Send one frame, wait for ACK |

---

## Compilation Commands

```bash
# Option A - Character Count Framing
gcc -o framing Slip_11_Q2_OptionA.c
./framing

# Option B - Stop-and-Wait ARQ
gcc -o arq Slip_11_Q2_OptionB.c
./arq
```
