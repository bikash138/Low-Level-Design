#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Product {
  public:
    string name;
    double price;

    Product(string name, double price){
      this->name = name;
      this->price = price;
    }
};

//Lets see the code violating the SRP
//Here We can clearly see all the methods related to the shopping cart
//are in the same class. which is not a good practice.
class ShoppingCart {
  private:
    vector<Product*> products;
  public:
    void addProduct(Product* product) {
      products.push_back(product);
    }

    void getAllProducts() {
      for(auto product: products) {
        cout << product->name << " " << product->price << endl;
      }
    }
    //Can be present in the class single job to calvulate the total price
    int calculateTotalPrice(){
      double totalPrice = 0;
      for(auto product: products) {
        totalPrice = totalPrice + product->price;
      }
      return totalPrice;
    }
    //Here SRP gets violated as the this method has to be in separate class.
    void generateInvoice() {
      cout << "Invoice for the shopping cart:" << endl;
      getAllProducts();
      cout << "Total Price: " << calculateTotalPrice() << endl;
    }
    //SImilar to generateInvoice, we should have a separate class to handle the database operations.
    void insertIntoDatabase() {
      cout << "Inserting into database..." << endl;
    }
};


