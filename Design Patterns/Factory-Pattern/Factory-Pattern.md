# Factory Design Pattern

## Overview
What we have seen in the Strategy Design Pattern is that the objects of the strategies to be used are already created. So there was no need to create an object of the strategy. There, we abstracted the object-creation process using dependency injection, and the behavior was decided at runtime.

## Why use the Factory Pattern?
When we mix business logic with object creation (e.g., calling `new SomeClass()` directly inside business code), the architecture becomes tightly coupled and hard to maintain.
The Factory Pattern separates object creation from business logic.
Instead of the business class deciding which concrete class to instantiate, it delegates this responsibility to a factory.
This gives us two benefits:
- The business logic stays clean and focused on behavior.
- We can change the object-creation process (or add new types) without modifying the existing business logic.

## Idea
The client simply tells the factory object: `bhai tu mereko object ban kr de`, and the factory object creates the object and returns it to the client.

## Types of Factory
- Simple Factory
- Factory Method
- Abstract Factory
