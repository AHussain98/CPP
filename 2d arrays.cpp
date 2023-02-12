#include <iostream>
// 2d array is stored as a single contigous memory block
//

int main(){

    // example of a 2d array on the heap:
    // to iterate over a 2d array, we use nested loops
 int rows = 2;
 int columns = 4;
 int ** array = new int * [rows];
 for (int i = 0; i < rows; i++){
          array[i] = new int [columns];
     for (int j = 0; j < columns; j++){
              std::cin >> array[i][j];
     }
 }

 // we can also initialse a 2d array on the stack
 int arr[2][4] {1,2,3,4,5,6,7,8}; // doing this implicitly creates pointers in the first array leading to arrays of the second

 int arr2[2][4] {
 {1,2,3,4},{5,6,7,8} // in one long bracket
 };

 std::cout << arr2[0][3];

 // its better to create one longer array rather than an array pointing to arrays, because dereferencing a pointer is more computationally demanding than just
 //multiplying to get the element we want

 int arr3[] {1,2,3,4,5,6,7,8}; //delcared as a single array
 for (int i = 0; i < rows; i++){
     for (int j = 0; j < columns; j++){
         std::cout << arr3[i*columns + j]; // get every value faster
     }
 }

}