//csv2tex file loader HEADER

#include "csv2tex.h"
#include "csv2texfileloader.h"
#include <stdio.h>
#include <stdlib.h>

//Returns file length in byte
static inline
long
getSize (FILE *file)
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
char*
loadFile (char* address)
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

	long newlinecount = 0;
	for (int i = 0; i < length; ++i) {
		rv[i] = getc(file);
		//Detect '\r' and ignore it
		if (rv[i] == '\r'){
			++newlinecount;
			--i;
		}
	}
	rv[length-newlinecount] = '\0';
	
	fclose(file);
	
	return rv;
}

