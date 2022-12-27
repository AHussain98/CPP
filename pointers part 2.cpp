#include <iostream>
using namespace std;

int main() {
//	if you change the value of your pointer, it will now point to anothe memory address, and you'll have to repoint it back to where you want
// this will cause your pointer to point to a garbage value, and is dangerous because you could be pointing to a critical part of your system memory
// best practice is to declare your pointer with a null value of you don't where where it needs to point just yet

	int arr[10];
	arr[0] = 10;
	arr[1] = 11;
	cout << arr[0] << endl;
	cout << arr << endl;
	cout << &arr[0] << endl;
	cout << *arr << endl;
	cout << *(arr +1) << endl;
	int *p = arr;
	
	cout << p << endl;
	cout << arr << endl;
	cout << &arr << endl;
	
	cout << endl;
	
	cout << *p << endl;
	
	cout << p[0] << endl;
	//you can treat your pointer as an array, even though you're pointing to the address of arr
	cout << p[1] << endl;
	
	//arr[0] and arr have the same memory location, 'arr' can be used as the memory address of the array
	// by dereferencing using *arr, we can access the value of arr[0] just with the *
	//you can even access the next value by deferencing the next value in the address 
// arr + 1 can be used since we're pointing to an integer, and adding one to the address where we're pointing menas adding 4 bytes to the addresss, therefore accessing the next variable in the array when dereferencing (arr+1)
// this is the same as cout << arr[1]
//sizeof(p) will be 8 bytes, as it is an address
//sizeof(arr) will be 40 bytes, as its an array of 10 ints
//regardless of having the same memory address, the size of these are different
//however, the value of p, arr and &arr are the same, as these are all the value of the address of the array
// using the dereference operator *, we can use access the value that p is pointing at
//you can also use your pointer to access array values directly, e.g. p[0] and p[1]

}