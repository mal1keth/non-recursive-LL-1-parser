#ifndef helpers
#define helpers
#include "common_def.h"

node * create_node(sym *sym, int n);
char * create_parse_prod(char nt, char * alpha, int n);
void add_prod(node * p, sym *sym, int n);
void traverse(node * p);
void traverse_helper(node ** G, int n);
void g_destructor(node * p);
void grammar_destructor(node ** G, int n);
int max(int a, int b);
int find_index(char nt, node ** G,  int n);
#endif