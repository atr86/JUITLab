# lexer.py
import ply.lex as lex

# ---- Token List ----
tokens = ['NUMBER', 'PLUS', 'MINUS']

# ---- Token Rules ----
t_PLUS  = r'\+'
t_MINUS = r'-'

def t_NUMBER(t):
    r'\d+'
    t.value = int(t.value)   # convert string to int
    return t

# ---- Ignore whitespace ----
t_ignore = ' \t'

# ---- Error Handling ----
def t_error(t):
    print("Illegal character:", t.value[0])
    t.lexer.skip(1)

# ---- Build Lexer ----
lexer = lex.lex()

data = input("Enter a mathematical expression with number, plus and minus: ")
lexer.input(data)

print("Tokenizing:", data)
while True:
    tok = lexer.token()
    if not tok:
        break
    print(tok)