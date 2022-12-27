#include <iostream>
using namespace std;

void increment(int ** p) {
	**p = **p +1;
}

// the above will cause a change to teh value because we're passing it the value of a variable in a stored memory address
//so its operating on teh value itself

int main() {
	int i = 11;
	int * p = &i;
	cout << i << endl;
	*p  = *p + 1;
	//i will now become 12, as we have accessed the value of the variable stored at p using the * operator
	cout << i << endl;
	
	// you can create a pointer that points to another pointer
	//your pointer must be the same data type as the type it points to
	//double pointers are declared by doing ** in the declaration
	int ** p2 = &p;
	
	cout << "address of i : " << &i;
	cout << endl;
	cout << p2 << endl; // address of p
	cout << *p2 << endl; // p2 is derefenced using * so we're accessing the value of what's stored at p2 which is the address of i stored via p
	cout << **p2 << endl; //now we're finding the value stored at the address of the value stored at the earlier pointer address, which is the value of i

increment(p2);
cout << **p2;
//we've now increased i by using the increment function with a double pointer
}