# Return Type Rule

Here in this rule we should make sure that the return type of the method in the child class must be the same or narraower as the return type of the method in the parent class.

Lets take a code example:
```c++
class Parent {
  virtual Animal random(string s) = 0;
}
class Child : public Parent {
  Animal random(string s) override {
    cout << "Here the random method can have same return type as the parent class that is Animal.Or it can return a narrower type like Dog. But it cannot return a wider type like Organism." << endl;
  }
}
```
This is called covariance