//csv2texcommandline

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv2tex.h"
#include "csv2tex_args.h"

static const char *helptext = "csv2tex - convert csv-data to .tex-compatible tables. \n "
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

//returns
//	0:Failure
//	1:Success
// -1:Help wanted
int read_args(int argc, char* argv[])
{
	static struct option getoptions[] = {
		{"help", no_argument, NULL, 'h'},
		{"seperator", required_argument, NULL, 's'},
		{0, 0, 0, 0}
	};
	
	int option_index = 0;
	
	int opt;
	opt = getopt_long(argc, argv, "s:h", getoptions, &option_index);
	
	while (opt != -1) {
		switch (opt) {
		case 'h':
			printf("%s",helptext);
			return -1;
			break;
		
		case 's':
			printf("bla");
			if (!strcmp(optarg, "and"))
				csv2tex_seperator = '&';
			else if(!strcmp(optarg, "space"))
				csv2tex_seperator = ' ';
			else
				csv2tex_seperator = *optarg;
			break;
		
		case '?':
			fprintf(stderr, "Unknown error.");
			break;
			
		default:
			abort();
		}
		
		opt = getopt_long(argc, argv, "s:h", getoptions, &option_index);
	}
	
	if (option_index < argc)
		csv2tex_filepos_in_args = option_index + 1;
	
	return 1;
}
