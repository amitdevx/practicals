# Slip 18 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) In Cisco’s Packet tracer, which command used to change the prompt from Router> to Router# mode?

Use the `enable` command.
---

### b) Write down the steps to connect a PC to the Linksys router's web-based configuration page and find the default IP address.

Connect the PC to the router, open the browser, enter the router default IP address, and access the web configuration page.
---

### c) What is dynamic routing? Gives its features.

Dynamic routing automatically learns and updates routes using routing protocols such as RIP, OSPF, and EIGRP.
---

### d) List the commands used for Network Address Translation on Cisco’s Packet Tracer.

Common NAT commands include interface `ip nat inside`, interface `ip nat outside`, ACL configuration, and `ip nat inside source` rules.
---

### f) Explain steps to identify a phishing email.

Check sender address, suspicious links, urgent language, spelling mistakes, and unexpected requests for passwords or OTPs.
---

### g) Perform dictionary attack on SHA256 hash using Hashcat.

Hashcat can be used with an authorized wordlist attack to test password strength against SHA256 hashes.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a C program for Phishing Simulation.

Implement and verify using [Slip_18_Q2_OptionA.c](Slip_18_Q2_OptionA.c).

---

### OPTION B: Write a C program that simulates a NAT system.

Implement and verify using [Slip_18_Q2_OptionB.c](Slip_18_Q2_OptionB.c).

---

### Q3: Bus Topology in Cisco Packet Tracer

To create and simulate a Bus Topology using four PCs in Cisco Packet Tracer. Assign appropriate IP addresses to all nodes and verify communication between them using the ping command.

- PC1 → 192.168.1.1 / 255.255.255.0
- PC2 → 192.168.1.2 / 255.255.255.0
- PC3 → 192.168.1.3 / 255.255.255.0
- PC4 → 192.168.1.4 / 255.255.255.0
