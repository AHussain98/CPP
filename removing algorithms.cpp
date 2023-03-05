# include <iostream>
# include <vector>
# include <algorithm>

// removing algorithms are used to remove elements from a range
// however, the elements are "logically" removed
// they are still physically present in the container

// std::remove() works by moving each element that has a given value to the back of the container
// the "removed" elements still exist in the container, the values of the removed elements are no longer defined
// accesing them will cause undefined behaviour
// elements that were behind the moved ones are brought forward
// calling size() will return the same value as before, the container still has the same number of elements
// remove() returns an iterator to the first removed element



int main(){

std::vector<int> vec {1,2,3,4,5};
auto defunct = std::remove(begin(vec),end(vec),1); //returns an iterator to the removed element, we're removing 1 from the list
std::cout << vec.size() << '\n'; // still the same number of elements

for (auto i : vec){
    std::cout << i << " "; // still has it in there, but teh value of 1 has changed to some garbage value
}
std::cout << std::endl;
// to actually physically remove elemnts, we need to call the containers erase() function

// we can actually pass the erase() function the iterator generated from the remove() function, everything after thisiterator will then be erased

vec.erase(defunct,end(vec));

for (auto i : vec){
    std::cout << i << " "; // now fewer elements
}

// there are other versions of remove(), remove_if() takes a predicate, remove_copy() version writes to a destination
// remove() uses the == operator, remove_if() allows us to provide our own predicate
// this determines whether to remove an element

// remove_copy() writes the result to a destination
// it performs a copy operation, which omits the matching elements
// this is the same as using copy_if()

// unique() removes duplicate elements
// the elements in the iterator range must be sorted
// unique behaves similarly to remove(), the elements are only logically removed, to actually remove them from teh data structure, we need to pass the returned iterator to erase()

std::vector<int> vec2 {1,1,1,2,2,2,3,3,3};   // if bector wasn't sorted, we'd have to use std::sort()
auto duplicates = std::unique(begin(vec2),end(vec2));
vec2.erase(duplicates,end(vec2));  // elements staring from first duplicate will not be destroyed
std::cout << std::endl;
for (auto i : vec2){
    std::cout << i << " "; // now no duplicates
}
// again, we can inlcude a predicate to customise this algorithm, it uses the == operator

// we can also create a copy of the unique vectoir, rather than editing the original
// this is done with unique_copy()


}