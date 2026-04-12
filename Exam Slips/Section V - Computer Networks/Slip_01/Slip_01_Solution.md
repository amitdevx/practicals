# Slip 1 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) What is the purpose of a modem in a network? Can we connect directly to the internet without it?

A modem converts digital data to a transmission format used by the ISP medium and converts received signals back to digital data. In most internet connections, a modem or modem-router is required before access.
---

### b) What is a MAC address and how is it different from an IP address?

A MAC address is a hardware address used at the data link layer, while an IP address is a logical address used at the network layer for routing.
---

### c) What is a loopback IP address? What is its range?

A loopback IP address is used to test the local network stack on the same device. The IPv4 loopback range is 127.0.0.0/8.
---

### d) Write the command to assign a static IP in Linux.

Use the `ip addr add` command to assign the IP address and `ip route add default via` to set the gateway.
---

### f) Which online tool used to check password strength.

PasswordMeter, HowSecureIsMyPassword, and similar password-checker websites can be used to test password strength.
---

### g) How to Use Nmap to Scan for Open Ports.

Use an Nmap command such as `nmap <target-ip>` or `nmap -sS <target-ip>` to scan for open ports on a target system.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a C program to implement the data link layer framing methods such as character and bit stuffing.

Implement and verify using `Slip_01_Q2_OptionA.c`.

---

### OPTION B: Write a C program to check password is strong or weak.

Implement and verify using `Slip_01_Q2_OptionB.c`.

---

### OPTION C: What is subnetting?

Given the network address 192.168.10.0/25 (Class C):

- Identify the number of network bits and host bits.
- Find the total number of subnetworks in a given network.
- Calculate the total number of IP addresses available in each subnet.
- Determine the total number of usable host addresses in each subnet.

Configure the following IP address on a PC and also on a Desktop end device in Cisco Packet Tracer. Verify the configuration using appropriate commands.

- IP Address: 192.168.1.10
- Subnet Mask: 255.255.255.0
- Default Gateway: 192.168.1.1
