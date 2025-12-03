# CN Lab - Assignment 10

## Objective
Using RAW sockets to generate packets.

## Exercise
Write two C programs using raw socket to send i. TCP packet where TCP payload will contain your roll number. ii. ICMP time stamp messages towards a target IP.

## Implementation

### TCP Packet Sender ([raw_tcp_sender.c](file:///c%3A/Users/spysc/OneDrive/Desktop/CSM24065_CNAssignment/assignment10/raw_tcp_sender.c))
- Creates custom TCP packets using raw sockets
- Includes roll number in TCP payload
- Sets appropriate TCP headers (SYN packet)
- Uses Mininet IP (10.0.0.1) as source

### ICMP Timestamp Sender ([icmp_timestamp.c](file:///c%3A/Users/spysc/OneDrive/Desktop/CSM24065_CNAssignment/assignment10/icmp_timestamp.c))
- Creates ICMP timestamp request packets
- Fills timestamp fields with current time
- Calculates proper checksums for both IP and ICMP headers

## Compilation
```bash
gcc icmp_timestamp.c -o icmpTime
gcc raw_tcp_sender.c -o rawSender
```

Note: Root privileges are required to create raw sockets.

## Usage
1. Send TCP packet with roll number:
   ```bash
   sudo ./rawSender 10.0.0.2 CSM24065
   ```

2. Send ICMP timestamp request:
   ```bash
   sudo ./icmpTime 10.0.0.2
   ```

## Verification with Wireshark
1. Start Wireshark capture on the Mininet interface
2. Run the programs
3. Stop capture and analyze:
   - Look for custom TCP packets with roll number in payload
   - Look for ICMP timestamp requests

## Learning Outcomes
1. Use of RAW socket to create custom TCP and ICMP messages.
2. Use of RAW socket for packet generation.


CSM24065