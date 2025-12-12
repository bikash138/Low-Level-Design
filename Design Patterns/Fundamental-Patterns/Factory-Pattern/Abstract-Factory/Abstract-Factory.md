# Abstract Factory Pattern

## Definition
It provides an interface for creating a family of related or dependent objects without specifying their concrete classes.

## Motivation
What if each franchise decides to include garlic bread in their menus.
Here, one subclass of the factory class is responsible for creating multiple products.
 
## UML Diagram (Abstract Factory)
 
 ```mermaid
 classDiagram
     class Burger {
         <<abstract>>
         +prepare()
     }
     class GarlicBread {
         <<abstract>>
         +prepare()
     }
 
     Burger <|-- BasicBurger
     Burger <|-- BasicWheatBurger
     GarlicBread <|-- BasicGarlicBread
     GarlicBread <|-- BasicWheatGarlicBread
 
     class RestaurantFactory {
         <<abstract>>
         +createBurger(type): Burger
         +createGarlicBread(type): GarlicBread
     }
 
     RestaurantFactory <|-- SinghFactory
     RestaurantFactory <|-- KingFactory
 
     class SinghFactory {
         +createBurger(type): Burger
         +createGarlicBread(type): GarlicBread
     }
     class KingFactory {
         +createBurger(type): Burger
         +createGarlicBread(type): GarlicBread
     }
 
     SinghFactory ..> BasicBurger : creates
     SinghFactory ..> BasicGarlicBread : creates
     KingFactory ..> BasicWheatBurger : creates
     KingFactory ..> BasicWheatGarlicBread : creates
 ```
