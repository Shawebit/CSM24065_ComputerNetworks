# CN Lab - Assignment 2

## Objective
To gain experience of TCP Socket Programming for simple applications.

## Exercise
Implementation of a fruit shop management system using TCP socket programming with the following features:

1. Server maintains records of fruits (name, quantity, last sold timestamp)
2. Multiple clients can purchase fruits one at a time
3. Fruit quantities are updated after each sale
4. Server sends regret message if requested quantity is not available
5. Server displays client IDs (IP, port) who have done transactions
6. Server displays total number of unique customers after each transaction

## Compilation
```bash
gcc tcp_server -o server
gcc tcp_client -o client
```

## Usage
1. Start the server:
   ```bash
   ./server
   ```

2. In another terminal, run clients:
   ```bash
   ./client apple 5
   ./client banana 10
   ```

## Features Implemented
- Fruit inventory management
- Multi-client support
- Transaction tracking
- Client identification
- Real-time stock updates

CSM24065