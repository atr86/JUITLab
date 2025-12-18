#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
using namespace std;

class multiple {
public:
    int n;
    set<int> state;
    set<int> action = {0, 1};
    map<int, map<int, int>> d; // map<State, map<Action, State>>

    multiple(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) {
            state.insert(i);
        }
        creatett(0, 0, 0); // start with num=0, state=0, input=0
        cout<<"Transition Table for n = "<<n<<"\n";
        displayd();
    }
    
    int decimal(int num) {
        int res = 0;
        int base = 1;
        while (num > 0) {
            int digit = num % 10;
            res += digit * base;
            base *= 2;
            num /= 10;
        }
        return res;
    }

    void creatett(int num, int s, int a) {
        if (isCompleteSA(s, a)) 
        {
            // cout<<"Once More"<<"\n";
            return;
            
        }

        int toState = decimal(num)%n;
        d[s][a] = toState;

        // cout << "State " << s << " with input " << a
        //      << " -> State " << toState << "\n";

        creatett(num * 10 + 0, toState, 0); // encounter 0
        creatett(num * 10 + 1, toState, 1); // encounter 1
    }

    bool isCompleteSA(int s, int a) {
        auto it = d.find(s);
        if (it == d.end()) return false; // state not present

        if (it->second.find(a) == it->second.end()) return false;
        return true;
    }

    bool isComplete() {
        for (int s : state) {
            auto it = d.find(s);
            if (it == d.end()) return false;

            for (int a : action) {
                if (it->second.find(a) == it->second.end()) return false;
            }
        }
        return true;
    }

    void displayd() {
        cout<<"      | 0  |  | 1  |"<<endl;
        for (const auto& [outerKey, innerMap] : d) {
            cout << "q" << outerKey << " : ";
            for (const auto& [innerKey, value] : innerMap) {
                cout << " | q" << value << " | " ;
            }
            cout<<endl;
        }
    }
    string toBin(int n)
    {
        string word="";
        while(n>0)
        {
            word=to_string(n%2)+word;
            n=n/2;
        }
        return word;
    }
    bool div(int num)
    {
        string word= toBin(num);
    int curr=0;
    for(int i=0;i<word.length();i++)
    {
        int digit=((int)word[i]-(int)'0');
        curr=d[curr][digit];
    }
    cout<<"You reached state q"<<curr<<" when divided by "<<n<<"\n";
   
    return (curr==0);


    }
    

};

int main() {
    multiple obj2(2);
    multiple obj3(3);
    multiple obj5(5);
    multiple obj7(7);
    int num;
    cout<<"Enter number"<<"\n";
    cin>>num;
    cout<<"\n";
    if(num==2 || num==3 || num==5 || num==7)
    {
        cout<<"Prime within 10";
        return 0;
    }
    if(obj2.div(num))
    {
        cout<<"Divisible by 2";
        return 0;
    }
    if(obj3.div(num))
    {
        cout<<"Divisible by 3";
        return 0;
    }
    if(obj5.div(num))
    {
        cout<<"Divisible by 5";
        return 0;
    }
    if(obj7.div(num))
    {
        cout<<"Divisible by 7";
        return 0;
    }
    cout<<"Prime Number";
    
    return 0;
}
