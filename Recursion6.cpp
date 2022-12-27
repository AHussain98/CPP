#include<iostream>
using namespace std;

//if you store an array of strings, internally, they get stored as an array like so: [a,s,a,d,\0]
// \0 is the null character that terminates the end of a char array
//for recursion, we can use the null character as our base case
//remember chars are in single quotes

int lengthString(char str[]) {
	if (str[0] == '\0') { // if the current array index has a value of the null char, retrun 0, end the function
	return 0; // base case
	}
	
	int ans = lengthString(str + 1); // so if the current char is not null, the recursive functionis called and the chain continues with a smaller array
		return ans + 1; // if the value is not the null char, then you havent reached the end of the string, therefore add 1
}

//removing certain char from string, doesn't need to return anything, just needs to remove those chars so void
void removeFrom(char str[]) {
	if (str[0] == '\0') {
		return; // if you reach the end, don't do anything, just return
	}
	if (str[0] != 'x') { // in this case, we're looking for x, if the value at out current index is not x, then carry on
		removeFrom(str + 1);
	}
	else {
	 // if it is equal to x, you need to shift all the elements to reassign the value at that index
		int i; // define i outside loop because we want to use it outside
		for (i = 1; str[i] != '\0'; i++) { // as long as the char is not null
			str[i-1] = str[i]; // all elements shifted to the left, the one at str[0] which is x if teh function reachs this point, gets replaced by the next value at index 1
		}
         str[i-1] ='\0';	// at end of loop, index i is where '\0' is, and we need to move the null char across aswell, so this statement at the end of the lop accomplishes that
          removeFrom(str); // we need it to point to str, not str + 1 because there's a chance that an x is now at the 0 index	
	}
	
}


int main() {
	char str[100];
	cout << "enter the string" <<endl;
	cin >> str; //you can do this for a char array
	
	int ans = lengthString(str);
	cout << ans << endl;

    removeFrom(str);
    cout << str << endl;

}