#include <iostream>
#include <vector>
#include <string>

// we can perform similar arithmetic on iterators as we can on pointers

int main(){

std::string name {"Asad"};

for (auto it = begin(name); it != end(name); it++){  // standard loop for iterator
    std::cout << *it;
}

std::cout << '\n'; // better than std::cout << std::endl which flushes the output buffer, no reason to do this here

for(auto it = begin(name) +1; it != end(name) -1; it++){ // end(name) returns an iterator to the element after last, so -1 is the last element, so our condition here is while it does not point to the last element
    std::cout << *it;    //  now we only print the middle two characters
}

// we can get the number of elements by doing end(name) - begin(name)
// therefore we cna get the middle element by doing begin(name) + (end(name) - begin(name))/2

// next() takes an iterator and returns the following iterator
// prev() takes an iterator and returns the previous iterator

// distance() returns the number of steps needed to go from its first argument to its second
// advance() moves an iterator by its second argument

std::cout << '\n';

for (auto it = next(begin(name)); it != prev(end(name)); it++){ // always better to have teh initaliser be defined in the loop rather than outside, when there are multiple loops in the same scope, this will help avoid potential errors
 // same as above
      std::cout << *it;
}

// now for the number of elements
std::cout << distance(begin(name), end(name));

}