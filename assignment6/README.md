# CN Lab - Assignment 6

## Objective
To gain knowledge of more TCP/IP C libraries.

## Exercise
Develop a simple C based network simulator to analyze TCP traffic.

## Implementation

The provided [packet_analyzer.c](file:///c%3A/Users/spysc/OneDrive/Desktop/CSM24065_CNAssignment/assignment6/packet_analyzer.c) program:

1. Uses raw sockets to capture all network packets
2. Parses Ethernet, IP, and TCP headers
3. Extracts and displays header fields
4. Runs in a continuous loop to analyze incoming traffic

## Compilation
```bash
gcc packet_analyzer.c -o packet_analyzer
```

## Usage
```bash
sudo ./packet_analyzer
```

Note: Root privileges are required to create raw sockets.

## Header Fields Extracted

### Ethernet Header
- Source MAC Address
- Destination MAC Address
- Protocol Type

### IP Header
- Version
- Internet Header Length
- Type of Service
- Total Length
- Identification
- Time To Live
- Protocol
- Header Checksum
- Source IP Address
- Destination IP Address

### TCP Header
- Source Port
- Destination Port
- Sequence Number
- Acknowledge Number
- Header Length
- Flags (URG, ACK, PSH, RST, SYN, FIN)
- Window Size
- Checksum
- Urgent Pointer

## Learning Outcomes
1. Knowledge of TCP/IP libraries.


CSM24065