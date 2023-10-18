CC=gcc
CFLAGS=-c -Wall -ggdb

all: test.out functions

#compile the executable
test.out: main.o
	$(CC) main.o -o test.out

#compile main.c
main.o: src/main.c
	$(CC) $(CFLAGS) src/main.c

# extract flat binary from function object file
function.bin: function.o
	$(CC) -o function.bin -Wl,-T src/function.ld function.o -nostdlib

functions: function.bin

# compile the function
function.o:
	$(CC) $(CFLAGS) src/function.c -lc

clean:
	rm *.out *.o *.bin
