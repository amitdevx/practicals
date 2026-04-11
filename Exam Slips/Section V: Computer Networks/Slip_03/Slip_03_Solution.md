# Slip 3 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) What is Cyber Attack? Write the types of Cyberattacks.

A **cyber attack** is a deliberate attempt or series of attempts by an attacker to breach the security, confidentiality, integrity, or availability of an information system or network without authorization.

**Types of Cyberattacks:**

1. **Malware Attacks**
   - **Viruses**: Self-replicating programs attached to files, spread via infected files
   - **Worms**: Self-propagating malware that spreads through networks without user interaction
   - **Trojans**: Appear as legitimate software but contain hidden malicious code
   - **Ransomware**: Encrypts files and demands payment for decryption

2. **Phishing**
   - Social engineering via email, SMS, or messages
   - Trick users into revealing sensitive information or clicking malicious links
   - Spear phishing targets specific individuals

3. **DDoS (Denial of Service)**
   - Floods server with traffic to make services unavailable
   - Distributed DDoS uses multiple sources
   - Prevents legitimate users from accessing services

4. **Man-in-the-Middle (MITM)**
   - Attacker intercepts communication between two parties
   - Can eavesdrop, steal data, or modify messages
   - Common on unsecured WiFi networks

5. **SQL Injection**
   - Exploits database query vulnerabilities
   - Inserting malicious SQL code into input fields
   - Can lead to unauthorized data access or deletion

6. **Password Attacks**
   - Brute force attacks trying all possible passwords
   - Dictionary attacks using common passwords
   - Rainbow table attacks using pre-computed hash values

7. **Zero-day Exploits**
   - Exploiting unknown, unpatched vulnerabilities
   - Attackers exploit before vendors release patches
   - Most dangerous as no immediate fix available

8. **Social Engineering**
   - Manipulating people to divulge confidential information
   - Pretexting, baiting, tailgating techniques
   - Exploits human psychology rather than technical vulnerabilities

---

### b) How can you reset or release an IP address obtained from DHCP?

**DHCP (Dynamic Host Configuration Protocol)** automatically assigns IP addresses. To reset or release them:

**On Linux:**
```bash
# Release current IP
sudo dhclient -r eth0

# Renew/obtain new IP
sudo dhclient eth0

# Both in one command (release and renew)
sudo dhclient -r eth0 && sudo dhclient eth0

# For systemd systems
sudo systemctl restart networking
```

**On Windows:**
```cmd
# Release current IP
ipconfig /release

# Renew/obtain new IP
ipconfig /renew

# Both together
ipconfig /release && ipconfig /renew

# For specific adapter
ipconfig /release "Ethernet"
ipconfig /renew "Ethernet"
```

**On macOS:**
```bash
# Release
sudo dhclient -r en0

# Renew
sudo dhclient en0

# Or via System Preferences
# System Preferences → Network → Wi-Fi/Ethernet → Advanced → TCP/IP → Renew DHCP Lease
```

**What happens:**
- **Release**: Device sends DHCP RELEASE message, returning IP to server pool
- **Renew**: Device sends DHCP REQUEST for new IP address
- **Result**: Device gets fresh IP address from DHCP server

---

### c) Explain supernetting with an example combining IPv4 Class C networks.

**Supernetting** (also called route aggregation) combines multiple smaller networks into one larger network by reducing network bits (increasing host bits). This reduces routing table entries and simplifies network management.

**Concept:**
- Takes multiple Class C networks (or other classes)
- Combines them into a single larger network
- Reduces network prefix length (e.g., /24 becomes /22)
- Useful for route summarization and network consolidation

**Example - Combining Four Class C Networks:**

```
Network 1: 192.168.0.0/24     (192.168.0.0 to 192.168.0.255)
Network 2: 192.168.1.0/24     (192.168.1.0 to 192.168.1.255)
Network 3: 192.168.2.0/24     (192.168.2.0 to 192.168.2.255)
Network 4: 192.168.3.0/24     (192.168.3.0 to 192.168.3.255)

Combined Supernet: 192.168.0.0/22

Supernet Range: 192.168.0.0 to 192.168.3.255 (1024 addresses)
```

**How Supernetting Works:**

| Network | Binary Address | /24 Prefix |
|---------|----------------|-----------|
| 192.168.0.0 | 11000000.10101000.00000000.00000000 | /24 |
| 192.168.1.0 | 11000000.10101000.00000001.00000000 | /24 |
| 192.168.2.0 | 11000000.10101000.00000010.00000000 | /24 |
| 192.168.3.0 | 11000000.10101000.00000011.00000000 | /24 |
| **Supernet** | **11000000.10101000.0000000x.00000000** | **/22** |

**Advantages:**
- Reduces routing table size (fewer entries needed)
- Simplifies network administration
- Reduces memory and CPU usage on routers
- Faster route lookups

**Disadvantages:**
- Networks must be contiguous and power-of-2 aligned
- Can only combine networks in specific arrangements
- Requires careful planning

---

### d) How do you crack passwords with John the Ripper?

**John the Ripper** is a password cracking tool used for testing and security audits on authorized systems.

**Installation:**
```bash
# Linux/Ubuntu
sudo apt-get install john

# CentOS
sudo yum install john

# macOS
brew install john-jumbo
```

**Password Cracking Methods:**

**1. Dictionary Attack** (Using wordlist):
```bash
# Basic dictionary attack on password file
john --wordlist=/usr/share/wordlists/rockyou.txt /etc/shadow

# With custom wordlist
john --wordlist=mywords.txt passwordfile

# Show results
john --show passwordfile
```

**2. Brute Force Attack** (Try all combinations):
```bash
# Incremental mode (brute force all combinations)
john --incremental passwordfile

# Specify character set
john --incremental=Digits passwordfile
```

**3. Hybrid Attack** (Wordlist + brute force):
```bash
john --wordlist=wordlist.txt --rules passwordfile
```

**4. Specify User and Rules:**
```bash
# Attack specific user
john --user=admin passwordfile

# Specify rules for word variations
john --rules passwordfile
```

**5. Performance Options:**
```bash
# Use multiple cores/threads
john -t=4 passwordfile

# Disable jumbo rules (faster)
john --format=sha512crypt passwordfile
```

**Show Cracked Passwords:**
```bash
john --show passwordfile

# Shows all successfully cracked passwords in format: username:password
```

**⚠️ Legal/Ethical Note:**
- Use ONLY on authorized systems for security testing
- Unauthorized password cracking is illegal
- Requires explicit permission from system owner
- Use in controlled lab environments only

---

### f) Explain the use of copy running-config startup-config.

This is a Cisco networking command for saving running configuration to persistent storage.

**Command Syntax:**
```cisco
Router# copy running-config startup-config
Destination filename [startup-config]?
Building configuration... [OK]
```

**What it does:**
- Saves currently active running configuration (in RAM)
- Writes to startup-config (stored in NVRAM)
- Ensures configuration persists after device reboot

**Why it's Important:**
- **Without this command**: Changes are lost when device restarts
- **With this command**: Configuration survives power outages and reboots
- **Default behavior**: Device loads startup-config on boot

**Related Commands:**

```cisco
# Show running configuration (current/active)
Router# show running-config

# Show startup configuration (saved to NVRAM)
Router# show startup-config

# Shorter syntax
Router# copy run start

# Erase startup configuration (factory reset)
Router# erase startup-config

# Reload device from startup-config
Router# reload
```

**Typical Workflow:**
```cisco
Router# configure terminal
Router(config)# hostname ROUTER-1
Router(config)# interface GigabitEthernet0/0
Router(config-if)# ip address 192.168.1.1 255.255.255.0
Router(config-if)# no shutdown
Router(config-if)# exit
Router(config)# exit

# NOW SAVE - without this, changes lost on reboot
Router# copy running-config startup-config
```

---

### g) What is a loopback IP address? What is its range?

A **loopback address** is a special IP address that routes network traffic back to the same computer without sending it to an external network. Used for testing and diagnostics.

**Loopback Address Range:**

**IPv4 Loopback Block:**
- **Range**: 127.0.0.0 to 127.255.255.255 (127.0.0.0/8)
- **Most commonly used**: 127.0.0.1 (mapped to "localhost")
- **Total addresses**: 16.7 million (all reserved for loopback)

**IPv6 Loopback:**
- **Address**: ::1 (single address)
- **Equivalent to IPv4 127.0.0.1**

**Loopback Address Entry in Hosts File:**
```
# /etc/hosts (Linux/Mac) or C:\Windows\System32\drivers\etc\hosts (Windows)
127.0.0.1    localhost
::1          localhost
```

**Key Characteristics:**
- Packets sent to loopback **never leave the host** machine
- Entire 127.x.x.x range reserved for loopback use
- No network interface required
- Used for local testing and inter-process communication

**Uses:**
1. **Testing Network Software**: Test TCP/IP stack without network hardware
2. **Self-Diagnostics**: Verify TCP/IP implementation is working
3. **Local Development**: Run and test web servers locally
4. **Inter-Process Communication**: Applications on same host communicate

**Testing Loopback:**
```bash
# Ping IPv4 loopback
ping 127.0.0.1
ping localhost

# Ping IPv6 loopback
ping6 ::1
ping6 localhost
```

**Expected Output:**
```
PING 127.0.0.1 (127.0.0.1) 56(84) bytes of data.
64 bytes from 127.0.0.1: icmp_seq=1 ttl=64 time=0.041 ms
64 bytes from 127.0.0.1: icmp_seq=2 ttl=64 time=0.035 ms
```

---

## Q2: Practical Questions (20 Marks)

### OPTION A: Read email from file and perform phishing pattern detection

This program reads email content from a file and analyzes it for phishing indicators such as:
- Suspicious sender patterns
- Generic greetings
- Urgent language and threats
- Requests for sensitive information
- Suspicious links or attachments
- Poor grammar and spelling

**Algorithm:**
1. Read email content
2. Check for phishing patterns:
   - Analyze sender field
   - Scan for urgent/threatening language
   - Look for requests for passwords/financial data
   - Check for suspicious links or attachments
3. Assign phishing risk score
4. Display results and recommendations

---

### OPTION B: Check private IP ranges

This program validates and categorizes IP addresses as private or public based on RFC 1918 private IP ranges:
- **10.0.0.0 to 10.255.255.255** (10.0.0.0/8)
- **172.16.0.0 to 172.31.255.255** (172.16.0.0/12)
- **192.168.0.0 to 192.168.255.255** (192.168.0.0/16)

**Algorithm:**
1. Get IP address input
2. Parse IP octets
3. Check against private IP ranges
4. Return classification (private/public)
5. Display additional information

**Example:**
```
Check IP: 192.168.1.1 → PRIVATE
Check IP: 10.50.25.100 → PRIVATE
Check IP: 8.8.8.8 → PUBLIC
```

---

