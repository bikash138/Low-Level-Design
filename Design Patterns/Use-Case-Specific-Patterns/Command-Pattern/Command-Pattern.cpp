#include <iostream>
#include <string>
using namespace std;

//Command Interface
class Command {
  public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() {};
};

//Receivers
class Fan{
  public:
    void on(){
      cout << "Fan is on" << endl;
    }
    void off(){
      cout << "Fan is off" << endl;
    }
};

class Light{
  public:
    void on(){
      cout << "Light is on" << endl;
    }
    void off(){
      cout << "Light is off" << endl;
    }
};


//Concrete Command for Light
class LightCommand : public Command {
  private:
    Light* light;
  public:
    LightCommand(Light* l){
      light = l;
    }
    void execute(){
      light->on();
    }
    void undo(){
      light->off();
    }
};

class FanCommand : public Command {
  private:
    Fan* fan;
  public:
    FanCommand(Fan* f){
      fan = f;
    }
    void execute(){
      fan->on();
    }
    void undo(){
      fan->off();
    }
};

//Invoker: REmote Controller
class RemoteeController{
  private:
    static const int numButtons = 2;
    Command* buttons[numButtons];
    bool ButtonPressed[numButtons];
  public:
    RemoteeController(){
      for(int i=0; i<numButtons; i++){
        //Initally buttons will have no functions
        buttons[i] = nullptr;
        //Initially buttons are not pressed
        ButtonPressed[i] = false;
      }
    }

    void SetCommand(int index, Command* cmd){
      //First check the index is valid or not
      if(index >=0 && index<numButtons){
        if(buttons[index] != nullptr){
          //If the button already has a command, then delete it
          delete buttons[index];
        }
        //Set the new command passed by the client
        buttons[index] = cmd;
        //Initially the button is not pressed
        ButtonPressed[index] = false;
      }
    }

    void PressButton(int index){
      //SO first we have to check that the index is valid and the command is not null then only it can be pressed
      if(index >= 0 && index<numButtons && buttons[index] != nullptr){
        if(ButtonPressed[index] == false){
          //If the button is not pressed, then execute the command
          buttons[index]->execute();
        }else{
          //If the button is pressed, then undo the command
          buttons[index]->undo();
        }
        //After pressing the button we have to update the button pressed state
        ButtonPressed[index] = !ButtonPressed[index];
      }else{
        cout << "Invalid Button INdex or No command assigned to the button: " << index << endl;
      }
    }

    ~RemoteeController(){
      for(int i=0; i<numButtons; i++){
        if(buttons[i] != nullptr){
          delete buttons[i];
        }
      }
    }
};

int main(){
  //First create a appliances
  Light* livingRoomLight = new Light();
  Fan* livingRoomFan = new Fan();

  //Now we are creating Remote COntroller
  RemoteeController*remote = new RemoteeController();

  //Now call the set command of the remote that will set the command on particular indexes
  //Here the set command method takes a Command parameter and the lightCommand itself takes the light receiver
  remote->SetCommand(0, new LightCommand(livingRoomLight));
  remote->SetCommand(1, new FanCommand(livingRoomFan));

  //Now we will perform the on/off method
  cout << "-----Toggle the light Button at 0-----" << endl;
  remote->PressButton(0);//This should turn on the light
  remote->PressButton(0);//This should turn off the light

  cout << "-----Toggle the fan Button at 1-----" << endl;
  remote->PressButton(1);//This should turn on the fan
  remote->PressButton(1);//This should turn off the fan

  delete remote;
  delete livingRoomLight;
  delete livingRoomFan;

  return 0;

}
