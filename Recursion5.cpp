#include <iostream>
using namespace std;


//sum of array
int sumArray(int arr[], int n) { // n is number of array elements
	if (n == 1) { //when n == 1, there is only one elemnent in the array, so return its value
		return arr[0];
	}
	int smallOutput = sumArray(arr + 1, n -1); // start of array moves along by one, using arr\=1 means arr[0] then becomes what arr[1] was before
	int sum = arr[0]+ smallOutput; // add the value of the index you're at right now
	return sum;
	
}






// the process is to find the base case, then store the result of the recursive function in a variable, before generating the value to be passed


//finding a number
bool findNum(int arr[], int n, int y) {
	if (n == 0) { // we need to go beyond the end of the array as we need to search and examine all of it, hence implement base case for when n==0
	return false; // false because if we get to this point then the number doesn't appear, hence fail
		}	
	if (arr[0] == y) { // if present at this reduced array, then return true, and this findNum becomes true
		return true; // if you find your number, you can just return true
	}			
	bool check = findNum(arr + 1, n - 1, y); // if the function gets to this point, it means the vallue wasn't at this index, so we take the check value of the next index on as our bool
	if (check) {
		return true; // check becomes true as soon as you find it
	}
	else {return false;
	}
}


//first index of a number
int firstIndex(int arr[], int n, int x) {
	if (n == 0) {
		return -1; // base case, we have been through every element and the number hasn't appeared, therefore its not in there and we can return -1 to show so
	  }
    if (arr[0] == x) {
    	return 0; // if the number we're searching for is tha the current index, then return this index
	}
   int ans = firstIndex(arr+1,n-1,x); // for the next index in the srray, that index becomes arr[0], the array is shortened so n-1, store this recursive function in the variable ans
    if (ans == -1) {
    	return -1; // to carry the ans back up the chain when it gets to the end and the number isnt there ( in the case that num isnt in array)
	} // remmeber not to use = in if statement, equality operator ==!!!!!
    else { return ans+1; // add one to answer because the arrays are shortened by one each time, so if they find the value, it is at index 0 from where the shortened array starts. We see the full array however so we add in 1 to compensate
	}


}

//last index of a number
int lastIndex(int arr[], int n, int z) {
	if(n==0) { 
		return -1; // in this case, the function WILL get all the way to the end and then return -1
	}
	int ans = lastIndex(arr+1,n-1,z); // call the function with reduced array and store retunred value in this variable, the call stack function chain begins in reverse from this point, evaluating if the value being sreached for is at their location by checking arr[0]
	if(ans == -1) {
		if (arr[0] == z) { // return 0 when the value is found, since we're going all the way to the end, returning -1 and then coming back, the latest occurence of the value will have its index returned
			return 0;
		}
	     else {
	     	return -1; // this prevents duplicate values of the value we're after being taken as the last index 
		 }
	   
	}  
	 else {
	 }
	 return ans+1; // if ans is not -1, then the value has been found, so just add one to ans and pass it along
	    
}



int main() {
	int arr[] = {1,3,2,8,3};
	int n = 5;
	int sum = sumArray(arr,n);
	cout << sum << endl;


int y = 7;
bool ans = findNum(arr,n,y);
if (ans) {
	cout << "value is present" << endl;
	}else {
	cout << "value is not present" << endl;
	}

int x = 8;
int index = firstIndex( arr, n, x);
	cout << "Index is: " << index << endl;
	
int z = 8;
int lIndex = lastIndex(arr,n,z);
cout << "Index is: " << lIndex << endl;
 
}










