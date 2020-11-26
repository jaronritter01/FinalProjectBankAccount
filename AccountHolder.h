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
        vector <Account> accounts;

    public:
        AccountHolder(string, string, string, string, string, string);
        void withdraw(int, double);
        void deposit(int, double);
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
        void createSavingsAccount(int, int);
        void createCDAccount(int, int, int);
        void changePassword(string);
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

void AccountHolder::withdraw(int accountNumber, double amount)
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
            accounts[location].withdraw(amount);
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

void AccountHolder::deposit(int accountNumber, double amount)
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
        if(amount > 0)
        {
            accounts[location].deposit(amount);
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
        Account newAccount(accountNumber);
        accounts.push_back(newAccount);
    }
    else
    {
        cout << "An account with this Account Number already exists\n";
    }
}

void AccountHolder::createSavingsAccount(int accountNumber, int interestRate)
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
        Account newAccount(accountNumber);
        newAccount.setInterestRate(interestRate);
        accounts.push_back(newAccount);
    }
    else
    {
        cout << "An account with this Account Number already exists\n";
    }
}

void AccountHolder::createCDAccount(int accountNumber, int interestRate, int term)
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
        Account newAccount(accountNumber);
        newAccount.setInterestRate(interestRate);
        newAccount.setTermLength(term);
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