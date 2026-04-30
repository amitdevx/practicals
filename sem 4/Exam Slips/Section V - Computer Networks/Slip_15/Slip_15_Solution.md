# Slip 15 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) What command do you type to move from Router> to Router# mode?

Use the `enable` command to enter privileged EXEC mode.
---

### b) How many hexadecimal digits are needed for a 64-bit WEP key? Give any 5 examples.

A 64-bit WEP key is usually entered as 10 hexadecimal digits, representing the 40-bit secret key portion of WEP-40. Example values include 1A2B3C4D5E, 0123456789, A1B2C3D4E5, FEDCBA9876, and 0F1E2D3C4B.
---

### c) Create a dummy phishing email and explain indicators of phishing.

Phishing emails often use urgent language, fake links, suspicious sender addresses, and requests for passwords or OTPs. A common sign is pressure to act quickly without verification.
---

### d) Crack a zip file protected with a password using fcrackzip.

Use authorized password-recovery tools like fcrackzip only on files you own or are permitted to test. The usual approach is to try a wordlist or brute-force attack within an authorized recovery workflow.
---

### f) Compare the output of ip addr and ifconfig.

`ip addr` is the modern command with more detailed interface and address information, while `ifconfig` is older and less detailed. `ip addr` is preferred on current Linux systems.
---

### g) How can you reset or release an IP address obtained from DHCP?

Use `ipconfig /release` on Windows or `dhclient -r` on Linux to release the DHCP address, then renew it if needed.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a program to Command-Line Phishing Simulation.

The program demonstrates a command-line phishing simulation by showing how suspicious prompts or messages can be presented to a user for awareness training. Implement and verify using [Slip_15_Q2_OptionA.c](Slip_15_Q2_OptionA.c).

---

### OPTION B: Write a program to displays a Mesh Topology.

The program displays a mesh topology by connecting nodes with multiple links to improve redundancy and fault tolerance. Implement and verify using [Slip_15_Q2_OptionB.c](Slip_15_Q2_OptionB.c).

---

### Q3: Mesh Topology in Cisco Packet Tracer

Create a Mesh Topology in Cisco Packet Tracer using four PCs. Assign the following IP addresses and verify connectivity between all nodes.

- PC1 → 172.16.1.1 / 255.255.0.0
- PC2 → 172.16.1.2 / 255.255.0.0
- PC3 → 172.16.1.3 / 255.255.0.0
- PC4 → 172.16.1.4 / 255.255.0.0
