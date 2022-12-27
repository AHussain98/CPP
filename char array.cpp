#include <iostream>
using namespace std;
int main() {
	
	char ch[] = "brexit";
	//internally, an array has been created which consists of [a,b,c,\0]
//	cout << ch << endl;
	
	char *p = &ch[0];
//	cout << p << endl;
	//this prints the content and not the address, this is because p is a char pointer 
	// a char pointer will print every character until it reaches a null value
	
	char ch2 = 'a';
	char *p2 = &ch2;
	cout << p2 << endl;
	
	//this prints out aabc
	// printing the char pointer p2 causes a to be printed
	//however, when searching for a null character, when the char is only a single character
	//this will cause garbage characters to be printed afterwards, as there are no null chars after a single char
	//this happens if you try to access a single char via pointer
}