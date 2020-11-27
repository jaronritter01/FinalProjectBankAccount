#ifndef ACCOUNTHOLDER_H
#define ACCOUNTHOLDER_H

#include <string>
#include <iostream>
#include <vector>
#include "account.h"

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
        AccountP & getAccountAt(int);
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
        void setLogin(string);
        string getLogin() const;
        double getAccountBalance(int) const;
        void createCheckingAccount(int);
        void createSavingsAccount(int, double);
        void createCDAccount(int, double, double);
        void changePassword(string);
        int numberOfAccounts() const;
        vector<AccountP> & getAccounts();
        string getType(int);
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

string AccountHolder::getType(int accountNumber)
{
    for(int i = 0; i < accounts.size(); i++)
    {
        if(accounts[i].getAccountNumber() == accountNumber)
        {
            return accounts[i].getType();
        }
    }
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

AccountP AccountHolder::findAccount(int accountNumber)
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
        return accounts[location];
    }
    else
    {
        cout << "Account with account number: " << accountNumber << " does not exist\n";
    }
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

double AccountHolder::getAccountBalance(int accountNumber) const
{
    bool found = false;
    for(int i = 0; i < accounts.size(); i++)
    {
        if(accounts[i].getAccountNumber() == accountNumber)
        {
            found = true;
            return accounts[i].getBalance();
        }
    }

    if(!found)
    {
        cout << "This Account does not exist\n";
        return -1;
    }
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
#endif