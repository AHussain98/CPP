#include<iostream>
using namespace std;


int factorial(int n) {
		int i = 1;
		int factorialn = 1;
	while (i <= n) {
		
		factorialn = factorialn * i;
		i++;
}
	
	return factorialn;
}


int main() {
	
	cout << "enter n" << endl;
	int n, r;
	cin >> n;
	cout << "enter r" << endl;
	cin >> r;
	
 int factn = factorial(n);
int factr = factorial(r);
int factnr = factorial(n-r);

cout << (factn / (factr * factnr));
}


/*
	int factorialn = 1;
	int i = 1;
	while (i <= n) {
		
		factorialn = factorialn * i;
		i++;
	}
int factorialr = 1;
int b = 1;
 while (b <= r) {
 	factorialr = factorialr * b;
 b++;
 }

int factnr = 1;
int c = 1;
while (c <= n-r) {
	factnr *= c;
c++;
}

int ans = factorialn/(factorialr * factnr);

cout << "Your answer is " << ans;
*/
