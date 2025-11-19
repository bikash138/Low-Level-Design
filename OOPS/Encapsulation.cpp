#include <iostream>
#include <string>
using namespace std;

//Lets say we have a class called SportsCar.
//And we want to hide the odometer method from being modified but can be read.
//This can be done using Access Modifiers.
class SportsCar {
  private:
    string brand;
    string model;
    //We have declared the odometer as private so that it cannot be accessed from outside the class.
    int odometer;
  
  //Always remember the to interact with the object the methods has to be public.
  public:
    SportsCar(string brand, string model) {
      this->brand = brand;
      this->model = model;
      this->odometer = 0;
    }
    //We can add a getter to read the odometer.
    void getOdometer() {
      cout << "Odometer: " << odometer << endl;
    }
    //We can use setters to modify the data rather making the variable as public
    //In this way we can add some validation logic while modifying the data.
    void setOdometer(int odometer) {
      //Lets say we have a variable called companyAdmin who can only change the odometer value
      //companyAdmin is a boolean variable which is set to false by default.
      //We can set it to true if the user is a company admin.
      bool companyAdmin = false;
      if(companyAdmin) {
        this->odometer = odometer;
      }
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

  SportsCar* myCar = new SportsCar("Fortuner", "top model");

  myCar->startEngine();
  myCar->brake();
  myCar->stopEngine();
  //We can read the odometer value using the getter method.
  //But we cannot modify the odometer value from outside the class.
  //So we can say that the odometer is Encapsulated.
  myCar->getOdometer();
}