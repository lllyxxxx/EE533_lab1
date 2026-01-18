# EE533 Lab 1 – Client-Server Socket Programming

## Overview
This lab demonstrates a basic client-server communication model using
TCP sockets in the Internet domain. Two Ubuntu virtual machines were
configured as a Server and a Client using VMware.

## Environment
- VMware Workstation
- Ubuntu Linux (Server VM and Client VM)
- Network mode: NAT
- Programming language: C

## Files
- server/server.c : TCP socket server implementation
- client/client.c : TCP socket client implementation

## How to Compile
gcc server.c -o server
gcc client.c -o client

## How to Run
- On the Server VMh
./server 51717
- On the Client VM
./client <192.168.244.128> 51717

## Result
The client successfully connects to the server, sends a message, and
receives an acknowledgement response.
