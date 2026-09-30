## The Python Receiver
The second most important part of the project. It will be a program which receives the serialised data transmitted by the STM32 through UART. It will also uses the definition in the ICD to validate the data as a valid packet, and reconstruct it into readable data.
## 30/09/2026
- As of 30/09/2026, I will simply attempt to write a program that takes in the simulated data, validates it and then reconstruct it back to its intended original form, all according to the ICD.
- The main limitation is that, unlike receiving data from an STM32, the simulated data will all be present initially.
- Whereas an STM32 will send data byte by byte.
- Therefore, this may impact my ability to test the program's ability to wait for the entire packet.
- However, I can still implement and test the other major functions, e.g. finding key fields, performing CRC, and reconstructing data.
### Intended approach
- After doing some researching (ChatGPT), I found out that the uint8_t data will be read as bytes by the Python receiver as well.
- This means that sending 0xAB from the STM32 will be read as b'\xAB' by the Python receiver.
- Therefore, I will create a simulated data sequence such as b'\xAB\xCD\xEF'.
- I will then have to create a program that iterates through each received byte, checking its value against the start marker.
- Once the start marker is found, we will then check the type and length, and whether they are both in the valid ranges.
- If they are, we can start reading the payload + CRC using the found length.
- With the payload, we can calculate the CRC and compared the two values.
- If every passes, we can use the ICD specifications to deconstruct the payload into the correct format.
- All deconstructed data will be saved into .csv file.
### Assumptions of approach:
- For now, if any error is raised during this process then we will restart the entire process -- starting again with the starter marker.
- For now, we will assume that there will be no errors during the process.
