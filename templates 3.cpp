# include <iostream>
# include <string>
# include <tuple>

// the extern keyword turns the definition of an uninitialized variable into a decleration
// this is used to make a global variable accessible accross source files
// extern just means the variable is defined somewhere else
// there must be exactly one file where the variable is defined (instantiated without the extern keyword)

// extern keyword can also be used with templates
// declare the instantiaton as an extern template (this must come after the template definition)
// there must be exactly one file where the function is instantiated

// e.g.  template<typename T> class test{...}
//         extern template class test<int>   // declares test<int> as instantiated somewhere

//   in another file:     template class test<int>;    // compiler will instantiate test<int> here


// a variadic function can take any number of arguments, a variadic template has a list of parameter types which is written as typename...T
// variadic template functions execute at compile time
// the list of function parameter types is written as T...
// template<typename...Args>  // Args is a list of template parameter types
// void func(Args...args); // args is a list of arguments whise types match Args
// these ...lists are known as parameter packs

// the compiler will deduce the number of arguments and their types from the call

// parameter packs are only available at compile time, we can do three things with a parameter pack:
// use sizeof...(args) to get the number of elements
// use make_tuple() to store them in an std::tuple
// iterate over the elements using template recursion

template <typename... Args>  // Args is a list of types (template parameter pack)
void func(Args... args){    //args is a list of arguments whose types match Args
    std::cout << "compiler has deduced call with " << sizeof...(args) << " arguments \n";
    auto arg_tuple = std::make_tuple(args...); //store the arguments in a tuple
    auto first = std::get<0>(arg_tuple);
    std::cout << "First argument is " << first;
}

// we can have template recursion, recursive template function calls
// we can process a variadic template's pack by making recursive function calls
// each call removes the first element from the list
// to terminate the recursion, we write another template with a single argument, this will be passed the final element in the list
/// this must be declared above the variadic template in the source code


int main(){
int i {42}; double d {0.4}; std::string s {"Yo!"};

func(s); // instantated as func(string&)

std::cout << std::endl;
func(i,d,s); //instantiated as func(int,double,string)

static_assert(sizeof(int) == 8, "this program requires a 64 bit compiler");    // size of int is 4 for a 32 bit compiler, so comilation fails

}

// c++ inherited assert() from c, defined in <cassert>
// this thecks its argument at runtime, if the argument is not true, it calls std::abort(), otherwode the program continues normal execution
// can be disabled by #define NDEBUG

// c++11 provides static_assert(), it takes a constant bool expression and a string literal
// the bool expression is checked during compilation, if false, the compilation stops and the string literal will be used in the compilers error message
// otherwise the compilation continues as normal
// mainly used in template metaprogramming


// also you can set defaults for data types within the template
// e.g. template<typename T = int>, now when we instantiate the template object with <>, it will use ints during compilation