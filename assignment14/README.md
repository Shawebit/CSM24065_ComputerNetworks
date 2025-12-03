# CN Lab - Assignment 14

## Objective
Creating customized topologies in mininet.

## Exercise
Create a custom leaf-spine topology in mininet using python which can be scaled with increasing switch radix.

## Implementation

### Leaf-Spine Topology ([leaf_spine_topo.py](file:///c%3A/Users/spysc/OneDrive/Desktop/CSM24065_CNAssignment/assignment14/leaf_spine_topo.py))
- Python script using Mininet API to create scalable leaf-spine topology
- Configurable switch radix (ports per switch)
- Automatically calculates number of leaf and spine switches based on radix
- Reserves ports for host connections
- Provides interactive CLI for experimentation

## Usage
```bash
# Run with default radix (4)
sudo python3 leaf_spine_topo.py

# Run with custom radix
sudo python3 leaf_spine_topo.py 6
```

## Topology Structure
- Leaf switches form the access layer
- Spine switches form the core layer
- All leaf switches connect to all spine switches
- Hosts connect to leaf switches (2 hosts per leaf switch)
- Radix determines the number of ports per switch

## Scalability
The topology can be scaled by changing the radix parameter:
- Higher radix = More ports per switch
- More ports = More leaf/spine switches
- More switches = Larger network

## Learning Outcomes
1. Understanding mininet API.
2. Learning to perform experiments in virtual networks.


CSM24065