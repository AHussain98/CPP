#include <iostream>
using namespace std;

void replace(char input[], char x, char y) {
	
		cout << input << endl;
	int i = 0;
	while(input[i] != '\0') {
		// remember to use equality operator, else the if sttement automatically becomes true if you just use the equality operator =
// easier to use while loop here since we know exactly when the loop should end/don't need to calculate length with a while loop
if (input[i] == x) {
	input[i] = y;
}
i++; //remember to incrmement i! OUTSIDE THE LOOP!!
	
}
}

int findLength(char input[]) {
	int count = 0;
	int i = 0;
	while (input[i] != '\0') {
		count ++;
		i++;
	}
	return count;
}

void reverseString (char input[]) {
	int i,j;
	i=0;
	j=findLength(input)-1;
	
	while(i<j) {
		char temp=input[i];
		input[i] = input[j];
		input[j] = temp;
		i++;
		j--;
		//when i = j, they're at the middle element, which doesn't need to be swapped
	}
	//string is now reversed
}

int main() {
	//you can quantify exactly whats in an array by using {}
	int arr[] = {1,2,3,4,5};
	char arr2[] = {'a','b','c'};
	
	cout << arr[0] <<endl;
	cout << arr << endl;
	cout << arr2 << endl;
	// we get the whole content of the array arr2, but only the address of arr
	//this is because the std::cout operator << is overloaded for const char* in such a way that the string that it points to is printed out. This is not the case for int* arguments.
	// printing the array immediately sends the compiler to arr[0] memory address
	//char data types are used to store a single character
	//however to store a name, you have to create an array of chars
	//when you print arr2, you also print a null char which is appended at the end of your array
	 //this is done automatically by your compiler
	 //printing this array is done by printing each char one at a time, when the compiler reaches the null value, it stops printing
	  
//	char input[100];
	//cin >> input; // dont have to endl a cin
	//cout << input << endl;
	
	//string is an array of characters
	//printing the array causes the compiler to go to input[0] and print each char until reaching the null value at the end
	//null character is '\0'
	//wherever you put the null character will cause the compiler to stop printing at that point
	
    //input[2] = '\0';
	//cout << input;
	
	char length[100];
	//cin >> length;
	//we can use the null value to find the length of a string
	
	// when entering your name, if you put a space, that and anything following will not be counted
    //c++ compiler assumes that whitespace terminates input from that point on
	//can get around this by using getline function
     
     cin.getline(length,100);
	
	//store count as a variable
	int ans = findLength(length);
	cout << ans << endl;

//to reverse a string, you need to swap index values strting from i = 0 and j = length -1
//the end of the string  has the null value so we only go upto length -1, to leave it out
//compiler puts the '\0' on the end automatically
//now do i++ and j--, then swap these values
//once i >j we can stop

cout << "before reverse" << endl;
    cout << length << endl;;
    
    reverseString(length);
    
 cout << "after reversal" << endl;
 cout << length << endl;   

replace(length,'a','x');
cout << length;
}