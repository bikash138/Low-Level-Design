#include <iostream>
#include <string>
using namespace std;

// Interface for the image
class IImage
{
public:
  virtual void display() = 0;
  virtual ~IImage() = default;
};

// Actual concrete class where the business logic is implemented
class RealImage : public IImage
{
  string filename;

public:
  RealImage(string file)
  {
    this->filename = file;
    // Heavy Operation
    cout << "[RealImage] Loading image from disk: " << filename << "\n";
  }

  void display() override
  {
    cout << "[RealImage] Displaying " << filename << "\n";
  }
};

//Proxy class that implements the same interface as the real subject
class ImageProxy : public IImage
{
  RealImage *realImage;
  string filename;

public:
//While constructing the object the pointer is pointing to null
  ImageProxy(string file)
  {
    this->filename = file;
    realImage = nullptr;
  }
//If the client call the display method of the proxy then only it will create the real object
  void display() override
  {
    // Lazy initialization of RealImage
    if (!realImage)
    {
      realImage = new RealImage(filename);
    }
    realImage->display();
  }
};

int main()
{
//Always make sure to pass the proxy object while creating the client object
  IImage *image1 = new ImageProxy("sample.jpg");
  image1->display();
}
