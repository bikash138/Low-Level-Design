#include <iostream>
using namespace std;

//Lets say we have two databases MySQL and Mongo and both of them is low level module

class MySQLDatabase {  // Low-level module
public:
    void saveToSQL(string data) {
        cout << "Executing SQL Query: INSERT INTO users VALUES('" << data << "');" << endl;
    }
};

class MongoDBDatabase {  // Low-level module
public:
    void saveToMongo(string data) {
        cout << "Executing MongoDB Function: db.users.insert({name: '" << data << "'})" << endl;
    }
};

//This is the high level module which is tightly coupled with the low level modules.
class UserService { 
private:
    MySQLDatabase sqlDb;  // Direct dependency on MySQL
    MongoDBDatabase mongoDb;  // Direct dependency on MongoDB

public:
    void storeUserToSQL(string user) {
        // MySQL-specific code
        sqlDb.saveToSQL(user);  
    }

    void storeUserToMongo(string user) {
        // MongoDB-specific code
        mongoDb.saveToMongo(user);  
    }
};

//So here in this line if we want to add new db then we have to change the UserService class.
//This clearly violates OCP as we are adding new functionality to the class.

int main() {
    UserService service;
    //here the client has to manually pass the db object to the service class.
    service.storeUserToSQL("Aditya");
    service.storeUserToMongo("Rohit");
}