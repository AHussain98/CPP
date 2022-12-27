#include <iostream>
using namespace std;

// array has to be sorted to use binary search 
//linear search can be used on an unsorted array
//for binary search, the sorted array gets split in half each time
//you start by searchung for the particular elemnt in the middle of the array, then search the appropriate side of the array
//the element you're searching for will be on the remaining side of the array
//then repeat those two steps until you find the element 

//middle index found by adding starting index and end index then dividing by 2
//then evaluate the number at that index
//if the target is smaller, new end index is mid index - 1
//if target is larger than midpoint, new start index is midpoint +1
//only one elemnt left when the start index and mid index are the same;
//if the value is the same as the one being searched for, then return the index position
//else the value is not in the array, when start index becomes > end, then we can confirm element doesn't exist
//start is always less or eqyal to yout end index, as soon as its more, the value isn't in the array

int binarySearch(int arr[],int n, int x) {
	//x is the value we're searching for
	int start = 0;
	int end = n-1;
	while (start <= end) {
		int mid = (start+end)/2;
// has to be == because we're comparing, not assigning. using = eould change the value of x and therefore end the loop
		if (arr[mid] == x) {
			return mid;
		}
		else if (arr[mid] < x) {
			 start = mid + 1;
		}
		else { end = mid -1;
		}
	}
// if the program reaches here, then the value is not in the loop, therefore return -1	
return -1
}

int main() {
	
	int arr[100];
	int n;
	cout << "enter n" << endl
	cin >> n;
	
	for (int i = 0;i <n;i++) {
		cin >> arr[i];
	}
	int x = 11;
	//remember you actually have to print out the answer

cout << binarySearch(arr,n,x);	
}

