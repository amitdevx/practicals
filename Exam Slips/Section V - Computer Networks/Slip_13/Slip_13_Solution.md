# Slip 13 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) How do you verify if an interface received an IP dynamically?

Use commands such as `ip addr`, `ifconfig`, or router/switch show commands to confirm that the interface has obtained an IP address.
---

### b) Demonstrate assigning IPs and testing connectivity for 3 systems in a LAN.

Assign unique IP addresses in the same subnet to three systems and test connectivity using the ping command.
---

### c) Explain the role of VLAN1 in a switch’s initial configuration.

VLAN1 is the default management VLAN and is commonly used for initial switch configuration and basic management access.
---

### d) What steps are required to configure the default gateway as 192.168.1.1.

Set the default gateway to 192.168.1.1 in the device network settings or routing configuration.
---

### f) What steps are required to configure Dynamic NAT with a pool of public IP addresses.

Create a pool of public IP addresses, define inside and outside interfaces, and map inside hosts to available addresses from the pool.
---

### g) Use debug ip routing or debug ip rip to monitor routing events and updates.

These debug commands display live routing updates and help monitor routing behavior during troubleshooting.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a program to displays a Hybrid Topology.

Implement and verify using [Slip_13_Q2_OptionA.c](Slip_13_Q2_OptionA.c).

---

### OPTION B: Write a program to version that saves an Initial Switch Configuration into a text file.

Implement and verify using [Slip_13_Q2_OptionB.c](Slip_13_Q2_OptionB.c).

---

### Q3: Hybrid Topology in Cisco Packet Tracer

To create and simulate a Hybrid Topology in Cisco Packet Tracer by combining two different network topologies (e.g., Star and Bus or Star and Star). Assign appropriate IP addresses to all nodes and verify communication between them using the ping command.

Topology Arrangement:

- Star Network 1: PC1, PC2, PC3, PC4 → Switch1
- Star Network 2: PC5, PC6, PC7, PC8 → Switch2
- Connect Switch1 ↔ Switch2

PC IP Address:

- PC1 192.168.1.1
- PC2 192.168.1.2
- PC3 192.168.1.3
- PC4 192.168.1.4
- PC5 192.168.1.5
- PC6 192.168.1.6
- PC7 192.168.1.7
- PC8 192.168.1.8

Subnet Mask:

- 255.255.255.0
- 255.255.255.0
- 255.255.255.0
- 255.255.255.0
- 255.255.255.0
- 255.255.255.0
- 255.255.255.0
- 255.255.255.0
