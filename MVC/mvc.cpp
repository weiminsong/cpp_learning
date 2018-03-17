// mvc.cpp
// https://helloacm.com/model-view-controller-explained-in-c/
#include <iostream>
#include "view.h"
#include "model.h"
#include "controller.h"
#include "common.h"
 
using namespace std;
void DataChange(string data) {
  cout << "Data Changes: " << data <<endl; 
}
 
int main() {
    Model model("Model");
    View view(model);    
    // register the data-change event
    model.RegisterDataChangeHandler(&DataChange);
    // binds model and view.
    Controller controller(model, view);
    // when application starts or button is clicked or form is shown...
    controller.OnLoad();
    model.SetData("Changes"); // this should trigger View to render
    return 0;
}


