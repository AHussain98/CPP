#include <iostream>
using namespace std;
#include "staticMembers.cpp"

int main(){
	Student s1, s2, s3, s4, s5;
	
cout << Student::NumStudents(); //this is how you call a static function, through the use of the scope resolution operator
 // this is good practice since the static variable hsere doesn't belong to any one object, but rather the class
}