#include <iostream>
using namespace std;

void reverse(int a[], int n) {
	int i, j;
	i=0;
// initially, i is 0 and j must be n-1 to be at the end of the array
	j=n-1;
	
	while (i < j) {
		int temp = a[i];
		a[i] = a[j];
		a[j] = temp;
		i++;
		j--;
	}
	for (int k = 0;k<n;k++) {
		cout << a[k];
//the array changes are going to be carried over into the main code, because we have passed the array by reference	
}
}

int main() {
	int a[100];
	int n;
	cout << "Enter n" << endl;
	cin >> n;
	
		for (int i = 0;i<n;i++) {
		cin >> a[i];
}
	reverse(a,n);
	
	//we can see the changes have been reflected as a is the address of the array
	for (int k = 0;k<n;k++) {
		cout << a[k];
}
}
	
