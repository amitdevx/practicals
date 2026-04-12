# Slip 17 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) What is the primary purpose of a banner MOTD?

A banner MOTD displays a warning or notice to users before login and is used for security and legal awareness.
---

### b) What is one benefit of using a simulator like Packet Tracer for learning networking, and what is one limitation compared to actual hardware?

Packet Tracer is safe and low-cost for practice, but it cannot perfectly reproduce every real hardware behavior.
---

### c) Differentiate between Static NAT, Dynamic NAT, and Port Address Translation (PAT).

Static NAT maps one private IP to one fixed public IP, Dynamic NAT maps from a pool of public IPs, and PAT allows many private hosts to share one public IP using ports.
---

### d) List the commands used for Network Address Translation on Cisco’s Packet Tracer.

Common NAT commands include interface configuration, `ip nat inside`, `ip nat outside`, ACL configuration, and `ip nat inside source` rules.
---

### f) Use Netstat command to view active connections.

Use `netstat -an` to display active and listening connections.
---

### g) What is the primary purpose of a banner MOTD?

A banner MOTD displays a warning or notice to users before login and is used for security and legal awareness.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a C program for password security with Special Characters that includes special character checks along with uppercase, lowercase, digit, and length rules.

Implement and verify using [Slip_17_Q2_OptionA.c](Slip_17_Q2_OptionA.c).

---

### OPTION B: Write a C program to convert plain message to cipher message.

Implement and verify using [Slip_17_Q2_OptionB.c](Slip_17_Q2_OptionB.c).

---

### Q3: Simple Network in Cisco Packet Tracer

To create and configure a simple network in Cisco Packet Tracer by connecting two PCs through a switch. Assign the IP addresses 172.16.1.1 and 172.16.1.2 with subnet mask 255.255.0.0 to the PCs, and verify network connectivity using the ping command.
