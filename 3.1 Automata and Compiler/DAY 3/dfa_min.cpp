#include <iostream>
#include <vector>
#include <map>
using namespace std;

class dfa_min
{
public:
    // DFA Transition Table: state -> input symbol -> next state
    map<int, map<int, int>> d;

    // Partition of states into groups
    vector<vector<int>> pi;

    void run()
    {
        pi.resize(2); // Initially two groups: non-final and final

        cout << "Enter states with transitions (state 0_state 1_state), -1 to stop\n";

        int s, s0, s1;

        while (true)
        {
            cout << "Enter state: ";
            cin >> s;
            if (s == -1) break;

            cout << "Enter state to go for 0: ";
            cin >> s0;
            cout << "Enter state to go for 1: ";
            cin >> s1;

            d[s][0] = s0;
            d[s][1] = s1;
        }

        int finalState;
        cout << "Enter final state: ";
        cin >> finalState;

        // Initial partition: non-final and final
        for (const auto& [state, trans] : d)
        {
            if (state == finalState)
                pi[1].push_back(state);
            else
                pi[0].push_back(state);
        }

        // Print partitions
        cout << "\nInitial Partitions:\n";
        for (size_t i = 0; i < pi.size(); ++i)
        {
            cout << "Group " << i << ": ";
            for (int st : pi[i])
                cout << st << " ";
            cout << "\n";
        }

        // Print transition table
        cout << "\nTransition Table:\n";
        for (const auto& [state, transitions] : d)
        {
            cout << "State " << state << ":\n";
            for (const auto& [input, nextState] : transitions)
            {
                cout << "  On " << input << " -> " << nextState << "\n";
            }
        }
    }

    // Returns the index of the block in the partition that contains 'state'
    int block_present(int state, const vector<vector<int>>& partition)
    {
        for (int i = 0; i < partition.size(); ++i)
        {
            for (int s : partition[i])
            {
                if (s == state)
                    return i;
            }
        }
        return -1;
    }

    void calc()
    {
        vector<vector<vector<int>>> history;
        history.push_back(pi);

        bool changed = true;

        while (changed)
        {
            changed = false;
            vector<vector<int>> new_pi;

            for (const auto& block : pi)
            {
                vector<vector<int>> subBlocks;

                for (int state : block)
                {
                    bool placed = false;

                    for (auto& subBlock : subBlocks)
                    {
                        int rep = subBlock[0];
                        bool same = true;

                        for (int input = 0; input <= 1; ++input)
                        {
                            int t1 = d[state][input];
                            int t2 = d[rep][input];

                            if (block_present(t1, pi) != block_present(t2, pi))
                            {
                                same = false;
                                break;
                            }
                        }

                        if (same)
                        {
                            subBlock.push_back(state);
                            placed = true;
                            break;
                        }
                    }

                    if (!placed)
                    {
                        subBlocks.push_back({state});
                    }
                }

                for (auto& sb : subBlocks)
                    new_pi.push_back(sb);
            }

            if (new_pi != pi)
            {
                pi = new_pi;
                history.push_back(pi);
                changed = true;
            }
        }

        // Print final minimized DFA
        cout << "\nFinal Minimized DFA Partitions:\n";
        for (size_t i = 0; i < pi.size(); ++i)
        {
            cout << "Block " << i << ": ";
            for (int s : pi[i])
                cout << s << " ";
            cout << "\n";
        }
    }
};

int main()
{
    dfa_min ob;
    ob.run();
    ob.calc();

    return 0;
}