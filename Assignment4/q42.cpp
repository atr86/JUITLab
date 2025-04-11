// Design and implement class(es) to support the following code segment.
// Table t(4, 5), t1(4, 5);
// cin >> t;
// t[0][0] = 5;
// int x = t[2][3];
// t1 = t;
// cout << t << “\n” << t1;
#include <iostream>
using namespace std;
class Table
{
int r,c;
int** ptr;
public:
    Table(int row=01, int col=01)
{
    r=row;
    c=col;
    ptr=(int**)malloc(r*sizeof(int));
    for(int i=0;i<c;i++)
        {
            ptr[i]=(int*)malloc(c*sizeof(int));
        }
}
    Table(Table& t)
{
    r=t.r;
    c=t.c;
    ptr=(int**)malloc(r*sizeof(int));
    for(int i=0;i<c;i++)
        {
            ptr[i]=(int*)malloc(c*sizeof(int));
        }
    int i;
    for(int i=0;i<r;i++)
      for(int j=0;j<c;j++)
        ptr[i][j]=t.ptr[i][j];
}




    int* operator[](int i)
{
    return ptr[i];
}
    



friend istream& operator>>(istream& is,Table& t )
{
    int r,c;
    cout<<"Enter the row and column size and all elements of table";
    is>>r;
    is>>c;
    Table t1(r,c);
    int i,j;
    for(i=0;i<r;i++)
        {
           for(j=0;j<c;j++)
               {
                   is>>t1.ptr[i][j];
               }
        }
    t=t1;
    return is;
}
 friend ostream& operator<<(ostream& os,Table& t )
{
    int i,j;
    for(i=0;i<t.r;i++)
        {
           for(j=0;j<t.c;j++)
               {
                   os<<t.ptr[i][j]<<" ";
               }
            os<<endl;
        }
    return os;
}
};

    
int main()
    {
        Table t(4, 5), t1(4, 5);
        cin >> t;
        t[0][0] = 5;
        int x = t[2][3];
        t1 = t;
        cout << t << "\n" << t1;
    }