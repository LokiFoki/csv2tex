//csv2tex

#include "csv2tex.h"
#include "csv2tex_args.h"
#include "csv2tex_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int csv2tex_debug = 0;
char csv2tex_seperator = ';';
int csv2tex_filepos_in_args = 0;

//Returns the maximum width
static inline
long
max_width (char *data, char seperator)
{
	int i = 0;
	int line_width = 0;
	int max = 0;
	while (data[i] != '\0') {
		if (data[i] == seperator) ++line_width;
		if (data[i] == '\n') {
			++line_width;
			if (line_width > max) max = line_width;
			line_width = 0;
		}
		++i;
	}
	return max;
}

//Print the data as tex code
static inline
void
print_tex (char *data, int width, char seperator)
{
	printf("\\begin{table}\n\n\\begin{tabular}{");
	
	for (int i = 0; i < width; ++i) {
		printf("|c");
	}
	
	printf("|}\n\t\\hline ");
	
	int i = 0;
	while (data[i] != '\0') {
		// "seperator" turns to &
		if (data[i] == seperator)
			printf(" & ");
		
		//newline
		else if (data[i] == '\n')
			printf(" \\\\\n\t\\hline ");
		//non of the above -> regular datafield
		else
			printf("%c", data[i]);
		++i;
	}
	
	printf("\n\\end{tabular}\n\\end{table}\n");
}

int
main (int argc, char *argv[])
{
	char *data = NULL;
	int width;
	
	int read_args_return = read_args(argc, argv);
	
	if (read_args_return == 0)
		return EXIT_FAILURE;
	if (read_args_return == -1)
		return EXIT_SUCCESS;
	
	//So was there a fileaddress in the arguments?
	if (csv2tex_filepos_in_args == 0) {
		fprintf(stderr, "Error: No file specified.\nType 'csv2tex -h' for help.\n");
		return EXIT_FAILURE;
	}
	
	//Load that file
	data = load_file(argv[csv2tex_filepos_in_args]);
	if (data == NULL)
		return EXIT_FAILURE;
	
	//DEBUGMODE 2
	//output of the unchanged file
	if (csv2tex_debug >= 2)
		printf("Printing file:\n%s\n", data);
	
	//Whats the width/number of column
	width = max_width(data, csv2tex_seperator);
	
	//It's zero. wat
	if (!width) {
		fprintf(stderr, "Error: Expected some %c\n", csv2tex_seperator);
		return EXIT_FAILURE;
	}
	
	if (csv2tex_debug >= 1) printf("*Debug* Width = %d.\n", width);
	
	//This is where the magic happens
	print_tex(data, width, csv2tex_seperator);
	
	return EXIT_SUCCESS;
}
