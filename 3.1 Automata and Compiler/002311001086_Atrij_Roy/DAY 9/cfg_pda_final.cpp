#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <iomanip>

using namespace std;

struct Production {
    char variable;
    string replacement;
};

struct Transition {
    string currentState;
    string inputSymbol;
    string stackTop;
    string nextState;
    string pushStack;
};

bool isTerminal(char c) {
    return !isupper(c) && c != 'e';
}

// Recursive PDA simulation using DFS
bool simulate(const string& input, int pos, vector<char> stack,
              const vector<Production>& productions) {
    if (pos > input.length()) return false;
    if (stack.empty()) return pos == input.length();

    char top = stack.back();

    // ✅ Case 3: Finished input, Z0 still on stack
    if (top == 'Z' && stack.size() == 1 && pos == input.length()) {
        return true;
    }

    stack.pop_back();

    // Case 1: Top is variable → apply productions
    if (isupper(top)) {
        for (const auto& prod : productions) {
            if (prod.variable == top) {
                vector<char> newStack = stack;
                if (prod.replacement != "e") {
                    for (int i = prod.replacement.length() - 1; i >= 0; --i) {
                        newStack.push_back(prod.replacement[i]);
                    }
                }
                if (simulate(input, pos, newStack, productions)) {
                    return true;
                }
            }
        }
    }
    // Case 2: Terminal match
    else if (pos < input.length() && input[pos] == top) {
        if (simulate(input, pos + 1, stack, productions)) {
            return true;
        }
    }

    return false;
}


int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;
    cin.ignore();

    vector<Production> productions;

    cout << "Enter productions (use '->' and 'e' for epsilon):" << endl;
    for (int i = 0; i < n; ++i) {
        string line;
        getline(cin, line);
        if (line.find("->") == string::npos || line.length() < 4) {
            cout << "Invalid format. Use A->α format.\n";
            --i;
            continue;
        }
        Production p;
        p.variable = line[0];
        p.replacement = line.substr(3);
        productions.push_back(p);
    }

    // Build transition list
    vector<Transition> transitions;
    transitions.push_back({"q_start", "e", "Z0", "q_loop", "S Z0"});

    for (auto& p : productions) {
        string to_push = (p.replacement == "e") ? "e" : p.replacement;
        transitions.push_back({"q_loop", "e", string(1, p.variable), "q_loop", to_push});
    }

    map<char, bool> terminals;
    for (auto& p : productions) {
        for (char c : p.replacement) {
            if (isTerminal(c)) {
                terminals[c] = true;
            }
        }
    }

    for (auto& t : terminals) {
        char term = t.first;
        transitions.push_back({"q_loop", string(1, term), string(1, term), "q_loop", "e"});
    }

    transitions.push_back({"q_loop", "e", "Z0", "q_accept", "e"});

    // Print Transition Table
    cout << "\n--- PDA Transition Table ---\n\n";
    cout << left << setw(15) << "Current State"
         << setw(10) << "Input"
         << setw(12) << "Stack Top"
         << setw(15) << "Next State"
         << setw(12) << "Stack Push" << "\n";

    cout << string(64, '-') << "\n";

    for (auto& t : transitions) {
        cout << left << setw(15) << t.currentState
             << setw(10) << t.inputSymbol
             << setw(12) << t.stackTop
             << setw(15) << t.nextState
             << setw(12) << t.pushStack << "\n";
    }

    // Input string
    string input;
    cout << "\nEnter input string to test: ";
    getline(cin, input);

    // Initialize stack with Z0 and S
    vector<char> stack;
    stack.push_back('Z');
    stack.push_back('S');

    bool accepted = simulate(input, 0, stack, productions);

    cout << "\nResult: ";
    if (accepted)
        cout << " Accepted by PDA\n";
    else
        cout << " Rejected by PDA\n";

    return 0;
}

    //     stack.push_back('\0');
    //     cout << "❌ Rejected by PDA\n";
    //     cout<<"Stack state is "<<&stack[0]<<"\n";
    // }
// 4
// S->aBc
// S->ab
// B->SB
// B->e


