#include <iostream>
using namespace std;
#include "Fraction.cpp" // in an include statement for a cpp file, the cpp file name must be written in full quotes

void fun(int i) {
	i++;
}

void addressfun(int &i) {
	i++;
}

int main() {
	
	Fraction f1(1,2);
	f1.display();
	cout << endl;
	
	Fraction f2(1,4);
	
	f1.add(f2);
	cout << "after adding f2: " << endl;
	f1.display();
	
	cout << "multiply f1 and f2" << endl;
	f1.multiply(f2);
	f1.display();	
	//more practice of passing by reference 
	
	cout << endl;
	cout << endl;
	
	cout << "initial value of i: " << endl;
	int i = 5;
	fun(i);
	cout << i << endl; // even though we've dont i++ in the fun function and passed i to it, when we print the value of i it remains as 5
	//this is because we passed i by falue to fun, we didnt pass my memory address or reference the address, so a copy of i was made with the same value, but the i in main was unaffected by the change
// fun created a copy variable with the same value as i, but this is seperate from main i

//we can see the main i change by calling the function and passing i by reference, no copy is made when this is done
cout << "now passing i by reference: " << endl;
addressfun(i);
cout << i << endl; // so to avoid making copies and accessing the values at the actual address, we can pass by reference 
//however, maybe we want to access the values at that address but we don't want to make any changes to them?
//in which case, you pass by const reference : fun(int const &i)
//now we can addess the value at i's address without making copies and without risking any changes beng made to that value
//however, if fun has a const keyword in the parameters, we cant change i through the fun cuntion, we can still change it through main code, only the path through teh function is blocked
// so i++ in main would still work



//practice using getters and setters

Fraction const f5(1,2);  //calling the below functions will not work without making them also const, as the object us a constant, so een the get functions which don't change anything cannot be called, as the compiler doesn't know the difference
cout << f5.getDenominator();
cout << endl;
cout <<f5.getNumerator();
cout << endl;
// f5.setDenominator(4); this wont work because the set function changes the values of the object, and the object is const so the compiler will throw an error
cout << f5.getDenominator(); // const objects can only use const functions, that don't make any changes
// if you were to create another object taht wasn't const, then you would be able to call the set functions for those objects, as they make changes but the object is not const, so its acceptable
}