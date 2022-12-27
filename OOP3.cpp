#include <iostream>
#include <bits/stdc++.h>
#include <String>
using namespace std; // this code originally threw an error becasue this was below the include below. so the compiler came across a cout in the included file before it knew it was using namespace std, so it didnt know what cout was as namespace std came after the include
#include "Vehicle.cpp" //when files are included, they are essentially copy-pasted 

int main() {
	//encapsulation means binding together data and the functions that manipulate that data, that keeps both safe from outside 
	//misuse. So for example declaring a class with functions and variables that can only be accessed by that class or inherited classes. 
	//Access to object data should be rarely direct, object data should instead be declared as private and then read or modified by methods with public declerations to ensure correct access to the data (getters and setters)
	
	//abstraction -> recution of complex concepts to simplifed objects that can be referred to in generic terms
	//Data abstraction refers to providing only essential information to the outside world and hiding their background details, i.e., to represent the needed information in program without presenting the details.
    //Data abstraction is a programming (and design) technique that relies on the separation of interface and implementation
	//Let's take one real life example of a TV, which you can turn on and off, change the channel, adjust the volume, and add external components such as speakers, VCRs, and DVD players, BUT you do not know its internal details
	//In c++ we can call functions from different source files and classes without explicitly knowing what they're doing in detail, just what the result is
	
	int arr[] = {4,2,5,1,3};
	sort(arr, arr+5); //  we dont know how the sort function in the included file works exactly, its details are abstracted but we dont care because it does what we want
	for (int i = 0; i < 5; i++){
		cout << arr[i] << endl;
	}
	
	//inheritance-> allows us to define a class in terms of another class, which makes it easier to create and maintain an application. 
	//This also provides an opportunity to reuse the code functionality and fast implementation time.
    //When creating a class, instead of writing completely new data members and member functions, the programmer can designate that the new class should inherit the members of an existing class. 
	//This existing class is called the base class, and the new class is referred to as the derived class.

  //  Vehicle v;
  //  v.setInitials(4, "Blue");
  //  v.print();

  //  Car c1("Mercedes");
  //  c1.numGears = 3; //make and numGears can be accessed directly as these are public
    
 //   c1.setInitials(4, "Black");     //these data members were protected in the vehicle class, so they can onlybe accessed via a public function when inherited 
  //  c1.print();
    
    Audi a3(7,4,"Gun Metal");
    a3.print();   //audi class has a print function, so thats the fucntion getting called here, if it didnt then we'd be calling the print fucntion of the class that audi inherits from

}