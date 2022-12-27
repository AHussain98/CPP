#include <iostream>
using namespace std;
// include used to include header files, this is a preprocessor directive. 
// it goes preprocessor, them compiled into an executable binary
// then each module linked together via linker
// namespace is a declarative region 

int main() {
int arr[100];
int n;
cout << "Enter the value of n" << endl;
cin >> n;

for (int i = 0; i<n;i++)	 {
cin >> arr[i];	
}
	int max = INT_MIN;
	int min = INT_MAX;
	
	//INT_MIN is an inbuilt, smallest possible integer, useful for these kinds of tasks
    //INT_MAX useful to find the minimum in an array

	for (int i = 0; i < n;i++ ) {
		if (max < arr[i]) {
			max = arr[i];
		}
		if (min > arr[i]) {
			min = arr[i];
		}
	}
	
	cout << max;
	cout << min;
	
}