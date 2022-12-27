#include<iostream>
using namespace std;

int num = 1001;
int check = num;
int ans = 0;

int main() {
	
	while (num > 0) {
		
		ans = ans*10 + num%10;
		num /= 10;
	}
	
	cout << ans << endl;

if (ans == check) {
	cout << "pallindrome!" <<endl;
}
}