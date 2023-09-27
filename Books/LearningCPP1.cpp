# include <iostream>

//  Unicode defines unique integer code values that represent characters for virtually all of the languages in the world as well as many specialized character sets.Code values
// are referred to as code points.Unicode also defines how these code points may be encoded as byte sequences.

// a variable is a named piece of memory you define
// every variable stores data of only a specific type which we have go use a keyword to define

int apple_count{ 15 }; // braced initialization
// braced initalisation is safer than using () or = because it won't allow type conversion, e.g. int apple_count(15.5) will not compile

// you can write the value of any fundamental data type to an output stream

// short is 2 bytes, int is 4 bytes, long is 8 bytes
// use unsigned integers when we don't need to store negative numbers

// const keyword tells compiler that the value of a variable must not be changed
// constant values of any kind are referred to as literals

// since c++14, we can use a single ' in a numeric literal to make it more readable

//  The values that an operator acts upon are called operands, so in an expression such as 2 * 3, 
// the operands are 2 and 3. Operators such as multiplication that require two operands are called binary
// operators.Operators that require one operand are called unary operators.An example of a unary operator
// is the minus sign in the expression - width.

// remember integer divisions are rounded down
// This means that, in C++, 11 / 4 will always give the integer value 2.

// Parentheses can be nested, in which case subexpressions between parentheses are executed in sequence from the innermost pair of parentheses to the outermost.
// multiplication is always evaluated before addition

// compound assignment operators +=, -=, *=, /=, %=
// x += 1 is the same as x = x + 1
// these can also be done in bitwise manner

// sizeof() obtains the memory occupied by a data type, in bytes
// sizeof() can be applied to any fundamental type, class type or pointer type

// page 68






int main() {

}