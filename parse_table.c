#include "parse_table.h"


void make_table(char * p_table[128][128], ff * sets, node ** G, int n, int _n){
    for(int i = 0; i < n; i++){
        // For each 'production' A -> alpha (where A -> alpha|beta are two diff productions)
        // Do the following:
        // 1.   For each terminal a in FIRST(alpha), 'add' A->alpha to M[A,a] 
        // 2.   If eps in FIRST(alpha) : For each terminal b in FOLLOW(A), 'add' A->alpha to M[A,b]
        //      If eps in FIRST(alpha) && $ in FOLLOW(A) : 'add' A->alpha to M[A,$]
        // 3.   Let remaining M[A,a] = NULL to signify error; 

        char A = G[i]->s[0].data;
        node * p = G[i]->next;
        while(p){
            int m = p->n;
            sym * s = p->s;
            //  1.1 Find alpha
            char alpha[100]; 
            for(int j = 0; j < m; j++){
                alpha[j] = s[j].data;
            }
            alpha[m] = '\0';
            //  1.2 Find FIRST(ALPHA) : FIRST(ALPHA) if eps not present ELSE FIRST(A) U FIRST(ALPHA')
            char_set f_alpha = iterative_union_first(alpha, sets, m, _n);
            //  1.3 For each terminal a in FIRST(alpha), 'add' A->alpha to M[A,a]
            char * prod = create_parse_prod(A, alpha, m);
            if(alpha[0] != eps){
                for(int a = 0; a < 128; a++){
                    if(f_alpha.items[a] == 1) {
                        p_table[A][a] = prod;
                    }
                }
            }
            //  2.1 If eps in FIRST(alpha) : For each terminal b in FOLLOW(A), 'add' A->alpha to M[A,b]
            if(f_alpha.items[eps]){
                int idx = existing_set(sets, A, _n);
                if(idx == -1 ) printf("Error in %c follow set", A);
                char_set follow_A = access_follow(sets, idx);

                for(int b = 0; b < 128; b++){
                    if(follow_A.items[b] == 1) {
                        if(p_table[A][b]==NULL) p_table[A][b] = prod;
                        //printf("hello\n");
                    }
                }
            //  2.2
                if(follow_A.items['$']){
                    if(p_table[A]['$']==NULL) p_table[A]['$'] = prod;
                }
            }

            
            p = p->next;
        }
            //  3
     }
}

void print_table(char * p_table[128][128]){
    for(int i = 0; i < 128; i ++){
        for(int j = 0; j < 128; j++){
            if(p_table[i][j] != NULL) printf("(%c, %c) : %s\n", i, j, p_table[i][j]);
        }
    }
}

void table_destructor(char * p_table[128][128]){
    char * freed_addr[128*128];
    int count = 0;
    for(int i = 0; i < 128; i ++){
        for(int j = 0; j < 128; j++){
            if(p_table[i][j] != NULL) {
                char *addr = p_table[i][j];

                // Check if this address was already freed
                int freed = 0;
                for(int k = 0; k < count; k++) {
                    if(freed_addr[k] == addr) {
                        freed = 1;
                        break;
                    }
                }

                if(!freed) {
                    free(addr);
                    freed_addr[count++] = addr;
                }

                p_table[i][j] = NULL;
            }
        }
    }
}