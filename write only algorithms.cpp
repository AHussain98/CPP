# include <iostream>
# include <vector>
# include <algorithm>

// the standard library defines a few algorithms that write to an iterator range but do not read any elements
// these are useful for populating sequential containers
// fill() assigns a given value to the elements in an iterator range

// fill_n() is similar but takes a number instead of second iterator, this determines how many elements will be assigned
int main(){

std::vector<int> vec(10); // remmeber () is for creating the size, {} is for giving values
std::fill(begin(vec),end(vec),42); // give all 10 elements the value 42
std::fill_n(begin(vec),5,24); // give the first 5 elements the value 24

// we can also use back_inserter(vec) for the first argument, this calls push_back() for every element in the fill() function call

// fill_n() does not check the size of the container before hand, so this could cause an issue

// we can actually resize the vector ourselves
if (vec.size() < 12){
    std::vector<int> new_vec(12);   // create a new vector with the right number of elements
    new_vec.assign(begin(vec),end(vec)); // copy the elements of vec to vec2, if we don't do this, vec will become blank
    vec.swap(new_vec);  // calling swap exchanges the memory buffer of two vectors,so now vec has the 12 element size
}
// new_vec is local to the scope above, so once the program reaches this point, it is destroyed and the memory released
// vectors always expand to add more elements, but they can't shrink, this is one way to acheive that

for (auto i : vec){
    std::cout << i; // works!
}

// generate() uses the value returned from calling a function to assign the elements
// this function takes no arguments and returns a value of the elements type, it shoudl return a different value every time it is called


// we could use generate() to assign values using the value returned from a functor, for example



}