#include <iostream>
using namespace std;

//recursive functions work based on a call stack of sequential function calls
//to find the factorial
int fact(int n) { //fact(5) now has its own space in memory where n = 5, then it will create a memory value for n=4, etc...
//in each of these memory blocks, n is different, it reduces by 1 each time, but when it reaches 0, it will be retunred 1, so value of fact(0) is 1
//therefore, when n is 1, smallans =  fact(0) which is 1, and ans = 1 * 1 = 1
//therefore fact(1) is 1, and now fact(2) can be worked out, fact(2) smallans  = fact(1) = 1, ans = 2*1 = 2
//then fact(3) can be worked out because we now have a value for fact(2) etc...
	if(n==0) {
		return 1; //base case, this is the value that will kick off the recursive chain, because we know its value
	}
	//this is our equivalent of factorial(0) = 1
	//without this, the loop would continue on endlessly
	
	int smallans = fact(n-1); // first find the value of factorial(n-1), this will call the function for each value of n
	int ans = n*smallans;
	return ans;
	
}

int main() {
	
	//a function calling itself is a recursive function
	//Factorial is a function that is used to find the number of possible ways in which a selected number of objects can be arranged among themselves.
	//If you think about factorials as the number of possible combinations given a set of numbers, then 0 factorial means that there is only 1 possible way of combining 0 numbers.
	//so 0! = 1
	//factorial(n) = n * factorial(n-1)
	//factorial(5) = 5 * factorial(4), where factorial(4) = 4 * factorial(3) etc...
	
	int n = 5;
	int ans = fact(n);
	cout << "ans is: " << ans << endl;
}