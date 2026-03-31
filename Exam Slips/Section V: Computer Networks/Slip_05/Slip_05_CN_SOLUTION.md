# Slip 5 — Computer Networks Solution Guide

## Q1: Theory Questions (10 marks - Any 5)

---

### a) What does the `ip link set eth0 up` command do?

**Answer:**
This command activates/enables the network interface named `eth0`.

**Detailed Explanation:**
| Component | Description |
|-----------|-------------|
| `ip` | Modern Linux networking utility (replaces ifconfig) |
| `link` | Subcommand to manage network device properties |
| `set` | Modify device attributes |
| `eth0` | Target interface name (first Ethernet adapter) |
| `up` | Enable/activate the interface |

**Effects:**
- Changes interface state from DOWN to UP
- Enables the interface to send/receive packets
- Allows IP configuration to be applied
- Triggers link detection on physical ports

**Related Commands:**
```bash
# Disable interface
ip link set eth0 down

# Check interface status
ip link show eth0

# Legacy equivalent (deprecated)
ifconfig eth0 up
```

---

### b) How to detect hidden Wi-Fi networks

**Answer:**
Hidden Wi-Fi networks don't broadcast their SSID but can still be detected through active scanning and monitoring.

**Detection Methods:**

**1. Using `iwlist` (Linux):**
```bash
sudo iwlist wlan0 scan | grep -i "essid"
# Hidden networks show as ESSID:""
```

**2. Using `airodump-ng` (Kali Linux):**
```bash
# Put interface in monitor mode
sudo airmon-ng start wlan0
# Scan for networks
sudo airodump-ng wlan0mon
# Hidden networks appear with <length: X> instead of SSID
```

**3. De-authentication Attack (captures SSID when client reconnects):**
```bash
# Force client reconnection to reveal SSID
sudo aireplay-ng -0 5 -a <BSSID> wlan0mon
```

**4. Windows Method:**
```
netsh wlan show networks mode=bssid
```

**Key Indicators of Hidden Networks:**
- Empty SSID field in scan results
- Beacon frames with zero-length SSID
- Valid BSSID (MAC address) present

---

### c) Command sequence to configure a router interface with IP

**Answer:**
Configuration in Cisco IOS:

```
Router> enable
Router# configure terminal
Router(config)# interface GigabitEthernet0/0
Router(config-if)# ip address 192.168.1.1 255.255.255.0
Router(config-if)# no shutdown
Router(config-if)# description "LAN Interface"
Router(config-if)# exit
Router(config)# exit
Router# copy running-config startup-config
```

**Step-by-Step Breakdown:**

| Step | Command | Purpose |
|------|---------|---------|
| 1 | `enable` | Enter privileged EXEC mode |
| 2 | `configure terminal` | Enter global configuration mode |
| 3 | `interface GigabitEthernet0/0` | Select the interface |
| 4 | `ip address <IP> <mask>` | Assign IP address |
| 5 | `no shutdown` | Enable the interface |
| 6 | `description` | Add interface description |
| 7 | `copy run start` | Save configuration |

**Verification Commands:**
```
show ip interface brief
show interface GigabitEthernet0/0
show running-config interface GigabitEthernet0/0
```

---

### d) Purpose of assigning a hostname to a switch

**Answer:**
Assigning a hostname to a switch provides identification and management benefits.

**Purposes:**

| Purpose | Description |
|---------|-------------|
| **Identification** | Distinguishes devices in large networks |
| **Management** | Easier remote administration |
| **Documentation** | Self-documenting network topology |
| **Security** | Identifies unauthorized devices |
| **Troubleshooting** | Quick device identification in logs |
| **Prompt Display** | Shows current device in CLI |

**Configuration:**
```
Switch> enable
Switch# configure terminal
Switch(config)# hostname SW-FLOOR1
SW-FLOOR1(config)# exit
```

**Naming Conventions (Best Practices):**
- `LOC-TYPE-NUM` format (e.g., NYC-SW-01)
- Include location, device type, and number
- Avoid spaces and special characters
- Use uppercase for consistency

---

### f) What is Ethical Hacking?

**Answer:**
**Ethical Hacking** (also called Penetration Testing or White Hat Hacking) is the authorized practice of bypassing system security to identify vulnerabilities.

**Definition:**
Legal and authorized attempt to break into computer systems and networks to find security weaknesses before malicious hackers exploit them.

**Key Characteristics:**

| Aspect | Description |
|--------|-------------|
| **Authorization** | Written permission from owner required |
| **Purpose** | Improve security, not cause damage |
| **Reporting** | All findings documented and reported |
| **Legal** | Conducted within legal boundaries |
| **Scope** | Defined target systems and timeframe |

**Types of Ethical Hackers:**
1. **White Hat** - Authorized security professionals
2. **Gray Hat** - May work without permission but report vulnerabilities
3. **Bug Bounty Hunters** - Find bugs for rewards

**Phases of Ethical Hacking:**
```
1. Reconnaissance    → Information gathering
2. Scanning          → Port/vulnerability scanning
3. Gaining Access    → Exploit vulnerabilities
4. Maintaining Access→ Establish persistence
5. Covering Tracks   → Clear evidence (test detection)
6. Reporting         → Document all findings
```

**Tools Used:**
- Nmap, Wireshark, Metasploit, Burp Suite, Kali Linux

---

### g) What does the `show running-config` command display?

**Answer:**
Displays the current active configuration stored in RAM on Cisco devices.

**Information Displayed:**

| Section | Details |
|---------|---------|
| **Hostname** | Device name |
| **Passwords** | Enable, console, VTY passwords |
| **Interfaces** | IP addresses, states, descriptions |
| **Routing** | Static routes, routing protocols |
| **VLANs** | VLAN configurations |
| **ACLs** | Access control lists |
| **Services** | DHCP, NAT, QoS settings |

**Sample Output:**
```
Router# show running-config
Building configuration...

Current configuration : 1234 bytes
!
hostname Router1
!
enable secret 5 $1$mERr$hash
!
interface GigabitEthernet0/0
 ip address 192.168.1.1 255.255.255.0
 no shutdown
!
ip route 0.0.0.0 0.0.0.0 192.168.1.254
!
line vty 0 4
 password cisco
 login
!
end
```

**Related Commands:**
| Command | Description |
|---------|-------------|
| `show startup-config` | Shows saved config in NVRAM |
| `show running-config | section interface` | Filter specific section |
| `copy running-config startup-config` | Save running to startup |

**Key Difference:**
- `running-config` = Active in RAM (volatile)
- `startup-config` = Saved in NVRAM (persistent)

---

## Q2: Programming/Practical (20 marks)

---

### Option A: Ring Topology Display Program

**Concept:**
Ring topology connects each device to exactly two other devices, forming a circular data path.

**Characteristics:**
| Feature | Description |
|---------|-------------|
| **Structure** | Circular arrangement |
| **Data Flow** | Unidirectional or bidirectional |
| **Token Passing** | Used for access control |
| **Failure Impact** | Single point can break entire ring |

**Diagram:**
```
    Node 0
   ↗      ↘
Node 3    Node 1
   ↖      ↙
    Node 2
```

**Algorithm:**
```
1. Get number of nodes
2. Create adjacency matrix:
   - Node i connects to Node (i+1) % n
   - Node i connects to Node (i-1+n) % n
3. Display connections
4. Visualize ring structure
```

**Pseudocode:**
```
FUNCTION createRingTopology(n):
    FOR i = 0 TO n-1:
        next = (i + 1) MOD n
        prev = (i - 1 + n) MOD n
        adj[i][next] = 1
        adj[i][prev] = 1
    
FUNCTION displayConnections(n):
    FOR each node i:
        PRINT "Node", i, "connects to:"
        FOR each node j:
            IF adj[i][j] = 1:
                PRINT "Node", j
```

> **Solution Code:** See `Slip_05_Q2_OptionA.c`

---

### Option B: Odd Parity Error Detection

**Concept:**
Parity checking is a simple error detection method that adds an extra bit to make the total number of 1s either odd (odd parity) or even (even parity).

**Odd Parity:**
- The parity bit is set so that total number of 1s (including parity) is **ODD**

**Example:**
```
Data: 1010001 (three 1s - odd)
Odd Parity Bit: 0 (to keep count odd)
Transmitted: 10100010

Data: 1010101 (four 1s - even)
Odd Parity Bit: 1 (to make count odd)
Transmitted: 10101011
```

**Algorithm:**
```
SENDER SIDE:
1. Count number of 1s in data
2. If count is even, parity bit = 1
3. If count is odd, parity bit = 0
4. Append parity bit to data

RECEIVER SIDE:
1. Count number of 1s including parity bit
2. If count is odd → No error detected
3. If count is even → Error detected!
```

**Pseudocode:**
```
FUNCTION countOnes(data, size):
    count = 0
    FOR i = 0 TO size-1:
        IF data[i] = 1:
            count = count + 1
    RETURN count

FUNCTION calculateOddParity(data, size):
    ones = countOnes(data, size)
    IF ones MOD 2 = 0:    // Even number of 1s
        RETURN 1          // Add 1 to make odd
    ELSE:
        RETURN 0          // Already odd

FUNCTION checkOddParity(received, size):
    ones = countOnes(received, size)  // Including parity bit
    IF ones MOD 2 = 1:
        PRINT "No error detected"
    ELSE:
        PRINT "Error detected!"
```

**Worked Example:**
```
Original Data: 1 0 1 1 0 0 1
Count of 1s: 4 (even)
Parity Bit: 1 (to make total 5, which is odd)
Transmitted: 1 0 1 1 0 0 1 | 1

Case 1 - No Error:
Received: 1 0 1 1 0 0 1 1
Count of 1s: 5 (odd) → No error

Case 2 - Single Bit Error:
Received: 1 0 0 1 0 0 1 1  (3rd bit flipped)
Count of 1s: 4 (even) → Error detected!
```

**Limitations:**
- Detects only odd number of bit errors
- Cannot detect even number of bit errors
- Cannot correct errors

> **Solution Code:** See `Slip_05_Q2_OptionB.c`

---

### Option C: Packet Tracer - Switch Configuration

**Objective:**
Configure 2 PCs through a switch with IP addresses 10.0.0.1 and 10.0.0.2

**Steps:**

**1. Add Devices:**
- 1 × Switch (2960)
- 2 × PC

**2. Connect Devices:**
```
PC0 ----[Fa0/1]---- Switch ----[Fa0/2]---- PC1
      Straight-through         Straight-through
```

**3. Configure PC0:**
```
Click PC0 → Desktop → IP Configuration
IP Address: 10.0.0.1
Subnet Mask: 255.0.0.0
```

**4. Configure PC1:**
```
Click PC1 → Desktop → IP Configuration
IP Address: 10.0.0.2
Subnet Mask: 255.0.0.0
```

**5. Test Connectivity:**
```
PC0 → Desktop → Command Prompt
C:\> ping 10.0.0.2

Pinging 10.0.0.2 with 32 bytes of data:
Reply from 10.0.0.2: bytes=32 time<1ms TTL=128
Reply from 10.0.0.2: bytes=32 time<1ms TTL=128
Reply from 10.0.0.2: bytes=32 time<1ms TTL=128
Reply from 10.0.0.2: bytes=32 time<1ms TTL=128

Ping statistics for 10.0.0.2:
    Packets: Sent = 4, Received = 4, Lost = 0 (0% loss)
```

**Cable Testing with NSS-468A LAN Tester:**
| Test | Indicator | Meaning |
|------|-----------|---------|
| All LEDs 1-8 green sequentially | Good | Cable properly wired |
| Missing LED | Bad | Open/broken wire |
| Out of sequence | Bad | Crossed wires |

---

> **Solution Files:**
> - `Slip_05_Q2_OptionA.c` - Ring Topology C Program
> - `Slip_05_Q2_OptionB.c` - Odd Parity Error Detection Program
