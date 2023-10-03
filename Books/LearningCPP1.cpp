# include <iostream>
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