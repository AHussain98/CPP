#include <iostream>
using namespace std;

void fun(int &j) { //passing by reference so no copy, operating on the value contained in the memory address directly
// we can also pass constant values to functions, we could write const in the brackets above in the function arguments definition

	int a = j + 10;
	j++;
	cout << "a = " << a << endl;
}


int main() {
 int i = 20; // this means the value of i cannot change, const variables don't change their value
const int &k = i; //	we are creating k and setting its address to be the same address as i's, so they currently share a value
    //k++; // this will fail as we can't edit a const variable
    i++; //this will work as i is not a const variable
   cout << i << endl;
    //since the value has increased, this proves that even though k has become a constant, it doesn't mean that the value at k's memory location must rreamin constant, it just means we can't change this value through k
	
//fun(k) this will not work
	fun(i); // this works because i is not constant, the value at the address of i is increased, therefore so has k
cout << k << endl;	 


// if i was made constant initially, and you tried to make &k = i without also making k constant, it would fail
//if the variable is initially a constant, you cannot make anothe rvariable share the value at that memory address without also being constant

//pointers can also be constant
int const j = 12;
int const *p = &j; // pointer that is pointing at a constant integer
*p = *p + 1; //unnacceptable
// to make the pointer a constant too:
int * const p = &i; // put the * before const when declaring a pointer to make the pointer a constant, so this points to an address that can't be changed
// you can change where the pointer points, even if it points to a constant value, but only if the pointer itself is not a constant

//you can make the address teh pointer points to a constant, and also make the value at that address a constant, see below
// int const * const p = &i;
}