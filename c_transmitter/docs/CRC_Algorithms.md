## Cyclic Redundancy Check Algorithms
- The CRC is an important field within the packet, it allows for the integrity of a packet to be validated.  
- However, there are various CRC algorithms, and this document will outline some of them and justify the final selection.
### Common CRC Algorithms:
#### The n-bit binary CRC
- This that I will need to consider and justify for this algorithm:
    - The n-value for
    - The polynomial
    - The possibility that a faulty-message can still pass the check

### Working with binary data in C:
- Unlike Python, where these binary sequence can be represented as strings and treated as strings, C gives you specific operations to perform on these bit patterns.
- To join two bytes together, you can use bit shifting and the OR operator.
    - Joining two bytes
    ```uint16_t xy = (x << 8) | y;```
    - Padding with 3-bit
    ```uint32_t xy_padded = xy << 3;```

## Current Implementation:

### crc_remainder()
Input:
- uint8_t entry[8]: an array of eight 8-bit values, representing one double
- uint8_t poly: a polynomial of maximum size of 8-bit
- int n: the degree of the polynomial (max of 7 for 8-bit)
Output:
- uint8_t: the remainder of length n
Description:
- This function acts as a wrapper to the three other CRC funtions. It takes in one instance of a double through an array of 8 bytes, and returns the remainder given the polynomial and the n-degree.
Future work:
- Allows for compatibility with other data length by replacing the hardcoded for loop. E.g. an integer is only 4 bytes.
- Implement a feature which detects whether the given polynomial and the n-degree match each other, e.g. a 10101010 polynomial should have the n-degree of 7.

### division_first()
Input:
- uint8_t message: a message of size one byte
- uint8_t poly: a polynomial of size one byte
- int n: the degree of the polynomial
Output:
- uint8_t: a byte representing the remainder from the division 
Description:
- This function will be run on the first byte of the entry as it does not require a remainder to be appended infront of it.

### division_carry_over()
Input:
- uint8_t message: a message of size one byte
- uint8_t poly: a polynomial of size one byte
- int n: the degree of the polynomial
- uint8_t remainder: the remainder with the length of n
Output:
- uint8_t: a byte representing the remainder from the division 
Description:
- This function will be run after division_first and before division_final. It will append the remainder infront and return the remainder aftwards.

### division_final()
Input:
- uint8_t message: a message of size one byte
- uint8_t poly: a polynomial of size one byte
- int n: the degree of the polynomial
- uint8_t remainder: the remainder with the length of n
Output:
- uint8_t: a byte representing the final CRC
Description:
- This function will be run last within the crc_remainder pipeline. It will append the remainder infront and append n zeroes behind and calculate the CRC.

