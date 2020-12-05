#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

using namespace std;

class Transaction
{
    public:
        int date[3];
        string action;
        double amount;
        string official;
        Transaction();
        string printTransaction();
};

Transaction::Transaction()
{
    date[0] = 0;
    date[1] = 0;
    date[2] = 2;
    action = "";
    amount = 0.0;
    official = "";
}

string Transaction::printTransaction()
{
    string returnLine = to_string(date[0]) +"/"+to_string(date[1])+"/"+to_string(date[2]) + " " + action + " " + "$" + to_string(amount) + " Official: " + official;
    return returnLine;

}

#endif