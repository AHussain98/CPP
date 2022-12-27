#include <iostream>
using namespace std;

void increment(int &n) {
//now we are passing the memory address of n, rather than the value, so the change will be carried accross into main
//there is no copy of n made, rather the change is made on the value stored at the n address passed to the function
	n++;
}

int main() {
	int i = 10;
	int j = i;
	i++;
	cout << i << endl;
	cout << j << endl;
// so even though we've made j equal to i, the value of j isn't updated with the new value of i
//this is because we passed in just the value
	
	//putting an & in front of the variable will tell the compiler to internally store the variable at the same memory location as i
	//this is passing by reference, referencing the address of the variable
	
	int &k = i;
	//as soon as you declare something as a refrence variable, you must initialise it with a value
	// so just doing &k; woudl be invalid
	//k takes the address of whatever is after the =
	i++;
	
	//using & means whatevr is after the = will have the same address as the variable attached to &
     // we are not creating any memory for k, by passing by reference, k is just another name for i now, they share a single memory address
	//k now has the same address as i
	// therefore see below
	
	cout << k << endl;
	
	k++;
	cout << i << endl;
	
	//when i is updated, k is also updated

//when we pass i into the increment function, in the symbol table, we've created n who's address is the same as i
//there is no memory that has been created for n, n is pointed to i's address
//so the changes carry over
increment(i);
cout << i << endl;
}