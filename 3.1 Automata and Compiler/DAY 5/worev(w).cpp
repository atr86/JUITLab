//w concat rev(w) is not a regular language
#include <iostream>
using namespace std;
#include <set>
#include <map>

class pumpingLemma{
    public:
    string w;
    int k;
    int n;
    void input()
    {
        cout<<"Your language must in the form w o reverse(w) so enter w \n";
        cin>>w;
    }
    bool isSatisfied(string s)
    {
        for(int i=0;i<s.length()/2;i++)
        {
            if(s[i]!=s[s.length()-i-1])
            return false;
        }
        return true;
    }
    void run()
    {
        string s=w;
        for(int i=w.length()-1;i>=0;i--)
        {
            s+=w[i];
        }
        check(s);
    }
    void check(string s)
    {
        int p;
        for(p=1;p<s.length();p++)
        {
            string xy=s.substr(0,p);
            string z= s.substr(p,s.length()-p);
            for(int i=0;i<p;i++)
            {
                string x=xy.substr(0,i);
                string y=xy.substr(i,xy.length()-i);
                string y_j=y;
                for(int j=1;j<=p+1;j++)
                {
                    if(isSatisfied(x+y_j+z)==false)
                    {
                        cout<<"Not satisfied for p = "<<p<<"\n x = "<<x<<"\n y ^ "<<j<<" = "<<y_j<<"\n z = "<<z<<"\n hence not regular\n";
                        return;
                    }
                        
                        y_j=y_j+y;
                }

            }
        }
        cout<<"Cannot be determined regular or not"<<"\n";
    }
};
int main()
{
    pumpingLemma lang;
    lang.input();
    lang.run();
}
