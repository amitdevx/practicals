# Slip 13 — Computer Networks Solution Guide

## Q1: Theory Questions (10 Marks - Answer ANY 5)

---

### a) How do you verify if an interface received an IP dynamically?

#### Concept
DHCP (Dynamic Host Configuration Protocol) automatically assigns IP addresses to network interfaces. Verifying dynamic IP assignment is crucial for network troubleshooting.

#### Methods to Verify Dynamic IP Assignment

**1. Using ipconfig (Windows):**
```cmd
ipconfig /all
```
Look for:
- "DHCP Enabled: Yes"
- "Lease Obtained" and "Lease Expires" fields
- "DHCP Server" address

**2. Using ip command (Linux):**
```bash
ip addr show eth0
```
Look for "dynamic" flag in output.

**3. Check DHCP lease file (Linux):**
```bash
cat /var/lib/dhcp/dhclient.leases
# OR
cat /var/lib/NetworkManager/dhclient-*.lease
```

**4. Using nmcli (Linux NetworkManager):**
```bash
nmcli device show eth0 | grep -i dhcp
```

**5. On Cisco Router/Switch:**
```
show ip interface brief
show dhcp lease
```

#### Example Output (Windows):
```
Ethernet adapter Local Area Connection:
   DHCP Enabled. . . . . . . . . : Yes
   IPv4 Address. . . . . . . . . : 192.168.1.105
   Subnet Mask . . . . . . . . . : 255.255.255.0
   Lease Obtained. . . . . . . . : Monday, January 15, 2024 9:00:00 AM
   Lease Expires . . . . . . . . : Tuesday, January 16, 2024 9:00:00 AM
   DHCP Server . . . . . . . . . : 192.168.1.1
```

---

### b) Demonstrate assigning IPs and testing connectivity for 3 systems in a LAN

#### Network Setup
```
[PC1] ----+
          |
[PC2] ----+---- [Switch] ---- (LAN: 192.168.1.0/24)
          |
[PC3] ----+
```

#### Step 1: Assign IP Addresses

**PC1 Configuration (Windows):**
```cmd
netsh interface ip set address "Local Area Connection" static 192.168.1.10 255.255.255.0 192.168.1.1
```

**PC2 Configuration (Windows):**
```cmd
netsh interface ip set address "Local Area Connection" static 192.168.1.20 255.255.255.0 192.168.1.1
```

**PC3 Configuration (Windows):**
```cmd
netsh interface ip set address "Local Area Connection" static 192.168.1.30 255.255.255.0 192.168.1.1
```

**Linux Alternative:**
```bash
# PC1
sudo ip addr add 192.168.1.10/24 dev eth0
sudo ip link set eth0 up

# PC2
sudo ip addr add 192.168.1.20/24 dev eth0
sudo ip link set eth0 up

# PC3
sudo ip addr add 192.168.1.30/24 dev eth0
sudo ip link set eth0 up
```

#### Step 2: Test Connectivity

**From PC1 - Test connectivity to PC2 and PC3:**
```cmd
ping 192.168.1.20
ping 192.168.1.30
```

**From PC2 - Test connectivity to PC1 and PC3:**
```cmd
ping 192.168.1.10
ping 192.168.1.30
```

**From PC3 - Test connectivity to PC1 and PC2:**
```cmd
ping 192.168.1.10
ping 192.168.1.20
```

#### Expected Successful Output:
```
Pinging 192.168.1.20 with 32 bytes of data:
Reply from 192.168.1.20: bytes=32 time<1ms TTL=128
Reply from 192.168.1.20: bytes=32 time<1ms TTL=128
Reply from 192.168.1.20: bytes=32 time<1ms TTL=128
Reply from 192.168.1.20: bytes=32 time<1ms TTL=128

Ping statistics for 192.168.1.20:
    Packets: Sent = 4, Received = 4, Lost = 0 (0% loss)
```

#### IP Assignment Summary Table:
| Device | IP Address    | Subnet Mask     | Default Gateway |
|--------|---------------|-----------------|-----------------|
| PC1    | 192.168.1.10  | 255.255.255.0   | 192.168.1.1     |
| PC2    | 192.168.1.20  | 255.255.255.0   | 192.168.1.1     |
| PC3    | 192.168.1.30  | 255.255.255.0   | 192.168.1.1     |

---

### c) Explain the role of VLAN1 in a switch's initial configuration

#### What is VLAN1?
VLAN1 is the **default VLAN** (also called the **native VLAN** or **management VLAN**) on Cisco switches. All switch ports belong to VLAN1 by default.

#### Roles of VLAN1:

**1. Default VLAN:**
- All switch ports are assigned to VLAN1 out of the box
- Enables immediate communication between connected devices
- No configuration required for basic operation

**2. Management VLAN:**
- Used for remote switch management (Telnet, SSH, HTTP)
- Switch virtual interface (SVI) for VLAN1 receives management IP
- Example configuration:
```
Switch(config)# interface vlan 1
Switch(config-if)# ip address 192.168.1.254 255.255.255.0
Switch(config-if)# no shutdown
```

**3. Native VLAN for Trunk Ports:**
- Untagged traffic on trunk links belongs to VLAN1
- IEEE 802.1Q standard specifies native VLAN
- Security Note: Consider changing native VLAN to prevent VLAN hopping attacks

**4. Control Plane Protocols:**
- CDP (Cisco Discovery Protocol) operates on VLAN1
- VTP (VLAN Trunking Protocol) advertisements use VLAN1
- STP (Spanning Tree Protocol) BPDUs sent on VLAN1

#### Security Considerations:
```
! Best Practice: Don't use VLAN1 for user traffic
Switch(config)# interface range fa0/1-24
Switch(config-if-range)# switchport access vlan 10

! Change native VLAN on trunks
Switch(config)# interface gi0/1
Switch(config-if)# switchport trunk native vlan 999
```

#### Diagram:
```
+------------------------------------------+
|              SWITCH                       |
|  +--------------------------------------+ |
|  |           VLAN 1 (Default)           | |
|  |  - All ports initially              | |
|  |  - Management IP: 192.168.1.254     | |
|  |  - CDP, VTP, STP traffic            | |
|  +--------------------------------------+ |
+------------------------------------------+
```

---

### d) What steps are required to configure the default gateway as 192.168.1.1

#### On Windows PC:

**Method 1: Command Line (netsh)**
```cmd
netsh interface ip set address "Local Area Connection" static 192.168.1.100 255.255.255.0 192.168.1.1
```

**Method 2: GUI**
1. Open Network Connections (ncpa.cpl)
2. Right-click adapter → Properties
3. Select IPv4 → Properties
4. Enter Default Gateway: 192.168.1.1
5. Click OK

#### On Linux PC:

**Method 1: ip command (temporary)**
```bash
sudo ip route add default via 192.168.1.1
```

**Method 2: Netplan (Ubuntu - permanent)**
```yaml
# /etc/netplan/01-config.yaml
network:
  version: 2
  ethernets:
    eth0:
      addresses: [192.168.1.100/24]
      gateway4: 192.168.1.1
```
Apply: `sudo netplan apply`

#### On Cisco Switch (Layer 2):
```
Switch> enable
Switch# configure terminal
Switch(config)# ip default-gateway 192.168.1.1
Switch(config)# end
Switch# write memory
```

#### On Cisco Router:
```
Router> enable
Router# configure terminal
Router(config)# ip route 0.0.0.0 0.0.0.0 192.168.1.1
Router(config)# end
Router# write memory
```

#### Verification Commands:
```cmd
# Windows
route print
netstat -rn

# Linux
ip route show
route -n

# Cisco
show ip route
show running-config | include default
```

---

### f) What steps are required to configure Dynamic NAT with a pool of public IP addresses

#### Concept
**Dynamic NAT** maps internal private IP addresses to a pool of public IP addresses on a first-come, first-served basis.

#### Network Scenario:
```
[Inside Network]          [Router]          [Outside Network]
192.168.1.0/24  -----> NAT Pool: 203.0.113.10-20 -----> Internet
```

#### Configuration Steps on Cisco Router:

**Step 1: Define the NAT Pool**
```
Router(config)# ip nat pool MYPOOL 203.0.113.10 203.0.113.20 netmask 255.255.255.0
```

**Step 2: Create Access List for Inside Hosts**
```
Router(config)# access-list 1 permit 192.168.1.0 0.0.0.255
```

**Step 3: Associate ACL with NAT Pool**
```
Router(config)# ip nat inside source list 1 pool MYPOOL
```

**Step 4: Define Inside and Outside Interfaces**
```
Router(config)# interface GigabitEthernet0/0
Router(config-if)# ip address 192.168.1.1 255.255.255.0
Router(config-if)# ip nat inside
Router(config-if)# exit

Router(config)# interface GigabitEthernet0/1
Router(config-if)# ip address 203.0.113.1 255.255.255.0
Router(config-if)# ip nat outside
Router(config-if)# exit
```

#### Complete Configuration:
```
! Define NAT pool
ip nat pool MYPOOL 203.0.113.10 203.0.113.20 netmask 255.255.255.0

! Define which internal addresses can use NAT
access-list 1 permit 192.168.1.0 0.0.0.255

! Link ACL to NAT pool
ip nat inside source list 1 pool MYPOOL

! Configure interfaces
interface GigabitEthernet0/0
 ip address 192.168.1.1 255.255.255.0
 ip nat inside

interface GigabitEthernet0/1
 ip address 203.0.113.1 255.255.255.0
 ip nat outside
```

#### Verification Commands:
```
Router# show ip nat translations
Router# show ip nat statistics
Router# debug ip nat
```

#### NAT Translation Table Example:
| Inside Local    | Inside Global   | Outside Local   | Outside Global  |
|-----------------|-----------------|-----------------|-----------------|
| 192.168.1.10    | 203.0.113.10    | 8.8.8.8         | 8.8.8.8         |
| 192.168.1.20    | 203.0.113.11    | 8.8.8.8         | 8.8.8.8         |

---

### g) Use debug ip routing or debug ip rip to monitor routing events and updates

#### debug ip routing

**Purpose:** Monitors routing table changes and routing protocol events.

**Enable Debugging:**
```
Router# debug ip routing
IP routing debugging is on
```

**Sample Output:**
```
*Mar  1 00:01:23: RT: add 10.0.0.0/8 via 192.168.1.2, rip metric [120/1]
*Mar  1 00:01:23: RT: SET_LAST_RDB for 10.0.0.0/8
*Mar  1 00:01:25: RT: del 172.16.0.0/16 via 192.168.1.3, rip metric [120/1]
*Mar  1 00:01:25: RT: delete subnet route to 172.16.0.0/16
```

**Interpretation:**
- `RT: add` - New route added to routing table
- `RT: del` - Route removed from routing table
- Shows metric, next-hop, and protocol

#### debug ip rip

**Purpose:** Monitors RIP (Routing Information Protocol) specific events.

**Enable Debugging:**
```
Router# debug ip rip
RIP protocol debugging is on
```

**Sample Output:**
```
*Mar  1 00:02:00: RIP: received v2 update from 192.168.1.2 on FastEthernet0/0
*Mar  1 00:02:00:      10.0.0.0/8 via 0.0.0.0 in 1 hops
*Mar  1 00:02:00:      172.16.0.0/16 via 0.0.0.0 in 2 hops
*Mar  1 00:02:30: RIP: sending v2 update to 224.0.0.9 via FastEthernet0/0
*Mar  1 00:02:30: RIP: build update entries
*Mar  1 00:02:30:      192.168.2.0/24 via 0.0.0.0, metric 1, tag 0
```

**Interpretation:**
- Shows RIP version (v1/v2)
- Received updates with network and hop count
- Sent updates with advertised networks
- Multicast address 224.0.0.9 for RIPv2

#### Best Practices:

**1. Use with Terminal Monitor:**
```
Router# terminal monitor
Router# debug ip rip
```

**2. Disable When Done:**
```
Router# undebug all
! OR
Router# no debug ip routing
Router# no debug ip rip
```

**3. Limit Output:**
```
Router# debug ip rip events    ! Only major events
```

#### Comparison:
| Command | Use Case |
|---------|----------|
| debug ip routing | General routing table changes |
| debug ip rip | RIP-specific updates and timers |
| debug ip ospf | OSPF protocol debugging |
| debug ip eigrp | EIGRP protocol debugging |

---

## Q2: Programming Questions (20 Marks)

---

## Option A: Display Hybrid Topology

### Concept
A **Hybrid Topology** combines two or more network topologies to leverage advantages of each. Common combinations include:
- Star + Bus
- Star + Ring
- Star + Star (Tree topology)

### Characteristics:
- **Flexibility** - Mix topologies based on needs
- **Scalability** - Easy to expand
- **Fault Tolerance** - Failure isolation between segments
- **Cost Effective** - Use appropriate topology per segment

### Program Structure:
```
Main Network (Bus Backbone)
    |
+---+---+---+---+
|       |       |
Star1   Star2   Star3
 /|\     /|\     /|\
Devices Devices Devices
```

### Files:
- **Slip_13_Q2_OptionA.c** - Complete implementation

### Pseudocode:
```
FUNCTION displayHybridTopology():
    PRINT header
    PRINT bus backbone
    FOR each star segment:
        PRINT central hub
        FOR each device in star:
            PRINT connection
    PRINT topology summary
```

### Compilation & Execution:
```bash
gcc -o hybrid_topology Slip_13_Q2_OptionA.c
./hybrid_topology
```

---

## Option B: Save Initial Switch Configuration

### Concept
Switch configuration includes:
- Hostname, passwords, interfaces
- VLANs, spanning tree, security
- Saving config ensures backup and documentation

### Configuration Elements:
| Element | Purpose |
|---------|---------|
| Hostname | Device identification |
| Enable Secret | Privileged mode security |
| VTY Lines | Remote access config |
| Console | Local access config |
| Interfaces | Port settings |
| VLANs | Broadcast domain separation |

### Files:
- **Slip_13_Q2_OptionB.c** - Complete implementation

### Pseudocode:
```
FUNCTION saveConfigToFile(filename):
    OPEN file for writing
    WRITE header with timestamp
    WRITE hostname config
    WRITE password config
    WRITE interface config
    WRITE VLAN config
    WRITE line config (console, vty)
    CLOSE file
    PRINT success message
```

### Compilation & Execution:
```bash
gcc -o switch_config Slip_13_Q2_OptionB.c
./switch_config
```

---

## Option C: Packet Tracer - Hybrid Topology

### Objective
Create a Hybrid Topology (Star + Star/Bus) connecting 8 PCs with IP addresses 192.168.1.1 through 192.168.1.8.

### Network Design:
```
           +---------+
           | Switch1 |---- (Backbone)
           +---------+
              |   |
    +---------+   +---------+
    |                       |
+---------+           +---------+
| Switch2 |           | Switch3 |
+---------+           +---------+
 /   |   \             /   |   \
PC1 PC2  PC3         PC5  PC6  PC7
         PC4                   PC8
```

### Step-by-Step Instructions:

**Step 1: Open Packet Tracer**
- Launch Cisco Packet Tracer
- Create new project

**Step 2: Add Network Devices**
- Add 3 switches (2960-24TT)
- Add 8 PCs (PC-PT)

**Step 3: Connect Devices**
```
Switch1 Fa0/1 ---- Fa0/24 Switch2 (Trunk)
Switch1 Fa0/2 ---- Fa0/24 Switch3 (Trunk)

Switch2:
  Fa0/1 ---- PC1
  Fa0/2 ---- PC2
  Fa0/3 ---- PC3
  Fa0/4 ---- PC4

Switch3:
  Fa0/1 ---- PC5
  Fa0/2 ---- PC6
  Fa0/3 ---- PC7
  Fa0/4 ---- PC8
```

**Step 4: Configure PC IP Addresses**
| Device | IP Address    | Subnet Mask     | Gateway       |
|--------|---------------|-----------------|---------------|
| PC1    | 192.168.1.1   | 255.255.255.0   | 192.168.1.254 |
| PC2    | 192.168.1.2   | 255.255.255.0   | 192.168.1.254 |
| PC3    | 192.168.1.3   | 255.255.255.0   | 192.168.1.254 |
| PC4    | 192.168.1.4   | 255.255.255.0   | 192.168.1.254 |
| PC5    | 192.168.1.5   | 255.255.255.0   | 192.168.1.254 |
| PC6    | 192.168.1.6   | 255.255.255.0   | 192.168.1.254 |
| PC7    | 192.168.1.7   | 255.255.255.0   | 192.168.1.254 |
| PC8    | 192.168.1.8   | 255.255.255.0   | 192.168.1.254 |

**Step 5: Configure on Each PC**
1. Click PC → Desktop → IP Configuration
2. Select Static
3. Enter IP, Subnet Mask, Gateway
4. Close window

**Step 6: Test Connectivity**
1. Click PC1 → Desktop → Command Prompt
2. Type: `ping 192.168.1.8`
3. Verify replies from all PCs

### Verification Commands on PCs:
```
C:\> ipconfig
C:\> ping 192.168.1.2
C:\> ping 192.168.1.5
C:\> ping 192.168.1.8
```

### Switch Configuration (Optional):
```
Switch>enable
Switch#configure terminal
Switch(config)#hostname Switch1
Switch(config)#interface vlan 1
Switch(config-if)#ip address 192.168.1.254 255.255.255.0
Switch(config-if)#no shutdown
Switch(config-if)#exit
Switch(config)#end
Switch#write memory
```

### Expected Ping Results:
```
C:\> ping 192.168.1.8

Pinging 192.168.1.8 with 32 bytes of data:

Reply from 192.168.1.8: bytes=32 time<1ms TTL=128
Reply from 192.168.1.8: bytes=32 time<1ms TTL=128
Reply from 192.168.1.8: bytes=32 time<1ms TTL=128
Reply from 192.168.1.8: bytes=32 time<1ms TTL=128

Ping statistics for 192.168.1.8:
    Packets: Sent = 4, Received = 4, Lost = 0 (0% loss)
```

---

## Quick Reference Summary

| Topic | Key Points |
|-------|------------|
| Dynamic IP Verify | `ipconfig /all`, look for DHCP Enabled: Yes |
| LAN IP Assignment | Static IP via netsh/ip command, ping to test |
| VLAN1 Role | Default VLAN, management, native VLAN |
| Default Gateway | `ip default-gateway` (switch), `ip route 0.0.0.0` (router) |
| Dynamic NAT | Pool + ACL + inside/outside interfaces |
| Debug Routing | `debug ip routing` for table changes |
| Debug RIP | `debug ip rip` for RIP updates |

---

## Files in This Solution

| File | Description |
|------|-------------|
| Slip_13_CN_SOLUTION.md | This document with theory answers |
| Slip_13_Q2_OptionA.c | Hybrid topology display program |
| Slip_13_Q2_OptionB.c | Switch configuration save program |
