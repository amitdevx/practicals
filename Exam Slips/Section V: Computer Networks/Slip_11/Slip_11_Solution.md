# Slip 11 — Computer Networks Solution Guide

## Q1: Short Answer Questions

### a) What is network security?

**Network Security:** Protects data and resources from unauthorized access and attacks.

**Measures:**
- Firewalls
- Intrusion detection
- Encryption
- Access control
- Authentication

---

### b) How to set up DHCP server?

**DHCP Server Configuration:**

```cisco
ip dhcp pool LAN
network 192.168.1.0 255.255.255.0
default-router 192.168.1.1
dns-server 8.8.8.8
```

---

### c) What is default gateway?

**Default Gateway:** Router used for all traffic not on local network.

```
Configuration:
IP: 192.168.1.100
Gateway: 192.168.1.1
```

---

### d) Important Cisco IOS commands.

```cisco
enable                   # Enter privileged mode
configure terminal       # Enter config mode
interface GigabitEthernet0/0
ip address 192.168.1.1 255.255.255.0
show running-config      # Display current config
copy running-config startup-config  # Save
```

---

### f) What is configuration backup?

**Backup Methods:**
- TFTP server
- USB drive
- Cloud storage

---

### g) What is network device?

**Devices:**
- Router: Inter-network communication
- Switch: Local network switching
- Firewall: Security enforcement
- Gateway: Protocol conversion

---

## Q2: Practical Questions

Network setup and device configuration.

---

