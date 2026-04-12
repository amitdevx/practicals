# Slip 6 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) Identify the network device from a given physical sample or image and write down its purpose and ports.

Identify the device by ports and function: switch (LAN forwarding), router (inter-network routing), modem (ISP conversion), AP (wireless access).
---

### b) List different types of network cables and their uses of Coaxial, Twisted Pair (STP & UTP), Fiber Optic.

Coaxial is shielded legacy/media cable, UTP/STP are common LAN copper cables, and fiber optic supports high-speed long-distance links.
---

### c) What is the role of no shutdown in router configuration?

`no shutdown` administratively enables the router interface so it can pass traffic.
---

### d) Compare the output of ip addr and ifconfig.

`ip addr` is the modern command from iproute2 with richer output; `ifconfig` is older and often deprecated.
---

### f) What command do you type to move from Router> to Router# mode?

Use `enable` to enter privileged EXEC mode (`Router#`).
---

### g) How many hexadecimal digits are needed for a 64-bit WEP key? Give any 5 examples.

A 64-bit WEP key uses 16 hexadecimal digits.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a program to implement framing using character count method in the data link layer.

Implement and verify using [Slip_06_Q2_OptionA.c](Slip_06_Q2_OptionA.c).

---

### OPTION B: Write a program to display Star Topology.

Create and configure a Star Topology in Cisco Packet Tracer using one switch (2960) and five PCs (PC1, PC2, PC3, PC4, PC5). Assign the following IP addresses to the PCs and verify network connectivity using the ping command.

- PC1 192.168.1.1
- PC2 192.168.1.2
- PC3 192.168.1.3
- PC4 192.168.1.4
- PC5 192.168.1.5

Implement and verify using [Slip_06_Q2_OptionB.c](Slip_06_Q2_OptionB.c).

---

### OPTION C: To create and configure a network in Cisco Packet Tracer using two PCs and one router.

Assign the following IP addresses, configure the router interfaces, and verify network connectivity using ipconfig, ping, and tracert commands.

- PC1 → 192.168.1.2 / 255.255.255.0
- PC2 → 192.168.2.2 / 255.255.255.0
- Router G0/0 → 192.168.1.1 / 255.255.255.0
- Router G0/1 → 192.168.2.1 / 255.255.255.0
