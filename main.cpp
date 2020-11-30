#include <iostream>
#include "AccountP.h"
#include "AccountHolder.h"
#include "bankOfficial.h"
#include "Admin.h"
#include <vector>

using namespace std;

void handleOfficialAdmin(vector<BankOfficial>& bankOfficials);
void modifyOfficial(vector<BankOfficial>&, int);
void handleAccountUser(string userName, int locationInV, vector<AccountHolder>& accountHolders);
void handleAccountOfficial(vector<AccountHolder>&, int, vector<BankOfficial>&, int);
void handleOfficialUser(string, int, vector<BankOfficial>&, vector<AccountHolder>&);
void searchForAccountHolder(vector<AccountHolder>& accountHolders,vector<BankOfficial>& bankOfficials, int location);
bool checkIfNumberI(string);
bool checkIfNumberD(string);

int main() {
   
  Admin admin("cole","kassing","ck115","butt",12345);
  vector<BankOfficial> bankOfficials;
  vector<AccountHolder> accountHolders;
  
  cout<<"Hello Welcome to Bear Bank"<<endl; 
  
  string userInput = "0";
  
  while(userInput != "4")
  {
      cout<<"Login as Admin[1]:"<<endl;
      cout<<"Login as Bank Official[2]:" << endl; 
      cout<<"Login as Account Holder[3]:" << endl;
      cout<<"Exit[4]:\n";
      getline(cin,userInput);
      
      if(userInput == "1")
      {
         string adminPassword;
         
         cout<<"Enter Admins Password:\n"<<endl;
         getline(cin, adminPassword); 
         
         if(adminPassword == admin.getPassword())
         {
            string adminChoice; 
            
            while(adminChoice != "4")
            {
               cout<<"Official Users[1]:" <<endl;
               cout<<"Acount Holders[2]:" <<endl;
               cout<<"Change admin Password[3]:"<<endl;
               cout<<"Exit[4]:\n";
               
               if(adminChoice == "1")
               {
                  handleOfficialAdmin(bankOfficials);
               }
               else if(adminChoice == "2")
               {
               }
               else if(adminChoice == "3")
               {
               }
               else if(adminChoice == "4")
               {
                  cout<<"Closing"<<endl;
               }
               else
               {
                  cout<<"Invalid Entry"<<endl;
               }
            }
         }
         else
         {
            cout<<"Incorrect Password"<<endl; 
         }
         
      }
      else if(userInput == "2")
      {
         string officalName;
         int location = 0;
         bool ifPresent = false; 
         
         cout<<"Enter Bank Official Login:\n";
         getline(cin,officalName);
         
         for(int i =0; i < bankOfficials.size(); i++)
         {
            if (bankOfficials[i].getLogin() == officalName)
            {
               ifPresent = true;
               location = i;
            }
         }
         
         if(ifPresent && bankOfficials[location].getStatus() == true)
         {
            handleOfficialUser(officalName, location, bankOfficials,accountHolders);
         }
         else
         {
            cout<<"Account does not exsist or is closed " <<endl; 
         }
      }
      else if(userInput == "3")
      {
         string accountName;
         int location = 0;
         bool ifPresent = false; 
         
         cout<<"Enter Account Login:\n";
         getline(cin,accountName);
         
         for(int i =0; i < accountHolders.size(); i++)
         {
            if (accountHolders[i].getLogin() == accountName)
            {
               ifPresent = true;
               location = i;
            }
         }
         
         if(ifPresent)
         {
            handleAccountUser(accountName, location, accountHolders);
         }
         else
         {
            cout<<"Account does not exsist" <<endl; 
         }
      }   
      else if(userInput == "4")
      {
      }  
      else
      {
         cout<<"invalid Entry"<<endl;
      }
  }
  
  return 0;
}


void handleAccountUser(string userName, int locationInV, vector<AccountHolder>& accountHolders)
{
   string userEnter;
   cout<<"Enter password for account";
   int i = locationInV;
   
   getline(cin, userEnter);
   
   string accountPassword = accountHolders[i].getPassword();
   
   if(userEnter == accountPassword)
   {
      string accountChoice;
      
      
      while(accountChoice != "4");
      {
      
         cout<<"Change Password[1]:" <<endl;
         cout<<"View Your Current Accounts[2]:" << endl;
         cout<<"View Account[3]:" << endl;
         cout<<"Exit[4]:\n";
      
         getline(cin, accountChoice);
      
         if(accountChoice == "1")
         {
            string newPassword; 
            
            cout<<"Enter New Password:\n";
            getline(cin,newPassword);
            
            accountHolders[i].changePassword(newPassword);
            
            cout<<"Password has been Changed"<<endl;
         }
         else if(accountChoice == "2")
         {
            accountHolders[i].printAccounts();
         }
         else if(accountChoice == "3")
         {
            string accountIdS;
            
            cout<<"Enter Account id"<<endl;
            getline(cin,accountIdS);
            
            bool truth = checkIfNumberI(accountIdS);
            
            
            if(truth)
            {
               int accountNum = stoi(accountIdS);
               accountHolders[i].printAccountInfo(accountNum);
            }
            
         }
         else if(accountChoice == "4")
         {
            cout<<"Goodbye"<<endl;
         }
         else
         {
            cout<<"invalid entry, try again" << endl;
         }
      }
      
   }
   else
   {
      cout<<"password is inccorrect" << endl; 
   }
}

void handleOfficialUser(string userName, int locationInV, vector<BankOfficial>& bankOfficials,vector<AccountHolder>& accountHolders)
{
   string userEnter;
   cout<<"Enter password for account";
   int i = locationInV;
   
   getline(cin, userEnter);
   
   string accountPassword = bankOfficials[i].getPassword();
   
   if(userEnter == accountPassword)
   {
      string accountChoice;
      
      
      while(accountChoice != "3");
      {
      
         cout<<"Search for Users[1]:" <<endl;
         cout<<"Access Users[2]:" << endl;
         cout<<"Exit[3]:\n";
         
         if(accountChoice == "1")
         {
            searchForAccountHolder(accountHolders, bankOfficials, locationInV);
         }
         else if(accountChoice == "2")
         {
            string accountName;
            int location = 0;
            bool ifPresent = false; 
         
            cout<<"Enter Account Login:\n";
            getline(cin,accountName);
         
            for(int i =0; i < accountHolders.size(); i++)
            {
               if (accountHolders[i].getLogin() == accountName)
               {
                  ifPresent = true;
                  location = i;
               }
            }
            
            if(ifPresent)
            {
               handleAccountOfficial(accountHolders,location,bankOfficials, locationInV);
            }
            else
            {
               cout<<"account doesnt Exist"<<endl;
            }
         }
         else if(accountChoice == "3")
         {
            cout<<"Closing"<<endl;
         }
         else
         {
            cout<<"Invalid Entry, try again"<<endl;
         }
      }
      
   }
   else
   {
      cout<<"password is inccorrect" << endl; 
   }
}

void searchForAccountHolder(vector<AccountHolder>& accountHolders,vector<BankOfficial>& bankOfficials,int location)
{
   string userEnter;
   string userSearch;
   
   while(userEnter != "3")
   {
      cout<<"Search by Login[1]:"<<endl;
      cout<<"Search by phoneNumber or last name[2]:"<< endl;
      cout<<"Exit:\n";
      
      getline(cin, userEnter);
      
      
      if(userEnter == "1")
      {
         cout<<"Enter account Number:\n";
         
         getline(cin,userSearch);
         
         if(checkIfNumberI(userSearch))
         {
            int id = stoi(userSearch);
            
            bankOfficials[location].search(accountHolders, id);
         }
         else
         {
            cout<<"invalid Entry"<<endl;
         }
      }
      else if(userEnter == "2")
      {
         cout<<"Enter account last name or number\n:";
         
         getline(cin,userSearch);
         
         bankOfficials[location].search(accountHolders, userSearch);
      }
      else if(userEnter == "3")
      {
         cout<<"closing"<<endl;
      }
      else
      {
         cout<<"invalid Entry"<<endl;
      }
   }
}

void handleAccountOfficial(vector<AccountHolder>&  accountHolders, int locationAH, vector<BankOfficial>& bankOfficials, int locationBO)
{
   
   string userEnter;
   cout<<"Enter password for account";
   
   getline(cin, userEnter);
   
   string accountPassword = accountHolders[locationAH].getPassword();
   
   if(userEnter == accountPassword)
   {
      string accountChoice;
    
      while(accountChoice != "5")
      {
         cout<<"Open New Account[1]:"<<endl;
         cout<<"Close Account[2]:" <<endl; 
         cout<<"deposit[3]:" << endl;
         cout<<"withdraw[4]:" << endl;
         cout<<"Exit[5]:\n";
         
         if(accountChoice == "1")
         {
            string accountID;
            cout<<"Enter account number:\n";
            getline(cin, accountID);
            
            if(checkIfNumberI(accountID))
            {
               int id = stoi(accountID);
            
               bankOfficials[locationBO].openAccountD(accountHolders[locationAH], id);    
            }
            else
            {
               cout<<"invalid account id"<<endl;
            }
         }
         else if(accountChoice == "2")
         {
            string accountID;
            cout<<"Enter account number:\n";
            getline(cin, accountID);
            
            if(checkIfNumberI(accountID))
            {
               int id = stoi(accountID);
            
               bankOfficials[locationBO].closeAccount(accountHolders[locationAH], id);    
            }
            else
            {
               cout<<"invalid account id"<<endl;
            }

         }
         else if(accountChoice == "3")
         {
            string ammount;
            string accountID;
            cout<<"Enter account number:\n";
            getline(cin, accountID);
            
            if(checkIfNumberI(accountID))
            {
               int id = stoi(accountID);
            
               cout<<"Enter ammount:\n";
               getline(cin, ammount);
               
               if(checkIfNumberD(ammount))
               {
                  int ammountD = stod(ammount);
                  
                  bankOfficials[locationBO].deposit(accountHolders[locationAH], id, ammountD);
                  
               }
               else
               {
                  cout<<"invalid ammount" << endl; 
               }    
            }
            else
            {
               cout<<"invalid account id"<<endl;
            }
         }
         else if(accountChoice == "4")
         {
            string ammount;
            string accountID;
            cout<<"Enter account number:\n";
            getline(cin, accountID);
            
            if(checkIfNumberI(accountID))
            {
               int id = stoi(accountID);
            
               cout<<"Enter ammount:\n";
               getline(cin, ammount);
               
               if(checkIfNumberD(ammount))
               {
                  int ammountD = stod(ammount);
                  
                  bankOfficials[locationBO].withdraw(accountHolders[locationAH], id, ammountD);
                  
               }
               else
               {
                  cout<<"invalid ammount" << endl; 
               }    
            }
            else
            {
               cout<<"invalid account id"<<endl;
            }

         }
         else if(accountChoice == "5")
         {
            cout<<"closing"<<endl;
         }
         else
         {
            cout<<"invalid entry"<<endl;
         }
      }
   }
   else
   {
      cout<<"Password is Incorrect"<<endl;
   }
}

void handleOfficialAdmin(vector<BankOfficial>& bankOfficials)
{
   string officalName;
   int location = 0;
   bool ifPresent = false; 
         
   cout<<"Enter Bank Official Login:\n";
   getline(cin,officalName);
         
   for(int i =0; i < bankOfficials.size(); i++)
   {
      if (bankOfficials[i].getLogin() == officalName)
      {
         ifPresent = true;
         location = i;
      }
   }
         
   if(ifPresent && bankOfficials[location].getStatus() == true)
   {
      string userEnter;
      cout<<"Enter password for account";
   
      getline(cin, userEnter);
   
      string accountPassword = bankOfficials[location].getPassword();
   
      if(userEnter == accountPassword)
      {
         string accountChoice;
    
         while(accountChoice != "3")
         {
            cout<<"Create Official[1]:"<<endl;
            cout<<"Modify Official[2]:" <<endl; 
            cout<<"Exit[3]:\n";
            
            getline(cin,accountChoice);
            
            if(accountChoice == "1")
            {
               string firstName, lastName, login, password,ids;
               int id;
               
               cout<<"Enter new user id"<<endl;
               getline(cin,ids);
               
               if(checkIfNumberI(ids))
               {
                  id = stoi(ids);
                  
                  bool value= true;
                  
                  for(int i =0; i < bankOfficials.size();i++)
                  {
                     if(bankOfficials[i].getID() == id)
                     {
                        value = false;
                     }
                  }
                  
                  if(value)
                  {
                     cout<<"Enter first Name\n";
                     getline(cin,firstName);
                     
                     cout<<"Enter lastName\n";
                     getline(cin,lastName);
                     
                     cout<<"Enter login\n";
                     getline(cin,login);
                     
                     cout<<"Enter password\n";
                     getline(cin,password);
                     
                     BankOfficial newOfficial(firstName,lastName, id, login, password);
                     
                     bankOfficials.push_back(newOfficial);
                  }
                  else
                  {
                     cout<<"number doesnt exsist"<<endl;
                  }
               }
               else
               {
                  cout<<"invalid Number"<<endl;
               }
            }
            else if(accountChoice == "2")
            {
               string officalName;
               int location = 0;
               bool ifPresent = false; 
               
               cout<<"Enter Bank Official Login:\n";
               getline(cin,officalName);
               
               for(int i =0; i < bankOfficials.size(); i++)
               {
                  if (bankOfficials[i].getLogin() == officalName)
                  {
                     ifPresent = true;
                     location = i;
                  }
               }
               
               if(ifPresent)
               {
                  modifyOfficial(bankOfficials, location);
               }
               else
               {
                  cout<<"Account does not exsist or is closed " <<endl; 
               }
            }
            else if(accountChoice == "3")
            {
               cout<<"closing" <<endl;
            }
            else
            {
               cout<<"invalid Entry" <<endl; 
            }
         }
       }
       else
       {
         cout<<"Password is Incorrect"<<endl;
       }
   }
   else
   {
       cout<<"Account does not exsist or is closed " <<endl; 
   }   
}

void modifyOfficial(vector<BankOfficial>& bankOfficials, int location)
{
   string userEnter; 
   while(userEnter != "3");
   {
      cout<<"activate/deactivate[1];"<<endl;
      cout<<"change password[2]:"<<endl;
      cout<<"Exit[3]:\n";
      
      getline(cin,userEnter);
      
      if(userEnter == "1")
      {
         string choice;
      
         cout<<"Set Active[1]"<<endl;
         cout<<"Deactivate[2]\n";
         getline(cin,choice);
         
         if(choice == "1")
         {
            bankOfficials[location].setStatus("enable");
         }
         else if(choice == "2")
         {
            bankOfficials[location].setStatus("disable");
         }
         else
         {
            cout<<"Invalid Entry"<<endl;
         }
      }
      else if(userEnter == "2")
      {
         string password; 
         
         cout<<"Enter new password\n";
         getline(cin,password);
         
         bankOfficials[location].setPassword(password);        
      }
      else if(userEnter == "3")
      {
         cout<<"closing" <<endl;
      }
      else
      {
         cout<<"Invalid Entry"<<endl;
      }
   }
   
   
}

bool checkIfNumberI(string number) 
{
   //checks to see if the number is double or not 
   try
   {
      int test = stoi(number);
   }
   catch(const invalid_argument&)
   {
      return false;
   }
   return true;
}

bool checkIfNumberD(string number) 
{
   //checks to see if the number is double or not 
   try
   {
      int test = stod(number);
   }
   catch(const invalid_argument&)
   {
      return false;
   }
   return true;
}
