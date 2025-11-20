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

//Now this ShoppingCart class is following the SRP.
//It has only one responsibility which is to manage the products and calculate the total price in the shopping cart.
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

    int calculateTotalPrice(){
      double totalPrice = 0;
      for(auto product: products) {
        totalPrice = totalPrice + product->price;
      }
      return totalPrice;
    }
};

class InvoiceGenerator {
  private:
  //Here we are taking the pointer reference of actual ShoppingCart
    ShoppingCart* shoppingCart;
  public:
  //Constructor
    InvoiceGenerator(ShoppingCart* shoppingCart) {
      this->shoppingCart = shoppingCart;
    }

    void genrateIvoice() {
      cout << "Invoice for the shopping cart:" << endl;
      shoppingCart->getAllProducts();
      cout << "Total Price: " << shoppingCart->calculateTotalPrice() << endl;
    }
};

class SaveInDatabase {
  private:
    ShoppingCart* shoppingCart;
  public:
    void saveToDatabase() {
      cout << "Saving to database..." << endl;
    }
};