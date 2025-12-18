#include <iostream>
#include <set>
#include <map>


using namespace std;


// Define types for clarity
using State = set<int>;              // a state is a set of ints
using Action = int;                  // input symbols like 0 or 1
using TransitionTable = map<State, map<Action, State>>;




class nfa_dfa
{
    public:
    set<int> actionSet = {0, 1};
    
    TransitionTable d;
    set<State> state;//statespace
    State prim;//all primitive states' set - each state here is an int

    nfa_dfa()
    {
        state.insert({0});
    }

    void input()
    {
        cout<<"Enter State, Action and list of states to visit. For either case, to stop enter -1 (for state)|n";
        int s=0;
        while (true)
        {
            cout << "Enter state: ";
            cin >> s;
            if (s == -1) break;
            state.insert({s});
            cout << "Enter state to go for 0: ";
            State present0,present1;
            while(true)
            {
                int s1;
                cin >> s1;
                if (s1 == -1) break;
                present0.insert(s1);//creating new complex state
                prim.insert(s1);
                
            }
            state.insert(present0);
            cout << "Enter state to go for 1: ";
            while(true)
            {
                int s2;
                cin >> s2;
                if (s2 == -1) break;
                present1.insert(s2);//creating new complex state
                prim.insert(s2);
            }
            state.insert(present1);

            for(int primitive:prim)//Add to state space if new primitive states are entered 
                if(state.find({primitive})==state.end())
                {
                    state.insert({primitive});
                }
            
            
            d[{s}][0] = present0;
            d[{s}][1] = present1;

        
        }
        // Print the transitions
        cout<<"\t        |0--->| |1--->|"<<endl;
        for (const auto& [fromState, transitions] : d) 
        {
            cout << "{ ";
            for (int s : fromState) 
                cout << s << ",";
            cout << "} --> \t";


            for (const auto& [action, toState] : transitions)
            {
                // cout << "\n Action = " << action << " to { ";
                cout<<"| {";
                for (int s : toState)
                    cout << s << ",";
                cout << "} | ";
            }
        cout << endl;
        }

}


void calculate()
{
    
}



};

int main() {
    // // Example states
    // State Q0 = {0};
    // State Q1 = {1};
    // State Q2 = {2};
    // State Q3= {3};
    // State Q4= {0,1};
    // State Q5= {0,2};
    // State Q6= {0,3};
    // State Q7= {0,1,2};
    // State Q8= {0,1,3};
    // State Q9= {0,2,3};
    // State Q10= {0,1,2,3};
    // State Q11={};
    // // Input alphabet
    nfa_dfa ob;
    ob.input();

   return 0;
}

    

