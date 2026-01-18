*This project has been created as part of the 42 curriculum by rlutucir.*

# minitalk

## Description

**minitalk** is a small communication program written in C that demonstrates how two processes can exchange data using UNIX signals.

The project consists of a **server** and a **client**:
- The **server** receives signals and reconstructs characters bit by bit.
- The **client** sends a string to the server by encoding each character into signals.

Only the signals `SIGUSR1` and `SIGUSR2` are used.  
Each character is transmitted one bit at a time, and the server acknowledges each bit to ensure reliable communication.

---

## Instructions

### Compilation

Compile the project using `make`:

```bash
make
```

1. Start the server first:

```bash
./server
```

The server will print its PID

2. Run the client using the PID and your message

```bash
./client <SERVER_PID> "Your message here"
```

The message will appear in the server terminal

## Resources
### Documentation & References

https://www.youtube.com/watch?v=83M5-NPDeWs&list=PL9LZM-hWdUvsqXxqghK5H1fF07nCV9MyF&index=1

https://www.youtube.com/watch?v=Tq-roajRVVI&list=PL9LZM-hWdUvsqXxqghK5H1fF07nCV9MyF&index=7

https://www.youtube.com/watch?v=VVDiup7Q4rw&list=PL9LZM-hWdUvsqXxqghK5H1fF07nCV9MyF&index=5

Linux Signals documentation

### Use of AI
AI was used as a learning aid to:

Understand how sigaction works

Clarify signal handling and acknowledgment logic