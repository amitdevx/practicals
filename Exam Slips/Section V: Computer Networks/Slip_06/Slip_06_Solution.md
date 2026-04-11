# Slip 6 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) What is the difference between IPv6 and IPv4?

**IPv4 vs IPv6 Comparison:**

| Feature | IPv4 | IPv6 |
|---------|------|------|
| **Address Size** | 32 bits | 128 bits |
| **Address Format** | Dotted decimal (X.X.X.X) | Hexadecimal (X:X:X:X:X:X:X:X) |
| **Total Addresses** | 4.3 billion (2^32) | 340 undecillion (2^128) |
| **Header Size** | 20-60 bytes | 40 bytes (fixed) |
| **Address Classes** | Classful/Classless | Only classless (CIDR) |
| **Example** | 192.168.1.1 | 2001:0db8:85a3:0000:0000:8a2e:0370:7334 |
| **Loopback** | 127.0.0.1 | ::1 |
| **Broadcast** | Yes (255.255.255.255) | No (uses multicast) |
| **Fragmentation** | By routers and hosts | By hosts only |
| **Security** | Optional (IPsec) | Built-in (IPsec) |

---

### b) How to configure a network interface in Linux?

**Temporary Configuration (Lost on reboot):**
```bash
# Assign IP address
sudo ip addr add 192.168.1.10/24 dev eth0

# Set gateway
sudo ip route add default via 192.168.1.1

# Bring interface up
sudo ip link set eth0 up

# View configuration
ip addr show eth0
```

**Permanent Configuration (Netplan - Ubuntu 18.04+):**

Edit `/etc/netplan/01-netcfg.yaml`:
```yaml
network:
  version: 2
  ethernets:
    eth0:
      dhcp4: no
      addresses:
        - 192.168.1.10/24
      gateway4: 192.168.1.1
      nameservers:
        addresses: [8.8.8.8, 8.8.4.4]
```

Apply:
```bash
sudo netplan apply
```

---

### c) What is a netmask and what is its purpose?

**Netmask (Subnet Mask):**
- Determines which part of IP is network and which is host
- Uses binary 1s for network bits, 0s for host bits
- Written in dotted decimal: 255.255.255.0
- Or in CIDR: /24 (24 network bits)

**Example:**
```
IP: 192.168.1.100
Netmask: 255.255.255.0
Network: 192.168.1.0
Host ID: .100
Broadcast: 192.168.1.255
```

**Common Netmasks:**
- /8 (255.0.0.0): 16 million hosts
- /16 (255.255.0.0): 65,000 hosts
- /24 (255.255.255.0): 254 hosts
- /32 (255.255.255.255): Single host

---

### d) What is Nmap? How to use it for network scanning?

**Nmap (Network Mapper):** Tool for network discovery and port scanning.

**Installation:**
```bash
sudo apt install nmap
```

**Basic Usage:**
```bash
# Scan single host
nmap 192.168.1.1

# Scan network range
nmap 192.168.1.0/24

# Scan specific ports
nmap -p 22,80,443 192.168.1.1

# Scan all ports
nmap -p- 192.168.1.1

# OS detection
sudo nmap -O 192.168.1.1

# Service version detection
nmap -sV 192.168.1.1

# Aggressive scan
sudo nmap -A 192.168.1.1
```

**Output Example:**
```
22/tcp   open   ssh
80/tcp   open   http
443/tcp  open   https
3306/tcp closed mysql
```

---

### f) What is a Hosts file? How to edit it?

**Hosts File:** Maps hostnames to IP addresses locally (before DNS lookup).

**Location:**
- Linux/Mac: `/etc/hosts`
- Windows: `C:\Windows\System32\drivers\etc\hosts`

**Format:**
```
IP_address    hostname    [alias]
127.0.0.1     localhost
192.168.1.1   router.local
10.0.0.1      server.local
```

**Edit Linux/Mac:**
```bash
sudo nano /etc/hosts
```

**Edit Windows:**
- Open Notepad as Administrator
- File → Open
- Navigate to `C:\Windows\System32\drivers\etc`
- Open `hosts` file
- Edit and save

**Example Uses:**
- Block websites locally
- Map IPs to human-readable names
- Test before DNS propagation

---

### g) What is IPS and IDS? How do they differ?

**IDS (Intrusion Detection System):**
- Monitors for threats
- Detects attacks and anomalies
- Logs and alerts
- **Passive** - doesn't block, only monitors

**IPS (Intrusion Prevention System):**
- Monitors and prevents threats
- Detects and blocks attacks
- **Active** - can stop malicious traffic

**Difference:**

| Feature | IDS | IPS |
|---------|-----|-----|
| **Action** | Detect only | Detect & Block |
| **Type** | Passive | Active |
| **Response** | Log/Alert | Block/Drop |
| **False Positives** | Less critical | May drop legitimate traffic |
| **Performance** | Better | Slower (inline) |

---

## Q2: Practical Questions (20 Marks)

### OPTION A: Hybrid Topology

Hybrid topology combines multiple topology types for flexibility and reliability.

**Characteristics:**
- Mix of bus, star, ring, or mesh
- Advantages of multiple topologies
- Flexible design
- Complex implementation

---

### OPTION B: Protocol Comparison

Compare network protocols based on reliability, speed, connection type, and use cases.

---

