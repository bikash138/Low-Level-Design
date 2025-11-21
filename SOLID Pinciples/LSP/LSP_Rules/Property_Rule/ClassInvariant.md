# Class Invariant

## Definition
A class must always maintain certain internal conditions (invariants) that keep the object valid. These invariants must be true at the end of the constructor and at the end of every public method.

This is not enforced by the compiler, but it is good practice to keep the invariants true.

## Example: BankAccount
- The class has a property called `balance`.
- The `balance` must always be non-negative.

In the code, the invariant is maintained in the constructor and in the `deposit` and `withdraw` methods by making sure the balance is never negative.

```cpp
class BankAccount {
private:
    double balance;

public:
    BankAccount(double initialBalance) : balance(initialBalance) {
        if (initialBalance < 0) {
            throw invalid_argument("Initial balance cannot be negative");
        }
    }

    void deposit(double amount) {
        if (amount < 0) {
            throw invalid_argument("Deposit amount cannot be negative");
        }
        balance += amount;
    }

    void withdraw(double amount) {
        // Handling this condition makes the withdraw method invariant
        if (amount < 0) {
            throw invalid_argument("Withdrawal amount cannot be negative");
        }
        if (amount > balance) {
            throw runtime_error("Insufficient funds");
        }
        balance -= amount;
    }

    // Method not following the invariant rule
    void faultyWithdraw(double amount) {
        balance -= amount;
        // Violating the invariant rule
    }
};
```