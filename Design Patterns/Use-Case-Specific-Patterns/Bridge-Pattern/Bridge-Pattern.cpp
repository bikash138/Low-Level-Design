#include <iostream>
#include <string>
using namespace std;

//Lets first define our Implementor class: LLP
class Engine {
  public: 
    virtual void start() = 0;
    virtual ~Engine() {};
};

//Now implement the concrete class for the LLP
//All these concrete classes will be implementing the start() method
class PetrolEngine : public Engine {
  public: 
    void start() override {
      cout << "Petrol Engine is starting" << endl;
    }
};

class DisselEngine : public Engine {
  public: 
    void start() override {
      cout << "Dissel Engine is starting " << "endl";
    }
};

class ElectricEngine: public Engine {
  public: 
    void start() override {
      cout << "Electric Engine is starting" << endl;
    }
};

//Now we will define the Abstraction class: HLP
//This will be abstract class with virtual drive() method
class Car {
  protected:
  //We will keep the reference of the Engine class
    Engine* engine;
  public:
    Car(Engine* e){
      engine = e;
    }
    virtual void drive() = 0;
};

//Now we will define the Concrete Abstraction of LLP
//In these classes the drive method will be implemented 
class Sedan: public Car {
  public:
  //This line invokes the constructor of the base class Car
  //It makes sure that the Car class is properly initialized with the engine before the Sedan class
    Sedan(Engine* e) : Car(e) {}
    void drive() override {
      engine->start();
      cout << "Driving a Sedan with engine on" << endl;
    }
};

class Hatchback: public Car {
  public:
    Hatchback(Engine* e) : Car(e) {}
    void drive() override {
      engine->start();
      cout << "Driving a Hatchback with engine on" << endl;
    }
};

class SUV: public Car {
  public:
    SUV(Engine* e) : Car(e) {}
    void drive() override {
      engine->start();
      cout << "Driving a SUV with engine on" << endl;
    }
};

int main () {
  //First create the engines
  PetrolEngine* petrolEg = new PetrolEngine();
  DisselEngine* disselEg = new DisselEngine();
  ElectricEngine* electricEg = new ElectricEngine();

  //Create the cars with the required engines
  Car* sedan = new Sedan(petrolEg);
  Car* hatchback = new Hatchback(disselEg);
  Car* suv = new SUV(electricEg);

  //Now use the car
  sedan->drive(); //Petrol Engine + Sedan
  suv->drive(); //Electric Engine + SUV

  //Clean up the Referecnes
  delete sedan;
  delete hatchback;
  delete suv;
  
  return 0;
};