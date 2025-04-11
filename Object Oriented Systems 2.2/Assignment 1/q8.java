// Write a class for “Account” containing data members ‘accountNumber’, ‘holderName’,
// ‘balance’ and add constructors and necessary accessor/modifier functions for these data
// members. Now create two class “SavingsAccount” and “CurrentAccount” extending from this
// class. SavingsAccount will have a member variable ‘interestRate’ and member function
// ‘calculateYearlyInterest’. Write another class “Manager” that contains a list Account. Also write
// a main() function to create an instance of Manager class. Add two SavingsAccount and three
// CurrentAccount to Manager. Calculate interest of each SavingsAccount. Print the details of all
// accounts.

class Account {
    private int accountNumber;
    private String holderName;
    private double balance;
    
    public Account(int accountNumber, String holderName, double balance) {
        this.accountNumber = accountNumber;
        this.holderName = holderName;
        this.balance = balance;
    }

    public int getAccountNumber() {
        return accountNumber;
    }
    
    public String getHolderName() {
        return holderName;
    }
    
    public double getBalance() {
        return balance;
    }
    
    public void setAccountNumber(int accountNumber) {
        this.accountNumber = accountNumber;
    }
    
    public void setHolderName(String holderName) {
        this.holderName = holderName;
    }
    
    public void setBalance(double balance) {
        this.balance = balance;
    }
    
    public String toString() {
        return "Account Number: " + accountNumber + ", Holder Name: " + holderName + ", Balance: " + balance;
    }
}


class SavingsAccount extends Account {
    private double interestRate; 
    
    public SavingsAccount(int accountNumber, String holderName, double balance, double interestRate) {
        super(accountNumber, holderName, balance);
        this.interestRate = interestRate;
    }
    
    public double getInterestRate() {
        return interestRate;
    }
    
    public void setInterestRate(double interestRate) {
        this.interestRate = interestRate;
    }
    
    public double calculateYearlyInterest() {
        return getBalance() * interestRate;
    }

    public String toString() {
        return "SavingsAccount -> " + super.toString() + ", Interest Rate: " + interestRate;
    }
}


class CurrentAccount extends Account {
    
    public CurrentAccount(int accountNumber, String holderName, double balance) {
        super(accountNumber, holderName, balance);
    }
    
    public String toString() {
        return "CurrentAccount -> " + super.toString();
    }
}

class Manager {
    private Account[] accounts;
    private int count;  
    
    public Manager(int capacity) {
        accounts = new Account[capacity];
        count = 0;
    }
    
    public void addAccount(Account account) {
        if (count < accounts.length) {
            accounts[count++] = account;
        } else {
            System.out.println("capacity reached.");
        }
    }
    
    public void printAllAccounts() {
        for (int i = 0; i < count; i++) {
            System.out.println(accounts[i]);
        }
    }
    
    public Account[] getAccounts() {
        return accounts;
    }
    
 
    public int getCount() {
        return count;
    }
}


public class q8 {
    public static void main(String[] args) {
       
        Manager manager = new Manager(5);
        
        SavingsAccount savings1 = new SavingsAccount(101, "Ram Das", 5000.0, 0.04); // 4% interest rate
        SavingsAccount savings2 = new SavingsAccount(102, "Shyam Das", 10000.0, 0.05); // 5% interest rate
        
      
        CurrentAccount current1 = new CurrentAccount(201, "Manami Mukherjee", 1500.0);
        CurrentAccount current2 = new CurrentAccount(202, "Jadu Ghosh", 2500.0);
        CurrentAccount current3 = new CurrentAccount(203, "Madhu Ghosh", 3500.0);
        

        manager.addAccount(savings1);
        manager.addAccount(savings2);
        manager.addAccount(current1);
        manager.addAccount(current2);
        manager.addAccount(current3);
        
      
        System.out.println("Yearly interest calculations for Savings Accounts:");
        SavingsAccount sa;
        Account[] accounts = manager.getAccounts();
        for (int i = 0; i < manager.getCount(); i++) {
          
            if (accounts[i] instanceof SavingsAccount) {
                sa = (SavingsAccount) accounts[i];
                double interest = sa.calculateYearlyInterest();
                System.out.println("Account Number " + sa.getAccountNumber() +  " (Holder: " + sa.getHolderName() + ") earns yearly interest: " + interest);
            }
        }
        
      
        System.out.println("\nDetails of all accounts:");
        manager.printAllAccounts();
    }
}
