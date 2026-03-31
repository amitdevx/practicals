# Slip 10 — Computer Networks Solution Guide

## Q1: Theory Questions (Answer ANY 5) — 10 Marks

---

### a) Differences Between Cat5e, Cat6, and Cat7 Ethernet Cables

| Feature | Cat5e | Cat6 | Cat7 |
|---------|-------|------|------|
| **Maximum Speed** | 1 Gbps | 10 Gbps | 10 Gbps |
| **Bandwidth** | 100 MHz | 250 MHz | 600 MHz |
| **Max Distance (at max speed)** | 100m | 55m (10G), 100m (1G) | 100m |
| **Shielding** | UTP (Unshielded) | UTP or STP | STP/SFTP (Fully Shielded) |
| **Crosstalk Protection** | Basic | Better (separator spline) | Excellent (individual shielding) |
| **Connector** | RJ-45 | RJ-45 | GG45 / TERA |
| **Cost** | Low | Medium | High |
| **Use Case** | Home networks | Office/Enterprise | Data centers, high EMI areas |

#### Key Points:
- **Cat5e**: Enhanced Category 5, suitable for gigabit Ethernet in homes
- **Cat6**: Tighter twists, better crosstalk handling, ideal for 10GbE short runs
- **Cat7**: Individual pair shielding, backwards compatible, industrial use

---

### b) Purpose of a Modem in a Network

#### What is a Modem?
**MOdulator-DEModulator** — converts digital signals to analog and vice versa.

#### Primary Functions:
1. **Signal Conversion**: Digital (computer) ↔ Analog (telephone/cable line)
2. **Protocol Translation**: Converts data between ISP protocols and Ethernet
3. **Line Interface**: Terminates the ISP connection at customer premises

#### Can We Connect Directly to Internet Without a Modem?

| Scenario | Possible? | Explanation |
|----------|-----------|-------------|
| **DSL/Cable Internet** | ❌ No | Signal modulation required |
| **Fiber (FTTH)** | ⚠️ Partial | ONT (Optical Network Terminal) needed, some call it "fiber modem" |
| **Direct Ethernet from ISP** | ✅ Yes | Some ISPs provide direct Ethernet handoff |
| **Mobile Internet (4G/5G)** | ⚠️ Partial | Modem built into mobile device/dongle |

#### Diagram:
```
Internet ─── ISP ─── [Analog Signal] ─── MODEM ─── [Digital Signal] ─── Router ─── PC
                      (Coax/Phone)                    (Ethernet)
```

---

### c) Command to Assign a Static IP in Linux

#### Method 1: Using `ip` command (Temporary)
```bash
# Assign IP address
sudo ip addr add 192.168.1.100/24 dev eth0

# Set default gateway
sudo ip route add default via 192.168.1.1

# Verify
ip addr show eth0
```

#### Method 2: Using `ifconfig` (Legacy)
```bash
sudo ifconfig eth0 192.168.1.100 netmask 255.255.255.0 up
sudo route add default gw 192.168.1.1
```

#### Method 3: Permanent Configuration (Netplan - Ubuntu 18.04+)
File: `/etc/netplan/01-netcfg.yaml`
```yaml
network:
  version: 2
  ethernets:
    eth0:
      addresses:
        - 192.168.1.100/24
      gateway4: 192.168.1.1
      nameservers:
        addresses: [8.8.8.8, 8.8.4.4]
```
Apply: `sudo netplan apply`

#### Method 4: Permanent Configuration (Traditional - `/etc/network/interfaces`)
```
auto eth0
iface eth0 inet static
    address 192.168.1.100
    netmask 255.255.255.0
    gateway 192.168.1.1
    dns-nameservers 8.8.8.8
```
Apply: `sudo systemctl restart networking`

#### Method 5: Using `nmcli` (NetworkManager)
```bash
sudo nmcli con mod "Wired connection 1" ipv4.addresses 192.168.1.100/24
sudo nmcli con mod "Wired connection 1" ipv4.gateway 192.168.1.1
sudo nmcli con mod "Wired connection 1" ipv4.dns "8.8.8.8"
sudo nmcli con mod "Wired connection 1" ipv4.method manual
sudo nmcli con up "Wired connection 1"
```

---

### d) Use of the Ping Command in Networking

#### What is Ping?
**Ping** uses ICMP (Internet Control Message Protocol) Echo Request/Reply to test network connectivity.

#### Primary Uses:

| Use Case | Description |
|----------|-------------|
| **Connectivity Test** | Check if a host is reachable |
| **Latency Measurement** | Measure round-trip time (RTT) |
| **Packet Loss Detection** | Identify network reliability issues |
| **DNS Resolution Test** | Verify hostname to IP resolution |
| **Network Troubleshooting** | Isolate where connectivity fails |
| **MTU Discovery** | Test maximum packet size |

#### Syntax and Examples:
```bash
# Basic ping
ping google.com

# Ping with count limit
ping -c 4 192.168.1.1

# Ping with specific packet size
ping -s 1000 192.168.1.1

# Continuous ping (Linux)
ping -i 0.5 192.168.1.1    # 0.5 second interval

# Ping with timeout
ping -W 2 192.168.1.1      # 2 second timeout
```

#### Sample Output Analysis:
```
PING google.com (142.250.193.46) 56(84) bytes of data.
64 bytes from del11s14-in-f14.1e100.net: icmp_seq=1 ttl=117 time=12.3 ms
64 bytes from del11s14-in-f14.1e100.net: icmp_seq=2 ttl=117 time=11.8 ms

--- google.com ping statistics ---
2 packets transmitted, 2 received, 0% packet loss, time 1001ms
rtt min/avg/max/mdev = 11.800/12.050/12.300/0.250 ms
```

| Field | Meaning |
|-------|---------|
| `icmp_seq` | Sequence number of packet |
| `ttl` | Time To Live (hops remaining) |
| `time` | Round-trip time in milliseconds |
| `packet loss` | Percentage of lost packets |
| `rtt` | Round-trip time statistics |

---

### f) Static NAT vs Dynamic NAT vs PAT (Port Address Translation)

#### Overview Table:

| Feature | Static NAT | Dynamic NAT | PAT (NAT Overload) |
|---------|------------|-------------|-------------------|
| **Mapping** | 1:1 (Fixed) | 1:1 (From Pool) | Many:1 |
| **Public IPs Needed** | One per host | Pool of IPs | Single IP |
| **IP Assignment** | Permanent | Temporary | Shared |
| **Uniqueness** | IP address | IP address | IP + Port |
| **Use Case** | Servers (Web, Mail) | Medium networks | Home/Small office |
| **Bidirectional** | Yes | No (outbound only) | No (outbound only) |

#### Detailed Comparison:

##### Static NAT (One-to-One)
```
Private IP          Public IP
192.168.1.10  <-->  203.0.113.10  (Permanent mapping)
192.168.1.20  <-->  203.0.113.20  (Permanent mapping)
```
- **Use**: Web servers, mail servers needing consistent public IP
- **Advantage**: Allows inbound connections
- **Disadvantage**: Requires one public IP per private host

##### Dynamic NAT (Pool-Based)
```
Private IP          Public IP Pool
192.168.1.10  --->  203.0.113.10  (Temporary)
192.168.1.20  --->  203.0.113.11  (Temporary)
192.168.1.30  --->  [Waiting - pool exhausted]
```
- **Use**: When public IPs < private hosts, but need unique public IPs
- **Advantage**: Efficient IP utilization
- **Disadvantage**: Connection fails if pool exhausted

##### PAT / NAT Overload (Port-Based)
```
Private IP:Port         Public IP:Port
192.168.1.10:5001  -->  203.0.113.1:40001
192.168.1.20:5002  -->  203.0.113.1:40002
192.168.1.30:5003  -->  203.0.113.1:40003
```
- **Use**: Home networks, small offices
- **Advantage**: Single public IP supports thousands of hosts
- **Disadvantage**: No inbound connections without port forwarding

#### Diagram:
```
Static NAT:      [PC1: 10.0.0.1] ─────────── [203.0.113.1] ─── Internet
                                   1:1 Fixed

Dynamic NAT:     [PC1: 10.0.0.1] ─┐
                 [PC2: 10.0.0.2] ─┼── Pool ── [203.0.113.1-5] ── Internet
                 [PC3: 10.0.0.3] ─┘   1:1 Temp

PAT:             [PC1: 10.0.0.1] ─┐
                 [PC2: 10.0.0.2] ─┼── [203.0.113.1:port] ──── Internet
                 [PC3: 10.0.0.3] ─┘    Many:1 with ports
```

---

### g) Configure Static NAT on Cisco Router

#### Network Topology:
```
[PC1: 192.168.1.10] ── [R1] ── [Internet]
   Private Network    G0/0   G0/1   Public IP: 203.0.113.10
   192.168.1.0/24            Public: 203.0.113.0/24
```

#### Cisco IOS Commands:

```cisco
! Enter global configuration mode
Router> enable
Router# configure terminal

! Configure inside interface (private network)
Router(config)# interface GigabitEthernet0/0
Router(config-if)# ip address 192.168.1.1 255.255.255.0
Router(config-if)# ip nat inside
Router(config-if)# no shutdown
Router(config-if)# exit

! Configure outside interface (public network)
Router(config)# interface GigabitEthernet0/1
Router(config-if)# ip address 203.0.113.1 255.255.255.0
Router(config-if)# ip nat outside
Router(config-if)# no shutdown
Router(config-if)# exit

! Configure Static NAT mapping
! Maps private 192.168.1.10 to public 203.0.113.10
Router(config)# ip nat inside source static 192.168.1.10 203.0.113.10

! Save configuration
Router(config)# exit
Router# write memory
```

#### Verification Commands:
```cisco
! Show NAT translations
Router# show ip nat translations
Pro Inside global      Inside local       Outside local      Outside global
--- 203.0.113.10       192.168.1.10       ---                ---

! Show NAT statistics
Router# show ip nat statistics

! Debug NAT (for troubleshooting)
Router# debug ip nat
```

#### Packet Tracer Steps:
1. Create topology: PC → Switch → Router → Cloud/Server
2. Configure PC with IP 192.168.1.10/24, Gateway 192.168.1.1
3. Apply above router commands
4. Test with ping from PC to external server
5. Verify with `show ip nat translations`

---

## Q2: Programming Questions — 20 Marks

### Option A: Even Parity Error Detection
See: `Slip_10_Q2_OptionA.c`

### Option B: Subnetting and Supernetting Calculator
See: `Slip_10_Q2_OptionB.c`

### Option C: Packet Tracer Configuration

#### Network Requirements:
- Subnet: 192.168.10.0/25
- PC1: 192.168.10.1
- PC2: 192.168.10.2
- Subnet Mask: 255.255.255.0

#### Step-by-Step Configuration:

##### 1. Create Topology
```
[PC0] ────┐
          ├──── [Switch0]
[PC1] ────┘
```

##### 2. Configure PC0
```
IP Address: 192.168.10.1
Subnet Mask: 255.255.255.0
Default Gateway: 192.168.10.254 (optional)
```

##### 3. Configure PC1
```
IP Address: 192.168.10.2
Subnet Mask: 255.255.255.0
Default Gateway: 192.168.10.254 (optional)
```

##### 4. Test Connectivity
From PC0: `ping 192.168.10.2`
From PC1: `ping 192.168.10.1`

##### 5. Subnet Analysis for /25

| Property | Value |
|----------|-------|
| Network Address | 192.168.10.0 |
| Subnet Mask | 255.255.255.128 (/25) |
| Usable Host Range | 192.168.10.1 - 192.168.10.126 |
| Broadcast Address | 192.168.10.127 |
| Total Hosts | 126 |

**Note**: The question mentions /25 subnet but uses /24 mask (255.255.255.0). Both PCs would work in either case since 192.168.10.1 and 192.168.10.2 fall within both subnets.

---

## Quick Reference

### ICMP Message Types
| Type | Name |
|------|------|
| 0 | Echo Reply |
| 3 | Destination Unreachable |
| 8 | Echo Request |
| 11 | Time Exceeded |

### NAT Command Summary (Cisco)
| Command | Purpose |
|---------|---------|
| `ip nat inside` | Mark interface as inside |
| `ip nat outside` | Mark interface as outside |
| `ip nat inside source static` | Static NAT mapping |
| `ip nat inside source list` | Dynamic/PAT NAT |
| `show ip nat translations` | View NAT table |

### Network Troubleshooting Order
1. `ping 127.0.0.1` — Test TCP/IP stack
2. `ping <local IP>` — Test NIC
3. `ping <gateway>` — Test local network
4. `ping <remote IP>` — Test routing
5. `ping <hostname>` — Test DNS

---

## Compilation & Execution

```bash
# Option A: Even Parity
gcc -o parity Slip_10_Q2_OptionA.c
./parity

# Option B: Subnetting Calculator
gcc -o subnet Slip_10_Q2_OptionB.c -lm
./subnet
```
