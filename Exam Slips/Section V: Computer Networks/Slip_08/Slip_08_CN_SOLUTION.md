# Slip 08 - Computer Networks Solutions

## Q1: Theory Questions (10 Marks - Answer ANY 5)

---

### a) Why is it important to configure an enable (EXEC mode) password on a switch?

**Importance of Enable Password:**

The enable password (also called privileged EXEC mode password) is crucial for network security:

1. **Access Control**: Prevents unauthorized users from accessing privileged EXEC mode where sensitive configurations can be viewed or modified.

2. **Protection of Configuration**: Without the enable password, anyone with console access could:
   - View running configurations (including other passwords)
   - Modify VLAN configurations
   - Change IP addresses
   - Disable ports
   - Reset the device

3. **Security Layers**: Provides defense-in-depth security:
   ```
   User EXEC Mode (>) → Limited commands
         ↓ (requires enable password)
   Privileged EXEC Mode (#) → Full access
   ```

4. **Compliance Requirements**: Most security standards (PCI-DSS, HIPAA) require access controls on network devices.

5. **Audit Trail**: When combined with usernames, helps in tracking who made configuration changes.

**Configuration Commands:**
```cisco
Switch> enable
Switch# configure terminal
Switch(config)# enable password cisco123        ! Plain text (not recommended)
Switch(config)# enable secret cisco456          ! MD5 encrypted (recommended)
```

**Best Practice**: Always use `enable secret` instead of `enable password` as it uses MD5 hashing.

---

### b) Explain the role of VLAN1 in a switch's initial configuration.

**VLAN1 - The Default/Native VLAN:**

VLAN1 serves several critical roles in Cisco switch configuration:

1. **Default VLAN**: All switch ports belong to VLAN1 by default out of the box.

2. **Management VLAN**: Used for remote switch management:
   - Telnet/SSH access
   - SNMP monitoring
   - HTTP/HTTPS management interface

3. **Native VLAN**: Carries untagged traffic on trunk links (802.1Q)

4. **Control Plane Traffic**: Carries important protocols:
   - CDP (Cisco Discovery Protocol)
   - VTP (VLAN Trunking Protocol)
   - STP (Spanning Tree Protocol)
   - DTP (Dynamic Trunking Protocol)

**Initial Configuration Diagram:**
```
┌─────────────────────────────────────┐
│           SWITCH (Initial)          │
├─────────────────────────────────────┤
│  Fa0/1  │  Fa0/2  │  ...  │ Fa0/24 │
│  VLAN1  │  VLAN1  │  ...  │ VLAN1  │
└─────────────────────────────────────┘
         All ports in VLAN1
```

**Management IP Configuration:**
```cisco
Switch(config)# interface vlan 1
Switch(config-if)# ip address 192.168.1.2 255.255.255.0
Switch(config-if)# no shutdown
Switch(config-if)# exit
Switch(config)# ip default-gateway 192.168.1.1
```

**Security Consideration**: Best practice is to change the management VLAN from VLAN1 to another VLAN to prevent VLAN hopping attacks.

---

### c) Configure Static NAT on a router using Cisco Packet Tracer

**Static NAT Concept:**
Static NAT creates a one-to-one mapping between a private (inside) IP address and a public (outside) IP address.

```
┌─────────────┐      ┌──────────────┐      ┌─────────────┐
│  PC/Server  │──────│    Router    │──────│  Internet   │
│ 192.168.1.10│      │   NAT        │      │             │
│  (Private)  │      │              │      │             │
└─────────────┘      └──────────────┘      └─────────────┘
                     Inside: Gig0/0              Outside: Gig0/1
                     192.168.1.1                 203.0.113.1
                     
        Static NAT: 192.168.1.10 ↔ 203.0.113.10
```

**Configuration Steps:**

```cisco
! Step 1: Enter global configuration mode
Router> enable
Router# configure terminal

! Step 2: Configure inside interface
Router(config)# interface GigabitEthernet0/0
Router(config-if)# ip address 192.168.1.1 255.255.255.0
Router(config-if)# ip nat inside
Router(config-if)# no shutdown
Router(config-if)# exit

! Step 3: Configure outside interface
Router(config)# interface GigabitEthernet0/1
Router(config-if)# ip address 203.0.113.1 255.255.255.0
Router(config-if)# ip nat outside
Router(config-if)# no shutdown
Router(config-if)# exit

! Step 4: Create Static NAT mapping
Router(config)# ip nat inside source static 192.168.1.10 203.0.113.10

! Step 5: Verify configuration
Router# show ip nat translations
Router# show ip nat statistics
```

**Verification Output:**
```
Router# show ip nat translations
Pro  Inside global     Inside local       Outside local      Outside global
---  203.0.113.10      192.168.1.10       ---                ---
```

---

### d) Configure Dynamic NAT with a pool of public IP addresses

**Dynamic NAT Concept:**
Dynamic NAT maps private IP addresses to a pool of public IP addresses on a first-come, first-served basis.

```
┌─────────────┐
│ PC1: .10    │───┐
├─────────────┤   │     ┌──────────────┐     ┌─────────────┐
│ PC2: .20    │───┼─────│    Router    │─────│  Internet   │
├─────────────┤   │     │   NAT Pool   │     │             │
│ PC3: .30    │───┘     │ 203.0.113.   │     │             │
└─────────────┘         │  10-14       │     └─────────────┘
  192.168.1.0/24        └──────────────┘
  (5 hosts)               (5 public IPs)
```

**Configuration Steps:**

```cisco
! Step 1: Enter global configuration mode
Router> enable
Router# configure terminal

! Step 2: Configure inside interface
Router(config)# interface GigabitEthernet0/0
Router(config-if)# ip address 192.168.1.1 255.255.255.0
Router(config-if)# ip nat inside
Router(config-if)# no shutdown
Router(config-if)# exit

! Step 3: Configure outside interface
Router(config)# interface GigabitEthernet0/1
Router(config-if)# ip address 203.0.113.1 255.255.255.0
Router(config-if)# ip nat outside
Router(config-if)# no shutdown
Router(config-if)# exit

! Step 4: Define the NAT pool with public IP addresses
Router(config)# ip nat pool PUBLIC_POOL 203.0.113.10 203.0.113.14 netmask 255.255.255.0

! Step 5: Create Access Control List to identify inside hosts
Router(config)# access-list 1 permit 192.168.1.0 0.0.0.255

! Step 6: Associate ACL with NAT pool
Router(config)# ip nat inside source list 1 pool PUBLIC_POOL

! Step 7: Exit and save
Router(config)# exit
Router# copy running-config startup-config
```

**Verification Commands:**
```cisco
Router# show ip nat translations
Pro  Inside global     Inside local       Outside local      Outside global
---  203.0.113.10      192.168.1.10       ---                ---
---  203.0.113.11      192.168.1.20       ---                ---
---  203.0.113.12      192.168.1.30       ---                ---

Router# show ip nat statistics
Total active translations: 3
Outside interfaces: GigabitEthernet0/1
Inside interfaces: GigabitEthernet0/0
Hits: 156  Misses: 3
Dynamic mappings:
  -- Inside Source
  access-list 1 pool PUBLIC_POOL refcount 3
  pool PUBLIC_POOL: netmask 255.255.255.0
    start 203.0.113.10 end 203.0.113.14
    type generic, total addresses 5, allocated 3, misses 0
```

---

### f) Define Hashing

**Definition:**
Hashing is a cryptographic technique that converts data of any size into a fixed-size string of characters (hash value/digest) using a mathematical function called a hash function.

**Key Properties of Hash Functions:**

1. **Deterministic**: Same input always produces same output
2. **Fixed Output Size**: Regardless of input size
3. **One-Way Function**: Cannot reverse to get original data
4. **Avalanche Effect**: Small input change → completely different hash
5. **Collision Resistant**: Difficult to find two inputs with same hash

**Common Hash Algorithms:**

| Algorithm | Output Size | Security Level |
|-----------|-------------|----------------|
| MD5       | 128 bits    | Weak (deprecated) |
| SHA-1     | 160 bits    | Weak (deprecated) |
| SHA-256   | 256 bits    | Strong |
| SHA-512   | 512 bits    | Very Strong |

**Visual Representation:**
```
Input Data (any size)          Hash Function         Hash Value (fixed size)
┌──────────────────┐          ┌───────────┐         ┌──────────────────┐
│ "Hello World"    │ ───────► │  SHA-256  │ ──────► │ a591a6d40bf420...│
│ (11 characters)  │          └───────────┘         │ (256 bits/64 hex)│
└──────────────────┘                                └──────────────────┘

┌──────────────────┐          ┌───────────┐         ┌──────────────────┐
│ "Hello World!"   │ ───────► │  SHA-256  │ ──────► │ 7f83b1657ff1fc...│
│ (12 characters)  │          └───────────┘         │ (completely diff)│
└──────────────────┘                                └──────────────────┘
```

**Applications in Networking:**

1. **Password Storage**: Store hash instead of plain text
2. **Data Integrity**: Verify file/message not modified
3. **Digital Signatures**: Sign hash of document
4. **HMAC**: Message authentication codes
5. **Blockchain**: Linking blocks securely
6. **Certificate Verification**: SSL/TLS certificates

**Example (MD5):**
```
Input: "password123"
MD5 Hash: 482c811da5d5b4bc6d497ffa98491e38
```

---

### g) What are Cyber Security Policies?

**Definition:**
Cyber Security Policies are formal documented guidelines that define how an organization protects its digital assets, manages security risks, and responds to security incidents.

**Types of Cyber Security Policies:**

```
┌────────────────────────────────────────────────────────────────┐
│                  CYBER SECURITY POLICIES                        │
├────────────────────────────────────────────────────────────────┤
│                                                                 │
│  ┌─────────────────┐  ┌─────────────────┐  ┌─────────────────┐│
│  │ Access Control  │  │ Data Protection │  │ Network Security││
│  │ Policy          │  │ Policy          │  │ Policy          ││
│  └─────────────────┘  └─────────────────┘  └─────────────────┘│
│                                                                 │
│  ┌─────────────────┐  ┌─────────────────┐  ┌─────────────────┐│
│  │ Incident        │  │ Password        │  │ Acceptable Use  ││
│  │ Response Policy │  │ Policy          │  │ Policy          ││
│  └─────────────────┘  └─────────────────┘  └─────────────────┘│
│                                                                 │
│  ┌─────────────────┐  ┌─────────────────┐  ┌─────────────────┐│
│  │ BYOD Policy     │  │ Remote Access   │  │ Backup & Recovery│
│  │                 │  │ Policy          │  │ Policy          ││
│  └─────────────────┘  └─────────────────┘  └─────────────────┘│
└────────────────────────────────────────────────────────────────┘
```

**Key Policy Components:**

1. **Access Control Policy**
   - User authentication requirements
   - Role-based access control (RBAC)
   - Privilege management

2. **Password Policy**
   - Minimum length (e.g., 12+ characters)
   - Complexity requirements
   - Expiration periods
   - History restrictions

3. **Data Protection Policy**
   - Data classification (Public, Internal, Confidential)
   - Encryption requirements
   - Data retention periods

4. **Network Security Policy**
   - Firewall rules
   - VPN usage
   - Wireless security standards

5. **Incident Response Policy**
   - Detection procedures
   - Reporting chain
   - Containment steps
   - Recovery procedures

**Importance:**
- Regulatory compliance (GDPR, HIPAA, PCI-DSS)
- Risk management
- Employee awareness
- Legal protection
- Business continuity

---

## Q2: Practical Programming Questions (20 Marks)

### Option A: Network Configuration Verification Program
See: `Slip_08_Q2_OptionA.c`

### Option B: Dynamic Routing Protocol (RIP) Simulation
See: `Slip_08_Q2_OptionB.c`

### Option C: Configure Cisco Switch 2960 Initial Settings

**Packet Tracer Steps:**

1. **Open Packet Tracer** and add a Switch 2960
2. **Connect via Console Cable** to a PC
3. **Access CLI** through Terminal on PC

**CLI Configuration Commands:**

```cisco
! Step 1: Enter privileged EXEC mode
Switch> enable

! Step 2: Enter global configuration mode
Switch# configure terminal

! Step 3: Set hostname
Switch(config)# hostname SW-CLASSROOM

! Step 4: Secure console line with password
SW-CLASSROOM(config)# line console 0
SW-CLASSROOM(config-line)# password console123
SW-CLASSROOM(config-line)# login
SW-CLASSROOM(config-line)# exit

! Step 5: Set enable password (encrypted)
SW-CLASSROOM(config)# enable secret admin456

! Step 6: Set VTY (Telnet/SSH) password
SW-CLASSROOM(config)# line vty 0 15
SW-CLASSROOM(config-line)# password vty789
SW-CLASSROOM(config-line)# login
SW-CLASSROOM(config-line)# exit

! Step 7: Encrypt all plain-text passwords
SW-CLASSROOM(config)# service password-encryption

! Step 8: Set Message of the Day banner
SW-CLASSROOM(config)# banner motd #Unauthorized Access Prohibited!#

! Step 9: Configure management interface
SW-CLASSROOM(config)# interface vlan 1
SW-CLASSROOM(config-if)# ip address 192.168.1.2 255.255.255.0
SW-CLASSROOM(config-if)# no shutdown
SW-CLASSROOM(config-if)# exit

! Step 10: Set default gateway
SW-CLASSROOM(config)# ip default-gateway 192.168.1.1

! Step 11: Exit and save configuration
SW-CLASSROOM(config)# exit
SW-CLASSROOM# copy running-config startup-config
Destination filename [startup-config]? 
Building configuration...
[OK]
```

**Verification Commands:**
```cisco
SW-CLASSROOM# show running-config
SW-CLASSROOM# show ip interface brief
SW-CLASSROOM# show version
```

---

## Summary Table

| Question | Topic | Key Points |
|----------|-------|------------|
| Q1(a) | Enable Password | Security, Access Control, MD5 Encryption |
| Q1(b) | VLAN1 | Default VLAN, Management, Native VLAN |
| Q1(c) | Static NAT | One-to-one mapping, ip nat inside/outside |
| Q1(d) | Dynamic NAT | Pool of IPs, ACL, First-come-first-served |
| Q1(f) | Hashing | One-way function, SHA-256, Integrity |
| Q1(g) | Security Policies | Guidelines, Compliance, Risk Management |
| Q2-A | Config Verification | show running-config, ping |
| Q2-B | Dynamic Routing | RIP, Distance Vector, Hop Count |
| Q2-C | Switch Config | hostname, console password, CLI |

---
*Slip 08 - Computer Networks - Complete Solutions*
