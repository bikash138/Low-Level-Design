#include <iostream>
using namespace std;

//Base Class Defining the methods to override and the template method
class ModelTrainer {
  public:
  //This is our public template method which is going to maintain the sequence of the steps
    void trainPipeline(const string& path){
      loadData(path);
      preprocessData();
      trainModel();
      evaluateModel();
      saveModel();
    }
  //This are our protected methods which are going to be used by the template method but cannot be used by the client
  protected:
  //We are going to keep some of the steps common and some are fully virtual to be overridden by the child classes
    void loadData(const string& path){
      cout << "[Common] Loading data from " << path << endl;
    }

    void preprocessData(){
      cout << "[Common] Preprocessing data" << endl;
    }
    
    virtual void trainModel() = 0;
    virtual void evaluateModel() = 0;

    virtual void saveModel(){
      cout << "[Common] Saving model" << endl;
    }
};

//Now we will be difining the the concrete classes to override the virtual methods
//Theses concrete classes has is-a relationship with the base class ModelTrainer
class NeuralNetworkModel : public ModelTrainer {
  protected:
    void trainModel() override {
      cout << "[NeuralNetworkModel] Training neural network model" << endl;
    }
    void evaluateModel() override {
      cout << "[NeuralNetworkModel] Evaluating neural network model" << endl;
    }
    void saveModel() override {
      cout << "[NeuralNetworkModel] Saving neural network model" << endl;
    }
};

class DecisionTreeModel : public ModelTrainer {
  protected:
    void trainModel() override {
      cout << "[DecisionTreeModel] Training decision tree model" << endl;
    }
    void evaluateModel() override {
      cout << "[DecisionTreeModel] Evaluating decision tree model" << endl;
    }
   //Uses default save method
};

int main () {
  //First start the the training of the Neural Network
  cout << "===Training Neural Network===" << endl;
  ModelTrainer *nTrainer = new NeuralNetworkModel();
  //the trainPipeline method is only accessibel to the client
  nTrainer->trainPipeline("neural_network_data.csv");

  //Now start the training of the Decision Tree
  cout << "===Training Decision Tree===" << endl;
  ModelTrainer *dTrainer = new DecisionTreeModel();
  dTrainer->trainPipeline("decision_tree_data.csv");
  return 0;
}