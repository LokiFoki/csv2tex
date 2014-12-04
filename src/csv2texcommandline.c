//csv2texcommandline

#include "csv2tex.h"
#include "csv2texcommandline.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//returns
//	0:Failure
//	1:Success
//  -1:Help wanted
int readCommandline(int argc, char* argv[])
{
	//Help needed?
	if (argc == 2 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))) {
		printf("todo: write help text ;)\n");
		return -1;
	}
	
	//Reading command line arguments
	for (int i = 1; i < argc; ++i) {
	
		//debug mode
		//0 normal, 1 some, 2 EXTREME DEBUG(tm)
		if (!strcmp(argv[i], "--debug") || !strcmp(argv[i], "-d")) {
			debug = atoi(argv[++i]);
			if (!debug || i >= argc) {
				fprintf(stderr, "Error: -debug [value] needs value 1 or 2.\n");
				return 0;
			}
			
			printf("*Debug* Debug mode %d activated.\n", debug);
		}
		
		//Specify seperator used in csv
		//todo: add alternatives for misinterpreted symbols
		else if (!strcmp(argv[i], "--seperator") || !strcmp(argv[i], "-s")) {
			++i;
			if (i < argc) {
				//& is misinterpreted by console, use "and" instead
				if (!strcmp(argv[i], "and")) seperator = '&';
				else seperator = *argv[i];
			} else {
				printf("Error: -seperator [char] needs char.\n");
				return 0;
			}
		}
		
		//I dont know what it is... it must be the file
		else if (filepos_in_args == 0) {
			filepos_in_args = i;
		}
		
		//Oh noes, i cant handle multiple files
		else {
			fprintf(stderr, "Error: Processing of multiple files not allowed.\n");
			return 0;
		}
	}
	
	return 1;
}