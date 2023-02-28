#include <iostream>
# include <algorithm>
#include <string>
# include <vector>

// an algorithm is a set of steps used to solve a problem, similar to a recipe in cooking
// an algorithm refers to a repeatable technique used to solve a specific problem, be it sorting or searching
// the c++ STL defines a number of functions in <algorithm>, these implement classic algorithms as well as a number of other useful routines

// std::string has a find() member function, this can perform searching but only on string objects
// the STL algorithms are global functions which will work on any kind of STL container
// these are known as "generic" algorithms

// typically, an STL algorithm is passed an iterator range, these specify which elements in the container will be processed by the algorithm, we often use begin() and end() in order to process the entire container
// the algorithm will iterator over this entire range and perform some function on each element
// usually the algorithm will return either an iterator representing a particular element or a value container the result of an operation on the elements

// string::find() returns an index, std::find() returns an iterator because some containers do not have the concept of an index, so the generec std version of the algorithm must account for this
// if the character is not found, the algorithm will return the iterator for the "one after last" element, this is an impossible value, so its returned to reflect failure to find the character

// many algorithms call a function on each element which returns bool
// find() calls the == operator for each element to compare it to the target value
// such a function is known as a predicate
// these algorithms allow us to supply our own predicate, we can pass a callable object as an optional extra argument to the algorithm call

// the std::sort() algorithm works by comparing pairs of elements, the comparison is done by calling the elements < operator on each pair of elements
// sort() moves the smallest elements to the front and largest to the back of the container

// many algorithms have two versions, the base version which takes a value argument, and an _if() version which takes a predicate argument
// find() takes a value and searches for the first element with this value
// find_if() takes a predicate function and searches for the first element where this predicate is true
// we can use a functor to provide this predicate

class ge_n{
    const int n; //numebr of characters we're searching for, private variable of class
    public:
        ge_n(int n) : n(n) { // set value of n when we create class, initialisation list used with constructor to set private variable
        }

        bool operator() (const std::string& str) {  // overloaded function call operator to create functor
            return str.size() > n;    // if the size of the string passed in is greater than n, return true
        }
};

bool find(const std::string& str) {  // overloaded function call operator to create functor
            return str.size() > 5;    // if the size of the string passed in is greater than n, return true
        }


int main(){

std::string name {"Asad Ali Hussain"};

auto result = std::find(cbegin(name),cend(name),'H'); // c versions of functions used because we don't want to modify the string

if (result != cend(name)){
    std::cout << "Match at index " << distance(cbegin(name),result);
}

std::cout << std::endl << "at this point in the string: ";

for (auto it = result; it != name.end(); ++it){
    std::cout << *it;
}

std::vector<int> nums {1223, 5743, 64, 4, 8643, 97743, 9, 101010};
std::cout << std::endl << "vector before sort: ";
for (auto i : nums){
    std::cout << i << " ";
}

std::cout << std::endl << "vector after sort: ";
std::sort(begin(nums),end(nums));
for (auto i : nums){
    std::cout << i << " ";
}

std::vector<std::string> names {"Asad", "raami", "kuthi", "pehnchod", "sid"};

// find the first function with more than 5 characters
// pass a functor object as a predicate

auto res2 = find_if(cbegin(names),cend(names),find);  //  this works because using the name of the function as a predicate causes the name to act as a function pointer
 /*   When calling a function with a function parameter, the value passed must be a pointer to a function. Use the function's name (without parentheses) for this:

func(print);
would call func, passing the print function to it.
*/

auto res3 = find_if(cbegin(names),cend(names),ge_n(5));  // its better to do this using a functor because then we can have different values of n, and the function will work for all of them
 // we can do this even more cleanly using a lambda expression instead of the functor in the code above

// display result
if (res3 != names.cend()){
    std::cout << "The first name with more than 4 characters is " << *res2;
}

}