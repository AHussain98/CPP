 #include <iostream>
using namespace std;
 #include <vector>


 //a priority queue performs operations on nodes in queue based on thier priority
 // this is implemented using a heap data structure
 // Heaps are a complete binary tree with a particular order property
 //complete binary tree is a tree where each level has the maximum amount of nodes it can have (two children for each node)
 //  Heap order property (for min heap): roots data must always be less than its chidlrens data, applies to every level
//  Max heap order property :  roots data must be larger than its children
//if an inserted node violates the order property, swap that node with its parent, continue up the chain, swapping as you go until it satisfies the order property
// STL priority queue is the implementation of the heap data structure
// A Binary Heap is a Binary Tree with following properties.
//1) It’s a complete tree (All levels are completely filled except possibly the last level and the last level has all keys as left as possible). This property of Binary Heap makes them suitable to be stored in an array.

//2) A Binary Heap is either Min Heap or Max Heap. In a Min Binary Heap, the key at root must be minimum among all keys present in Binary Heap. The same property must be recursively true for all nodes in Binary Tree. Max Binary Heap is similar to MinHeap.

class priorityQueue {
    vector<int> pq; //vector used because we need to store our data

    public:

    bool isEmpty(){

        return pq.size() == 0; //function to check if pq is empty
    }

    int returnSize(){
        return pq.size();
    }

    int minValue(){
        if (isEmpty()){
            return 0;
        }

        //minimum will always be stored at the top of the heap ( for min heap) or at index 0 of vector
        return pq[0];

    }
     //implement the insert function
    void insert(int element){
        pq.push_back(element);
        int childIndex = pq.size() -1; // this is the index in the vector where the newest element would be inserted

       while(childIndex > 0){

        int parentIndex = (childIndex -1) /2; // this is the formula for finding the parent index
        if(pq[parentIndex] > pq[childIndex]){
          int temp = pq[childIndex]; //swap them because the child is smaller than the parent which cant be the case for a min heap, min heap has smallest value at root
          pq[childIndex] = pq[parentIndex];
          pq[parentIndex] = temp;   //set up temp for the next run of the loop, where the new parent is compared with the parent above
        }
        else{
            break;  //as soon as parent index is smaller than child, break the while loop
        }
        childIndex = parentIndex;   //if parent index is smaller, make the swap, then continue to sweep upwards through the heap
    }

     }



    int removeMin(){ //so pop the most valuable node in the priority queue
        int ans = pq[0];    //first value in the vector, root of the heap
        pq[0] = pq[pq.size() - 1];
        pq.pop_back();

        //downward heapify
        int parentIndex = 0;
        int leftChild = (2 * parentIndex) + 1; //get the index of the left and right children of the new root
        int rightChild = (2*parentIndex) + 2;

        while(leftChild < pq.size()){    //wont run as soon as the left child of a node doesnt exist
        int minIndex = parentIndex;
        if( pq[leftChild] < pq[minIndex]){

            minIndex = leftChild; //so for root node and its children, compare the sizes of each
        }
        if ( rightChild<pq.size() && pq[rightChild] < pq[minIndex]){ //check that right child exists, if its index is bigger than the size of the vector, it cant exist
            minIndex = rightChild;
        }

        if (minIndex == parentIndex){
            //this means both children are larger than their parent as they should be, heapify completed
            break;
        }
         //no break, do the swap
        int temp = pq[minIndex];
        pq[minIndex] = pq[parentIndex];
        pq[parentIndex] = temp;

        parentIndex = minIndex;  //new parent becomes the one of the child nodes that was swapped
        leftChild = (2*parentIndex) + 1;  //initialise the new children
        rightChild = (2*parentIndex) + 2;

     }
     return ans;
     }

};



 int main(){

 priorityQueue p;
 p.insert(19);
 p.insert(100);
 p.insert(40);
 p.insert(5);
 p.insert(3);
 p.insert(1);
 p.insert(2);

 cout << p.minValue() << endl;
 cout << p.returnSize() << endl;
 cout << p.isEmpty() << endl;

 while(!p.isEmpty()) { //so while p is not empty
      cout << p.removeMin() << " "; //so remove the highest priority node as long as the vector is not empty
 }


 }