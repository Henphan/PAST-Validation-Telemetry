#include "../src/crc_algorithm.h"
#include <stdint.h>

typedef struct {
	uint8_t* message;
	int length;
	uint16_t expected;
} crc_tests_t;

int compare_crc(uint8_t* message, int length, uint16_t expected);

int main(void){
	crc_tests_t tests[] = {
		{(uint8_t *)"", 0, 0xFFFF},
		{(uint8_t *)"A", 1, 0xB915},
		{(uint8_t *)"123456789", 9, 0x29B1}
	};
	size_t num_tests = sizeof(tests) / sizeof(tests[0]);
	for(int i = 0; i < num_tests; i++){
		if(compare_crc(
			tests[i].message,
			tests[i].length,
			tests[i].expected
		)) printf("Test %d: Passed\n", i);
		else printf("Test %d: Failed\n", i);
	}
	return 0;
}

int compare_crc(uint8_t* message, int length, uint16_t expected){
	int bool = 0;
	if(crc16(message, length) == expected) bool = 1;
	return bool;
}
