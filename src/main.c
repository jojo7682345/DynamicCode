#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

int main(){

	// load in binary file
	FILE* file = fopen("function.bin", "rb");
	if(file==NULL){
		printf("failed to open file");
		return 1;
	}
	
	// get file size
	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	fseek(file, 0, SEEK_SET);


	// allocate memory for the dynamic function and cast it to a function pointer
	int (*funcMem)() = (int(*)()) mmap(NULL, size, PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if(funcMem==MAP_FAILED){
		printf("failed mmap\n");
		return 1;
	}
	
	// read the function into the allocated memory
	fread(funcMem, size, 1, file);	
	
	fclose(file);
	
	// set the memory to executable
	mprotect(funcMem, size, PROT_EXEC);
	
	// call the dynamic function
	int value = funcMem();
	
	// unmap the memory
	munmap(funcMem, size);

	// print the result
	printf("%i\n", value);

	return 0;

}

