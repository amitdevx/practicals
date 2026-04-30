# Slip 19 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) What is static routing? Gives its features.

Static routing is a manually configured route that does not change automatically. It is simple, secure, predictable, and suitable for small networks or fixed topologies.
---

### b) List the commands used for Network Address Translation on Cisco’s Packet Tracer.

Common NAT commands include `ip nat inside`, `ip nat outside`, ACLs, and `ip nat inside source` rules. These define the inside network and the translation mapping.
---

### c) Write an algorithm to Hash a password using SHA256.

SHA-256 hashes the password input into a fixed-length digest using a secure one-way hash function. The same input always produces the same digest, but the digest cannot be reversed to recover the original password.
---

### d) Write the Linux commands used to detect hidden Wi-Fi networks.

Use wireless scanning tools and adapter commands such as `iwlist`, `iw`, or NetworkManager utilities to inspect hidden SSIDs. These tools help identify networks that are not broadcasting a visible name.
---

### f) Explain steps to identify a phishing email.

Check sender details, suspicious links, urgent requests, grammar mistakes, and unexpected attachment behavior. Confirm the sender through a trusted source before taking any action.
---

### g) List types of Cyber Threats.

Examples include phishing, malware, ransomware, spyware, spoofing, and DDoS attacks. These threats target confidentiality, integrity, or availability.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a C program for Phishing Simulation.

The program demonstrates phishing simulation by showing how deceptive prompts or emails can be used to teach users to recognize attacks. Implement and verify using [Slip_19_Q2_OptionA.c](Slip_19_Q2_OptionA.c).

---

### OPTION B: Write a program to verify successful NAT translation using show NAT translation.

The program verifies NAT translation by checking that private addresses are mapped correctly to public addresses in the translation table, and the Cisco verification command is `show ip nat translations`. Implement and verify using [Slip_19_Q2_OptionB.c](Slip_19_Q2_OptionB.c).

---

### Q3: Two PCs and One Router in Cisco Packet Tracer

To create and configure a simple network in Cisco Packet Tracer using two PCs and one router. Assign the given IP addresses, configure the router interfaces, and verify network connectivity using ipconfig/ifconfig, ping, tracert, and nslookup commands.

Configuration:

- PC1 → 192.168.1.2 / 255.255.255.0
- PC2 → 192.168.2.2 / 255.255.255.0
- Router G0/0 → 192.168.1.1 / 255.255.255.0
- Router G0/1 → 192.168.2.1 / 255.255.255.0
