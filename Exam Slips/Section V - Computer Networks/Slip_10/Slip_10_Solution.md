# Slip 10 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) What are the differences between Cat5e, Cat6, and Cat7 Ethernet cables?

Cat5e supports Gigabit Ethernet, Cat6 provides better performance and less crosstalk, and Cat7 has stronger shielding and supports higher frequencies.
---

### b) What is the purpose of a modem in a network? Can we connect directly to the internet without it?

A modem converts signals between the ISP medium and digital devices. In most connections, a modem or gateway device is needed before internet access.
---

### c) Write the command to assign a static IP in Linux.

Use `ip addr add <ip>/<prefix> dev <iface>` and set the default gateway with `ip route add default via <gw>`.
---

### d) What is the use of the ping command in networking?

`ping` checks host reachability and response time using ICMP echo requests.
---

### f) Differentiate between Static NAT, Dynamic NAT, and Port Address Translation (PAT).

Static NAT maps one private IP to one fixed public IP, Dynamic NAT uses a public IP pool, and PAT lets many private hosts share one public IP using ports.
---

### g) Configure Static NAT on a router using Cisco Packet Tracer or GNS3. Assign a public IP to a private IP.

Static NAT is configured by setting inside and outside interfaces and creating a fixed private-to-public translation.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a program to implement even parity error detection..

Implement and verify using [Slip_10_Q2_OptionA.c](Slip_10_Q2_OptionA.c).

---

### OPTION B: Write a program to perform subnetting and supernetting calculations.

Implement and verify using [Slip_10_Q2_OptionB.c](Slip_10_Q2_OptionB.c).

---

### Q3: Subnetting in Cisco Packet Tracer

What is subnetting?

Given the network address 192.168.10.0/25 (Class C):

- Identify the number of network bits and host bits.
- How many host bits are available?
- Determine the number of networks and number of hosts per network.
- Calculate the total number of assignable IP addresses in each network.

To create and configure a simple network in Cisco Packet Tracer by connecting two PCs through a switch. Assign the IP addresses 192.168.10.1 and 192.168.10.2 with subnet mask 255.255.255.0 to the PCs, and verify network connectivity using the ping command.
