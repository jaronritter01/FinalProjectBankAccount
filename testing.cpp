#include <iostream>
#include "account.h"
#include "AccountHolder.h"
#include "BankOfficial.h"
#include "Admin.h"
#include <vector>
#include <list>
#include <fstream>

using namespace std;

int main()
{

    Admin admin("Jaron","Ritter","jr1915", "admin", 10);
    int choice = 0;

    while(choice != 4)
    {
        cout<<"[1]Login as Admin: "<<endl;
        cout<<"[2]Login as Bank Official: " << endl; 
        cout<<"[3]Login as Account Holder: " << endl;
        cout<<"[4]Exit: \n";

        cin >> choice;

        cin.ignore();
        switch(choice)
        {
            case 1:
            {
                string adminPassword, adminsLogin;

                
         
                cout<<"Enter Admins Login: ";
                getline(cin, adminsLogin); 
                cout<<"Enter Admins password: ";
                getline(cin, adminPassword);
                
                if(adminPassword == admin.getPassword() && adminsLogin == admin.getLogin())
                {
                    int adminChoice = 0; 
                    
                    while(adminChoice != 4)
                    {
                    cout<<"\n[1]Official Users: \n";
                    cout<<"[2]Acount Holders: \n";
                    cout<<"[3]Change admin Password: \n";
                    cout<<"[4]Exit:\n";

                    cin >> adminChoice;
                    
                    switch(adminChoice)
                    {
                        case 1:
                        {
                            break;
                        }
                        case 2:
                        {
                            break;
                        }
                        case 3:
                        {
                            break;
                        }
                        case 4:
                        {
                            cout << "Logging out...\n";
                            break;
                        }
                    }

                    }
                }
                else
                {
                    cout<<"Incorrect UserName or Password"<<endl; 
                }
         
                break;
            }
            case 2:
            {
                break;
            }
            case 3:
            {
                break;
            }
            case 4:
            {
                cout << "Goodbye!\n";
                break;
            }
            default:
            {
                cout << "Invalid Choice\n";
                break;
            }
        }
    }
    return 0;
}
