# Slip 4 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) What is Cyber Attack? Write the types of Cyberattacks.

A cyber attack is an attempt to damage, steal, disrupt, or gain unauthorized access to data or systems. Common types include malware attacks, phishing, ransomware, denial-of-service attacks, credential attacks, and spoofing.
---

### b) How can you reset or release an IP address obtained from DHCP?

On Windows, use `ipconfig /release` and `ipconfig /renew`. On Linux, use `dhclient -r` and then `dhclient` to drop and request a new lease.
---

### c) Explain supernetting with an example combining IPv4 Class C networks.

Supernetting combines multiple contiguous networks into a single larger route to reduce routing table entries. For example, 192.168.0.0/24 and 192.168.1.0/24 can be summarized into 192.168.0.0/23 if the networks are contiguous and aligned.
---

### d) How do you crack passwords with John the Ripper?

John the Ripper is a password auditing tool used on authorized systems to test the strength of stored password hashes. It should only be used for legitimate recovery or security assessment.
---

### f) Explain the use of copy running-config startup-config.

This command saves the current running configuration to the startup configuration in NVRAM so the settings remain after reboot. Without it, changes may be lost after a restart.
---

### g) What is a loopback IP address? What is its range?

A loopback IP address is used for local testing of the network stack on the same device. The IPv4 loopback range is 127.0.0.0/8, and 127.0.0.1 is the most commonly used address.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a C program that reads an email from a file and performs phishing pattern detection.

The program scans email content for phishing indicators such as suspicious links, urgent phrases, and fake sender patterns. Implement and verify using [Slip_04_Q2_OptionA.c](Slip_04_Q2_OptionA.c).

---

### OPTION B: Write a C program that checks private IP ranges.

The program checks whether an IP address falls within the private IPv4 ranges defined for Class A, B, and C networks. Implement and verify using [Slip_04_Q2_OptionB.c](Slip_04_Q2_OptionB.c).

---

### Q3: Packet Tracer Network Configuration

Create and configure a simple network in Cisco Packet Tracer by connecting two PCs through a switch. Assign the IP addresses 192.168.1.1 and 192.168.1.2 with subnet mask 255.255.255.0 to the PCs, and verify network connectivity using the ping command.

IP address classes are organized by the first octet. Class A ranges from 1.0.0.0 to 126.0.0.0, Class B from 128.0.0.0 to 191.255.0.0, Class C from 192.0.0.0 to 223.255.255.0, Class D from 224.0.0.0 to 239.255.255.255 for multicast, and Class E from 240.0.0.0 to 255.255.255.255 for experimental use.
