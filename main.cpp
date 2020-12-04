#include <iostream>
#include "account.h"
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

            BankOfficial newBankOfficial(firstName, lastName, id, login, password);
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

            string address = line; // address (might contain spaces)

            AccountHolder newAccountHolder(firstName, lastName, address, phoneNumber, password, login);

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

                getline(inputFile, line);

                string creationTime = line;
                newAccount.setCreationTimeFile(line);

                getline(inputFile, line);

                string lastOpenedTime = line;
                newAccount.setLastOpen(line);

                newAccount.setMaturity();

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
    

  cout<<"Hello, Welcome to Bear Bank"<<endl; 
  
  string userInput = "0";
  
  while(userInput != "4")
  {
      cout<<"Login as Admin[1]:"<<endl;
      cout<<"Login as Bank Official[2]:" << endl; 
      cout<<"Login as Account Holder[3]:" << endl;
      cout<<"Exit[4]:\n";
      getline(cin, userInput);
      
      if(userInput == "1")
      {
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
               cout<<"Official Users[1]:" <<endl;
               cout<<"Acount Holders[2]:" <<endl;
               cout<<"Change admin Password[3]:"<<endl;
               cout<<"Change admin login[4]:"<<endl;
               cout<<"Exit[4]:\n";

               getline(cin, adminChoice);
               
               if(adminChoice == "1")
               {
                  handleOfficialAdmin(bankOfficials);
               }
               else if(adminChoice == "2")
               {
                  handleHoldersAdmin(accountHolders);
               }
               else if(adminChoice == "3")
               {  

                  cout << "Please enter a new Password: ";
                  string newPassword;
                  getline(cin, newPassword);
                  admin.password = newPassword;
                  cout << "Password change successful\n";
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
            cout<<"Incorrect UserName or Password"<<endl; 
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
  }
  
  for(int i = 0; i < accountHolders.size(); i++)
  {
     outFile << "ACCOUNTHOLDER\n";
     accountHolderDetails = accountHolders[i].getFirstName() + " " + accountHolders[i].getLastName() + " " + accountHolders[i].getPhoneNumber() + " " + encrypt(accountHolders[i].getLogin()) + " " 
                            + encrypt(accountHolders[i].getPassword()) + " " + accountHolders[i].getAddress();

      outFile << accountHolderDetails << '\n';
      outFile << accountHolders[i].numberOfAccounts() << '\n';

      for(int j = 0; j < accountHolders[i].numberOfAccounts(); j++)
      {
         AccountP currAcc = accountHolders[i].getAccountAt(j);
         outFile << currAcc.getAccountNumber() << " " << currAcc.getBalance() << " " << currAcc.getInterest() << " " << currAcc.getTerm() << '\n';
         outFile << currAcc.getDateCreated() << '\n';
         outFile << currAcc.getTimeNow() << '\n';
         outFile << currAcc.numberOfTransactions() << '\n';

         for(int k = 0; k < 4; k++)
         {
            Transaction currTran = currAcc.getTransactionAt(k);
            outFile << currTran.date[0] << "/" << currTran.date[1] << "/" << currTran.date[2] << " " << currTran.action << " " << "$" << currTran.amount << " " << "Official: " << currTran.official << "\n";
         }
         
      }
  }
  
  
  
  return 0;
}


void handleAccountUser(string userName, int locationInV, vector<AccountHolder>& accountHolders)
{
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
   cout<<"Enter password for account\n";
   int i = locationInV;
   
   getline(cin, userEnter);
   
   string accountPassword = bankOfficials[i].getPassword();
   
   if(userEnter == accountPassword)
   {
      string accountChoice;
      
      
      while(accountChoice != "3")
      {
      
         cout<<"Search for Users[1]:" <<endl;
         cout<<"Access Users[2]:" << endl;
         cout<<"Exit[3]:\n";
         
         getline(cin,accountChoice);
         
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
      cout<<"Search by account number2[1]:"<<endl;
      cout<<"Search by phoneNumber or last name[2]:"<< endl;
      cout<<"Exit[3]:\n";
      
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
         
         getline(cin, accountChoice);
         
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
         string accountChoice;
         cout<<"Success"<<endl;
         cout<<"\n";
    
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
                     
                     for(int i =0; i < bankOfficials.size();i++)
                     {
                        if(bankOfficials[i].getLogin() == login)
                        {
                           value  = false;
                        }
                     }
                     
                     if(value)
                     {
                        cout<<"Enter password\n";
                        getline(cin,password);
                     
                        BankOfficial newOfficial(firstName,lastName, id, login, password);
                     
                        bankOfficials.push_back(newOfficial);
                     
                        cout<<"Account created"<<endl;
                     }
                     else
                     {
                        cout<<"login already exists choose another"<<endl;
                     }
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

void modifyOfficial(vector<BankOfficial>& bankOfficials, int location)
{
   string userEnter; 
   
   while(userEnter != "3")
   {
      cout<<"activate/deactivate[1]:"<<endl;
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

void handleHoldersAdmin(vector<AccountHolder>& accountHolders)
{   
     
         string accountChoice;
    
         while(accountChoice != "3")
         {
            cout<<"Create AccountHolder[1]:"<<endl;
            cout<<"Modify holder/create account[2]:" <<endl; 
            cout<<"Exit[3]:\n";
            
            getline(cin,accountChoice);
            
            if(accountChoice == "1")
            {
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
                     
                     bool value = false;
                     for(int i =0; i < accountHolders.size();i++)
                     {
                        if(accountHolders[i].getLogin() == login)
                        {
                           value = true;
                        }
                     }
                     if(!value)
                     {
                        
                        cout<<"Enter password\n";
                        getline(cin,password);
                        
                        
                        AccountHolder newAccount(firstName,lastName,address,phoneNumber, password, login);
                        
                        accountHolders.push_back(newAccount);
                     }
                     else
                     {
                        cout<<"login already exists choose another"<<endl;
                     }
            }
            else if(accountChoice == "2")
            {
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
                  modifyHolder(accountHolders, location);
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
            string choice ="";
            
            while(choice != "3")
            {
               cout<<"Set Active[1]"<<endl;
               cout<<"Deactivate[2]\n";
               getline(cin,choice);
               
               if(choice == "1")
               {
                  accountHolders[location].getAccountAt(accountLocation).setStatus(true);
               }
               else if(choice == "2")
               {
                  accountHolders[location].getAccountAt(accountLocation).setStatus(false);
               }
               else
               {
                  cout<<"Invalid Entry"<<endl;
               }
            }
         }
         else
         {
            cout<<"Account does not exist"<<endl;
         }
      }
      else if(userEnter == "2")
      {
         createAccounts(accountHolders, location);
      }
      else if(userEnter == "3")
      {
         modifyAccounts(accountHolders, location);
      }
      else if(userEnter == "4")
      {
         string password; 
         
         cout<<"Enter new password\n";
         getline(cin,password);
         
         accountHolders[location].changePassword(password);    
      }
      else if(userEnter == "5")
      {
         cout<<"Closing"<<endl;
      }
      else
      {
         cout<<"Ivalid Entry"<<endl;
      }
   }
}

void createAccounts(vector<AccountHolder>& accountHolders, int location)
{
   string userEnter,id; 
   
   while(userEnter != "4")
   {
      cout<<"Create checking account[1]"<<endl;
      cout<<"Create savings account[2]"<<endl;
      cout<<"create CD account[3]"<<endl;
      cout<<"Exit[4]\n";
      getline(cin, userEnter);
      
      if(userEnter == "1")
      {
         
         cout<<"Enter new id number\n";
         getline(cin, id);
         
         if(checkIfNumberI(id))
         {
            int ID = stoi(id);
            if(ID > 0)
            {
               accountHolders[location].createCheckingAccount(ID);
            }
            else
            {
               cout<<"Value must be positive" <<endl;
            }
         }
         else
         {
            cout<<"Invalid Entry"<<endl;
         } 
      }
      else if(userEnter == "2")
      {
         cout<<"Enter new id Number\n";
         getline(cin,id); 
         
         if(checkIfNumberI(id))
         {
            int ID = stoi(id);
            
            if(ID > 0)
            {
               cout<<"Enter Interest\n";
               getline(cin, id);
            
               if(checkIfNumberD(id))
               {
                  double Int = stod(id);
                  if(Int > 0.0)
                  {
                     accountHolders[location].createSavingsAccount(ID,Int);
                  }
                  else
                  {
                     cout<<"Enter positive value"<<endl;
                  }
               }
               else
               {
                  cout<<"invalid Entry"<<endl;
               }
            }
            else
            {
               cout<<"Value must be positive" <<endl;
            }
         }
         else
         {
            cout<<"Invlid Entry"<<endl;
         }
      }
      else if(userEnter == "3")
      {
         cout<<"Enter new id Number\n";
         getline(cin,id); 
         
         if(checkIfNumberI(id))
         {
            int ID = stoi(id);
            if(ID > 0)
            {
               cout<<"Enter Interest\n";
               getline(cin, id);
            
               if(checkIfNumberD(id))
               {
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
                           accountHolders[location].createCDAccount(ID,Int,terms);
                        }
                        else
                        {
                           cout<<"Value must be Positive"<<endl;
                        }
                     }
                     else
                     {
                        cout<<"Invalid Entry"<<endl;
                     }
                  }
                  else
                  {
                     cout<<"Value must be positive"<<endl;
                  }
               }
               else
               {
                  cout<<"Invalid Entry"<<endl;
               }
            }
            else 
            {
               cout<<"Value must be  positive"<<endl;
            }
         }        
         else
         {
            cout<<"Invlid Entry"<<endl;
         }
      }
      else if(userEnter == "4")
      {
         cout<<"Closing"<<endl;
      }
      else
      {
         cout<<"Invalid Entry"<<endl;
      }  
   }
}

void modifyAccounts(vector<AccountHolder>& accountHolders,int location)
{
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
         if(accountHolders[location].getAccountAt(accountLocation).getType() == "C")
         {
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
            cout<<"Nothing Able to be Changed" <<endl;
         }
      }
      else
      {
         cout<<"Account Doesent Exsist"<<endl;
      }
   }
   else
   {
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
