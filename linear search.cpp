#include <iostream>
using namespace std;

int linearSearch(int arr[], int n, int x) {
	for (int i = 0;i<n;i++) {
		if (arr[i] == x) {
			return i;
		}
	}
    return -1;
}

int main() {
	
	int arr[100];
	int n;
	
	cout << "enter n";
	cin >> n;
	
	for (int i=0;i<n;i++) {
		cin >> arr[i];
	}
   
   // we're going to look for the value of x within arr
    int x = 30;
    
    int index = linearSearch(arr,n,x);
    cout << "Index is: " << index;
}