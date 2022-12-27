#include <iostream>
using namespace std;
int main() {
	int arr[100][100];
	//this is a instantiated 2 dimensional array
	//right now we're wasting space by making the array so large
	//but we'll consider that later when dynamically adjusting memory allocation
	int m;
	int n;
	cout << "enter the rows" << endl;
	//user then gives num of rows
	cin >> m;
	cout << "enter the columns" << endl;
	cin >> n;
	
	//first array is row, second is column
	
	
	for(int i = 0; i<n;i++) {
		
		for(int j = 0;j<m;j++) {
			cin >> arr[i][j];
		}
	}
// now we've instantiated the array and given it a size
//we've now created the array

//printing row wise
for(int i = 0; i<m;i++) {
		
		for(int j = 0;j<n;j++) {
			cout << arr[i][j];
		}
	cout << endl;
	}
	
    cout << endl;
    
    //sum of the array
    
    int sum = 0;
    for(int i=0;i<m;i++) {
    	
    	for(int j=0;j<n;j++) {
    		sum += arr[i][j];
		}
	}
    
    cout << "sum is " << sum << endl;
    
    cout << endl;
    
    //finding sum of columns
    int colsum;
    
    	for(int j=0;j<n;j++) {
    		
    		colsum = 0;
    		for (int i=0;i<m;i++) {
			
    		colsum += arr[i][j];
		}
		int num = 0;
			 cout << "sum of column " << num <<" is " << colsum << endl;
num++;
		
		}
    
    cout << endl;
    
    //finding the maximum
int maximum = arr[0][0];
for (int i=0;i<m;i++) {
    	
    	for(int j=0;j<n;j++) {
    		if (arr[i][j] > maximum) {
    			maximum = arr[i][j];
			};
		}
	}   
    
    cout << "max is " << maximum << endl;
    
    cout << endl;
    
    //printing column wise
    for(int i = 0; i<m;i++) {
		
		for(int j = 0;j<n;j++) {
			cout << arr[j][i];
		}
	cout << endl;
	}
    

}
