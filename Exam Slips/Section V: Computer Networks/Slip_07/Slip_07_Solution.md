# Slip 7 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) What is the difference between TCP and UDP?

**TCP (Transmission Control Protocol):**
- Connection-oriented
- Reliable delivery
- Error checking and recovery
- Ordered data
- Slower but guaranteed
- Used for: Email, web, file transfer

**UDP (User Datagram Protocol):**
- Connectionless
- Unreliable delivery
- No error correction
- Unordered data
- Faster with less overhead
- Used for: Voice, video, gaming

**Comparison:**

| Feature | TCP | UDP |
|---------|-----|-----|
| **Connection** | Established | Connectionless |
| **Reliability** | Guaranteed | Best effort |
| **Ordering** | In sequence | Unordered |
| **Speed** | Slower | Faster |
| **Error Checking** | Yes | Minimal |
| **Use Case** | Accuracy critical | Speed critical |

---

### b) How does DHCP work? Explain the mechanism.

**DHCP (Dynamic Host Configuration Protocol)** automatically assigns network configuration to devices.

**4-Step DHCP Process:**

1. **DISCOVER**: Client broadcasts request for IP
2. **OFFER**: Server offers available IP
3. **REQUEST**: Client requests specific IP
4. **ACK**: Server confirms assignment

**Lease Time:**
- IP assigned for specific duration
- Device must renew before expiration
- Unused IPs returned to pool

---

### c) Convert the given binary number to decimal and vice versa.

**Binary to Decimal:**
```
10110101 (binary)
= 1×128 + 0×64 + 1×32 + 1×16 + 0×8 + 1×4 + 0×2 + 1×1
= 128 + 32 + 16 + 4 + 1
= 181 (decimal)
```

**Decimal to Binary:**
```
181 (decimal)
181 ÷ 2 = 90 remainder 1
90 ÷ 2 = 45 remainder 0
45 ÷ 2 = 22 remainder 1
22 ÷ 2 = 11 remainder 0
11 ÷ 2 = 5 remainder 1
5 ÷ 2 = 2 remainder 1
2 ÷ 2 = 1 remainder 0
1 ÷ 2 = 0 remainder 1

Result: 10110101 (binary)
```

---

### d) What are firewall rules? How to implement them?

**Firewall Rules:** Define which traffic is allowed/blocked.

**Rule Components:**
- Source IP/address
- Destination IP/address
- Protocol (TCP/UDP/ICMP)
- Port number
- Action (Allow/Block)

**Example Rules:**
```
Allow TCP port 80 (HTTP) from any to web server
Block UDP port 53 (DNS) from external
Allow SSH (port 22) from admin subnet only
```

---

### f) What is FTP? How does it work?

**FTP (File Transfer Protocol):**
- Transfers files between computers
- Uses port 21 (control) and port 20 (data)
- Unencrypted (use SFTP for security)

**Command:**
```bash
ftp server_ip
```

---

### g) What is TTL? Why is it important?

**TTL (Time To Live):**
- Hop count limit for packets
- Decremented at each router
- When TTL reaches 0, packet discarded
- Prevents infinite loops

**Default TTL:** 64 or 128 (varies by OS)

---

## Q2: Practical Questions (20 Marks)

### OPTION A: TCP Handshake (3-Way Handshake)

Establishes connection before data transfer.

**Steps:**
1. **SYN**: Client sends sequence number
2. **SYN-ACK**: Server acknowledges and sends its sequence
3. **ACK**: Client acknowledges server's sequence

---

### OPTION B: Data Link Layer Protocol

Implements error detection and MAC addressing.

---

