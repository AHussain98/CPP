#include <iostream>
using namespace std;

int substring(string s, string output[]) {// string we want to split is s, output is an empty array for storing our answer values
	if (s.size() == 0) {
		output[0] = ""; // when string is empty, the output value is empty
		return 1;
	}
	string smallSubstring = s.substr(1); // substr(1) means from index 1 to end, s.substr(1) is changing abc so it becomes bc, tne so it becomes c
	int ans = substring(smallSubstring,output); // when the size of the string is 0 (when we go beyond c), the value of ans becomes 1, as one is retuned in our base case
	for (int i = 0;i<ans;i++) {
		output[i + ans] = s[0] + output[i];
	}
return 2*ans;
}

//incase you don't want to store the values and just want to output them, we can do this
void printSubstring(string s, string output) {
	if (s.size() == 0) { // basecase, we initqally check abc and since its not == 0, we move on
		cout << output << endl;
     return ;	//without a return statement, the function will simply keep on calling forever
	}
    printSubstring(s.substr(1), output); // call the function, start from the beggining with s = abc, s = bc, then again with s = c, then again with an empty string 
    printSubstring(s.substr(1), output + s[0]); // nothing is beyond c, it is empty from there so making output +s[0] means c becomes output and gets printed
// then we come back to line 23 for s = bc, forst call has been done and returned so go to line 24
}


int main() {
	
	string s1 = "asad"; // you can define a strinf like this
	cout << s1 << endl;
    
    cout << s1.size() << endl; // you can use the size function to find the length of a string
    
    string s2 = " hussain";
    
    string s3 = s1 + s2; // you can concatenate strings by adding them
    cout << s3 << endl;
     
    cout << s3.find("ss") << endl; // find function gives the index of the first char in the string you pass it 
    
    s1[0] = 'x'; //you can edit specific index of string by reassigning
    cout << s1 << endl;

    // you can print specific subsections o fstrings by using the substr function
    
    cout << s3.substr(2,3); // (start from, continue for)

    string *s4 = new string; // stack pointer to a string on the heap, string created dynamically
    cout << s4 << endl; // address being pointed to
	*s4 = "asad hussain";
	cout << *s4 << endl;   // value at pointed address

// when taking an input for a string, using cin will only allow one value ot be entered
//when a space is encoutntered using cin, it ignores everything after it
//this can be avoided using the getline function

string s5; 
getline(cin,s5);
cout << s5 << endl;

string s6 = "abc";
string *output = new string[100];
int ans = substring(s6,output);
for (int i=0;i<ans;i++) {

cout << output[i] << " ";
}

string s7 = "abc";
string output1 = "";
printSubstring(s7,output1);


}