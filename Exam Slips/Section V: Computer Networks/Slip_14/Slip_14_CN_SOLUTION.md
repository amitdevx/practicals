# Slip 14: Computer Networks - Complete Solutions

## Q1: Theory Questions (10 Marks) - Answer ANY 5

---

### a) Configure PAT (NAT Overload) to Allow Multiple Internal Hosts to Access the Internet Using a Single Public IP

**Port Address Translation (PAT)**, also known as **NAT Overload**, allows multiple devices on a private network to share a single public IP address by using different port numbers to track connections.

#### Concept

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                           PAT (NAT Overload)                                │
├─────────────────────────────────────────────────────────────────────────────┤
│                                                                             │
│   PRIVATE NETWORK              ROUTER                    INTERNET           │
│   ┌─────────────┐                                                           │
│   │ PC1         │              ┌──────────────┐                             │
│   │ 192.168.1.10│──┐           │              │        ┌─────────────┐      │
│   └─────────────┘  │           │   PAT        │        │             │      │
│   ┌─────────────┐  │    ┌──────│   Router     │────────│  Internet   │      │
│   │ PC2         │──┼────│      │              │        │  Server     │      │
│   │ 192.168.1.11│  │    │      │ Public IP:   │        │  8.8.8.8    │      │
│   └─────────────┘  │    │      │ 203.0.113.1  │        └─────────────┘      │
│   ┌─────────────┐  │    │      └──────────────┘                             │
│   │ PC3         │──┘    │                                                   │
│   │ 192.168.1.12│       │                                                   │
│   └─────────────┘       │                                                   │
│                         │                                                   │
│   All use ports to      │                                                   │
│   share ONE public IP   │                                                   │
└─────────────────────────────────────────────────────────────────────────────┘
```

#### PAT Translation Table

| Inside Local | Inside Global | Outside Global | Port |
|--------------|---------------|----------------|------|
| 192.168.1.10:1025 | 203.0.113.1:1025 | 8.8.8.8:80 | HTTP |
| 192.168.1.11:1026 | 203.0.113.1:1026 | 8.8.8.8:80 | HTTP |
| 192.168.1.12:1027 | 203.0.113.1:1027 | 8.8.8.8:443 | HTTPS |

#### Configuration Steps (Cisco IOS)

```cisco
! Step 1: Define Access Control List for internal network
Router(config)# access-list 1 permit 192.168.1.0 0.0.0.255

! Step 2: Configure inside interface (connected to LAN)
Router(config)# interface GigabitEthernet0/0
Router(config-if)# ip address 192.168.1.1 255.255.255.0
Router(config-if)# ip nat inside
Router(config-if)# no shutdown
Router(config-if)# exit

! Step 3: Configure outside interface (connected to Internet)
Router(config)# interface GigabitEthernet0/1
Router(config-if)# ip address 203.0.113.1 255.255.255.0
Router(config-if)# ip nat outside
Router(config-if)# no shutdown
Router(config-if)# exit

! Step 4: Enable PAT (NAT Overload)
Router(config)# ip nat inside source list 1 interface GigabitEthernet0/1 overload

! Step 5: Configure default route to ISP
Router(config)# ip route 0.0.0.0 0.0.0.0 203.0.113.254
```

#### Verification Commands

```cisco
! View NAT translations
Router# show ip nat translations

! View NAT statistics
Router# show ip nat statistics

! Clear NAT translations
Router# clear ip nat translation *
```

#### Sample Output

```
Router# show ip nat translations
Pro Inside global      Inside local       Outside local      Outside global
tcp 203.0.113.1:1025   192.168.1.10:1025  8.8.8.8:80        8.8.8.8:80
tcp 203.0.113.1:1026   192.168.1.11:1026  8.8.8.8:80        8.8.8.8:80
tcp 203.0.113.1:1027   192.168.1.12:1027  8.8.8.8:443       8.8.8.8:443
```

#### Advantages of PAT
1. **IP Address Conservation**: Multiple hosts share one public IP
2. **Security**: Internal addresses hidden from external networks
3. **Cost Effective**: Reduces need for multiple public IPs

---

### b) Verify Routing with ping, traceroute, and show ip route Commands

#### 1. PING Command

**Purpose**: Tests basic connectivity between devices using ICMP Echo Request/Reply.

```
┌─────────────────────────────────────────────────────────────────┐
│                    PING Operation                               │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│   Source                                        Destination     │
│   ┌──────┐        ICMP Echo Request            ┌──────┐        │
│   │      │────────────────────────────────────>│      │        │
│   │ PC1  │                                     │ PC2  │        │
│   │      │<────────────────────────────────────│      │        │
│   └──────┘         ICMP Echo Reply             └──────┘        │
│                                                                 │
│   Measures: Round-trip time, Packet loss, TTL                   │
└─────────────────────────────────────────────────────────────────┘
```

**Syntax and Examples**:

```cisco
! Basic ping
Router# ping 192.168.2.1

! Extended ping with options
Router# ping
Protocol [ip]: ip
Target IP address: 192.168.2.1
Repeat count [5]: 10
Datagram size [100]: 1500
Timeout in seconds [2]: 5
Extended commands [n]: y
Source address or interface: 192.168.1.1
```

**Sample Output**:
```
Router# ping 192.168.2.1
Type escape sequence to abort.
Sending 5, 100-byte ICMP Echos to 192.168.2.1, timeout is 2 seconds:
!!!!!
Success rate is 100 percent (5/5), round-trip min/avg/max = 1/2/4 ms
```

**Symbols Interpretation**:
| Symbol | Meaning |
|--------|---------|
| ! | Reply received |
| . | Timeout (no reply) |
| U | Destination unreachable |
| Q | Source quench |
| M | Could not fragment |
| ? | Unknown packet type |

---

#### 2. TRACEROUTE Command

**Purpose**: Displays the path packets take to reach a destination, showing each hop.

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                      TRACEROUTE Operation                                   │
├─────────────────────────────────────────────────────────────────────────────┤
│                                                                             │
│   Source      Hop 1       Hop 2       Hop 3       Destination               │
│   ┌────┐     ┌────┐      ┌────┐      ┌────┐      ┌────┐                     │
│   │ PC │────>│ R1 │─────>│ R2 │─────>│ R3 │─────>│ Web │                    │
│   └────┘     └────┘      └────┘      └────┘      └────┘                     │
│                                                                             │
│   TTL=1      TTL=2       TTL=3       TTL=4       TTL=5                      │
│   Expires    Expires     Expires     Expires     Reaches                    │
│   here       here        here        here        destination                │
│                                                                             │
│   Each router sends ICMP Time Exceeded message back to source               │
└─────────────────────────────────────────────────────────────────────────────┘
```

**How It Works**:
1. Sends packets with incrementing TTL (Time To Live)
2. Each router decrements TTL; when TTL=0, router sends ICMP Time Exceeded
3. Reveals each hop's IP address and response time

**Syntax**:
```cisco
Router# traceroute 8.8.8.8
```

**Sample Output**:
```
Router# traceroute 8.8.8.8
Type escape sequence to abort.
Tracing the route to 8.8.8.8
  1 192.168.1.1 4 msec 4 msec 4 msec
  2 10.0.0.1 8 msec 8 msec 8 msec
  3 172.16.0.1 16 msec 16 msec 16 msec
  4 8.8.8.8 20 msec 20 msec 20 msec
```

---

#### 3. SHOW IP ROUTE Command

**Purpose**: Displays the complete routing table of the router.

**Syntax**:
```cisco
Router# show ip route
```

**Sample Output**:
```
Router# show ip route
Codes: C - connected, S - static, R - RIP, M - mobile, B - BGP
       D - EIGRP, EX - EIGRP external, O - OSPF, IA - OSPF inter area
       N1 - OSPF NSSA external type 1, N2 - OSPF NSSA external type 2
       E1 - OSPF external type 1, E2 - OSPF external type 2
       * - candidate default

Gateway of last resort is 203.0.113.254 to network 0.0.0.0

C    192.168.1.0/24 is directly connected, GigabitEthernet0/0
C    192.168.2.0/24 is directly connected, GigabitEthernet0/1
S    10.0.0.0/8 [1/0] via 192.168.2.2
R    172.16.0.0/16 [120/1] via 192.168.1.2, 00:00:23, GigabitEthernet0/0
S*   0.0.0.0/0 [1/0] via 203.0.113.254
```

**Route Code Meanings**:
| Code | Meaning | Administrative Distance |
|------|---------|------------------------|
| C | Connected | 0 |
| S | Static | 1 |
| R | RIP | 120 |
| O | OSPF | 110 |
| D | EIGRP | 90 |
| B | BGP | 20 (eBGP), 200 (iBGP) |

---

### c) Assign the Privileged EXEC Mode Password as "class"

**Privileged EXEC mode** (enable mode) provides full access to router configuration.

#### Understanding Password Levels

```
┌─────────────────────────────────────────────────────────────────┐
│                   Router Access Levels                          │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│   User EXEC Mode          Privileged EXEC Mode                  │
│   ┌────────────┐          ┌────────────────┐                    │
│   │ Router>    │──enable──│ Router#        │                    │
│   │            │   ───>   │                │                    │
│   │ Limited    │          │ Full Access    │                    │
│   │ commands   │          │ All commands   │                    │
│   └────────────┘          └────────────────┘                    │
│         │                        │                              │
│         │                        │ configure terminal           │
│         │                        ▼                              │
│         │                 ┌────────────────┐                    │
│         │                 │Router(config)# │                    │
│         │                 │ Global Config  │                    │
│         │                 └────────────────┘                    │
└─────────────────────────────────────────────────────────────────┘
```

#### Configuration Methods

**Method 1: Enable Password (Clear Text - NOT Recommended)**
```cisco
Router> enable
Router# configure terminal
Router(config)# enable password class
Router(config)# exit
```

**Method 2: Enable Secret (Encrypted - RECOMMENDED)**
```cisco
Router> enable
Router# configure terminal
Router(config)# enable secret class
Router(config)# exit
```

#### Comparison

| Feature | enable password | enable secret |
|---------|-----------------|---------------|
| Encryption | None (Type 0) | MD5 Hash (Type 5) |
| Security | Low | High |
| Visible in config | Yes (plaintext) | No (hashed) |
| Recommended | No | Yes |

#### Verification

```cisco
Router# show running-config | include enable

! Output with enable password:
enable password class

! Output with enable secret:
enable secret 5 $1$mERr$hx5rVt7rPNoS4wqbXKX7m0
```

#### Best Practice: Use Both with Password Encryption

```cisco
Router(config)# enable secret class
Router(config)# service password-encryption
```

---

### d) Use show running-config to Verify All Configurations

**show running-config** displays the current active configuration stored in RAM.

#### Command Usage

```cisco
! Display entire running configuration
Router# show running-config

! Display configuration with line numbers
Router# show running-config | linenum

! Filter specific sections
Router# show running-config | section interface
Router# show running-config | include hostname
Router# show running-config | begin line vty
```

#### Sample Output

```cisco
Router# show running-config
Building configuration...

Current configuration : 1523 bytes
!
version 15.1
service timestamps debug datetime msec
service timestamps log datetime msec
service password-encryption
!
hostname Router1
!
boot-start-marker
boot-end-marker
!
enable secret 5 $1$mERr$hx5rVt7rPNoS4wqbXKX7m0
!
no aaa new-model
!
interface GigabitEthernet0/0
 description LAN Interface
 ip address 192.168.1.1 255.255.255.0
 ip nat inside
 duplex auto
 speed auto
!
interface GigabitEthernet0/1
 description WAN Interface
 ip address 203.0.113.1 255.255.255.0
 ip nat outside
 duplex auto
 speed auto
!
ip nat inside source list 1 interface GigabitEthernet0/1 overload
ip route 0.0.0.0 0.0.0.0 203.0.113.254
!
access-list 1 permit 192.168.1.0 0.0.0.255
!
line con 0
 password 7 0822455D0A16
 login
line aux 0
line vty 0 4
 password 7 0822455D0A16
 login
 transport input ssh
!
end
```

#### Configuration File Locations

```
┌────────────────────────────────────────────────────────────────┐
│              Configuration Storage                             │
├────────────────────────────────────────────────────────────────┤
│                                                                │
│   ┌──────────────────┐        ┌──────────────────┐             │
│   │   NVRAM          │        │      RAM         │             │
│   │ (Non-Volatile)   │        │   (Volatile)     │             │
│   │                  │        │                  │             │
│   │ startup-config   │───────>│ running-config   │             │
│   │                  │  boot  │                  │             │
│   │ Saved config     │        │ Active config    │             │
│   └──────────────────┘        └──────────────────┘             │
│          ▲                           │                         │
│          │     copy running-config   │                         │
│          │     startup-config        │                         │
│          └───────────────────────────┘                         │
└────────────────────────────────────────────────────────────────┘
```

#### Related Commands

```cisco
! View startup configuration
Router# show startup-config

! Compare running and startup configs
Router# show archive config differences

! Save running config to startup
Router# copy running-config startup-config
! Or shorthand:
Router# write memory
```

---

### f) List Two Advantages and Two Disadvantages of Using Dynamic IP Configuration

**Dynamic IP Configuration** uses DHCP (Dynamic Host Configuration Protocol) to automatically assign IP addresses.

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                    DHCP Operation (DORA)                                    │
├─────────────────────────────────────────────────────────────────────────────┤
│                                                                             │
│   Client                                              DHCP Server           │
│   ┌──────┐                                            ┌──────────┐          │
│   │      │────── 1. DISCOVER (Broadcast) ───────────>│          │          │
│   │      │                                            │          │          │
│   │      │<───── 2. OFFER (IP available) ────────────│          │          │
│   │      │                                            │          │          │
│   │      │────── 3. REQUEST (Accept IP) ─────────────│          │          │
│   │      │                                            │          │          │
│   │      │<───── 4. ACK (Confirmed) ─────────────────│          │          │
│   └──────┘                                            └──────────┘          │
│                                                                             │
│   Client now has: IP Address, Subnet Mask, Gateway, DNS                     │
└─────────────────────────────────────────────────────────────────────────────┘
```

#### ✅ Advantages of Dynamic IP Configuration

| # | Advantage | Description |
|---|-----------|-------------|
| 1 | **Automatic IP Management** | No manual configuration needed on each device. DHCP server automatically assigns IPs, reducing administrator workload. |
| 2 | **Prevents IP Conflicts** | DHCP tracks assigned addresses, preventing duplicate IP issues that occur with manual configuration. |
| 3 | **Efficient IP Utilization** | Unused IPs return to pool after lease expires, maximizing address space usage. |
| 4 | **Centralized Management** | All IP settings managed from one server; changes propagate automatically. |
| 5 | **Scalability** | Easily accommodates network growth without reconfiguration of existing devices. |

#### ❌ Disadvantages of Dynamic IP Configuration

| # | Disadvantage | Description |
|---|--------------|-------------|
| 1 | **Dependency on DHCP Server** | If DHCP server fails, new devices cannot join the network. Network operations disrupted. |
| 2 | **Security Concerns** | Rogue DHCP servers can provide incorrect info. Attackers can perform DHCP spoofing attacks. |
| 3 | **IP Address Changes** | Device IPs may change after lease expiration, problematic for servers or devices needing consistent addresses. |
| 4 | **DNS Issues** | Changing IPs complicate DNS records if hostnames need to resolve to specific machines. |
| 5 | **Troubleshooting Complexity** | Harder to track which device has which IP at a given time. |

#### Best Practice

Use **DHCP Reservations** for devices that need static-like behavior:
```cisco
! Reserve IP for specific MAC address
Router(config)# ip dhcp pool STATIC-HOST
Router(dhcp-config)# host 192.168.1.100 255.255.255.0
Router(dhcp-config)# client-identifier 01AA.BBCC.DDEE.FF
```

---

### g) How Do You Verify If an Interface Received an IP Dynamically?

#### Method 1: Show IP Interface Brief

```cisco
Router# show ip interface brief
Interface              IP-Address      OK? Method Status    Protocol
GigabitEthernet0/0     192.168.1.1     YES DHCP   up        up
GigabitEthernet0/1     203.0.113.1     YES manual up        up
```

**Key**: The `Method` column shows:
- `DHCP` - IP obtained dynamically
- `manual` - IP configured statically
- `unset` - No IP assigned

#### Method 2: Show IP Interface (Detailed)

```cisco
Router# show ip interface GigabitEthernet0/0
GigabitEthernet0/0 is up, line protocol is up
  Internet address is 192.168.1.1/24
  Broadcast address is 255.255.255.255
  Address determined by DHCP
  ...
```

#### Method 3: Show DHCP Lease Information

```cisco
Router# show dhcp lease
Temp IP addr: 192.168.1.100  for peer on Interface: GigabitEthernet0/0
Temp  sub net mask: 255.255.255.0
   DHCP Lease server: 192.168.1.1, state: 5 Bound
   DHCP transaction id: 1234
   Lease: 86400 secs,  Renewal: 43200 secs,  Rebind: 75600 secs
Temp default-gateway addr: 192.168.1.1
   Next timer fires after: 11:59:45
   Retry count: 0   Client-ID: cisco-0023.33ab.cd01-Gi0/0
```

#### On Windows (Client Side)

```cmd
C:\> ipconfig /all

Ethernet adapter Local Area Connection:
   Connection-specific DNS Suffix  . : company.local
   Description . . . . . . . . . . . : Intel Ethernet
   Physical Address. . . . . . . . . : 00-1A-2B-3C-4D-5E
   DHCP Enabled. . . . . . . . . . . : Yes        <-- DHCP is enabled
   Autoconfiguration Enabled . . . . : Yes
   IPv4 Address. . . . . . . . . . . : 192.168.1.100
   Subnet Mask . . . . . . . . . . . : 255.255.255.0
   Lease Obtained. . . . . . . . . . : Monday, March 31, 2025 9:00:00 AM
   Lease Expires . . . . . . . . . . : Tuesday, April 1, 2025 9:00:00 AM
   Default Gateway . . . . . . . . . : 192.168.1.1
   DHCP Server . . . . . . . . . . . : 192.168.1.1
```

#### On Linux (Client Side)

```bash
# Check interface configuration
$ ip addr show eth0
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500
    inet 192.168.1.100/24 brd 192.168.1.255 scope global dynamic eth0
       valid_lft 86400sec preferred_lft 86400sec
#                                         ^^^^^^^ "dynamic" indicates DHCP

# Check DHCP client status
$ systemctl status dhclient

# View DHCP lease file
$ cat /var/lib/dhcp/dhclient.leases
```

#### Summary Table

| Command | Platform | What It Shows |
|---------|----------|---------------|
| `show ip interface brief` | Cisco | Method column (DHCP/manual) |
| `show dhcp lease` | Cisco | Detailed DHCP lease info |
| `ipconfig /all` | Windows | DHCP Enabled, Lease info |
| `ip addr show` | Linux | "dynamic" keyword |

---

## Q2: Programming Questions (20 Marks)

### Option A: Static Routing Simulation Program
See file: `Slip_14_Q2_OptionA.c`

### Option B: LAN Chat (Client-Server) Using Sockets
See file: `Slip_14_Q2_OptionB.c`

### Option C: Packet Tracer Configuration

#### Complete Router Configuration for Packet Tracer

```cisco
! ============================================
! Router Configuration - Cisco IOS
! ============================================

! Step 1: Enter privileged mode
Router> enable

! Step 2: Enter global configuration mode
Router# configure terminal

! Step 3: Set hostname
Router(config)# hostname MainRouter

! Step 4: Set enable password (plain text - not recommended)
MainRouter(config)# enable password cisco123

! Step 5: Set enable secret (encrypted - recommended)
MainRouter(config)# enable secret class

! Step 6: Configure Console Line Password
MainRouter(config)# line console 0
MainRouter(config-line)# password console123
MainRouter(config-line)# login
MainRouter(config-line)# logging synchronous
MainRouter(config-line)# exit

! Step 7: Configure VTY (Telnet/SSH) Lines Password
MainRouter(config)# line vty 0 4
MainRouter(config-line)# password vty123
MainRouter(config-line)# login
MainRouter(config-line)# transport input all
MainRouter(config-line)# exit

! Step 8: Encrypt all plain text passwords
MainRouter(config)# service password-encryption

! Step 9: Set MOTD Banner
MainRouter(config)# banner motd #
*******************************************
*     Authorized Access Only!             *
*     Unauthorized access prohibited      *
*******************************************
#

! Step 10: Configure interfaces
MainRouter(config)# interface GigabitEthernet0/0
MainRouter(config-if)# ip address 192.168.1.1 255.255.255.0
MainRouter(config-if)# description LAN Interface
MainRouter(config-if)# no shutdown
MainRouter(config-if)# exit

MainRouter(config)# interface GigabitEthernet0/1
MainRouter(config-if)# ip address 10.0.0.1 255.255.255.0
MainRouter(config-if)# description WAN Interface
MainRouter(config-if)# no shutdown
MainRouter(config-if)# exit

! Step 11: Save configuration
MainRouter(config)# exit
MainRouter# copy running-config startup-config
```

#### Linksys Wireless Router Configuration

```
┌─────────────────────────────────────────────────────────────────┐
│           Linksys Wireless Router Configuration                 │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  1. Access the Router:                                          │
│     • Open browser, go to: http://192.168.0.1                   │
│     • Default credentials: admin/admin                          │
│                                                                 │
│  2. Basic Settings Tab:                                         │
│     ┌─────────────────────────────────────────────────────┐     │
│     │ Internet Connection Type: [Automatic - DHCP]        │     │
│     │ Router IP: 192.168.0.1                              │     │
│     │ Subnet Mask: 255.255.255.0                          │     │
│     │ DHCP Server: [Enabled]                              │     │
│     │ Start IP: 192.168.0.100                             │     │
│     │ Maximum Users: 50                                   │     │
│     └─────────────────────────────────────────────────────┘     │
│                                                                 │
│  3. Wireless Settings Tab:                                      │
│     ┌─────────────────────────────────────────────────────┐     │
│     │ Network Mode: [Mixed]                               │     │
│     │ SSID: MySecureNetwork                               │     │
│     │ Radio Band: [Auto]                                  │     │
│     │ Wide Channel: [Auto]                                │     │
│     │ Standard Channel: [Auto]                            │     │
│     │ SSID Broadcast: [Enabled]                           │     │
│     └─────────────────────────────────────────────────────┘     │
│                                                                 │
│  4. Wireless Security Tab:                                      │
│     ┌─────────────────────────────────────────────────────┐     │
│     │ Security Mode: [WPA2 Personal]                      │     │
│     │ Encryption: [AES]                                   │     │
│     │ Passphrase: MyStr0ngP@ssw0rd                        │     │
│     └─────────────────────────────────────────────────────┘     │
│                                                                 │
│  5. Administration Tab:                                         │
│     ┌─────────────────────────────────────────────────────┐     │
│     │ Router Password: NewAdminPass123                    │     │
│     │ Re-enter Password: NewAdminPass123                  │     │
│     │ Web Access: [HTTP and HTTPS]                        │     │
│     │ Remote Management: [Disabled]                       │     │
│     └─────────────────────────────────────────────────────┘     │
│                                                                 │
│  6. Click [Save Settings] after each change                     │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

#### In Packet Tracer (GUI Steps)

1. **Add Linksys Router**: 
   - Drag "Linksys-WRT300N" from Network Devices > Wireless Devices

2. **Access GUI**:
   - Click on the router → GUI tab

3. **Configure SSID**:
   - Setup Tab → Basic Setup
   - Change SSID under "Wireless" section
   - Set to: `CompanyWiFi`

4. **Configure Security**:
   - Wireless → Wireless Security
   - Security Mode: WPA2 Personal
   - Passphrase: `SecureP@ss123`

5. **Save Settings**: Click "Save Settings" button

---

## Summary

| Question | Topic | Key Commands/Concepts |
|----------|-------|----------------------|
| a | PAT Configuration | `ip nat inside source list 1 interface overload` |
| b | Routing Verification | `ping`, `traceroute`, `show ip route` |
| c | Enable Password | `enable secret class` |
| d | Show Running Config | `show running-config` |
| f | Dynamic IP Pros/Cons | DHCP advantages and disadvantages |
| g | Verify Dynamic IP | `show ip interface brief`, Method column |

---

*End of Slip 14 Solutions*
