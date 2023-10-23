#include "_stack.h"

void initialize_stack(stack *st, int init_cap) {
    st->items = (char *)malloc(init_cap * sizeof(char));
    if (!st->items) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    st->top = -1;
    st->capacity = init_cap;
}
int is_empty(stack * st){
    if (st->top == -1) {
        return 1;
    }
    return 0;
}

void resize_stack(stack *st) {
    int new_capacity = st->capacity * 2;
    char *new_items = (char *)realloc(st->items, new_capacity * sizeof(char));
    if (!new_items) {
        printf("Memory allocation failed during resize!\n");
        exit(1);
    }
    st->items = new_items;
    st->capacity = new_capacity;
}


void push(stack *st, char item) {
    if (st->top == st->capacity - 1) {
        resize_stack(st);
    }
    st->items[++st->top] = item;
}




char pop(stack *st) {
    if (is_empty(st)) {
        printf("stack underflow!\n");
        exit(1);
    }
    return st->items[st->top--];
}


char peek(stack * st) {
    if (is_empty(st)) {
        printf("Stack is empty\n");
        return 1;
    }
    return st->items[st->top];
}


void destroy_stack(stack *st) {
    free(st->items);
}