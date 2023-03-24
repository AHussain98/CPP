# include <iostream>

// c++11 introduced attributes to provide standard syntax for compiler directives
//  attributes give extra information to the compiler, they should not be used to extend the language or change the meaning of the program
// an attribute goes inside a pair of double square brackets [[ ]]
// in declerations, attributes go before the entity they apply to e.g. [[noreturn]] void func(){...
// an attribute can be in a namespace
// attributes can take arguments

// [[noreturn]] indicates that a function does not return
// alignas() keyword is used for memory alignment

// [[deprecated]] causes a compiler warning if the object is used

// [[fallthrough]] is used in switch statements, inidcates that the break statement is intentionally omitted and the compiler should not give a warning

// c++17  provides [[nodiscard]], the compiler will give a warning if a nodiscard function is called and the return value is ignored

// attributes can also be used for variables, types, members or structs and classes etc...

// [[maybe_unused]] tells the compiler not to generate a warning if we don't use a variable we've declared

int main(){



}