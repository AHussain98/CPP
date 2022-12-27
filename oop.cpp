#include <iostream>
using namespace std;
#include "Student.cpp"// this means copy everything in the cpp file called student.cpp and paste it here 
//remeber to use quotes for source files and <> for header files
// you can define the classes in a seperate file, it is common practice to do this in a header file
int main() {
	//say for example you're creating a software system to use in a school
	//the student class would need properties such as name, age, phone, address, gender etc...
	//each student object is an instance of the student class, a class is a blueprint for an object with the attributes each instance should have defined in the class 
    
Student asad; // create an object

// asad.age = 24; //assign values to an objects variables, using . operator
// asad.student_id = 202234;

asad.getdata(24,1234567);
asad.printdata(1234); // because you're calling it for object asad, it will use the age and student id variables belonging to asad 

//cout << asad.age << endl; // won't work
//cout << asad.student_id << endl; // won't work

Student aisha; //  make another object

aisha.getdata(25,234523);
aisha.printdata(12); // false password, won't print

//arrow operator: first create a pointer of the type class
Student * s3 = new Student;
s3 -> getdata(30,10); // arrow operator is used by a pointer to access the members of the class it points to
s3 -> printdata(1234);
//alternatively, you can access the members of the class by dereferencing your pointer
(*s3).printdata(1234); // same as above, arrow operator is even simpler so preferred 

Student s4(33,999); //instantiate an object with non default constructor
s4.printdata(1234);
}