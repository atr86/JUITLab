variable=['S']
terminal=['a','b','']
rules=[('S','aSb'),('S','')]
start='S'

def replace_eps(string):
  for rule in rules:
    var,term = rule
    if term =='':
      string=string.replace(var,term)
  return string

if __name__ == '__main__':
  print("Enter the word")
  word=input()
  string=rules[0][1]
  print(string)
  while len(string) <= len(word):
    for rule in rules:
      var,term = rule
      for ch in string:
        if ch == var and term!='':
          string = string.replace(var,term)
          print(string)

  string=replace_eps(string)
  print("Original word",word,"\nNearest Generated word",string)
  print("CFG can generate original word?",string==word)