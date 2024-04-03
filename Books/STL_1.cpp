# include <iostream>
# include <vector>
# include <algorithm>
# include <array>
# include <string>
# include <unordered_set>
# include <span>
# include <ranges>
# include <memory>

// Big O notation expresses the runtime of an algorithm as a function of a given input of size n
// if runtime grows linearly with size of input then complexity is O(N)
/*
Constant O(1) The runtime is independent of the number of elements.
Logarithmic O(log(n)) The runtime grows logarithmically with respect to the number of
elements.
Linear O(n) The runtime grows linearly (with the same factor) as the number of elements grows.
n-log-n O(n ∗ log(n)) The runtime grows as a product of linear and logarithmic complexity.
Quadratic O(n2) The runtime grows quadratically with respect to the number of elements.

Some complexity definitions in the C++ reference manual are specified as amortized. This means
that the operations in the long term behave as described. However, a single operation may take
longer than specified. For example, if you append elements to a dynamic array, the runtime depends
on whether the array has enough memory for one more element. If there is enough memory, the
complexity is constant because inserting a new last element always takes the same time. However, if
there is not enough memory, the complexity is linear because, depending on the number of elements,
you have to allocate new memory and copy all elements. Reallocations are rather rare, so any
sufficiently long sequence of that operation behaves as if each operation has constant complexity.
Thus, the complexity of the insertion is “amortized” constant time.

*/

// initialisation can happen via parenthesis, braces or assignment operator
// braces can be used everywhere, use them

int values[]{ 1,2,3 };  // integer array
int i;  // i has undefined value
int j{};  // j is initialised to 0
int* p{};  // p is initalised to nullptr

// assignment operator and circular braces cause narrowing conversions, {} do not
/*
int x1(5.3); // OK, but OUCH: x1 becomes 5
int x2 = 5.3; // OK, but OUCH: x2 becomes 5
int x3{5.0}; // ERROR: narrowing
int x4 = {5.3}; // ERROR: narrowing
char c1{7}; // OK: even though 7 is an int, this is not narrowing
char c2{99999}; // ERROR: narrowing (if 99999 doesn’t fit into a char)
std::vector<int> v1 { 1, 2, 4, 5 }; // OK
std::vector<int> v2 { 1, 2.3, 4, 5.6 }; // ERROR: narrowing doubles to ints
*/

// std::initializer_list<> can support initialisations by a list of values or in any other place you want a list of values

void print(std::initializer_list<int> vals)
{
	for (auto i = vals.begin(); i != vals.end(); ++i)  // i is an interator remember
	{
		std::cout << *i << std::endl;  // dereference iterator
	}
}

/*
When there are constructors for both a specific number of arguments and an initializer list, the
version with the initializer list is preferred:
class P
{
public:
P(int,int);
P(std::initializer_list<int>);
};
P p(77,5); // calls P::P(int,int)
P q{77,5}; // calls P::P(initializer_list)
P r{77,5,42}; // calls P::P(initializer_list)
P s = {77,5}; // calls P::P(initializer_list

Because of initializer lists, explicit now also becomes relevant for constructors taking more
than one argument. So, you can now disable automatic type conversions from multiple values, which
is also used when an initialization uses the = syntax:
class P
{
public:
P(int a, int b) {
...
}
explicit P(int a, int b, int c) {
...
}
};
P x(77,5); // OK
P y{77,5}; // OK
P z {77,5,42}; // OK
P v = {77,5}; // OK (implicit type conversion allowed)
P w = {77,5,42}; // ERROR due to explicit (no implicit type conversion allowed)

assignment operator causes implicit type conversion

*/

// for each loop, can be used with all collections, ranges and arrays

void printElements(std::vector<int>& vec)
{
	for (auto& i : vec)  // by reference, so we don't make any copies or call the copy constructor unnecessarily
	{
		i++;
		std::cout << i << std::endl;
	}
}


/*

Overloading Rules for Rvalue and Lvalue References
The overloading rules for rvalues and lvalues are as follows:
• If you implement only
void foo(X&);
without void foo(X&&), the behavior is as in C++98: foo() can be called for lvalues but not
for rvalues.
• If you implement
void foo(const X&);
without void foo(X&&), the behavior is as in C++98: foo() can be called for rvalues and for
lvalues.
• If you implement
void foo(X&);
void foo(X&&);
or
void foo(const X&);
void foo(X&&);
you can distinguish between dealing with rvalues and lvalues. The version for rvalues is allowed
to and should provide move semantics. Thus, it can steal the internal state and resources of the
passed argument.
• If you implement
void foo(X&&);
but neither void foo(X&) nor void foo(const X&), foo() can be called on rvalues, but
trying to call it on an lvalue will trigger a compile error. Thus, only move semantics are provided
here.


*/

// noexcept used on fucntions that cannot throw, or are not prepared to throw

/* void foo () noexcept;
declares that foo() won’t throw. If an exception is not handled locally inside foo() — thus, if
foo() throws — the program is terminated, calling std::terminate(), which by default calls
std::abort()  */

/*

By using the new decltype keyword, you can let the compiler find out the type of an expression. This is the realization of the often requested typeof feature. However, the existing typeof
implementations were inconsistent and incomplete, so C++11 introduced a new keyword. For
example:
std::map<std::string,float> coll;
decltype(coll)::value_type elem;
One application of decltype is to declare return types (see below)




Sometimes, the return type of a function depends on an expression processed with the arguments.
However, something like
template <typename T1, typename T2>
decltype(x+y) add(T1 x, T2 y);
was not possible before C++11, because the return expression uses objects not introduced or in scope
yet.
But with C++11, you can alternatively declare the return type of a function behind the parameter
list:
template <typename T1, typename T2>
auto add(T1 x, T2 y) -> decltype(x+y);

namespace is a certain scope for identifiers:
According to the concept of namespaces, you have three options when using an identifier of the C++
standard library:
1. You can qualify the identifier directly. For example, you can write std::ostream instead of
ostream. A complete statement might look like this:
std::cout << std::hex << 3.4 << std::endl;
2. You can use a using declaration. For example, the following code fragment introduces the local
ability to skip std:: for cout and endl:
using std::cout;
using std::endl;
Thus, the example in option 1 could be written like this:
cout << std::hex << 3.4 << endl;
3. You can use a using directive. This is the easiest option. By using a using directive for namespace
std, all identifiers of the namespace std are available asif they had been declared globally. Thus,
the statement
using namespace std;
allows you to write
cout << hex << 3.4 << endl;
Note that in complex code, this might lead to accidental name clashes or, worse, to different
behavior due to some obscure overloading rules. You should never use a using directive when
the context is not clear, such as in header files

*/


// exceptions
// all exceptions thrown by the language or library are derived from the bae class exception, defined in <exception>
/*
errors can be either:
1. Language support
2. Logic errors
3. Runtime errors
Logic errors usually can be avoided because the reason is inside the scope of a program, such as a
precondition violation. Runtime exceptions are caused by a reason that is outside the scope of the
program, such as not enough resources


For all standard exception classes, only one member can be used to get additional information besides the type itself: the virtual member function what(), which returns a null-terminated byte
string:
namespace std {
class exception {
public:
virtual const char* what() const noexcept;
...
};
}
The content of the string returned by what() is implementation defined.
The C-string returned by what() is valid until the exception object from
which it is obtained gets destroyed or a new value is assigned to the exception object.

In several places, the C++ standard library uses special objects to handle the allocation and deallocation of memory. Such objects are called allocators. They represent a special memory model and are
used as an abstraction to translate the need to use memory into a raw call for memory. The use of
different allocator objects at the same time allows you to use different memory models in a program.
Originally, allocators were introduced as part of the STL to handle the nasty problem of different
pointer types on PCs (such as near, far, and huge pointers). Now, allocators serve as a base for
technical solutions that use certain memory models, such as shared memory, garbage collection, and
object-oriented databases, without changing the interfaces. However, this use is relatively new and
not yet widely adopted (this will probably change).
The C++ standard library defines a default allocator as follows:
namespace std {
template <typename T>
class allocator;
}
The default allocator is used as the default value everywhere an allocator can be used as an argument. It does the usual calls for memory allocation and deallocation; that is, it calls the new and
delete operators. However, when or how often these operators are called is unspecified. Thus, an
implementation of the default allocator might, for example, cache the allocated memory internally.
The default allocator is used in most programs. However, other libraries sometimes provide allocators to fit certain needs. In such cases, you must simply pass them as arguments. Only occasionally
does it make sense to program allocators. In practice, the default allocator is typically used.


*/


// cpp exceptions:






int main()
{
	print({ 1, 2, 3, 4, 5 }); // pass in initialiser list

	std::vector<int> vec{ 1,2,3,4,5 };
	printElements(vec);
}
