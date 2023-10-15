CC=gcc
CFLAGS=-c -Wall

all: test.out function.bin

#compile the executable
test.out: main.o
	$(CC) main.o -o test.out

#compile main.c
main.o: src/main.c
	$(CC) $(CFLAGS) src/main.c

# extract flat binary from function object file
function.bin: function.o
	objcopy -O binary -j .text function.o function.bin

# compile the function
function.o:
	$(CC) $(CFLAGS) src/function.c
 
