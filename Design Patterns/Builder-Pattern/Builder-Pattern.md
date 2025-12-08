# Builder Pattern

## HTTP Request Example
To understand this pattern, let's take an example of an HTTP request.

In an HTTP request we can have the following parts:
- URL
- Method
- Headers
- Body
- Query Parameters

To build this `HttpRequest` class, we might create a constructor that takes all these parts as parameters.

## Problems With Telescoping Constructors
- Query parameters and body are optional, so passing them in a single constructor is awkward.
- The client must remember the order of parameters, which is error‑prone.
- This is called constructor telescoping/overloading.

## Mutability Concerns
Another problem is the issue of mutability. In some objects (not in this case) we don't want the client to change the state of the object after it is created.
One might suggest removing the setters and making the class immutable.
But that would require changing existing logic, and it's not always a good practice to simply remove setters.

## Optional Parameters via Setters: Pitfalls
When trying to solve optional parameters:
- Use setters for optional parameters.
- Keep non‑optional parameters in the constructor.
- However, this can cause a critical issue:
  - Let's say query parameters are optional and headers are optional.
  - Object creation may look like `HttpRequest* httpRequest = new HttpRequest(url, method, body);`
  - Optional parameters can be set later: `httpRequest->setQueryParameters(queryParameters);`
  - After this we may call the execute method: `httpRequest->execute();`
  - But what if the client forgets to set query parameters or headers and directly calls `execute()`?
  - The client may not get the desired result, and there will be no compile‑time error.
  - We must ensure the client sets all required parameters before calling `execute()`.
  - This is a problem that the Builder pattern solves.

## Validation Burden
Another problem is validation. We must ensure that all required parameters are set before calling `execute()`, which becomes client overhead.

This is better explained in the code.


