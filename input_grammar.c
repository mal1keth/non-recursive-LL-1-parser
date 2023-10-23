
#include "common_def.h"
#include "helpers.h"

char ** read_file(char * path, int * line_count){
FILE *f_p;
    char buffer[g_sz];
    f_p = fopen(path, "r");

    if (f_p == NULL) {
        fprintf(stderr, "Could not open file at %s\n", path);
        exit(EXIT_FAILURE);
    }

    *line_count = 0;
    int lines_sz = 1;
    char ** lines = (char**)(malloc(lines_sz * sizeof(char*)));
    
    
    // Read lines from the file until the end of the file is reached
    while (fgets(buffer, g_sz, f_p) != NULL) {
        if(*line_count == lines_sz){{
            lines_sz *= 2;
            lines = (char**)realloc(lines, lines_sz * sizeof(char*));
        }}
        
        lines[*line_count] = strdup(buffer);
        *line_count += 1;
    }

    // Close the file
    fclose(f_p);
    return lines;
}
gramm input(node ** G){
    int * tmp = calloc(sizeof(int), 0);
    char ** lines = read_file("./grammar.txt", tmp);
    int n = *tmp;
    G = (node**)(malloc(n * sizeof(node*)));

    for(int i = 0; i < n; i++){
        char * l = lines[i];
        int m = strlen(l);
        sym s[1];
        s[0].type = 'N';
        s[0].data = l[1];
        G[i] = create_node(s, 1);
        // Remaining N1|N2|...|Nk|T1|T2||...|Tl
        int j = 4;
        while(j < m){
            sym tmp[100];
            int _i = j, k = 0, len_prod;
            while(j < m && l[j]!='|') j++;
            
            len_prod = j - _i;
            // If there is an empty production in between say S->A||B then len_prod = 0
            // If there is one in the end, say S->A| then len_prod == 1 (reads \n) and j == m
            if((len_prod == 1 && j == m) || (len_prod == 0)){
                tmp[k].type = 'U';
                tmp[k].data = eps;
                k++;
                add_prod(G[i], tmp, k);
            }
            else{
                char nt_flag = 'T';
                for(int z = _i; z < _i + len_prod; z++){
                    if(l[z] == '\n'){

                    }
                    else if(l[z] == '<') nt_flag = 'N';
                    else if(l[z] == '>') nt_flag = 'T';
                    else{
                        tmp[k].type = nt_flag;
                        tmp[k].data = l[z];
                        k++;
                    }
                }
                add_prod(G[i], tmp, k);
            }
            // If we are at last character of the string and it is '|' (last line so possibly no \n)
            if(j == m - 1 && l[j] == '|'){
                k = 0;
                tmp[k].type = 'U';
                tmp[k].data = eps;
                k++;
                add_prod(G[i], tmp, k);
            }
            j++;
        }
        free(l);
    }
    free(lines);
    free(tmp);

    gramm g;
    g.n = n;
    g.G = G;
    return g;
}