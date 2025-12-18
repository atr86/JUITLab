//// Show 0^n 1^kn is not a regular language
#include <iostream>
using namespace std;
#include <set>
#include <map>

class pumpingLemma{
    public:
    string a,b;
    int k;
    int n;
    void input()
    {
        cout<<"Your language must in the form a^nb^kn so enter a, b where k>=1 \n";
        cin>>a;
        cin>>b;
        cin>>k;
    }
    bool isSatisfied(string s)
    {
        
        int cnt_a=0;
        int cnt_b=0;
        for(int i=0;i<s.length();i++)
        {
            char ch= (char)s[i];
            if(ch==a[0])
                cnt_a++;
            if(ch==b[0])
                cnt_b++;
            if(cnt_a<s.length()/(k+1)&& cnt_b>0)
                return false;
        }
        if(cnt_a==n && cnt_b==k*n)
            return true;
        else
            return false;
    }
    void run()
    {
        n=3;
        string s="",a_str="",b_str="";
        for(int i=0;i<n;i++)
        {
           a_str+=a;
        }
        for(int i=0;i<k*n;i++)
        {
           b_str+=b;
        }
        s=a_str+b_str;
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
