# Slip 6 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) Identify the network device from a given physical sample or image and write down its purpose and ports.

Identify the device by its ports and function: a switch forwards frames within a LAN, a router connects multiple networks, a modem converts signals for ISP access, and an access point provides wireless connectivity.
---

### b) List different types of network cables and their uses of Coaxial, Twisted Pair (STP & UTP), Fiber Optic.

Coaxial is a shielded legacy cable, UTP and STP are common copper cables used in LANs, and fiber optic supports very high-speed, long-distance communication with low interference.
---

### c) What is the role of no shutdown in router configuration?

`no shutdown` administratively enables the router interface so it can pass traffic. Without it, the interface remains disabled even if the IP address is configured.
---

### d) Compare the output of ip addr and ifconfig.

`ip addr` is the modern command from iproute2 with richer output and better support for current Linux networking features, while `ifconfig` is older and often deprecated.
---

### f) What command do you type to move from Router> to Router# mode?

Use `enable` to enter privileged EXEC mode and move from `Router>` to `Router#`.
---

### g) How many hexadecimal digits are needed for a 64-bit WEP key? Give any 5 examples.

A 64-bit WEP key is usually entered as 10 hexadecimal digits, representing the 40-bit secret key portion of WEP-40. Examples include 1A2B3C4D5E, 0123456789, A1B2C3D4E5, FEDCBA9876, and 0F1E2D3C4B.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a program to implement framing using character count method in the data link layer.

The program frames data by prefixing each frame with a count of the number of characters it contains. Implement and verify using [Slip_06_Q2_OptionA.c](Slip_06_Q2_OptionA.c).

---

### OPTION B: Write a program to display Star Topology.

Create and configure a Star Topology in Cisco Packet Tracer using one switch (2960) and five PCs (PC1, PC2, PC3, PC4, PC5). Assign the following IP addresses to the PCs and verify network connectivity using the ping command.

- PC1 192.168.1.1
- PC2 192.168.1.2
- PC3 192.168.1.3
- PC4 192.168.1.4
- PC5 192.168.1.5

The topology uses one central switch and five PCs connected in a star arrangement, allowing easy communication through the switch. Implement and verify using [Slip_06_Q2_OptionB.c](Slip_06_Q2_OptionB.c).

---

### OPTION C: To create and configure a network in Cisco Packet Tracer using two PCs and one router.

Assign the following IP addresses, configure the router interfaces, and verify network connectivity using ipconfig, ping, and tracert commands.

- PC1 → 192.168.1.2 / 255.255.255.0
- PC2 → 192.168.2.2 / 255.255.255.0
- Router G0/0 → 192.168.1.1 / 255.255.255.0
- Router G0/1 → 192.168.2.1 / 255.255.255.0

This creates two separate LANs connected by a router so the PCs can communicate across networks after the router interfaces are configured and enabled.
