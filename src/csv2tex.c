//csv2tex

#include "csv2tex.h"
#include "csv2texcommandline.h"
#include "csv2texfileloader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int debug = 0;
char seperator = ';';
int filepos_in_args = 0;

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
		
		//newline
		else if (data[i] == '\n'){
			if (data[i-1] == '\n') break;	//remove multiple linebreaks
			else printf(" \\\\\n\t\\hline ");
		
		//non of the above -> regular datafield
		}else printf("%c", data[i]);
		++i;
	}
	
	printf("\n\\end{tabular}\n\n\\caption{Tabelle}\n\n\\end{table}\n");
}

int main(int argc, char *argv[])
{
	char *data = NULL;
	int width;
	
	int readCommandline_return = readCommandline(argc, argv);
	
	if (readCommandline_return == 0) return EXIT_FAILURE;
	if (readCommandline_return == -1) return EXIT_SUCCESS;
	
	//So was there a fileaddress in the arguments?
	if (filepos_in_args == 0) {
		fprintf(stderr, "Error: No file specified.\nType 'csv2tex -h' for help.\n");
		return EXIT_FAILURE;
	}
	
	//Load that file
	data = loadFile(argv[filepos_in_args]);
	
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