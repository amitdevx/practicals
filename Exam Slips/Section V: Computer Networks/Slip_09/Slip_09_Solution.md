# Slip 9 — Computer Networks Solution Guide

## Q1: Short Answer Questions

### a) What is a proxy server?

**Proxy Server:** Intermediary between client and server, hiding client IP and caching responses.

**Types:**
- Forward proxy: Client ↔ Proxy ↔ Server
- Reverse proxy: Internet ↔ Proxy ↔ Internal servers
- Transparent proxy: Invisible to client

---

### b) What is VLAN? Advantages?

**VLAN:** Virtual segmentation of physical network for better management and security.

**Advantages:**
- Improved security
- Better bandwidth management
- Easier network administration
- Cost reduction

---

### c) What are DNS query types?

**DNS Query Types:**
- A: IPv4 address
- AAAA: IPv6 address
- MX: Mail exchange
- CNAME: Canonical name (alias)
- NS: Nameserver
- TXT: Text records

---

### d) What is port scanning?

**Port Scanning:** Probing network to find open/closed ports and services.

**Tools:** Nmap, netstat
**Ports:** Well-known (0-1023), Registered (1024-49151), Dynamic (49152-65535)

---

### f) What is the route command?

**Route Command:** View and manipulate routing tables.

```bash
route print          # View routing table
route add 0.0.0.0 0.0.0.0 192.168.1.1  # Add route
route delete 192.168.1.0      # Remove route
```

---

### g) What is network latency?

**Latency:** Time delay in data transmission. Measured in milliseconds.

**Sources:**
- Physical distance
- Router processing
- Network congestion
- Link quality

---

## Q2: Practical Questions

Network design and configuration implementation.

---

