#include <iostream>
using namespace std;

//This is our base abstract base class
class Burger {
  public:
    virtual void prepare() = 0;
    virtual ~Burger() {};
};

//Now we have child burger class whose prepare method will override the parent's class prepare method
class BasicBurger: public Burger {
  public:
    void prepare() override{
      cout << "We are creating a Basic Burger with normal patty" << endl;
    }
}; 

class StandardBurger: public Burger {
  public:
    void prepare() override{
      cout << "We are creating a Standard Burger with normal patty and extra cheese" << endl;
    }
}; 

class PremiumBurger: public Burger {
  public:
    void prepare() override{
      cout << "We are creating a Premium Burger with extra patty and extra cheese" << endl;
    }
}; 

//Now we will create the factory clas whcih will create the different types of burger objects according to the type passed as argument
class BurgerFactory {
  public:
  //So here we are creating a method which will return object of Burger type and according to the type passed as argument it will create the object of that type
    Burger* createBurger(string &type) {
      if(type == "Basic"){
        return new BasicBurger();
      }
      else if(type == "Standard"){
        return new StandardBurger();
      }
      else if(type == "Premium"){
        return new PremiumBurger();
      }
      else{
        cout << "THe type is not valid" << endl;
        return nullptr;
      }
    }
};

int main(){
  string type = "Standard";
  //Now we will create a object of BurgerFactory class which will handle all burger object creation 
  BurgerFactory * myBurgerFactory = new BurgerFactory();
  //In the following line, burger object will be returned by createBurger method of BurgerFactory class according to the type
  Burger * burger = myBurgerFactory->createBurger(type);
  //Now we can easily call the prepare method of that method
  burger->prepare();
  
  return 0;
}