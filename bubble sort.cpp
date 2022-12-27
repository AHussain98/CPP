#include <iostream>
using namespace std;

//this is sorting values by comparing with the value next to them. If greater then swap.
//this is done pass by pass
//you don't need to compare the last value because this will be sorted on the last pass.

void bubblesort(int arr[], int n) {
for (int j = 0; j<n-1;j++) {
//again limited to n-1 because we're using index values, so they start from 0 and actually end at n-1
// j here is an optimisation, this stops us from considering the values we have already sorted
//j value is increased each pass because we've sorted the last value each time, so it doesn't need consideration at next pass
//n is number of elements, i is the index value here
	
	for (int i = 0; i<n-1-j;i++) {
		if (arr[i] > arr[i+1] ) {
			//swaps are done with the use of a temp variable
			int temp;
			temp = arr[i];
			arr[i] = arr[i+1];
			arr[i+1] = temp;
			
		}
	}
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
	
	bubblesort(arr,n);
		for (int i = 0;i <n;i++) {
		cout << " " << arr[i];
	}
}

