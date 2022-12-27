//shallow copy and deep copy
#include<string> // this will allow us to use string functionality like the functions used below for deep copy
class Student{
	int age; //these can be private because we're not changing them directly, rather we are changing them through the class
	char *name; //pointer to the char array
	
	public: //constructor should be public because it is called automatically
	
	Student (int age, char *name) { // so you pass in an age and the address of a name
		this->age = age; // so the age of the object is the age passed in
		this->name = name; //so the name of the object is the value at the address that is passed in
	} // why don't we use *name in the constructor??
	//An array is essentially a pointer to the first element in it, so you declare the function parameter as a pointer of your type.
	// When you pass an array as a parameter to a function it decays to a pointer to the first element of the array. So there is normally never a need to pass a pointer to an array.
	void display() {
		cout << "Name: " << name << endl;
		cout << "Age: " << age << endl; // as we know when printing an array,the whole array is printed starting form the address that is passed in, until the null pointer is reached
	}
//above is a shallow copy
//now we can make a deep copy constructor

Student(Student const &s) { // trying to create copy constructor logic in a class definition in header file can cause issues, give an address to the copy constructor so it copies from that object directly, and doesnt make any copies, whicch would cause another copy constrcutor to be called and an infinite loop 
	this->age=s.age;// say for example when using copy constructor, you do Student s2(s1), which on this line means Student s = main.s1 on one line, and this line calls the copy constructor, so we go back to Student(Student s), when we've defined s as main.s1, so Student s = main.s1 is called, and the cycle goes around again
	this->name= new char[strlen(s.name) + 1];// so since this is happeneing, Student(Student s) will cause an infinite loop due to constantly calling copy constructors, if we do Student(Student &s), it doesn't make a copy, it uses the values of teh original, so there is no infinite loop (in the same way we used the fun function erlier with &, accessing the value at that address only with no copies)
	strcpy(this->name,s.name); // we don't want the student S in the brackets to make a copy, so we do &s instead, so there's no loop
} // add const just to say s1's values can be read but they must not be changed through the copy constructor logic
	
};// below is same but deep copy version

class Student2{
int age;
char *name;

public:
Student2(int age, char *name) {
	this->age=age;
	this->name= new char[strlen(name) + 1]; //here we have dynamically allocated a space in memory for the name variable, which takes a copy of the original but in a new space on the heap
	//the this->name refers to the name variable of the object
//we've then created this as an array of chars on the heap, with the size of the array equal to the number of letters in the name, plus anothe rone for the null pointer
//so this is a completely new address from the original
//strlen will not include null pointer, so add one for it
// but right now the name has not been stored there, we've only just created the array and stored it in the heap as the name variable
//so now we need to copy the values into the new heap array we've created

strcpy(this->name,name); //this means in this->name, the heap array we've created dynamically, copy the value of the array we passed in to this->array
//so we're no longer copying the address like before, we're actually creating a new array and then copying the values in from the original name array

}

	void display() {
		cout << "Name: " << name << endl;
		cout << "Age: " << age << endl; 
}
};

