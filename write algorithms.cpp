# include <iostream>
# include <algorithm>
# include <vector>

// write algorithms can change the elements in an iterator range
// replace() changes all arguments iwthin an iterator range with a given value to another value

// replace_if() will do the same thing if the predicate becomes true , we can also do this with a ranged for loop

// algorithms which change the elements have two versions
// the base version which overwrites the data in the original range
// and a _copy() version which writes the data to a different iterator range
// this is useful when the data needs to be preserved for later use and for working with associative containers

int main(){
std::vector<int> vec {1,2,3,4,1,1,2,3};
std::replace(begin(vec),end(vec),1,2); //replace every instance of 1 with 2

for (auto i : vec){
    std::cout << i;
}
std::cout << std::endl;

// lets use the replace_copy() algorithm now
std::vector<int> vec2(vec.size()); //vec2 created, same size as vec
std::replace_copy(cbegin(vec),cend(vec),back_inserter(vec2),2,1); //so replace all the 2's with a 1, and copy this result into the vector vec2
// vec remains the same, we pass an iterator to tehe new vector in our thirs argument


// there is also a replace_copy_if() to do the same thing with a lambda expression
}