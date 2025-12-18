class BankAccount
{
	int AccountNumber;
	float balance;
	String ownerName;
	BankAccount(int a, float f, String name)
	{
		AccountNumber=a;
		balance=f;
		ownerName=name;
	}
	void add(float val)
	{
		balance+=val;
		System.out.println("Your current balnce is"+ balance);
	}
	void subtract(float val)
	{
		if(balance-val<=50.0f)
			System.out.println("You would not have enough balance");
		else
		{
			val-=balance;
			System.out.println("Your balance is"+ balance);
		}
	}

}
class AccountManager
{
	BankAccount bac[];
	int ind;
	AccountManager(int max)
	{
	ind=0;
	bac=new BankAccount[max];
	}
	void create(int a, float f, String name)
	{	
		
		bac[ind]=new BankAccount(a, f, name);
		ind++;
	}
	void delete(int a)
	{
		int i,j ;
		for(i=0;i<=ind;i++)
		{
			if(bac[i].AccountNumber==a)
			{
				for(j=i;j<ind;j++)
				{
					bac[j]=bac[j+1];
				}
			break;
			}
		}
	}
	
	void deposit(float val,int a)
	{
		int i ;
		for(i=0;i<=ind;i++)
		{
			if(bac[i].AccountNumber==a)
			{	
				bac[i].add(val);
			break;	}
		}
	}
	void withdraw(float val,int a)
	{
		int i;
		for(i=0;i<=ind;i++)
		{
			if(bac[i].AccountNumber==a)
			{
				bac[i].subtract(val);
				break;
			}
		}
	}
}

class Bank
{
	public static void main(String args[])
	{
		AccountManager acm= new AccountManager(5);
		acm.create(000111, 500.0f, "Atrij Roy");
		acm.create(000112, 1000.0f, "Anumit Kr Jana");
		acm.create(000113, 1000.0f, "Abishkar Chatterjee");
		acm.create(000114, 1000.0f, "Asmit Deb");
		acm.create(000115, 1000.0f, "Arya Sammaddar");
		int i;
		for(i=0;i<acm.ind;i++)
		{
			System.out.println(acm.bac[i].ownerName+"\t"+"Balance="+acm.bac[i].balance+"\thaving account Number"+acm.bac[i].AccountNumber);       
        }
	}
}

