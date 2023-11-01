#ifndef common_def
#define common_def
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_G_SZ 1000
#define MAX_PROD_SZ 128
#define eps '#'


typedef struct symbol{
    char type;
    char data;
}sym;

typedef struct Node{
    int n;
    sym s[MAX_PROD_SZ];
    struct Node *next;
}node;

typedef struct grammar{
    node **G;
    int n;
}gramm;





#endif