# Slip 1 — Computer Networks Solution Guide

## Q1: Theory Questions (10 Marks - Answer ANY 5)

---

### a) What is the purpose of a modem in a network? Can we connect directly to the internet without it?

#### Concept
A **MODEM** (Modulator-Demodulator) is a hardware device that converts digital signals from a computer into analog signals for transmission over telephone lines (modulation) and vice versa (demodulation).

#### Purpose of a Modem
1. **Signal Conversion**: Converts digital data (0s and 1s) to analog signals for transmission
2. **Enable Communication**: Allows computers to communicate over analog telephone networks
3. **Data Transmission**: Facilitates internet connectivity through ISP
4. **Protocol Handling**: Manages communication protocols between devices

#### Types of Modems
| Type | Connection | Speed |
|------|------------|-------|
| DSL Modem | Phone line | Up to 100 Mbps |
| Cable Modem | Coaxial cable | Up to 1 Gbps |
| Fiber Modem (ONT) | Fiber optic | Up to 10 Gbps |
| Dial-up Modem | Phone line | Up to 56 Kbps |

#### Can We Connect Without a Modem?
**Yes**, in certain scenarios:
- **Direct Fiber/Ethernet from ISP**: Some ISPs provide direct Ethernet connection
- **Mobile Hotspot**: Uses cellular network (modem built into phone)
- **LAN Networks**: Direct connection within local network doesn't need modem
- **Leased Line**: Direct digital connection for enterprises

**No**, when:
- Using DSL/Cable internet (analog to digital conversion required)
- Traditional telephone line connections

---

### b) What is a MAC address and how is it different from an IP address?

#### MAC Address (Media Access Control)
A **MAC address** is a unique hardware identifier assigned to the Network Interface Card (NIC) by the manufacturer.

**Format**: 48-bit (6 bytes), written as `XX:XX:XX:XX:XX:XX` (hexadecimal)
**Example**: `00:1A:2B:3C:4D:5E`

**Structure**:
```
First 3 bytes (OUI): Manufacturer ID (Organizationally Unique Identifier)
Last 3 bytes (NIC): Unique device identifier
```

#### IP Address (Internet Protocol)
A **logical address** assigned to devices for network identification and location addressing.

**IPv4 Format**: 32-bit, written as `X.X.X.X` (dotted decimal)
**Example**: `192.168.1.100`

#### Key Differences

| Feature | MAC Address | IP Address |
|---------|-------------|------------|
| **Layer** | Data Link (Layer 2) | Network (Layer 3) |
| **Type** | Physical/Hardware | Logical/Software |
| **Assigned by** | Manufacturer | Network Admin/DHCP |
| **Uniqueness** | Globally unique | Unique within network |
| **Format** | 48-bit hexadecimal | 32-bit (IPv4) / 128-bit (IPv6) |
| **Change** | Permanent (can be spoofed) | Can be changed |
| **Scope** | Local network | Global (routable) |
| **Example** | `00:1A:2B:3C:4D:5E` | `192.168.1.10` |

#### Commands to View
```bash
# View MAC address
ifconfig          # Linux/Mac
ip link show      # Linux
ipconfig /all     # Windows

# View IP address
ifconfig          # Linux/Mac
ip addr show      # Linux
ipconfig          # Windows
```

---

### c) What is a loopback IP address? What is its range?

#### Concept
A **loopback address** is a special IP address that routes traffic back to the same device without sending it to the network. It's used for testing and diagnostics.

#### Purpose
1. **Testing Network Software**: Test applications without network hardware
2. **Self-Diagnostics**: Verify TCP/IP stack is functioning
3. **Local Development**: Run and test servers locally
4. **Inter-Process Communication**: Applications on same host communicate

#### Loopback Address Range
**IPv4 Loopback Range**: `127.0.0.0` to `127.255.255.255` (127.0.0.0/8)

| Address | Description |
|---------|-------------|
| `127.0.0.1` | Standard loopback (localhost) |
| `127.0.0.0/8` | Entire loopback block (16 million addresses) |

**IPv6 Loopback**: `::1` (single address)

#### Key Characteristics
- Packets sent to loopback **never leave the host**
- The entire `127.x.x.x` range is reserved for loopback
- Most commonly used: `127.0.0.1` (mapped to `localhost` in hosts file)
- Used for testing TCP/IP stack functionality

#### Testing Loopback
```bash
# Ping loopback address
ping 127.0.0.1
ping localhost

# IPv6 loopback
ping6 ::1
```

#### Hosts File Entry
```
# /etc/hosts (Linux) or C:\Windows\System32\drivers\etc\hosts (Windows)
127.0.0.1    localhost
::1          localhost
```

---

### d) Write the command to assign a static IP in Linux

#### Method 1: Using `ip` command (Temporary - until reboot)
```bash
# Assign static IP
sudo ip addr add 192.168.1.100/24 dev eth0

# Set default gateway
sudo ip route add default via 192.168.1.1

# Bring interface up
sudo ip link set eth0 up
```

#### Method 2: Using `ifconfig` (Deprecated but still works)
```bash
# Assign IP and netmask
sudo ifconfig eth0 192.168.1.100 netmask 255.255.255.0 up

# Add default gateway
sudo route add default gw 192.168.1.1 eth0
```

#### Method 3: Permanent Configuration (Netplan - Ubuntu 18.04+)
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

Apply configuration:
```bash
sudo netplan apply
```

#### Method 4: Permanent Configuration (interfaces file - Debian/older Ubuntu)
Edit `/etc/network/interfaces`:
```
auto eth0
iface eth0 inet static
    address 192.168.1.100
    netmask 255.255.255.0
    gateway 192.168.1.1
    dns-nameservers 8.8.8.8 8.8.4.4
```

Restart networking:
```bash
sudo systemctl restart networking
```

#### Method 5: Using nmcli (NetworkManager)
```bash
# Add static IP configuration
sudo nmcli con mod "Wired connection 1" ipv4.addresses 192.168.1.100/24
sudo nmcli con mod "Wired connection 1" ipv4.gateway 192.168.1.1
sudo nmcli con mod "Wired connection 1" ipv4.dns "8.8.8.8"
sudo nmcli con mod "Wired connection 1" ipv4.method manual

# Restart connection
sudo nmcli con down "Wired connection 1" && sudo nmcli con up "Wired connection 1"
```

---

### f) Which online tool is used to check password strength?

#### Popular Online Password Strength Checkers

| Tool | URL | Features |
|------|-----|----------|
| **How Secure Is My Password** | howsecureismypassword.net | Shows time to crack |
| **Password Meter** | passwordmeter.com | Detailed strength analysis |
| **Kaspersky Password Checker** | password.kaspersky.com | Security company tool |
| **LastPass Password Generator** | lastpass.com/password-generator | Create & check passwords |
| **NordPass Password Checker** | nordpass.com/password-strength-checker | Breach database check |
| **Bitwarden Password Strength** | bitwarden.com/password-strength | Open source option |

#### What These Tools Check
1. **Length**: Minimum 8-12 characters recommended
2. **Character Variety**: Uppercase, lowercase, numbers, symbols
3. **Common Patterns**: Dictionary words, sequences (123, abc)
4. **Personal Info**: Avoids names, dates, common substitutions
5. **Entropy**: Measure of randomness/unpredictability

#### Password Strength Criteria
```
Weak:     < 8 chars, dictionary words, no special chars
Medium:   8-12 chars, some variety
Strong:   12-16 chars, mixed case, numbers, symbols
Very Strong: 16+ chars, high entropy, passphrase
```

#### Security Note
⚠️ **Never enter your actual password** on untrusted websites. Use these tools to test password **patterns**, not your real passwords.

---

### g) How to Use Nmap to Scan for Open Ports

#### What is Nmap?
**Nmap** (Network Mapper) is an open-source tool for network discovery and security auditing. It can detect open ports, services, and operating systems.

#### Installation
```bash
# Ubuntu/Debian
sudo apt install nmap

# CentOS/RHEL
sudo yum install nmap

# macOS
brew install nmap
```

#### Basic Port Scanning Commands

##### 1. Scan Single Host
```bash
nmap 192.168.1.1
nmap example.com
```

##### 2. Scan Specific Ports
```bash
# Single port
nmap -p 80 192.168.1.1

# Multiple ports
nmap -p 22,80,443 192.168.1.1

# Port range
nmap -p 1-1000 192.168.1.1

# All ports (65535)
nmap -p- 192.168.1.1
```

##### 3. Scan Types
```bash
# TCP SYN scan (default, requires root)
sudo nmap -sS 192.168.1.1

# TCP Connect scan (no root needed)
nmap -sT 192.168.1.1

# UDP scan
sudo nmap -sU 192.168.1.1

# Service version detection
nmap -sV 192.168.1.1

# OS detection
sudo nmap -O 192.168.1.1
```

##### 4. Scan Network Range
```bash
# Scan entire subnet
nmap 192.168.1.0/24

# Scan IP range
nmap 192.168.1.1-50

# Scan from file
nmap -iL targets.txt
```

##### 5. Common Useful Scans
```bash
# Fast scan (top 100 ports)
nmap -F 192.168.1.1

# Aggressive scan (OS, version, scripts, traceroute)
nmap -A 192.168.1.1

# Scan common ports with service versions
nmap -sV --top-ports 20 192.168.1.1
```

#### Sample Output
```
Starting Nmap 7.80
Nmap scan report for 192.168.1.1
Host is up (0.0012s latency).

PORT     STATE  SERVICE     VERSION
22/tcp   open   ssh         OpenSSH 8.2
80/tcp   open   http        Apache 2.4.41
443/tcp  open   https       Apache 2.4.41
3306/tcp closed mysql

Nmap done: 1 IP address (1 host up) scanned in 2.34 seconds
```

#### Port States
| State | Meaning |
|-------|---------|
| `open` | Service accepting connections |
| `closed` | Accessible but no service listening |
| `filtered` | Firewall blocking probe |
| `unfiltered` | Accessible, undetermined if open/closed |

#### ⚠️ Legal Notice
Only scan networks you own or have explicit permission to test. Unauthorized scanning is illegal in many jurisdictions.

---

## Q2: Practical Questions (20 Marks)

---

## Option A: Data Link Layer Framing - Character & Bit Stuffing

### Concept

**Framing** is the process of dividing data into manageable frames at the Data Link Layer. The receiver needs to identify frame boundaries.

#### Character Stuffing
Used when frames are delimited by special characters (e.g., DLE STX ... DLE ETX).

**Problem**: What if data contains the delimiter?
**Solution**: "Stuff" an extra DLE before any DLE in data.

```
Original Data:  A DLE B
After Stuffing: DLE STX A DLE DLE B DLE ETX
                ↑start      ↑stuffed  ↑end
```

#### Bit Stuffing
Used in protocols like HDLC where frame delimiter is `01111110` (flag).

**Problem**: What if data contains six consecutive 1s?
**Solution**: After five consecutive 1s, insert a 0.

```
Original:       011111110
After Stuffing: 0111110110
                     ↑inserted 0
```

### Algorithm

#### Character Stuffing
```
FUNCTION characterStuff(data):
    result = "DLE STX "
    FOR each character c in data:
        IF c == "DLE":
            result += "DLE DLE "  // Stuff extra DLE
        ELSE:
            result += c + " "
    result += "DLE ETX"
    RETURN result

FUNCTION characterDestuff(frame):
    Remove "DLE STX" from start and "DLE ETX" from end
    result = ""
    i = 0
    WHILE i < length(frame):
        IF frame[i] == "DLE" AND frame[i+1] == "DLE":
            result += "DLE"
            i += 2  // Skip stuffed DLE
        ELSE:
            result += frame[i]
            i += 1
    RETURN result
```

#### Bit Stuffing
```
FUNCTION bitStuff(data):
    result = "01111110"  // Start flag
    count = 0
    FOR each bit b in data:
        result += b
        IF b == '1':
            count++
            IF count == 5:
                result += '0'  // Stuff a 0
                count = 0
        ELSE:
            count = 0
    result += "01111110"  // End flag
    RETURN result

FUNCTION bitDestuff(frame):
    Remove start and end flags
    result = ""
    count = 0
    FOR each bit b in frame:
        result += b
        IF b == '1':
            count++
            IF count == 5:
                Skip next bit (stuffed 0)
                count = 0
        ELSE:
            count = 0
    RETURN result
```

### Time & Space Complexity
| Operation | Time | Space |
|-----------|------|-------|
| Character Stuffing | O(n) | O(n) - worst case doubles size |
| Bit Stuffing | O(n) | O(n) - worst case adds n/5 bits |

### Worked Example

#### Character Stuffing
```
Input:  H E L DLE L O
Output: DLE STX H E L DLE DLE L O DLE ETX
```

#### Bit Stuffing
```
Input:  01111111100
        ↑5 ones, then 6th one

After Stuffing:
        01111110 011111011100 01111110
        ↑flag    ↑stuffed 0    ↑flag
```

---

## Option B: Password Strength Checker

### Concept
A password strength checker evaluates passwords based on multiple criteria:
1. **Length** - Longer is stronger
2. **Character Types** - Mix of uppercase, lowercase, digits, symbols
3. **Entropy** - Randomness/unpredictability
4. **Common Patterns** - Avoid dictionary words, sequences

### Strength Criteria
| Strength | Requirements |
|----------|--------------|
| Very Weak | < 6 characters |
| Weak | 6-7 characters, limited variety |
| Medium | 8-11 characters, some variety |
| Strong | 12-15 characters, good variety |
| Very Strong | 16+ characters, all types, high entropy |

### Algorithm
```
FUNCTION checkPasswordStrength(password):
    score = 0
    length = len(password)
    
    // Length scoring
    IF length >= 8: score += 1
    IF length >= 12: score += 1
    IF length >= 16: score += 1
    
    // Character type scoring
    IF hasUppercase(password): score += 1
    IF hasLowercase(password): score += 1
    IF hasDigit(password): score += 1
    IF hasSpecialChar(password): score += 1
    
    // Penalty for common patterns
    IF hasSequence(password): score -= 1
    IF hasRepeating(password): score -= 1
    
    RETURN strengthLevel(score)
```

### Pseudocode
```
FUNCTION main():
    READ password
    
    hasUpper = FALSE
    hasLower = FALSE
    hasDigit = FALSE
    hasSpecial = FALSE
    length = 0
    
    FOR each char c in password:
        length++
        IF c is uppercase: hasUpper = TRUE
        IF c is lowercase: hasLower = TRUE
        IF c is digit: hasDigit = TRUE
        IF c is special: hasSpecial = TRUE
    
    score = 0
    IF length >= 8: score++
    IF length >= 12: score++
    IF hasUpper: score++
    IF hasLower: score++
    IF hasDigit: score++
    IF hasSpecial: score++
    
    IF score <= 2: PRINT "Weak"
    ELSE IF score <= 4: PRINT "Medium"
    ELSE: PRINT "Strong"
```

### Time & Space Complexity
| Operation | Time | Space |
|-----------|------|-------|
| Check Password | O(n) | O(1) |

Where n = length of password.

---

## Option C: Subnetting in Packet Tracer

### Given Information
- **Network Address**: 192.168.10.0/25
- **Configuration IP**: 192.168.1.10
- **Subnet Mask**: 255.255.255.0 (/24)
- **Default Gateway**: 192.168.1.1

### Subnetting Calculations for 192.168.10.0/25

#### Step 1: Calculate Network and Host Bits
```
/25 means 25 bits for network, 7 bits for hosts

Total bits in IPv4: 32
Network bits: 25
Host bits: 32 - 25 = 7
```

#### Step 2: Calculate Number of Subnetworks
```
Original network: 192.168.10.0/24 (Class C)
Borrowed bits for subnetting: 25 - 24 = 1 bit

Number of subnets = 2^1 = 2 subnets
```

#### Step 3: Calculate Usable Hosts per Subnet
```
Host bits = 7
Total addresses = 2^7 = 128 addresses per subnet
Usable hosts = 128 - 2 = 126 hosts (minus network and broadcast)
```

#### Step 4: Subnet Details
| Subnet | Network Address | First Usable | Last Usable | Broadcast |
|--------|-----------------|--------------|-------------|-----------|
| Subnet 0 | 192.168.10.0 | 192.168.10.1 | 192.168.10.126 | 192.168.10.127 |
| Subnet 1 | 192.168.10.128 | 192.168.10.129 | 192.168.10.254 | 192.168.10.255 |

#### Summary Table
| Parameter | Value |
|-----------|-------|
| Network Address | 192.168.10.0/25 |
| Subnet Mask | 255.255.255.128 |
| Network Bits | 25 |
| Host Bits | 7 |
| Number of Subnets | 2 |
| Hosts per Subnet | 126 (usable) |

### Packet Tracer Configuration Steps

#### Step 1: Open Packet Tracer
1. Launch Cisco Packet Tracer
2. Create new topology with PC and Router

#### Step 2: Configure PC IP Address
1. Click on PC → Desktop tab → IP Configuration
2. Select "Static" (not DHCP)
3. Enter:
   - **IP Address**: 192.168.1.10
   - **Subnet Mask**: 255.255.255.0
   - **Default Gateway**: 192.168.1.1

#### Step 3: Configure Router (if applicable)
```
Router> enable
Router# configure terminal
Router(config)# interface GigabitEthernet0/0
Router(config-if)# ip address 192.168.1.1 255.255.255.0
Router(config-if)# no shutdown
Router(config-if)# exit
```

#### Step 4: Verify Configuration
On PC Command Prompt:
```
C:\> ipconfig
C:\> ping 192.168.1.1
```

### Subnetting Quick Reference Formula
```
Number of subnets = 2^n (n = borrowed bits)
Hosts per subnet = 2^h - 2 (h = host bits)
Block size = 256 - subnet mask last octet
```

---

> **Solution Code:** See `Slip_01_Q2_OptionA.c` and `Slip_01_Q2_OptionB.c` in this folder.
