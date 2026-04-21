# Slip 12 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) What is the function of a switch in a computer network?

A switch connects devices in a LAN and forwards frames to the correct port using MAC addresses. It learns MAC-to-port mappings dynamically.
---

### b) Write the command to assign a static IP in Linux.

Use `ip addr add <ip>/<prefix> dev <iface>` to assign the address and `ip route add default via <gateway>` to set the gateway. Example: `ip addr add 192.168.1.10/24 dev eth0`.
---

### c) What does the ip link set eth0 up command do?

It brings the network interface `eth0` into the active state so that it can transmit and receive packets.
---

### d) Explain the difference between ping and traceroute.

`ping` checks reachability and latency, while `traceroute` shows the path and intermediate hops to the destination. Traceroute is useful for identifying where a route is breaking.
---

### f) What does the ip route show command display?

It displays the routing table of the system, including destination networks, gateways, and interface information.
---

### g) Why should two connected systems be in the same subnet?

Systems in the same subnet can communicate directly without requiring a router for local traffic. If they are in different subnets, a router is needed to forward the packets.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a C program to display a Star Topology.

The program models a star topology by showing multiple nodes connected to a central switch. Implement and verify using [Slip_12_Q2_OptionA.c](Slip_12_Q2_OptionA.c).

---

### OPTION B: Write a program to configure hostname, enable password and encrypted secret password.

The program sets the device hostname, configures the enable password, and secures privileged access with an encrypted secret password. Implement and verify using [Slip_12_Q2_OptionB.c](Slip_12_Q2_OptionB.c).

---

### Q3: Cisco Packet Tracer Star Topology

To create and configure a Star Topology in Cisco Packet Tracer using one switch (Example 2960) and five PCs (PC1, PC2, PC3, PC4, PC5). Assign the following IP addresses to the PCs and verify network connectivity using the ping command.

- PC1 192.168.10.1
- PC2 192.168.10.2
- PC3 192.168.10.3
- PC4 192.168.10.4
- PC5 192.168.10.5

Subnet Mask:

- 255.255.255.0
- 255.255.255.0
- 255.255.255.0
- 255.255.255.0
- 255.255.255.0

All five PCs are placed in the same /24 subnet so they can communicate directly through the switch.
