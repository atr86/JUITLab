v=['S']
t=['a','b','']
rules=[('S','aaSb'),('S','aaa')]
start='S'

def generate1(state, goal):

  visited=[]

  queue=[(state)]
  while queue:
    state=queue.pop(0)
    if state not in visited:
      visited.append(state)
    else:
      continue
    if state==goal:
      return True
    for rule in rules:
      variable,terminal=rule
      for i in range(0,len(state)):
        if state[i]==variable:
            queue.append(state[0:i]+terminal+state[i+1:])
if __name__ == '__main__':
    print("Enter the word")
    word=input()
    print("CFG can generate original word?", generate1(start,word) )

