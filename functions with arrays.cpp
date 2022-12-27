#include <iostream>
using namespace std;

//void because its just being used to print
void printarr(int arr[], int n) {
// this function has been passed an address
//to store an integer, you need 4 bytes, an address requires 8 bytes
// sizeof() for an array in this function would be 8
//this is because the address has been passed here, not declared, so you get the size of the address of the function
//a[0] in the main fucntion would also point to this address
// the n passed here is also an address to the same n that is defined in the main function
    for (int i = 0; i < n; i++) {
    	cout << arr[i];
	}
}

int main() {
	int n;
	cout << "Enter the value of n" << endl;
	cin >> n;
	
	// don't do a[n] because we don't know how large the array will be
	// better to assume the size of the array won't be more than 100 for now
	//can create the memory dynamically using pointers later
	
	int arr[100];
    for (int i = 0; i<n; i++) {
    	cin >> arr[i];
	}
// sizeof(arr) will be 400, as one int is 4 bytes and there are 100 in the array
printarr(arr, n);
}
