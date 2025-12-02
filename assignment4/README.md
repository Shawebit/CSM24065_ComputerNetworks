# CN Lab - Assignment 4

## Objective
To gain knowledge of packet capturing tools and understand header structures.

## Exercise
Install Wireshark in a VM (Virtual Machine) environment. Draw a time diagram to show the steps in the protocols recorded in the captured file (saved in the .pcap file of Wireshark) during a PING operation. List the L2, L3, L4 header fields that can be extracted from the .pcap file.

## Steps to Perform the Exercise

1. Install Wireshark in your Linux VM with Mininet
2. Start capturing packets on any interface
3. Ping any two hosts (e.g., ping 10.0.0.2 from host 10.0.0.1)
4. Stop the capture and save the .pcap file
5. Analyze the captured packets

## Expected Analysis

### Time Diagram for PING Operation
```
Time     Host A           Network           Host B
 |        |                 |                |
 |-----> ARP Request ----->|                |
 |        |                 |-----> ARP Request
 |        |                 |<----- ARP Reply |
 |<----- ARP Reply --------|                |
 |        |                 |                |
 |-----> ICMP Echo Req --->|-----> ICMP Echo Req
 |        |                 |<----- ICMP Echo Reply
 |<----- ICMP Echo Reply --|<----- ICMP Echo Reply
 |        |                 |                |
```

### Header Fields Extractable from .pcap File

#### L2 (Data Link Layer) - Ethernet Header
- Destination MAC Address
- Source MAC Address
- EtherType (Protocol ID)

#### L3 (Network Layer) - IP Header
- Version
- Header Length
- Type of Service
- Total Length
- Identification
- Flags
- Fragment Offset
- Time to Live (TTL)
- Protocol
- Header Checksum
- Source IP Address
- Destination IP Address

#### L4 (Transport Layer) - ICMP Header
- Type
- Code
- Checksum
- Identifier
- Sequence Number
- Data (timestamp for timestamp messages)

## Learning Outcomes
1. Knowledge of packet capturing tools, protocols and headers.