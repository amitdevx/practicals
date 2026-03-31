# Slip 17 — Computer Networks Solution Guide

## Q1: Theory Questions (10 Marks - Answer ANY 5)

---

### a) What is the primary purpose of a banner MOTD?

#### Concept
A **Banner MOTD** (Message of the Day) is a configurable message displayed to users when they connect to a network device (router, switch, or server).

#### Primary Purpose
1. **Legal Notice**: Displays warnings about unauthorized access
2. **Security Deterrent**: Warns potential intruders of legal consequences
3. **Information Display**: Provides system information, maintenance schedules
4. **Compliance**: Meets legal requirements for access warnings
5. **User Notification**: Communicates important messages to all users

#### Why It's Important
```
┌─────────────────────────────────────────────────────────────┐
│  AUTHORIZED ACCESS ONLY!                                     │
│  This system is for authorized users only.                   │
│  Unauthorized access is prohibited and will be prosecuted.   │
│  All activities are monitored and logged.                    │
└─────────────────────────────────────────────────────────────┘
```

#### Cisco IOS Configuration
```
Router> enable
Router# configure terminal
Router(config)# banner motd #
Enter TEXT message. End with the character '#'.
*** WARNING: Unauthorized access is prohibited ***
*** All activities are monitored and logged ***
#
Router(config)# exit
```

#### Types of Banners in Cisco
| Banner Type | Command | When Displayed |
|-------------|---------|----------------|
| MOTD | `banner motd` | First, to all users |
| Login | `banner login` | Before authentication prompt |
| Exec | `banner exec` | After successful login |
| Incoming | `banner incoming` | For reverse Telnet sessions |

#### Best Practices
- ✅ Include legal warning about unauthorized access
- ✅ Mention monitoring and logging
- ❌ Don't include system type, OS version, or hostnames
- ❌ Don't use "Welcome" (implies invitation to hackers)

---

### b) Benefits and Limitations of Packet Tracer

#### What is Packet Tracer?
Cisco Packet Tracer is a **network simulation software** that allows users to create, configure, and troubleshoot networks in a virtual environment.

#### Benefits of Using Packet Tracer

| Benefit | Description |
|---------|-------------|
| **Cost-Free Learning** | No need to purchase expensive hardware |
| **Safe Environment** | Mistakes don't affect real networks |
| **Visualization** | See packet flow in real-time |
| **Accessibility** | Run complex topologies on any computer |
| **Repeatability** | Save, share, and reload configurations |
| **Multi-Protocol Support** | Supports routing, switching, wireless, IoT |
| **Assessment Ready** | Built-in activity grading for education |

#### Limitations Compared to Real Hardware

| Limitation | Impact |
|------------|--------|
| **Limited IOS Features** | Not all Cisco commands are available |
| **Simplified Behavior** | Some protocols behave differently |
| **No Physical Issues** | Can't simulate cable faults, hardware failures |
| **Performance Not Realistic** | No real latency, throughput constraints |
| **Limited Device Models** | Fewer device options than real world |
| **No Third-Party Equipment** | Only Cisco devices (mostly) |
| **Timing Differences** | Convergence times may differ from reality |

#### Comparison Table
| Aspect | Packet Tracer | Real Hardware |
|--------|---------------|---------------|
| Cost | Free | $100s - $1000s per device |
| Risk | None | Can disrupt live networks |
| Commands | ~70% coverage | 100% IOS features |
| Physical Layer | Simulated | Real cables, ports, LEDs |
| Performance | Idealized | Real-world constraints |
| Troubleshooting | Limited | Full diagnostic tools |

---

### c) Differentiate between Static NAT, Dynamic NAT, and PAT

#### What is NAT?
**Network Address Translation (NAT)** translates private IP addresses to public IP addresses, allowing multiple devices to share limited public IPs.

#### Types of NAT Comparison

| Feature | Static NAT | Dynamic NAT | PAT (Overload) |
|---------|------------|-------------|----------------|
| **Mapping** | One-to-One | One-to-One (from pool) | Many-to-One |
| **IP Allocation** | Permanent | Temporary | Shared |
| **Public IPs Needed** | 1 per private IP | Pool of IPs | 1 (or few) |
| **Use Case** | Servers | Medium networks | Home/Office |
| **Port Translation** | No | No | Yes |
| **Scalability** | Poor | Medium | Excellent |

#### 1. Static NAT
```
Private IP          Public IP
192.168.1.10  <-->  203.0.113.10   (permanent mapping)
192.168.1.11  <-->  203.0.113.11   (permanent mapping)
```
**Use Case**: Web servers, mail servers that need consistent public IP

#### 2. Dynamic NAT
```
Private IP          Public IP Pool
192.168.1.10  <-->  203.0.113.10   (temporary)
192.168.1.11  <-->  203.0.113.11   (temporary)
192.168.1.12  <-->  [waiting]      (pool exhausted)
```
**Use Case**: Organizations with multiple public IPs but not enough for all hosts

#### 3. PAT (Port Address Translation / NAT Overload)
```
Private IP:Port          Public IP:Port
192.168.1.10:5001  <-->  203.0.113.1:40001
192.168.1.11:5002  <-->  203.0.113.1:40002
192.168.1.12:5003  <-->  203.0.113.1:40003
```
**Use Case**: Home routers, small offices (most common type)

#### Diagram
```
            STATIC NAT                    PAT (Overload)
    ┌──────────────────┐           ┌──────────────────┐
    │ 192.168.1.10     │           │ 192.168.1.10:5001│─┐
    │      ↓           │           │ 192.168.1.11:5002│─┼─→ 203.0.113.1:4xxxx
    │ 203.0.113.10     │           │ 192.168.1.12:5003│─┘
    └──────────────────┘           └──────────────────┘
       1:1 Mapping                    Many:1 Mapping
```

---

### d) NAT Commands in Cisco Packet Tracer

#### Basic NAT Configuration Commands

##### Define Inside and Outside Interfaces
```
Router(config)# interface GigabitEthernet0/0
Router(config-if)# ip nat inside
Router(config-if)# exit

Router(config)# interface GigabitEthernet0/1  
Router(config-if)# ip nat outside
Router(config-if)# exit
```

##### Static NAT Configuration
```
Router(config)# ip nat inside source static 192.168.1.10 203.0.113.10
```

##### Dynamic NAT Configuration
```
! Define NAT pool
Router(config)# ip nat pool MYPOOL 203.0.113.1 203.0.113.10 netmask 255.255.255.0

! Define access list for internal hosts
Router(config)# access-list 1 permit 192.168.1.0 0.0.0.255

! Link ACL to NAT pool
Router(config)# ip nat inside source list 1 pool MYPOOL
```

##### PAT (Overload) Configuration
```
! Using interface IP
Router(config)# access-list 1 permit 192.168.1.0 0.0.0.255
Router(config)# ip nat inside source list 1 interface GigabitEthernet0/1 overload

! Or using pool with overload
Router(config)# ip nat inside source list 1 pool MYPOOL overload
```

#### Verification Commands
| Command | Purpose |
|---------|---------|
| `show ip nat translations` | View NAT table |
| `show ip nat statistics` | View NAT stats |
| `clear ip nat translation *` | Clear all translations |
| `debug ip nat` | Debug NAT operations |

#### Example Output
```
Router# show ip nat translations
Pro Inside global      Inside local       Outside local      Outside global
tcp 203.0.113.1:40001  192.168.1.10:5001  8.8.8.8:80        8.8.8.8:80
tcp 203.0.113.1:40002  192.168.1.11:5002  8.8.8.8:443       8.8.8.8:443
```

---

### f) Using Netstat Command to View Active Connections

#### What is Netstat?
**Netstat** (Network Statistics) is a command-line tool that displays network connections, routing tables, interface statistics, and protocol information.

#### Basic Netstat Commands

##### Windows
```cmd
# Show all active connections
netstat

# Show all connections with process ID
netstat -ano

# Show listening ports only
netstat -an | findstr LISTENING

# Show specific protocol
netstat -p tcp
netstat -p udp

# Show with executable names
netstat -b

# Continuous monitoring (refresh every 5 seconds)
netstat -an 5
```

##### Linux/macOS
```bash
# Show all connections
netstat -a

# Show listening ports
netstat -l

# Show with process names
netstat -p

# Show TCP connections only
netstat -t

# Show UDP connections only
netstat -u

# Numeric output (no DNS resolution)
netstat -n

# Combined common usage
netstat -tulpn

# Alternative modern command (Linux)
ss -tulpn
```

#### Common Netstat Options
| Option | Windows | Linux | Description |
|--------|---------|-------|-------------|
| `-a` | ✓ | ✓ | All connections and listening ports |
| `-n` | ✓ | ✓ | Numeric addresses (no DNS lookup) |
| `-o` | ✓ | ✗ | Show process ID (PID) |
| `-p` | Protocol | Show process | Platform-specific |
| `-b` | ✓ | ✗ | Show executable name |
| `-t` | ✗ | ✓ | TCP only |
| `-u` | ✗ | ✓ | UDP only |
| `-l` | ✗ | ✓ | Listening only |
| `-r` | ✓ | ✓ | Routing table |
| `-s` | ✓ | ✓ | Statistics by protocol |

#### Sample Output
```
Active Connections

  Proto  Local Address          Foreign Address        State           PID
  TCP    0.0.0.0:80             0.0.0.0:0              LISTENING       4
  TCP    0.0.0.0:443            0.0.0.0:0              LISTENING       4
  TCP    192.168.1.10:52341     142.250.190.4:443      ESTABLISHED     15832
  TCP    192.168.1.10:52342     20.190.160.20:443      TIME_WAIT       0
  UDP    0.0.0.0:53             *:*                                    1832
```

#### Connection States Explained
| State | Description |
|-------|-------------|
| LISTENING | Waiting for incoming connections |
| ESTABLISHED | Active connection |
| TIME_WAIT | Waiting after close to handle delayed packets |
| CLOSE_WAIT | Remote side has closed, waiting for local close |
| SYN_SENT | Connection request sent |
| SYN_RECEIVED | Connection request received |
| FIN_WAIT | Waiting for FIN from remote |

#### Practical Usage Examples
```bash
# Find what's using port 80
netstat -ano | findstr :80        # Windows
netstat -tulpn | grep :80         # Linux

# Count connections by state
netstat -an | findstr ESTABLISHED | find /c /v ""   # Windows
netstat -an | grep ESTABLISHED | wc -l              # Linux

# Find all connections to a specific IP
netstat -an | findstr 192.168.1.100
```

---

### g) What is the primary purpose of a banner MOTD?

**(Same as Question a - See answer above)**

---

## Q2: Practical Questions (20 Marks)

---

## Option A: Password Security Checker with Special Characters

### Concept
A comprehensive password security checker validates passwords against multiple security criteria including:
- Minimum length requirements
- Uppercase letter presence
- Lowercase letter presence  
- Digit/number presence
- Special character presence

### Password Security Requirements

| Criterion | Requirement | Reason |
|-----------|-------------|--------|
| Length | ≥ 8 characters | Increases brute-force time |
| Uppercase | At least 1 (A-Z) | Expands character space |
| Lowercase | At least 1 (a-z) | Expands character space |
| Digit | At least 1 (0-9) | Adds numeric complexity |
| Special Char | At least 1 (!@#$%^&*) | Maximum entropy |

### Algorithm

```
FUNCTION checkPassword(password):
    // Initialize flags
    hasMinLength = FALSE
    hasUppercase = FALSE
    hasLowercase = FALSE
    hasDigit = FALSE
    hasSpecial = FALSE
    
    // Check minimum length
    IF length(password) >= 8:
        hasMinLength = TRUE
    
    // Scan each character
    FOR each char c in password:
        IF c >= 'A' AND c <= 'Z':
            hasUppercase = TRUE
        ELSE IF c >= 'a' AND c <= 'z':
            hasLowercase = TRUE
        ELSE IF c >= '0' AND c <= '9':
            hasDigit = TRUE
        ELSE IF c is in "!@#$%^&*()-_=+[]{}|;:',.<>?/`~":
            hasSpecial = TRUE
    
    // Evaluate results
    IF all flags are TRUE:
        RETURN "STRONG - Password meets all criteria"
    ELSE:
        PRINT missing criteria
        RETURN "WEAK - Password needs improvement"
```

### Pseudocode

```
PROGRAM PasswordSecurityChecker:
    DEFINE specialChars = "!@#$%^&*()-_=+[]{}|;:',.<>?/`~"
    
    PRINT "Enter password to check: "
    READ password
    
    length = 0
    hasUpper = hasLower = hasDigit = hasSpecial = FALSE
    
    WHILE password[length] != '\0':
        ch = password[length]
        
        IF ch >= 'A' AND ch <= 'Z':
            hasUpper = TRUE
        
        IF ch >= 'a' AND ch <= 'z':
            hasLower = TRUE
        
        IF ch >= '0' AND ch <= '9':
            hasDigit = TRUE
        
        IF ch IN specialChars:
            hasSpecial = TRUE
        
        length++
    
    PRINT "Password Analysis:"
    PRINT "=================="
    
    IF length >= 8:
        PRINT "[✓] Length requirement (≥8 characters)"
    ELSE:
        PRINT "[✗] Length requirement (need " + (8 - length) + " more)"
    
    IF hasUpper:
        PRINT "[✓] Contains uppercase letter"
    ELSE:
        PRINT "[✗] Missing uppercase letter"
    
    IF hasLower:
        PRINT "[✓] Contains lowercase letter"
    ELSE:
        PRINT "[✗] Missing lowercase letter"
    
    IF hasDigit:
        PRINT "[✓] Contains digit"
    ELSE:
        PRINT "[✗] Missing digit"
    
    IF hasSpecial:
        PRINT "[✓] Contains special character"
    ELSE:
        PRINT "[✗] Missing special character"
    
    // Calculate strength score
    score = 0
    IF length >= 8: score++
    IF hasUpper: score++
    IF hasLower: score++
    IF hasDigit: score++
    IF hasSpecial: score++
    
    PRINT "\nStrength: " + score + "/5"
    
    IF score == 5:
        PRINT "Password is STRONG"
    ELSE IF score >= 3:
        PRINT "Password is MEDIUM"
    ELSE:
        PRINT "Password is WEAK"
```

### Time & Space Complexity
| Operation | Time | Space |
|-----------|------|-------|
| Password Check | O(n × m) | O(1) |

Where n = password length, m = special characters count

### Worked Example

```
Input: "MyPass123!"

Analysis:
- Length: 10 chars (≥8) ✓
- Uppercase: 'M', 'P' present ✓
- Lowercase: 'y', 'a', 's', 's' present ✓
- Digit: '1', '2', '3' present ✓
- Special: '!' present ✓

Score: 5/5 - STRONG PASSWORD
```

```
Input: "password"

Analysis:
- Length: 8 chars (≥8) ✓
- Uppercase: None ✗
- Lowercase: All lowercase ✓
- Digit: None ✗
- Special: None ✗

Score: 2/5 - WEAK PASSWORD
```

---

## Option B: Plain Message to Cipher Message Encryption

### Concept
**Encryption** transforms readable plaintext into unreadable ciphertext to protect data confidentiality. The **Caesar Cipher** is a classic substitution cipher where each letter is shifted by a fixed number of positions.

### Types of Simple Ciphers

| Cipher Type | Method | Example (key=3) |
|-------------|--------|-----------------|
| Caesar Cipher | Shift letters by key | A→D, B→E, Z→C |
| ROT13 | Fixed shift of 13 | A→N, N→A |
| Atbash | Reverse alphabet | A→Z, B→Y |
| Substitution | Custom mapping | A→X, B→Q, ... |

### Caesar Cipher Algorithm

```
FUNCTION encrypt(plaintext, key):
    ciphertext = ""
    
    FOR each character c in plaintext:
        IF c is uppercase letter:
            // Shift within A-Z range
            newChar = ((c - 'A' + key) MOD 26) + 'A'
            ciphertext += newChar
        
        ELSE IF c is lowercase letter:
            // Shift within a-z range
            newChar = ((c - 'a' + key) MOD 26) + 'a'
            ciphertext += newChar
        
        ELSE:
            // Keep non-alphabetic characters unchanged
            ciphertext += c
    
    RETURN ciphertext

FUNCTION decrypt(ciphertext, key):
    // Decryption is encryption with negative key
    RETURN encrypt(ciphertext, 26 - key)
```

### Mathematical Formula

```
Encryption: E(x) = (x + key) mod 26
Decryption: D(x) = (x - key) mod 26
           OR
           D(x) = (x + (26 - key)) mod 26

Where x = position of letter (A=0, B=1, ..., Z=25)
```

### Pseudocode

```
PROGRAM CipherEncryption:
    PRINT "=== Caesar Cipher Encryption ==="
    PRINT "Enter the plaintext message: "
    READ plaintext
    
    PRINT "Enter the shift key (1-25): "
    READ key
    
    // Normalize key to 0-25 range
    key = key MOD 26
    IF key < 0:
        key = key + 26
    
    // Encrypt the message
    ciphertext = ""
    
    FOR i = 0 TO length(plaintext) - 1:
        ch = plaintext[i]
        
        IF ch >= 'A' AND ch <= 'Z':
            // Uppercase encryption
            shifted = ch - 'A'           // Convert to 0-25
            shifted = (shifted + key) MOD 26
            newCh = shifted + 'A'        // Convert back to char
            ciphertext += newCh
        
        ELSE IF ch >= 'a' AND ch <= 'z':
            // Lowercase encryption
            shifted = ch - 'a'           // Convert to 0-25
            shifted = (shifted + key) MOD 26
            newCh = shifted + 'a'        // Convert back to char
            ciphertext += newCh
        
        ELSE:
            // Non-alphabetic (spaces, punctuation)
            ciphertext += ch
    
    PRINT "\nEncryption Results:"
    PRINT "==================="
    PRINT "Plaintext:  " + plaintext
    PRINT "Key:        " + key
    PRINT "Ciphertext: " + ciphertext
    
    // Also decrypt to verify
    PRINT "\nDecryption Verification:"
    decryptKey = 26 - key
    decrypted = encrypt(ciphertext, decryptKey)
    PRINT "Decrypted:  " + decrypted
```

### Time & Space Complexity
| Operation | Time | Space |
|-----------|------|-------|
| Encrypt/Decrypt | O(n) | O(n) |

Where n = length of message

### Worked Example

```
Plaintext: "HELLO WORLD"
Key: 3

Character-by-character encryption:
H → (7 + 3) mod 26 = 10 → K
E → (4 + 3) mod 26 = 7  → H
L → (11 + 3) mod 26 = 14 → O
L → (11 + 3) mod 26 = 14 → O
O → (14 + 3) mod 26 = 17 → R
(space remains space)
W → (22 + 3) mod 26 = 25 → Z
O → (14 + 3) mod 26 = 17 → R
R → (17 + 3) mod 26 = 20 → U
L → (11 + 3) mod 26 = 14 → O
D → (3 + 3) mod 26 = 6  → G

Ciphertext: "KHOOR ZRUOG"
```

### Decryption Example
```
Ciphertext: "KHOOR ZRUOG"
Key: 3 (Decrypt key = 26 - 3 = 23)

K → (10 + 23) mod 26 = 7  → H
H → (7 + 23) mod 26 = 4   → E
O → (14 + 23) mod 26 = 11 → L
...

Plaintext: "HELLO WORLD"
```

### Cipher Alphabet Reference (Key=3)
```
Plain:  A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
Cipher: D E F G H I J K L M N O P Q R S T U V W X Y Z A B C
```

---

## Option C: Subnetting in Packet Tracer

### Given Information
- **Network Address**: 192.168.10.0/25
- **PC Configuration**: 172.16.1.1 and 172.16.1.2
- **Subnet Mask**: 255.255.0.0 (/16)
- **Switch Connection**: 2 PCs through switch

### Part 1: Subnetting 192.168.10.0/25

#### Step-by-Step Calculation

```
Given: 192.168.10.0/25

Step 1: Determine subnet mask
/25 = 25 network bits = 11111111.11111111.11111111.10000000
Subnet Mask = 255.255.255.128

Step 2: Calculate host bits
Host bits = 32 - 25 = 7 bits

Step 3: Calculate addresses per subnet
Total addresses = 2^7 = 128
Usable hosts = 128 - 2 = 126 (excluding network & broadcast)

Step 4: Calculate block size
Block size = 256 - 128 = 128
```

#### Subnet Details
| Subnet | Network Address | First Host | Last Host | Broadcast |
|--------|-----------------|------------|-----------|-----------|
| 0 | 192.168.10.0 | 192.168.10.1 | 192.168.10.126 | 192.168.10.127 |
| 1 | 192.168.10.128 | 192.168.10.129 | 192.168.10.254 | 192.168.10.255 |

### Part 2: PC Configuration (172.16.1.0/16 Network)

#### Network Setup Diagram
```
         172.16.1.0/16 Network
    ┌──────────────────────────────┐
    │                              │
    │   ┌────┐      ┌────────┐     │
    │   │PC1 │──────│ Switch │     │
    │   └────┘      │        │     │
    │  172.16.1.1   │        │     │
    │               │        │     │
    │   ┌────┐      │        │     │
    │   │PC2 │──────│        │     │
    │   └────┘      └────────┘     │
    │  172.16.1.2                  │
    │                              │
    └──────────────────────────────┘
```

#### PC Configuration Table
| Device | IP Address | Subnet Mask | Default Gateway |
|--------|------------|-------------|-----------------|
| PC1 | 172.16.1.1 | 255.255.0.0 | 172.16.1.254 (optional) |
| PC2 | 172.16.1.2 | 255.255.0.0 | 172.16.1.254 (optional) |

### Packet Tracer Configuration Steps

#### Step 1: Create Topology
1. Open Cisco Packet Tracer
2. Add a **2960 Switch** from network devices
3. Add **2 PCs** from end devices
4. Connect PC1 to Switch (FastEthernet0)
5. Connect PC2 to Switch (FastEthernet1)
6. Use **Copper Straight-Through** cables

#### Step 2: Configure PC1
1. Click on PC1 → **Desktop** tab → **IP Configuration**
2. Select **Static**
3. Enter:
   - IP Address: `172.16.1.1`
   - Subnet Mask: `255.255.0.0`
   - (Gateway: optional for same subnet)

#### Step 3: Configure PC2
1. Click on PC2 → **Desktop** tab → **IP Configuration**
2. Select **Static**
3. Enter:
   - IP Address: `172.16.1.2`
   - Subnet Mask: `255.255.0.0`

#### Step 4: Verify Connectivity
On PC1 Command Prompt:
```
C:\> ping 172.16.1.2

Pinging 172.16.1.2 with 32 bytes of data:

Reply from 172.16.1.2: bytes=32 time<1ms TTL=128
Reply from 172.16.1.2: bytes=32 time<1ms TTL=128
Reply from 172.16.1.2: bytes=32 time<1ms TTL=128
Reply from 172.16.1.2: bytes=32 time<1ms TTL=128

Ping statistics for 172.16.1.2:
    Packets: Sent = 4, Received = 4, Lost = 0 (0% loss)
```

On PC2 Command Prompt:
```
C:\> ping 172.16.1.1

Reply from 172.16.1.1: bytes=32 time<1ms TTL=128
...
```

### 172.16.0.0/16 Network Analysis
```
Network: 172.16.0.0
Mask: 255.255.0.0 (/16)
Network bits: 16
Host bits: 16

Total addresses: 2^16 = 65,536
Usable hosts: 65,534

Network Address: 172.16.0.0
First Usable: 172.16.0.1
Last Usable: 172.16.255.254
Broadcast: 172.16.255.255

PC1 (172.16.1.1) and PC2 (172.16.1.2) are in same subnet ✓
```

---

> **Solution Code:** See `Slip_17_Q2_OptionA.c` and `Slip_17_Q2_OptionB.c` in this folder.
