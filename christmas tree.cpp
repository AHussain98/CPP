#include<iostream>
using namespace std;

int main(){
	
	int n;
	cin >> n;
	
	int i = 1;
	
	while (i<=n) {
		int j = 1;
		while (j <= n-i) {
			cout << " ";
			j++;
		}
		
		int k = 1;
		while (k <= 2*i -1) {
			cout << "*";
			k++;
		}
		
		
		
		i++;
		cout << endl;
	}
	
	
	
	
	return 0;
}