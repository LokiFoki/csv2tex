//csv2texcommandline

#include "csv2tex.h"
#include "csv2tex_args.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//returns
//	0:Failure
//	1:Success
// -1:Help wanted
int read_args(int argc, char* argv[])
{
	//Help needed?
	const char * helptext = "csv2tex - convert csv-data to .tex-compatible tables. \n "
							"Usage: csv2tex [-s 'SEPARATORCHAR'] [-d 1/2] PATH/TO/FILE.csv\n\n"
							
							"Options:\n"
							"-d, -debug :\tDebugmode offers more information about\n"
							"\t\tfile access and other suboperations.\n"
							"\t\tHigher number for more information.\n"

							"-s,seperator : \tChose which character separates datafields in your .csv file\n"
							"\t\t(e.g. 3;5;8 vs. 7-13-9)\n"
							"\t\tFor symbols misinterpreted by console:\n"
							"\t\t\t\"and\" for '&',\n"
							"\t\t\t\"space\" for ' '"
							"\n"
							"Maintained by ::::::\n"
							"Enjoy!\n";
	
	if (argc == 2 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))) {
		printf("%s",helptext);
		return -1;
	}
	
	//Reading command line arguments
	for (int i = 1; i < argc; ++i) {
	
		//debug mode
		//0 normal, 1 some, 2 EXTREME DEBUG(tm)
		if (!strcmp(argv[i], "--debug") || !strcmp(argv[i], "-d")) {
			csv2tex_debug = atoi(argv[++i]);
			if (!csv2tex_debug || i >= argc) {
				fprintf(stderr, "Error: -debug [value] needs value 1 or 2.\n");
				return 0;
			}
			
			printf("*Debug* Debug mode %d activated.\n", csv2tex_debug);
		}
		
		//Specify seperator used in csv
		//todo: add alternatives for misinterpreted symbols
		else if (!strcmp(argv[i], "--seperator") || !strcmp(argv[i], "-s")) {
			++i;
			if (i < argc) {
				//& is misinterpreted by console, use "and" instead
				if (!strcmp(argv[i], "and")) csv2tex_seperator = '&';
				else if(!strcmp(argv[i], "space")) csv2tex_seperator = ' ';
				else csv2tex_seperator = *argv[i];
			} else {
				printf("Error: -seperator [char] needs char.\n");
				return 0;
			}
		}
		
		//I dont know what it is... it must be the file
		else if (csv2tex_filepos_in_args == 0) {
			csv2tex_filepos_in_args = i;
		}
		
		//Oh noes, i cant handle multiple files
		else {
			fprintf(stderr, "Error: Processing of multiple files not allowed.\n");
			return 0;
		}
	}
	
	return 1;
}
