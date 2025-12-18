// Online C++ compiler to run C++ program online
#include <iostream>
#include <array>
#include <string>
using namespace std;

class Machine
{

    public:
    string d[3][2];
    string state[3]={"q0","q1","q2"};
    int action[2]={0,1};
    
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

        for(int i=0;i<3;i++)
            {
                for(int j=0;j<2;j++)
                    cout<<d[i][j]<<" ";
               cout<<"\n";
            }
    }
    
    void run(string num)
    {
        int i;
        transition();
        string curr_state="q0";
        cout<<curr_state<<" is 1st step for this input \n";
        for(i=0;i<num.length();i++)
        {
            if(curr_state=="q0")
            {
                switch(num[i])
                {
                    case '0':curr_state=d[0][0];
                    break;
                    case '1':curr_state=d[0][1];
                    break;
                }
            }
            else if(curr_state=="q1")  
            {
                switch(num[i])
                {
                    case '0':curr_state=d[1][0];
                    break;
                    case '1':curr_state=d[1][1];
                    break;
                }
            }
            else if(curr_state=="q2")
            {
                switch(num[i])
                {
                    case '0':curr_state=d[2][0];
                    break;
                    case '1':curr_state=d[2][1];
                    break;
                }
            }
            cout<<curr_state<<"\n";
        }
        cout<<curr_state<<" is last step for this input\n";
        if(curr_state=="q2")
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


