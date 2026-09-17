## Converting Doubles to Binary
- Given the four GNSS attributes, I now need to convert them from doubles to binary representation.
- It is known that C stores their doubles using the IEEE-754 conventions, meaning that they are stored as 64-bit values in the memory.
- It is also possible to convert these doubles into signed integers and stored them that way, with the ICD defining the scale applied to convert them.
- This document will contain my decision on how the conversion will take place and the justification.
### The two possible paths:
1. Directly converting the doubles into binary values.
2. Scaling the doubles into signed integers and then into binary values.

### Doubles --> binary values
- Using an 'unsigned char* ptr', we can point the pointer at the address of the double.
- This will give us the starting byte of the 8-byte value.
- However, it has come to my attention that I must consider the concept of 'endianess' when reading these bytes.
#### Endianness
- Endianness refers to the order of which bytes are read or written in a computer system.
- The two primary forms of Endianness are Big-Endian and Little-Endian.
- Big-Endian: The most-significant bytes are stored first.
- Little-Enndian: The least-significant bytes are stored first.
- The MSBytes refers to the the bytes that hold the highest positional values.
    - E.g. in 2,543, changes in '2' has the highest positional value comapred to '3'.
#### Sample conversion
- In IEEE-754 the double '123456.78' has the binary form of '01000000 11111110 00100100 00001100 01111010 11100001 01000111 10101110'
- Which converts to '0x40FE240C7AE147AE'
#### Endianess of the current C program
- Reading the bytes of '123456.78', we can see that 0xAE is the first byte, then 0x40 is the last byte. This tells us that these bytes are ordered using Little-Endian.
