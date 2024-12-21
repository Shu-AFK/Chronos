# Packets

## Packet structure for communication between agents and the main dashboard (sent from the agent)

### Agent initiation packet

This packet is used to request a new Agent ID from the server 

```
+---------------+-----------------+-------------------+-------------------------------+
| Version (4)   | Packet Type (4) | Name Length (8)   | Name (variable length)        |
+---------------+-----------------+-------------------+-------------------------------+
```

#### Description:
- **Version** (4 bits): The version of the protocol used by the agent.
- **Packet Type** (4 bits): Indicates the packet type, here it's 0 for initiation.
- **Name Length** (8 bits): Specifies the length of the name field in bytes.
- **Name** (variable length): The name of the agent or system initiating the connection, whose length is defined by the "Name Length" field.

### Metric data packet

This packet is sent by the agent to send metrics and health data to the main dashboard.

```
+---------------+-----------------+-----------------------------+
| Version (4)   | Packet Type (4) |         Agent ID (24)       |
+---------------+-----------------+-----------------------------+
|                       Timestamp (64)                          |
+---------------------------------------------------------------+
| Reserved (8)  |         Data Length (16)                      |
+---------------+-----------------------------------------------+
| Metric Count (16) |             Data (variable length)        |
+-------------------+-------------------------------------------+
|                       Checksum (32)                           |
+---------------------------------------------------------------+
```

#### Description:
- **Version** (4 bits): The version of the protocol.
- **Packet Type** (4 bits): Set to 1 for metric data.
- **Agent ID** (24 bits): Unique identifier for the agent sending the packet.
- **Timestamp** (64 bits): Timestamp indicating when the packet was generated.
- **Reserved** (8 bits): Reserved for future use, currently unused.
- **Data Length** (16 bits): Length of the data section (in bytes).
- **Metric Count** (16 bits): Number of metrics or alerts included in the packet.
- **Data** (variable length): The actual metric or alert data being sent from the agent.
- **Checksum (32 bits)**: A checksum used for error-checking the integrity of the packet.

## Packet structure for communication between agents and the main dashboard (sent from the server)

### Server initiation packet

This packet acknowledges the initiation attempt and gives the agent instructions.

```
+---------------+-----------------+---------------------+
| Version (4)   | Packet Type (4) |       Flags (8)     |
+---------------+-----------------+---------------------+
|                  Agent ID (24)                        |
+-------------------------------------------------------+
|          Response Time (16)         |  Reserved (16)  |
+-------------------------------------------------------+
```

**Flags**:
```
+---+---+---+---+---+---+---+---+
| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
+---+---+---+---+---+---+---+---+
| A | E | B | V | R | X | X | X |
+---+---+---+---+---+---+---+---+
```

#### Flags

- **A**: ACK (Acknowledgment)
- **E**: ERR (Error)
- **B**: BUSY (Server Busy)
- **V**: VER (Version Mismatch)
- **R**: READY (Server Ready)
- **X**: Reserved for future use


#### Description

- **Version** (4 bits): The version of the protocol being used.
- **Packet Type** (4 bits): Specifies the type of packet, set it to 2 for the server initiation packet.
- **Flags** (8 bits): Indicates specific states or control information (e.g., ACK, ERR).
- **Agent ID** (24 bits): The Agent ID, the agent should use in future requests.
- **Response Time** (16 bits): The interval (in milliseconds) at which the agent should send data.
- **Reserved** (16 bits): Reserved for future use; currently unused.


### Acknowledge packet

This packet tells the agent if the data packets got received without error and asks for resend if it didn't.

```
+---------------+-----------------+---------------------+
| Version (4)   | Packet Type (4) |       Flags (8)     |
+---------------+-----------------+---------------------+
```

#### Flags

```
+---+---+---+---+---+---+---+---+
| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
+---+---+---+---+---+---+---+---+
| A | R | C | X | X | X | X | X |
+---+---+---+---+---+---+---+---+
```

- **A**: ACK (Acknowledgment)
- **R**: RESEND
- **C**: CLOSE CONNECTION (Close and reopen socket)
- **X**: Reserved for future use

#### Description

- **Version** (4 bits): The version of the protocol being used.
- **Packet Type** (4 bits): Specifies the type of packet, set it to 3 for the server acknowledge packet.
- **Flags** (8 bits): Indicates specific states or control information (e.g., ACK, RESEND).


# Communication

```
+-------------------+                  +-------------------+
|     Agent         |                  |      Server       |
+-------------------+                  +-------------------+

1. Agent Initiation:
   +-----------------> INIT Packet (Version, Name)
   |                   (Requesting Agent ID)
   |
   |                   +--------------------+
2. Server Response:    | INIT Response Packet|
   |<------------------+ (Agent ID, Flags,   |
   |                     Response Time)      |
   |
3. Metric Flow Begins:
   +-----------------> Metric Data Packet
   |                   (Metrics, Timestamp)
   |
4. Server Acknowledges:
   |<------------------ Acknowledge Packet
   |                   (ACK, Flags)
   |
5. Handling Errors: (If needed)
   |                   +--------------------+
   +-----------------> | RESEND Request     |
   |                   | or CLOSE Connection|
   |<------------------+ Packet             |
   |

Repeat steps 3-5 for ongoing metric data exchange, once every interval given in the server INIT packet.
```