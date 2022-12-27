#include<iostream>
using namespace std;

int main(){
	
int n;
cout << "enter n" << endl;
cin >> n;
int value = 1;

int i = 1;
while (i<=n) {
	int j = 1;
	while (j<=n-i) {
		cout << " ";
		j = j + 1;
	}

int k = 1;
while(k<=i) {
	cout << value;
	k++;
	value = value + 1;
}

i=i+1;
cout << endl;
}
	

	return 0;
}