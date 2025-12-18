// Simple Grammar
//E:E+T|E-T
//E:T
//T:Number

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Forward declarations
int yylex();
int yyerror(const char *s);

typedef struct node {
    char *name;
    struct node *left;
    struct node *right;
} node;

node* make_node(char *name, node *left, node *right);
void print_tree(node *root, int level);

%}


%token NUMBER
%left '+' '-'

%%

input:
      /* empty */
    | input line
    ;

line:
      expr '\n'   { printf("= %d\n", $1); }
    ;

expr:
      expr '+' expr   { $$ = $1 + $3; }
    | expr '-' expr   { $$ = $1 - $3; }
    | NUMBER          { $$ = $1; }
    ;

%%

int yyerror(const char *s) {
    printf("Error: %s\n", s);
    return 0;
}

int main() {
    return yyparse();
}

