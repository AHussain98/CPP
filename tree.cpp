# include <iostream>

// c++ associative containers are implemented using a tree
// this is a data structure in which each element has its own node
// a node has a key for the element and two pointers, left and right
// the positions of elements depends on the relative values of their keys, left points to an element that has a lower key and right points to an element which has a higher key

// inserting an element just involved modifying a pointer
// the main advantage of using a tree data structure is that locating and searching for elements is very fast
// its faster to search a tree than a sequential container because you just need to compare element data and dereference a pointer
//  to add or remove elements, we need to compare the element data, dereference a pointer, compare the element data and assign a pointer
// these operations are very fast, no memory is allocated or released and only one other element is modified, no elements are moved around

// inserting and erasing elements may cause teh tree to become unbalanced, too many elements in one branch of teh tree
// this makes the tree less efficient, we may need to rebalance the tree by choosing a new root and/or moving elements around until the tree is balanced
// balanced trees automatically rebalance themselves when needed, such as red-black trees and avl trees

int main(){



}