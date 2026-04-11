# Slip 8 — Computer Networks Solution Guide

## Q1: Short Answer Questions

---

### a) What is IP fragmentation?

**IP Fragmentation** breaks large packets into smaller units when they exceed MTU (Maximum Transmission Unit).

**When it occurs:**
- Packet size > link MTU (usually 1500 bytes Ethernet)
- Router must forward but link has smaller MTU
- Fragments reassembled at destination

**Fragment Offset:** Indicates fragment position in original packet

---

### b) How does ARP work?

**ARP (Address Resolution Protocol):** Maps IP addresses to MAC addresses.

**Process:**
1. Host wants to send to IP X but doesn't know MAC
2. Broadcasts ARP Request "Who has IP X?"
3. Target host responds with its MAC
4. Sender updates ARP cache with mapping
5. Data sent using MAC address

---

### c) Explain IP addressing schemes.

**IP Addressing:** Logical addresses for network communication.

**IPv4:** 32 bits, 4 octets (192.168.1.1)
**IPv6:** 128 bits, 8 groups (2001:db8::1)

---

### d) Packet Tracer routing between networks.

**Routing:** Forward packets between different networks using routers.

---

### f) What is wireless security? Types of encryption.

**Security Types:**
- WEP: Outdated, weak
- WPA: Improved security
- WPA2: Current standard
- WPA3: Latest with enhanced security

---

### g) What is VLAN?

**VLAN (Virtual LAN):** Logically segments network without physical separation.

---

## Q2: Practical Questions

### OPTION A & B: Routing and Network Configuration

Implement routing protocols and network setups.

---

