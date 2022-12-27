#include <iostream>
using namespace std;

int main() {
	// each variable you create is stores in the internal symbol table
	// this table is created and maintained by the compiler to track variables, names, instances of functions, classes, objects etc...
	// when you call a variable in your programme, you are pointing the compiler to the associated memory address of the variable in the symbol table
	int i = 10;
	cout << &i << endl;
	
	// & ampersand used to access the address of the variable, printed in hexadecimal
	// hexadecimal addresses usually atored in 8 bytes, but this can depend on compiler(use sizeof() to check)
	//pointers are basically a variable that store the address of a specific variable
	//pointers are defined by putting a * before a variable name and equalling it to the address of a variable
    // pointer should have the same data type as the variable it points to
    int * p1 = &i;
	cout << p1 << endl;	
	//pointers have their own memory addresses, as they're variables themselves
	cout << &p1 << endl;
	cout << * p1 << endl;
	
	
	double sid = 145.55;
	double * d_ptr = &sid;
	cout << sid << endl;
	cout << *d_ptr << endl;
	
	// doing cout << p1 will just print the address stored in the pointer
	//doing cout << *p1 will print the actual value of the variable at that address
	// so the pointer can be used to access the variable its pointing to
	//so line 16 is declaring the pointer, 17 prints the address the pointer is pointing to
	//line 19 is printing the address of the pointer
	//20 prints the value of the variable at the address the pointer points to (dereferencing)
	//Take note that the symbol * has different meaning in a declaration statement and in an expression. When it is used in a declaration (e.g., int * pNumber), it denotes that the name followed is a pointer variable. Whereas when it is used in a expression (e.g., *pNumber = 99; temp << *pNumber;), it refers to the value pointed to by the pointer variable.


}

