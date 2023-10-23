#ifndef first_follow
#define first_follow
#include "common_def.h"
#include "helpers.h"



typedef struct {
    char items[128];
} char_set;

typedef struct {
    char non_terminal;  
    char_set first;
    char_set follow;
} ff;

char_set union_first(char_set s1, char_set s2);
char_set iterative_union_first(char * alpha, ff* sets, int m, int n);
char_set access_first(ff* sets, int i);
int existing_set(ff * sets, char nt, int n);
char_set access_follow(ff* sets, int i);
char_set compute_first(char nt, node ** G, int n);
char_set compute_follow(ff * sets, char nt, node ** G, int n);
void compute_first_all(ff * sets, node **G, int n);
void compute_follow_all(ff * sets, node **G, int n);
void print_first_sets(ff * sets, int n);
void print_follow_sets(ff * sets, int n);

#endif