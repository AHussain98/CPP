
#include <iostream>
using namespace std; // placement of this matters, cant be too low
#include "Fraction.cpp"


//operator overloading

int main() {
	
	//Imagine we want to find a way to add two of the fraction classes we defined earlier
	//because + is defined to work with ints and not classes, we'll need to overload it 
	//overload means extend the definition of an operator
	
	
	Fraction f1(1,2);
	f1.display();
	Fraction f2(1,4);
//	f1.add(f2);
//	Fraction f3 = f1 + f2; // this is how we use the overloaded + operator in the main codeblock
//	f3.display();
	Fraction f4 = f1*f2; // test the overloaded * operator
	cout << endl;
//	bool ans = f1==f2;
//	cout << ans; // gives 0 so shows they're not equal
//	++(f1); //this is how you call the overloaded precrement operator
f1.display(); // added one
//Fraction f5 = ++(f1); // here we're calling the overloaded precrement operator and assigning it to the new fraction object f3, so both f1 and f3 get updated
//f5.display();

Fraction f6 = ++(++f1); //this type of nesting is only possible for preincrement operator, not postincrement
f6.display();

Fraction f7 = f1++;
f7.display();
f1.display();


Fraction f8(1,2);
Fraction f9(1,4);
f8+=f9;
f8.display();
}