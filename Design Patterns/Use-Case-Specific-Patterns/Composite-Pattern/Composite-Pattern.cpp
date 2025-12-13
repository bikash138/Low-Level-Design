#include <iostream>
#include <vector>
using namespace std;

//First of all we are creating the base Interface for the files and folders
class FilSystemItem {
  public:
  //Defining the pure virtual methods which are going to be implemented by the child classes
    virtual void ls(int indent = 0) = 0;
    virtual void openAll(int indent = 0) = 0;
    virtual string getName() = 0;
    virtual int getSize() = 0;
    virtual FilSystemItem* cd(const string& name) = 0;
    virtual bool isFolder ()= 0;
    virtual ~FilSystemItem() {}
};

//Now we will be creating the File class which will be a leaf
class File: public FilSystemItem {
  string name;
  int size;
  public:
    File(const string& n, int s){
      name = n;
      size = s;
    }
  //Now start implementing the pure virtual methods
  //File ls just prints the name of the file
  void ls(int indent = 0) override {
    cout << string(indent, ' ') << name << endl;
  }
  //File openAll just prints the name of the file
  void openAll(int indent = 0) override {
    cout << string(indent, ' ') << name << endl;
  }
  int getSize() override {
    return size;
  }
  string getName() override {
    return name;
  }
  //File cd just returns nullptr as it cannot go into any folder
  FilSystemItem* cd(const string&) override {
    return nullptr;
  }
  bool isFolder () override {
    return false;
  }
};

//Noe lets create the Folder class
class Folder: public FilSystemItem {
  string name;
  //Below line shows has a realtion
  vector<FilSystemItem*> children;
  public:
    Folder(const string& n){
      name = n;
    }
    void add(FilSystemItem* item){
      children.push_back(item);
    }

    //Now start overriding the pure virtual methods
    void ls(int indent = 0) override {
      //Loop thorugh all the children and print their names
      //All the children will of type FilSystemItem so we can call their methods
      for(auto child: children){
        if(child->isFolder()){
          cout << string(indent, '+') << child->getName() << "\n";
        }else{
          cout << string(indent, ' ') << child->getName() << "\n";
        }
      }
    }
    void openAll(int indent = 0) override{
      //Here we will loop through all the children and call their openAll method
      //At first we will print the name of the folder
      cout << string(indent, ' ') << "+ " << name << "\n";
      //Now we will loop through all the children and call their openAll method recursively
      for(auto child: children){
        child->openAll(indent+4);
      }
    }
    int getSize() override{
      int size = 0;
      //This will also recursively calcualte the size of all the files in the folder
      for(auto child: children){
        size = size + child->getSize();
      }
      return size;
    }

    FilSystemItem *cd(const string& target) override {
      //This loop will check if the target is there in the list
      //If its there then it will return the pointer to that folder
      //Otherwise it will return nullptr
      for(auto child: children){
        if(child->isFolder() && child->getName() == target){
          return child;
        }else{
          return nullptr;
        }
      }
    }
    string getName() override {
      return name;
    }
    bool isFolder () override {
      return true;
    }
};

int main () {
  //Build the File System
  Folder * root = new Folder("root");
  root->add(new File("file1.txt", 100));
  root->add(new File("file2.txt", 200));
  // root->openAll();
  root->ls();
  return 0;
}