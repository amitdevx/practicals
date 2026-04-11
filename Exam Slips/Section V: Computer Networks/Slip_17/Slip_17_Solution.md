# Slip 17 — Computer Networks Solution Guide

## Q1: Short Answer Questions

### a) What is Frame Relay?

**Frame Relay:**
- WAN technology for packet switching
- Operates at Data Link layer (L2)
- Efficient for bursty traffic
- Lower overhead than X.25
- PVC (Permanent Virtual Circuit) or SVC (Switched Virtual Circuit)

**Features:**
- No error correction (relies on upper layers)
- Variable frame sizes
- Used in enterprise WAN

---

### b) What is X.25?

**X.25:**
- Older WAN protocol
- Packet-switched network
- Three layers: Physical, Link, Packet
- Error checking and flow control
- Slower than Frame Relay
- Mostly obsolete, replaced by Frame Relay/MPLS

---

### c) What is NAT?

**NAT (Network Address Translation):**
- Translates private IPs to public IPs
- Enables multiple devices to share single public IP
- Types: Static NAT (1-to-1), Dynamic NAT (pool), PAT (many-to-1)

**Configuration:**
```
Inside private: 192.168.1.100
Outside public: 203.0.113.5
```

---

### d) Compare connection types.

**Connection Types:**

| Type | Speed | Reliability | Use Case |
|------|-------|-------------|----------|
| Dial-up | 56 Kbps | Poor | Legacy |
| DSL | 10-100 Mbps | Good | Residential |
| Cable | 100-1000 Mbps | Good | Residential/Business |
| Fiber | 1-10 Gbps | Excellent | Enterprise |
| Leased Line | Fixed | Excellent | Enterprise |

---

### f) What is protocol?

**Protocol:** Set of rules for network communication.

**Examples:**
- HTTP: Web browsing
- FTP: File transfer
- SMTP: Email sending
- DNS: Domain name resolution

---

### g) What is packet switching?

**Packet Switching:**
- Divides data into packets
- Each packet routed independently
- Packets may take different paths
- Reassembled at destination
- Efficient for shared networks

---

## Q2: Practical Questions

Frame Relay and NAT configuration.

---

