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

    Admin admin;
    string newPass;

    cout << "Please enter a new Password: ";
    getline(cin, newPass);
    admin.setPassword(newPass);
    cout << "Password change successful\n";
    cout << admin.getPassword() << endl;
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

