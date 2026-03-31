# Slip 07 — Computer Networks Solution Guide

## Q1: Theory Questions (Any 5 × 2 = 10 Marks)

---

### Q1.a) Difference Between Ping and Traceroute

| Aspect | **Ping** | **Traceroute** |
|--------|----------|----------------|
| **Purpose** | Test if a host is reachable | Show the path (route) packets take |
| **Protocol** | ICMP Echo Request/Reply | ICMP + TTL manipulation |
| **Output** | Round-trip time (RTT), packet loss | List of routers (hops) along the path |
| **Information** | Connectivity status only | Full network path with latency per hop |
| **Usage** | `ping google.com` | `traceroute google.com` (Linux) or `tracert` (Windows) |

**Ping Working:**
1. Sends ICMP Echo Request to destination
2. Destination responds with ICMP Echo Reply
3. Measures round-trip time (RTT)
4. Reports packet loss percentage

**Traceroute Working:**
1. Sends packets with TTL=1, then TTL=2, TTL=3, etc.
2. Each router decrements TTL; when TTL=0, router sends "Time Exceeded" message
3. Source identifies each router in the path
4. Shows complete route from source to destination

**Example:**
```
PING:
$ ping 8.8.8.8
64 bytes from 8.8.8.8: time=15.3 ms

TRACEROUTE:
$ traceroute 8.8.8.8
1  192.168.1.1     1.2 ms
2  10.0.0.1        5.4 ms
3  8.8.8.8        15.3 ms
```

---

### Q1.b) Steps to Identify a Phishing Email

**Step-by-Step Identification Process:**

| Step | Check | Red Flag Indicator |
|------|-------|-------------------|
| 1 | **Sender Address** | Misspelled domain (amaz0n.com, g00gle.com) |
| 2 | **Greeting** | Generic "Dear Customer" instead of your name |
| 3 | **Urgency** | "Act immediately" or "Account suspended" |
| 4 | **Links** | Hover to see actual URL different from displayed |
| 5 | **Attachments** | Unexpected .exe, .zip, or macro-enabled files |
| 6 | **Grammar** | Poor spelling, awkward phrasing |
| 7 | **Request Type** | Asking for passwords, SSN, credit card |
| 8 | **Logo/Branding** | Low quality or slightly different logos |

**Detailed Steps:**

1. **Check Sender's Email Address:**
   - Real: support@amazon.com
   - Fake: support@amazon-secure.com or support@amaz0n.com

2. **Examine the Greeting:**
   - Legitimate emails use your name
   - Phishing uses "Dear User" or "Dear Customer"

3. **Look for Urgency/Threats:**
   - "Your account will be closed in 24 hours"
   - "Unusual activity detected"

4. **Hover Over Links (Don't Click!):**
   - Displayed: www.paypal.com/verify
   - Actual: www.paypa1-secure.malicious.com

5. **Check for Grammatical Errors:**
   - Professional companies proofread emails

6. **Verify Unexpected Attachments:**
   - Banks never send executable files

7. **Contact Company Directly:**
   - Use official website, not email links

---

### Q1.c) Function of a Switch in a Computer Network

**Definition:**
A switch is a Layer 2 (Data Link Layer) network device that connects multiple devices within a LAN and forwards data based on MAC addresses.

**Key Functions:**

| Function | Description |
|----------|-------------|
| **MAC Address Learning** | Builds a MAC address table by examining source addresses |
| **Frame Forwarding** | Sends frames only to the specific destination port |
| **Loop Prevention** | Uses Spanning Tree Protocol (STP) to prevent broadcast storms |
| **Collision Domain Separation** | Each port is a separate collision domain |
| **Full Duplex** | Allows simultaneous send and receive |

**How a Switch Works:**

```
            [SWITCH]
           /   |    \
         PC1  PC2   PC3
        
MAC Table:
+---------+------+
| MAC     | Port |
+---------+------+
| AA:AA:AA| 1    |
| BB:BB:BB| 2    |
| CC:CC:CC| 3    |
+---------+------+
```

**Process:**
1. PC1 sends frame to PC2
2. Switch reads source MAC (AA:AA:AA), adds to table
3. Switch looks up destination MAC (BB:BB:BB)
4. Forwards frame ONLY to Port 2
5. PC3 never sees this traffic (unlike a hub)

**Switch vs Hub:**
| Feature | Switch | Hub |
|---------|--------|-----|
| Forwards to | Specific port | All ports |
| Collision domain | Per port | Entire network |
| Performance | High | Low |
| Intelligence | Smart (MAC table) | Dumb (signal repeater) |

---

### Q1.d) Hexadecimal Digits for 64-bit WEP Key

**Calculation:**

| WEP Type | Key Size | Hex Digits Required |
|----------|----------|---------------------|
| 64-bit WEP | 40 bits for key + 24 bits IV | **10 hex digits** |
| 128-bit WEP | 104 bits for key + 24 bits IV | 26 hex digits |

**Why 10 Hex Digits?**
- 64-bit WEP actually uses a 40-bit key (the other 24 bits are Initialization Vector)
- 1 hexadecimal digit = 4 bits
- 40 bits ÷ 4 bits/digit = **10 hexadecimal digits**

**5 Examples of 64-bit WEP Keys:**

| # | WEP Key (10 Hex Digits) | Description |
|---|-------------------------|-------------|
| 1 | `1234567890` | Sequential digits |
| 2 | `ABCDEF1234` | Mixed alphanumeric |
| 3 | `A1B2C3D4E5` | Alternating pattern |
| 4 | `DEADBEEF00` | Commonly used test key |
| 5 | `0F1E2D3C4B` | Random hex string |

**Valid Hex Characters:** 0-9 and A-F (case insensitive)

**Note:** WEP is deprecated due to security vulnerabilities. Use WPA2/WPA3 instead.

---

### Q1.f) Banner MOTD - Purpose, Legal and Security Functions

**What is Banner MOTD?**
- MOTD = Message of the Day
- Text message displayed before login prompt on network devices (routers/switches)
- Configured using `banner motd` command

**Primary Purpose:**
Display warning messages to users accessing the device, informing them of:
- Authorized access only
- Monitoring policies
- Legal consequences of unauthorized access

**Legal Function:**

| Aspect | Description |
|--------|-------------|
| **Legal Notice** | Establishes that only authorized users may access |
| **Evidence in Court** | Shows intruder was warned before unauthorized access |
| **Liability Protection** | Company can prove due diligence in security |
| **Policy Acknowledgment** | Users acknowledge terms by proceeding |

**Security Function:**

| Aspect | Description |
|--------|-------------|
| **Deterrent** | Warns potential attackers of monitoring |
| **No Information Leakage** | Should NOT reveal device type, OS, location |
| **Audit Trail** | Documents that warnings were in place |
| **Compliance** | Meets regulatory requirements (HIPAA, PCI-DSS) |

**Configuration Example:**
```
Router(config)# banner motd #
*********************************************
* WARNING: AUTHORIZED ACCESS ONLY!          *
* All activities are monitored and logged.  *
* Unauthorized access will be prosecuted.   *
*********************************************
#
```

**Best Practices:**
1. ❌ Don't include: hostname, IP addresses, OS version
2. ✅ Do include: warning, legal notice, monitoring statement
3. Use delimiter characters (#, $, %) that aren't in the message

---

### Q1.g) Dummy Phishing Email with Indicators

**Example Phishing Email:**

```
From: security-alert@amaz0n-verify.com        ← [1] Fake domain
To: customer@email.com
Subject: ⚠️ URGENT: Your Account Will Be Suspended!  ← [2] Urgency

Dear Valued Customer,                          ← [3] Generic greeting

We have detected unusual activity in your Amazon account. Your 
account will be permanantly suspended within 24 hours unless you 
verify your informations immediately.           ← [4] Grammar errors

Please click the link below to verify your account:

[Verify Now] → https://amaz0n-secure.malicious.com/verify
                                               ← [5] Fake URL

You will need to provide:
- Full Name
- Credit Card Number                           ← [6] Requesting 
- Social Security Number                           sensitive info
- Account Password

If you do not verify within 24 hours, your account will be 
closed and all purchases refunded.             ← [7] Threat

Thank you for your cooperation.

Amazon Security Team
[Low quality Amazon logo]                      ← [8] Poor branding
```

**Phishing Indicators Explained:**

| # | Indicator | What's Wrong |
|---|-----------|--------------|
| 1 | **Spoofed Domain** | amaz0n-verify.com (not amazon.com) |
| 2 | **Urgency/Pressure** | "URGENT", "24 hours", creates panic |
| 3 | **Generic Greeting** | "Valued Customer" not your name |
| 4 | **Grammar Errors** | "permanantly", "informations" |
| 5 | **Suspicious Link** | URL doesn't match amazon.com |
| 6 | **Data Harvesting** | Asking for SSN, passwords, credit card |
| 7 | **Threats** | Account closure, creates fear |
| 8 | **Poor Branding** | Blurry logo, inconsistent formatting |

**How to Respond:**
1. ❌ Don't click any links
2. ❌ Don't reply to the email
3. ✅ Report to IT/Security team
4. ✅ Mark as spam/phishing
5. ✅ Go directly to amazon.com (type in browser)
6. ✅ Check account status directly

---

## Q2: Practical Options (20 Marks)

---

## Q2 Option A: Program to Display Mesh Topology

### Concept
**Mesh Topology:** Every node connects directly to every other node.
- **Full Mesh:** All devices connected to all others
- **Formula:** Number of links = n(n-1)/2 (where n = number of nodes)

### Topology Diagram
```
For 4 nodes (A, B, C, D):

    A -------- B
    |\        /|
    | \      / |
    |  \    /  |
    |   \  /   |
    |    \/    |
    |    /\    |
    |   /  \   |
    |  /    \  |
    | /      \ |
    |/        \|
    D -------- C

Links: A-B, A-C, A-D, B-C, B-D, C-D = 6 links
Formula: 4(4-1)/2 = 6 ✓
```

### Algorithm
1. Input number of nodes
2. Create nodes with names (A, B, C, ...)
3. For each pair of nodes (i, j) where i < j:
   - Create a connection
4. Display adjacency matrix
5. Display connection list
6. Calculate total connections

### Pseudocode
```
FUNCTION displayMeshTopology(n):
    // Create adjacency matrix
    FOR i = 0 to n-1:
        FOR j = 0 to n-1:
            IF i != j THEN
                matrix[i][j] = 1
            ELSE
                matrix[i][j] = 0
    
    // Display connections
    FOR i = 0 to n-2:
        FOR j = i+1 to n-1:
            PRINT "Node " + i + " <---> Node " + j
    
    // Total connections
    total = n * (n-1) / 2
    PRINT "Total connections: " + total
```

### See: `Slip_07_Q2_OptionA.c`

---

## Q2 Option B: Router Configuration Simulation

### Concept
Simulate Cisco router CLI commands for:
1. **Hostname** - Device name identification
2. **Enable Password** - Unencrypted privileged access password
3. **Secret Password** - Encrypted privileged access password (MD5)

### Cisco IOS Commands
```
Router> enable
Router# configure terminal
Router(config)# hostname MyRouter
MyRouter(config)# enable password cisco123
MyRouter(config)# enable secret class456
MyRouter(config)# exit
MyRouter# show running-config
```

### Password Types
| Type | Command | Storage | Security |
|------|---------|---------|----------|
| Enable Password | `enable password <pwd>` | Plaintext | Weak |
| Secret Password | `enable secret <pwd>` | MD5 Hash | Strong |

**Note:** Secret password overrides enable password when both are set.

### Algorithm
1. Display initial router prompt
2. Simulate entering privileged EXEC mode
3. Enter global configuration mode
4. Accept hostname from user
5. Accept enable password (store as plaintext)
6. Accept secret password (hash with MD5)
7. Display running configuration
8. Show difference between stored passwords

### Pseudocode
```
FUNCTION configureRouter():
    hostname = "Router"
    enable_password = ""
    secret_password = ""
    
    PRINT hostname + "> enable"
    PRINT hostname + "# configure terminal"
    
    INPUT "Enter hostname: " -> new_hostname
    hostname = new_hostname
    
    INPUT "Enter enable password: " -> enable_password
    INPUT "Enter secret password: " -> secret_input
    secret_password = MD5_HASH(secret_input)
    
    PRINT "Running Configuration:"
    PRINT "hostname " + hostname
    PRINT "enable password " + enable_password
    PRINT "enable secret 5 " + secret_password
```

### See: `Slip_07_Q2_OptionB.c`

---

## Q2 Option C: Packet Tracer - Mesh Topology

### Network Diagram
```
                  PC0 (192.168.1.1)
                    /     |     \
                   /      |      \
                  /       |       \
                 /        |        \
   PC1 --------+-------- HUB -------+-------- PC2
(192.168.1.2)   \         |        / (192.168.1.3)
                 \        |       /
                  \       |      /
                   \      |     /
                    \     |    /
                  PC3 (192.168.1.4)
```

### Configuration Table
| Device | IP Address | Subnet Mask | Gateway |
|--------|------------|-------------|---------|
| PC0 | 192.168.1.1 | 255.255.255.0 | - |
| PC1 | 192.168.1.2 | 255.255.255.0 | - |
| PC2 | 192.168.1.3 | 255.255.255.0 | - |
| PC3 | 192.168.1.4 | 255.255.255.0 | - |

### Step-by-Step Configuration

**Step 1: Add Devices**
1. Open Cisco Packet Tracer
2. Drag 4 PCs from End Devices
3. Add switches/direct connections for mesh

**Step 2: Connect Devices (Mesh requires 6 connections)**
```
Connections needed for full mesh:
PC0 -- PC1 (Cross-over cable)
PC0 -- PC2 (Cross-over cable)
PC0 -- PC3 (Cross-over cable)
PC1 -- PC2 (Cross-over cable)
PC1 -- PC3 (Cross-over cable)
PC2 -- PC3 (Cross-over cable)
```

**Step 3: Configure IP Addresses**
For each PC:
1. Click on PC
2. Go to Desktop → IP Configuration
3. Enter:
   - IP Address: 192.168.1.X
   - Subnet Mask: 255.255.255.0

**Step 4: Verify Connectivity**
```
PC0> ping 192.168.1.2  ✓
PC0> ping 192.168.1.3  ✓
PC0> ping 192.168.1.4  ✓
PC1> ping 192.168.1.3  ✓
PC1> ping 192.168.1.4  ✓
PC2> ping 192.168.1.4  ✓
```

### Alternative: Using a Switch (Logical Mesh)
```
         [Switch]
        /  |  |  \
      PC0 PC1 PC2 PC3
```
All PCs connect to central switch - each can reach all others.

---

## Quick Reference

### Network Commands
| Command | Purpose | Example |
|---------|---------|---------|
| `ping` | Test connectivity | `ping 192.168.1.1` |
| `traceroute` | Show path | `traceroute google.com` |
| `ipconfig` | Show IP (Windows) | `ipconfig /all` |
| `ifconfig` | Show IP (Linux) | `ifconfig eth0` |

### Cisco IOS Modes
| Mode | Prompt | Access |
|------|--------|--------|
| User EXEC | `Router>` | Default |
| Privileged EXEC | `Router#` | `enable` |
| Global Config | `Router(config)#` | `configure terminal` |

### Mesh Topology Formulas
- **Full Mesh Links:** n(n-1)/2
- **Ports per device:** n-1

---

## Files in This Directory
| File | Description |
|------|-------------|
| `Slip_07_CN_SOLUTION.md` | This solution guide |
| `Slip_07_Q2_OptionA.c` | Mesh Topology display program |
| `Slip_07_Q2_OptionB.c` | Router configuration simulation |
