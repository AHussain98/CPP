#include <iostream>
using namespace std;
#include "Student.cpp"

class operations {
	int a;
	int b; //private by default
	
	public: 
	operations(int a, int b){  //have to still use data type for constrcutor and function params within class, even if already defined
    this->a = a; //so the a and b values passed in will becomes the a and b values of the current object when instatiated
    this->b = b;
}

int addition() {
	return this->a + this->b; //using this again
}
    
int subtraction() {
	return this->a - this->b;
}

int multiply() { //since its a member of the class, it has access to a and b already and knows what they are, don't need to define them
	return a*b; //not using this here will make no difference, it matters when your paratemers and variables have the same name however
}
};

int main() {
	//whenever you create an object, it is stored at a particular address
	//the this keyword stores the value of that address
	
	Student s1; //create an object and print its address, constructor called as soon as object created
	cout << &s1 << endl; // same as this (called in constructor)
	//when you call a function for your object, it uses the value of this to find the memory address of the object and make the change
	//there are also situations where you would write this explicitly, writing this->var would refer to the variable belonging to the current object being operated on
	Student s2(10,20); //so for s2, a different this will be created, which points to the address of s2
	s2.printdata(1234); //works, as the constructor has successfully recieved values using this to specifiy that they belong to the address of s2
	
	
	operations op1(12,24); // constructor called as soon as you create it
	int addition_ans = op1.addition();
	cout << addition_ans << endl;

    operations op2(30,15);
    int subtraction_ans = op2.subtraction();
    cout << subtraction_ans << endl;

    cout << op2.multiply();
    
    //we can also create an object and have it take on the constructor values of a previously created object
    
    Student s3(s2); //copy constructor used, we've also taken the private variable values used by the s2 object
    cout << "print s3 data, will be same as s2 as we used copy constructor" << endl;
    s3.printdata(1234);
    
    //however, imagine we have created an object s4, and we want to change its variable values to the ones defined in the constructor of s2
    //this can be done using the copy assignmnet operator ( = is the assignment operator)
    
    Student s4(50,90); //object s4 defined
    s4 = s2; //copied whatever was in s2 object to s4, 
	//Imagine defining a student object with the copy constructor like Student s4=s2. when you do this, this is the same as doing Student s4(s2)
    //using an assignment operator on a object you just declared in a single line is the same as using the copy constructor, the compiler doesnt have to desine an object and then use the assignment operator on it in a seperate line, its all in one
	cout << "used copy assignment operator to change s4 values to s2 values, printed values are same as s2" << endl;
    s4.printdata(1234);
    
    //we can also do the same thing using pointers
    
    Student *s5 = new Student(200,10); //created a pointer of class Student, called it s5 and had it point to a student object stored on the heap
    // so now the copy assignment operator will not work (s4 = s5 would not work)
    //this is because s5 is a pointer, when you create a pointer nad you want to print the value stored at the address the pointer contains, you co cout << *p;
    //so to make the copy constructor work, you dereference the pointer to get to the object it points to
    
    s4 = *s5; //this will work
    cout << "changed value of s4 using copy assignment operator so they reflect taht of the object stored at address in s5"<< endl;
    s4.printdata(1234);
    
    delete s5; // destructor won't be called until you delete the dynamically stored object





}