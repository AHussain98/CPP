#include <iostream>
using namespace std;

// remember that == is equality operator!!!
// using = in the if statement would just make arr[i] the same as arr[j]

int findDuplicate(int arr[], int n) {
	for(int i =0;i<n;i++) {
		for (int j=i+1;j<n;j++) {
			if (arr[i] == arr[j]) {
			return arr[i];}
		}
	}
    return -1;
}

int main() {
	
	int arr[] = {1,2,3,4,5,6,3,7,8,9,10};
	int n = 11;
	int ans = findDuplicate(arr,n);
	cout << "Duplicate is " << ans;
}