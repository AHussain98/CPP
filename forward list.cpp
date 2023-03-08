# include <iostream>
# include <forward_list>

// unlike a string, array or vector, a list does not use a single block of memory to store all its elements
// in a list, each element has its own memory allocation, called a node
// each node contains the element value and a pointer, the pointer stores the address to the next element
// the last node has an invalid link pointer, this signifies it does not have a next node

// to iterate through a list, we start at the first node, we get its link pointer and go to that addresss
// we then use that nodes link pointer to go to the third node etc...
// we stop when we get to a node which has an invalid link pointer

// this data structure is known as a forward list, or a singly linked list, each node has a single link and we can iterate forwards through the list by following the links
// each node has a single link, we can iterate forwards through the list by following the links, going backwards through the list is more difficult
// the c++ standard library provides std::forward_list which implemnets this data structure

// to add an element at the back of a linked list, create a node for it and make the last nodes link point to it, the added node is now the last node
// to insert a node in the middle of a linked list, make the link from the node before point to the new node, then make the new nodes link point to the node after, the other elements are left untouched
// to remove an element from a linked list, make the previous node link point to the next node, and then destroy the node, again the other elements are left untouched

// usually, sequential containers have an insert() and erase() member function, these add or remove an element before a given location, this requires that the container supports reverse iterators
// std::forward_list only supports forward iterators, to add or remove an element, use insert_after() and erase_after(), these will add or remove an element after a given location

int main(){

std::forward_list<int> list {1,2,3}; // created a list object

for (auto i : list){
    std::cout << i << " ";
}
auto second = list.begin(); // create an iterator to the first element
advance(second,1);  // advance the iterator to the second element

list.insert_after(second,55); // insert an element after the second one

std::cout << std::endl;

for (auto i : list){
    std::cout << i << " ";
}

list.erase_after(second); // now remove it

std::cout << std::endl;

for (auto i : list){
    std::cout << i << " ";
}


}