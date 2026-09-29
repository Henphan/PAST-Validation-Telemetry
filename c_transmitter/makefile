# As per https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
CC = gcc
TARGET = out/program 
OBJS = src/gnss_data.o src/binary_conversion.o src/crc_algorithm.o src/main.o 
DEPS = src/gnss_data.h src/binary_conversion.h src/crc_algorithm.h

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

# NOTE: Perhaps the repetitiveness can be reduced 
TEST_OBJS = src/gnss_data.o src/binary_conversion.o src/crc_algorithm.o 

test_crc: $(TEST_OBJS)
	$(CC) -o out/test $^ tests/crc_tests.c
	./out/test

clean:
	rm -f src/*.o out/*
