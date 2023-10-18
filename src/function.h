#ifndef __FUNCTION__
#define __FUNCTION__

#include <stdint.h>

typedef struct FunctionTable {
	int (*getNumber)();
	int (*getOtherNumber)();
	int (*add)(int, int);
} FunctionTable;

typedef FunctionTable (*FunctionLinker)();

#ifdef FUNCTION_IMPLEMENTATION

int getNumber();
int getOtherNumber();
int add(int a, int b);

void _start(void){}

FunctionTable __attribute((section(".linker"))) linkFunctions(){
	FunctionTable table = { 0 };
	table.getNumber = &getNumber;
	table.getOtherNumber = &getOtherNumber;
	table.add = &add;
	return table;
}

#endif
#endif
