//csv2tex

#include "csv2tex.h"
#include "csv2texfileloader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int debug = 0;

//Returns the maximum width
long maxWidth(char *data, char seperator) {
	int i = 0;
	int tempmax = 0;
	int max = 0;
	while (data[i] != '\0') {
		if (data[i] == seperator) ++tempmax;
		if (data[i] == '\n') {
			++tempmax;
			if (tempmax > max) max = tempmax;
			tempmax = 0;
		}
		++i;
	}
	return max;
}

//Print the data as tex code
void printTex(char *data, int width, char seperator) {
	
	printf("\\begin{table}[H]\n\n\\begin{tabular}{");
	
	for (int i = 0; i < width; ++i) {
		printf("|c");
	}
	
	printf("|}\n\t\\hline ");
	
	int i = 0;
	while (data[i] != '\0') {
		// "seperator" turns to &
		if (data[i] == seperator) printf(" & ");
		
		/*
		NOT NEEDED SINCE ITS HANDLED IN THE FILELOADER NOW
		//windows end of line is \r\n, so skip the \n
		else if (data[i] == '\r') {
			printf(" \\\\\n\t\\hline ");
			++i;
		}
		*/
		
		//newline
		else if (data[i] == '\n') printf(" \\\\\n\t\\hline ");
		
		//non of the above -> regular datafield
		else printf("%c", data[i]);
		++i;
	}
	
	printf("\n\\end{tabular}\n\n\\caption{Tabelle}\n\n\\end{table}\n");
}

int main(int argc, char *argv[])
{
	char *data = NULL;
	int filepos = 0;
	int width;
	char seperator = ';';
	
	//Help needed?
	if (argc == 2 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "-help"))) {
		printf("todo: write help text ;)\n");
		return EXIT_SUCCESS;
	}
	
	//Reading command line arguments
	for (int i = 1; i < argc; ++i) {
	
		//debug mode
		//0 normal, 1 some, 2 EXTREME DEBUG(tm)
		if (!strcmp(argv[i], "-debug") || !strcmp(argv[i], "-d")) {
			debug = atoi(argv[++i]);
			if (!debug || i >= argc) {
				fprintf(stderr, "Error: -debug [value] needs value 1 or 2.\n");
				return EXIT_FAILURE;
			}
			
			printf("*Debug* Debug mode %d activated.\n", debug);
		}
		
		//Specify seperator used in csv
		//todo: add alternatives for misinterpreted symbols
		else if (!strcmp(argv[i], "-seperator") || !strcmp(argv[i], "-s")) {
			++i;
			if (i < argc) {
				//& is misinterpreted by console, use "and" instead
				if (!strcmp(argv[i], "and")) seperator = '&';
				else seperator = *argv[i];
			} else {
				printf("Error: -seperator [char] needs char.\n");
				return EXIT_FAILURE;
			}
		}
		
		//I dont know what it is... it must be the file
		else if (filepos == 0) {
			filepos = i;
		}
		
		//Oh noes, i cant handle multiple files
		else {
			fprintf(stderr, "Error: Processing of multiple files not allowed.\n");
			return EXIT_FAILURE;
		}
	}
	
	//So was there a fileaddress in the arguments?
	if (filepos == 0) {
		fprintf(stderr, "Error: No file specified.\n");
		return EXIT_FAILURE;
	}
	
	//Load that file
	data = loadFile(argv[filepos]);
	
	//Didnt work lol
	if (data == NULL) {
		return EXIT_FAILURE;
	}
	
	//DEBUGMODE 2
	//output of the unchanged file
	if (debug >= 2) {
		printf("Printing file:\n%s\n", data);
	}
	
	//Whats the width/number of column
	width = maxWidth(data, seperator);
	
	//It's zero. wat
	if (!width) {
		fprintf(stderr, "Error: Expected some %c\n", seperator);
		return EXIT_FAILURE;
	}
	
	if (debug >= 1) printf("*Debug* Width = %d.\n", width);
	
	//This is where the magic happens
	
	printTex(data, width, seperator);
	
	
	
	return EXIT_SUCCESS;
}