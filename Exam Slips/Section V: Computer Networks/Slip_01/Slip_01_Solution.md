# Slip 1 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) What is the purpose of a modem in a network? Can we connect directly to the internet without it?

A **MODEM** (Modulator-Demodulator) is a device that converts digital signals from computers into analog signals for transmission over telephone or cable lines (modulation) and converts incoming analog signals back to digital (demodulation).

**Purpose:**
- Enables communication between digital devices and analog transmission lines
- Allows internet connectivity through ISP networks
- Handles protocol conversion between different network types

**Can we connect without a modem?**
- **Yes**, in certain scenarios:
  - Direct fiber connection from ISP (already digital)
  - Mobile hotspot using cellular networks
  - Within local area networks (LAN) that don't need internet
  - Enterprise leased line connections
  
- **No**, when:
  - Using DSL or Cable internet services
  - Connecting through traditional telephone lines

---

### b) What is a MAC address and how is it different from an IP address?

**MAC Address (Media Access Control):**
- Hardware identifier burned into Network Interface Card (NIC)
- 48-bit address written as: `00:1A:2B:3C:4D:5E` (hexadecimal)
- First 3 bytes = Manufacturer ID (OUI)
- Last 3 bytes = Device-specific ID
- Used for local network communication (Layer 2 - Data Link)

**IP Address (Internet Protocol):**
- Logical software address assigned by network administrator or DHCP
- 32-bit (IPv4) or 128-bit (IPv6)
- Written as: `192.168.1.100` (dotted decimal for IPv4)
- Used for routing across networks (Layer 3 - Network)

**Key Differences:**

| Feature | MAC Address | IP Address |
|---------|-------------|------------|
| Layer | Data Link (L2) | Network (L3) |
| Type | Physical/Hardware | Logical/Software |
| Scope | Local network only | Global (routable) |
| Assignment | By manufacturer | By admin/DHCP |
| Change | Permanent (spoofable) | Can be changed |

---

### c) What is a loopback IP address? What is its range?

A **loopback address** is a special IP address that routes traffic back to the same computer for testing purposes without actually sending data to the network.

**Reserved Range:**
- **IPv4:** `127.0.0.0` to `127.255.255.255` (entire Class A block: 127.0.0.0/8)
- **Most commonly used:** `127.0.0.1` (mapped to hostname "localhost")
- **IPv6:** `::1`

**Purpose:**
- Test if TCP/IP stack is functioning properly
- Run and test applications locally without network hardware
- Inter-process communication on same host
- Verify network services are available

**Key Characteristic:**
- Packets sent to loopback **never leave the host** - they are immediately returned to the sending application

---

### d) Write the command to assign a static IP in Linux.

**Using `ip` command (temporary - cleared on reboot):**
```bash
sudo ip addr add 192.168.1.100/24 dev eth0
sudo ip route add default via 192.168.1.1
sudo ip link set eth0 up
```

**Permanent configuration using Netplan (Ubuntu 18.04+):**

Edit `/etc/netplan/01-netcfg.yaml`:
```yaml
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

Apply changes:
```bash
sudo netplan apply
```

**Using interfaces file (Debian/older Ubuntu):**

Edit `/etc/network/interfaces`:
```
auto eth0
iface eth0 inet static
    address 192.168.1.100
    netmask 255.255.255.0
    gateway 192.168.1.1
    dns-nameservers 8.8.8.8 8.8.4.4
```

Restart:
```bash
sudo systemctl restart networking
```

---

### f) Which online tool is used to check password strength?

Common online password strength checking tools:

| Tool | Website | Features |
|------|---------|----------|
| How Secure Is My Password | howsecureismypassword.net | Shows time to crack |
| Password Meter | passwordmeter.com | Detailed analysis |
| Kaspersky Password Checker | password.kaspersky.com | Security company tool |
| LastPass Password Generator | lastpass.com | Create & check passwords |
| NordPass Password Checker | nordpass.com | Checks breached passwords |

**What these tools evaluate:**
- Length (minimum 8-12 characters)
- Character variety (uppercase, lowercase, digits, symbols)
- Common patterns (dictionary words, sequences)
- Personal information (names, dates, common substitutions)
- Overall entropy (randomness)

**⚠️ Security Warning:** Never enter your actual password on untrusted websites. Use pattern-based testing instead.

---

### g) How to Use Nmap to Scan for Open Ports

**Nmap** is an open-source network discovery and security auditing tool used to map networks and discover open ports.

**Installation:**
```bash
# Ubuntu/Debian
sudo apt install nmap

# CentOS/RHEL
sudo yum install nmap
```

**Basic Scanning:**
```bash
# Scan single host
nmap 192.168.1.1

# Scan specific port
nmap -p 80 192.168.1.1

# Scan multiple ports
nmap -p 22,80,443 192.168.1.1

# Scan port range
nmap -p 1-1000 192.168.1.1

# Scan all ports
nmap -p- 192.168.1.1
```

**Common Scan Types:**
```bash
# TCP SYN scan (requires root)
sudo nmap -sS 192.168.1.1

# TCP Connect scan
nmap -sT 192.168.1.1

# Service version detection
nmap -sV 192.168.1.1

# OS detection (requires root)
sudo nmap -O 192.168.1.1

# Aggressive scan (all above)
nmap -A 192.168.1.1
```

**Sample Output:**
```
PORT     STATE  SERVICE  VERSION
22/tcp   open   ssh      OpenSSH 7.4
80/tcp   open   http     Apache 2.4.6
443/tcp  open   https    Apache 2.4.6
3306/tcp closed mysql
```

**Port States:**
- `open` - Service accepting connections
- `closed` - Port accessible but no service
- `filtered` - Firewall blocking probe

---

## Q2: Practical Questions (20 Marks)

### OPTION A: Data Link Layer Framing - Character & Bit Stuffing

**Problem:** Frame boundaries must be identified. Data may contain delimiter characters or bit patterns, causing errors.

#### Character Stuffing Method

**Delimiter Scheme:**
- Frame start: `DLE STX` (Data Link Escape + Start of Text)
- Frame end: `DLE ETX` (Data Link Escape + End of Text)
- Problem: What if data contains DLE?

**Solution:** Insert extra DLE before any DLE in the data.

**Example:**
```
Original data:     A, B, DLE, C
After stuffing:    A, B, DLE, DLE, C
                             ↑ inserted
Frame:             DLE STX A B DLE DLE C DLE ETX
```

**Receiver destuffing:** When DLE DLE is found, replace with single DLE.

#### Bit Stuffing Method

**Delimiter Scheme:**
- Flag: `01111110` (0x7E in hex)
- Problem: What if data contains six consecutive 1s?

**Solution:** After five consecutive 1s, insert a 0 bit.

**Example:**
```
Original data:  01111111
After stuffing: 01111101 1
                     ↑inserted 0
```

**Receiver destuffing:** After reading five consecutive 1s, skip the next 0 bit.

#### Algorithm Summary
1. **Encoding:** Scan data, insert stuffing when delimiter pattern found
2. **Transmission:** Send frame with added stuffing
3. **Reception:** Recognize frame delimiters (no stuffing)
4. **Decoding:** Remove stuffing to recover original data

---

### OPTION B: Password Strength Checker

**Objective:** Validate password security by checking multiple criteria.

**Criteria Evaluated:**

1. **Length Check:**
   - Weak: < 8 characters
   - Medium: 8-11 characters
   - Strong: 12-15 characters
   - Very Strong: 16+ characters

2. **Character Type Check:**
   - Uppercase letters (A-Z) ✓
   - Lowercase letters (a-z) ✓
   - Digits (0-9) ✓
   - Special characters (!@#$%^&*) ✓

3. **Pattern Detection:**
   - Avoid dictionary words
   - Avoid sequences (123, abc)
   - Avoid repeating characters (aaa, 111)

**Strength Scoring:**
```
Score 0-2: WEAK - Easy to crack
Score 3-4: MEDIUM - Reasonable security
Score 5-6: STRONG - Good security
Score 7+: VERY STRONG - Excellent security
```

**Example:**
- Password: `MyPassword123!`
- Length ≥ 8: ✓
- Has uppercase: ✓
- Has lowercase: ✓
- Has digit: ✓
- Has special: ✓
- Result: **STRONG** (5/5 criteria met)

---

### OPTION C: Subnetting in Cisco Packet Tracer

**Given Network:** 192.168.10.0/25 (Class C)

**Calculations:**

| Parameter | Value |
|-----------|-------|
| Network bits | 25 |
| Host bits | 32 - 25 = 7 |
| Subnet mask | 255.255.255.128 |
| Subnets | 2^(25-24) = 2 |
| Addresses per subnet | 2^7 = 128 |
| Usable hosts per subnet | 128 - 2 = 126 |

**Subnet Details:**

| Subnet | Network | First Host | Last Host | Broadcast |
|--------|---------|-----------|-----------|-----------|
| 0 | 192.168.10.0 | 192.168.10.1 | 192.168.10.126 | 192.168.10.127 |
| 1 | 192.168.10.128 | 192.168.10.129 | 192.168.10.254 | 192.168.10.255 |

**Packet Tracer Configuration Steps:**

1. **Create Topology:**
   - Drag 2 PCs and 1 Switch into workspace
   - Connect PCs to switch using copper straight-through cables

2. **Configure PC1:**
   - Right-click → Desktop → IP Configuration
   - IP Address: `192.168.1.10`
   - Subnet Mask: `255.255.255.0`
   - Default Gateway: `192.168.1.1`

3. **Configure PC2:**
   - Same settings but IP: `192.168.1.11`

4. **Verify Connectivity:**
   - Open Command Prompt on PC1
   - Type: `ping 192.168.1.11`
   - Success: PCs can communicate

---
