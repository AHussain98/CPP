#include<iostream>
using namespace std;

int main() {
	
	int myarr[9];
	for (int i = 0; i < 9; i++)
	 {
		myarr[i] = i;
	}
	
	//size of used to confirm the size of each int is 4 bytes
	
	// cout << myarr will just give the memory address
int b = 0;
    while (b < 9) {
    	cout << sizeof(myarr[b]) << endl;
    	b++;
	}
}