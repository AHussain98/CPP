#include <iostream>
using namespace std;

//lets try doing an inplace heap sort
 //imagine we get given an array, we need to sort the values and insert them in a specific array
 // arrays are less costly than vectors for this because an array uses only as much memory as its elements. A vector uses some memory to store some housekeeping information like the length and location of the data.
 // An in-place algorithm is an algorithm that does not need an extra space and produces an output in the same memory that contains the data by transforming the input ‘in-place’.

void inplaceSort(int * arr, int n){   //recieves pointer to array and a int value
    for(int i = 1; i<n;i++){ //for loop runs this through for every index
        //start from one as we assume the value at index 0 is sorted
        int childIndex = i; // this is the index in the vector where the newest element would be inserted

       while(childIndex > 0){

        int parentIndex = (childIndex -1) /2; // this is the formula for finding the parent index
        if(arr[parentIndex] > arr[childIndex]){
          int temp = arr[childIndex]; //swap them because the child is smaller than the parent which cant be the case for a min heap, min heap has smallest value at root
          arr[childIndex] = arr[parentIndex];
          arr[parentIndex] = temp;   //set up temp for the next run of the loop, where the new parent is compared with the parent above
        }
        else{
            break;  //as soon as parent index is smaller than child, break the while loop
        }
        childIndex = parentIndex;
    }

}       //so at this point, we've got our heap, we need to heapify it now, array at this point is [0,1,8,5,4]

int size = n;

while(size > 1){
    int ans = arr[0];    //ans is storing 0
        arr[0] = arr[size - 1];
        arr[size -1] = ans;
        size--; //so now only the unsorted part of the array will be considered

        //downward heapify
        int parentIndex = 0;
        int leftChild = (2 * parentIndex) + 1; //get the index of the left and right children of the new root
        int rightChild = (2*parentIndex) + 2;

        while(leftChild < size){    //wont run as soon as the left child of a node doesnt exist
        int minIndex = parentIndex;
        if( arr[leftChild] < arr[minIndex]){

            minIndex = leftChild; //so for root node and its children, compare the sizes of each
        }
        if ( rightChild<size && arr[rightChild] < arr[minIndex]){ //check that right child exists, if its index is bigger than the size of the vector, it cant exist
            minIndex = rightChild;
        }

        if (minIndex == parentIndex){
            //this means both children are larger than their parent as they should be, heapify completed
            break;
        }
         //no break, do the swap
        int temp = arr[minIndex];
        arr[minIndex] = arr[parentIndex];
        arr[parentIndex] = temp;

        parentIndex = minIndex;  //new parent becomes the one of the child nodes that was swapped
        leftChild = (2*parentIndex) + 1;  //initialise the new children
        rightChild = (2*parentIndex) + 2;

     }
}


 }


//the above is inplace because we've only made changes within the arr array itself

int main(){

  int arr[] = {4,0,8,5,1};
  inplaceSort(arr,5);

  for (int i = 0; i<5; i++){
      cout << arr[i] << endl;
  }

  //since we didnt use any extra space, our space complexity is O(1)

}