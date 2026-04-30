# Slip 2 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) What is the functional difference between a switch and a router?

A switch connects devices within the same LAN and forwards frames using MAC addresses. A router connects different networks and forwards packets using IP addresses and routing tables.
---

### b) How many hosts are possible in a /26 subnet?

A /26 subnet has 6 host bits, so it provides 64 total addresses and 62 usable host addresses after excluding the network and broadcast addresses.
---

### c) What are the differences between Cat5e, Cat6, and Cat7 Ethernet cables?

Cat5e supports Gigabit Ethernet over short to medium distances, Cat6 offers better crosstalk performance and higher bandwidth, and Cat7 provides stronger shielding for reduced interference in higher-frequency networks.
---

### d) Write the steps to identify a phishing email.

Check the sender address, inspect links before clicking, look for urgent or threatening language, verify spelling and grammar, and avoid opening suspicious attachments or sharing credentials.
---

### f) What are the two analysis methods used for analyzing malware?

The two methods are static analysis, where the file is inspected without execution, and dynamic analysis, where the malware is run in a controlled environment to observe behavior.
---

### g) What is the use of the ping command in networking?

`ping` checks whether a host is reachable and measures response time using ICMP echo requests and replies. It is commonly used for basic connectivity testing and troubleshooting.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a C program to Simple Hash Simulation.

The program computes a simple hash value from the input string and shows how data can be reduced to a fixed-size result. Implement and verify using [Slip_02_Q2_OptionA.c](Slip_02_Q2_OptionA.c).

---

### OPTION B: Write a C program to implement framing using character count method in the data link.

The program uses the character-count framing method, where each frame begins with a count field indicating the number of characters in the frame. Implement and verify using [Slip_02_Q2_OptionB.c](Slip_02_Q2_OptionB.c).

---

### OPTION C: What is subnetting?

Given the network address 192.168.10.0/26 (Class C):

- Identify the number of network bits and host bits.
- Find the total number of subnetworks in a given network.
- Calculate the total number of IP addresses available in each subnet.
- Determine the total number of usable host addresses in each subnet.

For 192.168.10.0/26, there are 26 network bits and 6 host bits, which gives 4 subnets, 64 addresses per subnet, and 62 usable host addresses per subnet.

To configure the IP address on a PC (real system) and also on a Desktop end device (virtual PC) in Cisco Packet Tracer using the following network details, verify the configuration using appropriate commands.

- IP Address: 192.168.2.10
- Subnet Mask: 255.255.255.0
- Default Gateway: 192.168.2.1
