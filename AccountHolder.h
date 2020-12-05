#ifndef ACCOUNTHOLDER_H
#define ACCOUNTHOLDER_H

#include <string>
#include <iostream>
#include <vector>
#include "AccountP.h"

using namespace std;

class AccountHolder
{
    private:
        int id;
        string firstName, lastName, address, phoneNumber, password, login;
        vector <AccountP> accounts;

    public:
        AccountHolder(string, string, string, string, string, string);
        AccountP findAccount(int);
        AccountP &getAccountAt(int);
        void withdraw(int, double, string);
        void deposit(int, double, string);
        void setId(int);
        int getId() const;
        void setFirstName(string);
        string getFirstName() const;
        void setLastName(string);
        string getLastName() const;
        void setAddress(string);
        string getAddress() const;
        void setPhoneNumber(string);
        string getPhoneNumber() const;
        void setPassword(string);
        string getPassword();
        void setLogin(string);
        string getLogin() const;
        double getAccountBalance(int);
        void createCheckingAccount(int);
        void createSavingsAccount(int, double);
        void createCDAccount(int, double, double);
        void changePassword(string);
        int numberOfAccounts() const;
        vector<AccountP>& getAccounts();
        string getType(int);
        void printAccounts();
        void printAccountInfo(int);
        void addAccount(AccountP &);
        void printTransacions(int,int,int,int);
        void closeAccount(int);
        void openAccount(int);
};

AccountHolder::AccountHolder(string FirstName = "", string LastName = "", string Address = "", string PhoneNumber = "", string Password = "", string Login = "")
{
    firstName = FirstName;
    lastName = LastName;
    address = Address;
    phoneNumber = PhoneNumber;
    password = Password;
    login = Login;
}

void AccountHolder::addAccount(AccountP &newAccount)
{
    accounts.push_back(newAccount);
}

string AccountHolder::getType(int accountNumber)
{
    for(int i = 0; i < accounts.size(); i++)
    {
        if(accounts[i].getAccountNumber() == accountNumber)
        {
            return accounts[i].getType();
        }
    }
    return "account doesnt exsist";
}

AccountP & AccountHolder::getAccountAt(int index)
{
    return accounts[index];
}

vector<AccountP> & AccountHolder::getAccounts()
{
    return accounts;
}

int AccountHolder::numberOfAccounts() const
{
    return accounts.size();
}

void AccountHolder::withdraw(int accountNumber, double amount, string BankOfficialName)
{
    bool found = false;
    int location = 0;
    for(int i = 0; i < accounts.size(); i++)
    {
        if(accounts[i].getAccountNumber() == accountNumber)
        {
            found = true;
            location = i;
        }
    }

    if(found)
    {
        if(amount > 0 && accounts[location].getBalance() >= amount)
        {
            accounts[location].withdraw(amount, BankOfficialName);
        }
        else
        {
            cout << "Enter a valid amount\n";
        }
    }
    else
    {
        cout << "An account with this Account Number does not exists\n";
    }
}

void AccountHolder::deposit(int accountNumber, double amount, string BankOfficialName)
{
    bool found = false;
    int location = 0;
    for(int i = 0; i < accounts.size(); i++)
    {
        if(accounts[i].getAccountNumber() == accountNumber)
        {
            found = true;
            location = i;
        }
    }

    if(found)
    {
        if(amount > 0.0)
        {
            accounts[location].deposit(amount, BankOfficialName);
        }
        else
        {
            cout << "Enter a valid amount\n";
        }
    }
    else
    {
        cout << "An account with this Account Number does not exists\n";
    }
}

string AccountHolder::getLogin() const
{
    return login;
}

void AccountHolder::setLogin(string newLogin)
{
    login = newLogin;
}

void AccountHolder::setPassword(string newPassword)
{
    password = newPassword;
}

void AccountHolder::setPhoneNumber(string newNumber)
{
    phoneNumber = newNumber;
}

string AccountHolder::getPhoneNumber() const
{
    return phoneNumber;
}

void AccountHolder::setAddress(string newAddress)
{
    address = newAddress;
}

string AccountHolder::getAddress() const
{
    return address;
}

void AccountHolder::setLastName(string newName)
{
    lastName = newName;
}

string AccountHolder::getLastName() const
{
    return lastName;
}
    
void AccountHolder::setFirstName(string newName)
{
    firstName = newName;
}

string AccountHolder::getFirstName() const
{
    return firstName;
}

void AccountHolder::setId(int ID)
{
    id = ID;
}

int AccountHolder::getId() const
{
    return id;
}

string AccountHolder :: getPassword()
{
   return password;
}

double AccountHolder::getAccountBalance(int accountNumber) 
{
    bool found = false;
    for(int i = 0; i < accounts.size(); i++)
    {
        if(accounts[i].getAccountNumber() == accountNumber)
        {
            cout<<accounts[i].getBalance()<< endl;
            return true;
        }
    }

    return false;
}

void AccountHolder::createCheckingAccount(int accountNumber)
{

    bool found = false;
    for(int i = 0; i < accounts.size(); i++)
    {
        if(accounts[i].getAccountNumber() == accountNumber)
        {
            found = true;
        }
    }

    if(!found)
    {
        AccountP newAccount(accountNumber, 0.0);
        newAccount.setType("C");
        newAccount.setCreationTime();
        newAccount.setTimeNow();
        accounts.push_back(newAccount);
    }
    else
    {
        cout << "An account with this Account Number already exists\n";
    }
}

void AccountHolder::createSavingsAccount(int accountNumber, double interestRate)
{
    bool found = false;
    for(int i = 0; i < accounts.size(); i++)
    {
        if(accounts[i].getAccountNumber() == accountNumber)
        {
            found = true;
        }
    }

    if(!found)
    {
        AccountP newAccount(accountNumber, 0.0);
        newAccount.setInterest(interestRate);
        newAccount.setType("S");
        newAccount.setCreationTime();
        newAccount.setTimeNow();
        accounts.push_back(newAccount);
    }
    else
    {
        cout << "An account with this Account Number already exists\n";
    }
}

void AccountHolder::createCDAccount(int accountNumber, double interestRate, double term)
{
    bool found = false;
    for(int i = 0; i < accounts.size(); i++)
    {
        if(accounts[i].getAccountNumber() == accountNumber)
        {
            found = true;
        }
    }

    if(term < 0){
        found = true;
    }

    if(!found)
    {
        AccountP newAccount(accountNumber, 0.0);
        newAccount.setInterest(interestRate);
        newAccount.setTerm(term);
        newAccount.setType("CD");
        newAccount.setCreationTime();
        newAccount.setTimeNow();
        newAccount.setMaturity();
        accounts.push_back(newAccount);
    }
    else
    {
        cout << "An account with this Account Number already exists or the interest rate is invalid\n";
    }
}

void AccountHolder::changePassword(string newPassword)
{
    password = newPassword;
}

void AccountHolder:: printAccounts()
{
   for(int i= 0; i < accounts.size(); i++)
   {
      cout<<"account number " << to_string(accounts[i].getAccountNumber()) << endl;
      cout<<"account type " << accounts[i].getType() << endl;
   }
}

void AccountHolder::printAccountInfo(int accountNumber)
{

    bool found = false;

    int location = 0;

    for(int i = 0; i < accounts.size(); i++)
    {
        if(accounts[i].getAccountNumber() == accountNumber)
        {
            location = i;
            found = true;
        }
    }

    if(found)
    {
        cout<<"Last Open " + accounts[location].getDateLastOpen()<<endl;
        cout<<"Type " + accounts[location].getType()<<endl;
        cout<<"Balance " + to_string(accounts[location].getBalance())<<endl;
        if(accounts[location].getType() != "Checking Account")
        {
            cout<<"Interest " + to_string(accounts[location].getInterest())<<endl;
        }
        if(accounts[location].getType() == "CD Accounts")
        {
            cout<<"Interest " + to_string(accounts[location].getInterest())<<endl;
            cout<<"Date of Maturity " + accounts[location].getMaturity() <<endl;
        }
        
        accounts[location].printTransactions();
       
    }
    else
    {
        cout << "Account with account number: " << accountNumber << " does not exist\n";
    }
}

void AccountHolder::closeAccount(int accountNumber)
{
        bool found = false;

        int location = 0;

        for(int i = 0; i < accounts.size(); i ++)
        {
            if(accounts[i].getAccountNumber() == accountNumber)
            {
                location = i;
                found = true;
            }
        }

        if(found)
        {
            accounts[location].setStatus(false);
            cout << "Account succesfully closed\n";
        }
        else
        {
            cout << "An account with this account number was not found\n";
        }
}

void AccountHolder::openAccount(int accountNumber)
{
       bool found = false;

        int location = 0;

        for(int i = 0; i < accounts.size(); i ++)
        {
            if(accounts[i].getAccountNumber() == accountNumber)
            {
                location = i;
                found = true;
            }
        }

        if(found)
        {
            accounts[location].setStatus(true);
            cout << "Account succesfully closed\n";
        }
        else
        {
            cout << "An account with this account number was not found\n";
        }
}
#endif
