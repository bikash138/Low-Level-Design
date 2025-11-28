# Factory Method Pattern

## Overview
We now move to the Factory Method pattern, which is a proper design pattern.

## Definition
It defines an interface for creating objects (a factory) but allows subclasses to decide which class to instantiate.

## Description
Here we make an abstract factory class with an abstract method, and its subclass overrides the method to create the correct object expected by the client.


So extending our example of Burger. Let's say we have two franchises. 
- `SinghBurger`
- `KingBurger`

And now we have three varieties of burger available for each franchise.
### SinghBurger
- `Basic Burger`
- `Standard Burger`
- `Premium Burger`
### KingBurger
- `Basic Wheat Burger`
- `Standard Wheat Burger`
- `Premium Wheat Burger`

Following is the UML diagram for the same:
 
## UML Diagram (Factory Method)
 
 ```mermaid
 classDiagram
     class Burger {
         +prepare()
     }
 
     Burger <|-- BasicBurger
     Burger <|-- StandardBurger
     Burger <|-- PremiumBurger
     Burger <|-- BasicWheatBurger
     Burger <|-- StandardWheatBurger
     Burger <|-- PremiumWheatBurger
 
     class BurgerFactory {
         +createBurger(type): Burger
     }
 
     BurgerFactory <|-- SinghBurgerFactory
     BurgerFactory <|-- KingBurgerFactory
 
     class SinghBurgerFactory {
         +createBurger(type): Burger
     }
     class KingBurgerFactory {
         +createBurger(type): Burger
     }
 
     SinghBurgerFactory ..> Burger : creates
     KingBurgerFactory ..> Burger : creates
 ```
