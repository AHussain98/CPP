#include<iostream>
using namespace std;

void printNumber(int n) {
	//we want to print all numbers to n, so we want to print the number argument last
	//the recursive function base case must therefore be the printing of 1
	if (n==1) {
		cout << n << endl;
		return; //function can end here, and this covers us incase n is 1 initially
	}
	printNumber(n-1); //assume this is true, this is the part which calls the function for each number to n sequentially, 1 is returned first due to the placement of the basecase
	//the numbers are then ouputted in the reverse order of how they were generated in the memory, following the chain back to n
	cout << n << endl;
}
// so initally, take n=5 as an example, this is the first argument in the printNumber function
//since n is not 1, the first if block is bypassed and printNumber(4) is called, this ocntinues until n == 1, which prints 1 and then returns
//then each sequential printNumber(n) function can complete, printing their n values sequentially until n becomes its original 5
//the return statement when n == 1 means return to the previously called fucntoin of printStatment(2), these are on LIFO stack
// once printNumber(5) gets printed, the stack is clear and the program can return to the main function, as there are no more printNumber functions to call


//we can also do this in reverse, see below
//again, start with base case
void reverse(int n) {
	//so first reverse(6) is called, then of 5, then 4...
	//we want to start by printing n and then reduce each n by 1
	//base case as before to break the recursive chain and get it going backwards in the memory stack
	if (n == 1) {
		cout << n << endl;
		return;
	} //say we make n = 5, when reverse(5) is first called, it will print 5 first and then call reverse(4) which prints 4 and tehn calls reverse(3) etc... until n is 1 when 1 is printed and the function breaks
	cout << n << endl; 
	reverse(n-1); // once teh break happens, reverse(2) will resume from this point, it has alread printed 2 and the function ends here so the fucntion just completes, so the programme just moves onto reverse(3), which has already printed so just completes and the programme moves again, backwards down the stack until we reach main
} //reverse(6) is last to complete, and the programme returns to the main function

int main() {
	
	//recursion is derived from a principle called PMI, principle of mathematical induction
	//this involves using a base case to generate an inital value and thereby generate subsequent values which cancel out a recursive function
cout << "enter n " << endl;
int n;
cin >> n;
printNumber(n);

reverse(n);




}