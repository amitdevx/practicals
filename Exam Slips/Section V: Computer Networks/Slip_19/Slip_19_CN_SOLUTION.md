# Slip 19 — Computer Networks Solution Guide

## Q1: Theory Questions (10 Marks - Answer ANY 5)

---

### a) What is static routing? Give its features.

#### Concept
**Static Routing** is a manual routing method where network administrators manually configure routing table entries to define paths for network traffic. Unlike dynamic routing, routes don't change automatically when network topology changes.

#### How Static Routing Works
```
              [Router A]
             /          \
     Network A          Network B
   192.168.1.0        192.168.2.0

Admin manually configures:
"To reach 192.168.2.0, use interface Gi0/1"
```

#### Features of Static Routing

| Feature | Description |
|---------|-------------|
| **Manual Configuration** | Routes are added, modified, or removed by admin |
| **Predictable Path** | Traffic always takes the configured path |
| **No Overhead** | No routing protocol traffic consumes bandwidth |
| **Low CPU Usage** | No route calculation required |
| **Simple Security** | No routing updates that can be exploited |
| **Scalability Issues** | Doesn't scale well for large networks |

#### Advantages
1. **No Bandwidth Overhead**: No routing protocol messages exchanged
2. **Security**: Routes can't be advertised or manipulated by attackers
3. **Resource Efficient**: Minimal CPU and memory usage
4. **Predictable**: Traffic always follows configured paths
5. **Simple for Small Networks**: Easy to implement in small environments

#### Disadvantages
1. **Manual Updates Required**: Every change needs admin intervention
2. **No Fault Tolerance**: Doesn't adapt to link failures automatically
3. **Administrative Burden**: Time-consuming for large networks
4. **Error Prone**: Misconfigurations can cause routing loops

#### Configuration Example (Cisco)
```
Router(config)# ip route <destination_network> <subnet_mask> <next_hop_ip>
Router(config)# ip route 192.168.2.0 255.255.255.0 10.0.0.2

# Or using exit interface
Router(config)# ip route 192.168.2.0 255.255.255.0 GigabitEthernet0/1
```

#### When to Use Static Routing
- Small networks with few routers
- Stub networks (single entry/exit point)
- Default routes to ISP
- Backup routes with higher administrative distance
- Security-sensitive environments

---

### b) List the commands used for Network Address Translation on Cisco's Packet Tracer

#### NAT Basics
**NAT (Network Address Translation)** translates private IP addresses to public IP addresses, allowing multiple devices to share a single public IP for internet access.

#### Types of NAT

| Type | Description | Use Case |
|------|-------------|----------|
| **Static NAT** | One-to-one mapping | Servers needing external access |
| **Dynamic NAT** | Pool of public IPs | Multiple hosts, limited public IPs |
| **PAT/NAT Overload** | Many-to-one using ports | Most common, home/office networks |

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

##### 2. Static NAT Configuration
```
Router(config)# ip nat inside source static <inside_local> <inside_global>
Router(config)# ip nat inside source static 192.168.1.10 203.0.113.10
```

##### 3. Dynamic NAT Configuration
```
! Define NAT pool
Router(config)# ip nat pool MYPOOL 203.0.113.1 203.0.113.10 netmask 255.255.255.0

! Define access list for internal network
Router(config)# access-list 1 permit 192.168.1.0 0.0.0.255

! Associate ACL with NAT pool
Router(config)# ip nat inside source list 1 pool MYPOOL
```

##### 4. PAT (NAT Overload) Configuration
```
! Using interface IP (most common)
Router(config)# access-list 1 permit 192.168.1.0 0.0.0.255
Router(config)# ip nat inside source list 1 interface GigabitEthernet0/1 overload

! Or using pool with overload
Router(config)# ip nat inside source list 1 pool MYPOOL overload
```

##### 5. Verification Commands
```
Router# show ip nat translations
Router# show ip nat statistics
Router# show running-config | include nat
Router# debug ip nat
Router# clear ip nat translation *
```

#### Sample NAT Translation Table Output
```
Router# show ip nat translations
Pro  Inside global     Inside local      Outside local     Outside global
tcp  203.0.113.1:1024  192.168.1.10:80   8.8.8.8:443      8.8.8.8:443
tcp  203.0.113.1:1025  192.168.1.11:443  1.1.1.1:80       1.1.1.1:80
---  203.0.113.10      192.168.1.100     ---              ---
```

---

### c) Write an algorithm to Hash a password using SHA256

#### Concept
**SHA-256** (Secure Hash Algorithm 256-bit) is a cryptographic hash function that produces a fixed 256-bit (32-byte) hash value. It's part of the SHA-2 family and is widely used for password hashing, digital signatures, and data integrity verification.

#### Properties of SHA-256
1. **Deterministic**: Same input always produces same hash
2. **Fixed Length**: Always 256 bits (64 hex characters)
3. **One-way**: Cannot reverse hash to get original input
4. **Collision Resistant**: Extremely hard to find two different inputs with same hash
5. **Avalanche Effect**: Small input change completely changes hash

#### Algorithm to Hash Password using SHA256

```
ALGORITHM HashPasswordSHA256(password)

INPUT: password (string)
OUTPUT: hash (256-bit hexadecimal string)

BEGIN
    // Step 1: Pre-processing - Add padding
    message = ConvertToBytes(password)
    original_length = BitLength(message)
    
    // Step 2: Append single '1' bit
    message = message + 0x80
    
    // Step 3: Pad with zeros until length ≡ 448 (mod 512)
    WHILE (BitLength(message) mod 512) ≠ 448:
        message = message + 0x00
    
    // Step 4: Append original length as 64-bit big-endian
    message = message + Int64ToBigEndian(original_length)
    
    // Step 5: Initialize hash values (first 32 bits of fractional parts 
    //         of square roots of first 8 primes)
    H0 = 0x6a09e667
    H1 = 0xbb67ae85
    H2 = 0x3c6ef372
    H3 = 0xa54ff53a
    H4 = 0x510e527f
    H5 = 0x9b05688c
    H6 = 0x1f83d9ab
    H7 = 0x5be0cd19
    
    // Step 6: Initialize round constants K[0..63]
    K = [0x428a2f98, 0x71374491, ... ] // 64 constants
    
    // Step 7: Process message in 512-bit chunks
    FOR each 512-bit chunk in message:
        // Step 7a: Create message schedule W[0..63]
        W[0..15] = chunk divided into 16 32-bit words
        FOR i = 16 TO 63:
            s0 = ROTR(W[i-15], 7) XOR ROTR(W[i-15], 18) XOR SHR(W[i-15], 3)
            s1 = ROTR(W[i-2], 17) XOR ROTR(W[i-2], 19) XOR SHR(W[i-2], 10)
            W[i] = W[i-16] + s0 + W[i-7] + s1
        
        // Step 7b: Initialize working variables
        a, b, c, d, e, f, g, h = H0, H1, H2, H3, H4, H5, H6, H7
        
        // Step 7c: Compression function main loop
        FOR i = 0 TO 63:
            S1 = ROTR(e, 6) XOR ROTR(e, 11) XOR ROTR(e, 25)
            ch = (e AND f) XOR ((NOT e) AND g)
            temp1 = h + S1 + ch + K[i] + W[i]
            S0 = ROTR(a, 2) XOR ROTR(a, 13) XOR ROTR(a, 22)
            maj = (a AND b) XOR (a AND c) XOR (b AND c)
            temp2 = S0 + maj
            
            h = g
            g = f
            f = e
            e = d + temp1
            d = c
            c = b
            b = a
            a = temp1 + temp2
        
        // Step 7d: Add compressed chunk to current hash value
        H0 = H0 + a
        H1 = H1 + b
        H2 = H2 + c
        H3 = H3 + d
        H4 = H4 + e
        H5 = H5 + f
        H6 = H6 + g
        H7 = H7 + h
    
    // Step 8: Produce final hash value (concatenate)
    hash = H0 || H1 || H2 || H3 || H4 || H5 || H6 || H7
    
    RETURN ConvertToHex(hash)
END
```

#### Simplified Pseudocode for Implementation
```
FUNCTION HashPassword(password):
    // Using a library function (practical approach)
    salt = GenerateRandomSalt(16 bytes)
    salted_password = salt + password
    hash = SHA256(salted_password)
    RETURN salt + ":" + hash
END

FUNCTION VerifyPassword(password, stored_hash):
    parts = Split(stored_hash, ":")
    salt = parts[0]
    expected_hash = parts[1]
    computed_hash = SHA256(salt + password)
    RETURN (computed_hash == expected_hash)
END
```

#### Example
```
Input:  "MyPassword123"
Output: "ef92b778bafe771e89245b89ecbc08a44a4e166c06659911881f383d4473e94f"
```

#### Best Practices for Password Hashing
1. **Always use salt**: Prevents rainbow table attacks
2. **Use key stretching**: bcrypt, scrypt, Argon2 preferred over plain SHA256
3. **Never store plain text**: Always hash passwords
4. **Use unique salt per password**: Prevents identical hash for same passwords

---

### d) Write the Linux commands used to detect hidden Wi-Fi networks

#### Concept
**Hidden Wi-Fi networks** (also called non-broadcast or cloaked networks) don't broadcast their SSID in beacon frames. However, they can still be detected through various methods.

#### Commands to Detect Hidden Wi-Fi Networks

##### 1. Using `iwlist` (Wireless Tools)
```bash
# Scan for all networks including hidden
sudo iwlist wlan0 scan

# Filter for hidden networks (shown as ESSID:"")
sudo iwlist wlan0 scan | grep -B5 'ESSID:""'

# Show all detected networks
sudo iwlist wlan0 scan | grep -E "ESSID|Signal|Address"
```

##### 2. Using `iw` (Modern Tool)
```bash
# Scan for networks
sudo iw dev wlan0 scan

# Show SSIDs (hidden shown as empty or "\x00")
sudo iw dev wlan0 scan | grep -E "SSID:|signal:|BSS"

# Detailed scan with hidden networks
sudo iw dev wlan0 scan ap-force
```

##### 3. Using `nmcli` (NetworkManager)
```bash
# List all detected networks
nmcli device wifi list

# Rescan and list
nmcli device wifi rescan && nmcli device wifi list

# Show hidden networks (marked with *)
nmcli -f SSID,BSSID,SIGNAL,SECURITY device wifi list
```

##### 4. Using `airmon-ng` and `airodump-ng` (Aircrack-ng Suite)
```bash
# Put interface in monitor mode
sudo airmon-ng start wlan0

# Scan for all networks (hidden shown as <length: X>)
sudo airodump-ng wlan0mon

# Capture probe requests to reveal hidden SSIDs
sudo airodump-ng -c <channel> --bssid <MAC> wlan0mon
```

##### 5. Using `wavemon`
```bash
# Install wavemon
sudo apt install wavemon

# Run wireless monitor
sudo wavemon
# Press F3 for scan view
```

##### 6. Using `kismet` (Advanced)
```bash
# Install kismet
sudo apt install kismet

# Run kismet
sudo kismet -c wlan0

# View detected networks in web interface
# Open browser: http://localhost:2501
```

#### Detection Techniques

| Method | How Hidden Networks Appear |
|--------|---------------------------|
| `iwlist` | ESSID:"" (empty string) |
| `iw` | SSID: \x00\x00\x00 or blank |
| `airodump-ng` | <length: X> (X = SSID length) |
| `nmcli` | Listed with blank name or asterisk |

#### Revealing Hidden SSID
```bash
# Method 1: Wait for client probe request
sudo airodump-ng wlan0mon
# When client connects, SSID is revealed

# Method 2: Deauth attack (forces reconnection)
sudo aireplay-ng -0 5 -a <BSSID> wlan0mon
# WARNING: Only use on networks you own/have permission
```

#### Note
Hidden networks provide **security through obscurity** which is not real security. The SSID is transmitted in:
- Probe requests from clients
- Probe responses from AP
- Association requests

---

### f) Explain steps to identify a phishing email

#### Concept
**Phishing** is a social engineering attack where attackers send fraudulent emails pretending to be from legitimate sources to steal sensitive information like passwords, credit card numbers, or personal data.

#### Steps to Identify a Phishing Email

##### Step 1: Check the Sender's Email Address
```
Legitimate: support@amazon.com
Phishing:   support@amaz0n-security.com
            amazon.support@gmail.com
            support@amazon.com.malicious.net
```
**Red Flags:**
- Misspelled domain names
- Extra characters or numbers
- Free email services (gmail, yahoo) for official communication
- Subdomains designed to deceive

##### Step 2: Analyze the Greeting
```
Legitimate: "Dear John Smith," or "Hello John,"
Phishing:   "Dear Customer," 
            "Dear User,"
            "Dear Account Holder,"
```
**Red Flags:**
- Generic greetings instead of your name
- Misspelled name
- No greeting at all

##### Step 3: Look for Urgency or Threats
```
Phishing examples:
- "Your account will be suspended in 24 hours!"
- "Immediate action required!"
- "Unauthorized access detected - verify now!"
- "You've won $1,000,000! Claim within 1 hour!"
```
**Red Flags:**
- Artificial urgency
- Threats of account closure
- Too-good-to-be-true offers
- Fear-inducing language

##### Step 4: Inspect Links Before Clicking
```
Display Text: www.paypal.com/login
Actual URL:   http://paypal-secure.malicious-site.com/login

How to check:
- Hover over link (don't click) to see actual URL
- Look for HTTPS (though phishing sites may have it too)
- Check for misspellings in domain
```
**Red Flags:**
- URL doesn't match display text
- HTTP instead of HTTPS
- IP addresses instead of domain names
- Shortened URLs (bit.ly, tinyurl)

##### Step 5: Check for Spelling and Grammar Errors
```
Phishing: "Your account has been compromize. Please login 
          to you're account immediately to verify."

Legitimate companies have professional copywriters and proofreaders.
```
**Red Flags:**
- Multiple spelling errors
- Poor grammar
- Awkward phrasing
- Mixed languages

##### Step 6: Examine Attachments
```
Dangerous attachments:
- .exe, .scr, .bat (executables)
- .zip, .rar (compressed files hiding malware)
- .doc, .xls with macros
- PDF files (can contain malicious scripts)
```
**Red Flags:**
- Unexpected attachments
- Executable file types
- Requests to enable macros
- Generic filenames like "Invoice.pdf" or "Document.zip"

##### Step 7: Verify Email Headers
```bash
# View full headers in email client
# Look for:
Received: from <actual sending server>
Return-Path: <where replies go>
X-Originating-IP: <sender's IP>
```
**Red Flags:**
- Mismatched "From" and "Return-Path"
- Suspicious originating IP
- Multiple "Received" hops through unusual servers

##### Step 8: Check for Request of Sensitive Information
```
Phishing requests:
- Password
- Credit card numbers
- Social Security Number
- Bank account details
- OTP/Verification codes
```
**Important:** Legitimate companies NEVER ask for sensitive information via email.

#### Phishing Email Checklist

| Check | Legitimate | Suspicious |
|-------|------------|------------|
| Sender address | Company domain | Free email/misspelled |
| Greeting | Personalized | Generic |
| Urgency | Reasonable | Threatening/Immediate |
| Links | Match display text | Different destination |
| Grammar | Professional | Errors |
| Attachments | Expected | Unexpected executables |
| Sensitive data | Never requested | Requested |

#### What to Do If You Suspect Phishing
1. **Don't click** any links or download attachments
2. **Don't reply** to the email
3. **Report** to your IT department or email provider
4. **Delete** the email
5. **Verify** by contacting the company directly through official channels

---

### g) List types of Cyber Threats

#### Concept
**Cyber threats** are malicious acts that seek to damage, steal data, or disrupt digital operations. They can originate from various actors including hackers, criminal organizations, nation-states, or insiders.

#### Categories of Cyber Threats

##### 1. Malware (Malicious Software)
| Type | Description |
|------|-------------|
| **Virus** | Self-replicating code that attaches to files |
| **Worm** | Self-replicating, spreads without user action |
| **Trojan Horse** | Disguised as legitimate software |
| **Ransomware** | Encrypts data, demands payment |
| **Spyware** | Secretly monitors user activity |
| **Adware** | Displays unwanted advertisements |
| **Rootkit** | Provides persistent privileged access |
| **Keylogger** | Records keystrokes |

##### 2. Social Engineering Attacks
| Type | Description |
|------|-------------|
| **Phishing** | Fraudulent emails to steal credentials |
| **Spear Phishing** | Targeted phishing at specific individuals |
| **Whaling** | Phishing targeting executives |
| **Vishing** | Voice phishing (phone calls) |
| **Smishing** | SMS/text message phishing |
| **Pretexting** | Creating false scenario to extract info |
| **Baiting** | Offering something enticing to deliver malware |
| **Tailgating** | Physical following into secure areas |

##### 3. Network Attacks
| Type | Description |
|------|-------------|
| **DDoS** | Distributed Denial of Service - overwhelm servers |
| **DoS** | Single-source denial of service |
| **Man-in-the-Middle (MitM)** | Intercepting communications |
| **Packet Sniffing** | Capturing network traffic |
| **DNS Spoofing** | Redirecting DNS queries |
| **ARP Spoofing** | Linking attacker's MAC to legitimate IP |
| **Session Hijacking** | Taking over user sessions |

##### 4. Web-Based Attacks
| Type | Description |
|------|-------------|
| **SQL Injection** | Injecting malicious SQL queries |
| **Cross-Site Scripting (XSS)** | Injecting client-side scripts |
| **Cross-Site Request Forgery (CSRF)** | Forging authorized requests |
| **Drive-by Download** | Automatic malware download from websites |
| **Watering Hole** | Compromising frequently visited sites |

##### 5. Password Attacks
| Type | Description |
|------|-------------|
| **Brute Force** | Trying all possible combinations |
| **Dictionary Attack** | Using common words/passwords |
| **Credential Stuffing** | Using leaked credentials |
| **Password Spraying** | Few passwords against many accounts |
| **Rainbow Table** | Pre-computed hash lookups |

##### 6. Advanced Persistent Threats (APT)
- Long-term targeted attacks
- Often state-sponsored
- Multiple attack vectors
- Focus on espionage/data theft
- Remain undetected for extended periods

##### 7. Insider Threats
| Type | Description |
|------|-------------|
| **Malicious Insider** | Employee intentionally causing harm |
| **Negligent Insider** | Accidental data exposure |
| **Compromised Insider** | Account taken over by attacker |

##### 8. Physical Threats
| Type | Description |
|------|-------------|
| **Device Theft** | Stealing laptops, phones |
| **Dumpster Diving** | Searching trash for information |
| **Shoulder Surfing** | Watching someone enter credentials |
| **USB Drops** | Leaving infected USB drives |

##### 9. Emerging Threats
| Type | Description |
|------|-------------|
| **Cryptojacking** | Unauthorized cryptocurrency mining |
| **AI-Powered Attacks** | Using AI to enhance attacks |
| **IoT Attacks** | Targeting Internet of Things devices |
| **Supply Chain Attacks** | Compromising software/hardware vendors |
| **Deepfakes** | AI-generated fake audio/video |

#### Threat Landscape Summary
```
┌─────────────────────────────────────────────────────┐
│                  CYBER THREATS                       │
├─────────────┬─────────────┬─────────────┬───────────┤
│   Malware   │   Social    │   Network   │    Web    │
│             │ Engineering │             │           │
├─────────────┼─────────────┼─────────────┼───────────┤
│ - Virus     │ - Phishing  │ - DDoS      │ - SQLi    │
│ - Worm      │ - Spear     │ - MitM      │ - XSS     │
│ - Trojan    │ - Vishing   │ - Sniffing  │ - CSRF    │
│ - Ransom    │ - Smishing  │ - Spoofing  │ - Drive-by│
└─────────────┴─────────────┴─────────────┴───────────┘
```

---

## Q2: Practical Questions (20 Marks)

---

## Option A: Phishing Simulation Program

### Concept
A phishing simulation demonstrates how phishing attacks work by creating fake login pages and capturing credentials. This is used for **security awareness training** to help users recognize phishing attempts.

**⚠️ WARNING: Use only for educational purposes and authorized security testing!**

### How Phishing Works
```
1. Attacker creates fake login page (looks like legitimate site)
2. Victim receives email with link to fake page
3. Victim enters credentials on fake page
4. Credentials are captured and stored by attacker
5. Victim is redirected to real site (unaware of attack)
```

### Algorithm
```
ALGORITHM PhishingSimulation

1. CREATE fake login page mimicking target site
2. SET UP local web server
3. DISPLAY login form to user
4. WHEN user submits form:
   a. CAPTURE username and password
   b. LOG credentials with timestamp and IP
   c. DISPLAY warning message (for simulation)
   d. OPTIONALLY redirect to real site
5. GENERATE report of captured attempts
```

### Program Features
- Creates simple HTTP server
- Displays fake login page
- Captures submitted credentials
- Logs attempts with metadata
- Educational warning messages

> **See:** `Slip_19_Q2_OptionA.c` for complete implementation

---

## Option B: NAT Translation Verification Program

### Concept
This program simulates NAT (Network Address Translation) functionality and demonstrates how to verify NAT translations similar to Cisco's `show ip nat translations` command.

### NAT Translation Table Structure
```
┌─────────────────────────────────────────────────────────────────┐
│ Pro │ Inside Global │ Inside Local │ Outside Local │ Outside Global │
├─────┼───────────────┼──────────────┼───────────────┼────────────────┤
│ TCP │ 203.0.113.1   │ 192.168.1.10 │ 8.8.8.8       │ 8.8.8.8        │
│ UDP │ 203.0.113.1   │ 192.168.1.11 │ 1.1.1.1       │ 1.1.1.1        │
└─────┴───────────────┴──────────────┴───────────────┴────────────────┘
```

### Algorithm
```
ALGORITHM NATTranslationVerification

1. INITIALIZE NAT translation table (array/linked list)
2. DEFINE NAT entry structure:
   - Protocol (TCP/UDP/ICMP)
   - Inside Local IP:Port
   - Inside Global IP:Port
   - Outside Local IP:Port
   - Outside Global IP:Port
   - Timeout/TTL

3. FUNCTION AddTranslation(inside_local, inside_global, outside):
   a. CREATE new NAT entry
   b. ASSIGN translated addresses
   c. SET timestamp
   d. ADD to translation table

4. FUNCTION ShowNATTranslations():
   a. PRINT header
   b. FOR each entry in table:
      - PRINT formatted entry
   c. PRINT statistics summary

5. FUNCTION VerifyTranslation(ip_address):
   a. SEARCH table for matching entry
   b. IF found:
      - PRINT translation details
      - RETURN success
   c. ELSE:
      - PRINT "No translation found"
      - RETURN failure
```

### Program Features
- Simulates NAT translation table
- Add/Remove NAT entries
- Display all translations
- Verify specific translations
- Show NAT statistics

> **See:** `Slip_19_Q2_OptionB.c` for complete implementation

---

## Option C: Packet Tracer Configuration (2 PCs, 1 Router)

### Network Topology
```
    ┌─────────┐                              ┌─────────┐
    │   PC1   │                              │   PC2   │
    │192.168.1.2                           192.168.2.2│
    └────┬────┘                              └────┬────┘
         │                                        │
         │ Fa0                              Fa0   │
         │                                        │
    ─────┴────────────┬────────────────────┬──────┴─────
                      │                    │
                   G0/0│      Router      │G0/1
                192.168.1.1            192.168.2.1
                      └────────────────────┘
```

### IP Addressing Table
| Device | Interface | IP Address | Subnet Mask | Default Gateway |
|--------|-----------|------------|-------------|-----------------|
| PC1 | Fa0 | 192.168.1.2 | 255.255.255.0 | 192.168.1.1 |
| PC2 | Fa0 | 192.168.2.2 | 255.255.255.0 | 192.168.2.1 |
| Router | G0/0 | 192.168.1.1 | 255.255.255.0 | - |
| Router | G0/1 | 192.168.2.1 | 255.255.255.0 | - |

### Step-by-Step Configuration

#### Step 1: Set Up Topology in Packet Tracer
1. Open Cisco Packet Tracer
2. Add devices:
   - 1 Router (2911 or similar with Gigabit interfaces)
   - 2 PCs
3. Connect:
   - PC1 → Router G0/0 (copper straight-through)
   - PC2 → Router G0/1 (copper straight-through)

#### Step 2: Configure Router
```
Router> enable
Router# configure terminal

! Configure hostname
Router(config)# hostname R1

! Configure G0/0 interface (connecting to PC1)
R1(config)# interface GigabitEthernet0/0
R1(config-if)# ip address 192.168.1.1 255.255.255.0
R1(config-if)# no shutdown
R1(config-if)# exit

! Configure G0/1 interface (connecting to PC2)
R1(config)# interface GigabitEthernet0/1
R1(config-if)# ip address 192.168.2.1 255.255.255.0
R1(config-if)# no shutdown
R1(config-if)# exit

! Save configuration
R1(config)# exit
R1# copy running-config startup-config
```

#### Step 3: Configure PC1
1. Click on PC1 → Desktop tab → IP Configuration
2. Configure:
   - IP Address: `192.168.1.2`
   - Subnet Mask: `255.255.255.0`
   - Default Gateway: `192.168.1.1`

#### Step 4: Configure PC2
1. Click on PC2 → Desktop tab → IP Configuration
2. Configure:
   - IP Address: `192.168.2.2`
   - Subnet Mask: `255.255.255.0`
   - Default Gateway: `192.168.2.1`

#### Step 5: Verify Configuration

##### On Router:
```
R1# show ip interface brief
Interface              IP-Address      OK? Method Status Protocol
GigabitEthernet0/0     192.168.1.1     YES manual up     up
GigabitEthernet0/1     192.168.2.1     YES manual up     up

R1# show ip route
C    192.168.1.0/24 is directly connected, GigabitEthernet0/0
C    192.168.2.0/24 is directly connected, GigabitEthernet0/1
```

##### On PC1 (Command Prompt):
```
C:\> ipconfig

C:\> ping 192.168.1.1      (Test gateway)
Reply from 192.168.1.1: bytes=32 time<1ms TTL=255

C:\> ping 192.168.2.1      (Test router's other interface)
Reply from 192.168.2.1: bytes=32 time<1ms TTL=255

C:\> ping 192.168.2.2      (Test PC2)
Reply from 192.168.2.2: bytes=32 time<1ms TTL=127
```

##### On PC2 (Command Prompt):
```
C:\> ping 192.168.2.1      (Test gateway)
Reply from 192.168.2.1: bytes=32 time<1ms TTL=255

C:\> ping 192.168.1.1      (Test router's other interface)
Reply from 192.168.1.1: bytes=32 time<1ms TTL=255

C:\> ping 192.168.1.2      (Test PC1)
Reply from 192.168.1.2: bytes=32 time<1ms TTL=127
```

### Troubleshooting Commands
```
! Check interface status
R1# show interfaces status

! Check IP configuration
R1# show running-config | section interface

! Check connectivity
R1# ping 192.168.1.2
R1# ping 192.168.2.2

! Debug routing
R1# show ip route
R1# show arp
```

### Common Issues and Solutions
| Issue | Solution |
|-------|----------|
| Interface down | Use `no shutdown` command |
| Wrong IP on PC | Verify IP Configuration |
| Can't ping across networks | Check default gateway on PCs |
| Link light off | Check cable connections |

---

> **Solution Code:** See `Slip_19_Q2_OptionA.c` and `Slip_19_Q2_OptionB.c` in this folder.
