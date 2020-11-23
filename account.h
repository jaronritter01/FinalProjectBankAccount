#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>

using namespace std;

class Account
{
    private:
        string holderFirstName, holderLastName, phoneNumber, address;
        double interestRate, termLength, balance;
        int accountNumber;

    public:
        Account(string, string, string, string);
        string getFirstName() const;
        string getLastName() const;
        string getPhoneNumber() const;
        string getAddress() const;
        double getInterestRate() const;
        double getTermLength() const;
        double getBalance() const;
        int getAccountNumber() const;
        void setFirstName(string);
        void setLastName(string);
        void setPhoneNumber(string);
        void setAddress(string);
        void setInterestRate(double);
        void setTermLength(double);
        void withdraw(double);
        void deposit(double);

};

Account::Account(string FirstName, string LastName, string PhoneNumber, string Address){
    holderFirstName = FirstName;
    holderLastName = LastName;
    phoneNumber = PhoneNumber;
    address = Address;
}

string Account::getFirstName() const
{
    return holderFirstName;
}

string Account::getLastName() const
{
    return holderLastName;
}

string Account::getPhoneNumber() const
{
    return phoneNumber;
}

string Account::getAddress() const
{
    return address;
}

double Account::getInterestRate() const
{
    return interestRate;
}

double Account::getTermLength() const
{
    return termLength;
}

double Account::getBalance() const
{
    return balance;
}

int Account::getAccountNumber() const
{
    return accountNumber;
}

void Account::setFirstName(string newFirstName)
{
    holderFirstName = newFirstName;
}

void Account::setLastName(string newLastName)
{
    holderLastName = newLastName;
}

void Account::setAddress(string newAddress)
{
    address = newAddress;
}

void Account::setPhoneNumber(string newPhoneNumber)
{
    phoneNumber = newPhoneNumber;
}

void Account::setInterestRate(double intRate)
{
    interestRate = intRate;
}

void Account::setTermLength(double termLen)
{
    termLength = termLen;
}

void Account::withdraw(double amount)
{
    if(amount > 0)
    {
        balance += amount;
    }
    else
    {
        cout << "Invalid amount entered\n";
    }
}

void Account::deposit(double amount)
{
    if(amount > 0)
    {
        balance -= amount;
    }
    else
    {
        cout << "Invalid amount entered\n";
    }
}
#endif