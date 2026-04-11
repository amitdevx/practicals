# Slip 4 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) Calculate the bandwidth required to transmit data.

**Bandwidth** is the maximum data transfer rate of a network or link, measured in bits per second (bps).

**Bandwidth Calculation Formula:**
```
Bandwidth (bps) = (File Size in bytes × 8 bits/byte) / Time in seconds
```

**Example Calculation:**
- File size: 100 MB = 104,857,600 bytes
- In bits: 104,857,600 × 8 = 838,860,800 bits
- Transmission time: 10 seconds
- Required bandwidth = 838,860,800 / 10 = **83.886 Mbps**

**Common Bandwidth Units:**
- **bps** (bits per second): Basic unit
- **Kbps** (kilobits per second): 1,000 bps
- **Mbps** (megabits per second): 1,000,000 bps
- **Gbps** (gigabits per second): 1,000,000,000 bps

**Typical Bandwidth Requirements:**
- Voice calls: 64-128 Kbps
- Video streaming: 5-25 Mbps
- Web browsing: 1-5 Mbps
- Large file transfer: Calculate from file size and time

**Bandwidth Planning Considerations:**
- Account for peak usage periods
- Plan for future network growth
- Consider overhead and protocol headers
- Include redundancy for reliability

---

### b) What is classful addressing? Write the class ranges.

**Classful Addressing** divides the IPv4 address space into predefined classes. Each class has a fixed network and host portion based on the leading bits.

**IPv4 Address Classes:**

| Class | Range | First Bits | Network Bits | Hosts/Network | Subnet Mask |
|-------|-------|-----------|--------------|---------------|-------------|
| **A** | 1-126 | 0 | 8 | 16,777,214 | 255.0.0.0 |
| **B** | 128-191 | 10 | 16 | 65,534 | 255.255.0.0 |
| **C** | 192-223 | 110 | 24 | 254 | 255.255.255.0 |
| **D** | 224-239 | 1110 | N/A | Multicast | N/A |
| **E** | 240-255 | 1111 | N/A | Reserved | N/A |

**Detailed Class Information:**

**Class A (1.0.0.0 - 126.255.255.255)**
- First bit: 0
- Network: 1-126 (126 networks)
- Hosts per network: 16,777,214
- Subnet mask: 255.0.0.0 (/8)
- Usage: Large enterprises, ISPs

**Class B (128.0.0.0 - 191.255.255.255)**
- First 2 bits: 10
- Networks: 16,384
- Hosts per network: 65,534
- Subnet mask: 255.255.0.0 (/16)
- Usage: Medium enterprises, universities

**Class C (192.0.0.0 - 223.255.255.255)**
- First 3 bits: 110
- Networks: 2,097,152
- Hosts per network: 254
- Subnet mask: 255.255.255.0 (/24)
- Usage: Small networks, ISP customers

**Class D & E:** Not for regular use (multicast and reserved)

**Disadvantages of Classful Addressing:**
- Inefficient use of address space (wasteful)
- Only 3 usable classes
- No flexibility in network size
- Led to rapid IPv4 depletion
- Solution: Classless addressing (CIDR) with subnetting

---

### c) What are private IP ranges?

**Private IP Addresses** are reserved for use within private networks and cannot be routed on the public Internet. Defined in RFC 1918.

**RFC 1918 Private IP Ranges:**

| Class | Start | End | CIDR | Use Case |
|-------|-------|-----|------|----------|
| **A** | 10.0.0.0 | 10.255.255.255 | 10.0.0.0/8 | Large enterprises |
| **B** | 172.16.0.0 | 172.31.255.255 | 172.16.0.0/12 | Medium networks |
| **C** | 192.168.0.0 | 192.168.255.255 | 192.168.0.0/16 | Home/small office |

**Other Special-Use Addresses:**
- **127.0.0.0/8**: Loopback (127.0.0.1 = localhost)
- **169.254.0.0/16**: Link-local addresses (APIPA)
- **224.0.0.0/4**: Multicast
- **240.0.0.0/4**: Reserved for future use
- **255.255.255.255**: Broadcast

**Key Characteristics:**
- Never visible on public Internet routers
- Can be reused in different networks
- No global routing - ISP routers ignore them
- Require NAT to access Internet
- Unlimited reusability across organizations

**Common Network Setups:**
- **Home routers**: Usually 192.168.1.0/24 or 192.168.0.0/24
- **Corporate**: Often 10.0.0.0/8 for large scale
- **ISPs**: 172.16.0.0/12 for management networks

---

### d) How to use the Tracert command to trace the route to a destination host?

**Tracert/Traceroute** shows the complete network path from your computer to a destination, including all intermediate routers (hops) and response times.

**Command Syntax:**
```bash
tracert destination_IP_or_hostname        # Windows
traceroute destination_IP_or_hostname     # Linux/Mac
trace destination_IP_or_hostname          # macOS alternative
```

**Windows Examples:**
```cmd
tracert google.com
tracert 8.8.8.8
tracert -h 15 google.com                  # Limit to 15 hops
tracert -w 2000 8.8.8.8                   # Wait 2 seconds per hop
```

**Linux/Mac Examples:**
```bash
traceroute google.com
traceroute -m 15 8.8.8.8                  # Max 15 hops
traceroute -w 2 8.8.8.8                   # Wait 2 seconds
```

**Sample Output:**
```
Tracing route to google.com [142.250.185.46] over 30 hops

1     <1 ms    <1 ms    <1 ms    192.168.1.1 (home gateway)
2     15 ms    14 ms    15 ms    isp-router.com
3     25 ms    24 ms    25 ms    transit.com
4     30 ms    29 ms    31 ms    google-peer.net
5     32 ms    31 ms    33 ms    142.250.185.46 (google.com)
```

**Output Columns:**
- **Hop #**: Sequential router number
- **Times (3 values)**: Round-trip time for 3 probes to that hop
- **Router name/IP**: Address of the router at that hop
- **ms**: Milliseconds (lower = better)

**Special Output Values:**
- **Asterisk (*)**: Router didn't respond (may be intentional)
- **Request timed out**: No response within timeout period
- **Destination host unreachable**: Host exists but unreachable

**Common Uses:**
- Troubleshooting network connectivity issues
- Identifying where connection breaks
- Detecting slow links or routers
- Understanding network topology
- Finding routing problems

---

### f) What is a default route? Why is it needed?

**Default Route** is the route used when no other route matches a destination IP address. It's the catch-all for unspecified destinations.

**Characteristics:**
- **Destination**: 0.0.0.0/0 (any destination)
- **Used when**: No specific route exists for destination
- **Next hop**: Default gateway (usually ISP router)
- **Essential for**: Internet connectivity

**How Default Routing Works:**
```
1. Router checks routing table for destination
2. If specific route found → use that route
3. If no match → use default route (0.0.0.0/0)
4. Send packet to default gateway
```

**Setting Default Route:**

Cisco IOS:
```cisco
Router# ip route 0.0.0.0 0.0.0.0 192.168.1.1
```

Linux:
```bash
route add default gw 192.168.1.1
ip route add 0.0.0.0/0 via 192.168.1.1
```

Windows:
```cmd
route add 0.0.0.0 MASK 0.0.0.0 192.168.1.1
```

**Importance:**
- Enables Internet access without knowing all routes
- Simplifies routing tables (no need for thousands of entries)
- Standard practice in all networks
- Works with both IPv4 and IPv6

**IPv6 Default Route:**
```
::/0 (equivalent to 0.0.0.0/0 in IPv6)
```

---

### g) What is ICMP? Why is it needed? Write the ping reply types.

**ICMP** (Internet Control Message Protocol) is a network layer protocol used for error reporting, diagnostics, and network management.

**Why ICMP is Needed:**
1. **Error Reporting**: Inform sender of delivery problems
2. **Network Diagnostics**: Test connectivity and performance
3. **Path Analysis**: Trace route to destination
4. **Network Troubleshooting**: Identify network issues
5. **Host Discovery**: Determine if hosts are reachable

**ICMP Message Types:**

| Type | Code | Name | Purpose |
|------|------|------|---------|
| 0 | 0 | Echo Reply | Response to ping |
| 3 | 0-15 | Destination Unreachable | Cannot reach destination |
| 4 | 0 | Source Quench | Reduce transmission rate |
| 5 | 0-3 | Redirect | Use better route |
| 8 | 0 | Echo Request | Ping request |
| 11 | 0-1 | Time Exceeded | TTL expired |
| 12 | 0-2 | Parameter Problem | Invalid parameters |
| 13 | 0 | Timestamp Request | Request time sync |
| 14 | 0 | Timestamp Reply | Time sync response |

**Ping Reply (Echo Reply = Type 0):**
- Sent in response to Echo Request (ping)
- Contains echoed data from ping request
- Includes TTL/Hop Limit value
- Sequence number matches request
- Timestamp information

**Example Ping Output:**
```
Reply from 8.8.8.8: bytes=32 time=20ms TTL=119
64 bytes from 8.8.8.8: icmp_seq=1 ttl=119 time=20.1 ms
```

**Destination Unreachable (Type 3) Codes:**
- Network unreachable
- Host unreachable
- Protocol unreachable
- Port unreachable
- Fragmentation needed (Don't Fragment bit set)

**Time Exceeded (Type 11) Codes:**
- TTL exceeded in transit
- Fragment reassembly time exceeded

---

## Q2: Practical Questions (20 Marks)

### OPTION A: Display Ring Topology

Ring topology connects all devices in a circular loop with unidirectional data flow.

**Characteristics:**
- Each node connected to exactly 2 other nodes (predecessor and successor)
- Data flows in one direction around the ring
- Each node receives and forwards messages
- One break in ring breaks entire network
- Fair media access using token-passing protocol

**Advantages:**
- Fair access (all nodes get equal opportunity)
- No collisions in token ring
- Predictable performance
- Suitable for deterministic networks

**Disadvantages:**
- One node failure breaks network
- Complex to add/remove nodes
- Troubleshooting difficult
- Higher latency than bus

---

### OPTION B: Odd Parity Error Detection

Odd parity adds a parity bit to make the total number of 1s odd.

**Algorithm:**
- Count 1s in data
- If count is even, set parity bit = 1
- If count is odd, set parity bit = 0
- Receiver checks if total 1s is odd

---

