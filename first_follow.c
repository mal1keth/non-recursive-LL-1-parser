#include "first_follow.h"

extern int is_nonterm(char t);

char_set union_first(char_set s1, char_set s2){
    for(int i = 0; i < 128; i++){
        if(s2.items[i]) s1.items[i] = 1;
    }
    return s1;
}

char_set iterative_union_first(char * alpha, ff* sets, int m, int n){
    char_set un, tmp;

    for(int i = 0; i < 128; i++) {
        un.items[i] = 0;
        tmp.items[i] = 0;
    }

    for(int i = 0; i < m; i++){
        // Putting this at the top ensures that the last non-terminal can have epsilon
        if(alpha[i] == eps){
            un.items[eps] = 1;
            return un;
        }
        if(un.items[eps] == 1){
            un.items[eps] = 0;
        }

        int idx = existing_set(sets, alpha[i], n);
        if(idx == -1) printf("Error with %c\n in FIRST\n",alpha[i]);
        tmp = access_first(sets, idx);
        un = union_first(un, tmp);
        if(un.items[eps] == 0) break;
    }
    return un;
}

char_set access_follow(ff* sets, int i){
    return sets[i].follow;
}

char_set access_first(ff* sets, int i){
    return sets[i].first;
}

int existing_set(ff * sets, char nt, int n){
    for(int i = 0; i < n; i ++){
        if(sets[i].non_terminal == nt){
            return i;
        }
    }
    return -1;
}
char_set compute_first(char nt, node ** G, int n){
    int ind = find_index(nt, G, n);
    char_set s;
    for(int i = 0; i < 128; i++) s.items[i] = 0;
    if(ind == -1){
        printf("Error, %c not found in G\n", nt);
        return s;
    }
    printf("check %c\n", nt);
    node *p = G[ind]->next;
    int eps_in = 0;
    while(p){
        int m = p->n, j = 0, flag = 1;
        while(j < m && flag==1){
            char sym = p->s[j].data;
            char type = p->s[j].type;
            if(type == 'U') {
                s.items[eps] = 1;
                eps_in = 1;
                break;
            }
            else if(type == 'T') {
                s.items[sym] = 1;
                break;  // No need to check further
            }
            else{
                if(sym != nt){
                    char_set t = compute_first(sym, G, n);
                    for(int i = 0 ; i < 128; i++){
                        if(t.items[i] && i!=eps) s.items[i] = 1;
                    }
                    if(t.items[eps]==0) flag = 0;
                }
            }
            j++;
        }
        p = p->next;
    }
    return s;
}

char_set compute_follow(ff * sets, char nt, node ** G, int n){
    char_set s;
    for(int i = 0; i < 128; i++) {
        s.items[i] = 0;
    }
    
    if(nt == G[0]->s[0].data ) s.items['$'] = 1;
    
    for(int ind = 0; ind < n; ind++){
        
        char parent = G[ind]->s[0].data;
        node *p = G[ind]->next;
        while(p){
            int m = p->n, j = 0;
            while(j < m){
                char sym = p->s[j].data;
                if(sym == nt){
                    int flag = 1;
                    while(flag && j+1 < m) {
                        char nxt = p->s[j+1].data;
                        char type = p->s[j+1].type;
                        if(type == 'T'){
                            s.items[nxt] = 1;
                            flag = 0;
                        }
                        else{
                            char_set t = compute_first(nxt, G, n);
                            for(int i = 0 ; i < 128; i++){
                                if(t.items[i] && i != eps) {
                                    s.items[i] = 1;
                                }
                            }
                            if(t.items[eps] == 0) flag = 0;
                        }
                        j++;
                    }
                    if(flag){
                        char_set t;
                        int i = existing_set(sets, parent, n);
                        if(i == -1) t = compute_follow(sets, parent, G, n);
                        else t = access_follow(sets, i);
                       
                        for(i = 0 ; i < 128; i++){
                            if(t.items[i] == 1) {
                                s.items[i] = 1;
                            }
                        }
                    }
                }
                j++;
            }
            p = p->next;
        }
    }
    return s;
}

void compute_first_all(ff * sets, node **G, int n){
    for(int i = 0; i < n; i++){
        char nt = G[i]->s[0].data;
        printf("%c\n", nt);
        char_set fs = compute_first(nt, G, n);
        sets[i].non_terminal = nt;
        sets[i].first = fs;
    }
}
void compute_follow_all(ff * sets, node **G, int n){
    for(int i = 0; i < n; i++){
        char nt = G[i]->s[0].data;
        char_set fs = compute_follow(sets, nt, G, n);
        sets[i].non_terminal = nt;
        sets[i].follow = fs;
    }
}

void print_first_sets(ff * sets, int n){
    for(int i = 0; i < n; i++){
        printf("FIRST(%c): {",sets[i].non_terminal);
        int flag = 1;
        for(int j = 0; j < 128; j++){
            if(sets[i].first.items[j] == 1){
                if(flag) printf("%c", j);
                else printf(", %c", j);
                flag = 0;
            }
        }
        printf("}\n");
    }
}
void print_follow_sets(ff * sets, int n){
    for(int i = 0; i < n; i++){
        printf("FOLLOW(%c): {",sets[i].non_terminal);
        int flag = 1;
        for(int j = 0; j < 128; j++){
            if(sets[i].follow.items[j] == 1) {
                if(flag) printf("%c", j);
                else printf(", %c", j);
                flag = 0;
            }
        }
        printf("}\n");
    }
}