# CN Lab – Assignment 2

## Objective
To gain experience of TCP Socket Programming for simple applications.

## Exercise
Write a program using TCP socket to implement the following:
1. Server maintains records of fruits in the format: fruit-name, quantity Last-sold, (server timestamp)
2. Multiple client purchase the fruits one at a time
3. The fruit quantity is updated each time any fruit is sold
4. Send regret message to a client if the requested quantity of the fruit is not available
5. Display the customer ids <IP, port> who has done transactions already. This list should be updated in the server every time a transaction occurs
6. The total number of unique customers who did some transaction will be displayed to the customer every time

## Steps/Hints
1. Use at least two mininet hosts as clients
2. Server must be kept running using a loop condition
3. Take another socket (from accept() call) for keeping client information
4. Server must send the current stock information to the transacting host as queried in the question

## Output Screenshots

![Screenshot](assgn2.png)

---
`CSM24065`