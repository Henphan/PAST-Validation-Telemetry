## Packet Construction
With the data converted into the required form for the payload, the start marker value defined, the type designated, etc. The next process is the construction of the payload for transmission.
### Why must the packet be constructed?
- I will not go in-depth into why a packet is a must for the transmission of data, but the idea is that a packet structurally
organise your data and information to make the process of receiving as much painless as possible.
- A well-documented packet will define key fields and information which will help your receiving system, the Python program in my case, assume and make decisions based of the design 
- In conclusion, a packet allows us to make predictions on the structure and layout of a packet.
### How will the packet be constructed?
- As of writing this, the packet will contain these five fields:
    - Start marker
    - Type
    - Length
    - Payload
    - CRC
- The ICD will provide ore information into what these fields do.
- The C program will construct the packet through the function createPacket(). This fill out a Packet struct, preparing it for serialisation.
### How will the packet be transmitted?
- With the packet constructed, we cannot simply send the address of the packet + the next 255 bytes because while a struct is contiguous, the system may insert paddings between the relevant bytes.
- This is why the 'serialisation' of the packet before transmission is imperative.
- The serialisation process involves the action of compressing these bytes together into one sequence of data that can be transmitted.
### How Endianness affects serialisation:
- When serialising data, the order in which the bytes are read depends on the processor architecture / the memory model of the system. 
- Different Endian systems will order the LSB and MSB differently. With STM32 using the Little Endian system.
- That means that given 0x12345678, the STM32 will read the bytes as 0x78, 0x56, 0x34, and 0x12.

### The functions
#### createPacket()
Takes in:
- Packet *packet
- uint8_t type
- uint8_t* payload
Returns:
- Void

#### serialisePacket()
Takes in:
- Packet packet
- uint8_t buffer[256]
Returns:
- uint16_t
