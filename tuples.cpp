# include <iostream>
# include <tuple>
# include <string>
// std::pair is a compound type, it has two members of any type, accessed as first and second
// we can create a pair object excplicitly std::pair<string,string> wordpair("hello","there")
// or use make_pair to create a pair object auto wordpair {make_pair("hello","there")}

// std::tuple is defined in <tuple>, it is similar to pair but can have any fixed number of elements
// elements are accessed by index, not by member name, as with pair, we can make a tuple object explicitly or use make_tuple


int main(){
std::tuple<double,int,std::string> numbers (10.1,5,"fifteen");

auto num {std::make_tuple("hello","there","all")};

// to access tuple members, we use the templated std::get() function
// this takes the tuple as argument and uses the elements index as the template parameter

std::cout << std::get<2>(numbers) << " " << std::get<2>(num) << std::endl;

// we can also set elements using the get function
std::get<2>(numbers) = "hello";

// we can unpack data from a tuple using the tie function, you have to generate variables first
int i,j;
std::string k;
std::tie(i,j,k) = numbers;         // tie stores teh tuple members in those variables and you can then print them
std::cout << i << "," << j << "," << k << std::endl;

// tuples are useful as an ad-hoc data type
// if we want to store data somewhere that doesnt need member or special member functions and has elements of different types
// tuples are used to return multiple values from a function call, tradionally we would use a struct to do this (create a struct with a unique name, think of names for all the members, populate members one by one in teh function, copy members one by one in the caller)
// using a tuple requires much less code, just return the tuple from the function and make tie(i,j ...) = the function
}