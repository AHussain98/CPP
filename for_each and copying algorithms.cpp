# include <iostream>
# include <string>
# include <vector>
# include <algorithm>
// for_each() calls a function on every element in a iterator range
// this can also be done in a ranged for loop, which is usually cleaner


int main(){

std::string name {"Asad Hussain"};

for (char& i : name){    // much easier and simpler than calling the for_each algorithm
    i = toupper(i);      // passed using & to change the actual value at the address, not make a copy
    std::cout << i << " "; // also we can include break or return statements to terminate the loop early
}

// copying algorithms copy elements into another range, they are often used to populate sequential containers

// copy() is the most basic copying algorithm, the target container must be big enough!

std::vector<int> vec {1,2,3,4,5,6};
std::vector<int> vec2(6);

std::copy(cbegin(vec),cend(vec),begin(vec2)); // copied succesfully
// we can also use back_inseter(vec2) instead of begin(vec2), to call the push_back function for insertion

// copy_n() will only copy the first n elements of a range

std::copy_n(cbegin(vec),2,begin(vec2)); //so only copy the first two elements of vec over to vec2

// again, these can be accomplished with a ranged for loop

// copy_if() copies only if a certain condition is made, write this condition using a lambda in the fourth argument
// copy_if() acts as a sort of filter in between the two vectors
}