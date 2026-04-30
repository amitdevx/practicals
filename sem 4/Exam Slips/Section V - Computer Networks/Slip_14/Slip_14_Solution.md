# Slip 14 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) Configure PAT (NAT overload) to allow multiple internal hosts to access the internet using a single public IP.

PAT maps many private hosts to one public IP using different port numbers. This lets multiple inside devices share a single outside address simultaneously.
---

### b) Verify routing with ping, traceroute, and show ip route commands.

Use ping to check reachability, traceroute to see the path, and `show ip route` to view the routing table. Together they confirm both connectivity and route selection.
---

### c) Assign the privileged EXEC mode password as class.

Set the privileged EXEC password to `class` using the switch or router configuration mode. This protects access to privileged commands.
---

### d) Use show running-config to verify all the configurations.

`show running-config` displays the active device configuration, including interfaces, passwords, and routing settings.
---

### f) List two advantages and two disadvantages of using dynamic IP configuration.

Advantages: automatic setup and efficient IP usage. Disadvantages: the IP can change and troubleshooting may be harder because the address is not permanent.
---

### g) How do you verify if an interface received an IP dynamically?

Check the interface configuration using `ip addr`, `ifconfig`, or device show commands to confirm the assigned IP. On Cisco devices, `show ip interface brief` is a quick check.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a program to implements Static Routing Simulation.

The program demonstrates static routing by using manually configured routes that remain fixed until changed by the administrator. Implement and verify using [Slip_14_Q2_OptionA.c](Slip_14_Q2_OptionA.c).

---

### OPTION B: Write a program to program for LAN chat (client-server) using sockets.

The program implements a simple LAN chat system using client-server sockets so two hosts can exchange messages over a network. Implement and verify using [Slip_14_Q2_OptionB.c](Slip_14_Q2_OptionB.c).

---

### Q3: Cisco Router and Linksys Wireless Router Configuration

Configure a router by setting the hostname, enable password, and encrypted secret password, and configure console and VTY passwords for secure access. Also, set up a Linksys Wireless Router in Cisco Packet Tracer and configure the SSID for wireless network connectivity.
