#ifndef BANKOFFICIAL_H
#define BANKOFFICIAL_H

#include <iostream>
#include <string>
#include <vector>
#include "AccountHolder.h"
#include "AccountP.h"

using namespace std;

class BankOfficial
{
    private:
        string firstName, lastName, login, password;
        int id;
        bool status;
    public:
        BankOfficial(string, string, int, string, string);
        void openAccount(AccountHolder &, int);
        void openAccount(AccountHolder &, int, double);
        void openAccount(AccountHolder &, int, double, double);
        void closeAccount( int,vector<AccountHolder>&,int);
        void openAccountD(int, vector<AccountHolder>&, int);
        void deposit(AccountHolder &, int, double);
        void withdraw(AccountHolder &, int, double);
        void search(vector<AccountHolder>&, int);
        void search(vector<AccountHolder>&, string);
        void setStatus(string);
        bool getStatus() const;
        void setFirstName(string);
        string getFirstName() const;
        void setLastName(string);
        string getLastName() const;
        void setID(int);
        int getID() const;
        void setLogin(string);
        string getLogin() const;
        void setPassword(string);
        string getPassword();
};

BankOfficial::BankOfficial(string FirstName ="", string LastName="", int ID=0, string Login="", string Password="")
{
    firstName = FirstName;
    lastName = LastName;
    id = ID;
    status = true;
    login = Login;
    password = Password;
}

string BankOfficial::getPassword()
{
   return password;
}

void BankOfficial::setPassword(string newPassword)
{
    password = newPassword;
}


string BankOfficial::getLogin() const
{
    return login;
}

void BankOfficial::setLogin(string newLogin)
{
    login = newLogin;
}

int BankOfficial::getID() const
{
    return id;
}

void BankOfficial::setID(int newID)
{
    id = newID;
}

string BankOfficial::getLastName() const
{
    return lastName;
}

void BankOfficial::setLastName(string newName)
{
    lastName = newName;
}

string BankOfficial::getFirstName() const
{
    return firstName;
}

void BankOfficial::setFirstName(string newName)
{
    firstName = newName;
}

bool BankOfficial::getStatus() const
{
    return status;
}

void BankOfficial::setStatus(string newStatus)
{
    if(newStatus == "enable" || newStatus == "Enable")
    {
        status = true;
    }
    else if(newStatus == "disable" || newStatus == "Disable")
    {
        status = false;
    }
    else
    {
        cout << "Please enter a valid status value.\n";
    }
}

void BankOfficial::openAccount(AccountHolder &accHolder, int newAccountNumber)
{
    if(status)
    {
        accHolder.createCheckingAccount(newAccountNumber);
    }
}

void BankOfficial::openAccount(AccountHolder &AccHolder, int newAccountNumber, double intRate)
{
    if(status)
    {
        AccHolder.createSavingsAccount(newAccountNumber, intRate);
    }
    else
    {
        cout <<"This account is not active\n";
    }
}

void BankOfficial::openAccount(AccountHolder &AccHolder, int newAccountNumber, double intRate, double termLen)
{
    if(status)
    {
        AccHolder.createCDAccount(newAccountNumber, intRate, termLen);
    }
    else
    {
        cout <<"This account is not active\n";
    }
}

void BankOfficial::closeAccount(int accountNumber, vector<AccountHolder>& accountHolders,int location)
{
   if(status)
   {
      accountHolders[location].closeAccount(accountNumber);
   }
   else
   {
      cout<<"bank Official is not active"<<endl;
   }
}

void BankOfficial::openAccountD(int accountNumber, vector<AccountHolder>& accountHolders, int location)
{
    if(status)
    {
       accountHolders[location].openAccount(accountNumber);
    }
    else
    {
      cout<<"bank official is not active"<<endl;
    }
}


void BankOfficial::deposit(AccountHolder &accHldr, int accountNumber, double amount)
{
    if(status)
    {
        accHldr.deposit(accountNumber, amount, firstName + " "  + lastName);
    }
    else
    {
        cout <<"This account is not active\n";
    }
}

void BankOfficial::withdraw(AccountHolder &accHldr, int accountNumber, double amount)
{
    if(status)
    {
        accHldr.withdraw(accountNumber, amount, firstName + " "  + lastName);
    }
    else
    {
        cout <<"This account is not active\n";
    }
}

void BankOfficial::search(vector<AccountHolder>& accountHolders, int accountNumber)
{
    if(status){
        int accountHolderID = 0;
        bool found = false;
        for(int i = 0; i < accountHolders.size(); i++)
        {
            if(accountHolders[i].getId() == accountNumber)
            {
               accountHolderID = i;
               found =true;
            }
        }

        if(found)
        {
            cout << "Accounts: \n";
            for(int i = 0; i < accountHolders[accountHolderID].numberOfAccounts(); i++)
            {
                cout <<"accout id "<<  accountHolders[accountHolderID].getAccountAt(i).getAccountNumber() << ": account balance " << accountHolders[accountHolderID].getAccountAt(i).getBalance() << '\n';
            }
        }
        else
        {
            cout << "This account does not exist\n";
        }
    }
    else
    {
        cout <<"This account is not active\n";
    }
}

void BankOfficial::search(vector<AccountHolder>& accountHolders, string LastNameOrNumber)
{
    if(status){
        bool found = false;

        int location = 0;

        for(int i = 0; i < accountHolders.size(); i++)
        {
            if(accountHolders[i].getLastName() == LastNameOrNumber || accountHolders[i].getPhoneNumber() == LastNameOrNumber)
            {
                found = true;
                location = i;
            }
        }

        if(found)
        {
            cout << "Accounts: \n";
            for(int i = 0; i < accountHolders[location].numberOfAccounts(); i++)
            {
                cout <<"Account Id "<< accountHolders[location].getAccountAt(i).getAccountNumber() << ": balance " << accountHolders[location].getAccountAt(i).getBalance() << '\n';
            }
        }
        else
        {
            cout << "This account holder does not exist\n";
        }
    }
    else
    {
        cout <<"This account is not active\n";
    }
}

#endif
