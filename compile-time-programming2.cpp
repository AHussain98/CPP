# include <iostream>

// c++11 has constexpr functions, argumnets are constant expressions, return a constant expression, executed at complile time, written in normal c++
// constexpr functions are implemented using a compile-time interpreter which supports most of c++  (this is an interpreter which runs inside of the compiler)

   constexpr milesTokm(double miles){ return miles*1.602;} // to make a function constexpr, we put the constexpr keyword before its return type
   // if the argument and return value are constant expressions, this function is evaluated at compile-time
// a constexpr function must be "pure", it cannot modify its arguments and cannot modify gloabl/static variables
// constexpr fucntions are implicitly defined as inline, multiple definitions are allowed and they can be used in header-only libraries

// a constexpr function can be called with arguments that are not constant expressions
// in this case, the return value will not be a constant expression, if the return value needs to be a constant expression, this is an error
// the function will be evaluated at runtime, like other functions
// this avoids the need to write an otehrwise identical version for variables

int main(){

const double dist1 = milesTokm(50); // argument and return values are constant expressions so function evaluated at compile time

double arg{40}; // this variable is not a constant expression because it can be modified
double dist2 = milesTokm(arg); // argument is not a constant expression and neither is return value so function evaluated at runtime

//constexpr double dist3 = milesTokm(arg);  // fails due to non constant argument, return value is supposed to be a constexpr variable, this won't compile because to do this, the argument and return type must be const
// change arg to an int and it will compile

// constexpr functions are useful for performing caluclations at compile time, the calculation is done once (during the development process) instead of every time the program is run
// no runtime overhead and reduces energy consumption

// in c++11, the body of a constexpr function could onlu contain a single return statement
// in c++14, these requirements were relaxed and constexpr functions can contain multiple statements, variable declerations (must be initialised and non static) and flow control (if, switch and loops including ranged for loops)
// however, the body of a constexpr function may not include anything which causes an action at runtime (new.delete, calling virtual function, throwing exceptions)

// a member function can be made constexpr, takes constant expression arguments and returns a constant expression
// this is a different restruction from a member fucntion which is const (such a function cannot modify "this" i.e. the object that called the function)
// constexpr member functions are allowed to modify "this" unless also delcared as const

// classes and structs can have members which are constexpr, these are initialed from a constant expression and cannot be modified
// these must also be declared static otherwise the data members will not be available at compile time
}