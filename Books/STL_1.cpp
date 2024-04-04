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
// exceptions provide a way to react to exceptional circumstances like runtime errors by transferring control to special functions called handlers
// this is done via try catch block
// exceptions thrown by throw keyword, handlers declared with catch keyword
// multiple catch blocks can be chained with different paraneter types
/*
Only the handler whose argument type matches the type of the exception specified in the throw statement is executed.

If an ellipsis (...) is used as the parameter of catch, that handler will catch any exception no matter what the type of the exception thrown. This can be used as a default handler that catches all exceptions not caught by other handlers:

try {
  // code here
}
catch (int param) { cout << "int exception"; }
catch (char param) { cout << "char exception"; }
catch (...) { cout << "default exception"; }

In this case, the last handler would catch any exception thrown of a type that is neither int nor char.

After an exception has been handled the program, execution resumes after the try-catch block, not after the throw statement!.

It is also possible to nest try-catch blocks within more external try blocks. In these cases, we have the possibility that an internal catch block forwards the exception to its external level. This is done with the expression throw; with no arguments. For example:

try {
  try {
	  // code here
  }
  catch (int n) {
	  throw;
  }
}
catch (...) {
  cout << "Exception occurred";
}

The C++ Standard library provides a base class specifically designed to declare objects to be thrown as exceptions. It is called std::exception and is defined in the <exception> header. This class has a virtual member function called what that returns a null-terminated character sequence (of type char *) and that can be overwritten in derived classes to contain some sort of description of the exception.

// using standard exceptions
#include <iostream>
#include <exception>
using namespace std;

class myexception: public exception
{
  virtual const char* what() const throw()
  {
	return "My exception happened";
  }
} myex;

int main () {
  try
  {
	throw myex;
  }
  catch (exception& e)
  {
	cout << e.what() << '\n';
  }
  return 0;
}
My exception happened.

We have placed a handler that catches exception objects by reference (notice the ampersand & after the type), therefore this catches also classes derived from exception, like our myex object of type myexception.

All exceptions thrown by components of the C++ Standard library throw exceptions derived from this exception class.

A typical example where standard exceptions need to be checked for is on memory allocation:

// bad_alloc standard exception

int main () {
  try
  {
	int* myarray= new int[1000];
  }
  catch (exception& e)
  {
	cout << "Standard exception: " << e.what() << endl;
  }
  return 0;
}

The exception that may be caught by the exception handler in this example is a bad_alloc. Because bad_alloc is derived from the standard base class exception, it can be caught (capturing by reference, captures all related classes).



*/


// sequence containers (ordered based on entry) : list, forward list, array, deque, vector
// associative constainers (sorted collections, position depends on key or value) : set, map
// unordered associative containers : unordered set, unordered map

// sequence containers usually implemented as arrays or linked lists
// associative containers usually implemented as binary trees
// unordered containers usually implemented as hash tables

// associative contains sort elements automatically upon entry and searching for an element is always logarithmic complexity. They are designed for easy fast searching

// vectors manage elements in a dynamic array, enable random access which means we can access any element quickly via index
// appending and removing elements at the end of the array is very fast
//  However, inserting an element in the middle or at the beginning of the array takes time because all the following elements have to be moved to make room for it while maintaining the order.
/*
Strictly speaking, appending elements is amortized very fast. An individual append may be slow when a vector has to reallocate new memory and to copy existing elements into the new memory. 
However, because such reallocations are rather rare, the operation is very fast in the long term.

*/


// deque is double ended queue
// dynamic array that can add and remove elements quickly at the front and back
// inserting elements in the middle takes time because elements must be moved

// arrays manage elements in a static fixed size sequential container
// arrays enable random access via index

// list is implemented as a double linked list of elements. each element has its own segment of memory and refers to its predecessor and its successor
// lists do not provide random access, you have to access each element sequentially. general access to an arbitrary element takes linear time because distance is proportional to the number of elements
// this is much worse than the amortised constant time provided by vectors and dequeues
// the advantage of a list is that insertion or removal of an element is fast at any position, only the links must be changed
// moving an element in the middle of the list is much faster than a vector or deque
// lists do not provide [] operator, no random access as this would have bad performance

// forward list is a singly linked list of elements
/*
// create forward-list container for some prime numbers
forward_list<long> coll = { 2, 3, 5, 7, 11, 13, 17 };
// resize two times
// - note: poor performance
coll.resize(9);
coll.resize(10,99);

resizing a list is poor performance because resize() is used to change the number of elements. If the size grows, you can pass an
additional parameter to specify the value of the new elements. Otherwise, the default value (zero for
fundamental types) is used. Calling resize() is really an expensive operation here. It has
linear complexity because to reach the end, you have to go element-by-element through the whole
list. 

*/


// associative containers sort elements automatically according to certain criteria
// by default, the containers compare the elements or the keys with operator <, we can supply our own comparison function
/*
All these associative container classes have an optional template argument for the sorting criterion.
The default sorting criterion is the operator <. The sorting criterion is also used as the test for
equivalence; that is, two elements are duplicates if neither of their values/keys is less than the other.
*/


/*
Associative containers are typically implemented as binary trees. Thus, every element (every
node) has one parent and two children. All ancestors to the left have lesser values; all ancestors to
the right have greater values. The associative containers differ in the kinds of elements they support
and how they handle duplicates.
The major advantage of associative containers is that finding an element with a specific value
is rather fast because it has logarithmic complexity (in all sequence containers, you have linear
complexity). Thus, when using associative containers, with 1,000 elements you have 10 instead of
500 comparisons on average. However, a drawback is that you can’t modify values directly, because
doing so would corrupt the automatic sorting of the elements.
The following associative containers are predefined in the STL:
• A set is a collection in which elements are sorted according to their own values. Each element
may occur only once, so duplicates are not allowed.
• A multiset is the same as a set except that duplicates are allowed. Thus, a multiset may contain
multiple elements that have the same value.
• A map contains elements that are key/value pairs. Each element has a key that is the basis for the
sorting criterion and a value. Each key may occur only once, so duplicate keys are not allowed.
A map can also be used as an associative array, an array that has an arbitrary index type 
• A multimap is the same as a map except that duplicates are allowed. Thus, a multimap may
contain multiple elements that have the same key. A multimap can also be used as dictionary.

a set can be thought of as a map where the key and value is the same

maps deal with key/value pairs. The type of each element in a map is pair<const key, value>
The key is constant because any modification of its value would break the order of the elements,
which are automatically sorted by the container. Because pairs don’t have an output operator,
you can’t print them as a whole. Instead, you must access the members of the pair structure,
which are called first and second.


*/


/*

unordered containers have elements in no particular order. it can be thought of like a bag
unordered containers are typically implemented as a hash table
internally, the container is an array of linked lists. using a hash function, the position of an element in the array gets processed
 The goal is that each element has its own position so that you have fast access to
each element, provided that the hash function is fast. But because such a fast perfect hash function
is not always possible or might require that the array consumes a huge amount of memory, multiple
elements might have the same position. For this reason, the elements in the array are linked lists so
that you can store more than one element at each array position.
The major advantage of unordered containers is that finding an element with a specific value
is even faster than for associative containers. In fact, the use of unordered containers provides
amortized constant complexity, provided that you have a good hash function. However, providing a
good hash function is not easy, and you might need a lot of memory
for the buckets

All these unordered container classes have a couple of optional template arguments to specify a hash
function and an equivalence criterion. The equivalence criterion is used to find specific values and
to identify duplicates. The default equivalence criterion is the operator ==.
You can consider an unordered set as a special kind of unordered map, in which the value is
identical to the key. In fact, all these unordered container types are usually implemented by using
the same basic implementation of a hash table.

the key is const, it cant be changed. The element can be modified however

range based for loops use iterators under the hood to iterate over all elements

An iterator is an object that can iterate over elements (navigate from element to element). These
elements may be all or a subset of the elements of an STL container. An iterator represents a certain
position in a container. The following fundamental operations define the behavior of an iterator:
• Operator * returns the element of the current position. If the elements have members, you can
use operator -> to access those members directly from the iterator.
• Operator ++ lets the iterator step forward to the next element. Most iterators also allow stepping
backward by using operator --.
• Operators == and != return whether two iterators represent the same position.
• Operator = assigns an iterator (the position of the element to which it refers).


All container classes provide the same basic member functions that enable them to use iterators
to navigate over their elements. The most important of these functions are as follows:

• begin() returns an iterator that represents the beginning of the elements in the container. The
beginning is the position of the first element, if any.

• end() returns an iterator that represents the end of the elements in the container. The end is the
position behind the last element. Such an iterator is also called a past-the-end iterator.

there's also cbegin() and cend()

You should always prefer a member function over an algorithm if good performance is the goal.

elements of containers must meet certain requirements because containers handle them in a special way. 
the elements in the stl containers must meet the fundamental requirements (exception will be thrown if a container object tried to do something and the custom type doesn't have the required function defined, but its not an error initially):

1. An element must be copyable or movable. Thus, an element type implicitly or explicitly has to
provide a copy or move constructor. A generated copy should be equivalent to the source. This means that any test for equality
returns that both are equal and that both source and copy behave the same.

2. An element must be (move) assignable by the assignment operator. Containers and algorithms
use assignment operators to overwrite old elements with new elements.

3. An element must be destroyable by a destructor. Containers destroy their internal copies of
elements when these elements are removed from the container. Thus, the destructor must not be
private. Also, as usual in C++, a destructor must not throw; otherwise, all bets are off.

These three operations are generated implicitly for any class. Thus, a class meets the requirements
automatically, provided that no special versions of these operations are defined and no special members disable the sanity of those operations.


• For some member functions of sequence containers, the default constructor must be available.
For example, it is possible to create a nonempty container or increase the number of elements
with no hint of the values those new elements should have. These elements are created without
any arguments by calling the default constructor of their type.
• For several operations, the test of equality with operator == must be defined and is especially
needed when elements are searched. For unordered containers, however, you can provide your
own definition of equivalence if the elements do not support operator == 
• For associative containers, the operations of the sorting criterion must be provided by the elements. By default, this is the operator <, which is called by the less<> function object.
• For unordered containers, a hash function and an equivalence criterion must be provided for the
elements


usually, all containers create internal copies of their elements and return copies of those elements
this means that container elements are equal but not identical to the objects you put into the container
if you modify objects as elements of the container, you modify a copy, not the original object.

Copying values means that the STL containers provide value semantics. The containers contain
the values of the objects you insert rather than the objects themselves. In practice, however, you may
also need reference semantics. This means that the containers contain references to the objects that
are their elements.
The approach of the STL to support only value semantics has both strengths and weaknesses. Its
strengths are that
• Copying elements is simple.
• References are error prone. You must ensure that references don’t refer to objects that no longer
exist. You also have to manage circular references, which might occur.
Its weaknesses are as follows:
• Copying elements might result in bad performance or may not even be possible.
• Managing the same object in several containers at the same time is not possible.
In practice, you need both approaches; you need copies that are independent of the original data
(value semantics) and copies that still refer to the original data and get modified accordingly (reference semantics). Unfortunately, there is no support for reference semantics in the C++ standard
library. However, you can implement reference semantics in terms of value semantics.
The obvious approach to implementing reference semantics is to use pointers as elements.14
However, ordinary pointers have the usual problems. For example, objects to which they refer may
no longer exist, and comparisons may not work as desired because pointers instead of the objects are
compared. Thus, you should be very careful when you use ordinary pointers as container elements.
A better approach is to use a kind of smart pointer: objects that have a pointer-like interface
but that do some additional checking or processing internally.

or you can use a vector of std::refernce_wrapper


The difference between a copy constructor and an assignment operator is that a copy constructor helps to create a copy of an already existing object without altering the original value of the created object, whereas an assignment operator helps to assign a new value to a data member or an object in the program.

class Test {
public:
	Test() {}
	Test(const Test& t)
	{
		cout << "Copy constructor called " << endl;
	}

	Test& operator=(const Test& t)
	{
		cout << "Assignment operator called " << endl;
		return *this;
	}
};

// Driver code
int main()
{
	Test t1, t2;
	t2 = t1;
	Test t3 = t1;
	getchar();
	return 0;
}
Output:
Assignment operator called
Copy constructor called

Explanation: Here, t2 = t1;  calls the assignment operator, same as t2.operator=(t1); and  Test t3 = t1;  calls the copy constructor, same as Test t3(t1)

So copy constructor is called at new object construction, even if assignment operator is used



*/

struct example {   // this cant be copied or assigned so trying to put it into a vector will throw an exception, using default on the copy consructor makes it usable
	int val{ 10 };

	example(const example& e) = default; // delete;
	example() {}
	example& operator= (const example& e) = delete; // default;   
	//~example() = delete;    always created anyways
};


/*

error handling in the STL:
STL is based on best performance rather than highest security, error checking wastes time so almost none is done

1. Error checking reduces performance, and speed is still a general goal of programs. As mentioned,
good performance was one of the design goals of the STL.
2. If you prefer safety over speed, you can still get it, either by adding wrappers or by using special
versions of the STL. But when error checking is built into all basic operations, you can’t program
to avoid error checking to get better performance For example, when every subscript operation
checks whether a range is valid, you can’t write your own subscripts without checking. However,
it is possible the other way around.



*/













int main()
{
	print({ 1, 2, 3, 4, 5 }); // pass in initialiser list

	std::vector<int> vec{ 1,2,3,4,5 };
	printElements(vec);

	try {
		throw 20;  // throw expression accepts one parameter
	}
	catch (int a)  // catch is declared like a regular function
	{
		std::cout << "caught the integer exception" << std::endl;
	}

	std::vector<example> vec2;
	vec2.reserve(10);

	example e1;

	vec2.push_back(e1);  // e1 is then copied into the vector


}
