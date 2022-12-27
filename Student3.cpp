#include <iostream>
using namespace std;

class Student{ //classed don't have the () in their decleration! Functions and constructors do
	int age;
	int const rollno; // imagine we want to make rollno a const, this will cause an error because the rollno isn't initialised on the same line it's declared
	//we can get around this by using an initialisation list on our constructor
	int &a; //we can do the same with reference variables, declare them in the class but set them up in the in the initialisation list
	public:
		Student(int r, int age, int a):rollno(r), age(age), a(this->age) { // this will work because even before the constructor is called, the rollno is assigned, thereby satisfying the const initalisation condition
		//initalisation list is used when you want to initalise something and keep it constant
	    //the age written in the parameters list is the objects age and the age in brackets is the value passed in the constructor parameter
		} // so you dont need to use this-> in the initalisation list, but it can be useful when you want to delcare a reference variable, as above
		// so the this-> age is referring to the age value initalised previously. This is how you can define elsewhere variables that you'd typically need to initalise on the same line (such as reference and const)
	//you can also include some parameters in the initalisation list, and leave others to be initalised in the constructor proper, they dont all have to be in the initalisation list. Its good to put the consts in the list and leave other thinsg in the constructor
		void display() {
			cout << "the age is: " << age << endl;
			cout << "the roll number is: " << rollno << endl;
			cout << "the reference variable for age is " << a << endl;
		}
};

int main(){
	
	Student s1(10,26,500);
	s1.display();
	
	
	int a = 5;
	int const b = a; // so b cannot be changed, const variables need to be initalised on the same line as they're declared
	cout << b << endl;
	int &k = a; //k is a reference variable, k is pointing to the same address as a, reference variables must also be initialised on the same line as they're delcared

k++;
cout << a << endl; // a is changed through changing the reference variable k


}