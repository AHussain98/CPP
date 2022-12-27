#include <iostream>
using namespace std;
#include "Vehicle.cpp"
//polymorphism refers to appearing in many different forms
//this can be done at compile time and runtime
//compile time polymorphism -> function overloading, function overriding, operator overloading



void area(int a, int b){
    int ans = a*b;
    cout << ans << endl;
}
void area(int side){    //overloaded function, overloading means doing the same thing but taking in different arguments
    int ans = side*side;
    cout << ans << endl;
}

int main(){
    
  int a = 10;
  int b = 5;
  area(10,5);   //we've used the original definition of the area function to find this area
  
  int side = 4;
  area(side); //uses the second area definition 
  //functions having the same name but different parameters like this is function overloading, overloading is strictly based on taking in different parameters , either a different number or a different data type
  
  Car c;
  c.print(); // there is a print function for the vehicle class and the car class that inherits from the vehicle class
  //the c.print fucntion above automatically calls the print fucntion defined in the car class,not the vehicle class
  //the vehicle print function has been overriden in car, this is function overriding
  //if the car class did not have a print fucntion, then the print function of the parent vehicle class would be called instead
  
  //we can also create a pointer of type vehicle and point it to a new vehicle object stored on the heap
  Vehicle *v = new Vehicle(); //vehicle pointer to new vehicle object
  v->print(); // you can call the print function using the pointer to the object 
  
  Car *c1 = &c; //made a car pointer and pointed to the address of c
  c1->print(); //can call the car print function via the pointer
  
  cout << endl;
  cout << endl;
  //create a vehicle type pointer and point it at the car object
  Vehicle *v1 = &c;
  v1->print(); // even though this is pointing to a car object, the vehicle version of the print function is called, as we're using a vehicle pointer and car inherits from vehicle
  // v1 is a pointer, it contains the address of a car object , but the print fucntion is calls is vehicle's
  //this is runtime polymorphism, to get the v1 pointer to call car's print function, we need to change the parent fucntion so that its virtual
  //so the vehicle print function is now virtual, and the v1 pointer is now calling the car version of the print function
  //The compiler binds virtual function at runtime, hence called runtime polymorphism.
  // Use of virtual function allows the program to decide at runtime which function is to be called based on the type of the object pointed by the pointer.
//In C++, the member function of a class is selected at runtime using virtual function. The function in the base class is overridden by the function with the same name of the derived class.
//a purely virtual function is a function in the base class that will never be called and is empty, it only exists because its derived classes will call a function with the same name, it exists as a mask for them.
//any class containing a purely virtual function can never be instantiated, this will cause an error, such classes are referred to as abstract classes
//An interface class is a class that has no member variables, and where all of the functions are pure virtual! In other words, the class is purely a definition, and has no actual implementation.
// Interfaces are useful when you want to define the functionality that derived classes must implement, but leave the details of how the derived class implements that functionality entirely up to the derived class.
}