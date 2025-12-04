#include <iostream>
#include <string>
using namespace std;

//Component Interface which will defines the common interface for all the decorators and Mario
class Character {
  public:
    virtual string getAbilities() = 0;
    virtual ~Character() {} // Virtual destructor to ensure proper cleanup of derived objects
};

//Concrete Component which the basic mario properties
class Mario : public Character {
  public:
    string getAbilities() override {
      return "Basic Mario";
    }
};

//Abstract Decorator class which will have "is-a" Chracter and "has-a" Character
class CharacterDecorator : public Character { //Ensures the "is-a" relationship with Character
  protected:
   Character *character; //Keeping the referecne of the Character object ensuring the has-a relationship
   public:
    CharacterDecorator(Character *c) {
      this->character = c; //Initializing the Character object reference
    }
};

//Concrete child of CharacterDecorator which adds extra abilities to the Character
//Height Increasing Decorator
class HeighUpDecorator: public CharacterDecorator {
  public:
    HeighUpDecorator(Character *c) : CharacterDecorator(c) {}; //Initializing the CharacterDecorator with the Character object reference
    
    string getAbilities() override {
      return character->getAbilities() + " can jump higher";
    }
};

//Gun Power Up Decorator
class GunPowerUpDecorator: public CharacterDecorator {
  public:
    GunPowerUpDecorator(Character *c) : CharacterDecorator(c) {}; //Initializing the CharacterDecorator with the Character object reference
    
    string getAbilities() override {
      return character->getAbilities() + " can use a gun";
    }
};

//Star Power up Decorator
class StarPowerUpDecorator: public CharacterDecorator {
  public:
    StarPowerUpDecorator(Character *c) : CharacterDecorator(c) {}; //Initializing the CharacterDecorator with the Character object reference
    
    string getAbilities() override {
      return character->getAbilities() + " with a star power";
    }
};

int main(){
  //First we will create a Mario Object
  Character *mario = new Mario();
  cout << "Basic Character: " << mario->getAbilities() << endl; //This will call the base class getAbilities method

  //Now we will decoreate Mario with some abilies
  mario = new HeighUpDecorator(mario);
  cout << "After Hieght Up: " << mario-> getAbilities() << endl;

  //Now we will decoreate Mario with Gun Power Up
  mario = new GunPowerUpDecorator(mario);
  cout << "After Gun Power Up: " << mario-> getAbilities() << endl; 

  //Now we will decoreate Mario with Star Power Up
  mario = new StarPowerUpDecorator(mario);
  cout << "After Star Power Up: " << mario-> getAbilities() << endl; 

  delete mario; //Freeing the memory allocated for Mario object

  return 0;
}


