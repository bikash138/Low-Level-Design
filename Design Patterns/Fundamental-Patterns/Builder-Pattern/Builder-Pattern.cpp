#include <iostream>
#include <map>
using namespace std;

class HttpRequest {
  private:
    string url;
    string method;
    string body;
    map<string, string> headers;
    map<string, string> queryParams;
    int timeout; //in seconds
  
    //We don't want clients to directly create `HttpRequest` objects.
    //So the client cannot construct `HttpRequest` directly (e.g., `HttpRequest req{}` or `new HttpRequest()`).
    HttpRequest() {};

  public:
    friend class HttpRequestBuilder;

    void execute() {
      cout << "Executing " << method << "request to " << url << endl;

      if(!queryParams.empty()){
        cout << "Quert Params: ";
        for(const auto& params: queryParams){
          cout << params.first << "=" << params.second << endl;
        }
      }

      cout << "Headers: ";
      for(const auto& header: headers){
        cout << " " << header.first << ": " << header.second << endl;
      }

      cout << "Body: ";
      if(!body.empty()){
        cout << body << endl;
      }

      cout << "Timeout: " << timeout << endl;
      cout << "Request is executed successfully" << endl;
    }

};

class HttpRequestBuilder {
  private:
  //We are able to access `HttpRequest` because it's a friend 
    HttpRequest req;
  public:
  //Method chaining
  //All the methods below are setters, but for the Builder pattern we use the `with` naming convention
  //Why have we created the setters here, not in the `HttpRequest` class?
  //Because we want the class to be immutable so that no one can modify the `HttpRequest` object directly
  //Hence we have kept it in the private scope, and each of these builder methods returns an `HttpRequestBuilder` reference
    HttpRequestBuilder& withUrl(const string& u){
      //This method returns the reference of the `HttpRequestBuilder` object.
      //This takes the URL as input and assigns it to the `HttpRequest` object.
      req.url = u;
      return *this;
    }

    HttpRequestBuilder& withMethod(const string& method){
      //This method returns the reference of the `HttpRequestBuilder` object.
      //This takes the method as input and assigns it to the `HttpRequest` object.
      req.method = method;
      return *this;
    }

    HttpRequestBuilder& withHeader(const string& key, const string& value){
      //This method returns the reference of the `HttpRequestBuilder` object.
      //This takes the header key/value as input and assigns it to the `HttpRequest` object.
      req.headers[key] = value;
      return *this;
    }

    HttpRequestBuilder& withQueryParams(const string& key, const string& value){
      //This method returns the reference of the `HttpRequestBuilder` object.
      //This takes the query parameter key/value as input and assigns it to the `HttpRequest` object.
      req.queryParams[key] = value;
      return *this;
    }

    HttpRequestBuilder& withBody(const string& body){
      //This method returns the reference of the `HttpRequestBuilder` object.
      //This takes the body as input and assigns it to the `HttpRequest` object.
      req.body = body;
      return *this;
    }

    HttpRequestBuilder& withTimeout(int timeout){
      //This method returns the reference of the `HttpRequestBuilder` object.
      //This takes the timeout as input and assigns it to the `HttpRequest` object.
      req.timeout = timeout;
      return *this;
    }

    //Build method to create immutable HttpRequest object
    //Here actual validation takes place 
    //If validation fails here, the `HttpRequest` object creation will not proceed
    HttpRequest& build(){
      //Validation logic can be added here
      if(req.url.empty() || req.method.empty()){
        throw runtime_error("URL and Method are required");
      }
      return req;
    }
};

int main() {
  //We cannot directly call `new HttpRequest` because the constructor is private
  //We create the `HttpRequest` object using the Builder pattern
  //If we don't call the `build` method at the end, we will get a compile‑time error 
  //because `build` is the method that actually returns the `HttpRequest` object 
  //and before that all the builder methods return an `HttpRequestBuilder` reference which cannot be assigned to `HttpRequest`
  //This way we can guarantee consistency with proper validation
  HttpRequest request = HttpRequestBuilder()
    .withUrl("https://www.something.com")
    .withMethod("GET")
    .withHeader("Content-Type", "application/json")
    .withQueryParams("page", "2")
    .withTimeout(10)
    .build();

  request.execute();
}
