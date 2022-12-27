#include <iostream>
using namespace std;

void insertionSort(int arr[], int n) {
	for (int i = 1; i<n;i++) {
		// i is the second index initially
		int current = arr[i];
		//j is the index ofthe first value
		//j needs to be reset every time, as this is based on i and it needs to be accessed outside of the for loop, so it is declared here
		int j;
		for (j=i-1;j>=0;j--) {
			if (arr[j] > current) {
				arr[j+1] = arr[j];
				
			}
			//include else statement in case you don't need to swap the index values
			else {break;
			}
		}
		//since j has now beocme -1, this has broken the loop
		//therefore replace the value at 0 index with what was in current, they have now swapped and been sorted
	arr[j+1] = current;
	}
}

int main() {
	
	int arr[100];
	int n;
	cout << "enter n"<< endl;
	cin >> n;
	cout << "enter the values of the array" << endl;
	for (int i = 0; i<n;i++) {
		cin >> arr[i];
	}
	
	insertionSort(arr,n);
	
	for (int i = 0; i<n;i++) {
		cout << arr[i];
	}
}