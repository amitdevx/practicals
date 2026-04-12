# Slip 2 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) What is the functional difference between a switch and a router?

A switch connects devices within the same LAN and forwards frames using MAC addresses. A router connects different networks and forwards packets using IP addresses.
---

### b) How many hosts are possible in a /26 subnet?

A /26 subnet has 6 host bits, so it provides 64 total addresses and 62 usable host addresses.
---

### c) What are the differences between Cat5e, Cat6, and Cat7 Ethernet cables?

Cat5e supports basic Gigabit Ethernet, Cat6 offers better shielding and higher speed performance, and Cat7 has stronger shielding and is designed for higher-frequency, lower-interference networks.
---

### d) Write the steps to identify a phishing email.

Check the sender address, inspect links, look for urgent or threatening language, verify spelling and grammar, and avoid opening suspicious attachments or sharing credentials.
---

### f) What are the two analysis methods used for analyzing malware?

The two methods are static analysis, where the file is inspected without execution, and dynamic analysis, where the malware is run in a controlled environment.
---

### g) What is the use of the ping command in networking?

`ping` checks whether a host is reachable and measures response time using ICMP echo requests and replies.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a C program to Simple Hash Simulation.

Implement and verify using [Slip_02_Q2_OptionA.c](Slip_02_Q2_OptionA.c).

---

### OPTION B: Write a C program to implement framing using character count method in the data link.

Implement and verify using [Slip_02_Q2_OptionB.c](Slip_02_Q2_OptionB.c).

---

### OPTION C: What is subnetting?

Given the network address 192.168.10.0/26 (Class C):

- Identify the number of network bits and host bits.
- Find the total number of subnetworks in a given network.
- Calculate the total number of IP addresses available in each subnet.
- Determine the total number of usable host addresses in each subnet.

To configure the IP address on a PC (real system) and also on a Desktop end device (virtual PC) in Cisco Packet Tracer using the following network details, verify the configuration using appropriate commands.

- IP Address: 192.168.2.10
- Subnet Mask: 255.255.255.0
- Default Gateway: 192.168.2.1
