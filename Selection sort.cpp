#include <iostream>
using namespace std;

//round 1: starting at i=0, get the minimum value in the 0 index of the array, swap these values
//round 2: starting from cell 2, search for the second smallest value and put that in index 1, swap the values
//round 3: from the third cell, search for the smallest remaining value from here, and swap it into this cell
// you increase the starting index every time, continue until you get to the last cell, the sort is now complete

void selectionSort(int arr[], int n) {
// n is the size of the array, since we're operating on the indexes and we don't operate on the last cell since they'll be sorted by then, i<n-1
for (int i=0;i<n-1;i++) {
	//in the beggining, we can assume the minimum index is the avlue i
	//if we find a value lower than this, we update the min index value
	//so minIndex is beggining as 0 index value
	int minIndex = i;
	for (int j =i;j<n;j++) {
		//now travel the whole length of the array, starting from what i starts from
		//replace minIndex with the smallest value you find
		//so j is starting from 0, as in arr[0] and working its way across to find something smaller than itself
		if (arr[j] < arr[minIndex]) {
			minIndex = j;
		}
	}
//now we have a min index value, we actually need to make the swap
     int temp = arr[i];
     arr[i] = arr[minIndex];
     arr[minIndex] = temp;
     //round 1 complete, now i++, we do the same for the next index in the array

}	

	
}


int main() {
	
	int arr[100];
	int n;
	cout << "enter n" << endl;
	cin >> n;
	
	for (int i = 0;i <n;i++) {
		cin >> arr[i];
	}
	//remember to call the function and actually print it to the screen
	selectionSort(arr,n);
    //because we passed the address of the array, the changes are carried over to the main function
    for (int i = 0;i <n;i++) {
		cout << " " << arr[i];
	}
}