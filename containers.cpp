# include <iostream>
# include <array>

// strings and vectors are sequential containers, the data is stored in an order which is determined by the program
// the order of the data does not depend on its value, the data will remain in the same position unles the program performs some action which changes them
// sequential containers are useful for storing data in an order we can choose, we can typically access dataa by its position in the sequential container, such as string or vector indexing

// in an associative container, the order depends on the data
// each element has a key which identifies it, the key is used to look up the element in the container
// the key also determines the position of the element
// associative containers are useful for storing information which we want to be able to search
// c++ provides two types of associative container, a set and map
// a set is an unstructured collection of elements, an element is a single data item consisting of a key, the key is used to check if the data item is present in the collection
// a map is similar to a directory or hash map in other languages, an element consists of a pair of data items, a key and a value
// the key is used to search for an element and look up its value
// associative containers do not support push_back and push_front, the position of an element is determined by its key
// we can instead use insert() and erase() to add and remove elements, we can use iterators to loop over the container
// they also have member functions which are similar to generic algorithms

// the standard lbrary also defines container adaptors. these are data structures (stacks and queues) which are implemnted using sequential containers
// data is stored in these containers in an order which depends on when data was added


int main(){
// c++ has built in arrays, these are faster than vectors and directly compatible with c code

//int arr[] = {1,2,3,4,5};
//std::cout << arr[0] << std::endl;
// inbuilt arrays such as these have serius disadvantages, there is no direct way to find the number of elements
// if you use an array on the heap, you must manage its memory yourself
// the array identifier is silently converted to a pointer when passed as an argument or returned from a function
// arrays cannot be assigned to each other and passing arrays to and from functions requires a size argument

// modern c++ provides std::array which overcomes the above
// it is a templated type, the parameters are the element type and number of elements
// the number of elements is part of the type of the object
// trying to use an array with the wrong number of elements gives a compiler error
// it has a similar interface to other stl containers, while retaining the speed of built in arrays
//  does not automatically decay to a pointer, retains information about its size and supports iterators

// std::array can only be created on the stack (use a vector if you want one on the heap), the number of elements must be known at compile time
// a contigous block of memory is allocated to store the elements
// unlike other containers (default constructor for string and vector is just empty), the default constructor creates a fully-sized object, the elements are default initialised

std::array<int,5> arrNew;
arrNew[2] = 17; // we can reassign

for (int i = 0; i < arrNew.size(); ++i ){
    arrNew[i] = 10;
}


for (auto i : arrNew){
    std::cout << i << " ";
}

for (auto& i : arrNew){  // got to pass by reference to change the elements, otehrwise just making a copy, which is fine in the above case since we're just viewing
    i = 100;
}

std::cout << std::endl;

for (auto i : arrNew){
    std::cout << i << " ";
}

}