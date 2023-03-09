# include <iostream>
# include <deque>

// std::deque implements a double-ended queue, this is similar to a vector but elements can also be added efficiently at the front
// these are implemented as a two dimensional array, so an array whose elements are arrays
// vector has one memory block which stores all the elements
// list has one memory block per elements
// deque has multiple memory blocks which each store several elements

//  std::deque stores its elements over several blocks of memory, iterating from the first element of the first block to the last element of the last block will return all elements in order
// deque has a similar interface to std::vector
// deque also has a push_front() member function, this inserts an element before the frist element
// if there is not wnough room to store a new element, the deque will allocate another memory block and store it there
// the existing elements remain where the are
// this is different from std::vector, where the memory block is reallocated and the elements are copied into the new block




int main(){

std::deque<int> test {1,2,3,4};

test.push_back(5);

for (auto i : test){
    std::cout << i;
}

test.push_front(0); // we can also quickly add to the front, unlike a vector

std::cout << std::endl;

for (auto i : test){
    std::cout << i;
}

// sequential containers are arrays, vectors and deques
// compiler writers know that most people prefer vectors, so they optimise compilers for using vectors rather than deques or arrays
// deque is slightly slower than vector for most operations, however its faster than vector for adding and removing elements at the fron of teh container
// list is much slower than vector and deque for most operations, and uses more memory due to adding and removing pointers
// however list is much faster at adding and removing elements (if you already have an iterator to the element you want), but only if this does not involve searching
// vector should be the default choice, and modern hardware is optimised for accessing contigous blocks of memory, so vectors are preferable, this is why lists and deques are not prefereable


}