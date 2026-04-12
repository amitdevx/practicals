# Slip 3 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) What does the command tracert or traceroute do?

It shows the path taken by packets from the source to the destination and lists each intermediate hop with delay information.
---

### b) Differentiate between ip addr and ifconfig commands in Linux.

`ip addr` is the modern command used to view and manage IP addresses and interfaces, while `ifconfig` is an older legacy command.
---

### c) What does nslookup do?

`nslookup` queries DNS servers to resolve domain names to IP addresses or to get reverse DNS information.
---

### d) List two advantages and two disadvantages of dynamic IP configuration.

Advantages: easy automatic setup and efficient IP usage. Disadvantages: IP address may change and troubleshooting can be less predictable.
---

### f) What is the function of a switch in a computer network?

A switch connects devices in a LAN and forwards frames to the correct port using MAC address information.
---

### g) What is network topology? What are its applications?

Network topology is the arrangement of devices and links in a network. It is used in network design, planning, and troubleshooting.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a C program to display Bus Topology.

Implement and verify using [Slip_03_Q2_OptionA.c](Slip_03_Q2_OptionA.c).

---

### OPTION B: Write a C program to implement even parity error detection.

Implement and verify using [Slip_03_Q2_OptionB.c](Slip_03_Q2_OptionB.c).

---

### Q3: CIDR and Router-Based LAN Connectivity

1. What is a CIDR value?
1. List the CIDR values for Class A, Class B, and Class C public IP addresses.
1. Design and configure a network in Cisco Packet Tracer consisting of two LANs connected through a Router (2911). Assign IP addresses as given and verify connectivity between all PCs using the ping command.

Network Details:

- LAN 1 (10.0.0.0/8)
- PC1 → 10.0.0.1
- PC2 → 10.0.0.2
- PC3 → 10.0.0.3
- Subnet Mask → 255.0.0.0

- LAN 2 (192.168.1.0/24)
- PC4 → 192.168.1.1
- PC5 → 192.168.1.2
- PC6 → 192.168.1.3
- Subnet Mask → 255.255.255.0

- Router (2911) Configuration
- Interface G0/0 → 10.0.0.4 / 255.0.0.0
- Interface G0/1 → 192.168.1.4 / 255.255.255.0
