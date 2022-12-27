#include <iostream>
#include <cstring>
using namespace std;

void printPrefix(char input[]) {
	for(int i=0;input[i] != '\0';i++) 
	
	for(int j = 0; j <=i; j++) {
		cout << input[j];
	}
cout << endl; //start a new line
}
 // '\0' is not required if you are using it as character array. But if you use character array as string, you need to put '\0'. There is no separate string type in C
int main() {
	//can create strings by defining a char array and just typing it out in double quotes
char input[100] = "abcd";
//	cout << "before copying" << endl;
//	cout << input <<endl;
	char input2[100]="cdef";
	//cout << input2 << endl;
//	strcpy(input,input2);
//	cout << "after copying" << endl;
//	cout << input <<endl;
//	cout << input2 << endl;
	
	//cstring is an inbuilt, allows us to use the strcpy function to copy one string to another
	
//	if(strcmp(input,input2) == 0) {
		
	//	cout << "Same!";
//	}
	
	//strcmp is another function, it's used for comparison, if the two strings are the came, the value of strcmp is 0
strncpy(input, input2, 3);
//strncpy lets us specify how many characters to take from input 2 and copy them into input
cout << input;

}


//char str1[]    = "my string";
//char str2[64]  = "my string";
//char str3[]    = {'m', 'y', ' ', 's', 't', 'r', 'i', 'n', 'g', '\0'};
//char str4[64]  = {'m', 'y', ' ', 's', 't', 'r', 'i', 'n', 'g' };

//All these arrays have the same string "my string". In str1, str2, and str4, the '\0' character is added automatically, but in str3, you need to explicitly add the '\0' character.

//(When the size of an array is explicitly declared, and there are fewer items in the initializer list than the size of the array, the rest of the array is initialized with however many zeros it takes to fill it 