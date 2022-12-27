#include <iostream>
using namespace std;

void increment(int a[]) {
	a[0] = 100;
	
}

int incrementn(int n) {
	n++;
	return n;
}
// the value of a[0] will change in main due to the increment function being called
// this is because a is an address
//passing a memory address to a function causes the value at the addres to be changed by that function
//n is not a memory address so isn't changed without being returned and then having the n variable manually updated
//the memory address stored in a points to a[0]. Thats why indexing begins at 0.

int main() {
	//any array value you don't initialise will become 0 by default
	int a[5] = {1,2,3};
	int n = 10;
	
	increment(a);
	
	for (int i = 0;i<5;i++) {
		cout << a[i] << endl;
	}
	
	n = incrementn(n);
	cout << n << endl;
	
	cout << a;
	
	
}