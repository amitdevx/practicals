# Slip 7 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) Explain the difference between ping and traceroute.

`ping` checks reachability and latency to a host, while `traceroute` shows the path and intermediate hops used to reach the destination. Together they are useful for connectivity and routing diagnostics.
---

### b) Explain steps to identify a phishing email.

Check the sender address, suspicious links, urgent or unusual requests, spelling mistakes, and requests for passwords or OTPs. Any message that pressures the user to act quickly should be treated carefully.
---

### c) What is the function of a switch in a computer network?

A switch connects devices in a LAN and forwards frames to the correct port using MAC addresses. This keeps traffic local to the intended device.
---

### d) How many hexadecimal digits are needed for a 64-bit WEP key? Give any 5 examples.

A 64-bit WEP key is usually entered as 10 hexadecimal digits, representing the 40-bit secret key portion of WEP-40. Example values include 1A2B3C4D5E, 0123456789, A1B2C3D4E5, FEDCBA9876, and 0F1E2D3C4B.
---

### f) What is the primary purpose of a banner motd? How can it serve both a legal and security function?

A banner MOTD displays a login warning or notice before access. It can warn unauthorized users, state authorized-use rules, and support legal notice requirements.
---

### g) Create a dummy phishing email and explain indicators of phishing.

A dummy phishing email often uses urgent language, suspicious links, poor grammar, and fake sender details to trick the user. The key indicators are sender spoofing, urgency, and requests for confidential information.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a program to displays a Mesh Topology.

The program displays a mesh topology by connecting each node with multiple other nodes to improve redundancy. Implement and verify using [Slip_07_Q2_OptionA.c](Slip_07_Q2_OptionA.c).

---

### OPTION B: Write a program to configure hostname, enable password and encrypted secret password.

The program configures a device hostname, sets the enable password, and applies an encrypted enable secret for privileged access. Implement and verify using [Slip_07_Q2_OptionB.c](Slip_07_Q2_OptionB.c).

---

### Q3: Mesh Topology in Cisco Packet Tracer

Create a Mesh Topology in Cisco Packet Tracer using four PCs. Assign the following IP addresses and verify connectivity between all nodes.

- PC1 → 192.168.1.1 / 255.255.255.0
- PC2 → 192.168.1.2 / 255.255.255.0
- PC3 → 192.168.1.3 / 255.255.255.0
- PC4 → 192.168.1.4 / 255.255.255.0
