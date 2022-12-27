#include <iostream>
using namespace std;

bool isprime(int a);
int main() {	
	int i;
	while (i <= 20) {
	cout <<  i << ": "<< isprime(i) << endl;
	i++;
}

}

bool isprime(int a) {
int i = 2;
while (i < a) {
if (a%i == 0) {
return false;
}
i++;
}

return true;
}