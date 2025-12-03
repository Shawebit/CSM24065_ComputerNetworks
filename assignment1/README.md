# TCP Client-Server Socket Programming Assignment

This assignment demonstrates basic TCP client-server communication where the client sends "Hi" and the server responds with "Hello".

## Files Included

1. `tcp_server.c` - Minimal TCP server program
2. `tcp_client.c` - Minimal TCP client program
3. `Makefile` - For compiling the programs

## Compilation

To compile both programs, run:
```bash
gcc tcp_server -o server
gcc tcp_client -o client
```

This will create two executables:
- `tcp_server`
- `tcp_client`

## Running the Programs in Mininet

1. Start Mininet with two hosts:
```bash
sudo mn --topo single,2
```

2. In the Mininet CLI, open terminals for both hosts:
```bash
xterm h1 h2
```

3. In h1 terminal, start the server:
```bash
./server
```

4. In h2 terminal, run the client:
```bash
./client
```

CSM24065