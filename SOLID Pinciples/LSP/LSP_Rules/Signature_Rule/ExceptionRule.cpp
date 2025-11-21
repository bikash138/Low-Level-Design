#include <iostream>
using namespace std;

// Exception Rule:
// A subclass(child class) should throw fewer or narrower exceptions provided by the parent class
// It should not throw additional or broader exceptions than the parent class.
// C++ does not enforces this. Hence no compilation error.

/*
├── std::logic_error        <-- For logical errors detected before runtime
│   ├── std::invalid_argument   <-- Invalid function argument
│   ├── std::domain_error       <-- Function argument domain error
│   ├── std::length_error       <-- Exceeding valid length limits
│   ├── std::out_of_range       <-- Array or container index out of bounds
│
├── std::runtime_error      <-- For errors that occur at runtime
│   ├── std::range_error        <-- Numeric result out of range
│   ├── std::overflow_error     <-- Arithmetic overflow
│   ├── std::underflow_error   
*/

class Parent {
public:
    virtual void getValue() noexcept(false) { // Parent throws logic_error exception
      throw logic_error("Parent error");
    }
};

class Child : public Parent {
public:
    void getValue() noexcept(false)  override { 
      // Child throws out_of_range exception which is okay as 
      // out_of_range is a subclass of logic_error
      throw out_of_range("Child error");
      //We can also write logic_error here
      // throw logic_error("Child error");

      //Writing runtime_error is wrong as runtime_error is a completely different class
      // throw runtime_error("Child Error");
    }
};

class Client {
private:
    Parent* p;

public:
    Client(Parent* p) {
        this->p = p;
    }
    void takeValue() {
        try {
          p->getValue();
        }
  //Here the client catches the logic_error exception which is thrown by the parent
  //The child throws out_of_range exception which is a subclass of logic_error
  //So the client can catch it as well.
  //But if any error occured related to runtime_error then client 
  //won't be able to catch it.
        catch(const logic_error& e) {
            cout << "Logic error exception occured : " << e.what() << endl;
        }
    }
};

int main() {
    Parent* parent = new Parent();
    Child* child = new Child();

    Client* client = new Client(parent);

    client->takeValue();

    return 0;
}
    