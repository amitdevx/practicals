# Slip 1 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) What is the purpose of a modem in a network? Can we connect directly to the internet without it?

A modem converts digital signals into a form suitable for the ISP medium and converts incoming signals back into digital data. In most home and office connections, a modem or modem-router is required before the device can reach the internet.
---

### b) What is a MAC address and how is it different from an IP address?

A MAC address is a permanent hardware address assigned to a network interface and used at the data link layer. An IP address is a logical address assigned to identify a device on a network and is used at the network layer for routing.
---

### c) What is a loopback IP address? What is its range?

A loopback IP address is used to test the local network stack on the same device without sending traffic to a physical network. The IPv4 loopback range is 127.0.0.0/8, with 127.0.0.1 commonly used as the default loopback address.
---

### d) Write the command to assign a static IP in Linux.

Use `ip addr add <ip>/<prefix> dev <interface>` to assign the address and `ip route add default via <gateway>` to set the default route. For example, `ip addr add 192.168.1.10/24 dev eth0`.
---

### f) Which online tool used to check password strength.

Online tools such as PasswordMeter, How Secure Is My Password, or similar password-strength checkers can be used to evaluate password quality. They estimate strength based on length, complexity, and common patterns.
---

### g) How to Use Nmap to Scan for Open Ports.

Use an Nmap command such as `nmap <target-ip>` for a basic scan or `nmap -sS <target-ip>` for a TCP SYN scan. The output lists open ports, detected services, and sometimes service versions.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a C program to implement the data link layer framing methods such as character and bit stuffing.

The program demonstrates framing by inserting start and end delimiters for character stuffing and by escaping or modifying control bits for bit stuffing. Implement and verify using [Slip_01_Q2_OptionA.c](Slip_01_Q2_OptionA.c).

---

### OPTION B: Write a C program to check password is strong or weak.

The program validates password strength by checking length, uppercase and lowercase letters, digits, and special characters. Implement and verify using [Slip_01_Q2_OptionB.c](Slip_01_Q2_OptionB.c).

---

### OPTION C: What is subnetting?

Given the network address 192.168.10.0/25 (Class C):

- Identify the number of network bits and host bits.
- Find the total number of subnetworks in a given network.
- Calculate the total number of IP addresses available in each subnet.
- Determine the total number of usable host addresses in each subnet.

For a /25 subnet, the first 25 bits are network bits and the remaining 7 bits are host bits. That gives 2 subnets, 128 total addresses per subnet, and 126 usable host addresses per subnet.

Configure the following IP address on a PC and also on a Desktop end device in Cisco Packet Tracer. Verify the configuration using appropriate commands.

- IP Address: 192.168.1.10
- Subnet Mask: 255.255.255.0
- Default Gateway: 192.168.1.1
