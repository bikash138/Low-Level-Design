# Dependency Inversion (DI)

## 1. What Is Dependency Injection?

**Dependency Injection (DI)** means:

> This principle says high level modules should not depend on low level modules.
> Instead, those low level module should be injected into high level module from outside.

---

## 2. The Abstraction (Interface)

Your UserService depends on a `Database` interface.

```cpp
class Database {
public:
    virtual void save(std::string user) = 0;
    virtual ~Database() = default;
};
```

This means:
- UserService talks ONLY to this interface
- Any real database class must implement `save()`

---

## 3. Concrete Database Implementations

### MySQL Database

```cpp
class MySQLDatabase : public Database {
public:
    void save(std::string user) override {
        std::cout << "Saving " << user << " to MySQL" << std::endl;
    }
};
```

### MongoDB Database

```cpp
class MongoDBDatabase : public Database {
public:
    void save(std::string user) override {
        std::cout << "Saving " << user << " to MongoDB" << std::endl;
    }
};
```

These two classes behave like databases and follow the Database interface.

---

## 4. UserService Class (Where DI Happens)

```cpp
class UserService {
private:
    Database* db;   // Dependency Injection

public:
    UserService(Database* database) {
        db = database;     // Store the injected dependency
    }

    void storeUser(std::string user) {
        db->save(user);    // Calls the correct database's save()
    }
};
```

### Key understanding:
- UserService **does not know** if it’s MySQL or MongoDB.
- It only knows: “I have some Database that can save users.”

This is the heart of dependency injection.

---

## 5. Flow in main()

```cpp
int main() {
    MySQLDatabase mysql;
    MongoDBDatabase mongodb;

    UserService service1(&mysql);
    service1.storeUser("Aditya");

    UserService service2(&mongodb);
    service2.storeUser("Rohit");

    return 0;
}
```

### Step-by-step explanation:

#### 1. Create real database objects
```cpp
MySQLDatabase mysql;
MongoDBDatabase mongodb;
```
Each knows how to save data in its own style.

#### 2. Inject database into UserService
```cpp
UserService service1(&mysql);
```
UserService now holds a pointer to **mysql**.

#### 3. Call storeUser()
```cpp
service1.storeUser("Aditya");
```
Inside this method:

```cpp
db->save("Aditya");
```

But `db` points to MySQLDatabase,  
so `MySQLDatabase::save()` is called.

#### 4. Same process with MongoDB
```cpp
UserService service2(&mongodb);
service2.storeUser("Rohit");
```

Now `db` points to MongoDBDatabase,  
so `MongoDBDatabase::save()` is executed.

---

## 6. Why This Works (Polymorphism + DI)

- `db` is a pointer to **Database** (the abstract class)
- At runtime, it actually points to MySQL or MongoDB
- Calling `db->save()` automatically invokes the correct implementation

This is **runtime polymorphism**.

Combined with DI:
- UserService is flexible
- UserService does not depend on any specific database
- You can add new databases without modifying UserService

---

## 7. Summary

- You define a `Database` interface.
- You create multiple database classes that implement it.
- You inject a specific database into UserService from `main()`.
- UserService uses whichever database was injected.
- This makes UserService independent, flexible, and testable.

