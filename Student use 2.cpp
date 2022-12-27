#include <iostream>
using namespace std;
#include "Student2.cpp"

int main() {
	
	int age = 24;
	char name[] = "asad"; // create the array asad, [a,s,a,d,\0], imagine at address 700
	Student s1(age,name); // so we have now passed in address 700 into the constructor, once it recieves that address, and then sets its name variable equal to whatever it finds at that address
	//although we are passing in the char array for my name, it will only recieve the address, as the constructor only takes the pointer
	
	s1.display();
	
	name[2] = 'x'; // change the value that's being pointed at
	age = 33;
	Student s2(age,name); // s2 has different age but s2.name has the same value as s1.name, as the same address is being possed in 
	s2.display(); // so s1 and s2 have the same name value, as they're pointing to the same place
	
	s1.display(); //change carried over
	//s1 and s2 names being the same and reflecting the same changes is an example of a shallow copy
	// In shallow copy, an object is created by simply copying the data of all variables of the original object. This works well if none of the variables of the object are defined in the heap section of memory. If some variables are dynamically allocated memory from heap section, then the copied object variable will also reference the same memory location.
    //This will create ambiguity and run-time errors, dangling pointer. Since both objects will reference to the same memory location, then change made by one will reflect those change in another object as well. Since we wanted to create a replica of the object, this purpose will not be filled by Shallow copy. 
    //Here, the shallow copy references the same underlying array address as the original, so the changes are reflected in teh orignial, this can eb dangerous

//so to create an exact replica and avoid changing the same data values, we need to create  a deep copy
//we need to set it so that the replica exists on its own address, and changes are independednt of the original

    cout << "this is a new student s3, copyingin values from s1" << endl;
    Student2 s3(age,name);
    s3.display();

cout << "make another change to name" << endl;
name[0]='x';
name[1]='x';
cout << "change carried over in s1: " << endl;
s1.display();
cout << "but not in s3: "<< endl;
s3.display();

//now create student s4, use the copy constructor on s1

Student s4(s1);
s2.display(); // will be same as s1
//the copy constructor internally also does shallow copy, so now any change in the name array will affect s4.name aswell
//in this case, we've copied in the same address for the name variable passed in for s1 for s4 aswell, so the change is reflected
//so to stop the copy constructor from using shallow copy, we need to define our own copy constructor
}




