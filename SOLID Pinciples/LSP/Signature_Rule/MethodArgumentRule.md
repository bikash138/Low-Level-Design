# Method Argument Rule

Lets look into the code below:
```c++
class Parent {
  virtual void solve(string s) = 0;
}
class Child : public Parent {
  void solve(string s) override {
    cout << "Here the solve function needs to have the same argument as the parent class." << endl;
  }
}
```
So in the code above we see the `solve` method of the abstract class is taking a string argument.
This same argument must be passed in the concrete class `Child` as well.
Otherwise it will result in a compilation error.
This is called Method Argument Rule.
