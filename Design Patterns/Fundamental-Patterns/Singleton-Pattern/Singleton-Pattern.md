# Singleton Pattern
It is a design pattern that allows creating only one instance of a class. This class provides a global access point to that instance.

## Basics
Let's first start with the basics.

What happens behind the scenes when we write `A* a = new A();`?

So, whenever we write the above line, a new object of `A` is created in the heap memory, which is pointed to by the pointer `a` present in the stack memory.

If we see, `A` is a class for which we are creating an object. But if we look carefully, we are calling a method (represented by `()`).

So what does this `()` mean beside a class name?

It means that we are calling a constructor of class `A`.

What does a constructor do?

It simply initializes the object of the class `A` with some initial values. If we don't write our constructor ourselves, then the compiler will create a default constructor for us.

### Example
```c++
class Singleton {
public:
    Singleton () {
      cout << "Ctor called for the class singleton" << endl;
    }
};
int main(){
  Singleton* a = new Singleton();
  Singleton* b = new Singleton();
  cout << (a == b) << endl;
  return 0;
}
```
Following code gives output as:
```
Ctor called for the class singleton
Ctor called for the class singleton
0
```
That means two separate constructors are called and two different objects are made.

So this was the basics of how we create an object. In doing this, we can see that whenever we use the keyword `new` we are creating a new object in the heap memory.

In Singleton pattern we have to solve this problem by making sure the client always gets the same instance of the class.

## Lazy Initialization Singleton
Take a look at the following code:

```c++
class Singleton {
private:
  static Singleton* instance;
  //We made the constructor private so that no one can create object of this class from outside.
  Singleton () {
    cout << "Ctor called for the class singleton" << endl;
  }
public:
  static Singleton* getInstance() {
    if (instance == NULL) {
      instance = new Singleton();
    }
    return instance;
  }
};
Singleton * Singleton::instance = NULL;
int main(){
  Singleton* a = Singleton::getInstance();
  Singleton* b = Singleton::getInstance();
  cout << (a == b) << endl;
  return 0;
}
```
Following code gives output as:
```
Ctor called for the class singleton
1
```

In the above code:
- We have made the constructor private so that no one can create an object of this class from outside.
- We have made a static pointer called `instance` which points to the instance (object) of the `Singleton` class. This line only declares the pointer and no memory is allocated yet.

### Why `static`?
- Static variables belong to the class, not to the object.
- They exist even before any object of that class is created.
- Only one copy of a static variable exists in memory.

### Memory allocation of `instance` pointer
- It is allocated in static memory by using the line `Singleton * Singleton::instance = NULL;`
- This line actually defines the pointer and initializes it with `NULL`, which is possible only for static variables.
- Static members require a separate definition.
- Though we are defining it outside the class, in Java we can define it inside the class as well.

### Private constructor and access
So here, one question is quite obvious: if the constructor is private, then how will we create the first instance of the class?

This problem is solved by the `static` keyword. It allows calling a method of a class without creating an object of that class, like `Singleton::getInstance()`.

### Execution flow
- At first, the static variable `instance` gets defined and initialized with `NULL`.
- Now we call `getInstance()` the first time, which will check if `instance` is `NULL` or not.
- Since it is `NULL`, it will create a new object of `Singleton` and assign it to the `instance` pointer.
- Now if we call `getInstance()` a second time, it will check if `instance` is `NULL` or not.
- Since it is not `NULL`, it will return the same object which was created the first time.

So, by this way we are sure that we are always getting the same instance of the class.

## Multithreading Issue
If we look carefully, one problem prevails in the above code, which is the problem of multithreading.

If two threads call `getInstance()` at the same time, then both will check if `instance` is `NULL` or not. Since both will find it `NULL`, they will create two different objects of `Singleton`. So here the whole point of using the Singleton pattern is violated.

To solve this problem, we have to make the `getInstance()` method thread-safe. This can be done using a thread locking mechanism, which is implemented in C++ using the `mutex` class.

### Thread-safe using `mutex`
```c++
class Singleton {
private:
  static Singleton* instance;
  static mutex mtx;
  Singleton () {
    cout << "Ctor called for the class singleton" << endl;
  }
public:
  static Singleton* getInstance() {
    lock_guard<mutex> lock(mtx); //Thread safe lock
    if (instance == NULL) {
      instance = new Singleton();
    }
    return instance;
  }
};
//Initialize the static variables
Singleton * Singleton::instance = NULL;
mutex Singleton::mtx;
int main(){
  Singleton* a = Singleton::getInstance();
  Singleton* b = Singleton::getInstance();
  cout << (a == b) << endl;
  return 0;
}
```
In the above code snippet:
- We have added a `lock_guard` object called `lock` which will lock the mutex `mtx`.
- This will ensure that only one thread can access the `getInstance()` method at a time.
- If any other thread tries to access the method, it will wait until the lock is released.
- This way we are solving the problem of multithreading.

But creating a lock is an expensive operation. So we have to make sure that we are not creating a lock unnecessarily.

## Double-Checked Locking
To avoid unnecessary locks, we can use the double-checked locking pattern.

This pattern checks if `instance` is `NULL` twice. If it is `NULL`, then it will create a lock and check again if `instance` is `NULL` or not. If it is still `NULL`, then it will create a new object of `Singleton`. If it is not `NULL`, then it will return the same object which was created first time.

### Code
```c++
class Singleton {
private:
  static Singleton* instance;
  static mutex mtx;
  Singleton () {
    cout << "Ctor called for the class singleton" << endl;
  }
public:
  static Singleton* getInstance() {
    //Locks will only be created if instance in NULL otherwise a simple return will be done
    if (instance == NULL) {
      //Here the instance is found to be null so lock will be created
      lock_guard<mutex> lock(mtx); //Thread safe lock
      //Again check the instance before calling the constructor
      if (instance == NULL) {
        instance = new Singleton();
      }
    }
    return instance;
  }
};
//Initialize the static variables
Singleton * Singleton::instance = NULL;
mutex Singleton::mtx;
int main(){
  Singleton* a = Singleton::getInstance();
  Singleton* b = Singleton::getInstance();
  cout << (a == b) << endl;
  return 0;
}
```

### Why double-checked locking?
- In the above code snippet, we are checking if `instance` is `NULL` twice.
- Let's say two threads `T1` and `T2` are calling `getInstance()` at the same time.
- `T1` will check if `instance` is `NULL` or not.
- Since it is `NULL`, it will create a lock and check again if `instance` is `NULL` or not.
- `T2` will also check if `instance` is `NULL` or not.
- Since it is also `NULL`, it will wait until `T1` releases the lock.
- `T1` will create a new object of `Singleton` and assign it to the `instance` pointer.
- Now if we don't check for `NULL` again in `T2`, then it will also create a new object of `Singleton`.
- This will violate the whole point of using the Singleton pattern.
- So to handle multithreading, we are using the double-checked locking pattern.

## Eager Initialization
One question can easily be asked here: rather than doing all this, can't we simply create the object of `Singleton` while defining the static variable?
- Yes, we can do that.
- But this will create the object of `Singleton` even if we are not using it. And if it is unused, then there will be unnecessary use of memory.
- Rather, we can use it somewhere where the object getting created is very lightweight.
- This is called eager initialization. But usually we avoid it because it can be a performance issue.

### Code
```c++
class Singleton {
private:
  static Singleton* instance;
  Singleton () {
    cout << "Ctor called for the class singleton" << endl;
  }
public:
  static Singleton* getInstance() {
    if (instance == NULL) {
      instance = new Singleton();
    }
    return instance;
  }
};
//Initialize the static variables
Singleton * Singleton::instance = new Singleton();
int main(){
  Singleton* a = Singleton::getInstance();
  Singleton* b = Singleton::getInstance();
  cout << (a == b) << endl;
  return 0;
}
```

## Use Cases
- Logger classes
- Database connection classes
- Configuration classes


