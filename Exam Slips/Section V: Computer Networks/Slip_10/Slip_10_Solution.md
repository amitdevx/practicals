# Slip 10 — Computer Networks Solution Guide

## Q1: Short Answer Questions

### a) What are network protocol layers?

**Protocol Stack Layers:**
1. **Physical Layer**: Cables, signals
2. **Data Link**: MAC addresses, frames
3. **Network**: IP routing
4. **Transport**: TCP/UDP
5. **Application**: HTTP, FTP, DNS

---

### b) What is a routing table?

**Routing Table:** Database of routes showing destination networks and next-hop routers.

**Entry Components:**
- Destination network
- Subnet mask
- Next hop (gateway)
- Interface
- Metric (cost)

---

### c) Subnetting formulas and calculations.

**Key Formulas:**
- Subnets = 2^n (n = borrowed bits)
- Hosts = 2^h - 2 (h = host bits)
- Subnet size = 256 / number_of_subnets

---

### d) What is ACL in networking?

**ACL (Access Control List):** Rules for filtering traffic.

```cisco
access-list 1 permit 192.168.1.0 0.0.0.255
access-list 1 deny any
```

---

### f) What is encryption?

**Encryption:** Converting plain text to cipher text for confidentiality.

**Types:**
- Symmetric: Same key encode/decode
- Asymmetric: Public/private key pair

---

### g) What is network performance?

**Metrics:**
- Bandwidth: Maximum capacity
- Latency: Delay time
- Throughput: Actual transfer rate
- Jitter: Latency variation
- Packet loss: Dropped packets percentage

---

## Q2: Practical Questions

Stop-and-wait ARQ protocol and network implementation.

---

