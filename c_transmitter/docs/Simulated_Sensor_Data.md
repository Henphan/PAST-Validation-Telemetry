## Simulated Sensor Data Documentation
This document will contain information regarding the simulated sensor data.

### What is the simulated sensor data?
- This project requires an STM32 written in C to 'read' simulated sensor values, structure them into packets, and transmit them to a Python receiver application.
- The main concern of this document is to decide how the microcontroller will 'read' these values.

### What are the main problems required to be considered?
- Unlike a C program that is compiled on a computer with, an STM32 does not have a structured file system which allows it to interact and read from files.
- This leads to the consideration of what format and form should the simulated sensor values be in for this project?

### The proposed solution and justification:
- The sensor values will be kept in a 2D array in a stand-alone file, as if it has already be processed and parsed into a convienient format.
- While this implementation will greatly simplify the problem related to the process of file reading and data validation, it will have to be the temporary solution as we focus on the more important parts of this project.
- It is also possible to have the STM32 read a file. However, this approach requires us to implement a file system library and a storage system to store these files, and this simply falls under the "Nice-To-Have" features as I have never created a C library, let alone a file system library.

### Current implementation (15/9/26):
- The GNSS data is contained within a 2D array, where each inner array represents one GNSS data entry.
- This raw data array is then parsed into a GNSS_Struct, which stores the time, latitute, longitude, and altitude. All these attributes are converted into doubles using strtod() before being stored.

### Possible future implementations:
- Given the struct, we can now create a program which converts it into binary data. How it is stored in binary data? That is yet to be decided.
