#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include "function.h"



int main(){

	// load in binary file
	FILE* file = fopen("function.bin", "rb");
	if(file==NULL){
		printf("failed to open file\n");
		return 1;
	}
	
	// get file size
	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	fseek(file, 0, SEEK_SET);


	// allocate memory for the dynamic function and cast it to a function pointer
	FunctionLinker linkFunctions = (FunctionLinker) mmap(NULL, size, PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if(linkFunctions==MAP_FAILED){
		printf("failed mmap\n");
		return 1;
	}
	
	// read the function into the allocated memory
	fread(linkFunctions, size, 1, file);	
	
	fclose(file);
	
	// set the memory to executable
	mprotect(linkFunctions, size, PROT_EXEC|PROT_READ|PROT_WRITE);
	
	// call the dynamic function
	FunctionTable functions = linkFunctions();
	int value = functions.getOtherNumber();
	

	// unmap the memory
	munmap(linkFunctions, size);

	// print the result
	printf("%i\n", value);

	return 0;

}

