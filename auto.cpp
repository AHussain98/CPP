#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(){



    std::vector<int> v {1,2,3,4,5}; // this is how you declare a vector, std::vector<int>
    // auto just means we want the compiler to deduce what the type of a variable should be based on its initial value

    auto i {1}; //assigned as an int
    auto j {1.20}; //assigned as a double
    std::string k = "Hello"; //assigned as a string

     auto it = v.begin(); // auto can even be assigned to iterators of a class, this is the same as vector<int>::iterator
    std::cout << *it;

    auto hello = "Hello!"s;  // this creates a string class object
//this creates a std::string and is the same as writing auto hello = std::string{"Hello!"};, whereas

//auto hello = "Hello!"; // creates a const char* pointer pointing to a const char[7] array.

    // const and reference are ignored when using auto, its just the data type

    const int& x {6};
    auto y = x;
    y++; // this is legal as const ignores const and references, so its just going to value copy the value of x
    // if we wanted to make y the same as x, we'd have to incldue the const and & ourselves,
    // const auto& y = x
}