# Slip 18 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) In Cisco’s Packet tracer, which command used to change the prompt from Router> to Router# mode?

Use the `enable` command to enter privileged EXEC mode.
---

### b) Write down the steps to connect a PC to the Linksys router's web-based configuration page and find the default IP address.

Connect the PC to the router, open the browser, enter the router default IP address, and access the web configuration page. The default gateway address is often printed on the device label or documented in the manual.
---

### c) What is dynamic routing? Gives its features.

Dynamic routing automatically learns and updates routes using routing protocols such as RIP, OSPF, and EIGRP. It adapts to topology changes without manual route updates.
---

### d) List the commands used for Network Address Translation on Cisco’s Packet Tracer.

Common NAT commands include interface `ip nat inside`, interface `ip nat outside`, ACL configuration, and `ip nat inside source` rules. These are used to identify inside and outside interfaces and define translations.
---

### f) Explain steps to identify a phishing email.

Check sender address, suspicious links, urgent language, spelling mistakes, and unexpected requests for passwords or OTPs. Verify links before opening them and confirm any sensitive request through a trusted channel.
---

### g) Perform dictionary attack on SHA256 hash using Hashcat.

Hashcat can be used with an authorized wordlist attack to test password strength against SHA256 hashes. It should only be used for legitimate password auditing and recovery.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a C program for Phishing Simulation.

The program demonstrates phishing simulation by presenting deceptive content that helps users recognize warning signs in fake messages. Implement and verify using [Slip_18_Q2_OptionA.c](Slip_18_Q2_OptionA.c).

---

### OPTION B: Write a C program that simulates a NAT system.

The program simulates NAT by translating internal addresses to external ones according to the configured mapping logic, and verification is done with `show ip nat translations`. Implement and verify using [Slip_18_Q2_OptionB.c](Slip_18_Q2_OptionB.c).

---

### Q3: Bus Topology in Cisco Packet Tracer

To create and simulate a Bus Topology using four PCs in Cisco Packet Tracer. Assign appropriate IP addresses to all nodes and verify communication between them using the ping command.

- PC1 → 192.168.1.1 / 255.255.255.0
- PC2 → 192.168.1.2 / 255.255.255.0
- PC3 → 192.168.1.3 / 255.255.255.0
- PC4 → 192.168.1.4 / 255.255.255.0

Use a shared-medium layout to represent the bus topology in Packet Tracer, then assign the PCs to the same subnet and verify that each host can ping the others.
