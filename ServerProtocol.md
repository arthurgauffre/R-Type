# R-Type Game Network Protocol

This document outlines the design and implementation of a custom UDP-based protocol for the R-Type game. The protocol ensures low-latency transmission of game data while providing reliability for critical events. The protocol begins with a connection phase that mimics TCP over UDP, followed by efficient handling of game state data and guaranteed delivery for essential information. The implementation utilizes the **ASIO** C++ library for asynchronous I/O operations.

## 1. Overview

The R-Type game is a fast-paced, multiplayer shoot 'em up game. The networking protocol is built on top of UDP to optimize for latency and throughput, given the real-time nature of the game. However, critical game events (such as a player dying) require guaranteed delivery to maintain game state consistency. To achieve this, we adopt a hybrid approach where certain aspects of the protocol resemble TCP (connection establishment and critical message delivery), while regular game updates are sent over standard UDP way.

### 2.1 Connection Establishment

Although the game operates over UDP, the connection phase is designed to resemble TCP's 3-way handshake to ensure that both the client and server acknowledge each other before proceeding with game data transmission. **ASIO** is used to manage asynchronous sending and receiving of these messages.

#### Encrypted Handshake

To ensure the connection is secure from unauthorized access, the handshake process is encrypted using **bcrypt**. This ensures that the client and server exchange data securely and that only authorized clients can establish a connection.

The encrypted handshake process is as follows:

1. **Client sends SYN**: The client initiates a connection request by sending a SYN message to the server.
2. **Server responds with SYN-ACK**: The server generates a challenge (a cryptographic nonce or hash) and responds with a SYN-ACK.
3. **Client sends encrypted ACK**: The client hashes the challenge using bcrypt (or equivalent) and sends the encrypted ACK message to the server.
4. **Server validates ACK**: The server verifies the hash to ensure the client has the correct credentials, completing the handshake securely.

This encryption ensures that the connection setup is secure from the beginning, protecting the game from potential security risks, such as unauthorized access or man-in-the-middle attacks.

#### Connection Handshake Example

| Step  | Message         | Description                                                      |
|-------|-----------------|------------------------------------------------------------------|
| 1     | SYN             | Client initiates connection                                      |
| 2     | SYN-ACK         | Server acknowledges connection and sends cryptographic challenge |
| 3     | Encrypted ACK   | Client responds with an encrypted hash using bcrypt              |
| 4     | Validate ACK    | Server validates the encrypted response, completing the handshake|

### 2.2 Data Transmission

After the connection is established, the game data is transmitted over UDP using **ASIO** to handle asynchronous communication. Game data includes player positions, actions, enemy spawns, and environment updates. These packets are sent frequently and are designed to tolerate packet loss, as minor data loss does not significantly impact the game's experience.

The message structure is composed of two parts: the **header** and the **body**. The header contains important metadata such as:

- **Transaction ID (TID)**: A unique identifier for the message.
- **Size**: The size of the message in bytes.
- **Priority**: A value (integer or enum) representing the priority of the message.

The body contains the actual game data, and its size can vary depending on the message being transmitted.

#### Game Data Packet Structure

| Field      | Size     | Description                       |
|------------|----------|-----------------------------------|
| TID        | 4 bytes  | Unique identifier for the packet   |
| Size       | 4 bytes  | Size of the packet in bytes        |
| Priority   | 1 byte   | Priority level (0 = Low, 1 = High) |
| Payload    | Variable | Game state data                   |

### 2.3 Critical Event Transmission

Certain game events are too important to risk losing due to packet loss. These include events like:

- A player dying
- Boss spawning
- Game ending

For these critical events, we employ a retransmission mechanism until the server confirms that all clients have successfully received the message.

#### Critical Event Packet Structure

| Field        | Size     | Description                          |
|--------------|----------|--------------------------------------|
| Event Type   | 2 bytes  | Type of event (e.g., player death)    |
| Event Data   | Variable | Data specific to the event            |
| Acknowledgment | 1 byte  | 0 = Not acknowledged, 1 = Acknowledged|

1. **Event Sent**: The server sends the event packet to all clients.
2. **Client ACK**: Each client sends an acknowledgment (ACK) back to the server.
3. **Retransmit if necessary**: If the server does not receive an ACK from a client, it will retransmit the event until the ACK is received.

#### Critical Event Example

| Step  | Message        | Description                                     |
|-------|----------------|-------------------------------------------------|
| 1     | Event (Death)   | Server sends player death event                 |
| 2     | ACK             | Client acknowledges the event                   |
| 3     | Retransmit      | If ACK not received, server retransmits the event|

## 3. Reliability Mechanisms

### 3.1 Packet Acknowledgment

For critical game events, the protocol requires clients to acknowledge receipt of important packets. The server keeps track of these acknowledgments and retransmits if necessary.

### 3.2 Retransmission Strategy

- **Timeout-Based Retransmission**: The server uses a timeout mechanism to determine if a packet needs to be retransmitted. If no acknowledgment is received within the timeout window, the packet is retransmitted.
- **Max Retransmissions**: To avoid excessive retransmissions, a maximum number of attempts is set. After this, the server logs an error and may take corrective actions, such as notifying the client of a disconnection.

## 4. Conclusion

This UDP-based protocol, implemented with the **ASIO** C++ library, balances the need for speed with the requirement for reliability in critical moments. While game state updates are transmitted without guarantees, important events are handled with care to ensure consistency across all clients. The use of a priority field in the message header ensures that critical information is delivered with precedence. This design allows for a fluid and responsive multiplayer experience while maintaining the integrity of essential game events.

#
Go to the main documentation : [Main documentation](Readme.md)