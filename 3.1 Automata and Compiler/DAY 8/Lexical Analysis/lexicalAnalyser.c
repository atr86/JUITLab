/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_IDENTIFIERS 1000
#define MAX_IDENTIFIER_LEN 100
#define MAX_LINE_LEN 1024

// Keywords list
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if", "int",
    "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile",
    "while", NULL
};

typedef enum {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_CONSTANT,
    TOKEN_OPERATOR,
    TOKEN_PUNCTUATOR
} TokenType;

typedef struct {
    char lexeme[MAX_IDENTIFIER_LEN];
} Identifier;

// Symbol table
Identifier symbol_table[MAX_IDENTIFIERS];
int symbol_count = 0;

// Store lexical errors
typedef struct {
    int line;
    char msg[256];
} LexError;

LexError errors[1000];
int error_count = 0;

// Token count
int token_count = 0;

// Check if a string is a keyword
int is_keyword(const char *str) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

// Check if identifier is already in symbol table
int is_in_symbol_table(const char *id) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].lexeme, id) == 0)
            return 1;
    }
    return 0;
}

// Add identifier to symbol table if unique
void add_symbol(const char *id) {
    if (!is_in_symbol_table(id) && symbol_count < MAX_IDENTIFIERS) {
        strncpy(symbol_table[symbol_count].lexeme, id, MAX_IDENTIFIER_LEN);
        symbol_table[symbol_count].lexeme[MAX_IDENTIFIER_LEN-1] = '\0';
        symbol_count++;
    }
}

// Check if a character can start an identifier (letter or _)
int is_id_start(char c) {
    return (isalpha(c) || c == '_');
}

// Check if a character can be part of an identifier (letter, digit, _)
int is_id_char(char c) {
    return (isalnum(c) || c == '_');
}

// Check if a character is an operator character
int is_operator_char(char c) {
    const char ops[] = "+-*/%=!<>&|^~";
    for (int i = 0; ops[i]; i++) {
        if (c == ops[i])
            return 1;
    }
    return 0;
}

// Check if a character is a punctuator
int is_punctuator_char(char c) {
    const char punc[] = "();{},[]";
    for (int i = 0; punc[i]; i++) {
        if (c == punc[i])
            return 1;
    }
    return 0;
}

// Add lexical error
void add_error(int line, const char *msg) {
    if (error_count < 1000) {
        errors[error_count].line = line;
        strncpy(errors[error_count].msg, msg, 255);
        errors[error_count].msg[255] = '\0';
        error_count++;
    }
}

// Lexical analyzer for one line
void analyze_line(const char *line, int lineno) {
    int i = 0;
    int len = strlen(line);

    while (i < len) {
        // Skip whitespace
        if (isspace(line[i])) {
            i++;
            continue;
        }

        // Handle single-line comments: //
        if (line[i] == '/' && (i+1 < len) && line[i+1] == '/') {
            // Comment till end of line - ignore rest
            break;
        }

        // Identifier or keyword
        // Keyword or identifier
        if (is_id_start(line[i])) {
            int start = i;
            i++;
            while (i < len && is_id_char(line[i])) i++;
        
            int tok_len = i - start;
            if (tok_len >= MAX_IDENTIFIER_LEN) {
                add_error(lineno, "Identifier too long");
                continue;
            }
        
            char token[MAX_IDENTIFIER_LEN];
            strncpy(token, line + start, tok_len);
            token[tok_len] = '\0';
        
            if (is_keyword(token)) {
                token_count++;
                printf("Token: %-15s → Keyword\n", token);
            } else {
                token_count++;
                printf("Token: %-15s → Identifier\n", token);
                add_symbol(token);
            }
            continue;
        }


        // Numeric constants (only integer constants here)
        // Numeric constants
        if (isdigit(line[i])) {
            int start = i;
            while (i < len && isdigit(line[i])) i++;
        
            int tok_len = i - start;
            char token[64];
            if (tok_len > 63) {
                add_error(lineno, "Numeric constant too long");
                continue;
            }
        
            strncpy(token, line + start, tok_len);
            token[tok_len] = '\0';
        
            token_count++;
            printf("Token: %-15s → Constant\n", token);
            continue;
        }


        // Operators (handle multi-char ops ==, !=, <=, >=, &&, ||)
       // Operators
        if (is_operator_char(line[i])) {
            char op[3] = {0};
            op[0] = line[i];
        
            if (i+1 < len) {
                char next = line[i+1];
                if ((op[0] == '=' && next == '=') ||
                    (op[0] == '!' && next == '=') ||
                    (op[0] == '<' && next == '=') ||
                    (op[0] == '>' && next == '=') ||
                    (op[0] == '&' && next == '&') ||
                    (op[0] == '|' && next == '|')) {
                    op[1] = next;
                    op[2] = '\0';
                    i += 2;
                    token_count++;
                    printf("Token: %-15s → Operator\n", op);
                    continue;
                }
            }
        
            op[1] = '\0';
            i++;
            token_count++;
            printf("Token: %-15s → Operator\n", op);
            continue;
        }


                if (is_punctuator_char(line[i])) {
            char sep[2] = { line[i], '\0' };
            i++;
            token_count++;
            printf("Token: %-15s → Separator\n", sep);
            continue;
        }


        char err_msg[100];
        snprintf(err_msg, sizeof(err_msg), "Invalid symbol '%c'", line[i]);
        add_error(lineno, err_msg);
        i++;

    }
}

int main() {
    char line[MAX_LINE_LEN];
    int lineno = 0;

        // Hardcoded input source code lines
    const char *source_code[] = {
        "int main() {",
        "    int x = 10;",
        "    int y=2;",
        "    int z=2;",
        "    // This is a comment",
        "    if (x > 5) {",
        "        x = x + 1;",
        "    }",
        "}"
    };

    int num_lines = sizeof(source_code) / sizeof(source_code[0]);

    for (int i = 0; i < num_lines; i++) {
        analyze_line(source_code[i], i + 1);
    }


    // 1) Print lexical errors
    if (error_count == 0) {
        printf("No lexical errors.\n");
    } else {
        printf("Lexical Errors:\n");
        for (int i = 0; i < error_count; i++) {
            printf("Line %d: %s\n", errors[i].line, errors[i].msg);
        }
    }
    printf("\n");

    // 2) Print symbol table
    printf("Symbol Table (Unique Identifiers):\n");
    if (symbol_count == 0) {
        printf("No identifiers found.\n");
    } else {
        for (int i = 0; i < symbol_count; i++) {
            printf("%s\n", symbol_table[i].lexeme);
        }
    }
    printf("\n");

    // 3) Print total token count
    printf("Total tokens: %d\n", token_count);

    return 0;
}
