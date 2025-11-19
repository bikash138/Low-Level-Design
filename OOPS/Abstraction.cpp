#include <iostream>
#include <string>
using namespace std;

//Car class is an abstract class which has pure virtual methods.
//And a abstract class with only virtual methods is called Interface.
class Car {
  public:
    virtual void startEngine() = 0;
    virtual void brake() = 0;
    virtual void stopEngine() = 0;
    virtual ~Car() {}
};

//SportsCar is inheriting the Car class and acting as a concrete class.
//So it 100% required to implement all the pure virtual methods of the Car class.
class SportsCar: public Car {
  string brand;
  string model;
  public:
    SportsCar(string brand, string model) {
      this->brand = brand;
      this->model = model;
    }
    void startEngine() {
      cout << "SportsCar engine started" << endl;
    }

    void brake() {
      cout << "SportsCar braking" << endl;
    }

    void stopEngine() {
      cout << "SportsCar engine stopped" << endl;
    }
};

int main(){
  //Car is an abstract class so we cannot create an object of it.
  //But we can create a pointer of it and point to the objects of its child class.
  Car* myCar = new SportsCar("Fortuner", "top model");

  //Now we can see that all the methods of our sports car in abstracted
  //We dont need to know the inner working of the sports car.
  //We just need to know that we can start the engine, brake and stop the engine.
  //And this is called Abstraction.
  myCar->startEngine();
  myCar->brake();
  myCar->stopEngine();
}

