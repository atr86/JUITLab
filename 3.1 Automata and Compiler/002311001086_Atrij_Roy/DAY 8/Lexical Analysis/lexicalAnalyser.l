%{
#include <stdio.h>
#include <string.h>

#define MAX_SYMBOLS 1000
#define MAX_TOKEN_LEN 100

char symbol_table[MAX_SYMBOLS][MAX_TOKEN_LEN];
int symbol_count = 0;

int token_count = 0;

int is_in_symbol_table(const char* id) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i], id) == 0) {
            return 1;
        }
    }
    return 0;
}

void add_symbol(const char* id) {
    if (!is_in_symbol_table(id) && symbol_count < MAX_SYMBOLS) {
        strcpy(symbol_table[symbol_count], id);
        symbol_count++;
    }
}

%}


KEYWORD  break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while


ID       [a-zA-Z_][a-zA-Z0-9_]*


NUMBER   [0-9]+

%%

{KEYWORD}     { token_count++; printf("Keyword: %s\n", yytext); }

{ID}          { 
                  token_count++; 
                  add_symbol(yytext);
                  printf("Identifier: %s\n", yytext);
              }

{NUMBER}      { token_count++; printf("Number: %s\n", yytext); }

(\+|\-|\*|\/|=|;|\(|\)|\{|\}|,|<|>|==|!=|<=|>=) {
                token_count++; 
                printf("Operator/Punct: %s\n", yytext);
             }

[ \t\n]+      ;  

.             { token_count++; printf("Unknown token: %s\n", yytext); }

%%
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <source.c>\n", argv[0]);
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("fopen");
        return 1;
    }

    yyin = file;

    yylex();

    printf("\nTotal tokens: %d\n", token_count);
    printf("Symbol table (identifiers):\n");
    for (int i = 0; i < symbol_count; i++) {
        printf("%s\n", symbol_table[i]);
    }

    fclose(file);
    return 0;
}


