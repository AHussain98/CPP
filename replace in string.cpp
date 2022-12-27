#include <iostream>
using namespace std;

int main() {
	char arr[] = {'a','s','a','d'};
	
	cout << arr << endl;
	
	for (int i = 0; i<4; i++) {
		// remember to use equality operator, else the if sttement automatically becomes true if you just use the equality operator =
	
	if (arr[i] == 'a') {
		
		arr[i] = 'x' << endl;
	}
	}
	
	cout << arr;
	
}