//csv2tex file loader HEADER

#include "csv2tex.h"
#include <stdio.h>
#include <stdlib.h>

long getSize(FILE *file)
{
	long pos = ftell(file);
	long rv;
	
	fseek(file, 0L, SEEK_END);
	rv = ftell(file);
	fseek(file, pos, SEEK_SET);
	
	return rv;
}


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
	
	for (int i = 0; i<length; ++i) {
		rv[i] = getc(file);
	}
	
	rv[length] = '\0';
	
	fclose(file);
	
	return rv;
}

