# Slip 15 — Computer Networks Solution Guide

## Q1: Theory Questions (10 marks) — Answer ANY 5

---

### Q1(a) Command to Move from Router> to Router# Mode

#### Concept
Cisco routers have different privilege levels:
- **User EXEC Mode (Router>):** Limited commands, monitoring only
- **Privileged EXEC Mode (Router#):** Full access to all commands

#### Answer
```
Router> enable
Router#
```

#### Explanation
| Mode | Prompt | Access Level |
|------|--------|--------------|
| User EXEC | Router> | View-only, basic diagnostics |
| Privileged EXEC | Router# | Full configuration access |
| Global Config | Router(config)# | System-wide settings |

#### Additional Commands
```
Router# disable          → Return to User EXEC
Router# configure terminal → Enter Global Config Mode
Router(config)# exit     → Return to Privileged EXEC
```

---

### Q1(b) Hexadecimal Digits for 64-bit WEP Key

#### Concept
**WEP (Wired Equivalent Privacy):** Early Wi-Fi encryption standard.

#### Calculation
- 64-bit WEP key = 40 bits for key + 24 bits IV (Initialization Vector)
- User provides 40-bit key
- 40 bits ÷ 4 bits per hex digit = **10 hexadecimal digits**

#### Answer
**10 hexadecimal digits** are needed for a 64-bit WEP key.

#### 5 Examples of 64-bit WEP Keys
| # | Key (10 hex digits) | Description |
|---|---------------------|-------------|
| 1 | `1234567890` | Sequential digits |
| 2 | `ABCDEF1234` | Mixed alphanumeric |
| 3 | `A1B2C3D4E5` | Alternating pattern |
| 4 | `0F0F0F0F0F` | Repeating pattern |
| 5 | `DEADBEEF01` | Memorable hex word |

#### WEP Key Sizes
| Standard | Total Bits | Key Bits | IV Bits | Hex Digits |
|----------|-----------|----------|---------|------------|
| 64-bit WEP | 64 | 40 | 24 | 10 |
| 128-bit WEP | 128 | 104 | 24 | 26 |

> **Note:** WEP is deprecated due to security vulnerabilities. Use WPA2/WPA3.

---

### Q1(c) Dummy Phishing Email and Indicators

#### Dummy Phishing Email
```
From: security@amaz0n-verify.com
To: customer@email.com
Subject: URGENT: Your Amazon Account Has Been Compromised!

Dear Valued Customer,

We have detected suspicious activity on your Amazon account. Your account 
will be SUSPENDED within 24 hours unless you verify your information.

Click here immediately to secure your account:
http://amaz0n-secure-login.fakesite.com/verify

Please provide the following:
- Full Name
- Credit Card Number
- CVV Code
- Social Security Number

Failure to respond will result in permanent account closure.

Amazon Security Team
This email was sent from an unmonitored address.
```

#### Phishing Indicators

| Indicator | Example from Email | Why It's Suspicious |
|-----------|-------------------|---------------------|
| **Spoofed Domain** | `amaz0n-verify.com` | Zero instead of 'o', not official domain |
| **Urgency/Fear** | "SUSPENDED within 24 hours" | Creates panic to bypass rational thinking |
| **Generic Greeting** | "Dear Valued Customer" | Legitimate emails use your name |
| **Suspicious Links** | `fakesite.com/verify` | Hover reveals non-Amazon URL |
| **Requests Sensitive Data** | SSN, CVV | Real companies never ask for this via email |
| **Grammar/Spelling Issues** | Often present | Professional companies proofread emails |
| **Unmonitored Address** | "sent from unmonitored" | Prevents verification attempts |
| **Mismatched Sender** | From header vs actual | Headers can be spoofed |

#### How to Verify Legitimacy
1. **Hover over links** — Check actual URL before clicking
2. **Check sender email** — Verify domain is official
3. **Contact company directly** — Use official website/phone
4. **Look for HTTPS** — Secure sites use SSL certificates
5. **Check for personalization** — Real emails know your name

---

### Q1(d) Cracking ZIP Password with fcrackzip

#### Concept
**fcrackzip:** Linux tool for cracking password-protected ZIP archives using:
- Dictionary attacks
- Brute-force attacks

#### Installation
```bash
sudo apt-get install fcrackzip
```

#### Method 1: Dictionary Attack
```bash
# Using a wordlist
fcrackzip -D -p /usr/share/wordlists/rockyou.txt -u secret.zip
```

#### Method 2: Brute-Force Attack
```bash
# Brute-force with lowercase letters, max 6 characters
fcrackzip -b -c a -l 1-6 -u secret.zip

# Brute-force with all characters (a-z, A-Z, 0-9)
fcrackzip -b -c aA1 -l 1-8 -u secret.zip
```

#### Options Explained
| Option | Description |
|--------|-------------|
| `-D` | Dictionary mode |
| `-b` | Brute-force mode |
| `-p <file>` | Path to wordlist/password file |
| `-c <charset>` | Character set: a=lowercase, A=uppercase, 1=digits, !=special |
| `-l <min>-<max>` | Password length range |
| `-u` | Use unzip to verify (eliminates false positives) |
| `-v` | Verbose output |

#### Complete Example
```bash
# Create a test password-protected ZIP
zip -P "test123" secret.zip important_file.txt

# Crack with dictionary
fcrackzip -D -p /usr/share/wordlists/rockyou.txt -u secret.zip

# Output: PASSWORD FOUND!!!!: pw == test123

# Extract using found password
unzip -P "test123" secret.zip
```

#### Practical Brute-Force Example
```bash
# Numbers only, 4 digits (PIN-style)
fcrackzip -b -c 1 -l 4-4 -u encrypted.zip

# Lowercase + numbers, 1-6 chars
fcrackzip -b -c a1 -l 1-6 -u encrypted.zip
```

---

### Q1(f) Comparing ip addr vs ifconfig Output

#### Concept
Both commands display network interface information, but `ip addr` is modern and `ifconfig` is legacy.

#### Command Execution
```bash
# Modern command (iproute2 package)
ip addr

# Legacy command (net-tools package)
ifconfig
```

#### Sample Output: ip addr
```
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
    inet6 ::1/128 scope host

2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc fq_codel state UP
    link/ether 00:1a:2b:3c:4d:5e brd ff:ff:ff:ff:ff:ff
    inet 192.168.1.100/24 brd 192.168.1.255 scope global dynamic eth0
    inet6 fe80::21a:2bff:fe3c:4d5e/64 scope link
```

#### Sample Output: ifconfig
```
eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.1.100  netmask 255.255.255.0  broadcast 192.168.1.255
        inet6 fe80::21a:2bff:fe3c:4d5e  prefixlen 64  scopeid 0x20<link>
        ether 00:1a:2b:3c:4d:5e  txqueuelen 1000  (Ethernet)
        RX packets 12345  bytes 6789012 (6.7 MB)
        TX packets 9876  bytes 1234567 (1.2 MB)

lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        inet 127.0.0.1  netmask 255.0.0.0
        inet6 ::1  prefixlen 128  scopeid 0x10<host>
        loop  txqueuelen 1000  (Local Loopback)
```

#### Comparison Table

| Feature | ip addr | ifconfig |
|---------|---------|----------|
| **Package** | iproute2 (default) | net-tools (legacy) |
| **Status** | Modern, actively maintained | Deprecated |
| **CIDR Notation** | Yes (192.168.1.100/24) | No (shows netmask separately) |
| **Multiple IPs** | Shows all IPs per interface | May not show secondary IPs |
| **IPv6 Support** | Full support | Limited |
| **Interface Numbering** | Shows index (1:, 2:) | No index |
| **State Information** | Detailed (UP, LOWER_UP) | Basic flags |
| **Output Format** | Consistent, parseable | Less structured |
| **Alias Support** | Secondary addresses | eth0:0, eth0:1 aliases |

#### Key Differences
1. **ip addr** uses CIDR notation (`/24`), ifconfig shows netmask (`255.255.255.0`)
2. **ip addr** is part of iproute2, the standard Linux networking toolkit
3. **ifconfig** requires net-tools package, often not installed by default
4. **ip addr** shows more detailed interface states

#### Recommendation
```bash
# Use ip command family for modern Linux
ip addr       # Show addresses
ip link       # Show link layer info
ip route      # Show routing table
```

---

### Q1(g) Reset/Release IP Address from DHCP

#### Concept
DHCP (Dynamic Host Configuration Protocol) assigns IP addresses dynamically. You can release the current lease and obtain a new one.

#### Linux Commands
```bash
# Release current DHCP lease
sudo dhclient -r

# Obtain new IP address
sudo dhclient

# Or in one command (release and renew)
sudo dhclient -r && sudo dhclient

# For specific interface
sudo dhclient -r eth0
sudo dhclient eth0
```

#### Alternative: Using systemd-networkd
```bash
# Restart networking service
sudo systemctl restart systemd-networkd

# Or using networkctl
sudo networkctl reconfigure eth0
```

#### Windows Commands
```cmd
REM Release IP address
ipconfig /release

REM Renew IP address
ipconfig /renew

REM Release specific adapter
ipconfig /release "Ethernet"

REM View current configuration
ipconfig /all
```

#### DHCP Lease Process (DORA)
| Step | Message | Direction | Purpose |
|------|---------|-----------|---------|
| 1 | **D**iscover | Client → Server | Find DHCP servers |
| 2 | **O**ffer | Server → Client | Server offers IP |
| 3 | **R**equest | Client → Server | Client accepts offer |
| 4 | **A**ck | Server → Client | Server confirms lease |

#### Additional Commands
```bash
# Check current DHCP lease
cat /var/lib/dhcp/dhclient.leases

# View DHCP client status
systemctl status dhclient

# Force release and flush
sudo ip addr flush dev eth0
sudo dhclient eth0
```

---

## Q2: Practical Programs (20 marks)

---

## Q2 Option A: Command-Line Phishing Simulation

### Concept
Simulate a phishing attack to demonstrate how attackers collect credentials through fake login prompts.

### Algorithm
1. Display fake login banner (mimicking legitimate service)
2. Prompt for username
3. Prompt for password (hide input)
4. Store/display captured credentials
5. Show educational message about phishing dangers

### Pseudocode
```
FUNCTION phishing_simulation():
    DISPLAY fake_banner
    PRINT "Enter username: "
    READ username
    PRINT "Enter password: "
    READ password (hidden)
    
    LOG credentials to file
    DISPLAY "Login failed" (typical phishing response)
    DISPLAY educational warning
END FUNCTION
```

### Program Features
- Simulates bank/email login page
- Demonstrates credential harvesting
- Educational purpose only

> **See:** `Slip_15_Q2_OptionA.c`

---

## Q2 Option B: Mesh Topology Display

### Concept
Mesh topology: Every device connects to every other device directly.

### Formula
- **Full Mesh Connections:** n(n-1)/2 (undirected)
- **Full Mesh Links:** n(n-1) (directed)

### Algorithm
1. Accept number of nodes
2. Calculate total connections
3. Display adjacency matrix (all 1s except diagonal)
4. List all connections graphically

### Pseudocode
```
FUNCTION display_mesh(n):
    connections = n * (n - 1) / 2
    
    // Create adjacency matrix
    FOR i = 0 TO n-1:
        FOR j = 0 TO n-1:
            IF i == j:
                matrix[i][j] = 0
            ELSE:
                matrix[i][j] = 1
    
    // Display connections
    FOR i = 0 TO n-1:
        FOR j = i+1 TO n-1:
            PRINT "Node" + i + " <---> Node" + j
END FUNCTION
```

### Mesh Topology Properties
| Property | Value |
|----------|-------|
| Connections | n(n-1)/2 |
| Fault Tolerance | High |
| Redundancy | Maximum |
| Cost | High (more cables) |
| Use Case | Critical networks |

> **See:** `Slip_15_Q2_OptionB.c`

---

## Q2 Option C: Packet Tracer — Mesh Topology (4 PCs)

### Network Configuration
| Device | IP Address | Subnet Mask | Gateway |
|--------|------------|-------------|---------|
| PC0 | 172.16.1.1 | 255.255.0.0 | - |
| PC1 | 172.16.1.2 | 255.255.0.0 | - |
| PC2 | 172.16.1.3 | 255.255.0.0 | - |
| PC3 | 172.16.1.4 | 255.255.0.0 | - |

### Steps in Packet Tracer
1. **Add Devices:** Place 4 PCs (PC0-PC3)
2. **Add NICs:** Each PC needs 3 additional Ethernet NICs (total 4 per PC)
3. **Connect PCs:** Create mesh connections:
   - PC0 ↔ PC1, PC0 ↔ PC2, PC0 ↔ PC3
   - PC1 ↔ PC2, PC1 ↔ PC3
   - PC2 ↔ PC3
4. **Configure IPs:** Set IP addresses on each interface
5. **Verify:** Ping between all PCs

### Mesh Connections for 4 Nodes
```
Total Connections = 4(4-1)/2 = 6 connections

PC0 -------- PC1
 | \        / |
 |  \      /  |
 |   \    /   |
 |    \  /    |
 |     \/     |
 |     /\     |
 |    /  \    |
 |   /    \   |
 |  /      \  |
 | /        \ |
PC3 -------- PC2
```

### Configuration Commands (per PC)
```
PC0:
  FastEthernet0: 172.16.1.1, 255.255.0.0
  
PC1:
  FastEthernet0: 172.16.1.2, 255.255.0.0
  
PC2:
  FastEthernet0: 172.16.1.3, 255.255.0.0
  
PC3:
  FastEthernet0: 172.16.1.4, 255.255.0.0
```

### Verification
```
PC0> ping 172.16.1.2   (Success)
PC0> ping 172.16.1.3   (Success)
PC0> ping 172.16.1.4   (Success)
```

---

## Quick Reference Card

### Cisco Router Mode Commands
| Command | Transition |
|---------|-----------|
| `enable` | User → Privileged |
| `disable` | Privileged → User |
| `configure terminal` | Privileged → Global Config |
| `exit` | Back one level |
| `end` | To Privileged from any |

### Network Commands
| Task | Linux | Windows |
|------|-------|---------|
| Show IP | `ip addr` | `ipconfig` |
| Release DHCP | `dhclient -r` | `ipconfig /release` |
| Renew DHCP | `dhclient` | `ipconfig /renew` |
| Flush DNS | `systemd-resolve --flush` | `ipconfig /flushdns` |

### WEP Key Sizes
| Type | Hex Digits | Bits |
|------|-----------|------|
| 64-bit | 10 | 40 key + 24 IV |
| 128-bit | 26 | 104 key + 24 IV |

---

> **Solution Programs:** See `Slip_15_Q2_OptionA.c` and `Slip_15_Q2_OptionB.c`
