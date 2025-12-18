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






def getFollow(ch,rules,map,follow):
  print(f"Entering get Follow with ch: {ch}, follow: {follow}") # Added print statement

  # Helper to get the type ('var' or 'term') of a character from the map list
  def _get_char_type(char_to_find, map_list):
      for item in map_list:
          if item[0] == char_to_find:
              return item[1]
      return None # Should not happen if grammar is well-formed and map is complete

  if ch=='S': # Assuming 'S' is the start symbol
    follow.add('$')

  for lhs,rhs in rules:
    for term_production in rhs: # Renamed 'term' to 'term_production' to avoid confusion with 'term' as a terminal
      # Iterate through each symbol in the current production term_production
      for i in range(0,len(term_production)):
        if term_production[i] == ch:
          # This variable tracks if epsilon can propagate all the way to the end of the current `term_production`
          epsilon_propagates_to_end = True
          
          # Check symbols immediately after 'ch' in the current production
          k = i + 1
          while k < len(term_production):
              next_sym = term_production[k]
              sym_type = _get_char_type(next_sym, map)

              if sym_type == 'term':
                  follow.add(next_sym)
                  epsilon_propagates_to_end = False # Terminal stops epsilon propagation
                  break # Stop processing symbols in this term_production
              else: # next_sym is a variable
                  firstset_of_next_sym = set()
                  # Call getFirst to find the First set of the variable
                  getFirst(next_sym, rules, map, firstset_of_next_sym)
                  
                  contains_epsilon = False
                  for f_item in firstset_of_next_sym:
                      if f_item != 'e':
                          follow.add(f_item)
                      else:
                          contains_epsilon = True # Found epsilon in First set
                  
                  if not contains_epsilon:
                      epsilon_propagates_to_end = False # Non-epsilon symbol stops propagation
                      break # Stop processing symbols in this term_production
                  else:
                      # If epsilon was found, continue to the next symbol in the production
                      k += 1
          
          # If 'ch' was the last symbol in `term_production` (i.e., k == len(term_production) after loop)
          # OR if all symbols after 'ch' could derive epsilon
          if epsilon_propagates_to_end:
              # Add Follow(LHS) to Follow(ch), but avoid direct recursion if LHS is ch
              if lhs != ch:
                  getFollow(lhs, rules, map, follow)
  return follow

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
  # Example usage
        rules = [['S', ['xXZA']], ['Z', ['z', 'e']], ['A', ['a', 'e']]]
        ch='X'
    print(rules)
    first = set()
    follow = set()
    map=typeOfCh(rules)
    print(map)
    print("*******************************************")
    getFollow(ch,rules,map,first)
    print("Follow Set: ",first)