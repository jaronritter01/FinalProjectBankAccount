#ifndef ACCOUNTP_H
#define ACCOUNTP_H

#include <string>
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

class AccountP
{
    private:
        bool status;
        double interestRate =0.0, termLength, balance =0.0,monthlyServiceFee;
        int accountNumber,term =0;
        string type;
        tm* timeCreated;
        tm* timeNow;
        tm* lastOpen;
        tm* timeClosed;
        tm* maturity;
        vector<string> transactions;
        

    public:
        AccountP(int, double);
        int getAccountNumber();
        double getBalance();
        void setInterest(double);
        double getInterest();
        string getType();
        void setType(string);
        bool getStatus();
        void setStatus(bool);
        string getDateCreated() const;
        string getDateClosed() const;
        string getDateLastOpen() const;
        string getMaturity() const; 
        void withdraw(double,string);
        void deposit(double,string);
        void setCreationTime();
        void setCreationTimeFile(string);
        void setTimeNow();
        void setLastOpen(string);
        void closeAccount();
        void setCloseAccountFile(string);
        void setTerm(int);
        void setMonTerm(double);
        double getMonTerm();
        void calculateInt();
        void calculateMonTerm();
        void setMaturity();
        bool checkMaturity();
        void printTransactions();
        

};

AccountP::AccountP(int newAccountNumber, double newBalance)
{
    accountNumber = newAccountNumber;
    balance = newBalance;  
    status = true;
}

int AccountP:: getAccountNumber()
{ 
   return accountNumber;
}

void AccountP:: setCreationTime()
{
    time_t currentTime;
    time(&currentTime);
    timeCreated = localtime(&currentTime);
}

void AccountP:: setCreationTimeFile(string date)
{
   
   int mon = stoi(date.substr(0, date.find("/")));
   date = date.substr(date.find("/") +1 , date.length());
   int day = stoi(date.substr(0, date.find("/")));
   date = date.substr(date.find("/") +1 , date.length());
   int year = stoi(date.substr(0, date.length()));
   
   timeCreated->tm_mday = day;
   timeCreated->tm_mon = mon - 1;
   timeCreated->tm_year = year - 1900;
   
}

void AccountP:: setTimeNow()
{
    time_t currentTime;
    time(&currentTime);
    timeNow = localtime(&currentTime);
}

void AccountP:: setLastOpen(string date)
{
   
   int mon = stoi(date.substr(0, date.find("/")));
   date = date.substr(date.find("/") +1 , date.length());
   int day = stoi(date.substr(0, date.find("/")));
   date = date.substr(date.find("/") +1 , date.length());
   int year = stoi(date.substr(0, date.length()));
   
   lastOpen->tm_mday = day;
   lastOpen->tm_mon = mon - 1;
   lastOpen->tm_year = year - 1900;
}

void AccountP:: setInterest(double Interest)
{
   interestRate = Interest;
}

double AccountP:: getInterest()
{
   return interestRate;
}

double AccountP:: getBalance()
{
   return balance;
}

void AccountP:: setType(string newType)
{
   type = newType;
}

string AccountP:: getType()
{
   return type;
}

void AccountP:: setStatus(bool value)
{
   status = value;
}

bool AccountP:: getStatus()
{
   return status;
}

string AccountP::getDateCreated() const{
    //Getter for the creation date of the account
    string dateLine, day, month, year;
    day = to_string(timeCreated->tm_mday);
    month = to_string(timeCreated->tm_mon + 1);
    year = to_string(timeCreated->tm_year + 1900);
    dateLine = month + "/" + day + "/" + year;
    
    return dateLine;
}

string AccountP::getDateClosed() const
{
    string dateLine, day, month, year;
    day = to_string(timeClosed->tm_mday);
    month = to_string(timeClosed->tm_mon + 1);
    year = to_string(timeClosed->tm_year + 1900);
    dateLine = month + "/" + day + "/" + year;
    
    return dateLine;

}

string AccountP::getDateLastOpen () const
{
    string dateLine, day, month, year;
    day = to_string(lastOpen->tm_mday);
    month = to_string(lastOpen->tm_mon + 1);
    year = to_string(lastOpen->tm_year + 1900);
    dateLine = month + "/" + day + "/" + year;
    
    return dateLine;

}

string AccountP::getMaturity () const
{
    string dateLine, day, month, year;
    day = to_string(maturity->tm_mday);
    month = to_string(maturity ->tm_mon + 1);
    year = to_string(maturity->tm_year + 1900);
    dateLine = month + "/" + day + "/" + year;
    
    return dateLine;

}
void AccountP::withdraw(double amount, string bankOfficialName)
{
    tm* wTime;
    if(status == true)
    {
       if(amount > 0)
       {
           if(amount < balance)
           {
               balance -= amount;
               
               time_t withdrawTime;
               time(&withdrawTime);
               wTime = localtime(&withdrawTime);
               
               string dateLine, day, month, year;
               day = to_string(wTime->tm_mday);
               month = to_string(wTime->tm_mon + 1);
               year = to_string(wTime->tm_year + 1900);
               dateLine = month + "/" + day + "/" + year;
               
               transactions.push_back(dateLine + " withdrew $" + to_string(amount) + "Official: " + bankOfficialName); 
                           
           }
           else
           {
               cout<< "Not enough in Account" <<endl;
           }
       }
       else
       {
           cout << "Invalid amount entered\n";
       }
    }
    else
    {
      cout << " Account is closed" <<endl;
    }
}

void AccountP::deposit(double amount, string bankOfficialName)
{
    tm* dTime;
    if(status == true)
    {
       if(amount > 0)
       {
            balance += amount;
               
            time_t depositTime;
            time(&depositTime);
            dTime = localtime(&depositTime);
               
            string dateLine, day, month, year;
            day = to_string(dTime->tm_mday);
            month = to_string(dTime->tm_mon + 1);
            year = to_string(dTime->tm_year + 1900);
            dateLine = month + "/" + day + "/" + year;
            
            if(term != 0 && checkMaturity() == false)
            {
               interestRate = 0;
            }
               
            transactions.push_back(dateLine + " deposited $" + to_string(amount) + "Official: " + bankOfficialName);             
       }
       else
       {
           cout << "Invalid amount entered\n";
       }
    }
    else
    {
      cout << " Account is closed" <<endl;
    }
}


void AccountP :: closeAccount()
{
   status = false;
   balance = 0; 
   type += "(Closed)";
   
   time_t currentTime;
   time(&currentTime);
   timeClosed = localtime(&currentTime);  
}

void AccountP:: setCloseAccountFile(string date)
{
   int mon = stoi(date.substr(0, date.find("/")));
   date = date.substr(date.find("/") +1 , date.length());
   int day = stoi(date.substr(0, date.find("/")));
   date = date.substr(date.find("/") +1 , date.length());
   int year = stoi(date.substr(0, date.length()));
   
   timeClosed->tm_mday = day;
   timeClosed->tm_mon = mon - 1;
   timeClosed->tm_year = year - 1900;
}

void AccountP:: setTerm(int years)
{
   term = years; 
}

void AccountP:: setMonTerm(double amount)
{
   monthlyServiceFee = amount;
}

double AccountP:: getMonTerm()
{
   return monthlyServiceFee;
}

void AccountP:: calculateInt()
{
   if(term ==0 || checkMaturity() == true)
   {
      time_t oldDate = mktime(lastOpen);
      time_t newDate = mktime(timeNow);
      
      double days = difftime(newDate, oldDate)/(60*60*24);
      
      if(interestRate != 0)
      {
         for(int i= 0; i < days; i++)
         {
            double dailyInterestRate = interestRate / 365.25;
            double dailyInterest = balance * dailyInterestRate;
            balance += dailyInterest;
         }
      }
   }
}

void AccountP:: calculateMonTerm()
{
   time_t oldDate = mktime(lastOpen);
   time_t newDate = mktime(timeNow);
   
   double days = difftime(newDate, oldDate)/(60*60*24);
   double months = days/12; 
   
   for(int i= 0; i < months; i++)
   {
      balance -= monthlyServiceFee;
   }
}

void AccountP:: setMaturity()
{
   int day,month,year;
   
    day = timeCreated->tm_mday;
    month = timeCreated->tm_mon;
    year = timeCreated->tm_year;
    
    maturity->tm_mday = day;
    maturity->tm_mon = month;
    maturity->tm_year = year + term;
    
}

bool AccountP:: checkMaturity()
{
   time_t currentTime = mktime(timeNow);
   time_t maturityTime = mktime(maturity);
   
   double seconds = difftime(currentTime, maturityTime);
   
   if(seconds <= 0)
   {
      return true;
   }
   
   return false;
}

void AccountP:: printTransactions()
{
   for(int i =0; i < transactions.size();i++)
   {
      cout<< transactions[i]<< endl;
   }
}
#endif
