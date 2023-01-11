#include <iostream>
using namespace std;
#include <vector>  //this is how we'll use the vector built in

//trees are another type of data structure
//a tree has nodes which link to a n number of nodes, trees start from a root node
//in a linked list, a node only has one address, to the next node
//however, in a tree, a node must have data, and then n addresses of other nodes it is the parent node of
//so nodes can point to any node that comes after it in the tree, but not any nodes further down than that
//leaf nodes are nodes without children

//vectors are dynamic arrays, we use these to create arrays without specifying the size. It handles the size at compile time
//we can use vectors to create children arrays for parent nodes, we can store the childrens addresses in the vectors

int main(){
          vector<int> v1;
          v1.push_back(10);   //this is how we add elements into a vector
         cout << v1.capacity() << endl;
          v1.push_back(20);
          cout << v1.size() << endl;
          v1.push_back(30);
          cout << v1.size() << endl;  //vectors have a built in size function
         cout << v1.capacity() << endl;
          v1.push_back(40);
          cout << v1.size() << endl;
         cout << v1.capacity() << endl; //as soon as size catches up with capacity, capacity doubles automatically

         //this is how we access the elements
         for (int i = 0; i < v1.size();i++){
             cout << v1[i] << " "; // access vector elements just like an array
         }

         //to delete the last element entered into the vector, you use the pop back fucntion
         v1.pop_back();
         cout << endl;
         for (int i = 0; i < v1.size();i++){
             cout << v1[i] << " "; // access vector elements just like an array
         }
         cout << endl;
         cout << "Popped!" << endl;

         //but what if we want to access the element at a specific position? use the at fucntion

         cout << v1.at(2) << endl; //show me the value at index 2

}