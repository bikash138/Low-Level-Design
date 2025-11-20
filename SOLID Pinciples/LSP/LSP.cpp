#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Account {
  public:
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
};

class SavingAccount : public Account {
  public:
    void deposit(double amount) {
      cout << "Depositing " << amount << " into the saving account." << endl;
    }
    void withdraw(double amount) {
      cout << "Withdrawing " << amount << " from the saving account." << endl;
    }
};

class CurrentAccount : public Account {
  public:
   void deposit(double amount) {
    cout << "Depositing " << amount << " into the current account." << endl;
   }
   void withdraw(double amount) {
    cout << "Withdrawing " << amount << " from the current account." << endl;
   }
};

class FixedDepositAccount : public Account {
  public:
    void deposit(double amount) {
      cout << "Depositing " << amount << " into the fixed deposit account." << endl;
    }
    void withdraw(double amount) {
      throw logic_error("Withdrawal not allowed in Fixed Term Account!");    
    }
};

class BankClient {
  private: 
    vector<Account*> accounts;
  public:
    BankClient(vector<Account*> accounts) {
      this->accounts = accounts;
    }
    //Here we can clearly see LSP is vioalted as we are trying to withdraw from the fixed deposit account.
    void processTransaction() {
      //*****Learn about this looping and how it different from the normal for loop.*****
      for(Account* account : accounts) {
        account->deposit(1000);
        
        //Assuming All account supports withdrawl
        //Here we have handled the case using try catch but it is not a good practice.
        try {
          account->withdraw(500);
        } catch (const logic_error& e) {
            cout << "Exception: " << e.what() << endl;
        }
      }
    }
};