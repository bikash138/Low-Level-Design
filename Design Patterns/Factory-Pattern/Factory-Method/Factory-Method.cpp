#include <iostream>
using namespace std;

//This is our base abstract base class
class Burger {
  public:
    virtual void prepare() = 0;
    virtual ~Burger() {};
};

//Now we have child burger classes which are from different franchises
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

class BasicWheatBurger: public Burger {
  public:
    void prepare() override{
      cout << "We are creating a Basic Wheat Burger with normal patty" << endl;
    }
}; 

class StandardWheatBurger: public Burger {
  public:
    void prepare() override{
      cout << "We are creating a Standard Wheat Burger with normal patty and extra cheese" << endl;
    }
}; 

class PremiumWheatBurger: public Burger {
  public:
    void prepare() override{
      cout << "We are creating a Premium Burger with extra patty and extra cheese" << endl;
    }
}; 

//This is our Abstract Factory class which will create the different types of burger objects according to the type passed as argument
class BurgerFactory{
  public:
    virtual Burger* createBurger(string &type) = 0;
};

//Here we will simply inherit the BurgerFactory class and implement the createBurger method in the franchise of SinghBurger
class SinghBurger: public BurgerFactory {
  public:
    Burger* createBurger(string &type) override {
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

class KingBurger: public BurgerFactory {
  public:
    Burger* createBurger(string &type) override {
      if(type == "Basic"){
        return new BasicWheatBurger();
      }
      else if(type == "Standard"){
        return new StandardWheatBurger();
      }
      else if(type == "Premium"){
        return new PremiumWheatBurger();
      }
      else{
        cout << "THe type is not valid" << endl;
        return nullptr;
      }
    }
};

int main(){
  string type = "Standard";
  //Now we will create a object of BurgerFactory according to the franchise
  BurgerFactory * myBurgerFactory = new KingBurger();
  //In the following line, burger object will be returned by createBurger method of KingBurger class according to the type that is BasicWheatBurger
  Burger * burger = myBurgerFactory->createBurger(type);
  //Now we can easily call the prepare method of that method
  burger->prepare();
  
  return 0;
}