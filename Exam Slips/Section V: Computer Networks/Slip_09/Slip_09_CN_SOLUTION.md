# Slip 9 — Computer Networks Solution Guide

## Q1: Theory Questions (10 marks - Answer Any 5)

---

### Q1.a) List and Explain All Five IP Address Classes with Examples

#### Concept
IP addresses are divided into **5 classes** (A, B, C, D, E) based on the first octet value and network/host bit allocation.

#### IP Address Classes Table

| Class | First Octet Range | Network Bits | Host Bits | Default Subnet Mask | Networks | Hosts/Network |
|-------|-------------------|--------------|-----------|---------------------|----------|---------------|
| **A** | 1-126 | 8 | 24 | 255.0.0.0 | 126 | 16,777,214 |
| **B** | 128-191 | 16 | 16 | 255.255.0.0 | 16,384 | 65,534 |
| **C** | 192-223 | 24 | 8 | 255.255.255.0 | 2,097,152 | 254 |
| **D** | 224-239 | N/A | N/A | N/A | Multicast | Multicast |
| **E** | 240-255 | N/A | N/A | N/A | Reserved | Research |

#### Binary First Octet Patterns
```
Class A: 0xxxxxxx  (starts with 0)
Class B: 10xxxxxx  (starts with 10)
Class C: 110xxxxx  (starts with 110)
Class D: 1110xxxx  (starts with 1110)
Class E: 1111xxxx  (starts with 1111)
```

#### Detailed Explanation

**Class A:**
- **Range:** 1.0.0.0 to 126.255.255.255
- **Purpose:** Very large networks (governments, large corporations)
- **Format:** N.H.H.H (1 byte network, 3 bytes host)
- **Example:** 10.0.0.1 (Private), 8.8.8.8 (Google DNS)
- **Note:** 127.x.x.x reserved for loopback (127.0.0.1)

**Class B:**
- **Range:** 128.0.0.0 to 191.255.255.255
- **Purpose:** Medium to large organizations (universities, companies)
- **Format:** N.N.H.H (2 bytes network, 2 bytes host)
- **Example:** 172.16.0.1 (Private), 150.100.25.30

**Class C:**
- **Range:** 192.0.0.0 to 223.255.255.255
- **Purpose:** Small networks (small businesses, homes)
- **Format:** N.N.N.H (3 bytes network, 1 byte host)
- **Example:** 192.168.1.1 (Private), 200.100.50.25

**Class D:**
- **Range:** 224.0.0.0 to 239.255.255.255
- **Purpose:** Multicasting (one-to-many communication)
- **Example:** 224.0.0.1 (All hosts), 224.0.0.5 (OSPF routers)

**Class E:**
- **Range:** 240.0.0.0 to 255.255.255.255
- **Purpose:** Reserved for experimental/research use
- **Example:** 255.255.255.255 (Broadcast)

#### Private IP Address Ranges
| Class | Private Range |
|-------|---------------|
| A | 10.0.0.0 – 10.255.255.255 |
| B | 172.16.0.0 – 172.31.255.255 |
| C | 192.168.0.0 – 192.168.255.255 |

---

### Q1.b) Explain the Format and Example of an IPv6 Address

#### Concept
IPv6 is the next-generation Internet Protocol with **128-bit addresses** designed to overcome IPv4 address exhaustion.

#### IPv6 Address Format

```
Full Format: xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx
             |____|  Each group is a 16-bit hextet (4 hex digits)
             
Total: 8 groups × 16 bits = 128 bits
```

#### Key Features

| Feature | IPv4 | IPv6 |
|---------|------|------|
| Address Length | 32 bits | 128 bits |
| Notation | Decimal (dotted) | Hexadecimal (colon) |
| Total Addresses | ~4.3 billion | 3.4 × 10^38 |
| Example | 192.168.1.1 | 2001:0db8:85a3::8a2e:0370:7334 |

#### IPv6 Address Components
```
2001:0db8:85a3:0000:0000:8a2e:0370:7334
|__________|__________________|________|
  Prefix    Subnet ID          Interface ID
(Network)  (Organization)     (Host/Device)
```

#### Simplification Rules

**Rule 1: Remove Leading Zeros**
```
2001:0db8:0000:0042 → 2001:db8:0:42
```

**Rule 2: Replace Consecutive Zero Groups with `::`**
```
2001:0db8:0000:0000:0000:0000:0000:0001
→ 2001:db8::1
```

**Note:** `::` can only be used ONCE in an address.

#### Examples

| Type | Full Form | Shortened |
|------|-----------|-----------|
| Loopback | 0000:0000:0000:0000:0000:0000:0000:0001 | ::1 |
| Unspecified | 0000:0000:0000:0000:0000:0000:0000:0000 | :: |
| Link-Local | fe80:0000:0000:0000:0000:0000:0000:0001 | fe80::1 |
| Global | 2001:0db8:85a3:0000:0000:8a2e:0370:7334 | 2001:db8:85a3::8a2e:370:7334 |

#### IPv6 Address Types
```
┌─────────────────────────────────────────────────┐
│ Unicast: One-to-One communication               │
│   - Global: 2000::/3 (Internet routable)        │
│   - Link-Local: fe80::/10 (Local network only)  │
│   - Unique Local: fc00::/7 (Private)            │
├─────────────────────────────────────────────────┤
│ Multicast: One-to-Many communication            │
│   - ff00::/8 (All multicast addresses)          │
├─────────────────────────────────────────────────┤
│ Anycast: One-to-Nearest communication           │
│   - Same format as unicast                      │
└─────────────────────────────────────────────────┘
```

---

### Q1.c) Differentiate Between Static NAT, Dynamic NAT, and PAT

#### Concept
**NAT (Network Address Translation)** translates private IP addresses to public IP addresses for internet communication.

#### Comparison Table

| Feature | Static NAT | Dynamic NAT | PAT (NAT Overload) |
|---------|------------|-------------|---------------------|
| **Mapping** | One-to-One (permanent) | One-to-One (temporary) | Many-to-One |
| **IP Pool** | Single public IP per device | Pool of public IPs | Single or few public IPs |
| **Port Translation** | No | No | Yes |
| **Use Case** | Web servers, mail servers | Medium organizations | Home/office networks |
| **Cost** | Highest (many IPs needed) | Medium | Lowest |
| **Scalability** | Low | Medium | High |
| **Connection Initiated** | Both directions | Internal only | Internal only |

#### Detailed Explanation with Examples

**1. Static NAT (One-to-One)**
```
                   STATIC NAT
Internal           ┌──────────┐        External
192.168.1.10  ────►│ NAT      │────►  203.0.113.10
                   │ Router   │
192.168.1.20  ────►│          │────►  203.0.113.20
                   └──────────┘
Fixed mapping: Each private IP always maps to same public IP
```
- **Use:** Hosting servers that need consistent external access
- **Example:** Web server 192.168.1.100 → always 203.0.113.100

**2. Dynamic NAT (One-to-One, Temporary)**
```
                   DYNAMIC NAT
Internal           ┌──────────┐        External Pool
192.168.1.10  ────►│ NAT      │────►  {203.0.113.10
192.168.1.20  ────►│ Router   │────►   203.0.113.11
192.168.1.30  ────►│          │────►   203.0.113.12}
                   └──────────┘
Pool assigns IPs temporarily from available addresses
```
- **Use:** Organizations with multiple users needing internet
- **Example:** First available public IP assigned; returned when done

**3. PAT / NAT Overload (Many-to-One)**
```
                   PAT (Port Address Translation)
Internal                  ┌──────────┐         External
192.168.1.10:5000   ────►│ NAT      │────►  203.0.113.1:40001
192.168.1.20:5000   ────►│ Router   │────►  203.0.113.1:40002
192.168.1.30:5000   ────►│          │────►  203.0.113.1:40003
                         └──────────┘
Same public IP, different ports identify connections
```
- **Use:** Home/SOHO networks (most common)
- **Example:** All home devices share single public IP using port numbers

#### NAT Translation Table Example (PAT)
| Inside Local | Inside Global | Outside Global | Outside Local |
|--------------|---------------|----------------|---------------|
| 192.168.1.10:1025 | 203.0.113.1:40001 | 8.8.8.8:53 | 8.8.8.8:53 |
| 192.168.1.20:1026 | 203.0.113.1:40002 | 8.8.8.8:53 | 8.8.8.8:53 |

---

### Q1.d) Configure Dynamic NAT with a Pool of Public IP Addresses

#### Concept
Dynamic NAT configuration involves defining an IP pool and ACL to specify which internal addresses can be translated.

#### Configuration Steps (Cisco IOS)

```
Step 1: Define Internal and External Interfaces
─────────────────────────────────────────────────
Router(config)# interface GigabitEthernet0/0
Router(config-if)# ip address 192.168.1.1 255.255.255.0
Router(config-if)# ip nat inside
Router(config-if)# no shutdown

Router(config)# interface GigabitEthernet0/1
Router(config-if)# ip address 203.0.113.1 255.255.255.0
Router(config-if)# ip nat outside
Router(config-if)# no shutdown
```

```
Step 2: Define Public IP Address Pool
─────────────────────────────────────────────────
Router(config)# ip nat pool NATPOOL 203.0.113.10 203.0.113.20 netmask 255.255.255.0

Explanation:
- Pool name: NATPOOL
- Start IP: 203.0.113.10
- End IP: 203.0.113.20
- Provides 11 public IPs
```

```
Step 3: Create Access Control List (ACL)
─────────────────────────────────────────────────
Router(config)# access-list 1 permit 192.168.1.0 0.0.0.255

Explanation:
- ACL 1 permits internal network 192.168.1.0/24
- Wildcard mask: 0.0.0.255 (inverse of subnet mask)
```

```
Step 4: Associate ACL with NAT Pool
─────────────────────────────────────────────────
Router(config)# ip nat inside source list 1 pool NATPOOL

Explanation:
- Links ACL 1 (internal IPs) to NATPOOL (public IPs)
```

#### Complete Configuration Example
```cisco
! Configure interfaces
interface GigabitEthernet0/0
 description LAN Interface
 ip address 192.168.1.1 255.255.255.0
 ip nat inside
 no shutdown
!
interface GigabitEthernet0/1
 description WAN Interface  
 ip address 203.0.113.1 255.255.255.0
 ip nat outside
 no shutdown
!
! Define NAT pool
ip nat pool COMPANY_POOL 203.0.113.10 203.0.113.20 netmask 255.255.255.0
!
! Define which internal addresses to translate
access-list 10 permit 192.168.1.0 0.0.0.255
!
! Apply NAT
ip nat inside source list 10 pool COMPANY_POOL
```

#### Verification Commands
```cisco
Router# show ip nat translations      ! View active translations
Router# show ip nat statistics        ! View NAT statistics
Router# debug ip nat                  ! Debug NAT operations
Router# clear ip nat translation *    ! Clear all translations
```

#### Network Diagram
```
         Internal Network              NAT Router                Internet
    ┌─────────────────────┐       ┌──────────────┐        ┌───────────────┐
    │  PC1: 192.168.1.10  │───────│ Inside:      │        │               │
    │  PC2: 192.168.1.20  │───────│ 192.168.1.1  │────────│   Internet    │
    │  PC3: 192.168.1.30  │───────│              │        │   Servers     │
    │         ...         │       │ Outside:     │        │               │
    └─────────────────────┘       │ 203.0.113.1  │        └───────────────┘
                                  │              │
                                  │ Pool:        │
                                  │ 203.0.113.10 │
                                  │     to       │
                                  │ 203.0.113.20 │
                                  └──────────────┘
```

---

### Q1.f) Define Cyber Security

#### Definition
**Cyber Security** (also spelled Cybersecurity) is the practice of protecting systems, networks, programs, devices, and data from digital attacks, unauthorized access, damage, or theft.

#### Key Components (CIA Triad + AAA)

```
                     ┌─────────────────┐
                     │ CONFIDENTIALITY │
                     │ (Prevent        │
                     │  unauthorized   │
                     │  access)        │
                     └────────┬────────┘
                              │
              ┌───────────────┼───────────────┐
              │               │               │
     ┌────────▼───────┐       │      ┌────────▼───────┐
     │   INTEGRITY    │       │      │  AVAILABILITY  │
     │ (Prevent       │       │      │ (Ensure system │
     │  unauthorized  │◄──────┴─────►│  uptime and    │
     │  modification) │              │  accessibility)│
     └────────────────┘              └────────────────┘
```

#### Types of Cyber Security

| Domain | Description | Examples |
|--------|-------------|----------|
| **Network Security** | Protect network infrastructure | Firewalls, IDS/IPS, VPN |
| **Application Security** | Secure software applications | Code review, WAF, patches |
| **Information Security** | Protect data integrity | Encryption, DLP, backups |
| **Endpoint Security** | Secure end-user devices | Antivirus, EDR, MDM |
| **Cloud Security** | Protect cloud resources | IAM, encryption, monitoring |
| **Identity Management** | Control user access | MFA, SSO, RBAC |

#### Common Cyber Threats
```
┌────────────────────────────────────────────────────────┐
│ CYBER THREATS                                          │
├────────────────────────────────────────────────────────┤
│ • Malware: Viruses, worms, trojans, ransomware        │
│ • Phishing: Fraudulent emails/websites                │
│ • DDoS: Overwhelming systems with traffic             │
│ • Man-in-the-Middle: Intercepting communications      │
│ • SQL Injection: Database manipulation                │
│ • Zero-Day Exploits: Unknown vulnerabilities          │
│ • Social Engineering: Human manipulation              │
│ • Insider Threats: Malicious employees                │
└────────────────────────────────────────────────────────┘
```

#### Cyber Security Best Practices
1. **Strong Passwords:** Use complex, unique passwords
2. **Multi-Factor Authentication (MFA):** Add extra verification
3. **Regular Updates:** Patch systems and software
4. **Encryption:** Protect data in transit and at rest
5. **Backup:** Regular data backups (3-2-1 rule)
6. **Training:** Security awareness for employees
7. **Monitoring:** Continuous security monitoring

---

### Q1.g) Explain Ethical Hacking

#### Definition
**Ethical Hacking** (also called Penetration Testing or White Hat Hacking) is the authorized practice of bypassing system security to identify potential data breaches and threats in a network or system.

#### Ethical Hacking vs. Malicious Hacking

| Aspect | Ethical Hacking | Malicious Hacking |
|--------|-----------------|-------------------|
| **Authorization** | Has written permission | Unauthorized |
| **Intent** | Improve security | Cause harm/steal data |
| **Legal Status** | Legal | Illegal (criminal) |
| **Reporting** | Reports all findings | Exploits vulnerabilities |
| **Outcome** | Strengthens defenses | Creates damage |

#### Types of Hackers
```
┌──────────────────────────────────────────────────────────┐
│           HACKER CLASSIFICATION                          │
├──────────────────────────────────────────────────────────┤
│ WHITE HAT (Ethical)                                      │
│   • Authorized security professionals                    │
│   • Work to protect systems                              │
│   • Examples: Penetration testers, security researchers  │
├──────────────────────────────────────────────────────────┤
│ BLACK HAT (Malicious)                                    │
│   • Unauthorized access                                  │
│   • Criminal intent                                      │
│   • Examples: Cybercriminals, hacktivists (malicious)    │
├──────────────────────────────────────────────────────────┤
│ GREY HAT (Mixed)                                         │
│   • May not have explicit permission                     │
│   • No malicious intent                                  │
│   • May disclose vulnerabilities publicly                │
└──────────────────────────────────────────────────────────┘
```

#### Ethical Hacking Phases

```
  ┌─────────────┐     ┌─────────────┐     ┌─────────────┐
  │ 1.RECON     │────►│ 2.SCANNING  │────►│ 3.GAINING   │
  │ (Footprint- │     │ (Port scan, │     │   ACCESS    │
  │  ing)       │     │  vuln scan) │     │ (Exploit)   │
  └─────────────┘     └─────────────┘     └──────┬──────┘
                                                 │
  ┌─────────────┐     ┌─────────────┐            │
  │ 5.REPORTING │◄────│ 4.MAINTAIN  │◄───────────┘
  │ (Document   │     │   ACCESS    │
  │  findings)  │     │ (Persist)   │
  └─────────────┘     └─────────────┘
```

**Phase 1: Reconnaissance (Information Gathering)**
- Passive: WHOIS, DNS lookup, social media
- Active: Network scanning, social engineering

**Phase 2: Scanning**
- Port scanning (Nmap)
- Vulnerability scanning (Nessus, OpenVAS)
- Network mapping

**Phase 3: Gaining Access**
- Exploit vulnerabilities
- Password cracking
- Social engineering attacks

**Phase 4: Maintaining Access**
- Install backdoors
- Create persistence mechanisms
- Escalate privileges

**Phase 5: Covering Tracks & Reporting**
- Document all findings
- Provide remediation recommendations
- Present report to management

#### Common Ethical Hacking Tools
| Category | Tools |
|----------|-------|
| Reconnaissance | Nmap, Maltego, Shodan |
| Vulnerability Scanning | Nessus, OpenVAS, Nikto |
| Exploitation | Metasploit, Burp Suite |
| Password Cracking | John the Ripper, Hashcat |
| Wireless | Aircrack-ng, Wireshark |

#### Certifications for Ethical Hackers
- **CEH (Certified Ethical Hacker)** - EC-Council
- **OSCP (Offensive Security Certified Professional)**
- **GPEN (GIAC Penetration Tester)**
- **CompTIA PenTest+**

---

## Q2: Practical Questions (20 marks)

---

### Q2 Option A: IP Address Class Determination Program

#### Concept
Determine the class of an IP address by analyzing the first octet value.

#### Algorithm
```
1. Input IP address as string
2. Extract first octet (parse before first dot)
3. Convert first octet to integer
4. Determine class based on range:
   - 1-126: Class A
   - 127: Loopback
   - 128-191: Class B
   - 192-223: Class C
   - 224-239: Class D (Multicast)
   - 240-255: Class E (Reserved)
5. Display class and additional information
```

#### Pseudocode
```
FUNCTION determine_ip_class(ip_address):
    first_octet = extract_first_octet(ip_address)
    
    IF first_octet >= 1 AND first_octet <= 126:
        RETURN "Class A"
    ELSE IF first_octet == 127:
        RETURN "Loopback"
    ELSE IF first_octet >= 128 AND first_octet <= 191:
        RETURN "Class B"
    ELSE IF first_octet >= 192 AND first_octet <= 223:
        RETURN "Class C"
    ELSE IF first_octet >= 224 AND first_octet <= 239:
        RETURN "Class D (Multicast)"
    ELSE IF first_octet >= 240 AND first_octet <= 255:
        RETURN "Class E (Reserved)"
    ELSE:
        RETURN "Invalid IP"
```

> **Implementation:** See `Slip_09_Q2_OptionA.c`

---

### Q2 Option B: Static Routing Simulation Program

#### Concept
Simulate static routing by maintaining a routing table and determining next-hop for destination IPs.

#### Algorithm
```
1. Initialize routing table with network, mask, next-hop, interface
2. Input destination IP address
3. For each route in routing table:
   - Apply subnet mask to destination
   - Compare with network address
   - If match found, return route info
4. If no match, use default route (0.0.0.0)
5. Display routing decision
```

#### Pseudocode
```
STRUCTURE Route:
    network_address
    subnet_mask
    next_hop
    interface

FUNCTION find_route(destination, routing_table):
    best_match = NULL
    
    FOR each route IN routing_table:
        masked_dest = destination AND route.subnet_mask
        IF masked_dest == route.network_address:
            IF route is more specific than best_match:
                best_match = route
    
    IF best_match != NULL:
        RETURN best_match
    ELSE:
        RETURN default_route
```

> **Implementation:** See `Slip_09_Q2_OptionB.c`

---

### Q2 Option C: Packet Tracer Configuration

#### Network Setup
```
         PC1                    Switch                   PC2
    ┌──────────┐           ┌──────────┐            ┌──────────┐
    │172.20.1.1│───────────│  Switch  │────────────│172.20.1.2│
    │/16       │    Fa0    │          │    Fa1     │/16       │
    └──────────┘           └──────────┘            └──────────┘
```

#### Step-by-Step Configuration

**Step 1: Add Devices**
1. Open Cisco Packet Tracer
2. Add: 1 Switch (2960)
3. Add: 2 PCs

**Step 2: Connect Devices**
```
PC1 (FastEthernet0) ─── Copper Straight ─── Switch (Fa0/1)
PC2 (FastEthernet0) ─── Copper Straight ─── Switch (Fa0/2)
```

**Step 3: Configure PC1**
```
Click PC1 → Desktop → IP Configuration

IP Address:    172.20.1.1
Subnet Mask:   255.255.0.0
Default Gateway: 172.20.1.1 (or leave blank for same network)
```

**Step 4: Configure PC2**
```
Click PC2 → Desktop → IP Configuration

IP Address:    172.20.1.2
Subnet Mask:   255.255.0.0
Default Gateway: 172.20.1.2 (or leave blank)
```

**Step 5: Verify Connectivity**
```
PC1 → Desktop → Command Prompt
C:\> ping 172.20.1.2

Reply from 172.20.1.2: bytes=32 time<1ms TTL=128
Reply from 172.20.1.2: bytes=32 time<1ms TTL=128
```

#### IP Class Explanation for This Configuration

**IP Address: 172.20.1.1 and 172.20.1.2**
- **First Octet:** 172
- **Range Check:** 128-191
- **Class:** B

**Class B Characteristics:**
- Network portion: First 2 octets (172.20)
- Host portion: Last 2 octets (1.1 and 1.2)
- Default mask: 255.255.0.0 (matches configuration)
- Network ID: 172.20.0.0
- Broadcast: 172.20.255.255
- Usable hosts: 65,534 (2^16 - 2)

**Why Both PCs Can Communicate:**
1. Same network: 172.20.0.0/16
2. Same subnet mask: 255.255.0.0
3. Both hosts are in valid range (1-65534)
4. Switch provides Layer 2 connectivity

---

## Summary

| Question | Topic | Key Points |
|----------|-------|------------|
| Q1.a | IP Classes | A(1-126), B(128-191), C(192-223), D(224-239), E(240-255) |
| Q1.b | IPv6 | 128-bit, 8 hextets, :: compression, types |
| Q1.c | NAT Types | Static(1:1 fixed), Dynamic(1:1 pool), PAT(many:1+ports) |
| Q1.d | Dynamic NAT | Pool config, ACL, interface marking |
| Q1.f | Cyber Security | CIA triad, protection of digital assets |
| Q1.g | Ethical Hacking | Authorized testing, 5 phases, white hat |
| Q2.A | IP Class Program | Parse first octet, range checking |
| Q2.B | Routing Simulation | Routing table, longest prefix match |
| Q2.C | Packet Tracer | Switch config, Class B network |

---

> **Code Solutions:** See `Slip_09_Q2_OptionA.c` and `Slip_09_Q2_OptionB.c` in this folder.
