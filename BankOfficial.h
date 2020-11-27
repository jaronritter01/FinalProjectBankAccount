#ifndef BANKOFFICIAL_H
#define BANKOFFICIAL_H

#include <iostream>
#include <string>
#include <vector>
#include "AccountHolder.h"
#include "account.h"

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
        void closeAccount(AccountHolder &, int);
        void deposit(AccountHolder &, int, double);
        void withdraw(AccountHolder &, int, double);
        void search(vector<AccountHolder>, int);
        void search(vector<AccountHolder>, string);
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

void BankOfficial::closeAccount(AccountHolder &AccHolder, int accountNumber)
{
    if(status)
    {
        vector<Account> accounts = AccHolder.getAccounts();

        bool found = false;

        int location = 0;

        for(int i = 0; i < AccHolder.numberOfAccounts(); i ++)
        {
            if(accounts[i].getAccountNumber() == accountNumber)
            {
                location = i;
                found = true;
            }
        }

        if(found)
        {
            accounts[location].setStatus("inactive");
            cout << "Account succesfully closed\n";
        }
        else
        {
            cout << "An account with this account number was not found\n";
        }
    }
    else
    {
        cout <<"This account is not active\n";
    }
}

void BankOfficial::deposit(AccountHolder &accHldr, int accountNumber, double amount)
{
    if(status)
    {
        accHldr.deposit(accountNumber, amount);
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
        accHldr.withdraw(accountNumber, amount);
    }
    else
    {
        cout <<"This account is not active\n";
    }
}

void BankOfficial::search(vector<AccountHolder> accountHolders, int accountNumber)
{
    if(status){
        int accountHolderID = 0, accountID = 0;
        bool found = false;
        for(int i = 0; i < accountHolders.size(); i++)
        {
            for(int j = 0; j < accountHolders[i].numberOfAccounts(); j++)
            {
                if(accountHolders[i].getAccountAt(j).getAccountNumber() == accountNumber)
                {
                    accountHolderID = i;
                    accountID = j;
                    found = true;
                }
            }
        }

        if(found)
        {
            AccountHolder accHolderF = accountHolders[accountHolderID];
            Account accountLocated = accountHolders[accountHolderID].getAccountAt(accountID);
            cout << "Account Number: " << accountLocated.getAccountNumber() << '\n' << "Account Holder: " << accHolderF.getFirstName() << " " << accHolderF.getLastName() 
            << '\n' << "Account Balance: " << accountLocated.getBalance() <<  '\n' << "Account Type: " << accountLocated.getType() << '\n';
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

void BankOfficial::search(vector<AccountHolder> accountHolders, string LastNameOrNumber)
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
                cout << accountHolders[location].getAccountAt(i).getAccountNumber() << ": " << accountHolders[location].getAccountAt(i).getBalance() << '\n';
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