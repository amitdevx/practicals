# Slip 8 — Computer Networks Solution Guide

## Q1: Short Answer Questions (10 Marks - Answer ANY 5)

---

### a) Why is it important to configure an enable (EXEC mode) password on a switch?

It protects privileged switch access and prevents unauthorized users from entering configuration mode. This is a basic security measure for management access.
---

### b) Explain the role of VLAN1 in a switch’s initial configuration.

VLAN1 is the default management VLAN used for initial switch management and basic connectivity. It is often assigned the management IP address in simple labs.
---

### c) Configure Static NAT on a router using Cisco Packet Tracer or GNS3. Assign a public IP to a private IP.

Static NAT maps one private IP permanently to one public IP. It is used when a host must always be reachable at the same public address.
---

### d) Configure Dynamic NAT with a pool of public IP addresses.

Dynamic NAT maps private hosts to available public IPs from a configured pool. The translation is temporary and released when the session ends.
---

### f) Define Hashing.

Hashing converts input data into a fixed-length value using a hash function. The result is called a hash or digest.
---

### g) What are Cyber Security Policies.

Cyber security policies are organizational rules and guidelines for protecting systems, data, and users from security threats. They define acceptable use, access control, and incident handling expectations.
---

## Q2: Practical Questions (20 Marks)

### OPTION A: Write a program to verify the configuration using show running-config and ping commands.

The program demonstrates configuration verification by displaying active settings and checking connectivity with ping. Implement and verify using [Slip_08_Q2_OptionA.c](Slip_08_Q2_OptionA.c).

---

### OPTION B: Write a program to set up a dynamic routing protocols such as RIP, EIGRP or OSPF.

The program simulates a dynamic routing setup using protocols such as RIP, EIGRP, or OSPF to exchange route information automatically. Implement and verify using [Slip_08_Q2_OptionB.c](Slip_08_Q2_OptionB.c).

---

### Q3: Cisco Switch Initial Settings

To configure the initial settings of a Cisco Switch (Example 2960) in Cisco Packet Tracer by setting the hostname and console password using CLI commands. Verify the configuration using appropriate show commands.
