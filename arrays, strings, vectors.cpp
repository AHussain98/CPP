# include <iostream>
# include <string>
# include <vector>
// array is a block of contigous memory, can only be allocated on the programs stack of the number of elemenst is fixed and known at compile time



int main(){

int arr[10]; //initalised an array on the stack, full of ints and size 10, a constant fixed number
int num {10};
int arr2[num]; //still works as num has a value of 10 and this is copied into the arrays memory as its size

int unknown;
int arr3[unknown]; // you never used to be allowed to do this, but now can
// int arr4[]; doesnt work because it hasnt been initialsed. you can do this with the vector below, or with a dynamic array

// the array must be declared on the heap if we dont know the number of elements at compile time, or we want to vary the number of elements
// once a stack array is initialised, thats it, it cant change size, heap arrays can

std::string name {"Asad"}; //std::string objects behave like a dynamic array but are used like local variables
// the abov/e is a string allocated on the heap in its constructor and automatically calls the destructor and releases memory when it goes out of scope
// std::string also allows us to dynamically change the size of the string, see below
name = "Asad Hussain"; // remember to only use the {} when initialising a variable
 // you need to do std::string, we're getting them from stl, not part of the core language
// std::string is a class, it has a member which is a dynamic array, it also has a member that stores the number of elements in the array
std::cout << name[0] << std::endl; //because strings are an array of chars, this is allowed, [] subscript is supported
// the array has a null character at the end \0 at the end, compiler knows to stop when it gets there
std::cout << name.size() << std::endl;

std::vector<int> v;
 // vetcors are similar to strings but they can store data of any single type
// the type of data is a parameter of the class, see vector<int> above, you must specifiy
// the std::vector class has a member that is a dynamic array
// a vector is also a block of contigous memory

v = {1,2,3,4,5}; // you can only put {} right after the name when you initialise, else you have to use =
std::cout << v.size() << std::endl;
std::cout << v[3]; //subscript [] notation also allowed
v.push_back(21); //push back pushed an element onto the end of the vector

// a vector is based off of a dynamic array, but it's a standardised class, you don't need to use the delete keyword, or the new keyword
// or create any functions for it unlike ith a dynamic array, its all handled for you, you can grow or shrink your vector with build in functions

}