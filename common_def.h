#ifndef common_def
#define common_def
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define g_sz 1000
#define eps '#'


typedef struct symbol{
    char type;
    char data;
}sym;

typedef struct Node{
    int n;
    sym s[100];
    struct Node *next;
}node;

typedef struct grammar{
    node **G;
    int n;
}gramm;





#endif