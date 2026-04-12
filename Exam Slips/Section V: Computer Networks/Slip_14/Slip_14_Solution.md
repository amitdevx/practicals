# Slip 14 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) Configure PAT (NAT overload) to allow multiple internal hosts to access the internet using a single public IP.

PAT maps many private hosts to one public IP using different port numbers.
---

### b) Verify routing with ping, traceroute, and show ip route commands.

Use ping to check reachability, traceroute to see the path, and `show ip route` to view the routing table.
---

### c) Assign the privileged EXEC mode password as class.

Set the privileged EXEC password to `class` using the switch or router configuration mode.
---

### d) Use show running-config to verify all the configurations.

`show running-config` displays the active device configuration.
---

### f) List two advantages and two disadvantages of using dynamic IP configuration.

Advantages: automatic setup and efficient IP usage. Disadvantages: IP can change and troubleshooting may be harder.
---

### g) How do you verify if an interface received an IP dynamically?

Check the interface configuration using `ip addr`, `ifconfig`, or device show commands to confirm the assigned IP.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a program to implements Static Routing Simulation.

Implement and verify using [Slip_14_Q2_OptionA.c](Slip_14_Q2_OptionA.c).

---

### OPTION B: Write a program to program for LAN chat (client-server) using sockets.

Implement and verify using [Slip_14_Q2_OptionB.c](Slip_14_Q2_OptionB.c).

---

### Q3: Cisco Router and Linksys Wireless Router Configuration

Configure a router by setting the hostname, enable password, and encrypted secret password, and configure console and VTY passwords for secure access. Also, set up a Linksys Wireless Router in Cisco Packet Tracer and configure the SSID for wireless network connectivity.
