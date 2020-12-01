#ifndef ADMIN_H
#define ADMIN_H

#include "account.h"
#include "BankOfficial.h"
#include "AccountHolder.h"
#include <iostream>
#include <string>

using namespace std;

class Admin
{
    private:
        string firstName, lastName, login, password;
        int id;
    public:
        Admin(string, string, string, string, int);
        string getFirstName() const;
        void setFirstName(string);
        string getLastName() const;
        void setLastName(string);
        string getLogin() const;
        void setLogin(string);
        void setPassword(string);
        string getPassword();
        void setID(int);
        int getID() const;
        void enableBankOfficial(BankOfficial &);
        void disableBankOfficial(BankOfficial &);
        string getUserLogin(AccountHolder) const;
        string getUserLogin(BankOfficial) const;
        string getUserLogin(Admin) const;
        void setUserPassword(AccountHolder &, string);
        void setUserPassword(BankOfficial &, string);
        void setUserPassword(Admin &, string);
        void modify(AccountHolder &, int, double);
        void modify(AccountHolder &, int, double, double);
};

Admin::Admin(string FirstName, string LastName, string Login, string Password, int ID)
{
    firstName = FirstName;
    lastName = LastName;
    login = Login;
    password = Password;
    id = ID;
}

void Admin::modify(AccountHolder &accHldr, int accountNumber, double intRate)
{
    bool found = false;

    int location = 0;

    for(int i = 0; i < accHldr.numberOfAccounts(); i++)
    {
        if(accHldr.getAccountAt(i).getAccountNumber() == accountNumber)
        {
            found = true;
            location = i;
        }
    }

    if(found)
    {
        if(intRate >= 0.0)
        {
           accHldr.getAccountAt(location).setInterest(intRate);
        }
        else
        {
            cout << "Please enter a valid amount\n";
        }
    }
    else
    {
        cout << "This account does not exist\n";
    }
}

void Admin::modify(AccountHolder &accHldr, int accountNumber, double intRate, double term)
{
    bool found = false;

    int location = 0;

    for(int i = 0; i < accHldr.numberOfAccounts(); i++)
    {
        if(accHldr.getAccountAt(i).getAccountNumber() == accountNumber)
        {
            found = true;
            location = i;
        }
    }

    if(found)
    {
        if(intRate >= 0.0 && term >= 0.0)
        {
           accHldr.getAccountAt(location).setInterest(intRate);
           accHldr.getAccountAt(location).setTerm(term);
        }
        else
        {
            cout << "Please enter a valid amount\n";
        }
    }
    else
    {
        cout << "This account does not exist\n";
    }
}

void Admin::setUserPassword(Admin &admin, string newPassword)
{
    admin.setPassword(newPassword);
}

void Admin::setUserPassword(BankOfficial &bankOfficial, string newPassword)
{
    bankOfficial.setPassword(newPassword);
}

void Admin::setUserPassword(AccountHolder &accountHolder, string newPassword)
{
    accountHolder.setPassword(newPassword);
}

string Admin::getUserLogin(Admin admin) const
{
    return admin.getLogin();
}

string Admin::getUserLogin(BankOfficial bankOfficial) const
{
    return bankOfficial.getLogin();
}

string Admin::getUserLogin(AccountHolder accHldr) const
{
    return accHldr.getLogin();
}

void Admin::disableBankOfficial(BankOfficial &bankOfficial)
{
    bankOfficial.setStatus("disable");
}

void Admin::enableBankOfficial(BankOfficial &bankOfficial)
{
    bankOfficial.setStatus("enable");
}

int Admin::getID() const
{
    return id;
}

void Admin::setID(int newId)
{
    id = newId;
}

void Admin::setPassword(string newPassword)
{
    password = newPassword;
}

string Admin::getPassword(){
    return password;
}

void Admin::setLogin(string Login)
{
    login = Login;
}

string Admin::getLogin() const
{
    return login;
}

string Admin::getFirstName() const
{
    return firstName;
}

void Admin::setFirstName(string newName)
{
    firstName = newName;
}

string Admin::getLastName() const
{
    return lastName;
}

void Admin::setLastName(string newName)
{
    lastName = newName;
}

#endif 