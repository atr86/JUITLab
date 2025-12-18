import ply.lex as lex
import ply.yacc as yacc

# =============================
#           LEXER
# =============================

tokens = ['NUMBER', 'PLUS', 'MINUS']

t_PLUS  = r'\+'
t_MINUS = r'-'

def t_NUMBER(t):
    r'\d+'
    t.value = int(t.value)
    return t

t_ignore = " \t"

def t_error(t):
    print("Illegal character:", t.value[0])
    t.lexer.skip(1)

lexer = lex.lex()


# =============================
#           PARSER
# =============================
def p_expression_plus(p):
    'expression : expression PLUS term'
    p[0] = p[1] + p[3]

def p_expression_minus(p):
    'expression : expression MINUS term'
    p[0] = p[1] - p[3]

def p_expression_term(p):
    'expression : term'
    p[0] = p[1]

def p_term_number(p):
    'term : NUMBER'
    p[0] = p[1]

def p_error(p):
    print("Syntax error!", p)

parser = yacc.yacc()


# =============================
#        MAIN EXECUTION
# =============================

print("Grammar that this parser accepts:")
print("expression : expression PLUS term")
print("expression : expression MINUS term")
print("expression: term")
print("term : NUMBER")

print("\nEnter a mathematical expression with numbers, plus and minus (e.g., 3 + 5 - 2):")
expr = input("Expression: ")
print("Input:", expr)

result = parser.parse(expr)
print("Result:", result)
