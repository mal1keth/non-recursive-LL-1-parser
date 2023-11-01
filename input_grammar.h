#ifndef INP_GRAMMAR
#define INP_GRAMMAR

#include "common_def.h"
#include "helpers.h"

char ** read_file(char * path, int * line_count);
gramm input(node ** G);

#endif