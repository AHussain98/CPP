# include <iostream>
# include <array>

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

// total = --count + 6;
// Assuming count is 6 before this statement, the-- operator will decrement it to 5, and then this value
// will be used to calculate the value to be stored in total, which will be 11.

/* 
The postfix form of ++ increments the variable to which it applies after its value is used in context. For 
example, you can rewrite the earlier example as follows:
total = count++ + 6;
With an initial value of 5 for count, total is assigned the value 11. In this case, count will be 
incremented to 6 only after being used in the surrounding expression. The preceding statement is thus 
equivalent to the following two statements:
total = count + 6;
++count;
*/

// floating point types are always signed
// to explicitly change the data type to a given type, you have to static_cast
// its better to do std::round() from <cmath>

// <ios> and <iomanip> contain stream manipulators that allow us to customise how output appears

// cpp20 introduces the <format> module which contains even more optimisations
// this works similarly to pythons old .format method for strings

// cpp20 has <limits> which include infinity and the maxiumum storable sizes for data types

// ints can be converted to chars

/* Type wchar_t is a fundamental type intended for character sets where a single character does not fit 
into one byte. Hence its name: wchar_t derives from wide character, because the character is “wider” than 
the usual one-byte character. By contrast, type char is referred to as “narrow” because of the limited range of 
character codes that are available.*/


// the auto keyword tells the compiler to deduce the type of a variable
/*  if your compiler properly supports C++17, you can use braced initialization to initialize any 
variable with a single value, provided you do not combine it with an assignment. If your compiler is not fully upto-date yet, however, you should simply never use braced initializers with auto. Instead, either explicitly state 
the type or use assignment or functional notation.*/

// chapter 3

// nested parenthesis are evaluated from innermost to outermost

/* As their name suggests, bitwise operators enable you to operate on an integer variable at the bit level. You can 
apply the bitwise operators to any type of integer, both signed and unsigned, including type char. However, 
they’re usually applied to unsigned integer types. A typical application is to set individual bits in an integer 
variable. Individual bits are often used as flags, which is the term used to describe binary state indicators. You 
can use a single bit to store any value that has two states: on or off, male or female, true or false.*/

/* The bitwise shift operators shift the contents of an integer variable by a specified number of bits to the left or 
right. These are used in combination with the other bitwise operators to achieve the kind of operations we 
described in the previous section. The >> operator shifts bits to the right, and the << operator shifts bits to the 
left. Bits that fall off either end of the variable are lost.
All the bitwise operations work with integers of any type */

/*  Variables defined within a block that are not defined to be static have automatic 
storage duration. They exist from the point at which they are defined until the end 
of the block, which is the closing curly brace, }. They are referred to as automatic 
variables or local variables. Automatic variables are said to have local scope or block 
scope. All the variables you have created so far have been automatic variables.

• Variables defined using the static keyword have static storage duration. They are 
called static variables. Static variables exist from the point at which they are defined 
and continue in existence until the program ends.

• Variables for which you allocate memory at runtime have dynamic storage duration. 
They exist from the point at which you create them until you release their memory to 
destroy them. You'll learn how to create variables dynamically in Chapter 5.

• Variables declared with the thread_local keyword have thread storage duration*/

/* Remember that the lifetime and scope of a variable are different things. Lifetime is the period of 
execution time over which a variable survives. Scope is the region of program code over which the variable 
name can be used. It’s important not to get these two ideas confused.

Global variables have static storage duration by default, so they exist from the start of the program until
execution of the program ends. Initialization of global variables takes place before the execution of main()
begins, so they’re always ready to be used within any code that’s within the variable’s scope. If you don’t
initialize a global variable, it will be zero-initialized by default. This is unlike automatic variables, which
contain garbage values when uninitialized

we can access global variables by using the scope resolution operator with nothing coming before it


*/

// an enum is another data type, variables of this enumerates types can only have values from the set
enum class days{Monday, Tuesday, Wednesday};  // enum called days, values are Monday, Tuesday, Wednesday

days today{ days::Monday }; // today is a days object with the value Monday
// when you reference an enumerator, it must be qualified by the type name
// if you try to set the days object today to value that isnt in the enum list, the code won't compile
// Each enumerator will be automatically defined to have a fixed integer value of type int by default. The first name in the list, Monday, will have the value 0, Tuesday will be 1, and so on,
int global = 10;  // an example of a non-const global variable, which will have static storage

/* Values for enumerators must 
be compile-time constants, that is, constant expressions that the compiler can evaluate. Such expressions 
include literals, enumerators that have been defined previously, and variables that you’ve specified as const. 
You can’t use non-const variables, even if you’ve initialized them using a literal*/

/* Enumeration types defined with enum class are called scoped enumerations. By default, you cannot 
use their enumerators without specifying the type’s name as a scope. For instance, you could not 
simply write today = Friday; you have to add Day:: as a scope. In C++20, you can 
bypass this sometimes tedious requirement with a using enum or using declaration.*/

// scoped enums won't convert into their integer forms without an explicit static cast
// this is unlike previously used unscoped enums (without the class keyword)
// unscoped enums can also be accessed without using thier scopes, more dangerous

/* Just as with scoped enumerations, there are times were repeatedly specifying the name of a (nested) 
namespace can become tedious, or even hamper code readability. You can eliminate the need to qualify 
a specific name with the namespace in a source file with a using declaration. Here’s an example:
using std::cout; // Make cout available without qualification
This tells the compiler that when you write cout, it should be interpreted as std::cout. With this 
declaration before the main() function definition, you can write cout instead of std::cout, which can 
save typing and make the code look a little less cluttered */

// Always use the using keyword to define a type alias. In fact, if it weren’t for legacy code, we’d be advising you to forget the keyword typedef even exists.

/* If you cast true to an integer type, the result will be 1; casting false to an integer results in 0. 
Conversely, you can also convert numerical values to type bool. Zero converts to false, and any nonzero 
value converts to true. When you have a numerical value where a bool value is expected, the compiler will 
insert an implicit conversion to convert the numerical value to type bool. This is useful in decision-making 
code */

// the <cctype> header inlcudes a bunch of fucntions for chars

// && -> and, || -> or, ! -> not

// bitwise operands cannot be used to short circuit if statements

/*  You can only switch on values of integral (int, long, unsigned short, etc.), character (char, etc.), 
and enumeration types. Technically, switching on Boolean values is allowed as well, but instead 
of a switch on Booleans you should just use if/else statements. Unlike some other programming languages, 
however, C++ does not allow you to create switch() statements with conditions and labels that contain 
expressions of any other type. A switch that branches on different string values, for instance, is not allowed */

// if you omit the break statement for a case, the statements for the following case will execute
// each case value must be a constant expression, evaluated at compile time

// the size of an array must always be a constant

//  If the same constant is scattered around your code, it is easy to make a mistake by forgetting to update 
// some of them.Therefore, define magic numbers, or any constant variable for that matter, only once.If you then
// have to change the constant, you have to do so in only one place.

// continue is the keyword to skip this current iteration of the loop
// break is the keyword to break out of the loop

// for a char array to be treated as a string, it must be terminated by the null character
// There must be a '\0' at the end. If there isn’t, the standard output stream will continue to output characters from successive memory locations,
// which almost certainly contain garbage, until either a null character happens to turn up or an illegal memory access occurs

/* An array of elements of type char can have a dual personality. It can simply be an array of characters, in 
which each element stores one character, or it can represent a string. In the latter case, the characters in the 
string are stored in successive array elements, followed by a special string termination character called the 
null character that you write as '\0'. The null character marks the end of the string*/

//  A two-dimensional array of type is char is interesting because it can be an array of C - style strings

// The C++ standard does not permit an array dimension to be specified at runtime. That is, the array dimension must be a constant expression that can be evaluated by the compiler.H

// cpp containers are compared element by element

// using the array<> container carries no performance overhead at all compared to a standard array
// vectors are dynamic arrays

/* Every variable in your program is located somewhere in memory, so they all have a unique address that 
identifies where they are stored. These addresses depend on where your program is loaded into memory 
when you run it, so they may vary from one execution to the next. A pointer is a variable that can store an 
address of another variable, of some piece of data elsewhere in memory. */

// As a rule, you should always initialize a pointer when you define it. If you cannot give it its intended value yet, initialize the pointer to nullptr.

// The address-of operator, &, is a unary operator that obtains the address of a variable.

/* Applying the indirection operator, *, to a pointer accesses the contents of the memory location to which 
it points. The name indirection operator stems from the fact that the data is accessed “indirectly.” The 
indirection operator is often called the dereference operator as well, and the process of accessing the data in 
the memory location pointed to by a pointer is termed dereferencing the pointer. To access the data at the 
address contained in the pointer pnumber, you use the expression *pnumber. */



int main() {
	int x = 10;

	double new_x{ static_cast<double>(x) }; // casted

	std::cout << new_x << std::endl;

	new_x += 1.1;

	std::cout << new_x << std::endl;

	char ch{ 56 }; // int implicitly converted to char
	std::cout << ch << std::endl;

	int num = 10;
	num >>= 1;  // bitwise shift right by 1 bit
	std::cout << num << std::endl;

	std::cout << ::global << std::endl;  // access the global variable using SRO

	std::cout << "today's day is " << static_cast<int>(days::Monday) << std::endl;
	int temperatures[10]{1,2,3,4,5,6,7,8,9,10}; // defines an array of 10 elements if doubles called temperatures
	temperatures[0] = 1;  // change the value of an array element
	std::cout << temperatures[0] << std::endl;

	double test[5]; // test array with 5 elements
	test[0] = 10.6;

	for (int i = 0; i < 5; ++i) {
		test[i] = temperatures[i]; // copy elements from temperatures to test
	}
	std::cout << std::size(test) << std::endl; // size of the array

	std::array<int, 100> values; // array called values that stores 100 ints


}