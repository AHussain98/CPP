﻿# include <iostream>
# include <array>
# include <string>
# include <memory>


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

/* const char* const pstars[] {
 "Fatty Arbuckle", "Clara Bow", "Lassie",
"Slim Pickens", "Boris Karloff", "Mae West",
"Oliver Hardy", "Greta Garbo"
 };

The extra const keyword following the element type specification defines the elements as constant, so now 
the pointers and the strings they point to are defined as constant. Nothing about this array can be changed.*/

/*  A pointer to a constant: You can’t modify what’s pointed to, but you can set the 
pointer to point to something else:
const char* pstring {"Some text that cannot be changed"};

 A constant pointer: The address stored in the pointer can’t be changed. A constant
pointer can only ever point to the address that it’s initialized with. However, the
contents of that address aren’t constant and can be changed. Suppose you define an
integer variable data and a constant pointer pdata:
int data {20};
int* const pdata {&data};
pdata is const, so it can only ever point to data. Any attempt to make it point
to another variable will result in an error message from the compiler. The value
stored in data isn’t const, though, so you can change it:
*pdata = 25;

 A constant pointer to a constant: Here, both the address stored in the pointer and
the item pointed to are constant, so neither can be changed. Taking a numerical
example, you can define a variable called value like this:
const float value {3.1415f};
value is a constant, so you can’t change it. You can still initialize a pointer with
the address of value, though:
const float* const pvalue {&value};
pvalue is a constant pointer to a constant. You can’t change what it points to, and
you can’t change what is stored at that address

You know that an automatic variable is created when its definition is executed. The space for an automatic
variable is allocated in a memory area called the stack. The stack has a fixed size that is determined by your
compiler. There’s usually a compiler option that enables you to change the stack size, although this is rarely
necessary. At the end of the block in which an automatic variable is defined, the memory allocated for the
variable on the stack is released and is thus free to be reused. When you call a function, the arguments you
pass to the function will be stored on the stack along with the address of the location to return to when
execution of the function ends.
Memory that is not occupied by the operating system or other programs that are currently loaded
is called the free store.1
 You can request that space be allocated within the free store at runtime for a new
variable of any type. You do this using the new operator, which returns the address of the space allocated, and
you store the address in a pointer. The new operator is complemented by the delete operator, which releases
memory that you previously allocated with new. Both new and delete are keywords, so you must not use
them for other purposes.

Memory fragmentation can arise in programs that frequently allocate and release memory blocks. Each time
the new operator is used, it allocates a contiguous block of bytes. If you create and destroy many memory
blocks of different sizes, it’s possible to arrive at a situation in which the allocated memory is interspersed
with small blocks of free memory, none of which is large enough to accommodate a new memory allocation
request by your program. The aggregate of the free memory can be quite large, but if all the individual blocks
are small (smaller than a current allocation request), the allocation request will fail. Figure 6-6 illustrates the
effect of memory fragmentation.

 Never use the operators new, new[], delete, and delete[] directly in day-to-day coding. These
operators have no place in modern C++ code. Always use either the std::vector<> container (to replace
dynamic arrays) or a smart pointer (to dynamically allocate individual objects and manage their lifetimes). These
high-level alternatives are much, much safer than the low-level memory management primitives and will help
you tremendously by eradicating dangling pointers, multiple deallocations, allocation/deallocation mismatches,
and memory leaks from your programs.

 A unique_ptr<T> object behaves as a pointer to type T and is “unique” in the sense
that there can be only one single unique_ptr<> object containing the same address.
In other words, there can never be two or more unique_ptr<T> objects pointing to
the same memory address at the same time. A unique_ptr<> object is said to own
what it points to exclusively. This uniqueness is enforced by the fact that the compiler
will never allow you to copy a unique_ptr<>.

A shared_ptr<T> object also behaves as a pointer to type T, but in contrast with unique_
ptr<T> there can be any number of shared_ptr<T> objects that contain—or, share—the
same address. Thus, shared_ptr<> objects allow shared ownership of an object in the
free store. At any given moment, the number of shared_ptr<> objects that contain a
given address in time is known by the runtime. This is called reference counting. The
reference count for a shared_ptr<> containing a given free store address is incremented
each time a new shared_ptr<> object is created containing that address, and it’s
decremented when a shared_ptr<> containing the address is destroyed or assigned to
point to a different address. When there are no shared_ptr<> objects containing a given
address, the reference count will have dropped to zero, and the memory for the object
at that address will be released automatically. All shared_ptr<> objects that point to the
same address have access to the count of how many there are. 

A weak_ptr<T> is linked to a shared_ptr<T> and contains the same address.
Creating a weak_ptr<> does not increment the reference count associated with the
linked shared_ptr<> object, though, so a weak_ptr<> does not prevent the object
pointed to from being destroyed. Its memory will still be released when the last
shared_ptr<> referencing it is destroyed or reassigned to point to a different address,
even when associated weak_ptr<> objects still exist. If this happens, the weak_ptr<>
will nevertheless not contain a dangling pointer, at least not one that you could
inadvertently access. The reason is that you cannot access the address encapsulated
by a weak_ptr<T> directly. Instead, the compiler will force you to first create a
shared_ptr<T> out of it that refers to the same address. If the memory address for
the weak_ptr<> is still valid, forcing you to create a shared_ptr<> first ensures that
the reference count is again incremented and that the pointer can be used safely
again. If the memory is released already, however, this operation will result in a
shared_ptr<> containing nullptr.

One use for having weak_ptr<> objects is to avoid so-called reference cycles with shared_ptr<> objects.
Conceptually, a reference cycle is where a shared_ptr<> inside an object x points to some other object y
that contains a shared_ptr<>, which points back to x. With this situation, neither x nor y can be destroyed.
In practice, this may occur in ways that are more complicated. weak_ptr<> smart pointers allow you to break
such reference cycles. Another use for weak pointers is the implementation of object caches.
However, as you no doubt already started to sense, weak pointers are used only in more advanced
use cases.

To create a std::unique_ptr<T> object that points to a newly allocated T value, always use the
std::make_unique<T> () function.

It is mostly recommended to use a vector<T> container instead of a unique_ptr<T[]> because this
container type is far more powerful and flexible than the smart pointer. We refer to the end of the previous
chapter for a discussion of the various advantages of using vectors.

The expression std::make_unique<T>() creates a variable of type T that is value-initialized.
For fundamental types (such as int and double), this means the variable is initialized to zero. Similarly,
std::make_unique<T[]>(n) creates an array of n value-initialized T values. This initialization is not always
necessary, and may, at times, impact performance (zeroing out memory takes time). In C++20 you can
therefore use std::make_unique_default_init<T>() or make_unique_default_init<T[]>(n). These
new creational functions use default initialization instead of value initialization. For fundamental types, default
initialization results in indeterminate, uninitialized values (similar to what you get when defining a variable or
array variable on the stack without initializing their values)

Creating a shared_ptr<T> object involves a more complicated process than creating a unique_ptr<T>,
not least because of the need to maintain a reference count. The definition of pdata involves one memory
allocation for the double variable and another allocation relating to the smart pointer object. Allocating
memory in the free store is expensive on time. You can make the process more efficient3
 by using the
std::make_shared<T>() function that is defined in the <memory> module to create a smart pointer of type
shared_ptr<T>:

auto pdata{ std::make_shared<double>(999.0) }; // Points to a double variable

The type of variable to be created in the free store is specified between the angled brackets. The
argument between the parentheses following the function name is used to initialize the double variable it
creates. In general, there can be any number of arguments to the make_shared() function, with the actual
number depending on the type of object being created. When you are using make_shared() to create objects
in the free store, there will often be two or more arguments separated by commas. The auto keyword causes
the type for pdata to be deduced automatically from the object returned by make_shared<T>(), so it will be
shared_ptr<double>.
You can initialize a shared_ptr<T> with another when you define it:
std::shared_ptr<double> pdata2 {pdata};

pdata2 points to the same variable as pdata. You can also assign one shared_ptr<T> to another:

std::shared_ptr<double> pdata{ std::make_shared<double>(999.0) };
std::shared_ptr<double> pdata2; // Pointer contains nullptr
pdata2 = pdata; // Copy pointer - both point to the same variable
std::cout << *pdata2 << std::endl; // Outputs 999

A reference is a name that you can use as an alias for another variable. Obviously, it must be like a
pointer insofar as it refers to something else in memory, but there are a few crucial differences. Unlike a
pointer, you cannot declare a reference and not initialize it. Because a reference is an alias, the variable for
which it is an alias must be provided when the reference is initialized. Also, a reference cannot be modified
to be an alias for something else. Once a reference is initialized as an alias for some variable, it keeps
referring to that same variable for the remainder of its lifetime

You can define a reference as an alias for data like this variable:
double& rdata {data}; // Defines a reference to the variable data

None of the dereferencing that you need with a pointer is necessary—
you just use the name of the reference as though it were a variable. A reference always acts as a true alias,
otherwise indistinguishable from the original variable. If you take the address of a reference, for instance, the
result will even be a pointer to the original variable. In the following snippet, the addresses stored in pdata1
and pdata2 will thus be identical:
double* pdata1 {&rdata}; // pdata1 == pdata2
double* pdata2 {&data}

A reference variable is thus much like a const pointer variable:
double* const pdata {&data}; // A const pointer containing the address of data

Take care: we didn’t say a pointer-to-const variable but a const pointer variable. That is, the const
needs to come after the asterisk. Reference-to-const variables exist as well. You define such a reference
variable by using the const keyword:

const double& const_ref{ data };
Such a reference is similar to a pointer-to-const variable—a const pointer-to-const variable to be
exact—in the sense that it is an alias through which one cannot modify the original variable. The following
statement, for instance, will therefore not compile:
const_ref *= 2; // Illegal attempt to modify data through a reference-to-const


The variable t is initialized to the value of the current array element on each iteration, starting with
the first. The t variable does not access that element itself. It is just a local copy with the same value as the
element. You therefore also cannot use t to modify the value of an element. However, you can change the
array elements if you use a reference
Using a reference in a range-based for loop is efficient when you are working with collections of
objects. Copying objects can be expensive on time, so avoiding copying by using a reference type makes your
code more efficient.
When you use a reference type for the variable in a range-based for loop and you don’t need to modify
the values, you can use a reference-to-const type for the loop variable:
for (const auto& t : temperatures)
 std::cout << std::format("{:6.2}", t);
std::cout << std::endl;
You still get the benefits of using a reference type to make the loop as efficient as possible (no copies
of the elements are being made!), and at the same time you prevent the array elements from being
inadvertently changed by this loop.


The <string> module of the C++ Standard Library defines the std::string type, which is much easier
to use than a null-terminated string. The string type is defined by a class

 You can convert a std::string object to a C-style string using two similar methods. The first is by
calling its c_str() member function (short for C-string):
const char* proverb_c_str = proverb.c_str();
This conversion always results in a C-string of type const char*. This pointer can therefore not be used to
modify the characters of the string, only to access them. The second option, the data() member function,
results in a char* pointer1
:
char* proverb_data = proverb.data();
You should convert to C-style strings only when calling legacy C-style functions. In your own code, we
recommend you consistently use std::string objects (or equivalents) because these are far safer and far
more convenient than plain char arrays.

string objects can be concatenated

plain char arrays cannot be stored in containers, whereas string objects can which is a huge advantage
strings can be appended to, allow access to a particular char via [] and allow access to a ubstring via substr()

std::swap() is in <utility>

string_view allows you to inspect any
type of character sequence (in our case: string literals) using the same high-level functions as std::string, but
with the additional guarantee that it will never copy any (sub)strings. A string_view object only allows you to
view a string's characters (hence the name), not to alter, add, or remove them.

std::stoi() -> string to int

A function with a return type other than void must return a value of the type specified in the function header.
The only exception to this rule is the main() function, where, as you know, reaching the closing brace is
equivalent to returning 0.

When returned variable is a copy of the returned variable being returned is made
automatically, and this copy is made available to the calling function. The general form of the return
statement is as follows:

return expression;

expression must evaluate to a value of the type that is specified for the return value in the function
header or must be convertible to that type. The expression can be anything, as long as it produces a value
of an appropriate type. It can include function calls and can even include a call of the function

There are two mechanisms by which arguments are passed to functions, pass-by-value and pass-byreference. We’ll explain the pass-by-value mechanism first.
With the pass-by-value mechanism, the values of variables or constants you specify as arguments are not
passed to a function at all. Instead, copies of the arguments are created, and these copies are transferred to
the function. 

When a function parameter is a pointer type, the pass-by-value mechanism operates just as before. However,
a pointer contains the address of another variable; a copy of the pointer contains the same address and
therefore points to the same variable.

An array name is essentially an address, so you can pass the address of an array to a function just by using its
name. The address of the array is copied and passed to the function. This provides several advantages:

• First, passing the address of an array is an efficient way of passing an array to a
function. Passing all the array elements by value would be time-consuming because
every element would be copied. In fact, you can’t pass all the elements in an array by
value as a single argument because each parameter represents a single item of data.

• Second, and more significantly, because the function does not deal with the
original array variable but with a copy, the code in the body of the function can
treat a parameter that represents an array as a pointer in the fullest sense, including
modifying the address that it contains. This means you can use the power of pointer
notation in the body of a function for parameters that are arrays. Before we get to
that, let’s try the most straightforward case first—handling an array parameter using
array notation.

As you may recall, a reference is an alias for another variable. You can specify a function parameter as a
reference as well, in which case the function uses the pass-by-reference mechanism with the argument.
When the function is called, an argument corresponding to a reference parameter is not copied. Instead,
the reference parameter is initialized with the argument. Thus, it becomes an alias for the argument in the
calling function. Wherever the parameter name is used in the body of the function, it is as if it accesses the
argument value in the calling function directly.

You specify a reference type by adding & after the type name. To specify a parameter type as “reference
to string,” for example, you write the type as string&. Calling a function that has a reference parameter
is no different from calling a function where the argument is passed by value. Using references, however,
improves performance with objects such as type string. The pass-by-value mechanism copies the object,
which would be time-consuming with a long string and memory-consuming as well for that matter. With a
reference parameter, there is no copying.

Always declare variables as const whenever their values are not supposed to change anymore after
initialization. This will make your code more predictable and hence easier to read and less prone to subtle bugs.
Moreover, and perhaps even more importantly, in your function signatures, always declare pointer or reference
parameters with const as well if the function does not modify the corresponding arguments. First, this makes
it easier for programmers to use your functions because they can easily understand what will or will not be
modified by a function just by looking at its signature. Second, reference-to-const parameters allow your
functions to be called with const values. As we will show in the next section, const values—which as you now
know should be used as much as possible—cannot be assigned to a reference-to-non-const parameter.

Input parameters should usually be references-to-const. Only smaller values, most notably those of
fundamental types, should be passed by value. Use reference-to-non-const only for output parameters, and even
then you should often consider returning a value instead. We’ll study how to return values from functions soon.

in function parameters, implicit conversions are only supported for reference-to-const parameters, not for reference-tonon-const parameters.
 you can also specify default values for parameters that are passed by reference-to-const in the same manner:
void show_error(const std::string& message = "Program Error"); // Better...
From what you learned in the previous section, it also should come as no surprise that default values for
which the implicit conversion requires the creation of a temporary object—as is in our example—are illegal
for reference-to-non-const parameters. Hence, the following should not compile:
void show_error(std::string& message = "Program Error"); /* Does not compile 

In this case, the compiler will deduce std::string as a return type, not std::string& .That is, a copy
will be returned rather than a reference.If you want to return a reference for larger(), your options include
the following :
• Explicitly specify the std::string& return type as before.
• Specify auto & instead of auto.Then the return type will always be a reference.
While discussing all details and intricacies of C++ type deduction is well outside our scope, the good
news is that one simple rule covers most cases :

auto never deduces to a reference type, always to a value type.This implies that even when
you assign a reference to auto, the value still gets copied.This copy will moreover not be const, unless you
explicitly use const auto.To have the compiler deduce a reference type, you can use auto& or const auto &

A static variable that you
define within a function is created the first time its definition is executed. It then continues to exist until the
program terminates. This means you can carry over a value from one call of a function to the next. To specify
a variable as static, you prefix the type name in the definition with the static keyword.

You can specify any type of variable as static, and you can use a static variable for anything that
you want to remember from one function call to the next. You might want to hold on to the number of the
previous file record that was read, for example, or the highest value of previous arguments.

Function overloading allows several functions in a program to have the same name as long as they all
have a parameter list that is different from each other. You learned earlier in this chapter that the compiler
identifies a function by its signature, which is a combination of the function name and the parameter
list. Overloaded functions have the same name, so the signature of each overloaded function must be
differentiated by the parameter list alone. That allows the compiler to select the correct function for each
function call based on the argument list. Two functions with the same name are different if at least one of the
following is true:
• The functions have different numbers of parameters.
• At least one pair of corresponding parameters is of different types.
■ Note The return type of a function is not part of the function’s signature. To decide which function overload
to use, the compiler looks only at the number and types of the function parameters and arguments. If you
declare two functions with the same name and parameter list but with a different return type, your program will
fail to compile

 Functions are self-contained compact units of code with a well-defined purpose.
A well-written program consists of a large number of small functions, not a small
number of large functions.
• A function definition consists of the function header that specifies the function
name, the parameters, and the return type, followed by the function body containing
the executable code for the function.
• A function prototype enables the compiler to process calls to a function even though
the function definition has not been processed.
• The pass-by-value mechanism for arguments to a function passes copies of the
original argument values, so the original argument values are not accessible from
within the function.
• Passing a pointer to a function allows the function to change the value that is pointed
to, even though the pointer itself is passed by value.
• Declaring a pointer parameter as const prevents modification of the original value.
• You can pass the address of an array to a function as a pointer. If you do, you should
generally pass the array’s length along as well.
• Specifying a function parameter as a reference avoids the copying that is implicit in
the pass-by-value mechanism. A reference parameter that is not modified within a
function should be specified as const.
• Input parameters should be reference-to-const, except for smaller values such as
those of fundamental types. Returning values is generally preferred over output
parameters.
• Specifying default values for function parameters allows arguments to be optionally
omitted.
• Returning a reference from a function allows the function to be used on the left of
an assignment operator. Specifying the return type as a reference-to-const prevents
this.
• The signature of a function is defined by the function name together with the
number and types of its parameters.
• Overloaded functions are functions with the same name but with different
signatures and therefore different parameter lists. Overloaded functions cannot be
differentiated by the return type.
• A recursive function is a function that calls itself. Implementing an algorithm
recursively can result in elegant and concise code. Sometimes, but certainly not
always, this is at the expense of execution time when compared to other methods of
implementing the same algorithm.

 There exist two other cases where a string_view is not exactly equivalent to const string.
First, string_view does not provide a c_str() function to convert it to a const char* array. Luckily, it does
share with std::string its data() function, though, which for most intents and purposes is equivalent.
Second, string_views cannot be concatenated using the addition operator (+). To use a string_view value
my_view in a concatenation expression, you have to convert it to a std::string first, for instance using
std::string{my_view}

 Use std::optional<> to represent any value that may or may not be present.
Examples are optional inputs to a function or the result of a function that may fail.
This makes your code self-documenting and therefore safer.
• Use std::string_view instead of const std::string& to avoid inadvertent copies of
string literals or other character arrays.
• Use std::span<const T> instead of, for instance, const std::vector<T>&
parameters to make the same function work as well for C-style arrays, std::array<>
objects, etc.
• Similarly, use std::span<T> instead of std::vector<T>& parameters, unless you
need the ability to add or remove elements.
• Use std::span<(const) T,N> instead of (const) std::array<T,N>& parameters to
make the same function work for C-style arrays (or other containers you know to
contain at least N elements).

As soon as you add a constructor, any constructor, the compiler no longer implicitly defines a default default
constructor. 
We can still do this to get around that:
 Box() = default; // Defaulted default constructor

 This is more than just a different notation, though. When you initialize a member variable using an
assignment statement in the body of the constructor, the member variable is created (using a constructor
call if it is an instance of a class), after which the assignment is carried out as a separate operation. When
you use an initialization list, the initial value is used to initialize the member variable as it is created. This
can be a much more efficient process, particularly if the member variable is a class instance. This technique
for initializing parameters in a constructor is important for another reason. As you’ll see, it is the only way of
setting values for certain types of member variables.
There is one small caveat to watch out for with initializer lists. The order in which the member variables
are initialized is always determined by the order in which they are declared in the class definition—so not
as you may expect by the order in which they appear in the member initializer list.

 As a rule, it’s better to initialize all member variables either in-class or in the constructor’s member
initializer list. This is generally more efficient. To avoid any confusion, you ideally put the member variables
in the initializer list in the same order as they are declared in the class definition (some compilers will issue a
warning if you don’t). You should initialize member variables in the body of the constructor only if more complex
logic is required or if the order in which the variables are initialized is important.

■ Tip Implicit conversions may lead to confusing code; most of the time it becomes far more obvious why
code compiles and what it does if you use explicit conversions. By default, you should therefore declare singleargument constructors as explicit (note that this includes constructors with multiple parameters where at
least all but the first have default values); omit explicit only if implicit type conversions are truly desirable.
■ Note While less common, any constructor that is not a single-argument constructor can be marked
as explicit as well. Suppose processBox() is a function with a single parameter of type Box or
const Box&, then in modern C++ the expression processBox({ 1.0, 2.0, 3.0 }) is a valid shorthand for
processBox(Box{ 1.0, 2.0, 3.0 }). To prohibit such shorthand notations, and thus to force the explicit
mention of the Box type upon each construction, you can mark the ternary Box(double, double, double)
constructor as explicit

explicit keyword prevents any implicit conversions, useful for single argument constructors where this can happen

 For const objects, you can only call const member functions. You should therefore specify all member
functions that don’t change the object for which they are called as const.

Specifying a member function as const effectively makes the this pointer const for that function

■ Note To preserve const correctness, the following variation of a Box’s getters does not compile:
// Attempt to return non-const references to member variables from const functions
double& length() const { return m_length; }; // This must not be allowed to compile!
double& width() const { return m_width; };
double& height() const { return m_height; };
Because these are const member functions, their implicit this pointers are of type const-pointer-to-Box
(const Box*), which in turn makes the Box member variable names references-to-const within the scope of
these member function definitions. From a const member function, you can thus never return a reference or
a pointer to non-const parts of an object’s states. And this is a good thing. Otherwise, such members would
provide a backdoor to modify a const object

You can declare a whole class to be a friend of another class. All the member functions of a friend class have
unrestricted access to all the members of the class of which it has been declared a friend.
Or just declare a function to be friend in the class

Static member variables of a class are used to provide class-wide storage of data that is independent of any
particular object of the class type but is accessible by any of them. They record properties of the class as a
whole, rather than of individual objects. When you declare a member variable of a class as static, the static
member variable is defined only once and will exist even if no class objects have been created. Each static
member variable is accessible in any object of the class and is shared among however many objects there
are. An object gets its own independent copies of the ordinary member variables, but only one instance of
each static member variable exists, regardless of how many class objects have been defined.

Inline variables have been supported only since C++17. Before C++17, your only option was to
declare s_object_count as follows (this syntax, of course, remains valid today as well):
class Box
{
// ...
private:
 static size_t s_object_count;
// ...
};

Doing so, however, creates somewhat of a problem. How do you initialize a noninline static member variable?
You don’t want to initialize it in a constructor because you want to initialize it only once, not each time a
constructor is called; and anyway, it exists even if no objects exist (and therefore no constructors have been
called). The answer is to initialize each noninline static member outside the class with an extra clumsy
definition such as this:

size_t Box::s_object_count {}; // Initialize static member of Box class to 0

This defines s_object_count; the line in the class definition only declares that it is a noninline static member
of the class—a member that is to be defined elsewhere. Note that the static keyword must not be included in
such an out-of-class definition. You do have to qualify the member name with the class name, Box, though, so
that the compiler understands that you are referring to a static member of the class. Otherwise, you’d simply
be creating a global variable that has nothing to do with the class.

static inline size_t s_object_count {}; // Count of objects in existence

A static member function is independent of any individual class object but can be invoked by any class object
if necessary. It can also be invoked from outside the class if it is a public member. A common use of static
member functions is to operate on static member variables, regardless of whether any objects of the class
have been defined. In general:

■ Tip If a member function does not access any nonstatic member variables, it may be a good candidate for
being declared as a static member function

■ Caution Static member functions cannot be const. Because a static member function isn’t associated with
any class object, it has no this pointer, so const-ness doesn’t apply.

A class provides a way to define your own data types. Classes can represent whatever
types of objects your particular problem requires.

• A class can contain member variables and member functions. The member functions
of a class always have free access to the member variables of the same class.

• Objects of a class are created and initialized using member functions called
constructors. A constructor is called automatically when an object declaration is
encountered. Constructors can be overloaded to provide different ways of initializing
an object.

• A copy constructor is a constructor for an object that is initialized with an existing
object of the same class. The compiler generates a default copy constructor for a
class if you don’t define one.

• Members of a class can be specified as public, in which case they are freely
accessible from any function in a program. Alternatively, they can be specified as
private, in which case they may be accessed only by member functions, friends of
the class, or members of nested classes.

• Member variables of a class can be static. Only one instance of each static
member variable of a class exists, no matter how many objects of the class are
created.

• Although static member variables of a class are accessible in a member function of
an object, they aren’t part of the object and don’t contribute to its size.

• Every non-static member function contains the pointer this, which points to the
current object for which the function is called.

• static member functions can be called even if no objects of the class have been
created. A static member function of a class doesn’t contain the pointer this.

• const member functions can’t modify the member variables of a class object unless
the member variables have been declared as mutable.

• Using references to class objects as arguments to function calls can avoid substantial
overheads in passing complex objects to a function.

• A destructor is a member function that is called for a class object when it is
destroyed. If you don’t define a class destructor, the compiler supplies a default
destructor.

• A nested class is a class that is defined inside another class definition

The copy assignment operator is called under different circumstances than the copy constructor. The
following snippet illustrates this:
Message beware {"Careful"};
Message warning;
warning = beware; // Calls the assignment operator
Message otherWarning{warning}; // Calls the copy constructor

On the third line, you assign a new value to a previously constructed object. This means that the
assignment operator is used. On the last line, however, you construct an entirely new object as a copy of
another. This is thus done using the copy constructor. If you do not use the uniform initialization syntax, the
difference is not always that obvious. It is also legal to rewrite the last line as follows:

Message otherWarning = warning; // Still calls the copy constructor

Programmers sometimes wrongly assume that this form is equivalent to a copy assignment to an
implicitly default-constructed Message object. But that’s not what happens. Even though this statement
contains an equals sign, the compiler will still use the copy constructor here, not an assignment. Assignment
operators come into play only when assigning to existing objects that were already constructed earlier.

 To prevent copying, always delete both copy members. Deleting only the copy constructor or deleting
only the copy assignment operator is rarely a good idea.

• You can overload any number of operators within a class to provide class-specific
behavior. You should do so only to make code easier to read and write.

• Overloaded operators should mimic their built-in counterparts as much as possible.
Popular exceptions to this rule are the << and >> operators for Standard Library
streams and the + operator to concatenate strings.

• Operator functions can be defined as members of a class or as global operator
functions. You should use member functions whenever possible. You should resort
to global operator functions only if there is no other way or if implicit conversions are
desirable for the first operand.

• For a unary operator defined as a class member function, the operand is the class
object. For a unary operator defined as a global operator function, the operand is the
function parameter.

• For a binary operator function declared as a member of a class, the left operand
is the class object, and the right operand is the function parameter. For a binary
operator defined by a global operator function, the first parameter specifies the left
operand, and the second parameter specifies the right operand.

• If you overload operators == and <=>, you get operators !=, <, >, <=, and >= all for free.
In many cases you can even have the compiler generate the code for you.

• Functions that implement the overloading of the += operator can be used in the
implementation of the + function. This is true for all op= operators.

• To overload the increment or the decrement operator, you need two functions that
provide the prefix and postfix form of the operator. The function to implement a
postfix operator has an extra parameter of type int that serves only to distinguish the
function from the prefix version.

• To support customized type conversions, you have the choice between conversion
operators or a combinatiomn of conversion constructors and assignment operators

First let’s consider how private members of a base class are inherited in a derived class. Regardless
of the base class access specifier (public, protected, or private), a private base class member always
remains private to the base class. As you have seen, inherited private members are private members
of the derived class, so they’re inaccessible outside the derived class. They’re also inaccessible to member
functions of the derived class because they’re private to the base class.
Now, let’s look into how public and protected base class members are inherited. In all the remaining
cases, inherited members can be accessed by member functions of the derived class. The inheritance of
public and protected base class members works like this:
1. When the base class specifier is public, the access status of the inherited
members remains unchanged. Thus, inherited public members are public, and
inherited protected members are protected in a derived class.
2. When the base class specifier is protected, both public and protected
members of a base class are inherited as protected members.
3. When the base class specifier is private, inherited public and protected
members become private to the derived class, so they’re accessible by member
functions of the derived class but cannot be accessed if they’re inherited in
another derived class

. Creating each Carton object always results
in the default constructor of Box being called first, followed by the Carton class constructor.
Derived class objects are always created this way, even when there are several levels of derivation.
Every constructor of a derived class always starts by invoking a constructor of its base class. And that base
class constructor then invokes the constructor of its base class, and so on, until a class is reached that is not
derived from any other class. The effect is that the first constructor to be fully evaluated is that of the most
base class constructor, followed by the constructor for the class derived from that, and so on, until finally the
constructor for the most derived class is evaluated. This makes sense if you think about it. A derived class
object has a complete base class object inside it, and this needs to be created before the rest of the derived
class object. If that base class is derived from another class, the same applies

The order of destructor calls for a derived class object is the reverse of the constructor call sequence for the
object. The derived class destructor is called first, and then the base class destructor is called,

Every derived class object has a base class object inside it waiting to get out. Conversions from a derived type
to its base are always legal and automatic. Here’s a definition of a Carton object:
Carton carton{40, 50, 60, "Corrugated fiberboard"};
We have already seen two ways this object can be converted to a base class object of type Box. The first is
by means of a copy constructor:
Box box{carton};

And the second is a copy assignment:
Box box;
box = carton;
Both convert the carton object to a new object of type Box and store a copy of it in box. The assignment
operator that is used is the default assignment operator for the Box class. Of course, only the Box subobject
part of carton is used; a Box object has no room for the Carton-specific member variables. This effect is
called object slicing, as the Carton specific portion is sliced off, so to speak, and discarded.

Inheritance is a fundamental characteristic of objectoriented programming, and it makes polymorphism possible (polymorphism is the subject of the next
chapter). The important points to take from this chapter include the following:
• A class may be derived from one or more base classes, in which case the derived
class inherits members from all of its bases.
• Single inheritance involves deriving a class from a single base class. Multiple
inheritance involves deriving a class from two or more base classes.
• Access to the inherited members of a derived class is controlled by two factors: the
access specifier of the member in the base class and the access specifier of the base
class in the derived class declaration.

• A constructor for a derived class is responsible for initializing all members of the
class. This normally involves invoking a constructor of the base class to initialize all
inherited members.
• Creation of a derived class object always involves the constructors of all of the direct
and indirect base classes, which are called in sequence (from the most base through
to the most direct) prior to the execution of the derived class constructor.
• A derived class constructor can, and often should, explicitly call constructors for its
direct bases in the initialization list for the constructor. If you don’t call one explicitly,
the base class’s default constructor is called. A copy constructor in a derived class, for
one, should always call the copy constructor of all direct base classes.
• A member name declared in a derived class, which is the same as an inherited
member name, will hide the inherited member. To access the hidden member, use
the scope resolution operator to qualify the member name with its class name.
• You can use using not only for type aliases but also to inherit constructors (always
with the same access specification as in the base class), to modify the access
specifications of other inherited members, or to inherit functions that would
otherwise be hidden by a derived class’s function with the same name but different
signature.
• When a derived class with two or more direct base classes contains two or more
inherited subobjects of the same class, the duplication can be prevented by declaring
the duplicated class as a virtual base class.

 In C++, polymorphism always involves the use of a pointer or a reference to an object to call a member function. Polymorphism only operates with classes that share a common base class.

 w an object of a derived class type contains a subobject of the base class
type. In other words, you can regard every derived class object as a base class object. Because of this, you
can always use a pointer to a base class to store the address of a derived class object; in fact, you can use a
pointer to any direct or indirect base class to store the address of a derived class object
The reverse is not true.

A function that you specify as virtual in a base class will be virtual in all classes that are directly or
indirectly derived from the base. This is the case whether or not you specify the function as virtual in a
derived class. To obtain polymorphic behavior, each derived class may implement its own version of the
virtual function

Note that a call to a virtual function using an object is always resolved statically. You only get dynamic
resolution of calls to virtual functions through a pointer or a reference. Storing an object of a derived class
type in a variable of a base type will result in the derived class object being sliced, so it has no derived class
characteristics

If a member function definition is outside the class definition, you must not add the virtual
keyword to the function definition; it would be an error to do so. You can only add virtual to declarations or
definitions inside a class definition

For a function to behave “virtually,” its definition in a derived class must have the same signature as it has in
the base class. If the base class function is const, for instance, then the derived class function must therefore
also be const. Generally, the return type of a virtual function in a derived class must be the same as that
in the base class as well, but there’s an exception when the return type in the base class is a pointer or a
reference to a class type. In this case, the derived class version of a virtual function may return a pointer or a
reference to a more specialized type than that of the base. We won’t be going into this further, but in case you
come across it elsewhere, the technical term used in relation to these return types is covariance

static member functions cannot be virtual. As their name suggests, calls of static functions are
always resolved statically. Even if you call a static member function on a polymorphic object, the member
function is resolved using the static type of the object. This gives us yet another reason to always call static
member functions by prefixing them with the class name instead of that of an object. That is, always use
MyClass::myStaticFunction() instead of myObject.myStaticFunction(). This makes it crystal clear not to
expect polymorphism

The override specification, like the virtual one, only appears within the class definition. It must not
be applied to an external definition of a member function. The override specification causes the compiler to
verify that the base class declares a class member that is virtual and has the same signature. If it doesn’t, the
compiler flags the definition containing the override specification as an error (give it a try!).
■ Tip Always add an override specification to the declaration of a virtual function override. First, this
guarantees that you have not made any mistakes in the function signatures at the time of writing. Second, and
perhaps even more important, it safeguards you and your team from forgetting to change any existing function
overrides when the signature of the base class function changes

In principle you could declare a member function that is both virtual and final even if it does not
override any base class member. This would be self-contradictory, though. You add virtual to allow function
overrides, and you add final to prevent them. Note that there is no contradiction in combining override and
final. This just states that you disallow any further overrides of the function you are overriding.

In a way, private virtual functions give you the best of two worlds. On one hand, the function is
private, meaning it cannot be called from outside your class. On the other hand, the function is virtual,
allowing derived classes to override and customize its behavior. In other words, even though you facilitate
polymorphism, you are still in perfect control where and when such a private virtual member function
is called. This function could be a single step in a more complex algorithm, a step that is to be executed
only after all the previous steps of the algorithm have been correctly performed. Or it could be a function
that must to be called only after acquiring a particular resource, for instance after performing the necessary
thread synchronization.

To ensure that the correct destructor is always called for objects of derived classes that are allocated in the
free store, you need virtual class destructors. To implement a virtual destructor in a derived class, you just
add the keyword virtual to the destructor declaration in the base class. This signals to the compiler that
destructor calls through a pointer or a reference parameter should have dynamic binding, so the destructor
that is called will be selected at runtime. This makes the destructor in every class derived from the base class
virtual, in spite of the derived class destructors having different names; destructors are treated as a special
case for this purpose.

A dynamic cast is a conversion that’s performed at runtime. The dynamic_cast<>() operator performs a
dynamic cast. You can only apply this operator to pointers and references to polymorphic class types, which
are class types that contain at least one virtual function. The reason is that only pointers to polymorphic
class types contain the information that the dynamic_cast<>() operator needs to check the validity of the
conversion. This operator is specifically for the purpose of converting between pointers or references to class
types in a hierarchy. Of course, the types you are casting between must be pointers or references to classes
within the same class hierarchy. You can’t use dynamic_cast<>() for anything else.

■ Caution Virtual function calls made from inside a constructor or a destructor are always resolved statically.
If you, in rare cases, do need polymorphic calls during initialization, you should do so from within an init()
member function—often virtual itself—that you then call after the construction of the object has completed.
This is called the dynamic binding during initialization idiom

You pay for
polymorphism in two ways: it requires more memory, and virtual function calls result in additional runtime
overhead. These consequences arise because of the way that virtual function calls are typically implemented
in practice. Luckily, both costs are mostly marginal at best and can mostly be ignored.
For instance, suppose two classes, A and B, contain identical member variables, but A contains virtual
functions, whereas B’s functions are all nonvirtual. In this case, an object of type A requires more memory
than an object of type B.
■ Note You can create a simple program with two such class objects and use the sizeof operator to see the
difference in memory occupied by objects with and without virtual functions
.
The reason for the increase in memory is that when you create an object of a polymorphic class type, a
special pointer is created in the object. This pointer is used to call any of the virtual functions in the object.
The special pointer points to a table of function pointers that gets created for the class. This table, usually
called a vtable, has one entry for each virtual function in the class.

When a function is called through a pointer to a base class object, the following sequence of events occurs:
1. The pointer to the vtable in the object pointed to is used to find the beginning of
the vtable for the class.
2. The entry for the function to be called is found in the vtable, usually by
using an offset.
3. The function is called indirectly through the function pointer in the vtable. This
indirect call is a little slower than a direct call of a nonvirtual function, so each
virtual function call carries some overhead.
However, the overhead in calling a virtual function is small and shouldn’t give you cause for concern.
A few extra bytes per object and slightly slower function calls are small prices to pay for the power and
flexibility that polymorphism offers. This explanation is just so you’ll know why the size of an object that has
virtual functions is larger than that of an equivalent object that doesn’t.
■ Note The only time you should even debate whether the overhead of a virtual function table pointer is
worth it is when you have to manage many objects of the corresponding type at once. Suppose you have a
Point3D class that represents a point in 3D space. If your program manipulates millions and millions of such
points—a Microsoft Kinect, for instance, produces up to 9 million points per second—then avoiding virtual
functions in Point3D can save you a significant amount of memory. For most objects, the cost of a virtual
function table pointer is only marginal, though, and well worth the benefits

The purpose of a pure virtual function is to enable the derived class versions of the function to be called
polymorphically. To declare a pure virtual function rather than an “ordinary” virtual function that has a
definition, you use the same syntax but add = 0 to its declaration within the class

This raises the question, “If you can’t create an instance of an abstract class, then why does the abstract
class contain a constructor?” The answer is that the constructor for an abstract class is there to initialize
its member variables. The constructor for an abstract class will be called by a derived class constructor,
implicitly or from the constructor initialization list. If you try to call the constructor for an abstract class from
anywhere else, you’ll get an error message from the compiler.
Because the constructor for an abstract class can’t be used generally, it’s a good idea to declare it as
a protected member of the class,

Polymorphism involves calling a (virtual) member function of a class through
a pointer or a reference and having the call resolved dynamically. That is, the
particular function to be called is determined by the object that is pointed to or
referenced when the program is executing.
• A function in a base class can be declared as virtual. All occurrences of the function
in classes that are derived from the base will then be virtual too.
• You should always declare the destructor of classes intended to be used as a base
class as virtual (often this can be done in combination with = default). This
ensures correct selection of a destructor for dynamically created derived class
objects. It suffices to do so for the most base class, but it does not hurt to do it
elsewhere either.
• You should use the override qualifier with each member function of a derived class
that overrides a virtual base class member. This causes the compiler to verify that
the functions signatures in the base and derived classes are, and forever remain, the
same.
• The final qualifier may be used on an individual virtual function override to signal
that it may not be overridden any further. If an entire class is specified to be final,
no derived classes can be defined for it anymore.
• Default argument values for parameters in virtual functions are assigned statically,
so if default values for a base version of a virtual function exist, default values
specified in a derived class will be ignored for dynamically resolved function calls.
• The dynamic_cast<> operator is generally used to cast from a pointer-to-apolymorphic-base-class to a pointer-to-a-derived-class. If the pointer does not point
to an object of the given derived class type, dynamic_cast<> evaluates to nullptr.
This type check is performed dynamically, at runtime.
• A pure virtual function has no definition. A virtual function in a base class can be
specified as pure by placing = 0 at the end of the member function declaration.
• A class with one or more pure virtual functions is called an abstract class, for
which no objects can be created. In any class derived from an abstract class, all the
inherited pure virtual functions must be defined. If they’re not, it too becomes an
abstract class, and no objects of the class can be created

 The golden rule for exceptions is to always throw by value and catch by reference (reference-to-const,
normally). In other words, you mustn’t throw a new’ed exception (and definitely no pointer to a local object), nor
should you ever catch an exception object by value. Obviously, catching by value would result in a redundant
copy, but that’s not the worst of it. Catching by value may slice off parts of the exception object. The reason this
is so important is that this might slice off precisely that valuable piece of information that you need to diagnose
which error occurred and why

With exceptions that are basic types (rather than class types), an exact type match with the parameter in
the catch block is necessary. With exceptions that are class objects, implicit conversions may be applied to
match the exception type with the parameter type of a handler. When the parameter type is being matched
to the type of the exception that was thrown, the following are considered to be a match:
• The parameter type is the same as the exception type, ignoring const.
• The type of the parameter is a direct or indirect base class of the exception class type,
or a reference to a direct or indirect base class of the exception class, ignoring const.
• The exception and the parameter are pointers, and the exception type can be
converted implicitly to the parameter type, ignoring const.
The possible type conversions listed here have implications for how you sequence the catch blocks for
a try block. If you have several handlers for exception types within the same class hierarchy, then the most
derived class type must appear first and the most base class type last. If a handler for a base type appears
before a handler for a type derived from that base, then the base type is always selected to handle the derived
class exceptions. In other words, the handler for the derived type is never executed.

Let’s add a couple more exception classes to the module containing the Trouble class and use Trouble
as a base class for them. Here’s how the contents of the module file will look with the extra classes defined:
// troubles.cppm - Exception classes
export module troubles;
import <string>;
import <string_view>;
export class Trouble
{
public:
 explicit Trouble(std::string_view message = "There's a problem")
 : m_message {message}
 {}
 virtual ~Trouble() = default; // Base classes must have a virtual destructor!
 virtual std::string_view what() const { return m_message; }
private:
 std::string m_message;
};
// Derived exception class
export class MoreTrouble : public Trouble
{
public:
 explicit MoreTrouble(std::string_view str = "There's more trouble...")
 : Trouble {str}
 {}
};
// Derived exception class
export class BigTrouble : public MoreTrouble
{
public:
 explicit BigTrouble(std::string_view str = "Really big trouble...")
 : MoreTrouble {str}
 {}
};
Note that the what() member and the destructor of the base class have been declared as virtual.
Therefore, the what() function is also virtual in the classes derived from Trouble. It doesn’t make much
of a difference here, but it would in principle allow derived classes to redefine what(). Remembering to
declare a virtual destructor in a base class is important, though. Other than different default strings for the
message, the derived classes don’t add anything to the base class. Often, just having a different class name
can differentiate one kind of problem from another. You just throw an exception of a particular type when
that kind of problem arises; the internals of the classes don’t have to be different. Using a different catch
block to catch each class type provides the means to distinguish different problems. Here’s the code to throw
exceptions of the Trouble, MoreTrouble, and BigTrouble types, as well as the handlers to catch them:
// Ex16_03.cpp
// Throwing and catching objects in a hierarchy
import <iostream>;
import troubles;

int main()
{
 for (int i {}; i < 7; ++i)
 {
 try
 {
 if (i == 3)
 throw Trouble{};
 else if (i == 5)
 throw MoreTrouble{};
 else if (i == 6)
 throw BigTrouble{};
 }
 catch (const BigTrouble& t)
 {
 std::cout << "BigTrouble object caught: " << t.what() << std::endl;
 }
 catch (const MoreTrouble& t)
 {
 std::cout << "MoreTrouble object caught: " << t.what() << std::endl;
 }
 catch (const Trouble& t)
 {
 std::cout << "Trouble object caught: " << t.what() << std::endl;
 }
 std::cout << "End of the for loop (after the catch blocks) - i is " << i << std::endl;
 }
}

Here’s the output:
End of the for loop (after the catch blocks) - i is 0
End of the for loop (after the catch blocks) - i is 1
End of the for loop (after the catch blocks) - i is 2
Trouble object caught: There's a problem
End of the for loop (after the catch blocks) - i is 3
End of the for loop (after the catch blocks) - i is 4
MoreTrouble object caught: There's more trouble...
End of the for loop (after the catch blocks) - i is 5
BigTrouble object caught: Really big trouble...
End of the for loop (after the catch blocks) - i is 6

Inside the for loop, objects of type Trouble, MoreTrouble, and BigTrouble are thrown as an exception.
These objects are constructed at the moment they are thrown, as is often the case with exceptions. The type
of object that is thrown depends on the value of the loop variable, i. Each of the catch blocks contains a
different message, so the output shows which catch handler is selected when an exception is thrown. In
the handlers for the two derived types, the inherited what() function still returns the message. Note that the
parameter type for each of the catch blocks is a reference, as in the previous example. One reason for using
a reference is to avoid making an unnecessary copy of the exception object. In the next example, you’ll see
another, more crucial reason why you should always use a reference parameter in a handler

Exceptions of derived class types are implicitly converted to a base class type for the purpose of matching
a catch block parameter, so you could catch all the exceptions thrown in the previous example with a
single handler

If a thrown exception is not caught, either directly or indirectly (that is, it does not have to be caught within
the same function, as we discussed earlier), then the program is terminated instantly. And you really should
expect such a termination to be fairly abrupt. Destructors for static objects will not get called anymore, for
one; there is no guarantee that the destructors of any objects still allocated on the call stack will be executed.
In other words, the program essentially instantly crashes.
■ Note In actuality, if an exception goes uncaught, the Standard Library function std::terminate() is called
(declared in the <exception> module), which in turn by default calls std::abort() (declared in <cstdlib>), which
then terminates the program. This sequence of events for an uncaught exception is shown in Figure 16-7.
It is technically possible to override the behavior of std::terminate() by passing a function pointer to
std::set_terminate(). However, this is rarely recommended and should be reserved for (pun intended…)
exceptional cases. There is also not that much you are allowed to do in a terminate handler. Acceptable uses
include making sure that certain critical resources are properly cleaned up or writing a so-called crash dump
that your customers can then send to you for further diagnosis. These topics are too advanced for this book
to warrant further discussion though. One thing you must never do is attempt to keep your program running
after std::terminate() is called! std::terminate(), by definition, is invoked after an irrecoverable error;
any attempt to recover results in undefined behavior. Your terminate handler must always end with one of two
function calls: either std::abort() or std::_Exit().

 Both functions end the program without performing
any further cleanup (the difference between the two is that with the latter you can decide which error code the
process returns to the environment).

■ Caution If your code will throw exceptions of different types, it may be tempting to use a catch-all block to
catch them all at once. After all, it’s less work than enumerating catch blocks for every possible exception type.
Similarly, if you’re calling functions that you’re less familiar with, quickly adding a catch-all block is much easier
than researching which exception types these functions may throw. This is rarely the best approach though. A
catch-all block risks catching exceptions that need more specific handling, or sweeping unexpected, dangerous
errors under the rug. They also do not allow for much error logging or diagnosis. All too often we encounter
patterns such as this in code:
try
{
 doSomething();
}
catch (...)
{
 // Oops. Something went wrong... Let's ignore what happened and cross our fingers...
}
The comments usually don’t actually contain the part about ignoring the error and crossing your fingers,
but they might as well. The motivation behind such patterns is generally “Anything is better than uncaught
exceptions.” The truth of the matter is that this is mostly just a symptom of a lazy programmer. There is no
substitute for proper, thought-through error-handling code when it comes to delivering stable, fault-tolerant
programs. And like we said in the introduction of this chapter, writing error-handling and recovery code will
take time. So while catch-all blocks may be tempting shortcuts, it’s usually preferred to explicitly check which

exception types may be raised by the functions that you call and, for each, to consider whether you should add
a catch block and/or leave it to a calling function to handle the exception. Once you know the exception type,
you can usually extract more useful information from the object (like with the what() function of our Trouble
class) and use this for proper error handling and logging. Note also that, especially during development, a
program crash is actually better than a catch-all. Then at least you learn about potential errors, instead of
blindly ignoring them, and can adjust your code to properly prevent them or recover from them.
Make no mistake, we do not mean to say that catch-all blocks should never be used—they certainly have their
uses. Catch-all blocks that rethrow after some logging or cleanup, for instance, can be particularly useful. We
just want to caution you against using them as an easy, subpar substitute for more targeted error handling.

If you see a noexcept in a function’s header, you can be sure that this function will never throw an
exception. The compiler makes sure that if a noexcept function does unwittingly throw an exception that’s
not caught within the function itself, the exception will not be propagated to the calling function at runtime.
Instead, the C++ program will treat this as an irrecoverable error and call std::terminate(). As discussed
earlier in this chapter, std::terminate() always results in an abrupt termination of the process.
Note that this does not mean that no exceptions are allowed to be thrown within the function itself;
it only means that no exception will ever escape the function. That is, if an exception is thrown during the
execution of a noexcept function, it must be caught somewhere within that function and not rethrown. 

Starting with C++11, destructors are normally implicitly noexcept. Even if you define a destructor without a
noexcept specification, the compiler will normally add one implicitly. This means that should the destructor
of the following class be executed, the exception will never leave the destructor. Instead, std::terminate()
shall always be called (in accordance with the implicit noexcept specifier added by the compiler):

It is in principle possible to define a destructor from which exceptions may be thrown. You could do so
by adding an explicit noexcept(false) specification. But since you should normally never do this,2
 we won’t
discuss or consider this possibility any further.
■ Tip  Never allow an exception to leave a destructor. All destructors are normally3 noexcept, even if not
specified as such explicitly, so any exception they throw will trigger a call to std::terminate().

One of the hallmarks of modern C++ is the so-called RAII idiom, short for “resource acquisition is
initialization.” Its premise is that each time you acquire a resource you should do so by initializing an object.
Memory in the free store is a resource, but other examples include file handles (while holding these, other
processes often may not access a file), mutexes (used for synchronization in concurrent programming),
network connections, and so on. As per RAII, every such resource should be managed by an object, either
allocated on the stack or as a member variable. The trick to avoid resource leaks is then that, by default, the
destructor of that object makes sure the resource is always freed.

The body of main() is a try block, and its catch block catches any type of exception that has
std::exception as a base.

When throwing exceptions, always throw objects, never fundamental types. And the class of these
objects should always derive from std::exception, either directly or indirectly. Even if you declare your own
application-specific exception hierarchies—which often is a good idea—you should use std::exception or
one of its derived classes as the base class. Many popular C++ libraries already follow this same guideline.
Using only a single, standardized family of exceptions makes it much easier to catch and handle these
exceptions.
Summary
Exceptions are an integral part of programming in C++. Several operators throw exceptions, and you’ve seen
that they’re used extensively within the Standard Library to signal errors. Therefore, it’s important that you
have a good grasp of how exceptions work, even if you don’t plan to define your own exception classes. The
important points that we’ve covered in this chapter are as follows:
• Exceptions are objects that are used to signal errors in a program.
• Code that may throw exceptions is usually contained within a try block, which
enables an exception to be detected and processed within the program.
• The code to handle exceptions that may be thrown in a try block is placed in one or
more catch blocks that must immediately follow the try block.
• A try block, along with its catch blocks, can be nested inside another try block.
• A catch block with a parameter of a base class type can catch an exception of a
derived class type.
• A catch block with the parameter specified as an ellipsis will catch an exception of
any type.
• If an exception isn’t caught by any catch block, then the std::terminate() function
is called, which immediately aborts the program execution.
• Every resource, including dynamically allocated memory, should always be acquired
and released by an RAII object. This implies that, as a rule, you should normally no
longer use the keywords new and delete in modern C++ code.
• The Standard Library offers various RAII types you should use consistently; the ones
you already know about include std::unique_ptr<>, shared_ptr<>, and vector<>.
• The noexcept specification for a function indicates that the function does not
throw exceptions. If a noexcept function does throw an exception it does not catch,
std::terminate() is called.
• Even if a destructor does not have an explicit noexcept specifier, the compiler will
almost always generate one for you. This implies that you must never allow an
exception to leave a destructor; otherwise, std::terminate() will be triggered.
• The Standard Library defines a range of standard exception types in the <stdexcept>
module that are derived from the std::exception class that is defined in the
<exception> module

Every single expression is either an lvalue or an rvalue (sometimes written l-value and r-value and
pronounced like that). An lvalue evaluates to some persistent value with an address in memory in which
you can store something on an ongoing basis; an rvalue evaluates to a result that is stored only transiently.
Historically, lvalues and rvalues are so called because an lvalue expression typically appears on the left of an
assignment operator, whereas an rvalue could appear only on the right side. If an expression is not an lvalue,
it is an rvalue.
 An expression that consists of a single variable name is always an lvalue.

 Most function call expressions are rvalues. Only function calls that return a reference are lvalues.
One indication for the latter is that function calls that return a reference can appear on the left side of a built-in
assignment operator just fine. Prime examples are the subscript operators (operator[]()) and at() functions
of your typical container. If v is a vector<int>, for example, both v[1] = -5; and v.at(2) = 132; would make
for perfectly valid statements. v[1] and v.at(2) are therefore clearly lvalues.
When in doubt, another good guideline to decide whether a given expression is either an lvalue or an
rvalue is the following. If the value that it evaluates to persists long enough for you to take and later use its
address, then that value is an lvalue. Here’s an example (a, b, and c are ints as before, and v a vector<int>):
int* x = &(b + c); // Error!
int* y = &std::abs(a * c); // Error!
int* z = &123; // Error!
int* w = &a; // Ok!
int* u = &v.at(2); // Ok! (u contains the address of the third value in v)

A reference is a name that you can use as an alias for something else. What you don’t know yet—how could you?—is that there are actually two kinds of references:
lvalue references and rvalue references.
All references that you’ve worked with thus far are lvalue references. Normally, an lvalue reference
is an alias for another variable; it is called an lvalue reference because it normally refers to a persistent
storage location in which you can store data so it can appear on the left of an assignment operator. We say
“normally” because C++ does allow reference-to-const lvalue references—so variables of type const T&—to
be bound to temporary rvalues as well. 
An rvalue reference can be an alias for a variable, just like an lvalue reference, but it differs from an
lvalue reference in that it can also reference the outcome of an rvalue expression, even though this value
is generally transient. Being bound to an rvalue reference extends the lifetime of such a transient value. Its
memory will not be discarded as long as the rvalue reference is in scope. You specify an rvalue reference
type using two ampersands following the type name. Here’s an example:
int count {5};
int&& rtemp {count + 3}; // rvalue reference
std::cout << rtemp << std::endl; // Output value of expression
int& rcount {count}; // lvalue reference
This code will compile and execute, but of course it is definitely not the way to use an rvalue reference,
and you should never code like this.

A shallow copy simply copies all members of an object one by one, even if these members are pointers to dynamic memory. A deep
copy, on the other hand, copies all dynamic memory referred to by any of its pointer members as well.

s: You can turn any lvalue into an rvalue reference simply by applying
one of C++11’s most vital Standard Library functions: std::move().
2
 To see its effect, you should first replace
the final two lines of main() in Ex18_03.cpp with the following and then run the program again (you can find
this variant in Ex18_04):
 ...
 Array<std::string> more_strings{ 2'000 };
 strings = std::move(more_strings); // Move more_strings into strings
}
If you do, you will notice that more_strings is indeed no longer copied:
Array of 1000 elements moved (assignment)
Array of 2000 elements moved (assignment

No discussion of std::move() is complete without an honorary mention of std::unique_ptr<>—
undoubtedly the type whose variables you’ll be moving the most in modern C++ programming. As
explained in Chapter 6, there must never be two unique_ptr<> smart pointers pointing to the same address
in memory. Otherwise, both would delete (or delete[]) the same raw pointer twice, which is a perfect
way to initiate a tragic failure of your program. It is thus only fortunate that neither of the two lines that are
commented out at the end of the following code snippet compiles:
std::unique_ptr<int> one{ std::make_unique<int>(123) };
std::unique_ptr<int> other;
 other = one; /* Error: copy assignment operator is deleted! */
// std::unique_ptr<int> yet_another{ other }; /* Error: copy constructor is deleted! 
//What would compile, however, are these two lines :
//other = std::move(one); // Move assignment operator is defined
//std::unique_ptr<int> yet_another{ std::move(other) }; // Move constructor is defined

/*

. This is an outline of how
you’d normally accomplish this:
namespace std
{
 template <typename T>
 class unique_ptr
 {
 ...
Technically, std::move() is defined in the <utility> module. In practice, though, you’ll rarely have to explicitly import
this module to use std::move().

 // Prevent copying:
 unique_ptr(const unique_ptr&) = delete;
 unique_ptr& operator=(const unique_ptr&) = delete;
 // Allow moving:
 unique_ptr(unique_ptr&& source);
 unique_ptr& operator=(unique_ptr&& rhs);
 ...
 };
}

n As a rule, you should only move an object if you are absolutely sure it is no longer required. Unless
otherwise specified, you’re not supposed to keep on using an object that was moved. By default, any extended
use of a moved object results in undefined behavior (read: it’ll often result in crashes)

Make no mistake, std::move() does not move anything. All this function does is turn a given lvalue into an
rvalue reference. std::move() is effectively nothing more than a type conversion, not at all unlike built-in
cast operators static_cast<>() and dynamic_cast<>().

For fundamental types and pointers, you can simply use pass-by-value. For objects that are more 
expensive to copy, you should normally use a const T& parameter. This avoids any lvalue arguments from being 
copied, and rvalue arguments will bind just fine with a const T& parameter as well. If your function inherently 
copies its T argument, however, you should pass it by value instead. Lvalue arguments will then be copied when 
passed to the function, and rvalue arguments will be moved. The latter guideline presumes that the parameter 
types support move semantics—as all types should these days. In the less likely case that the parameter type 
lacks proper move members, you should stick with pass-by-reference. More and more types support move 
semantics these days, though—not in the least all Standard Library types—so pass-by-value is most certainly 
back on the table!

s. The idea of move operations is that since
the argument is temporary, the function doesn’t necessarily need to copy data members; it can instead steal
the data from the object that is the argument. If members of the argument object are pointers, for example,
the pointers can be transferred without copying what they point to because the argument object will be
destroyed and so doesn’t need them.
The important points and best-practice guidelines from this chapter include the following:
• An rvalue is an expression that typically results in a temporary value; an lvalue is one
that results in a more persistent value.
• std::move() can be used to convert an lvalue (such as a named variable) into an
rvalue. Take care, though. Once moved, an object should normally not be used
anymore.
• An rvalue reference type is declared using a double ampersand, &&.
• The move constructor and move assignment operator have rvalue reference
parameters, so these will be called when the argument is a temporary (or any other
rvalue).
• If a function inherently copies one of its inputs, passing this argument by value is
preferred, even this if concerns an object of a class type. By doing so, you can cater to
both lvalue and rvalue inputs with one single function definition.
• Automatic variables and function parameters should be returned by value and
without adding std::move() to the return statement.
• Move members should normally be noexcept; if not, they risk not being invoked by
Standard Library containers and other templates.
• The rule of five entails that you either declare all copy members, move members, and
the destructor together, or none of them at all. The rule of zero urges you to strive to
define none at all. The means to achieve rule of zero compliance you actually already
know: always manage dynamic memory and other resources using smart pointers,
containers, and other RAII techniques

template <typename T>
void Array<T>::push_back(const T& element)
{
...
 newArray[m_size] = element; // Copy the new element...
...
}
Your first instinct might be to simply slap another std::move() onto element, like so:
template <typename T>
void Array<T>::push_back(const T& element)
{
...
 newArray[m_size] = std::move(element); // Move the new element... (???)
...
}
This will not work, though, and with good reason. element is a reference to a const T, meaning that
the caller of the function expects the argument not to be modified. Moving its contents into another object
is therefore completely out of the question. This is also why the std::move() type conversion function will
never cast a const T or const T& type to T&&. Instead, std::move() converts it to the rather pointless type
const T&&—a reference to a transient value that you’re not allowed to modify. In other words, because the
type of element is const T&, the type of std::move(element) is const T&&, meaning that assigning the latter
expression still goes through the copy assignment operator, despite the std::move().
But of course you still want to cater to those cases where the caller does not need the element argument
anymore—that is, for those cases where push_back() is called with an rvalue. Luckily, you cannot only use
rvalue reference parameters for move constructors and move assignment operators; you can use them for
any function you want. And so you could easily add an extra overload of push_back() that accepts rvalue
arguments:
template <typename T>
void Array<T>::push_back(T&& element)
{
...
 newArray[m_size] = std::move(element); // Move the new element...
...
}

■ Caution When passing an argument such as element by rvalue reference, never forget that inside the
function’s body the expression element is again an lvalue. Remember, any named variable is an lvalue, even if
the variable itself has an rvalue reference type! In our push_back() example, this means that the std::move()
in the function’s body is very much required to compel the compiler into choosing T’s move assignment
operator rather than its copy assignment operator.

Here’s a definition of a pointer that can store the address of functions that have parameters of type long* and
int and return a value of type long:
long (*fun_ptr)(long*, int); // Variable fun_ptr (pointer to function that returns long)
This may look a little weird at first because of all the parentheses. The name of the pointer variable is
fun_ptr. It doesn’t point to anything because it is not initialized. Ideally, it would be initialized to nullptr
or with the address of a specific function. The parentheses around the pointer name and the asterisk are
essential. Without them, this statement would declare a function rather than define a pointer variable
because the * will bind to the type long:
long *fun_ptr(long*, int); // Prototype for a function fun_ptr() that returns long*

 Even though the name of a function already evaluates to a value of a function pointer type, you can
also explicitly take its address using the address-of operator, &. The following statements, in other words, have
the same effect as the earlier ones:
auto* fun_ptr = &findMaximum;
fun_ptr = &findMinimum

Pointer to function is a perfectly reasonable type, which means a function can have a parameter of this
type as well. The function can then use its pointer to function parameter to call the function to which the
argument points when the function is called. You can specify just a function name as the argument for a
parameter that is a “pointer to function” type. A function passed to another function as an argument is
referred to as a callback function; the function that accepts another function as an argument is a higher-order
function. Consider the following example:
// Optimum.cppm - a function template to determine the optimum element in a given vector
export module optimum;
import <vector>;
export template <typename T>
const T* findOptimum(const std::vector<T>& values, bool (*compare)(const T&, const T&))
{
 if (values.empty()) return nullptr;

 const T* optimum = &values[0];
 for (size_t i {1}; i < values.size(); ++i)
 {
 if (compare(values[i], *optimum))
 optimum = &values[i];
 }
 return optimum;
}
This higher-order function template generalizes the findMaximum() and findMinimum() functions we
alluded to earlier. The function pointer you pass to the compare parameter determines which “optimum”
is computed. The parameter’s type forces you to pass a pointer to a function that takes two T values as
input and returns a Boolean. This pointed-to function is expected to compare two T values and evaluate
whether the first one is somehow “better” than the second one. The higher-order findOptimum() function
then repeatedly calls the given comparison function through its compare parameter and uses the results to
determine which, out of all the T values in its vector argument, is best or optimal.
The key point is that you, as the caller of findOptimum(), determine what it means for one T value to be
better or more optimal than the other. If it’s the minimum element you want you pass a comparison function
equivalent to the less-than operator; if it’s the maximum element you want the compare callback to behave
like the greater-than operator; and so on. 

Just like pointers to data values, pointers to functions are low-level language constructs that C++ has inherited
from the C programming language. And just like raw pointers, function pointers have their limitations, which
can be overcome using an object-oriented approach. In this section we introduce a similar technique
where objects are used as a more powerful alternative to plain C-style function pointers. These objects are
called function objects or functors (the two terms are synonymous). Like a function pointer, a function object
acts precisely like a function; but unlike a raw function pointer, it is a full-fledged class type object—complete
with its own member variables and possibly even various other member functions.
A function object or functor is an object that can be called as if it were a function. The key in constructing one
is to overload the function call operator

This is where lambda expressions come in. They offer you a convenient, compact syntax to quickly
define callback functions or functors. And not only is the syntax compact, lambda expressions also allow you
to define the callback’s logic right there where you want to use it. This is often much better than having to
define this logic somewhere in the function call operator of some class definition. Lambda expressions thus
generally lead to particularly expressive yet still very readable code.
A lambda expression has a lot in common with a function definition. In its most basic form, a lambda
expression basically provides a way to define a function with no name, an anonymous function. But lambda
expressions are far more powerful than that. In general, a lambda expression effectively defines a full-blown
function object that can carry any number of member variables. The beauty is that there’s no need for an
explicit definition of the type of this object anymore; the compiler generates this type automatically for you.
Practically speaking, you’ll find that a lambda expression is different from a regular function in that
it can access variables that exist in the enclosing scope where it is defined. Thinking back to Ex19_04, for
instance, a lambda expression there would be able to access number_to_search_for, the number that was
entered by the user. Before we examine how lambda expressions get access to local variables, though, let’s
first take one step back again and begin by explaining how you can define a basic unnamed or anonymous
function using a lambda expression.

[] (int x, int y) { return x < y; }
As you can see, the definition of a lambda expression indeed looks very much like the definition of a
function. The main difference is that a lambda expression starts with square brackets instead of a return
type and a function name. The opening square brackets are called the lambda introducer. They mark
the beginning of the lambda expression. There’s more to the lambda introducer than there is here—the
brackets are not always empty—but we’ll explain this in more depth a little later. The lambda introducer is
followed by the lambda parameter list between round parentheses.
For lambda functions without parameters, you may omit the empty parameter list, (). That is, a lambda
expression of form []() {...} may be further shortened to [] {...}. An empty lambda initializer, [], must not
be omitted, though. The lambda initializer is always required to signal the start of a lambda expression.
The body of the lambda expression between braces follows the parameter list, again just like a normal
function. The body for this lambda contains just one statement, a return statement that also calculates the
value that is returned. In general, the body of a lambda can contain any number of statements. The return
type defaults to that of the value returned. If nothing is returned, the return type is void.
It’s educational to have at least a basic notion of how lambda expressions are compiled. This will
aid you later in understanding how more advanced lambda expressions behave. Whenever the compiler
encounters a lambda expression, it internally generates a new class type. 

Rather than first storing a lambda closure in a named variable, it is at least as common to directly use a
lambda expression as a callback argument as follows:
 std::cout << "Minimum element: "
 << *findOptimum(numbers, [] (int x, int y) { return x < y; }) << std::endl;

As we’ve said before, the lambda introducer, [], is not necessarily empty. It can contain a capture clause
that specifies how variables in the enclosing scope can be accessed from within the body of the lambda. The
body of a lambda expression with nothing between the square brackets can work only with the arguments
and with variables that are defined locally within the lambda. A lambda with no capture clause is called a
stateless lambda expression because it cannot access anything in its enclosing scope.
If used in isolation, a capture default clause applies to all variables in the scope enclosing the definition
of the lambda. There are two capture defaults: = and &. We’ll discuss both of them in turn next. The capture
clause can contain only one of the capture defaults, never both.
Capturing by Value
If you put = between the square brackets, the body of the lambda can access all automatic variables in the
enclosing scope by value. hat is, while the values of all variables are made available within the lambda 
expression, the values stored in the original variables cannot be changed. 

If you put & between the square brackets, all variables in the enclosing scope are accessible by reference, so
their values can be changed by the code in the body of the lambda. To count the number of comparisons
performed by findOptimum(), for instance, you could use this lambda expression:
unsigned count {};
auto counter{ [&](int x, int y) { ++count; return x < y; } };
findOptimum(numbers, counter);
All variables within the outer scope are available by reference, so the lambda can both use and alter
their values.

A pointer to a function stores the address of a function. A pointer to a function can
store the address of any function with the specified return type and number and
types of parameters.
• You can use a pointer to a function to call the function at the address it contains. You
can also pass a pointer to a function as a function argument.
• Function objects or functors are objects that behave precisely like a function by
overloading the function call operator.
• Any number of member variables or functions can be added to a function object,
making them far more versatile than plain function pointers.
• Function objects are powerful but do require quite some coding to set up. This is
where lambda expressions come in; they alleviate the need to define the class for
each function object you need.
• A lambda expression defines either an anonymous function or a function object.
Lambda expressions are typically used to pass a function as an argument to another
function.
• A lambda expression always begins with a lambda introducer that consists of a pair
of square brackets that can be empty.
• The lambda introducer can contain a capture clause that specifies which variables
in the enclosing scope can be accessed from the body of the lambda expression.
Variables can be captured by value or by reference.
• There are two default capture clauses: = specifies that all variables in the enclosing
scope are to be captured by value, and & specifies that all variables in the enclosing
scope are captured by reference.
• A capture clause can specify specific variables to be captured by value or by
reference.
• Variables captured by value will have a local copy created. The copy is not modifiable
by default. Adding the mutable keyword following the parameter list allows local
copies of variables captured by value to be modified.
• You can specify the return type for a lambda expression using the trailing return type
syntax. If you don’t specify a return type, the compiler deduces the return type from
the first return statement in the body of the lambda.
• You can use the std::function<> template type that is defined in the <functional>
module to specify the type of a function parameter that will accept any first-class
function as an argument, including a lambda expression. In fact, it allows you to
specify a named type for a variable—be it a function parameter, member variable,
or automatic variable—that can hold a lambda closure. This is a feat that would
otherwise be very hard, as only the compiler knows the name of this type.





*/

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

	std::unique_ptr<double> pdata{ std::make_unique<double>(999.9) };
	// unique pointer object created with the make_unique function

	std::cout << *pdata << std::endl;
}