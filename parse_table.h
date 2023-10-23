#ifndef parse_table
#define parse_table
#include "first_follow.h"
#include "helpers.h"
void make_table(char * p_table[128][128], ff * sets, node ** G, int n, int m);
void print_table(char * p_table[128][128]);
void table_destructor(char * p_table[128][128]);
#endif