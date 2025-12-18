// Online C++ compiler to run C++ program online
#include <iostream>
#include <array>
#include <string>
using namespace std;

class Machine
{

    public:
    string d[5][2];
    string state[5]={"q0","q1","q2"};
    char action[2]={'a','b'};
    string final[2]={"q0","q1"};
    Machine()
    {
    }

    void transition()
    {
        d[0][0]="q0";
        d[0][1]="q1";
        d[1][0]="q1";
        d[1][1]="q2";
        d[2][0]="q2";
        d[2][1]="q1";


        for(int i=0;i<5;i++)
            {
                for(int j=0;j<2;j++)
                    cout<<d[i][j]<<" ";
               cout<<"\n";
            }
    }
    
    void run(string word)
    {
        int i;
        transition();
        string curr_state="q0";
        cout<<curr_state<<" is 1st step for this input \n";
        for(i=0;i<word.length();i++)
        {
            int m=((int)curr_state[1]-(int)'0');
            int n=((int)word[i]-(int)'0');
            curr_state=d[m][n];
            cout<<curr_state<<"\n";
        }
        cout<<curr_state<<" is last step for this input\n";
        for(i=0;i<2;i++)
        {
            if(final[i]==curr_state)
                break;
        }
        if(i!=2)
            cout<<"Reached final state"<<"\n";
        else
            cout<<"Reached non-final state";
    }
};


int main()
{
    Machine m;
    cout<<"Enter your input";
    string input;
    cin >> input;
    m.run(input);
}


