#include "parser.h"
extern int is_nonterm();

int predictive_parsing(char * s, char * p_table[128][128]){
    stack * st = (stack*)malloc(sizeof(stack));

    // Setting up stack
    initialize_stack(st, 10);
    push(st, '$');
    push(st, 'S');

    int i = 0, ret = 1;
    while(is_empty(st) == 0){
        char X = peek(st);
        char * prod = p_table[X][s[i]];
        if(X == s[i]){
            pop(st);
            i++;
            printf("%c ", X);
        }
        else if(is_nonterm(X)){
            if (prod == NULL) {
                printf("(%c, %c) production doesn't exist in parse table\n", X, s[i]);
                ret = 0;
                break;
            }
            // Pop X, the non-terminal, from the stack.
            pop(st);
            
            if(prod[2] == eps) {
                printf("%c -> eps, ", X);
                continue;
            }
            else printf("%c -> ", X);
            int len = strlen(prod);
            for(int j = len - 1; j >= 2; j--){
                push(st, prod[j]);
            }
        }
        else {

            printf("Error parsing %c\n", X);
            ret = 0;
            break;
        }
    }
    
    // If the string is not fully parsed or the stack isn't at its start symbol, then parsing failed.
    if(ret && (s[i-1] != '$' || !is_empty(st))) {
        ret = 0;
    }
    printf("\n");
    destroy_stack(st);
    free(st);
    return ret;
}