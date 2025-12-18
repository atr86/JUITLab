#include <iostream>
#include <set>
#include <map>
#include <string.h>
using namespace std;

class Machine
{
public:
set<int> state={0,1,2,3,4,5};
set<int> action={0,1};
map<int,map<int,int>> d;//map<State,<map<Action,State>>

void transition()
{
    d[0][0]=0;
    d[0][1]=1;
    d[1][0]=2;
    d[1][1]=3;
    d[2][0]=4;
    d[2][1]=5;
    d[3][0]=0;
    d[3][1]=1;
    d[4][0]=2;
    d[4][1]=3;
    d[5][0]=4;
    d[5][1]=5;

    // Print the map
    for (const auto& [outerKey, innerMap] : d) {
        cout << "Row " << outerKey << ":\n";
        for (const auto& [innerKey, value] : innerMap) {
            cout << "  Column " << innerKey << " -> " << value << endl;
        }
    }
}
void run(string word)
{
    transition();
   
    int curr=0;
    for(int i=0;i<word.length();i++)
    {
        int digit=((int)word[i]-(int)'0');
        curr=d[curr][digit];
    }
    cout<<"You reached state q"<<curr<<"\n";
    
    if(curr==0)
        cout<<"Reached Final Step";
    else
        cout<<"Reached Non Final Step";

    }


};
int main()
{
    Machine m;
    string word;
    cout<<"Your input string is :";
    cin>>word;
    m.run(word);
    return 0;
}