#include <iostream>
#include "account.h"
#include "AccountHolder.h"
#include "BankOfficial.h"
#include "Admin.h"
#include <vector>
#include <list>
#include <fstream>
#include <ctime>

using namespace std;

string encrypt(string input);

string decrypt(string input);

int main()
{

    tm *newTime;

    int ten;


    newTime->tm_mday = ten;

    cout << newTime->tm_mday;
}

string encrypt(string input)
{
    for(int i = 0; i < input.length(); i++)
            input[i] = input[i] + 2;

    return input;
}

string decrypt(string input)
{
    for(int i = 0; i < input.length(); i++)
            input[i] = input[i] - 2;

    return input;
}

