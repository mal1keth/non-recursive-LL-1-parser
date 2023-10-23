#ifndef PARSER_H
#define PARSER_H
#include "common_def.h"
#include "_stack.h"
#include <string.h>


int predictive_parsing(char * s, char * p_table[128][128]);

#endif