# include <iostream>
# include <type_traits>

// compile time programming, the compiler executes code at compile-time, the result of the computation is available in the program, no run-time overhead
// traditional c++ has templates, these were intended to support generic programming, later were discovered to provide their own type of programming language
// template parameters can represent state variables, recursive instantiation can simulate loops, template specialisations to implement control flow, integer operations to calculate results

// template metaprogramming is mainly done by library developers, it can be used for compile time programming
// can also be used or writing generic code to avoid duplication, making decisions at compile time for efficiency and/or portability, domain specific programming and expressing complex software patterns and concepts

// template metaprogramming mostly uses class templates rather than functions
// by convention: members that represent numeric results or other values are named "value", members that represent types are named "type"
// template metaprogramming makes heavy use of template specialization, and of "type traits" to get information about the properties of types e.g. is_arithmetic<T>

// using only templates for compile time programming leads to clumsy and verbose syntax, complicated logical errors, incomprehensible error messages and no debugger support
// c++11 also provides constexpr -> the compiler executes normal c++ code, this gives understandable error messages

// a constant expression has a value that is evaluated at compiler time and which cannot change, this could be a literal, a value computed from literal, or a value computed from other constant expressions
// a variable can be a constant expression if it is initalised by a constant expression and it subsequently cannot be modified

// the const keyword is in all versions of c++
// a const variable cannot be modified after it has been initialized
// we can initialize a const variable from a constant expression e.g. const int i{3};  // we cannot change the value of i
// or from a value only known at runtime:  int x; cin >> x; const int y{x}; // cannot change the value of y

// in c++11, we have the constexpr keyword, this indicates that a variable is a constant expression
// a constexpr variable is evaluated at compile time and cannot be modified

// a const variable cannot be modified, these are mainly used for function arguments
// an argument can be passed by reference or pointer to const for efficiency and safety
// the compiler will not allow the called fucntion to modify it

// a constexpr variable has a value which is known at compile time and cannot be modified
// these are used for computing the values of constant, and to improve performance by doing computation at compile time instead of when the program runs

class A{
};

int main(){
std::cout << std::boolalpha; // modify output stream to say true or false
std::cout << std::is_arithmetic<int>::value << '\n'; // true
std::cout << std::is_class<A>::value << '\n'; //true
std::cout << std::is_floating_point<double>::value << '\n'; //true
std::cout << std::is_pointer<const char *>::value << '\n'; // true, pointer to c style string

const int i {42}; // constant expression, initalised from a literal
const int j {99}; // constant expression, initialsed from a literal
const int k {i + j}; // computed from constant expressions, therefore constant
// dimensions of an array must be a constant expression, so int arr[i+j]; is fine as i and j are constant expressions

int arr[i+j]; // compiles fine
// constant expressions should say const, obviously

constexpr int i {34}; // evaluated at compile time, cannot be modified

}