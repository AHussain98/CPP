#include<iostream>
using namespace std;

//finding a number to a sprcific power
int power(int x, int n) {
	if (n == 1) { // base case which will break the call stack function chain
		return x;
	}
int next = power(x,n-1); //we call the next function here because we need to stop the current one at this point, the returned value will be stored here when teh programme returns down the stack
// now we've got the value of the power before, we can store it
//now mulitply by the original x to get the next power, and return this to be carried down the stack
int ans = x * next;
return ans; // the return returns the value to teh function taht called it

}

//fibonacci sequence, 0,1,1,2,3,5,8 etc...
//the 0 value in fibonacci actually is the 0th index, 1 is 1st, 1 is 2nd, 2 is 3rd etc...
//essentially, fibo(n) = fibo(n-1) + fibo(n-2)
int fibo(int f) {
// we need two base cases since we're calling f-1 and f-2
if (f == 0) {
	return 0; //base case 1
}
if (f == 1) {
	return 1; //base case 2
}

int value1 = fibo(f -1); // call teh function recursively
int value2 = fibo(f -2); // call it again for the second value we need, this doesn't actually doesn't run until the chain of f-1 reaches its end and returns 1, thereby moving onto the f-2 function
return (value1 + value2);	
	
}



int main() {
	cout << "enter x " << endl;
	int x,n;
	cin >> x;
	cout << "enter n " << endl;
	cin >> n;
	
	int ans = power(x,n);
	cout << ans << endl;
	
	cout << endl;
	
	int f;
	cout << "enter f " << endl;
	cin >> f;
	int fibans = fibo(f);
	cout << "fibo(f) = " << fibans;
	
}