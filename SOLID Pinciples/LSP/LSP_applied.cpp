#include <iostream>
#include <string>
#include <vector>
using namespace std;

class DepositableAccount {
  public:
    virtual void deposit(double amount) = 0;
};

//Inherit DepositableAccount to support deposit.
class WithdrawableAccount : public DepositableAccount {
  public:
    virtual void withdraw(double amount) = 0;
};

//SavingAccount supports both deposit and withdrawl hence it is a child of WithdrawableAccount.
class SavingAccount : public WithdrawableAccount {
  public:
    void deposit(double amount) {
      cout << "Depositing " << amount << " into the saving account." << endl;
    }
    void withdraw(double amount) {
      cout << "Withdrawing " << amount << " from the saving account." << endl;
    }
};

//CurrentAccount supports both deposit and withdrawl hence it is a child of WithdrawableAccount.
class CurrentAccount : public WithdrawableAccount {
  public:
   void deposit(double amount) {
    cout << "Depositing " << amount << " into the current account." << endl;
   }
   void withdraw(double amount) {
    cout << "Withdrawing " << amount << " from the current account." << endl;
   }
};

//So here we have made the FixedDepositAccount a child of DepositableAccount which only supports deposit.
class FixedDepositAccount : public DepositableAccount {
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
  //A bank client can have a vector of both the type account
    vector<WithdrawableAccount*> withdrawableAccounts;
    vector<DepositableAccount*> depositableAccounts;
  public:
    BankClient(vector<WithdrawableAccount*> withdrawableAccounts, vector<DepositableAccount*> depositableAccounts) {
      this->withdrawableAccounts = withdrawableAccounts;
      this->depositableAccounts = depositableAccounts;
    }

    void processTransaction() {
      //*****Learn about this looping and how it different from the normal for loop.*****
      for(WithdrawableAccount* account : withdrawableAccounts) {
        account->deposit(1000);
        account->withdraw(500);
      }
      for(DepositableAccount* account : depositableAccounts) {
        account->deposit(1000);
        //Now the client simply see an error in below line as the fixed deposit account does not support withdrawl.
        // account->withdraw(500);
      }
    }
};