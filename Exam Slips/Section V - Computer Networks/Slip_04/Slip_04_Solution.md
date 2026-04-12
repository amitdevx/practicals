# Slip 4 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) What is Cyber Attack? Write the types of Cyberattacks.

A cyber attack is an attempt to damage, steal, or disrupt data or systems. Common types include malware attacks, phishing, ransomware, denial-of-service attacks, and password attacks.
---

### b) How can you reset or release an IP address obtained from DHCP?

On Windows, use `ipconfig /release` and `ipconfig /renew`. On Linux, use `dhclient -r` and then `dhclient`.
---

### c) Explain supernetting with an example combining IPv4 Class C networks.

Supernetting combines multiple contiguous networks into a single larger route. For example, two Class C /25 networks can be summarized into one /24 route.
---

### d) How do you crack passwords with John the Ripper?

John the Ripper is a password auditing tool used on authorized systems to test the strength of stored password hashes.
---

### f) Explain the use of copy running-config startup-config.

This command saves the current running configuration to the startup configuration in NVRAM so the settings remain after reboot.
---

### g) What is a loopback IP address? What is its range?

A loopback IP address is used for local testing of the network stack on the same device. The IPv4 loopback range is 127.0.0.0/8.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a C program that reads an email from a file and performs phishing pattern detection.

Implement and verify using [Slip_04_Q2_OptionA.c](Slip_04_Q2_OptionA.c).

---

### OPTION B: Write a C program that checks private IP ranges.

Implement and verify using [Slip_04_Q2_OptionB.c](Slip_04_Q2_OptionB.c).

---

### Q3: Packet Tracer Network Configuration

Create and configure a simple network in Cisco Packet Tracer by connecting two PCs through a switch. Assign the IP addresses 192.168.1.1 and 192.168.1.2 with subnet mask 255.255.255.0 to the PCs, and verify network connectivity using the ping command.

Explain the IP address classes (Class A, B, C, D, and E) and their IP address ranges.
