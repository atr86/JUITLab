def getGrammar():
  print("Enter production rules of grammar, line by line, enter 1 to stop")
  rules=[]
  while(True):
    line=input()
    if line=="1":
      break
    else:
      line=line.strip()
      left,right=line.split("->")
      right=right.split("|")
      rules.append([left,right])
  return rules



def typeOfCh(rules):
  map=[]
  done=[]
  for rule in rules: # Iterate through each rule in the rules list
    lhs, _ = rule # Unpack the elements of the current rule
    if lhs not in done:
      map.append([lhs,'var'])
      done.append(lhs)
  for rule in rules: # Iterate through each rule again
    _,rhs=rule # Unpack the elements of the current rule
    for term in rhs:
      for t in term:
        if t not in done:
          map.append([t,'term'])
          done.append(t)
  return map




def getFirst(ch,rules,map,first):
#   print(f"Entering getFirst with ch: {ch}, first: {first}") # Added print statement
  f='a'
  for i in range(0,len(map)):
    if ch==map[i][0]:
      break
  if map[i][1]=='term':
    first.add(ch)
    # print(f"  {ch} is a terminal. Appending to first.",first) # Added print statement
    return ch
  else:
    # print(f"  {ch} is a variable.") # Added print statement
    for lhs,rhs in rules:
      if lhs==ch:
        # print(f"    Processing rule: {lhs} -> {rhs}") # Added print statement
        for term in rhs:
        #   print(f"      Processing term: {term}") # Added print statement
          for r in term:
            # print(f"        Calling getFirst recursively with: {r}") # Added print statement
            f=getFirst(r,rules,map,first)
            # print(f"        Recursive call returned: {f}") # Added print statement
            if f != 'e':
              break
            else:
              continue
    # print(f"  Reached end for variable {ch}. Returning 'e'.") # Added print statement
    return 'e'
  




if __name__=="__main__":
  choice=input("Enter y to take user input or use default")
if choice=='y':
  rules=getGrammar()
  ch=input("Enter character to get First set")
else:
  rules=[['S',['Ba','C']],['B', ['Azk', 'b']], ['A', ['a', 'e']],['C',['c','e']]]
  ch='S'
print(rules)
first=set()
map=typeOfCh(rules)
print(map)
print("*******************************************")
getFirst(ch,rules,map,first)
print("First Set: ",first)


