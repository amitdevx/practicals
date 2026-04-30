# Slip 20 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) What is the primary purpose of a banner MOTD?

A banner MOTD displays a warning or message before login to inform users and support security policy. It can also state that only authorized access is permitted.
---

### b) How many hexadecimal digits are needed for a 64-bit WEP key? Give any 5 examples.

A 64-bit WEP key is usually entered as 10 hexadecimal digits, representing the 40-bit secret key portion of WEP-40. Example values include 1A2B3C4D5E, 0123456789, A1B2C3D4E5, FEDCBA9876, and 0F1E2D3C4B.
---

### c) List types of Cyber Threats. Describe any two.

Common cyber threats include phishing, malware, ransomware, spoofing, and DDoS attacks. Phishing tricks users into revealing data, while malware is malicious software designed to damage or control systems.
---

### d) Differentiate between Static and Dynamic routing.

Static routing is manually configured and fixed, while dynamic routing automatically learns and updates routes using routing protocols. Static routing is simpler, but dynamic routing adapts better to network changes.
---

### f) What is the function of a switch in a computer network?

A switch connects devices in a LAN and forwards frames to the correct port using MAC addresses. It learns which MAC address is on which port to reduce unnecessary traffic.
---

### g) Describe any two network topologies.

Star topology uses a central switch or hub, and mesh topology connects nodes through multiple paths for higher reliability. Star is easy to manage, while mesh provides better fault tolerance.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a C program to represent Mesh Topology.

The program represents a mesh topology by connecting nodes with multiple links so that each node has more than one path for communication. Implement and verify using [Slip_20_Q2_OptionA.c](Slip_20_Q2_OptionA.c).

---

### OPTION B: Write a C program for Hash Simulation.

The program demonstrates hash generation by converting input data into a fixed-size digest or hash value. Implement and verify using [Slip_20_Q2_OptionB.c](Slip_20_Q2_OptionB.c).

---

### Q3: Mesh Topology in Cisco Packet Tracer

To create a Mesh Topology in Cisco Packet Tracer using four PCs. Assign the following IP addresses and verify connectivity between all nodes.

- PC1 → 172.16.1.1 / 255.255.0.0
- PC2 → 172.16.1.2 / 255.255.0.0
- PC3 → 172.16.1.3 / 255.255.0.0
- PC4 → 172.16.1.4 / 255.255.0.0
