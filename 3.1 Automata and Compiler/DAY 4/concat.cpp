#include <iostream>
#include <set>
#include <map>
#include <string.h>
using namespace std;


class Machine
{
public:
set<int> state={0,1,2};
set<int> action={0,1};
map<int,map<int,int>> d;//map<State,<map<Action,State>>
set<int> fin;

void transition()
{//has same transition table
    d[0][0]=1;
    d[0][1]=2;
    d[1][0]=1;
    d[1][1]=2;
    d[2][0]=1;
    d[2][1]=2;



    // Print the map
     cout<<"      | 0  |  | 1  |"<<endl;
        for (const auto& [outerKey, innerMap] : d) {
            cout << "q" << outerKey << " : ";
            for (const auto& [innerKey, value] : innerMap) {
                cout << " | q" << value << " | " ;
            }
            cout<<endl;
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
   
    if(fin.count(curr)>0)
        cout<<"Reached Final Step";
    else
        cout<<"Reached Non Final Step";


    }




};
int main()
{
    Machine m;
    m.fin.insert(1);
    string word;
    cout<<"Your input string is :";
    cin>>word;
    m.run(word);
    return 0;
}
 