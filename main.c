
#include "common_def.h"
#include "input_grammar.h"
#include "helpers.h"
#include "first_follow.h"
#include "parse_table.h"
#include "parser.h"
#define MAX_INP_SZ 1024


char *non_term, *term;
int n, m;
node ** G;
void find_term(ff sets[], int n){
    int z = 0;
    char_set t;
    for(int i = 0; i < 128; i++) t.items[i] = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 128; j ++){
            if((sets[i].first.items[j] || sets[i].follow.items[j]) && j!=eps) {
                t.items[j] = 1;
            }
        }
    }
    for(int i = 0; i < 128; i ++){
        if(t.items[i]) z++;
    }
    m = z;
    term = (char*)malloc(sizeof(char) * m);
    int j = 0;
    for(int i = 0; i < 128; i ++){
        if(t.items[i] && i!=eps) term[j++] = i;
    }
}
int is_nonterm(char t){
    for(int i = 0; i < n; i++){
        if(t == non_term[i]) return 1;
    }
    return 0;
}
// Sample LL(1) grammar to try
// <S>:<T><X>
// <X>:+<T><X>|-<T><X>| 
// <T>:<F><Y>
// <Y>:*<F><Y>|/<F><Y>| 
// <F>:(<S>)|<N>
// <N>:0|1|2|3|4|5|6|7|8|9

int main(){

    /* */
    
    /* */
    {
        gramm g = input(G);
        n = g.n;
        G = g.G;
    }
    printf("------------PRINT GRAMMAR------------\n");
    traverse_helper(G,n);
    printf("\n");
    ff * sets = (ff*)malloc(sizeof(ff) * n);
    for(int i = 0; i < n; i++){
        sets[i].non_terminal = 0;
    }
    non_term = malloc(sizeof(char) * n);
    for(int i = 0; i < n ; i++){
        non_term[i] = G[i]->s[0].data;
    }
    
    compute_first_all(sets, G, n);
    compute_follow_all(sets,G,n);
    
    find_term(sets, n);
    sets = (ff*)realloc(sets, (n + m)*sizeof(ff));
    for(int i = 0; i < m; i++){
        sets[n+i].non_terminal = term[i];
        sets[n+i].first.items[term[i]] = 1;
        for(int j = 0; j < 128; j++){
            sets[n+i].follow.items[j] = 0;
        }
    }

    printf("-------------FIRST SETS--------------\n");
    print_first_sets(sets, n+m);
    printf("\n");
    printf("------------FOLLOW SETS--------------\n");
    print_follow_sets(sets,n+m);
    printf("\n");

    char * p_table[128][128];
    for(int i = 0; i < 128; i ++){
        for(int j = 0; j < 128; j++){
            p_table[i][j] = NULL;
        }
    }
    // printf("-------------------------------------\n");
    make_table(p_table, sets, G, n, n+m);
    printf("------Predictive Parsing Table------\n");
    printf("\n");
    print_table(p_table);
    printf("\n");
    
    while(1){
        printf("Input String: ");
        char inp[MAX_INP_SZ];
        fgets(inp, sizeof(inp), stdin);
        {
            int p = strlen(inp);

            inp[p-1] = '\0';
            if(strcmp(inp, "exit") == 0) break;

            inp[p-1] = '$';
            inp[p] = '\0';
            p = p + 1;
        }
        printf("------------Parsing Steps------------\n");
        int ret = predictive_parsing(inp, p_table);
        if(ret){
            printf("Successfully Parsed\n");
        }
        else{
            printf("Error in Parsing\n");
        }
    }
    grammar_destructor(G,n);
    table_destructor(p_table);
    return 0;
}

