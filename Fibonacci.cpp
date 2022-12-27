#include<iostream>
using namespace std;

int main() {
	
	
	int n = 5;
	int a = 0;
	int b = 1;
	int fibon = b;
	
	for (int i = 1;i<n;i++) {
		fibon = a + b;
		a = b;
		b = fibon;
		
	}

cout << fibon;
}