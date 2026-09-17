#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "gnss_data.h"
#include "binary_conversion.h"


void read_data(char* data[][4]);

int main(void){
	int i, j;
	// processing the raw data into an array of structs
	// struct GNSS_Struct s_array[52];
	// struct GNSS_Struct s1;
	// char* endptr;
	// for(i = 0; i < 52; i++){
	// 	s1.time = strtod(raw_data[i][0], &endptr);
	// 	s1.lat = strtod(raw_data[i][1], &endptr);
	// 	s1.lon = strtod(raw_data[i][2], &endptr);
	// 	s1.alt = strtod(raw_data[i][3], &endptr);
	// 	s_array[i] = s1;
	// }
	double attr;
	double entry[] = {134713.00,-32.02342,115.96431,2800.00};
	unsigned char hex_array[4][8];

	entry_to_hex(hex_array, entry);

	for(i = 0; i < 4; i++){
		for(j = 0; j < 8; j++){
			printf("%02X ", hex_array[i][j]);
		}
		printf("\n");
	}
	
	return 0;
};

