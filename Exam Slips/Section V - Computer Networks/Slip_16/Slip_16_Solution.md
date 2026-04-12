# Slip 16 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) Compare and contrast the functionalities of a switch and a router.

A switch operates within a LAN using MAC addresses, while a router connects different networks using IP addresses.
---

### b) What is a MAC address and how is it different from an IP address?

A MAC address is a hardware address for a device, whereas an IP address is a logical address used for network routing.
---

### c) Perform subnetting on 192.168.1.0/26 and list all 4 subnet ranges with usable host IPs.

A /26 network divides the range into smaller subnets with 62 usable hosts per subnet. The four subnet ranges should be listed with their host ranges and broadcast addresses.
---

### d) List and explain all five IP address classes with examples.

Class A, B, C, D, and E are the five IPv4 classes used for different address ranges and purposes.
---

### f) How many hexadecimal digits are needed for a 64-bit WEP key? Give any 5 examples.

A 64-bit WEP key uses 16 hexadecimal digits.
---

### g) What are two more secure wireless encryption standards that should be used instead of WEP in a real-world scenario?

WPA2 and WPA3 are more secure wireless encryption standards than WEP.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a C program to encrypt plain message to cipher message.

Implement and verify using [Slip_16_Q2_OptionA.c](Slip_16_Q2_OptionA.c).

---

### OPTION B: Write a C program to implement the any data link layer framing method.

Implement and verify using [Slip_16_Q2_OptionB.c](Slip_16_Q2_OptionB.c).

---

### Q3: Cisco Packet Tracer Star Topology

Create and configure a Star Topology in Cisco Packet Tracer using one switch (Ex.2960) and five PCs (PC1, PC2, PC3, PC4, PC5). Assign the following IP addresses to the PCs and verify network connectivity using the ping command.

- PC1 172.16.1.1
- PC2 172.16.1.2
- PC3 172.16.1.3
- PC4 172.16.1.4
- PC5 172.16.1.5

Subnet Mask:

- 255.255.0.0
- 255.255.0.0
- 255.255.0.0
- 255.255.0.0
- 255.255.0.0
