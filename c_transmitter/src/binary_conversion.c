#include "binary_conversion.h"

/*
 * double_to_hex:
 * takes in an array of unsigned char
 * takes in a double value
 * fills the array with the binary representation in bytes 
 * Little-Endian ordering
*/
void double_to_hex(unsigned char* hex_array, double val){
	int i;
	// ptr to 8-byte becomes ptr to 1-byte
	unsigned char *ptr = (unsigned char *)&val;
	// loop over the size of val (8-byte)
	for(i = 0; i < sizeof(val); i++){
		hex_array[i] = ptr[i];
	}
}

/*
 * entry_to_hex:
 * takes in a 2d array of unsigned char
 * takes in a double array for the data entry
 * fills out an array of binary representation for each attribute
 * Little-Endian ordering
*/
void entry_to_hex(unsigned char hex_array[][8], double* entry){
	int i;
	// NOTE: HARDCODED ENTRY ARRAY SIZE
	for(i = 0; i < 4; i++){
		double_to_hex(hex_array[i], entry[i]);
	}
}
