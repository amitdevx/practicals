# Slip 2 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) What is the functional difference between a switch and a router?

A **switch** operates at Layer 2 (Data Link) and forwards frames based on MAC addresses within a local network. A **router** operates at Layer 3 (Network) and forwards packets based on IP addresses across different networks.

**Key Differences:**

| Feature | Switch | Router |
|---------|--------|--------|
| **Layer** | Data Link (L2) | Network (L3) |
| **Uses** | MAC addresses | IP addresses |
| **Range** | Local network | Multiple networks |
| **Forwards** | Frames | Packets |
| **Function** | Local connectivity | Inter-network connectivity |
| **Speed** | Very fast | Slower (routing decision) |

Switches are used for local connectivity within a network; routers connect different networks together (e.g., LAN to Internet, WAN connections).

---

### b) How many hosts are possible in a /26 subnet?

With a /26 subnet, there are **32 - 26 = 6 host bits**.

**Calculation:**
- Total addresses per subnet = 2^6 = **64**
- Usable hosts = 64 - 2 = **62**
  - (Minus 1 for network address and 1 for broadcast address)

**Subnet Mask:** 255.255.255.192

**Example /26 Subnets:**
- Subnet 1: 192.168.1.0/26 → Network: 192.168.1.0, Hosts: 192.168.1.1 to 192.168.1.62, Broadcast: 192.168.1.63
- Subnet 2: 192.168.1.64/26 → Network: 192.168.1.64, Hosts: 192.168.1.65 to 192.168.1.126, Broadcast: 192.168.1.127

---

### c) What are the differences between Cat5e, Cat6, and Cat7 Ethernet cables?

| Feature | Cat5e | Cat6 | Cat7 |
|---------|-------|------|------|
| **Speed** | 100 Mbps - 1 Gbps | 10 Gbps | 40 Gbps |
| **Frequency** | 100 MHz | 250 MHz | 600 MHz |
| **Distance (full speed)** | 100m (1 Gbps limited) | 55m @ 10 Gbps; 100m @ 1 Gbps | 100m @ 40 Gbps |
| **Shielding** | Unshielded (UTP) | Unshielded or shielded (STP) | Fully shielded (STP) |
| **Cost** | Lowest | Medium | Highest |
| **Crosstalk** | More susceptible | Better protected | Minimal |
| **Common Use** | Home, small office | Data centers, offices | Enterprise, data centers |

**Recommendation:**
- Home/Office: Cat6 (good for future-proofing, supports Gigabit+)
- Data Center: Cat7 (high bandwidth needs, future-proof)
- Budget Option: Cat5e (still acceptable for basic gigabit use)

---

### d) Write the steps to identify a phishing email.

**Steps to identify phishing emails:**

1. **Check Sender Address**
   - Look for subtle misspellings (e.g., "amaz0n.com" instead of "amazon.com")
   - Verify it matches known legitimate email patterns
   - Check sender's domain, not just display name

2. **Verify Links (Don't Click!)**
   - Hover over links to see actual URL without clicking
   - Check if URL matches sender's claim
   - Look for HTTPS and lock icon in address bar

3. **Check Greeting**
   - Generic "Dear Customer" instead of your name
   - Legitimate companies use personalized greetings
   - Vague or impersonal salutations are warning signs

4. **Look for Urgency**
   - "Act now" or "Your account will be closed"
   - Time pressure ("24 hours to respond")
   - Threats or scare tactics

5. **Verify Requests**
   - Legitimate banks never request passwords via email
   - No requests for SSN, credit card, or financial info
   - Never ask for sensitive data via email

6. **Check Attachments**
   - Unexpected attachments (especially .exe, .zip, .jar)
   - Verify sender before opening any attachment
   - Be suspicious of macro-enabled documents

7. **Grammar & Formatting**
   - Poor spelling or awkward phrasing
   - Inconsistent formatting or fonts
   - Misaligned images or broken layouts

8. **Use Email Authentication**
   - SPF (Sender Policy Framework) validation
   - DKIM (DomainKeys Identified Mail) verification
   - DMARC (Domain-based Message Authentication) checks

**Best Practice:** When in doubt, contact the organization directly using official phone/website (not by clicking email links).

---

### f) What are the two analysis methods used for analyzing malware?

**1. Static Analysis**
- **What**: Examine malware code without running it
- **Method**: Disassemble/decompile executable, analyze strings, imports, and headers
- **Tools**: IDA Pro, Ghidra, Radare2, Strings utility
- **Advantages**: Very safe, can see exact code, understand logic flow, no sandboxing needed
- **Disadvantages**: Code obfuscation, encryption, code polymorphism, requires reverse engineering skills

**2. Dynamic Analysis**
- **What**: Run malware in controlled, isolated environment (sandbox)
- **Method**: Execute in isolated VM, monitor system calls, file access, network traffic, registry changes
- **Tools**: Wireshark, Process Monitor, Cuckoo Sandbox, IDA Pro Debugger
- **Advantages**: See actual behavior, understand how malware spreads/persists, detect exploitation techniques
- **Disadvantages**: Risky (requires isolation), malware may detect sandbox and behave differently, time-consuming

**Comparison:**

| Aspect | Static | Dynamic |
|--------|--------|---------|
| **Safety** | Very safe | Risky (needs isolation) |
| **Time** | Faster | Slower |
| **Shows** | Code structure, logic | Runtime behavior, exploitation |
| **Detects** | Algorithm structure | Propagation, persistence, C&C communication |
| **Tools** | Disassemblers, decompilers | Debuggers, network analyzers |

**Combined Approach:** Security professionals use both methods - static for understanding code logic, dynamic for seeing actual runtime behavior and impact.

---

### g) What is the use of the ping command in networking?

**Ping** (Packet Internet Groper) is a utility for testing connectivity between two devices on an IP network.

**How it works:**
1. Sends ICMP Echo Request packets to target host
2. Target responds with ICMP Echo Reply
3. Measures round-trip time for packet to travel

**Primary Uses:**
1. **Test Connectivity**: Verify if a host is reachable on the network
2. **Measure Latency**: See round-trip time (response time) in milliseconds
3. **Diagnose Network Issues**: Check network path and responsiveness
4. **Verify DNS Resolution**: Test hostname-to-IP address resolution
5. **Network Troubleshooting**: Identify network problems quickly

**Syntax:**
```bash
ping hostname_or_IP
ping -c count hostname_or_IP    # Linux/Mac - limit packets
ping -n count hostname_or_IP    # Windows - limit packets
```

**Sample Output:**
```
PING 8.8.8.8 (8.8.8.8) 56(84) bytes of data.
64 bytes from 8.8.8.8: icmp_seq=1 ttl=119 time=20.1 ms
64 bytes from 8.8.8.8: icmp_seq=2 ttl=119 time=19.8 ms
64 bytes from 8.8.8.8: icmp_seq=3 ttl=119 time=20.5 ms

--- 8.8.8.8 statistics ---
3 packets transmitted, 3 received, 0% packet loss, time 2003ms
rtt min/avg/max/stddev = 19.8/20.1/20.5/0.3 ms
```

**Parameters Explained:**
- **TTL (Time To Live)**: Hop count remaining (decreases at each router)
- **Time**: Round-trip time in milliseconds
- **Packet loss**: Percentage of packets not returned (indicates connectivity issues)
- **rtt (round-trip time)**: min/average/max values in milliseconds

---

## Q2: Practical Questions (20 Marks)

### OPTION A: Display Bus Topology

**Bus Topology** is a network configuration where all devices are connected to a single central cable (backbone).

**Characteristics:**
- **Single cable/backbone** connects all nodes sequentially
- **Linear arrangement** - nodes attached along the backbone
- **Simple to install** but difficult to modify and expand
- **Failure of backbone** disrupts the entire network
- **All nodes share the same bandwidth**

**Advantages:**
- Low cost - requires minimum cabling
- Easy installation and setup
- Minimal cabling infrastructure needed
- Simple to understand and implement

**Disadvantages:**
- Limited scalability - backbone becomes bottleneck
- Cable break disables entire network
- High collision rate with many devices
- Difficult to troubleshoot problems
- Performance degrades with more nodes
- Node failure doesn't break topology but adds load

**Example Layout:**
```
PC1 ────── PC2 ────── PC3 ────── PC4 ────── PC5
           (Single Shared Backbone Cable)
```

**Comparison with Other Topologies:**

| Aspect | Bus | Star | Ring | Mesh |
|--------|-----|------|------|------|
| **Backbone** | Single cable | Central hub | Ring loop | Multiple connections |
| **Fault tolerance** | Poor | Good | Poor | Excellent |
| **Cost** | Low | Medium | Medium | High |
| **Scalability** | Poor | Good | Fair | Excellent |
| **Installation** | Easy | Moderate | Moderate | Complex |

---

### OPTION B: Even Parity Error Detection

**Even Parity** is an error detection method where an extra parity bit ensures an even number of '1' bits in transmitted data.

**Concept:**
- Add 1 parity bit to each character/byte
- Total count of 1s (including parity bit) = always even
- If receiver counts odd number of 1s → error detected
- Can detect errors but **cannot correct** them

**Algorithm:**

```
FUNCTION addEvenParity(byte):
    count_ones = 0
    FOR each bit in byte:
        IF bit == 1:
            count_ones++
    
    IF count_ones % 2 == 1:  // Odd number of ones
        parity_bit = 1       // Add 1 to make even
    ELSE:
        parity_bit = 0       // Add 0 (already even)
    
    RETURN parity_bit || byte  // Prepend parity bit

FUNCTION checkEvenParity(byte_with_parity):
    count_ones = 0
    FOR each bit in byte_with_parity:
        IF bit == 1:
            count_ones++
    
    IF count_ones % 2 == 0:
        RETURN "NO ERROR"
    ELSE:
        RETURN "ERROR DETECTED"
```

**Example:**
```
Original: 1 0 1 0 1 (three 1s - odd)
Add parity bit: 1 (to make even count)
Transmitted: 1 | 1 0 1 0 1 (four 1s total - even)
           [P| DATA]

Receiver checks:
1 + 1 + 0 + 1 + 0 + 1 = 4 ones (even) ✓ Valid, No Error

If bit flips during transmission:
Received: 1 | 1 0 0 0 1 (three 1s - odd)
Receiver detects: Odd count ✗ Error Detected!
```

**Advantage & Limitations:**
- **Advantage**: Simple to implement, low overhead (1 bit per byte)
- **Limitation**: Can detect errors but cannot correct them
- **Limitation**: Cannot detect if 2 bits flip (still even count)

---

