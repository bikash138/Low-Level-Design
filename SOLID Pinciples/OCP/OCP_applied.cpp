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

//Create a Abstract class containing the virtual function only
class DBPersistor {
  private:
    ShoppingCart* shoppingCart;
  public:
  //This is a virtual method so it has to be implemented by its child classes
    virtual void save(ShoppingCart* shoppingCart) = 0;
};

//Now we will inherit the DBPersistor and override the save() method and this is called polymorphism.
class SaveToSQL : public DBPersistor {
  public:
    void save(ShoppingCart* shoppingCart) override {
      cout << "Saving to SQL database..." << endl;
    }
};
class SaveToMongoDB : public DBPersistor {
  public:
    void save(ShoppingCart* shoppingCart) override {
      cout << "Saving to MongoDB database..." << endl;
    }
};
class SaveToFile : public DBPersistor {
  public:
    void save(ShoppingCart* shoppingCart) override {
      cout << "Saving to File..." << endl;
    }
};

int main(){
  ShoppingCart* cart = new ShoppingCart();
  cart->addProduct(new Product("Apple", 100));
  cart->addProduct(new Product("Banana", 200));

  InvoiceGenerator* invoiceGenerator = new InvoiceGenerator(cart);
  invoiceGenerator->genrateIvoice();

  DBPersistor* saveToSQL = new SaveToSQL();
  saveToSQL->save(cart);

  DBPersistor* saveToMongoDB = new SaveToMongoDB();
  saveToMongoDB->save(cart);

  DBPersistor* saveToFile = new SaveToFile();
  saveToFile->save(cart);
}