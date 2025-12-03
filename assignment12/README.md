# CN Lab - Assignment 12

## Objective
Using RAW sockets to generate ICMP flooding attack.

## Exercise
Do the same attack as given in assignment no. 11 with ICMP packets using RAW socket.

## Implementation

### ICMP Flood ([icmp_flood.c](file:///c%3A/Users/spysc/OneDrive/Desktop/CSM24065_CNAssignment/assignment12/icmp_flood.c))
- Creates ICMP flood attack using raw sockets
- Uses four spoofed IPs as agent devices (10.0.0.3, 10.0.0.4, 10.0.0.5, 10.0.0.6)
- Sends continuous ICMP echo requests to target IP
- Includes data payload in ICMP packets
- Implements proper IP and ICMP header construction

## Compilation
```bash
gcc icmp_flood.c -o icmp_flood
```

Note: Root privileges are required to create raw sockets.

## Usage
```bash
sudo ./icmp_flood 10.0.0.2
```

## Mininet Setup
1. Create 6 hosts in Mininet:
   - 1 attacker (running the ICMP flood program)
   - 1 victim (target IP: 10.0.0.2)
   - 4 agent devices (spoofed IPs: 10.0.0.3, 10.0.0.4, 10.0.0.5, 10.0.0.6)

2. Run the ICMP flood program on the attacker host targeting the victim IP

## Learning Outcomes
1. Use of RAW sockets to generate ICMP based flooding attack.
2. Understanding the pattern of ICMP communication for DDoS attack.


CSM24065