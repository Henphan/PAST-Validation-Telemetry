#include <stdio.h>
#include <stdlib.h>
#include "gnss_data.h"

void read_data(char* data[][4]);

int main(void){
	int i, j;
	// processing the raw data into an array of structs
	struct GNSS_Struct s_array[52];
	struct GNSS_Struct s1;
	char* endptr;
	for(i = 0; i < 52; i++){
		s1.time = strtod(raw_data[i][0], &endptr);
		s1.lat = strtod(raw_data[i][1], &endptr);
		s1.lon = strtod(raw_data[i][2], &endptr);
		s1.alt = strtod(raw_data[i][3], &endptr);
		s_array[i] = s1;
	}
	return 0;
};

