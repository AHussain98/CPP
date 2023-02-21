# include <iostream>

// c++ defines operators for built in types
// operator + is used in a function to add two variables and return the result

// == operator is used in a function and returns a bool

// STL defines operators for its types, so you can use + and == on strings

// an operator that takes a single argument is "unary", 2 arguments is binary (such as +) and three arguments is ternary
// a ternary operator is a ? b : c  -> evaluates to if a then b, else c

// unary operators are usually member functions, binary operators are usually not
// classes in the STL will usually have operators whoch act on objects of that class, they will have similar syntax as operators for the built in types

// when we create a class, c++ will not provide us with default operators to use for it, (apart from the = assignment operator which can be synthesized)
// so we can define our own, called overloading the operators, we must use the same symbols and syntax as built in operators

// =/+* are only really useful for mathematical classes
// in general programming, the most useful operators are =, ==, !=, < ()

// you cannot and should not overload &&, || &, comma , , :: .* ?

// the return value of the overloaded operator should correspond to the equivalent c++ operator


int main(){



}