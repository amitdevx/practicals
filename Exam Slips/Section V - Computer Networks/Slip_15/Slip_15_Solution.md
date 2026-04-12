# Slip 15 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) What command do you type to move from Router> to Router# mode?

Use the `enable` command.
---

### b) How many hexadecimal digits are needed for a 64-bit WEP key? Give any 5 examples.

A 64-bit WEP key uses 16 hexadecimal digits.
---

### c) Create a dummy phishing email and explain indicators of phishing.

Phishing emails often use urgent language, fake links, suspicious sender addresses, and requests for passwords or OTPs.
---

### d) Crack a zip file protected with a password using fcrackzip.

Use authorized password-recovery tools like fcrackzip only on files you own or are permitted to test.
---

### f) Compare the output of ip addr and ifconfig.

`ip addr` is the modern command with more detailed interface and address information, while `ifconfig` is older and less detailed.
---

### g) How can you reset or release an IP address obtained from DHCP?

Use `ipconfig /release` on Windows or `dhclient -r` on Linux to release the DHCP address.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a program to Command-Line Phishing Simulation.

Implement and verify using [Slip_15_Q2_OptionA.c](Slip_15_Q2_OptionA.c).

---

### OPTION B: Write a program to displays a Mesh Topology.

Implement and verify using [Slip_15_Q2_OptionB.c](Slip_15_Q2_OptionB.c).

---

### Q3: Mesh Topology in Cisco Packet Tracer

Create a Mesh Topology in Cisco Packet Tracer using four PCs. Assign the following IP addresses and verify connectivity between all nodes.

- PC1 → 172.16.1.1 / 255.255.0.0
- PC2 → 172.16.1.2 / 255.255.0.0
- PC3 → 172.16.1.3 / 255.255.0.0
- PC4 → 172.16.1.4 / 255.255.0.0
