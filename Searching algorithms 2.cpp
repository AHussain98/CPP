# include <iostream>
# include <algorithm>
# include <vector>

// mismatch() takes two iterator ranges and looks for differences between the two ranges
// it returns a pair of iterators to the first element that has a different value in each range

// these three algorithms take an integer range and a predicate
// all_of() returns true if the predicate is true for every element
// any_of() returns true if the predicate is true for at least one element
// none_of() returns true if the predicate is false for every element

// we've used find() previously, but if the elements you're searching through are already stored, we can use binary_search()
// it assumed the iterator range is sorted which makes the search much faster
// by default, it uses the == operator of the element
// binary search is much faster than find(), but requires sorted elements
// binary search returns a bool

// includes() takes two iterator ranges
// it also assumes the iterator ranges are sorted
// includes() returns a bool, depending on whether all the elements in the second range are present in the first range
// by default, it uses the == operator of teh element


int main(){

std::vector<int> vec {1,2,3,4,5,6,7};
std::vector<int> vec2 {1,2,3,4,6,6,7}; // they're different

auto it = std::mismatch(cbegin(vec),cend(vec),cbegin(vec2),cend(vec2));
std::cout <<  *it.first  << std::endl; // shows the value of the mismatch in vec
std::cout << *it.second << std::endl; // same for vec2

std::cout << "Found mismatch in vec, at index " << std::distance(cbegin(vec),it.first) << std::endl;

// define a lambda expression that returns true if an alement is odd

auto is_odd = [] (const int n) { return ((n%2) != 0);};


bool result = std::any_of(cbegin(vec),cend(vec),is_odd);
std::cout << std::boolalpha << result << std::endl; // returns true, so there's atleast oen odd element

if (std::binary_search(cbegin(vec),cend(vec),4)) {  // if 4 is in this sorted sequence
    std::cout << "we found it!";

    // if the vector wasn't sorted, we could use sort() on it beforehand to get it in ascending order, then use binary_search()
}
}