#include <iostream>
using namespace std;

void print(int * p) {
	cout << p << endl;
	cout << *p << endl;
}

//you can include pointers as function arguments

void increment(int *p) {
	p= p + 5;
	cout << p << endl;
}
// p is an integer pointer
// adding 1 means adding 4 bytes, since one is an integer
//therefore address changes by 4 bytes


// the increment2 function below operates on the value stored at the memory address
//therefore the change carries over
//we are telling the compiler to increase the value of teh variable stored at address p
//the p value isnt changed, we're using it to change i
void increment2(int * p) {
	*p = *p + 1;
}

void change(int arr[], int size) {
	cout << "size of arr in change function = " << sizeof(arr) << endl;
	arr[0] = 89;
}

void change2(int arr[]) {
	arr[0] = 47;
}

int main() {
	
	int i = 10;
	int *p = &i;
	print(p);
	increment(p);
	
	cout << p << endl;
	// the value of the p above returns the original address, the address of i
	// when the functions are called, they are passed a copy of p
	//they then operate and when the function is finished, that p copy is destroyed
	//this is why we can cout p above and it has retained its original value

//in the increment2 function, value of i has been increased, because we have operated on the value, not the address
increment2(p);
cout << "New value of i is: " << i << endl;

cout << endl; 

int arr[10];
arr[0] = 9;
cout << "arr[0] is = " << arr[0] << endl;
cout << "size of arr in main = " << sizeof(arr) << endl;
change(arr,10);
cout << "New arr[0] is = " << arr[0] << endl;

//the change of the array value works because the function is passed the memory address of the array
//the change is being made at the address, because using arr as a function argument makes arr act as a pointer
//so teh compiler goes to that memory address and makes the change there 
// using sizeof() on the arr in the function returns 8 bytes, because pointers are usually 8 bytes
//using usingof() on the arr in main returns 40 because it is an array of 10 ints
//you can also pass part of an array, the compiler will take whichever part of teh array you pass as arr[0], it thinks the address starts form there

//see below, we have passed the array starting from the 4th cell, as the pointer arr is edited so it points 4 cells down from arr, which is arr[0]
//however the chnage2 function believes the array pointer we pas it starts at the 0 index of the array, it knows no better
//so it chnages thhat avlue, but because this same address is contained in the original array we created
//we can access the value and confim the change is made
change2(arr + 4);

cout << arr[4];

}