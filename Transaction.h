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

#endif