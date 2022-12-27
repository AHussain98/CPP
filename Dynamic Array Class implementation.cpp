#include <iostream>
using namespace std;
#include "Dynamic Array Class use.cpp"
//so we're trying to create an array class that will autoamitcally create another array when the current one if filled and copy over the old values into the larger one

int main() {
	
	DynamicArray d1;
	d1.add(7);
	d1.add(5);
	d1.add(8);
	d1.add(9); 
	d1.add(10);
	d1.add(11);
	d1.print();
	
	cout << endl;
	
	d1.add(0,99);
	d1.print();
	
	cout << d1.getData(2);
	
	DynamicArray d2(d1);
	cout << endl;
	d2.print();
}
