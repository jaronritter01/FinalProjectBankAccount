#include <iostream>
#include "AccountP.h"
#include "AccountHolder.h"
#include "BankOfficial.h"
#include "Admin.h"
#include <vector>
#include <list>
#include <fstream>

using namespace std;

void handleOfficialAdmin(vector<BankOfficial>& bankOfficials);
void handleHoldersAdmin(vector<AccountHolder>& accountHolders);
void modifyOfficial(vector<BankOfficial>&, int);
void modifyHolder(vector<AccountHolder>&, int);
void createAccounts(vector<AccountHolder>&, int);
void modifyAccounts(vector<AccountHolder>&, int);
void handleAccountUser(string userName, int locationInV, vector<AccountHolder>& accountHolders);
void handleAccountOfficial(vector<AccountHolder>&, int, vector<BankOfficial>&, int);
void handleOfficialUser(string, int, vector<BankOfficial>&, vector<AccountHolder>&);
void searchForAccountHolder(vector<AccountHolder>& accountHolders,vector<BankOfficial>& bankOfficials, int location);
bool checkIfNumberI(string);
bool checkIfNumberD(string);
string encrypt(string input);
string decrypt(string input);

int main() {

   
    fstream inputFile;
    inputFile.open("input.txt"); 
    string line = "";
    vector <BankOfficial> bankOfficials;
    vector <AccountHolder> accountHolders;
    Admin admin;

    while(getline(inputFile, line))
    {
        if(line == "ADMIN")
        {
            getline(inputFile, line);

            string firstName = line.substr(0, line.find(" ")); //first name
            line = line.substr(line.find(" ")+1, line.length());
            
            string lastName = line.substr(0, line.find(" ")); // last name
            line = line.substr(line.find(" ")+1, line.length());

            string login = decrypt(line.substr(0, line.find(" "))); // login
            line = line.substr(line.find(" ")+1, line.length());

            string password = decrypt(line.substr(0, line.find(" "))); // password
            line = line.substr(line.find(" ")+1, line.length());

            int id = stoi(line); // ID

            admin.setFirstName(firstName);
            admin.setLastName(lastName);
            admin.setID(id);
            admin.setPassword(password);
            admin.setLogin(login);
        }
        else if(line == "BANKOFFICIAL")
        {
            getline(inputFile, line);

            string firstName = line.substr(0, line.find(" ")); // first name
            line = line.substr(line.find(" ")+1, line.length());

            string lastName = line.substr(0, line.find(" ")); // last name
            line = line.substr(line.find(" ")+1, line.length());

            string login = decrypt(line.substr(0, line.find(" "))); // login
            line = line.substr(line.find(" ")+1, line.length());

            string password = decrypt(line.substr(0, line.find(" "))); // password
            line = line.substr(line.find(" ")+1, line.length());

            int id = stoi(line); // ID
            
            string status;
            
            getline(inputFile, status);

            BankOfficial newBankOfficial(firstName, lastName, id, login, password);
            newBankOfficial.setStatus(status);
            bankOfficials.push_back(newBankOfficial);
        }
        else if(line == "ACCOUNTHOLDER")
        {
            getline(inputFile, line);

            string firstName = line.substr(0, line.find(" ")); // first name 
            line = line.substr(line.find(" ")+1, line.length());

            string lastName = line.substr(0, line.find(" ")); // last name
            line = line.substr(line.find(" ")+1, line.length());

            string phoneNumber = line.substr(0, line.find(" ")); // phone number
            line = line.substr(line.find(" ")+1, line.length());

            string login = decrypt(line.substr(0, line.find(" "))); // login
            line = line.substr(line.find(" ")+1, line.length());

            string password = decrypt(line.substr(0, line.find(" "))); // password
            line = line.substr(line.find(" ")+1, line.length()); 

            string address = line.substr(0, line.find(" "));
            line = line.substr(line.find(" ")+1, line.length());
            
            string id = line; // address (might contain spaces)
            

            AccountHolder newAccountHolder(firstName, lastName, address, phoneNumber, password, login);
            newAccountHolder.setId(stoi(id));

            getline(inputFile, line);
            int numberOfAccounts = stoi(line); 

            for(int i = 0; i < numberOfAccounts; i++)
            {
                getline(inputFile, line);

                int accountNumber = stoi(line.substr(0, line.find(" "))); //reads in the account number
                line = line.substr(line.find(" ")+1, line.length());

                double balance = stod(line.substr(0, line.find(" "))); // reads in the balance
                line = line.substr(line.find(" ")+1, line.length());

                double interestRate = stod(line.substr(0, line.find(" "))); // reads in the interest rate
                line = line.substr(line.find(" ")+1, line.length());

                double termLength = stod(line); // reads in the term Length
                
                AccountP newAccount(accountNumber, balance); // initalizes newAccount
                newAccount.setInterest(interestRate); //sets interest
                newAccount.setTerm(termLength); //sets term
                
                string status;
                getline(inputFile,status);
                
                if(status == "true")
                {
                  newAccount.setStatus(true);
                }
                else
                {
                  newAccount.setStatus(false);
                }
                
                string type;
                getline(inputFile,type);
                
                newAccount.setType(type);

                getline(inputFile, line);
                string creationTime = line;
                newAccount.setCreationTimeFile(line);

                getline(inputFile, line);

                string lastOpenedTime = line;
                newAccount.setLastOpen(line);

                newAccount.setMaturity();
                newAccount.setTimeNow();

                newAccount.calculateInt();
                getline(inputFile, line); // reads number of transactions for this account;
                
                int numOfTransactions = stoi(line);

                for(int j = 0; j < numOfTransactions; j++)
                {
                    getline(inputFile, line); // gets transaction record
                        
                    Transaction transaction;

                    string dateLine = line.substr(0,line.find(" "));
                    line = line.substr(line.find(" ")+1, line.length());

                    transaction.date[0] = stoi(dateLine.substr(0,'/')); // sets month for this transaction
                    dateLine = dateLine.substr(dateLine.find('/')+1, dateLine.length());
                    transaction.date[1] = stoi(dateLine.substr(0,'/')); // sets day 
                    dateLine = dateLine.substr(dateLine.find('/')+1, dateLine.length());
                    transaction.date[2] = stoi(dateLine); // sets year 

                    transaction.action = line.substr(0,line.find(" ")); // sets action taken
                    line = line.substr(line.find(" ")+1, line.length());

                    string amountLine = line.substr(0,line.find(" "));
                    transaction.amount = stod(amountLine.substr(1, amountLine.length())); // chops off the dollar sign
                    line = line.substr(line.find(" ")+1, line.length());

                    line = line.substr(line.find(" ")+1, line.length()); // gets rid of the word Official:

                    transaction.official = line; //sets the name of the official that made the trasaction

                    newAccount.addTransation(transaction); // adds this tranaction to the transaction list
                }

                newAccountHolder.addAccount(newAccount); //adds the account to the list of accounts for an account holder
            }
            accountHolders.push_back(newAccountHolder); 
            
        }
        else
        {
            cout << "Invalid Data\n";
        }

    }
    inputFile.close();
    

  cout<<"Hello, Welcome to Bear Bank"<<endl; 
  
  string userInput = "0";
  
  /*
      Following while loop is the main menu give the choices for which 
      account you want to log in.
  */
  while(userInput != "4")
  {
      cout<<"Login as Admin[1]:"<<endl;
      cout<<"Login as Bank Official[2]:" << endl; 
      cout<<"Login as Account Holder[3]:" << endl;
      cout<<"Exit[4]:\n";
      getline(cin, userInput);
      
      //if users chooses to login as admin
      if(userInput == "1")
      {
         //gets password and if it works gives menu for admin else prints invalid password or username
         string adminPassword, adminsLogin;
         
         cout<<"Enter Admins Login: ";
         getline(cin, adminsLogin); 
         cout<<"Enter Admins password: ";
         getline(cin, adminPassword);
         
         if(adminPassword == admin.getPassword() && adminsLogin == admin.getLogin())
         {
            string adminChoice = "0"; 
            cout<<"Success"<<endl;
            
            while(adminChoice != "4")
            {
               //choices for the admin
               cout<<"Official Users[1]:" <<endl;
               cout<<"Acount Holders[2]:" <<endl;
               cout<<"Change admin Password[3]:"<<endl;
               cout<<"Exit[4]:\n";

               getline(cin, adminChoice);
               
               if(adminChoice == "1")
               {
                  //funciton handles the official user functions for admin
                  handleOfficialAdmin(bankOfficials);
               }
               else if(adminChoice == "2")
               {
                  //function handles the holder functions for admin
                  handleHoldersAdmin(accountHolders);
               }
               else if(adminChoice == "3")
               {  
                  //changes password 
                  cout << "Please enter a new Password: ";
                  string newPassword;
                  getline(cin, newPassword);
                  admin.setPassword(newPassword);
                  cout << "Password change successful\n";
               }
               else if(adminChoice == "4")
               {
                  //exist the menu
                  cout<<"Closing"<<endl;
               }
               else
               {
                  //if no valid choice is chosen
                  cout<<"Invalid Entry"<<endl;
               }
            }
         }
         else
         {
            cout<<"Incorrect UserName or Password"<<endl; 
         }
         
      }
      //handles the choice for loging in to official
      else if(userInput == "2")
      {
         //requests the official name and checks to see if it exsists
         
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
            //function for official users functions 
            handleOfficialUser(officalName, location, bankOfficials,accountHolders);
         }
         else
         {
            //returns print if account doesnt exists
            cout<<"Account does not exsist or is closed " <<endl; 
         }
      }
      //handles if user chooses access account holder
      else if(userInput == "3")
      {
         //user enters a account login and sees if it exist 
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
            //function for handling account user 
            handleAccountUser(accountName, location, accountHolders);
         }
         else
         {
            cout<<"Account does not exsist" <<endl; 
         }
      }   
      else if(userInput == "4")
      {
         //exists the menu
         cout<<"Goodbye"<<endl;
      }  
      else
      {
         cout<<"invalid Entry"<<endl;
      }
  }

  //start of output handling

  
  fstream outFile;
  outFile.open("outputFile.txt");

  
  string adminDetails = admin.getFirstName() + " " + admin.getLastName() + " " + encrypt(admin.getLogin()) + " " + encrypt(admin.getPassword()) + " " + to_string(admin.getID());
  
  outFile << "ADMIN\n";
  
  outFile << adminDetails << "\n";

  
  string bankOfficialDetails = "", accountHolderDetails = "";

  
  for(int i = 0; i < bankOfficials.size(); i++)
  {
     outFile << "BANKOFFICIAL\n";
     bankOfficialDetails = bankOfficials[i].getFirstName() + " " + bankOfficials[i].getLastName() + " " + encrypt(bankOfficials[i].getLogin()) + " " + encrypt(bankOfficials[i].getPassword()) 
                           + " " + to_string(bankOfficials[i].getID());
     outFile << bankOfficialDetails << '\n';
     if(bankOfficials[i].getStatus() == true)
     {
         outFile<<"enable"<<endl;
     }
     else
     {
         outFile<<"disable"<<endl;
     }
  }
  
  for(int i = 0; i < accountHolders.size(); i++)
  {
     outFile << "ACCOUNTHOLDER\n";
     accountHolderDetails = accountHolders[i].getFirstName() + " " + accountHolders[i].getLastName() + " " + accountHolders[i].getPhoneNumber() + " " + encrypt(accountHolders[i].getLogin()) + " " 
                            + encrypt(accountHolders[i].getPassword()) + " " + accountHolders[i].getAddress() + " " + to_string(accountHolders[i].getId());

      outFile << accountHolderDetails << '\n';
      outFile << accountHolders[i].numberOfAccounts() << '\n';

      for(int j = 0; j < accountHolders[i].numberOfAccounts(); j++)
      {
         AccountP currAcc = accountHolders[i].getAccountAt(j);
         outFile << currAcc.getAccountNumber() << " " << currAcc.getBalance() << " " << currAcc.getInterest() << " " << currAcc.getTerm() << '\n';
         if(currAcc.getStatus() == true)
         {
            outFile<<"true"<< "\n";
         }
         else
         {
            outFile<<"false"<< "\n";
         }
         
         outFile << currAcc.getType()<<'\n';
         
         outFile << currAcc.getDateCreated() << '\n';
         outFile << currAcc.getTimeNow() << '\n';
         outFile << currAcc.numberOfTransactions() << '\n';

         for(int k = 0; k < currAcc.numberOfTransactions(); k++)
         {
            Transaction currTran = currAcc.getTransactionAt(k);
            outFile << currTran.date[0] << "/" << currTran.date[1] << "/" << currTran.date[2] << " " << currTran.action << " " << "$" << currTran.amount << " " << "Official: " << currTran.official << "\n";
         }
         
      }
  }
  
  
  outFile.close();
  return 0;
}


void handleAccountUser(string userName, int locationInV, vector<AccountHolder>& accountHolders)
{
   //function for handling account 
   //asks for the account password and sees if it matches 
   string userEnter;
   cout<<"Enter password for account: \n";
   int i = locationInV;
   
   getline(cin, userEnter);
   
   string accountPassword = accountHolders[i].getPassword();
   
   if(userEnter == accountPassword)
   {
      string accountChoice;
      
      
      while(accountChoice != "4")
      {
         //choices for the account holders 
         cout<<"Change Password[1]:" <<endl;
         cout<<"View Your Current Accounts[2]:" << endl;
         cout<<"View Account[3]:" << endl;
         cout<<"Exit[4]:\n";
      
         getline(cin, accountChoice);
      
         if(accountChoice == "1")
         {
            //changes password for account
            string newPassword; 
            
            cout<<"Enter New Password:\n";
            getline(cin,newPassword);
            
            accountHolders[i].changePassword(newPassword);
            
            cout<<"Password has been Changed"<<endl;
         }
         else if(accountChoice == "2")
         {
            //prints all different account id and there type
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
            //exits the menu
            cout<<"Goodbye"<<endl;
         }
         else
         {
            //print if the user enter does not work
            cout<<"invalid entry, try again" << endl;
         }
      } 
   }
   else
   {
      //print if password does not match
      cout<<"password is inccorrect" << endl; 
   }
}

void handleOfficialUser(string userName, int locationInV, vector<BankOfficial>& bankOfficials,vector<AccountHolder>& accountHolders)
{
   //handles official users 
   //requests password for account and sees if its valid 
   string userEnter;
   cout<<"Enter password for account\n";
   int i = locationInV;
   
   getline(cin, userEnter);
   
   string accountPassword = bankOfficials[i].getPassword();
   
   if(userEnter == accountPassword)
   {
      string accountChoice;
      
      
      while(accountChoice != "3")
      {
         //menu options for the official 
         cout<<"Search for Users[1]:" <<endl;
         cout<<"Access Users[2]:" << endl;
         cout<<"Exit[3]:\n";
         
         getline(cin,accountChoice);
         
         if(accountChoice == "1")
         {
            //function that handles serch for account users
            searchForAccountHolder(accountHolders, bankOfficials, locationInV);
         }
         else if(accountChoice == "2")
         {
            //access account holders 
            //requests the account name and to see if it exists
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
               //if account exists moves into this function
               handleAccountOfficial(accountHolders,location,bankOfficials, locationInV);
            }
            else
            {
               //prints if account doesnt exist
               cout<<"account doesnt Exist"<<endl;
            }
         }
         else if(accountChoice == "3")
         {
            //exists the menu
            cout<<"Closing"<<endl;
         }
         else
         {
            //if no valid choices are chosen
            cout<<"Invalid Entry, try again"<<endl;
         }
      }
      
   }
   else
   {
      //if password is incorrcect 
      cout<<"password is inccorrect" << endl; 
   }
}

void searchForAccountHolder(vector<AccountHolder>& accountHolders,vector<BankOfficial>& bankOfficials,int location)
{
   //function for searching for account holders 
   string userEnter;
   string userSearch;
   
   while(userEnter != "3")
   {
      //menu for searching accounts 
      cout<<"Search by account number[1]:"<<endl;
      cout<<"Search by phoneNumber or last name[2]:"<< endl;
      cout<<"Exit[3]:\n";
      
      getline(cin, userEnter);
      
      
      if(userEnter == "1")
      {
         //if user chooses to search by id it checks to see if valid and returns the account information
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
         //searches by last name or the phone number
         cout<<"Enter account last name or number\n:";
         
         getline(cin,userSearch);
         
         bankOfficials[location].search(accountHolders, userSearch);
      }
      else if(userEnter == "3")
      {
         //exits menu
         cout<<"closing"<<endl;
      }
      else
      {
         //if value is invalid
         cout<<"invalid Entry"<<endl;
      }
   }
   
}

void handleAccountOfficial(vector<AccountHolder>&  accountHolders, int locationAH, vector<BankOfficial>& bankOfficials, int locationBO)
{
   //handles account official function for dealing with account holders 
   //checks to see if password matches user
   string userEnter;
   cout<<"Enter password for account";
   
   getline(cin, userEnter);
   
   string accountPassword = accountHolders[locationAH].getPassword();
   
   if(userEnter == accountPassword)
   {
      string accountChoice;
    
      while(accountChoice != "5")
      {
         //menu choices 
         cout<<"Open Account[1]:"<<endl;
         cout<<"Close Account[2]:" <<endl; 
         cout<<"deposit[3]:" << endl;
         cout<<"withdraw[4]:" << endl;
         cout<<"Exit[5]:\n";
         
         getline(cin, accountChoice);
         
         if(accountChoice == "1")
         {
            //searches for account inside holder and sets status as open
            string accountID;
            cout<<"Enter account number:\n";
            getline(cin, accountID);
            
            if(checkIfNumberI(accountID))
            {
               int id = stoi(accountID);
            
               bankOfficials[locationBO].openAccountD(id, accountHolders, locationAH);     
            }
            else
            {
               cout<<"invalid account id"<<endl;
            }
         }
         else if(accountChoice == "2")
         {
            //user enter account id and if it exsists sets status as inactive 
            string accountID;
            cout<<"Enter account number:\n";
            getline(cin, accountID);
            
            if(checkIfNumberI(accountID))
            {
               int id = stoi(accountID);
            
               bankOfficials[locationBO].closeAccount(id, accountHolders, locationAH);    
            }
            else
            {
               cout<<"invalid account id"<<endl;
            }

         }
         else if(accountChoice == "3")
         {
            //user enters a account number and sees if it exsists 
            string ammount;
            string accountID;
            cout<<"Enter account number:\n";
            getline(cin, accountID);
            
            if(checkIfNumberI(accountID))
            {
               int id = stoi(accountID);
               
               //requests the amount to deposit from user and cheks to see if it is valid
               cout<<"Enter ammount:\n";
               getline(cin, ammount);
               
               if(checkIfNumberD(ammount))
               {
                  double ammountD = stod(ammount);
                  
                  bankOfficials[locationBO].deposit(accountHolders[locationAH], id, ammountD);
                  
               }
               else
               {
                  // if amount is not valid 
                  cout<<"invalid ammount" << endl; 
               }    
            }
            else
            {
               //if account is invalid
               cout<<"invalid account id"<<endl;
            }
         }
         else if(accountChoice == "4")
         {
            //function is user wants to withdraw
            string ammount;
            string accountID;
            cout<<"Enter account number:\n";
            getline(cin, accountID);
            
            if(checkIfNumberI(accountID))
            {
               //checks to see if account id is valid
               int id = stoi(accountID);
            
               cout<<"Enter ammount:\n";
               getline(cin, ammount);
               
               if(checkIfNumberD(ammount))
               {
                  //checks to see if the user entered amount is valid
                  double ammountD = stod(ammount);
                  
                  bankOfficials[locationBO].withdraw(accountHolders[locationAH], id, ammountD);
                  
               }
               else
               {
                  //if amount is invalid
                  cout<<"invalid ammount" << endl; 
               }    
            }
            else
            {
               //if account is invalid
               cout<<"invalid account id"<<endl;
            }

         }
         else if(accountChoice == "5")
         {
            //exits menu
            cout<<"closing"<<endl;
         }
         else
         {
            //if entry is invalid
            cout<<"invalid entry"<<endl;
         }
      }
   }
   else
   {
      //if passord was incorrect
      cout<<"Password is Incorrect"<<endl;
   }
}

void handleOfficialAdmin(vector<BankOfficial>& bankOfficials)
{
         //function for handling officials functions for admin 
         string accountChoice;
         cout<<"Success"<<endl;
         cout<<"\n";
    
         while(accountChoice != "3")
         {
            //menu choices 
            cout<<"Create Official[1]:"<<endl;
            cout<<"Modify Official[2]:" <<endl; 
            cout<<"Exit[3]:\n";
            
            getline(cin,accountChoice);
            
            if(accountChoice == "1")
            {
               //function to create a new official
               string firstName, lastName, login, password,ids;
               int id;
               
               //enters id and sees if it exsist 
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
                  
                  if(value && id >0)
                  {
                     cout<<"Enter first Name\n";
                     getline(cin,firstName);
                     
                     cout<<"Enter lastName\n";
                     getline(cin,lastName);
                     
                     cout<<"Enter login\n";
                     getline(cin,login);
                     
                     //checks to see if login exist or not 
                     for(int i =0; i < bankOfficials.size();i++)
                     {
                        if(bankOfficials[i].getLogin() == login)
                        {
                           value  = false;
                        }
                     }
                     
                     if(value)
                     {
                        // if login doesnt exist
                        cout<<"Enter password\n";
                        getline(cin,password);
                     
                        BankOfficial newOfficial(firstName,lastName, id, login, password);
                     
                        bankOfficials.push_back(newOfficial);
                     
                        cout<<"Account created"<<endl;
                     }
                     else
                     {
                        //if login already exist
                        cout<<"login already exists choose another"<<endl;
                     }
                  }
                  else
                  {
                     //if id exist alread
                     cout<<"id already exist"<<endl;
                  }
               }
               else
               {
                  // if id number is correct
                  cout<<"invalid Number"<<endl;
               }
            }
            else if(accountChoice == "2")
            {
               //function for handling if admin wants to modify official 
               //checks to see if offical exsist or not
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
                  //if it exist than this function modify offical is called 
                  modifyOfficial(bankOfficials, location);
               }
               else
               {
                  //if account does not exist 
                  cout<<"Account does not exsist or is closed " <<endl; 
               }
            }
            else if(accountChoice == "3")
            {
               //exits menu
               cout<<"closing" <<endl;
            }
            else
            {
               //if user enter invalid entry 
               cout<<"invalid Entry" <<endl; 
            }
         }   
}

void modifyOfficial(vector<BankOfficial>& bankOfficials, int location)
{
   string userEnter; 
   
   while(userEnter != "3")
   {
      //menue for modifying official through admin 
      cout<<"activate/deactivate[1]:"<<endl;
      cout<<"change password[2]:"<<endl;
      cout<<"Exit[3]:\n";
      
      getline(cin,userEnter);
      
      if(userEnter == "1")
      {
         //will prompt menue for setting the official as active or inactive
         string choice;
      
         cout<<"Set Active[1]"<<endl;
         cout<<"Deactivate[2]\n";
         getline(cin,choice);
         
         if(choice == "1")
         {
            //sets official active 
            bankOfficials[location].setStatus("enable");
         }
         else if(choice == "2")
         {
            //set official as inactive
            bankOfficials[location].setStatus("disable");
         }
         else
         {
            cout<<"Invalid Entry"<<endl;
         }
      }
      else if(userEnter == "2")
      {
         //changes password for official
         string password; 
         
         cout<<"Enter new password\n";
         getline(cin,password);
         
         bankOfficials[location].setPassword(password);        
      }
      else if(userEnter == "3")
      {
         //exits the menu
         cout<<"closing" <<endl;
      }
      else
      {
         //if user enters wrong entry
         cout<<"Invalid Entry"<<endl;
      }
   }  
}

void handleHoldersAdmin(vector<AccountHolder>& accountHolders)
{   
    //function for handling holders through admins 
         string accountChoice;
    
         while(accountChoice != "3")
         {
            //menu for account holder functions for admin
            cout<<"Create AccountHolder[1]:"<<endl;
            cout<<"Modify holder/create account[2]:" <<endl; 
            cout<<"Exit[3]:\n";
            
            getline(cin,accountChoice);
            
            if(accountChoice == "1")
            {
               //creates a new Acount Holder 
               string firstName,lastName,login,password,address, phoneNumber;
            
                     cout<<"Enter first Name\n";
                     getline(cin,firstName);
                     
                     cout<<"Enter lastName\n";
                     getline(cin,lastName);
                     
                     cout<<"Enter Adress\n";
                     getline(cin,address);
                     
                     cout<<"Enter phone number\n";
                     getline(cin, phoneNumber);
                     
                     cout<<"Enter login\n";
                     getline(cin,login);
                     
                     //checks to see if the login exists or not
                     bool value = true;
                     for(int i =0; i < accountHolders.size();i++)
                     {
                        if(accountHolders[i].getLogin() == login)
                        {
                           value = false;
                        }
                     }
                     if(value)
                     {
                        // creates new account holder and adds it to vector 
                        cout<<"Enter password\n";
                        getline(cin,password);
                        
                        
                        AccountHolder newAccount(firstName,lastName,address,phoneNumber, password, login);
                        
                        accountHolders.push_back(newAccount);
                     }
                     else
                     {
                        //if loging exists 
                        cout<<"login already exists choose another"<<endl;
                     }
            }
            else if(accountChoice == "2")
            {
               //function for handling user creating new account in holder or modiying holder 
               //user enters account holder login and checks to see if exists 
               string officalName;
               int location = 0;
               bool ifPresent = false; 
               
               cout<<"Enter Account Holder:\n";
               getline(cin,officalName);
               
               for(int i =0; i < accountHolders.size(); i++)
               {
                  if (accountHolders[i].getLogin() == officalName)
                  {
                     ifPresent = true;
                     location = i;
                  }
               }
               
               if(ifPresent)
               {
                  //function for handling the account holder through admin
                  modifyHolder(accountHolders, location);
               }
               else
               {
                  //if account does not exists 
                  cout<<"Account does not exsist or is closed " <<endl; 
               }
            }
            else if(accountChoice == "3")
            {
               //exits menu
               cout<<"closing" <<endl;
            }
            else
            {
               //if user entry is invalid 
               cout<<"invalid Entry" <<endl; 
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

void modifyHolder(vector<AccountHolder>& accountHolders, int location)
{
   //function for changing account holder parameters and adding new accounts 
   string userEnter;
   
   
   while(userEnter != "5")
   {
      cout<<"Set Status of account[1]"<<endl;
      cout<<"Add Accounts[2]"<<endl;
      cout<<"Modify accounts[3]"<<endl;
      cout<<"Change password of holder[4]"<<endl;
      cout<<"Exit[5]:\n";
      
      getline(cin,userEnter);
      
      if(userEnter == "1")
      {
         //user enter a id to see if account exists 
         //checks to see if the account exists 
         string id; 
         int accountLocation;
   
         cout<<"Enter ID of Account\n";
         getline(cin, id); 
         
         bool ifPresent = false;
   
         if(checkIfNumberI(id))
         {
            int ID = stoi(id);
      
            for(int i =0; i < accountHolders[location].numberOfAccounts(); i++)
            {
               if (accountHolders[location].getAccountAt(i).getAccountNumber() == ID)
               {
                  ifPresent = true;
                  accountLocation = i;
               }
            }
         }
         
         
         if(ifPresent)
         {
            //promts menu to set the status of the accounts
            string choice ="";
            
            while(choice != "3")
            {
               cout<<"Set Active[1]"<<endl;
               cout<<"Deactivate[2]"<<endl;
               cout<<"Exit[3]\n";
               getline(cin,choice);
               
               if(choice == "1")
               {
                  //sets account as active
                  accountHolders[location].getAccountAt(accountLocation).setStatus(true);
               }
               else if(choice == "2")
               {
                  //sets account as inactive 
                  accountHolders[location].getAccountAt(accountLocation).setStatus(false);
               }
               else if(choice == "3")
               {
                  //exits the menu
                  cout<<"closing"<<endl;
               }
               else
               {
                  //invalid entry for menu
                  cout<<"Invalid Entry"<<endl;
               }
            }
         }
         else
         {
            //account doesnt exist
            cout<<"Account does not exist"<<endl;
         }
      }
      else if(userEnter == "2")
      {
         //function for creating accounts
         createAccounts(accountHolders, location);
      }
      else if(userEnter == "3")
      {
         //functions for modifying accounts 
         modifyAccounts(accountHolders, location);
      }
      else if(userEnter == "4")
      {
         //changes password for the account Holder
         string password; 
         
         cout<<"Enter new password\n";
         getline(cin,password);
         
         accountHolders[location].changePassword(password);    
      }
      else if(userEnter == "5")
      {
         //exit 
         cout<<"Closing"<<endl;
      }
      else
      {
         //invalid entry for menu
         cout<<"Ivalid Entry"<<endl;
      }
   }
}

void createAccounts(vector<AccountHolder>& accountHolders, int location)
{
   //function for creating new accounts 
   string userEnter,id; 
   
   while(userEnter != "4")
   {
      //menus for diferent types of accounts 
      cout<<"Create checking account[1]"<<endl;
      cout<<"Create savings account[2]"<<endl;
      cout<<"create CD account[3]"<<endl;
      cout<<"Exit[4]\n";
      getline(cin, userEnter);
      
      if(userEnter == "1")
      {
         //if user wants to crerate new checking account 
         cout<<"Enter new id number\n";
         getline(cin, id);
         
         if(checkIfNumberI(id))
         {
            //checks to see if user entered id is valid or not 
            int ID = stoi(id);
            if(ID > 0)
            {
               //creates new account
               accountHolders[location].createCheckingAccount(ID);
            }
            else
            {
               //if value is not positive
               cout<<"Value must be positive" <<endl;
            }
         }
         else
         {
            //if value is not a integer 
            cout<<"Invalid Entry"<<endl;
         } 
      }
      else if(userEnter == "2")
      {
         //if user wants to create new savings account 
         cout<<"Enter new id Number\n";
         getline(cin,id); 
         
         if(checkIfNumberI(id))
         {
            int ID = stoi(id);
            //checks to see if id is valid
            if(ID > 0)
            {
               cout<<"Enter Interest\n";
               getline(cin, id);
            
               if(checkIfNumberD(id))
               {
                  //checks to see if entered intrest is valid 
                  double Int = stod(id);
                  if(Int > 0.0)
                  {
                     //creates a new account 
                     accountHolders[location].createSavingsAccount(ID,Int);
                  }
                  else
                  {
                     //if interest is not positve
                     cout<<"Enter positive value"<<endl;
                  }
               }
               else
               {
                  //if interest is not a double 
                  cout<<"invalid Entry"<<endl;
               }
            }
            else
            {
               //if id is not positive
               cout<<"Value must be positive" <<endl;
            }
         }
         else
         {
            //if id is not integer 
            cout<<"Invlid Entry"<<endl;
         }
      }
      else if(userEnter == "3")
      {
         // if user wants to create new cd account 
         cout<<"Enter new id Number\n";
         getline(cin,id); 
         
         if(checkIfNumberI(id))
         {
            //checks to see if id is valid 
            int ID = stoi(id);
            if(ID > 0)
            {
               //checks to see if interest is valid
               cout<<"Enter Interest\n";
               getline(cin, id);
            
               if(checkIfNumberD(id))
               {
                  //checks to see if term is valid
                  double Int = stod(id);
                  if(Int > 0.0)
                  {
                     string term;
                     
                     cout<<"Enter term\n";
                     getline(cin,term);
                     
                     if(checkIfNumberI(term))
                     {
                        int terms = stoi(term);
                        
                        if(terms >0)
                        {
                           //creates new cd account 
                           accountHolders[location].createCDAccount(ID,Int,terms);
                        }
                        else
                        {
                           //if term is not positive
                           cout<<"Value must be Positive"<<endl;
                        }
                     }
                     else
                     {
                        //if term is not int 
                        cout<<"Invalid Entry"<<endl;
                     }
                  }
                  else
                  {
                     //interest must be postive 
                     cout<<"Value must be positive"<<endl;
                  }
               }
               else
               {
                  //interest is not double
                  cout<<"Invalid Entry"<<endl;
               }
            }
            else 
            {
               //id is not positive 
               cout<<"Value must be  positive"<<endl;
            }
         }        
         else
         {
            //id is not integer
            cout<<"Invlid Entry"<<endl;
         }
      }
      else if(userEnter == "4")
      {
         //exit
         cout<<"Closing"<<endl;
      }
      else
      {
         //if menu entry does not exist
         cout<<"Invalid Entry"<<endl;
      }  
   }
}

void modifyAccounts(vector<AccountHolder>& accountHolders,int location)
{
   // function to modify current accounts
   // request id of account holder id and sees if it exists 
   string id; 
   
   cout<<"Enter ID of Account\n";
   getline(cin, id); 
   
   if(checkIfNumberI(id))
   {
      int ID = stoi(id);
      bool ifPresent = false;
      int accountLocation;
      
      for(int i =0; i < accountHolders[location].numberOfAccounts(); i++)
         {
            if (accountHolders[location].getAccountAt(i).getAccountNumber() == ID)
            {
               ifPresent = true;
               accountLocation = i;
            }
         }
      
      if(ifPresent)
      {
         //if the account exists then it checks to see what type it is 
         if(accountHolders[location].getAccountAt(accountLocation).getType() == "C")
         {
            //nothing can be edited in in the account 
            cout<<"Nothing can be changed"<<endl;
         }
         else if(accountHolders[location].getAccountAt(accountLocation).getType() == "S")
         {
            string intrest;
            
            cout<<"Enter new Interest\n"<<endl;
            getline(cin, intrest);
            
            if(checkIfNumberI(intrest))
            {
               double Int = stod(intrest);
               
               if(Int > 0.0)
               {
                  accountHolders[location].getAccountAt(accountLocation).setInterest(Int);
               }
               else
               {
                  cout<<"Enter positive value"<<endl;
               }
            }
            else
            {
               cout<<"Invalid Entry"<<endl;
            }
         }
         else if(accountHolders[location].getAccountAt(accountLocation).getType() == "CD")
         {
            //nothing can be edited in this account 
            cout<<"Nothing Able to be Changed" <<endl;
         }
      }
      else
      {
         //account doesnt exist 
         cout<<"Account Doesent Exsist"<<endl;
      }
   }
   else
   {
      //if id is not valid 
      cout<<"Not valid Entry"<<endl; 
   }
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



string encrypt(string input)
{
   //function for encrypting string 
    for(int i = 0; i < input.length(); i++)
            input[i] = input[i] + 2;

    return input;
}

string decrypt(string input)
{
   //function for decrypting string
    for(int i = 0; i < input.length(); i++)
            input[i] = input[i] - 2;

    return input;
}
