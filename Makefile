CC=gcc
CFLAGS=-c -Wall -ggdb

all: functions test.out

#compile the executable
test.out: main.o
	$(CC) main.o -o test.out

#compile main.c
main.o: src/main.c
	$(CC) $(CFLAGS) src/main.c

# extract flat binary from function object file
function.getOtherNumber.bin: function.o
	objcopy -O binary -j .text.getOtherNumber function.o function.getOtherNumber.bin

function.add.bin: function.o
	objcopy -O binary -j .text.add function.o function.add.bin

functions: function.add.bin function.getOtherNumber.bin

# compile the function
function.o:
	$(CC) $(CFLAGS) -ffunction-sections src/function.c

clean:
	rm *.out
	rm *.o
	rm *.bin
