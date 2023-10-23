#ifndef stackH
#define stackH
#include <stdio.h>
#include <stdlib.h>

struct STACK{
    char * items;
    int top;
    int capacity;
}typedef stack;

void initialize_stack(stack *st, int init_cap);
int is_empty(stack * st);
void resize_stack(stack *st);
void push(stack *st, char item);
char pop(stack *st);
char peek(stack * st);
void destroy_stack(stack *st);

#endif