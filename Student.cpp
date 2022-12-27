class Student { //define class outside main function
//public : // everything below this public decleration becomes public
int age; // class variables are private by default, without being public, we cannot access them
int student_id; // c++ class variables are private by default, so you won't be able to access these in main code without making them public
// however the disadvantage of having public variables is they they can be edited at will	
public :
void getdata(int a, int b) { //to get around this, we can use the below method
	age = a; // age becomes a
	student_id = b; }// student_id becomes b
//you can do this because the getdata function is defined in the student class, so the age and student_id are variables are usable
//so if we make the getdata function public but the variables age and student_id are private by deafult, then they are protected,a dn only accessible through this function
// but you still won't be able to print them, since you can't get access tpo them directly, so you need to make a function to get around that
void printdata( int password){
	if (password != 1234){
		return;  //if the passowrd on the function is not correct, then the user will not have access to the values and the function ends
	}
	
cout << "age = " << age << endl;
cout << "student id = " << student_id << endl;
} // again we don't access the variables directly, simply refering to them

//constructors are functions which have the same name as the class, these initialise the object with default values
//constructors must be public to be called outside of the class, they have no return type
//default constructor takes no parameters, it you create a cusom constructor with parameters, you have to have parameters in each instatntiation of the object, or the compiler will error
 Student() {
 	age = 10;
 	student_id = 1234567; // these are defaulyt values upon creation of the object, despite them being private
	cout << "default constructor" << endl; //as soon as you create the constructor, it will be called when an object of the class is created
    cout << this << endl; // also print the value of the address of this particular object
}
//we use constructors to force the programme to work even if the user doesn't provide us any values, by providing default values
//as soon as you create an object, the default constructor is called, above we have changed the default constructor
//however, a class can have multiple constructors, see below for non default
Student(int age, int student_id) {
	this->age = age; //the this keyword is useful when you have a parameter with the same name as a class variable
	this->student_id = student_id; // ordinarily this would cause an error as the cmpiler would be confused at the variables having the same name, using this makes it clear that we are setting the age of the current object to the age value passed into the constructor
	cout << "non-default constructor" << endl;
}

//destructors are the inverse of constructors, they are called upon an object being created
//when objects are instantiated, a space in memory is reserved to store the object and its data
//to free the memory up again when the object is no longer used, we use destructors
//Destructors take no parameters and have no return type
//Destructors preceded by a tilde ~
//However, if you create an object with a pointer, the destructor will not be called until you use teh delete keyword on teh pointer

~Student() {
	cout << "Destructor called" << endl;
}

}; // this is how you define a class in c++, with the semicolon at the end