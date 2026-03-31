# Slip 18 — Computer Networks Solution Guide

## Q1: Theory Questions (10 Marks - Answer ANY 5)

---

### a) In Cisco's Packet Tracer, which command is used to change the prompt from Router> to Router# mode?

#### Concept
Cisco routers have different privilege levels or modes. Each mode provides different access levels and capabilities.

#### Router Modes

| Mode | Prompt | Description |
|------|--------|-------------|
| User EXEC Mode | `Router>` | Basic monitoring, limited commands |
| Privileged EXEC Mode | `Router#` | Full access, configuration, debugging |
| Global Configuration | `Router(config)#` | System-wide configuration |
| Interface Configuration | `Router(config-if)#` | Interface-specific settings |

#### Command to Change from Router> to Router#

```
Router> enable
Router#
```

The **`enable`** command is used to enter Privileged EXEC Mode (Router#) from User EXEC Mode (Router>).

#### Complete Mode Navigation Commands

```
Router> enable                          ! User → Privileged
Router# configure terminal              ! Privileged → Global Config
Router(config)# interface fa0/0         ! Global → Interface Config
Router(config-if)# exit                 ! Back one level
Router(config)# exit                    ! Back to Privileged
Router# disable                         ! Privileged → User
Router>
```

#### Password Protection

To require a password for `enable`:
```
Router(config)# enable secret MyPassword
```

#### Summary
- **Command**: `enable`
- **Purpose**: Elevates privileges from User EXEC to Privileged EXEC
- **Prompt Change**: `Router>` → `Router#`

---

### b) Steps to Connect a PC to the Linksys Router's Web-Based Configuration Page and Default IP Address

#### Default IP Address
**Linksys Router Default IP**: `192.168.1.1`

Other common defaults:
| Manufacturer | Default IP | Default Gateway |
|--------------|------------|-----------------|
| Linksys | 192.168.1.1 | 192.168.1.1 |
| Netgear | 192.168.0.1 | 192.168.0.1 |
| TP-Link | 192.168.0.1 | 192.168.0.1 |
| D-Link | 192.168.0.1 | 192.168.0.1 |

#### Steps to Connect

##### Step 1: Physical Connection
1. Connect one end of an Ethernet cable to the PC's network port
2. Connect the other end to one of the LAN ports (1-4) on the Linksys router
3. Ensure the router is powered ON
4. Wait for link lights to show connection

##### Step 2: Configure PC IP Settings
**Option A: DHCP (Automatic)**
1. Open Network Settings on PC
2. Select the Ethernet adapter
3. Set to "Obtain an IP address automatically"
4. PC will receive IP like 192.168.1.x from router

**Option B: Static IP**
1. Go to Network Connections → Ethernet Properties
2. Select IPv4 → Properties
3. Configure:
   - IP Address: `192.168.1.10`
   - Subnet Mask: `255.255.255.0`
   - Default Gateway: `192.168.1.1`
   - DNS Server: `192.168.1.1`

##### Step 3: Access Web Configuration
1. Open a web browser (Chrome, Firefox, Edge)
2. Enter router IP in address bar: `http://192.168.1.1`
3. Press Enter

##### Step 4: Login to Router
1. Login page appears
2. Default credentials:
   - **Username**: (leave blank or `admin`)
   - **Password**: `admin`
3. Click Login/Submit

##### Step 5: Configure Router
- Change admin password (security)
- Configure wireless settings (SSID, password)
- Set up internet connection type
- Configure DHCP settings
- Enable/disable firewall

#### Troubleshooting
```
# Windows Command Prompt
C:\> ipconfig                    # Check IP configuration
C:\> ping 192.168.1.1           # Test connection to router
C:\> ipconfig /release          # Release DHCP lease
C:\> ipconfig /renew            # Get new DHCP lease
```

---

### c) What is Dynamic Routing? Give its Features

#### Concept
**Dynamic Routing** is a networking technique where routers automatically learn and share network topology information using routing protocols, without manual configuration.

#### How Dynamic Routing Works
```
+----------+       Routing       +----------+
| Router A | ← → Protocol Messages → ← → | Router B |
+----------+                     +----------+
     ↓ Learns routes automatically ↓
   Updates routing table when network changes
```

#### Comparison: Static vs Dynamic Routing

| Feature | Static Routing | Dynamic Routing |
|---------|---------------|-----------------|
| Configuration | Manual | Automatic |
| Scalability | Low | High |
| Bandwidth Usage | None | Uses bandwidth for updates |
| Adaptability | No auto-adjustment | Adapts to changes |
| CPU Usage | Low | Higher |
| Best For | Small networks | Large networks |

#### Dynamic Routing Protocols

| Protocol | Type | Algorithm | Use Case |
|----------|------|-----------|----------|
| RIP | Distance Vector | Bellman-Ford | Small networks |
| OSPF | Link State | Dijkstra's | Enterprise networks |
| EIGRP | Hybrid | DUAL | Cisco environments |
| BGP | Path Vector | Best Path | Internet backbone |
| IS-IS | Link State | SPF | Large ISP networks |

#### Features of Dynamic Routing

##### 1. Automatic Route Discovery
- Routers discover neighbors automatically
- Build routing tables without manual entry
- Learn optimal paths to all networks

##### 2. Self-Healing/Convergence
- Automatically detects link failures
- Recalculates alternative routes
- Network recovers without admin intervention

##### 3. Load Balancing
- Distributes traffic across multiple paths
- Improves network performance
- Supports equal-cost multipath (ECMP)

##### 4. Scalability
- Easily add new routers/networks
- Protocol handles topology changes
- Suitable for large enterprise networks

##### 5. Reduced Administrative Overhead
- No need to manually update every router
- Changes propagate automatically
- Less prone to human configuration errors

##### 6. Metric-Based Path Selection
- Uses metrics (hop count, bandwidth, delay)
- Chooses best path based on criteria
- Example: OSPF uses cost (100M/bandwidth)

##### 7. Neighbor Relationships
- Routers form adjacencies
- Exchange routing information
- Maintain state of neighbor routers

#### Configuration Example (Cisco OSPF)
```
Router(config)# router ospf 1
Router(config-router)# network 192.168.1.0 0.0.0.255 area 0
Router(config-router)# network 10.0.0.0 0.255.255.255 area 0
```

#### Configuration Example (Cisco RIP)
```
Router(config)# router rip
Router(config-router)# version 2
Router(config-router)# network 192.168.1.0
Router(config-router)# network 10.0.0.0
```

---

### d) List Commands Used for Network Address Translation (NAT) on Cisco's Packet Tracer

#### Concept
**NAT (Network Address Translation)** translates private IP addresses to public IP addresses, allowing multiple devices to share a single public IP.

#### NAT Configuration Commands

##### 1. Define Inside and Outside Interfaces
```
Router(config)# interface GigabitEthernet0/0
Router(config-if)# ip nat inside
Router(config-if)# exit

Router(config)# interface GigabitEthernet0/1  
Router(config-if)# ip nat outside
Router(config-if)# exit
```

##### 2. Static NAT (One-to-One Mapping)
```
! Map internal IP to external IP
Router(config)# ip nat inside source static 192.168.1.10 203.0.113.10

! For specific port (Port Forwarding)
Router(config)# ip nat inside source static tcp 192.168.1.10 80 203.0.113.10 8080
```

##### 3. Dynamic NAT (Pool of Public IPs)
```
! Create pool of public addresses
Router(config)# ip nat pool MYPOOL 203.0.113.1 203.0.113.10 netmask 255.255.255.0

! Define which internal addresses to translate (ACL)
Router(config)# access-list 1 permit 192.168.1.0 0.0.0.255

! Link ACL to NAT pool
Router(config)# ip nat inside source list 1 pool MYPOOL
```

##### 4. PAT / NAT Overload (Many-to-One)
```
! Using interface's IP address
Router(config)# access-list 1 permit 192.168.1.0 0.0.0.255
Router(config)# ip nat inside source list 1 interface GigabitEthernet0/1 overload

! Or using a pool with overload
Router(config)# ip nat inside source list 1 pool MYPOOL overload
```

##### 5. Verification Commands
```
Router# show ip nat translations          ! View NAT table
Router# show ip nat statistics            ! View NAT stats
Router# clear ip nat translation *        ! Clear all translations
Router# debug ip nat                      ! Enable NAT debugging
Router# show running-config | section nat ! View NAT config
```

#### NAT Types Summary Table

| NAT Type | Command | Use Case |
|----------|---------|----------|
| Static NAT | `ip nat inside source static` | Servers needing public access |
| Dynamic NAT | `ip nat inside source list pool` | Many hosts, many public IPs |
| PAT/Overload | `ip nat inside source list ... overload` | Many hosts, one public IP |

#### Complete Configuration Example
```
! Configure interfaces
Router(config)# interface GigabitEthernet0/0
Router(config-if)# ip address 192.168.1.1 255.255.255.0
Router(config-if)# ip nat inside
Router(config-if)# no shutdown
Router(config-if)# exit

Router(config)# interface GigabitEthernet0/1
Router(config-if)# ip address 203.0.113.1 255.255.255.0
Router(config-if)# ip nat outside
Router(config-if)# no shutdown
Router(config-if)# exit

! Configure PAT
Router(config)# access-list 1 permit 192.168.1.0 0.0.0.255
Router(config)# ip nat inside source list 1 interface GigabitEthernet0/1 overload

! Verify
Router# show ip nat translations
```

---

### f) Explain Steps to Identify a Phishing Email

#### Concept
**Phishing** is a social engineering attack where attackers send fraudulent emails disguised as legitimate communications to steal sensitive information (passwords, credit cards, personal data).

#### Steps to Identify Phishing Emails

##### Step 1: Check the Sender's Email Address
```
Legitimate:  support@paypal.com
Phishing:    support@paypa1.com (using '1' instead of 'l')
             support@paypal-security.com (added domain)
             support@paypal.suspicious.com (subdomain trick)
```

**What to look for:**
- Misspelled domain names
- Extra characters or numbers
- Unusual domain extensions
- Different reply-to address

##### Step 2: Examine the Subject Line
**Red flags:**
- Urgent action required: "Your account will be closed!"
- Threats: "Unauthorized access detected!"
- Too good to be true: "You've won $1,000,000!"
- Suspicious urgency: "Act within 24 hours"

##### Step 3: Hover Over Links (Don't Click!)
```
Displayed text:  www.paypal.com/login
Actual URL:      www.phishing-site.com/paypal

Check by hovering to see the real destination in browser status bar
```

**What to check:**
- Does the URL match the displayed text?
- Is it using HTTP instead of HTTPS?
- Are there misspellings in the URL?
- Is it using URL shorteners (bit.ly, tinyurl)?

##### Step 4: Look for Grammar and Spelling Errors
**Phishing indicators:**
- Poor grammar: "Your account have been suspended"
- Spelling mistakes: "We have detcted unusual activity"
- Unusual formatting or inconsistent fonts
- Machine-translated text

##### Step 5: Check for Generic Greetings
```
Legitimate:  "Dear John Smith,"
Phishing:    "Dear Customer,"
             "Dear User,"
             "Dear Account Holder,"
```

##### Step 6: Verify Attachments Are Expected
**Dangerous attachment types:**
- `.exe`, `.bat`, `.cmd` (executables)
- `.zip`, `.rar` with password in email
- `.doc`, `.xls` asking to "enable macros"
- `.html`, `.htm` files

##### Step 7: Check for Requests for Sensitive Information
**Legitimate companies NEVER ask via email for:**
- Passwords
- Credit card numbers
- Social Security numbers
- PINs or OTPs
- Full account numbers

##### Step 8: Verify Through Official Channels
1. Don't click links in the email
2. Open a new browser window
3. Type the official website URL manually
4. Log in and check for alerts/messages
5. Call the company's official phone number

##### Step 9: Check Email Headers (Advanced)
```
View email headers to verify:
- Received: from (actual sending server)
- Return-Path: (where replies go)
- SPF/DKIM/DMARC: (authentication status)
```

#### Quick Checklist
```
[ ] Sender email matches official domain
[ ] No urgent/threatening language
[ ] Links point to legitimate URLs
[ ] No grammar/spelling errors
[ ] Personalized greeting (not generic)
[ ] No unexpected attachments
[ ] No requests for sensitive info
[ ] Company logo/branding looks correct
```

#### Example Phishing Email Analysis
```
From: security@amazon-verify.com        ← Fake domain!
Subject: URGENT: Verify your account NOW! ← Fear/urgency
--------------------------------------------------------
Dear Customer,                          ← Generic greeting

Your amazon account has been compromized. ← Spelling error
Click here to verify: [Verify Now]      ← Suspicious link
                      (points to malicious site)

If you don't act in 24 hours, your      ← Urgency/threat
account will be permanantly closed.     ← Spelling error

Amazon Security Team                    ← Generic signature
```

---

### g) Perform Dictionary Attack on SHA256 Hash Using Hashcat

#### Concept
**Dictionary Attack**: A method of cracking passwords by systematically testing each word from a pre-compiled list (dictionary/wordlist) until the correct password is found.

**SHA256**: A cryptographic hash function that produces a 256-bit (32-byte) hash value, commonly used for password storage.

#### Prerequisites
```bash
# Install Hashcat on Linux
sudo apt update
sudo apt install hashcat

# Verify installation
hashcat --version
```

#### Step 1: Create a Hash File
```bash
# Create file containing the SHA256 hash to crack
echo "5e884898da28047d9e8a52c8bfe11a3df7f24e8e0f7f2fb9b3f3e3c3e3c3e3c3" > hash.txt

# Or if you have a password and want to test:
echo -n "password123" | sha256sum
# Output: ef92b778bafe771e89245b89ecbc08a44a4e166c06659911881f383d4473e94f
```

#### Step 2: Obtain/Create a Wordlist
```bash
# Common wordlist locations on Kali Linux
/usr/share/wordlists/rockyou.txt
/usr/share/wordlists/dirb/common.txt

# Create a simple test wordlist
cat > wordlist.txt << EOF
password
123456
password123
admin
letmein
qwerty
welcome
monkey
dragon
master
EOF

# Download rockyou.txt (if not available)
wget https://github.com/brannondorsey/naive-hashcat/releases/download/data/rockyou.txt
```

#### Step 3: Identify Hash Type
```
Hashcat Hash Mode for SHA256: 1400

Common hash modes:
- 0     = MD5
- 100   = SHA1
- 1400  = SHA256
- 1700  = SHA512
- 3200  = bcrypt
- 1000  = NTLM
```

#### Step 4: Run Hashcat Dictionary Attack
```bash
# Basic syntax
hashcat -m <hash_mode> -a 0 <hash_file> <wordlist>

# SHA256 Dictionary Attack
hashcat -m 1400 -a 0 hash.txt wordlist.txt

# With options
hashcat -m 1400 -a 0 hash.txt rockyou.txt --force -o cracked.txt

# Explanation:
# -m 1400     : Hash type (SHA256)
# -a 0        : Attack mode (0 = straight/dictionary)
# hash.txt    : File containing hash to crack
# wordlist.txt: Dictionary file
# --force     : Ignore warnings (use if needed)
# -o cracked.txt : Output file for cracked passwords
```

#### Step 5: Useful Hashcat Options
```bash
# Show status during cracking
hashcat -m 1400 -a 0 hash.txt wordlist.txt --status

# Use rules to modify wordlist words
hashcat -m 1400 -a 0 hash.txt wordlist.txt -r /usr/share/hashcat/rules/best64.rule

# Use GPU (faster)
hashcat -m 1400 -a 0 hash.txt wordlist.txt -d 1

# Restore a previous session
hashcat --restore

# Show cracked passwords
hashcat -m 1400 hash.txt --show
```

#### Complete Example Session
```bash
# 1. Create test hash (password is "monkey")
echo -n "monkey" | sha256sum | awk '{print $1}' > hash.txt
cat hash.txt
# 000c285457fc971f862a79b786476c78812c8897063c6fa9c045f579a3b2d63f

# 2. Create wordlist
echo -e "password\n123456\nmonkey\nadmin\nqwerty" > wordlist.txt

# 3. Run hashcat
hashcat -m 1400 -a 0 hash.txt wordlist.txt

# 4. Expected output:
# 000c285457fc971f862a79b786476c78812c8897063c6fa9c045f579a3b2d63f:monkey
# Status: Cracked

# 5. View cracked password
hashcat -m 1400 hash.txt --show
```

#### Attack Modes Reference
| Mode | Type | Description |
|------|------|-------------|
| -a 0 | Dictionary | Straight wordlist attack |
| -a 1 | Combination | Combine two wordlists |
| -a 3 | Brute Force | Try all combinations |
| -a 6 | Hybrid | Wordlist + mask |
| -a 7 | Hybrid | Mask + wordlist |

#### Legal Disclaimer
⚠️ **IMPORTANT**: Only use Hashcat for:
- Testing your own password security
- Authorized penetration testing
- Educational purposes with proper permission

Unauthorized password cracking is illegal and unethical.

---

## Q2: Practical Questions (20 Marks)

---

## Option A: Phishing Simulation Program

### Concept
A phishing simulation demonstrates how attackers collect credentials through fake login pages. This educational program shows the mechanics without actual malicious intent.

### Algorithm
```
1. START
2. Display fake login prompt (mimicking legitimate site)
3. Collect username from user
4. Collect password from user (hidden input)
5. Log captured credentials
6. Display "authentication failed" message (typical phishing behavior)
7. Show educational warning about phishing
8. END
```

### Pseudocode
```
FUNCTION phishingSimulation():
    clearScreen()
    displayFakeBanner("SECURE BANK LOGIN")
    
    PRINT "Please enter your credentials"
    
    username = INPUT("Username: ")
    password = INPUT_HIDDEN("Password: ")
    
    timestamp = getCurrentTime()
    
    logCredentials(timestamp, username, password)
    
    PRINT "Authentication failed. Please try again."
    PRINT "(This was a simulation - never enter real credentials)"
    
    displayPhishingWarnings()

FUNCTION displayPhishingWarnings():
    PRINT "=== PHISHING AWARENESS ==="
    PRINT "Signs of phishing:"
    PRINT "- Suspicious URLs"
    PRINT "- Urgent/threatening language"
    PRINT "- Generic greetings"
    PRINT "- Requests for sensitive info"
```

### Time & Space Complexity
| Operation | Time | Space |
|-----------|------|-------|
| Display prompt | O(1) | O(1) |
| Capture input | O(n) | O(n) where n = input length |
| Log to file | O(n) | O(1) |

---

## Option B: NAT System Simulation

### Concept
**Network Address Translation (NAT)** allows multiple devices on a private network to access the internet using a single public IP address. This simulation demonstrates:
- Private to public IP translation
- Port mapping for multiple connections
- Translation table management

### NAT Types
| Type | Description | Use Case |
|------|-------------|----------|
| Static NAT | 1:1 mapping | Servers |
| Dynamic NAT | Pool of public IPs | Medium networks |
| PAT/Overload | Many:1 using ports | Home/office networks |

### Algorithm
```
1. START
2. Initialize NAT table (empty)
3. Initialize public IP and port range
4. LOOP:
   a. Receive packet from internal network
   b. Check if translation exists in NAT table
   c. If not exists:
      - Allocate new public port
      - Create NAT table entry (private_ip:port → public_ip:port)
   d. Translate source address
   e. Forward packet to destination
   f. For return traffic:
      - Look up translation in NAT table
      - Translate destination back to private address
5. END
```

### Pseudocode
```
STRUCTURE NATEntry:
    private_ip: STRING
    private_port: INTEGER
    public_port: INTEGER
    protocol: STRING
    destination: STRING
    timestamp: TIME

GLOBAL nat_table: ARRAY of NATEntry
GLOBAL public_ip: STRING = "203.0.113.1"
GLOBAL next_port: INTEGER = 10000

FUNCTION translateOutgoing(private_ip, private_port, dest_ip, dest_port):
    // Check for existing translation
    FOR entry IN nat_table:
        IF entry.private_ip == private_ip AND entry.private_port == private_port:
            RETURN (public_ip, entry.public_port)
    
    // Create new translation
    new_entry = CREATE NATEntry
    new_entry.private_ip = private_ip
    new_entry.private_port = private_port
    new_entry.public_port = next_port++
    new_entry.timestamp = NOW()
    
    ADD new_entry TO nat_table
    
    RETURN (public_ip, new_entry.public_port)

FUNCTION translateIncoming(public_port):
    FOR entry IN nat_table:
        IF entry.public_port == public_port:
            RETURN (entry.private_ip, entry.private_port)
    
    RETURN NULL  // No translation found

FUNCTION displayNATTable():
    PRINT "=== NAT Translation Table ==="
    PRINT "Private IP:Port  →  Public IP:Port"
    FOR entry IN nat_table:
        PRINT entry.private_ip:entry.private_port → public_ip:entry.public_port
```

### Time & Space Complexity
| Operation | Time | Space |
|-----------|------|-------|
| Add translation | O(n) lookup, O(1) insert | O(1) |
| Lookup translation | O(n) | O(1) |
| Display table | O(n) | O(1) |
| Total table | - | O(n) where n = active connections |

---

## Option C: Bus Topology with 4 PCs in Packet Tracer

### Configuration Details

| PC | IP Address | Subnet Mask | Gateway |
|----|------------|-------------|---------|
| PC0 | 192.168.1.1 | 255.255.255.0 | - |
| PC1 | 192.168.1.2 | 255.255.255.0 | - |
| PC2 | 192.168.1.3 | 255.255.255.0 | - |
| PC3 | 192.168.1.4 | 255.255.255.0 | - |

### Steps in Packet Tracer

#### Step 1: Add Devices
1. Open Cisco Packet Tracer
2. From End Devices, drag 4 PCs to workspace
3. From Network Devices → Hubs, drag a Hub (for bus simulation)

#### Step 2: Connect Devices
1. Select Connections → Copper Straight-Through cable
2. Connect PC0 FastEthernet0 → Hub Port0
3. Connect PC1 FastEthernet0 → Hub Port1
4. Connect PC2 FastEthernet0 → Hub Port2
5. Connect PC3 FastEthernet0 → Hub Port3

#### Step 3: Configure IP Addresses

**PC0:**
1. Click PC0 → Desktop → IP Configuration
2. Select Static
3. Enter:
   - IP Address: `192.168.1.1`
   - Subnet Mask: `255.255.255.0`

**PC1:**
1. Click PC1 → Desktop → IP Configuration
2. Enter:
   - IP Address: `192.168.1.2`
   - Subnet Mask: `255.255.255.0`

**PC2:**
1. Click PC2 → Desktop → IP Configuration
2. Enter:
   - IP Address: `192.168.1.3`
   - Subnet Mask: `255.255.255.0`

**PC3:**
1. Click PC3 → Desktop → IP Configuration
2. Enter:
   - IP Address: `192.168.1.4`
   - Subnet Mask: `255.255.255.0`

#### Step 4: Verify Connectivity
From PC0 Command Prompt:
```
C:\> ping 192.168.1.2
C:\> ping 192.168.1.3
C:\> ping 192.168.1.4
```

### Bus Topology Characteristics
- All devices share single communication line
- Hub broadcasts to all ports (simulates bus)
- Collision domain = entire network
- Simple but not scalable
- Single point of failure at hub

### Network Diagram
```
         HUB (Bus Simulation)
    ┌──────┬──────┬──────┐
    │      │      │      │
   PC0    PC1    PC2    PC3
192.168  192.168  192.168  192.168
  .1.1    .1.2    .1.3    .1.4
```

---

> **Solution Code:** See `Slip_18_Q2_OptionA.c` and `Slip_18_Q2_OptionB.c` in this folder.
