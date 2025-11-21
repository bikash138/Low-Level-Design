# History Constraint

## Definition
This rule says that once the parent class has defined behavior, the child class must follow it. This ensures that the child class does not break the contract of the parent class.

## Example
If we take the example of a bank account which says that every account has `deposit` and `withdraw` methods, then the child class must follow this contract.

## Violation and Fix
In the case of `FixedDepositAccount`, the `withdraw` method was throwing an exception, which breaks the history constraint of the base class that says the `withdraw` method must be defined properly.

In that case, we already saw LSP being broken, which was solved and fixed by using two different base classes.

## Immutable Classes and Methods
An immutable class is a class whose state cannot be changed after it is created, and an immutable method is a method whose behavior cannot be changed.

If a child class inherits an immutable class or method and changes its state or behavior, then it is breaking the history constraint of the parent class.

To enforce immutability, we can use the `final` keyword.

