#include "common_def.h"


int max(int a, int b){
    if(a>b) return a;
    return b;
}

int find_index(char nt, node ** G,  int n){
    for(int i = 0; i < n; i ++){
        if(G[i]->s[0].data == nt) {
            return i;
        }
    }
    return -1;
}

node * create_node(sym *sym, int n){

    node * p = (node*) malloc(sizeof(node ));
    for(int i = 0; i < n; i++){
        p->s[i] = sym[i];
    }
    p->n = n;
    p->next = NULL;
    return p;
}

char * create_parse_prod(char nt, char * alpha, int n){
    char * prod = (char*)(malloc(sizeof(char) *(n+3)));
    prod[0] = nt;
    prod[1] = ':';
    for(int i = 0; i < n; i++){
        prod[i+2] = alpha[i];
    }
    prod[n+2] = '\0';
    return prod;
}

void add_prod(node * p, sym * sym, int n){
    node * q = p;
    while( q->next ) q = q->next;
    q->next = create_node(sym, n);
}

void traverse(node * p){
    for(int i = 0; i < p->n; i++){
        printf("(%c, %c)", p->s[i].data, p->s[i].type);
    }
    
    if(p->next) {
        printf(" | ");
        traverse(p->next);
    }
    else printf("\n");
}

void traverse_helper(node ** G, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < G[i]->n; j++){
            printf("(%c, %c) : ", G[i]->s[j].data, G[i]->s[j].type);
        }
        traverse(G[i]->next);
    }
}

void g_destructor(node * p){
    if(p->next) g_destructor(p->next);
    free(p);
}
void grammar_destructor(node ** G, int n){
    for(int i = 0; i < n; i++){
        g_destructor(G[i]);
    }
    free(G);
}