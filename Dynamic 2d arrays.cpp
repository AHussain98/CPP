#include <iostream>
using namespace std;

int main() {
	
	int m, n;
	cout << "enter the values for rows and columns";
	cin >> m;
	cin >> n;
	int **p = new int * [m]; //we've created an array for each row, each entry in the p array will contain a pointer to the address of an array for the rows
	//so we have a pointer to an array of pointers on the stack, **p
	//number of columns is n, number of rows is m
	// this is a size array, which is populated in the array below
	
	for (int i = 0; i < m; i++) {
		p[i] = new int[n]; //for each row, I'm trying to create a new array of size column
		// image you want an array with 3 rows and 4 columns
		// so n is 4, above an array is created with size 4, so each of p[0], [1], p[2], p[3] will point to another array that is 4 columns long
		//so for each row, create the size of the array along it
		// so p[0][0] is saying for the first entry on the row array, go to the first column
        // if we wanted the sie of the row to increase each time, we could replace n with i+1
	}
	

for (int i = 0; i<m; i++) {
	for (int j = 0;j<n;j++) { // and if we wanted the size of the row to increase each time, we would replace n with i + 1
		cin >> p[i][j] ;
	}
// now we can access each value in here
}

for (int i = 0; i<m; i++) {
	for (int j = 0;j<n;j++) { // and if we wanted the size of the row to increase each time, we would replace n with i + 1
		cout << p[i][j] ;
	}
cout << endl;
}
}