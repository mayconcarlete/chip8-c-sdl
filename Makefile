CC=gcc
CFLAGS= -g -w -Wall
INCLUDE= -I ./include

compile_chip8_memory_tests: compile_chip8_memory
	$(CC) $(CFLAGS) $(INCLUDE) ./test/Chip8MemoryTest.c -o ./bin/Chip8MemoryTest ./bin/Chip8Memory.o

compile_chip8_memory:
	$(CC) $(CFLAGS) $(INCLUDE) -c ./src/Chip8Memory.c -o ./bin/Chip8Memory.o 
	
clean:
	rm -f ./bin/*