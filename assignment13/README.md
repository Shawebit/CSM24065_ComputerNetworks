# CN Lab - Assignment 13

## Objective
To learn packet capturing and analysis.

## Exercise
Create a binary tree topology with 7 switches in mininet. Capture packets at the root switch. Write a C program to extract the headers and draw a time diagram to show the protocols displayed in the captured file (save the .pcap/.pcapng file of wireshark/tshark) during a PING operation. List the L2, L3, L4 protocols that can be extracted from the .pcap/.pcapng file.

## Implementation

### Packet Analyzer ([packet_analyzer.c](file:///c%3A/Users/spysc/OneDrive/Desktop/CSM24065_CNAssignment/assignment13/packet_analyzer.c))
- Reads .pcap/.pcapng files captured from Mininet
- Extracts and analyzes L2, L3, and L4 protocol headers
- Generates time diagram showing packet protocol occurrences
- Lists unique protocols extracted from the capture

## Compilation
```bash
make
```

Note: Requires libpcap development library
```bash
sudo apt-get install libpcap-dev
```

## Usage
```bash
./packet_analyzer capture.pcap
```

## Mininet Setup
1. Create binary tree topology with 7 switches:
   ```bash
   sudo mn --topo tree,depth=3,fanout=2
   ```

2. In the Mininet CLI, open the root switch:
   ```bash
   xterm s1
   ```

3. Capture packets at the root switch:
   ```bash
   tcpdump -i s1-eth1 -w capture.pcap
   ```

4. Perform PING operation between hosts:
   ```bash
   h1 ping h2
   ```

5. Stop tcpdump and analyze the captured file with the packet analyzer

## Learning Outcomes
1. Learning to analyze packets and its corresponding protocols.
2. Learning the roles of L2/L3/L4 protocols for a communication.