# include <iostream>

// in c++14, the compiler can always deduce the return type of a lambda expression, in effect, the return type is implicitly auto
// we can also use auto for the type of the arguments to the lambda expression
// these are known as generic lambdas or polymorphic lambdas
// the compiler will reduce the argument types from the way the lambda expression is called
// it uses the same rules for a template function

auto func = [] (auto x, auto y) {return x + y;}; // the arguments of func can have any type, so long as the + operator is defined for them

// in c++14, we can create variables in the capture specifier, e.g. [y=2]
// y here would be local to the lambda body
// these variables are implicitly auto and must be initialised

auto add_two = [x=2] (auto y) {return x*y;};  // x is local to the lambda body

// these lambda local variables can be initalised from captures
/* e.g.  int z {5};
          [y = z+1] // this is valid, teh z variable is in the local scope and the lambda can use it therefore to initalise the y variable to be used in its body.
*/

// this is implemented via the compiler generating a functor with a private member which is initalised using teh capture code
// the compiler will then instantiate the functor and call it

int main(){
std::cout << func(2,5) << std::endl;
std::cout << func(2.45,7.92) << std::endl;

// this works because, as with a normal lambda, the compiler generates a functor
// only now, the functor is generated with a templated function call operator

std::cout << add_two(17);
}