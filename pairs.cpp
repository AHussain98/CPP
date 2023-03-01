# include <iostream>
# include <utility>
# include <string>
# include <algorithm>
# include <vector>
using namespace std;

// the std::pair is defined in <utility>
// it has two public data members, they can be of different types
// they are accessed as "first" and "second"
// there are no public member functions for std::pair
// std::pair can be used to return two related data items from a function
// std::pair is used by some of the containers in the standard library

// std::pair is a templated type
// when we call the pair constructor, we need to specify the types of both members

std::pair<int,int> test(1,2);
std::pair<std::string,std::string> test2("Hello","There");

// we can call make_pair() to create a pair variable

auto wordpair {std::make_pair("Hello"s,"There"s)};  // the compiler will work out what the types are based on inference
                             // put the s suffix after the string to ensure we create string objects, not an array of chars
// the s suffix is deifned in the namespace std::literals::string_literals, this is why we need to include the std namespace to get it to work

// in c++17, the compiler can deduce the types
// std::pair wordpair2 {"Hi"s, "Again"s};    // not seeming to work for me


// lets create another example
std::pair<std::string, int> find_index(const std::vector<std::string> vec, int max){ // create a function that returns a pair, we're tyring to find a string that has greater size than max
int idx {-1}; // create an index variable, initalise it as -1

auto res = find_if(cbegin(vec),cend(vec),
// capture idx by reference using lambda
[max, &idx] (const string& str) { ++idx; return str.size() > max;}); // this is the lambda predicate to run for every value in teh vector

if (res != cend(vec)){
    return {*res, idx}; //  we're using list initialisation to give values to the pair we're returning if there is a legitimate value of res, return the pair as the dereferenced res as first and index value as second
}
else { return {""s,idx}; // otherwise just return an empty string and the index we end at
}





}
int main(){

std::cout << test.first << std::endl;
std::cout << wordpair.second << std::endl;

std::vector<std::string> words {"a", "collection", "Asad", "table"};

int max {5};

auto res = find_index(words,max); // the pair will be called res

if (res.first != ""s){
    std::cout << "the first word which is more than 5 chars is " << res.first << " and its index is " << res.second;
}
}

