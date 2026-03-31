# Slip 4 — Computer Networks Solution Guide

## Question 1 (10 Marks) - Theory Questions (Answer ANY 5)

---

## Q1(a): What is Cyber Attack? Write the types of Cyberattacks

### Definition
A **Cyber Attack** is a deliberate attempt by individuals or organizations to breach the information systems of another individual or organization. The attacker seeks to gain unauthorized access, disrupt operations, steal data, or cause damage to computer systems, networks, or devices.

### Key Characteristics
| Aspect | Description |
|--------|-------------|
| Intent | Malicious purpose to harm or exploit |
| Target | Computer systems, networks, data |
| Method | Digital means via internet/network |
| Impact | Data loss, financial damage, service disruption |

### Types of Cyber Attacks

#### 1. **Malware Attacks**
- **Virus**: Self-replicating code that attaches to programs
- **Worm**: Spreads across networks without user action
- **Trojan Horse**: Disguised as legitimate software
- **Ransomware**: Encrypts data and demands payment
- **Spyware**: Secretly monitors user activity

#### 2. **Phishing Attacks**
- Fraudulent emails/messages mimicking legitimate sources
- Trick users into revealing sensitive information
- Types: Spear phishing (targeted), Whaling (executives)

#### 3. **Man-in-the-Middle (MITM) Attack**
```
[Victim A] ←→ [Attacker] ←→ [Victim B]
        Intercepts and modifies communication
```

#### 4. **Denial of Service (DoS/DDoS)**
- Floods target with traffic to overwhelm resources
- Distributed DoS uses multiple compromised systems

#### 5. **SQL Injection**
```sql
-- Normal query:
SELECT * FROM users WHERE username='admin'

-- Malicious input:
' OR '1'='1' --
-- Results in unauthorized access
```

#### 6. **Password Attacks**
- **Brute Force**: Try all possible combinations
- **Dictionary Attack**: Try common passwords
- **Credential Stuffing**: Use leaked password databases

#### 7. **Cross-Site Scripting (XSS)**
- Inject malicious scripts into web pages
- Execute in victims' browsers

#### 8. **Zero-Day Exploit**
- Attack exploiting unknown vulnerabilities
- No patch available yet

### Prevention Measures
| Attack Type | Prevention |
|-------------|-----------|
| Malware | Antivirus, software updates |
| Phishing | User training, email filtering |
| MITM | HTTPS, VPN encryption |
| DoS/DDoS | Rate limiting, CDN |
| SQL Injection | Parameterized queries |

---

## Q1(b): How can you reset or release an IP address obtained from DHCP?

### DHCP (Dynamic Host Configuration Protocol)
DHCP automatically assigns IP addresses to devices on a network. Sometimes you need to release the current IP and obtain a new one.

### Commands for Different Operating Systems

#### Windows Commands
```cmd
# Release current DHCP lease
ipconfig /release

# Renew DHCP lease (get new IP)
ipconfig /renew

# Release and renew together
ipconfig /release && ipconfig /renew

# View current IP configuration
ipconfig /all
```

#### Linux/Unix Commands
```bash
# Using dhclient (most common)
sudo dhclient -r eth0        # Release IP on eth0
sudo dhclient eth0           # Renew IP on eth0

# Using dhcpcd
sudo dhcpcd -k eth0          # Release
sudo dhcpcd eth0             # Renew

# Using nmcli (NetworkManager)
nmcli connection down eth0
nmcli connection up eth0
```

#### macOS Commands
```bash
# Release and renew
sudo ipconfig set en0 BOOTP
sudo ipconfig set en0 DHCP
```

### DHCP Process Flow
```
┌──────────┐     DHCPDISCOVER    ┌──────────┐
│  Client  │ ──────────────────→ │  Server  │
│          │     DHCPOFFER       │          │
│          │ ←────────────────── │          │
│          │     DHCPREQUEST     │          │
│          │ ──────────────────→ │          │
│          │     DHCPACK         │          │
│          │ ←────────────────── │          │
└──────────┘                     └──────────┘

    Release: Client sends DHCPRELEASE to server
```

### When to Release/Renew IP
| Scenario | Action |
|----------|--------|
| IP conflict | Release + Renew |
| Network change | Release + Renew |
| Troubleshooting | Release + Renew |
| Lease expired | Automatic renew |

---

## Q1(c): Explain supernetting with an example combining IPv4 Class C networks

### What is Supernetting?
**Supernetting** (also called **route aggregation** or **CIDR**) is the process of combining multiple smaller networks into a single larger network. It's the opposite of subnetting.

### Purpose of Supernetting
| Benefit | Description |
|---------|-------------|
| Reduce routing table size | Fewer entries to store/process |
| Efficient address allocation | Flexibility beyond classful limits |
| Faster routing decisions | Smaller tables = faster lookups |
| Conserve IP addresses | Better utilization of address space |

### Rules for Supernetting
1. All networks must be **contiguous** (consecutive)
2. Number of networks must be a **power of 2** (2, 4, 8, 16...)
3. First network address must be **evenly divisible** by total size

### Example: Combining 4 Class C Networks

**Given Networks:**
- 192.168.0.0/24 (192.168.0.0 - 192.168.0.255)
- 192.168.1.0/24 (192.168.1.0 - 192.168.1.255)
- 192.168.2.0/24 (192.168.2.0 - 192.168.2.255)
- 192.168.3.0/24 (192.168.3.0 - 192.168.3.255)

**Step 1: Verify Contiguity**
```
192.168.0.0 → 192.168.1.0 → 192.168.2.0 → 192.168.3.0
     ✓ Consecutive networks
```

**Step 2: Calculate New Prefix Length**
```
Original: /24 (255.255.255.0)
Number of networks: 4 = 2²
New prefix: 24 - 2 = /22

New mask: 255.255.252.0
```

**Step 3: Binary Analysis**
```
192.168.0.0   = 11000000.10101000.00000000.00000000
192.168.1.0   = 11000000.10101000.00000001.00000000
192.168.2.0   = 11000000.10101000.00000010.00000000
192.168.3.0   = 11000000.10101000.00000011.00000000
                ─────────────────────────┬───────────
                       22 bits same      │ 2 bits vary

Supernet: 192.168.0.0/22
```

**Step 4: Result Summary**
| Attribute | Value |
|-----------|-------|
| Supernet Address | 192.168.0.0/22 |
| Subnet Mask | 255.255.252.0 |
| Total Hosts | 4 × 254 = 1,016 usable |
| Range | 192.168.0.1 - 192.168.3.254 |
| Broadcast | 192.168.3.255 |

### Diagram
```
BEFORE (4 separate routes):              AFTER (1 supernet):
┌─────────────────────┐                 ┌─────────────────────┐
│ 192.168.0.0/24      │                 │                     │
├─────────────────────┤                 │                     │
│ 192.168.1.0/24      │   Supernetting  │  192.168.0.0/22     │
├─────────────────────┤  ───────────→   │   (1024 addresses)  │
│ 192.168.2.0/24      │                 │                     │
├─────────────────────┤                 │                     │
│ 192.168.3.0/24      │                 └─────────────────────┘
└─────────────────────┘
     4 routing entries                      1 routing entry
```

---

## Q1(d): How do you crack passwords with John the Ripper?

### What is John the Ripper?
**John the Ripper** is a popular open-source password security auditing and password recovery tool. It's used by security professionals to test password strength and recover lost passwords.

> ⚠️ **LEGAL WARNING**: Only use on systems you own or have explicit authorization to test!

### Supported Hash Types
| Hash Type | Example Use |
|-----------|-------------|
| MD5 | Linux, web applications |
| SHA-256/512 | Modern Linux (yescrypt) |
| NTLM | Windows passwords |
| bcrypt | Modern web apps |
| DES | Legacy Unix systems |

### Basic Usage

#### 1. **Extract Password Hashes**
```bash
# Linux - combine passwd and shadow files
sudo unshadow /etc/passwd /etc/shadow > hashes.txt

# Windows - extract from SAM (requires admin)
# Use tools like samdump2, pwdump
```

#### 2. **Run John the Ripper**
```bash
# Automatic mode (tries multiple attack types)
john hashes.txt

# Specify hash format
john --format=sha512crypt hashes.txt

# Show cracked passwords
john --show hashes.txt
```

### Attack Modes

#### Single Crack Mode (Default first)
```bash
john --single hashes.txt
# Uses username variations as password guesses
# user123 → user123, User123, USER123, 123user, etc.
```

#### Dictionary/Wordlist Mode
```bash
john --wordlist=/usr/share/wordlists/rockyou.txt hashes.txt

# With rules (mutations)
john --wordlist=words.txt --rules hashes.txt
# password → Password, password1, p@ssword, etc.
```

#### Incremental (Brute Force) Mode
```bash
john --incremental hashes.txt

# Specific character set
john --incremental=digits hashes.txt    # Numbers only
john --incremental=alpha hashes.txt     # Letters only
```

### Workflow Diagram
```
┌──────────────┐     ┌──────────────┐     ┌──────────────┐
│ Password     │     │   John the   │     │   Cracked    │
│   Hashes     │ ──→ │    Ripper    │ ──→ │  Passwords   │
│ (hashes.txt) │     │              │     │ (john.pot)   │
└──────────────┘     └──────────────┘     └──────────────┘
                            ↑
              ┌─────────────┼─────────────┐
              │             │             │
       ┌──────┴──────┐ ┌────┴────┐ ┌──────┴──────┐
       │  Wordlist   │ │  Rules  │ │ Incremental │
       │ rockyou.txt │ │  File   │ │   Mode      │
       └─────────────┘ └─────────┘ └─────────────┘
```

### Common Commands Reference
```bash
# Check status while running
john --status

# Resume interrupted session
john --restore

# List supported formats
john --list=formats

# Use multiple CPU cores
john --fork=4 hashes.txt
```

---

## Q1(f): Explain the use of copy running-config startup-config

### Cisco Router Configuration Files

Cisco devices have two main configuration files:

| Configuration | Location | Persistence |
|--------------|----------|-------------|
| **Running-config** | RAM | Lost on reboot |
| **Startup-config** | NVRAM | Survives reboot |

### The Command
```
Router# copy running-config startup-config
Destination filename [startup-config]? [Enter]
Building configuration...
[OK]
```

**Shorthand:** `copy run start` or `wr` (write memory)

### What It Does
This command copies the current active configuration (in RAM) to non-volatile memory (NVRAM), making changes permanent.

### Configuration Flow Diagram
```
┌───────────────────────────────────────────────────────┐
│                     NVRAM                              │
│  ┌─────────────────────────────────────────────────┐  │
│  │             startup-config                       │  │
│  │   (Loaded at boot, survives power loss)         │  │
│  └─────────────────────────────────────────────────┘  │
└───────────────────────────────────────────────────────┘
                          │
                          │ Boot Process
                          ↓
┌───────────────────────────────────────────────────────┐
│                       RAM                              │
│  ┌─────────────────────────────────────────────────┐  │
│  │              running-config                      │  │
│  │   (Active config, lost on power loss)           │  │
│  └─────────────────────────────────────────────────┘  │
└───────────────────────────────────────────────────────┘

    copy running-config startup-config
    ────────────────────────────────→
    Saves current changes to NVRAM
```

### When to Use
| Scenario | Action |
|----------|--------|
| After making changes | `copy run start` |
| Testing changes | Don't save (reboot reverts) |
| Before major changes | Backup startup-config first |
| Made a mistake | `copy startup-config running-config` to revert |

### Related Commands
```
# View running configuration
Router# show running-config

# View startup configuration  
Router# show startup-config

# Erase startup configuration
Router# erase startup-config

# Alternative save command
Router# write memory
```

### Practical Example
```
Router> enable
Router# configure terminal
Router(config)# hostname MyRouter
Router(config)# interface GigabitEthernet0/0
Router(config-if)# ip address 192.168.1.1 255.255.255.0
Router(config-if)# no shutdown
Router(config-if)# exit
Router(config)# exit
MyRouter# copy running-config startup-config
```

---

## Q1(g): What is a loopback IP address? What is its range?

### Definition
A **loopback IP address** is a special IP address used to test network software without involving actual network hardware. Data sent to the loopback address never leaves the host machine—it's processed locally.

### Loopback Address Range

#### IPv4 Loopback
| Attribute | Value |
|-----------|-------|
| Range | **127.0.0.0 to 127.255.255.255** |
| CIDR Notation | 127.0.0.0/8 |
| Most Common | **127.0.0.1** ("localhost") |
| Total Addresses | 16,777,216 (2²⁴) |

#### IPv6 Loopback
| Attribute | Value |
|-----------|-------|
| Address | **::1** (0000:0000:0000:0000:0000:0000:0000:0001) |
| Only One | Single address (not a range) |

### How Loopback Works
```
┌─────────────────────────────────────────────┐
│                  Host Machine                │
│                                             │
│  ┌──────────┐      ┌──────────────────┐     │
│  │  Client  │ ───→ │  Loopback        │     │
│  │  App     │      │  Interface (lo)  │     │
│  │ (Browser)│ ←─── │  127.0.0.1       │     │
│  └──────────┘      └──────────────────┘     │
│       ↑                    │                │
│       │                    ↓                │
│       │            ┌──────────────────┐     │
│       └─────────── │  Server App      │     │
│                    │  (Web Server)    │     │
│                    └──────────────────┘     │
│                                             │
│         ✗ No data leaves the machine        │
└─────────────────────────────────────────────┘
```

### Uses of Loopback Address
| Use Case | Example |
|----------|---------|
| Test network stack | `ping 127.0.0.1` |
| Local development | Web server on localhost |
| Inter-process communication | Database connections |
| Network diagnostics | Test TCP/IP is working |
| Application testing | Test before deployment |

### Common Applications
```bash
# Test if TCP/IP stack is working
ping 127.0.0.1

# Access local web server
curl http://127.0.0.1:8080

# Connect to local database
mysql -h 127.0.0.1 -u root -p

# /etc/hosts mapping
127.0.0.1    localhost
127.0.0.1    myapp.local
```

### Why 127.x.x.x Range?
- Reserved by IANA for loopback
- Any address in 127.0.0.0/8 works
- Entire Class A block dedicated to loopback
- Most software uses 127.0.0.1 by convention

### Verify Loopback Interface
```bash
# Linux
ip addr show lo
# lo: <LOOPBACK,UP> ...
#     inet 127.0.0.1/8 scope host lo

# Windows
ipconfig | findstr "127"
```

---

## Question 2 (20 Marks) - Practical Options

### Option A: Phishing Pattern Detection in Emails
See file: `Slip_04_Q2_OptionA.c`

### Option B: Private IP Range Checker
See file: `Slip_04_Q2_OptionB.c`

### Option C: Packet Tracer Lab (Network with Switch)

#### Network Topology
```
        ┌──────────────────┐
        │                  │
        │     SWITCH       │
        │   (Layer 2)      │
        │                  │
        └────┬────────┬────┘
             │        │
      ┌──────┘        └──────┐
      │                      │
┌─────┴─────┐          ┌─────┴─────┐
│   PC0     │          │   PC1     │
│192.168.1.1│          │192.168.1.2│
│ /24       │          │ /24       │
└───────────┘          └───────────┘
```

#### Configuration Steps
1. **Add Devices**: 2 PCs, 1 Switch (2960)
2. **Connect**: Use straight-through cables (PC to Switch)
3. **Configure PC0**:
   - IP: 192.168.1.1
   - Mask: 255.255.255.0
   - Gateway: 192.168.1.254 (optional)
4. **Configure PC1**:
   - IP: 192.168.1.2
   - Mask: 255.255.255.0
5. **Test**: `ping 192.168.1.2` from PC0

#### IP Address Classes Explained

| Class | First Octet Range | Default Mask | Network/Host Bits | Purpose |
|-------|-------------------|--------------|-------------------|---------|
| **A** | 1-126 | 255.0.0.0 (/8) | 8/24 | Large networks |
| **B** | 128-191 | 255.255.0.0 (/16) | 16/16 | Medium networks |
| **C** | 192-223 | 255.255.255.0 (/24) | 24/8 | Small networks |
| **D** | 224-239 | N/A | N/A | Multicast |
| **E** | 240-255 | N/A | N/A | Experimental |

#### Visual Representation
```
IP Address Classes:

Class A: |N|  Host   |  (8 network bits, 24 host bits)
         0xxxxxxx.xxxxxxxx.xxxxxxxx.xxxxxxxx
         1.0.0.0 - 126.255.255.255

Class B: | N  | Host |  (16 network bits, 16 host bits)
         10xxxxxx.xxxxxxxx.xxxxxxxx.xxxxxxxx
         128.0.0.0 - 191.255.255.255

Class C: |   N   |H|  (24 network bits, 8 host bits)
         110xxxxx.xxxxxxxx.xxxxxxxx.xxxxxxxx
         192.0.0.0 - 223.255.255.255

Class D: |    Multicast Address    |
         1110xxxx.xxxxxxxx.xxxxxxxx.xxxxxxxx
         224.0.0.0 - 239.255.255.255

Class E: |    Reserved/Experimental |
         1111xxxx.xxxxxxxx.xxxxxxxx.xxxxxxxx
         240.0.0.0 - 255.255.255.255
```

#### Private IP Ranges (Cannot be routed on Internet)
| Class | Private Range | CIDR |
|-------|---------------|------|
| A | 10.0.0.0 - 10.255.255.255 | 10.0.0.0/8 |
| B | 172.16.0.0 - 172.31.255.255 | 172.16.0.0/12 |
| C | 192.168.0.0 - 192.168.255.255 | 192.168.0.0/16 |

#### 192.168.1.0/24 Network Details
| Attribute | Value |
|-----------|-------|
| Network Address | 192.168.1.0 |
| First Usable IP | 192.168.1.1 |
| Last Usable IP | 192.168.1.254 |
| Broadcast Address | 192.168.1.255 |
| Total Usable Hosts | 254 |
| Subnet Mask | 255.255.255.0 |
| Class | C (Private) |

---

## Quick Reference Card

| Topic | Key Point |
|-------|-----------|
| Cyber Attack | Malicious attempt to breach computer systems |
| DHCP Release | `ipconfig /release` (Win), `dhclient -r` (Linux) |
| Supernetting | Combine networks, reduce routing table |
| John the Ripper | Password auditing tool |
| copy run start | Save Cisco config permanently |
| Loopback | 127.0.0.0/8, localhost testing |
| Class C | 192-223, /24, small networks |

---

*End of Slip 4 Computer Networks Solution Guide*
