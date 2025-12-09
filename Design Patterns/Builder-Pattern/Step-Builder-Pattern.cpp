#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>

using namespace std;

class HttpRequest {
private:
    string url;
    string method;
    map<string, string> headers;
    map<string,string> queryParams;
    string body;
    int timeout; // in seconds

    // Private constructor - can only be accessed by the Builder
    HttpRequest() { }

public:
    friend class HttpRequestStepBuilder;

    // Method to execute the HTTP request
    void execute() {
        cout << "Executing " << method << " request to " << url << endl;
        
        if (!queryParams.empty()) {
            cout << "Query Parameters:" << endl;
            for (const auto& param : queryParams) {
                cout << "  " << param.first << "=" << param.second << endl;
            }
        }

        cout << "Headers:" << endl;
        for (const auto& header : headers) {
            cout << "  " << header.first << ": " << header.second << endl;
        }
        
        if (!body.empty()) {
            cout << "Body: " << body << endl;
        }
        
        cout << "Timeout: " << timeout << " seconds" << endl;
        cout << "Request executed successfully!" << endl;
    }
};

// forward declaration
class MethodStep;
class HeaderStep;
class OptionalStep;

// Interface for each step of the builder
class UrlStep {
public:
//Return the reference of the next step: MethodStep
  virtual MethodStep& withUrl(const string& url) = 0;
};

class MethodStep {
public:
//Return the reference of the next step: HeaderStep
  virtual HeaderStep& withMethod(string method) = 0;
};

class HeaderStep {
public:
//Return the reference of the next step: OptionalStep
  virtual OptionalStep& withHeader(string key, string value) = 0;
};

class OptionalStep {
public:
//This is the final step/optional step
//Returns the reference of itself if withBody or withTimeout is called
//Otherwise build method returns the HttpRequest object
//This tells that user can either call the build method to end the chain or call the withBody or withTimeout method to add these optional fields
  virtual ~OptionalStep() {}
  virtual OptionalStep& withBody(const string& body) = 0;
  virtual OptionalStep& withTimeout(int timeout) = 0;
  virtual HttpRequest build() = 0;
};

// Concrete step builder that implements all interfaces
class HttpRequestStepBuilder : 
//We have inherited all the interfaces as steps: Multiple Inheritance
  public UrlStep, 
  public MethodStep, 
  public HeaderStep,
  public OptionalStep {

private:
//private member to ensure immutability of HttpRequest object
  HttpRequest req;
    
public:    
    // Implementing the URL Step which returns the reference of the next step: MethodStep
    MethodStep& withUrl(const string& url) override {
      req.url = url;
      //This returns the reference of the MethodStep and not HttpRequestBuilder because child can return the parent to match the return type
      return *this;
    }
    
    // MethodStep implementation
    HeaderStep& withMethod(string method) override {
      req.method = method;
      return *this;
    }
    
    // OptionalStep implementation
    OptionalStep& withHeader(string key, string value) override {
      req.headers[key] = value;
      return *this;
    }
    
    OptionalStep& withBody(const string& body) override {
      req.body = body;
      return *this;
    }
    
    OptionalStep& withTimeout(int timeout) override {
      req.timeout = timeout;
      return *this;
    }
    
    //Here the final build happens and it returns the HttpRequest object
    HttpRequest build() override {
      if (req.url.empty()) {
          throw runtime_error("URL cannot be empty");
      }
      return req;
    }
    
    // To start the building process, at first we return the reference of the UrlStep
    static UrlStep& getBuilder() {
      return *(new HttpRequestStepBuilder());
    }
};

int main() {
    HttpRequest stepRequest = HttpRequestStepBuilder::getBuilder()
    .withUrl("https://api.example.com/products")
    .withMethod("POST")
    .withHeader("Content-Type", "application/json")
    .withBody("{\"product\": \"Laptop\", \"price\": 49999}")
    .withTimeout(45)
    .build();

    stepRequest.execute();
}
    