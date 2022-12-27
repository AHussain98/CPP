#include<iostream>
using namespace std;

//checking an array is sorted using recursion
bool sortedArray(int arr[], int n) { // n is size of array, you are passing the address of arr to the fucntion
 if (n == 1 || n == 0) {
 return true;	        // as before, start with base case, the array is sorted is its empty or there's only 1 element in it
	}
bool smallAns = sortedArray(arr + 1, n -1);// arr + 1 means the address of the next int in the array, so the new array you pass to the function here is one smaller, and n has been reduced by 1 aswell
 if (!smallAns){ // means not true
 	return false; // smallans will be false if one of the members in the fucntion chain has returned false
 }

if (arr[0] < arr[1]) { // arr of 0 is the new number that makes the array new, the array has been cut down by one each recursive call until reaching base case, then steadily built back up
	return true;
}
else {
return false; }  //if this occurs, then smallAns will become false and the false chain will permeate throughout the call stack back to the main function
}

// we can do the sorting another way, to reduce the number of recursive calls and save memory
bool sortedArrayOptimised(int arr[], int n) {
	if (n == 0 || n == 1) {
		return true;
	}
	
	if (arr[0] < arr[1]) { // from here, we can return false immediately, rather than travelling along he recursive chain unneccessarily
		return false;
	}
   
   bool smallAns2= sortedArrayOptimised(arr+1,n-1);
 if (!smallAns2){  
 	return false; 
 }

if (arr[0] < arr[1]) { 
	return true;

}
}


int main() {
	int arr[] = {1,2,3,4,5};
	bool ans = sortedArray(arr,5);
	
	if (ans) {
		cout << "Array is sorted" << endl;
	}
	else { cout << "Array is not sorted" << endl;
	}
	
	int arr2[] = {6,1,2,4,90};
	
	bool ansopt = sortedArrayOptimised(arr2,5);
		if (ansopt){
		
		cout << "Array is sorted" << endl;
	}
	else { cout << "Array is not sorted" << endl;
	}
}