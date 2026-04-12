# Slip 9 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) List and explain all five IP address classes with examples.

Class A: 1.0.0.0 to 126.0.0.0, Class B: 128.0.0.0 to 191.255.0.0, Class C: 192.0.0.0 to 223.255.255.0, Class D: 224.0.0.0 to 239.255.255.255, Class E: 240.0.0.0 to 255.255.255.255.
---

### b) Explain the format and example of an IPv6 address.

IPv6 uses 128 bits written in hexadecimal groups separated by colons, for example `2001:db8::1`.
---

### c) Differentiate between Static NAT, Dynamic NAT, and Port Address Translation (PAT).

Static NAT maps one private address to one fixed public address, Dynamic NAT maps private addresses from a public pool, and PAT allows many private hosts to share one public IP using ports.
---

### d) Configure Dynamic NAT with a pool of public IP addresses.

Dynamic NAT uses a configured pool of public IP addresses and maps inside hosts to available addresses from that pool.
---

### f) Define Cyber Security.

Cyber security is the practice of protecting systems, networks, and data from unauthorized access, damage, and attacks.
---

### g) Explain Ethical Hacking.

Ethical hacking is authorized security testing performed to find and fix vulnerabilities before attackers exploit them.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a program to determine IP address class.

Implement and verify using [Slip_09_Q2_OptionA.c](Slip_09_Q2_OptionA.c).

---

### OPTION B: Write a program to implements Static Routing Simulation.

Implement and verify using [Slip_09_Q2_OptionB.c](Slip_09_Q2_OptionB.c).

---

### Q3: Cisco Packet Tracer Network Setup

To create and configure a simple network in Cisco Packet Tracer by connecting two PCs through a switch. Assign the IP addresses 172.20.1.1 and 172.20.1.2 with subnet mask 255.255.0.0 to the PCs, and verify network connectivity using the ping command.

Explain the IP address classes (Class A, B, C, D, and E) and their IP address ranges.
