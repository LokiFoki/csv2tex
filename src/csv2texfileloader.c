//csv2tex file loader HEADER

#include "csv2tex.h"
#include "csv2texfileloader.h"
#include <stdio.h>
#include <stdlib.h>

//Returns file length in byte
long getSize(FILE *file)
{
	long pos = ftell(file);
	long rv;
	
	fseek(file, 0L, SEEK_END);
	rv = ftell(file);
	fseek(file, pos, SEEK_SET);
	
	return rv;
}

//Opens file
//Returns NULL if an error occurs and prints error message
char* loadFile(char* address)
{
	FILE *file;
	
	file = fopen(address, "rb");
	
	if (file == NULL) {
		fprintf(stderr, "Error: File \"%s\" not found.\n", address);
		return NULL;
	}
	
	long length = getSize(file);
	
	if (debug >= 1) {
		printf("*Debug* File size: %ld Bytes\n", length);
	}
	
	char* rv = malloc(length + 1);
	
	//Newline in Windows: \r\n
	#ifdef _WIN32
	long newlinecount = 0;
	for (int i = 0; i<length; ++i) {
		rv[i] = getc(file);
		if (rv[i] == '\r') ++newlinecount;
	}
	rv[length-newlinecount] = '\0';
	#else
	for (int i = 0; i<length; ++i) {
		rv[i] = getc(file);
	}
	rv[length] = '\0';
	#endif
	
	fclose(file);
	
	return rv;
}

