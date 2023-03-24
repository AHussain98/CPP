# include <iostream>
# include <string>
# include <type_traits>

// constexpr if was added in c++17, allows conditionals to be evaluated at compile-time
// conditionals can be evailated at compile time, this an be used for conditional compilation,
// only the "true" branch is compiled into the program, the "false" branches are ignored by the compiler

// c++ has preprocessor directives that can be used for conditiona compilation
// #if and #ifdef conditionally include or exclude code form compilation
// c++ preprocessor directives have a number of drawbacks, they use simple text-based substitution, the preprocessor does not understand types or c++ syntax, arguments are not evaluated
// constexpr if is executed during compilation, has access to all the compilers internal data, in particular type information

template <typename T>
std::string get_string(const T& arg){
    if constexpr (std::is_same_v<std::string, T>) {// replaced by true if T is a string, else false
    return arg; }                        // will only compile the true branch
    else   {
       return std::to_string(arg);  }
}


int main(){
   int x {42};
   get_string(x);
}

// problem with runtime if is that all branches must compile, even if they are not taken
// with constexpr if, only the branch which is true gets compiled