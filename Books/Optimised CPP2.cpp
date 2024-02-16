# include <iostream>
# include <algorithm>
# include <vector>
# include <array>
# include <type_traits>

/* With guaranteed copy elision introduced in C++17, the statement auto x = Foo{}
is identical to Foo x{}; that is, the language guarantees that there is no temporary
object that needs to be moved or copied in this case. This means that we can now use
the left-to-right initialization style without worrying about performance and we can
also use it for non-movable/non-copyable types, such as std::atomic or std::mutex.

In contrast to a const reference, a mutable reference cannot bind to a temporary. As
mentioned, we use auto& to denote mutable references. Use a mutable reference only
when you intend to change the object it references.

determining whether an object is moved or copied is quite simple.
If it has a variable name, it is copied; otherwise, it is moved. If you are using
std::move() to move a named object, the object cannot be declared const.

Writing an empty destructor can prevent the compiler from implementing certain
optimizations.

Don't move when copies are elided anyway, moving is less efficient than not copying at all

the compiler moves an object when the object can be categorized as an
rvalue. The term rvalue might sound complicated, but in essence it is just an object
that is not tied to a named variable, for either of the following reasons:
• It's coming straight out of a function
• We make a variable an rvalue by using std::move()

Exceptions can be avoided because throwing and catching exceptions is relatively expensive and not deterministic
Exceptions increase the size of the binary program aswell

An important observation is that the caches are tiny compared to
the amount of main memory available

There are orders of magnitude between cache layers

Structuring the data in such a way that the caches can be fully utilized can have
a dramatic effect on performance. Accessing data that has recently been used and,
therefore, potentially already resides in the cache will make your program faster.
This is known as temporal locality.
Also, accessing data located near some other data you are using will increase the
likelihood that the data you need is already in a cache line that was fetched from the
main memory earlier. This is known as spatial locality.

there is no such thing as 2-dimensional memory. Instead, when this matrix is laid out in a 1-dimensional memory space, it resembles a long 1d array
accessing matrix elements by matrix[i][j] in a loop is much faster than by matrix[j][i] because the elements are laid out sequentially and the prefetcher can store them in cache

Sequence containers keep elements in the order we specify when adding the elements to the container, std::array, std::vector, std::deque, std::list, and std::forward_list.

 The elements added to a vector are guaranteed to be laid out contiguously in memory, which means that you can access any element in the array by its index in constant time. It
also means that it provides excellent performance when traversing the elements in the order they are laid out, thanks to the spatial locality mentioned earlier.
Adding elements to the end of a vector using the push_back() function is fast, as long as the size is less than the capacity. When adding an element and there is no room for
more, the vector will allocate a new internal buffer and then move all of the elements to the new space. The capacity will grow in such a way that resizing the buffer rarely happens, thus making push_back() an amortized constant-time operation

A vector template instance of type std::vector<Person> will store Person objects
by value. When the vector needs to rearrange the Person objects (for example, as
a result of an insert), the values will be copy constructed or moved. Objects will be
moved if they have a nothrow move constructor. Otherwise, the objects will be copy
constructed in order to guarantee strong exception safety

If you are adding newly created objects to the vector, you can take advantage of the
emplace_back() function, which will create the object in place for you, instead of
creating an object and then copying/moving it to the vector using the push_back()
function

However, now the recommended way to erase
elements from a std::vector is by using std::erase() and std::erase_if()

std::array is on the stack


*/

auto x = 10;  // auto is useful because you can't leave an auto variable uninitialised
auto v = { 1,2,3,4,5 };
auto num_above_3 = std::count_if(v.begin(), v.end(), [](int i) {return i > 3; });  //  stateless lambda

// std::array is on the stack 
//The size of the array is a template argument specified
//at compile time, which means that the size and type elements become a part of the
//concrete type :
auto a = std::array<int, 16>{};
auto b = std::array<int, 1024>{};
//In this example, a and b are not the same type, which means that you have to specify
//the size when using the type as a function parameter :
auto f(const std::array<int, 1024>& input) {
	// ...
}
//f(a); // Does not compile, f requires an int array of size 1024
//This might seem a bit tedious at first, but this is, in fact, the big advantage over the
//built - in array type(the C arrays), which loses the size information when passed to a
//function, since it automatically converts a pointer into the first element of the array:
// input looks like an array, but is in fact a pointer 
auto f(const int input[]) {
	// ...
}
int a[16];
int b[1024];
//f(a); // Compiles, but unsafe
//An array losing its size information is usually referred to as array decay.



/* Sometimes, you'll find yourself in a situation where you need to frequently add 
elements to both the beginning and end of a sequence. If you are using a std::vector
and need to speed up the inserts at the front, you can instead use std::deque, which 
is short for double-ended queue. std::deque is usually implemented as a collection 
of fixed-size arrays, which makes it possible to access elements by their index in 
constant time. However, as you can see in the following figure, all of the elements 
are not stored contiguously in memory, which is the case with std::vector and 
std::array. 


with lists, Note that even if the elements are ordered in a sequence, they are not laid out 
contiguously in memory like the vector and array are, which means that iterating a 
linked list will most likely generate a lot more cache misses compared to the vector.
To recap, the std::list is a doubly linked list with pointers to the next and previous 
elements:
std::list is a doubly linked list
The std::forward_list is a singly linked list with pointers to the next element

The std::forward_list is more memory efficient since it only has one pointer to the
next element.
Lists are also the only containers that support splicing, which is a way to transfer
elements between lists without copying or moving the elements. This means, for
example, that it is possible to concatenate two lists into one in constant time, O(1).
Other containers require at least linear time for such operations

associative containers are either ordered or unordered
• Ordered associative containers: These containers are based on trees;
the containers use a tree for storing their elements. They require that the
elements are ordered by the less than operator (<). The functions for adding,
deleting, and finding elements are all O(log n) in the tree-based containers.
The containers are named std::set, std::map, std::multiset, and
std::multimap.
• Unordered associative containers: These containers are based on hash tables;
the containers use a hash table for storing their elements. They require that
the elements are compared with the equality operator (==) and that there
is a way to compute a hash value based on an element. 
The functions for adding, deleting, and finding elements are all O(1) in the
hash table-based containers. The containers are named std::unordered_set,
std::unordered_map, std::unordered_multiset, and std::unordered_
multimap.
Since C++20, all associative containers are equipped with a function named
contains(), which should be used when you want to know whether a container
contains some specific elements. In earlier versions of C++, it was necessary to
use count() or find() to find out whether a container contained an element.



useful tip, Always use the specialized functions, such as contains() and 
empty(), instead of using count() > 0 or size() == 0. The 
specialized functions are guaranteed to be the most efficient ones.

Unordered associatve containers use hash values to decide where elements are stored. What if two different elements generate the same index,
either because they produced the same hash value, or because two different hash
values are being limited to the same index? When two non-equal elements end up at
the same index, we call that a hash collision. This is not just an edge case: this will
happen a lot, even if we are using a good hash function, and especially if the array is
small when compared to the number of elements we are adding. There are various
ways of dealing with hash collisions. Here, we will focus on the one that is being
used in the standard library, which is called separate chaining.
Data Structures
[ 112 ]
Separate chaining solves the problem of two unequal elements ending up at the
same index. Instead of just storing the elements directly in the array, the array is a
sequence of buckets. Each bucket can contain multiple elements, that is, all of the
elements that are hashed to the same index. So, each bucket is also some sort of
container. The exact data structure used for the buckets is not defined, and it can
vary for different implementations. However, we can think of it as a linked list and
assume that finding an element in a specific bucket is slow, since it needs to scan the
elements in the buckets linearly.

Apart from creating hash values that distribute the keys evenly among the buckets,
we can reduce the number of collisions by having many buckets. The average
number of elements per bucket is called the load factor.

Finally there are container adaptors, There are three container adaptors in the standard library: std::stack, std::queue, 
and std::priority_queue. Container adaptors are quite different from sequence 
containers and associative containers because they represent abstract data types that 
can be implemented by the underlying sequence container. For example, the stack, 
which is a last in, first out (LIFO) data structure supporting push and pop on the top 
of the stack, can be implemented by using a vector, list, deque, or any other custom 
sequence container that supports back(), push_back(), and pop_back(). The same goes 
for queue, which is a first in, first out (FIFO) data structure, and priortiy_queue.

A priority queue offers a constant-time lookup of the element with the highest
priority. The priority is defined using the less than operator of the elements. Insert
and delete both run in logarithmic time. A priority queue is a partially ordered data
structure, and it might not be obvious when to use one instead of a completely sorted
data structure, for example, a tree or a sorted vector. However, in some cases, a
priority queue can offer you the functionality you need, and for a lower cost than a
completely sorted container

std::string_view and std::span are not containers but lightweight views (or slices) of a 
sequence of contiguous elements. Views are small objects that are meant to be copied 
by value. They don't allocate memory, nor do they provide any guarantees regarding 
the lifetime of the memory they point to. In other words, they are non-owning 
reference types, which differ significantly from the containers

The fact that string_view does not need a null terminator means that it can handle
substrings much more efficiently than a C-style string or a std::string because it
does not have to create new strings just to add the null terminator. The complexity
of substr() using a std::string_view is constant, which should be compared to the
substr() version of std::string, which runs in linear time

There is also a performance win when passing strings to functions. Consider the
following code:

auto some_func(const std::string& s) {
 // process s ...
}
some_func("A string literal"); // Creates a std::string

When passing a string literal to some_func(), the compiler needs to construct a
new std::string object to match the type of the argument. However, if we let
some_func() accept a std::string_view, there is no longer any need to construct
a std::string:

auto some_func(std::string_view s) { // Pass by value
 // process s ...
}
some_func("A string literal");

A std::string_view instance can be constructed efficiently both from a std::string
and a string literal and is, therefore, a well-suited type for function parameters.

Array decay is the source of many bound-related bugs, and in situations where builtin arrays are used (for one reason or another), std::span offers a safer way to pass
arrays to functions. Since the span holds both the pointer to the memory and the size
together in one object, we can use it as the single type when passing sequences of
elements to functions:

auto f3(std::span<float> buffer) { // Pass by value
 for (auto&& b : buffer) { // Range-based for-loop
 // ...
 }
}
float a[256];
f3(a); // OK! Array is passed as a span with size
auto v = std::vector{1.f, 2.f, 3.f, 4.f};
f3(v); // OK!
A span is also more convenient to use over a built-in array since it acts more like a
regular container with support for iterators.
There are many similarities between std::string_view and std::span when it comes
to the data members (pointer and size) and the member functions. But there are also
some notable differences: the memory pointed to by std::span is mutable, whereas
the std::string_view always points to constant memory. std::string_view also
contains string-specific functions such as hash() and substr(), which are naturally
not part of std::span. Lastly, there is no compare() function in std::span, so it's not
possible to directly use the comparison operators on std::span objects

Knowing the time and memory complexity of data structures is important
when choosing between containers. But it's equally important to remember that
each container is afflicted with an overhead cost, which has a bigger impact on
the performance for smaller datasets. The complexity guarantees only become
interesting for sufficiently large datasets. It's up to you, though, to decide what
sufficiently large means in your use cases. Here, again, you need to measure your
program while executing it to gain insights.

In addition, the fact that computers are equipped with memory caches makes the use
of data structures that are friendly to the cache more likely to perform better. This
usually speaks in favor of the std::vector, which has a low memory overhead and 
stores its elements contiguously in memory, making access and traversal faster.

Here, we will focus on two small, but important, functions that can be found in the
standard library: contains() and empty(). Use contains() when checking whether
an element exists in an associated container. Use empty() if you want to know
whether a container has any elements or is empty. Apart from expressing the intent
more clearly, it also has performance benefits. Checking the size of a linked list is an
O(n) operation, whereas calling empty() on a list runs in constant time, O(1). Use these specific functions over your own handcrafted ones wherever possible

Iterating over collections of smaller objects is faster than bigger objects because of the way the computer uses the cache hierarchy to fetch data from 
the main memory.  Prefer classes to be small and have single responsibilities


Iterators provide a generic way to navigate through the elements in a sequence.
At its core, an iterator is an object that represents a position in a sequence. It has two main responsibilities:
• Navigating in the sequence
• Reading and writing the value at its current position

In C++, an iterator could be considered an object with the same properties as a
raw pointer; it can be stepped to the next element and dereferenced (if pointing to a
valid address). The algorithms only use a few of the operations that a pointer allows,
although the iterator may internally be a heavy object traversing a tree-like std::map.

vec.end() actually points to the memory address after the end of the vector, this iterator value is also known as a sentinel, its what we compare to check bounds

A range is a replacement for the iterator-sentinel pairs that we have used when
referring to a sequence of elements. The <range> header contains multiple concepts
that define requirements for different kinds of ranges.
This means that any type that exposes begin() and end() functions is considered a
range (given that these functions return iterators).

All algorithms use std::swap() and std::move() when moving elements around, but
only if the move constructor and move assignment are marked noexcept. Therefore,
it is important to have these implemented for heavy objects when using algorithms.
If they are not available and exception free, the elements will be copied instead. 

Be careful when using iterators on a vectoe.
Usually the implementation of vector iterator is just a simple pointer that points to some element to backing array. 
Therefore when capacity changes and array is reallocated, any such iterator is no longer valid as the pointer points to no longer valid memory

Views in the Ranges library are lazy evaluated iterations over a range. Technically,
they are only iterators with built-in logic, but syntactically, they provide a very
pleasant syntax for many common operations

t most operating systems today are virtual memory operating
systems, which provide the illusion that a process has all the memory for itself.
Each process has its own virtual address space.

Addresses in the virtual address space that programmers see are mapped to physical
addresses by the operating system and the memory management unit (MMU),
which is a part of the processor. This mapping or translation happens each time
we access a memory address.
This extra layer of indirection makes it possible for the operating system to use
physical memory for the parts of a process that are currently being used, and back
up the rest of the virtual memory on disk. In this sense, we can look at the physical
main memory as a cache for the virtual memory space, which resides on secondary
storage. The areas of the secondary storage that are used for backing up memory
pages are usually called swap space, swap file, or simply pagefile, depending on
the operating system.
Virtual memory makes it possible for processes to have a virtual address space
bigger than the physical address space, since virtual memory that is not in use
does not have to occupy physical memory.

The most common way to implement virtual memory today is to divide the address
space into fixed-size blocks called memory pages. When a process accesses memory
at a virtual address, the operating system checks whether the memory page is
backed by physical memory (a page frame). If the memory page is not mapped in the
main memory, a hardware exception occurs, and the page is loaded from disk into
memory. This type of hardware exception is called a page fault. This is not an error
but a necessary interrupt in order to load data from disk to memory. As you may
have guessed, though, this is very slow compared to reading data that is already
resident in memory.

When there are no more available page frames in the main memory, a page frame
has to be evicted. If the page to be evicted is dirty, that is, it has been modified since
it was last loaded from disk, it needs to be written to disk before it can be replaced.
This mechanism is called paging. If the memory page has not been modified, the
memory page is simply evicted

Thrashing can happen when a system runs low on physical memory and is,
therefore, constantly paging. Whenever a process gets time scheduled on the CPU,
it tries to access memory that has been paged out. Loading new memory pages
means that the other pages first have to be stored on disk. Moving data back and
forth between disk and memory is usually very slow; in some cases, this more or
less stalls the computer since the system spends all its time paging. Looking at the
system's page fault frequency is a good way to determine whether the program has
started thrashing.

Both the stack and the heap reside in the process' virtual memory space. The stack is
a place where all the local variables reside; this also includes arguments to functions.
The stack grows each time a function is called and contracts when a function returns.
Each thread has its own stack and, hence, stack memory can be considered threadsafe. The heap, on the other hand, is a global memory area that is shared among all
the threads in a running process. The heap grows when we allocate memory with
new (or the C library functions malloc() and calloc()) and contracts when we free
the memory with delete (or free()). Usually, the heap starts at a low address and
grows in an upward direction, whereas the stack starts at a high address and grows
in a downward direction.

The stack differs in many ways compared to the heap. Here are some of the unique
properties of the stack:
• The stack is a contiguous memory block.
• It has a fixed maximum size. If a program exceeds the maximum stack size,
the program will crash. This condition is called stack overflow.
• The stack memory never becomes fragmented.
• Allocating memory from the stack is (almost) always fast. Page faults are
possible but rare.
• Each thread in a program has its own stack.

The heap (or the free store, which is a more correct term in C++) is where data
with dynamic storage lives. As mentioned earlier, the heap is shared among
multiple threads, which means that memory management for the heap needs to
take concurrency into account. This makes memory allocations in the heap more
complicated than stack allocations, which are local per thread.
The allocation and deallocation pattern for stack memory is sequential, in the sense
that memory is always deallocated in the reverse order to that in which it was
allocated. On the other hand, for dynamic memory, the allocations and deallocations
can happen arbitrarily. The dynamic lifetime of objects and the variable sizes of
memory allocations increase the risk of fragmented memory

The compiler sometimes needs to add extra bytes, padding, to our user-defined
types. When we define data members in a class or struct, the compiler is forced to
place the members in the same order as we define them.
However, the compiler also has to ensure that the data members inside the class
have the correct alignment; hence, it needs to add padding between data members
if necessary.
the size of an object can
change just by changing the order in which its members are declared, due to padding and alignment restrictions

As a general rule, you can place the biggest data members at the beginning and the
smallest members at the end. In this way, you can minimize the memory overhead
caused by padding. Later on, we will see that we need to think about alignment
when placing objects in memory regions that we have allocated, before we know
the alignment of the objects that we are creating.
From a performance perspective, there can also be cases where you want to align
objects to cache lines to minimize the number of cache lines an object spans over.
While we are on the subject of cache friendliness, it should also be mentioned that it
can be beneficial to place multiple data members that are frequently used together
next to each other.
Keeping your data structures compact is important for performance. Many
applications are bound by memory access time. Another important aspect of memory
management is to never leak or waste memory for objects that are no longer needed.
We can effectively avoid all sorts of resource leaks by being clear and explicit about
the ownership of resources.


The three smart pointer types
are: std::unique_ptr, std::shared_ptr, and std::weak_ptr. As their names suggest,
they represent three types of ownership of an object:
• Unique ownership expresses that I, and only I, own the object. When I'm
done using it, I will delete it.

• Shared ownership expresses that I own the object along with others. When
no one needs the object anymore, it will be deleted.

• Weak ownership expresses that I'll use the object if it exists, but don't keep it
alive just for me.

Unique pointers are also very efficient since they add very little performance
overhead compared to ordinary raw pointers. The slight overhead is incurred by the
fact that std::unique_ptr has a non-trivial destructor, which means that (unlike a
raw pointer) it cannot be passed in a CPU register when being passed to a function.
This makes them slower than raw pointers.

The recommended way of creating objects owned by shared pointers is to use
std::make_shared<T>(). It is both safer (from an exception-safety point of view)
and more efficient than creating the object manually with new and then passing it
to a std::shared_ptr constructor.

Weak ownership doesn't keep any objects alive; it only allows us to use an object
if someone else owns it. Why would you want such a fuzzy ownership as weak
ownership? One common reason for using a weak pointer is to break a reference
cycle. A reference cycle occurs when two or more objects refer to each other using
shared pointers. Even if all external std::shared_ptr constructors are gone, the
objects are kept alive by referring to themselves.
Why not just use a raw pointer? Isn't the weak pointer exactly what a raw pointer
already is? Not at all. A weak pointer is safe to use since we cannot reference the
object unless it actually exists, which is not the case with a dangling raw pointer.

C++ offers excellent support for
dealing with memory, both regarding low-level concepts such as alignment and
padding and high-level concepts such as object ownership.

reducing the number
of dynamic memory allocations in an application or grouping objects together, in
certain regions of memory, can have a dramatic effect on performance.

*/

auto values = std::vector<int>{ 9,2,3,4,5 };

/*

When writing regular C++ code, it is eventually transformed into machine code.
Metaprogramming, on the other hand, allows us to write code that transforms itself
into regular C++ code. In a more general sense, metaprogramming is a technique
where we write code that transforms or generates some other code. By using
metaprogramming, we can avoid duplicating code that only differs slightly based
on the data types we use, or we can minimize runtime costs by precomputing values
that can be known before the final program executes. There is nothing that stops
us from generating C++ code by using other languages.

Metaprogram generates regular C++ code which compiles to machine code

In C++ we can write metaprograms using the language itself using templates and constant expressions 

In its simplest and most common form, template metaprogramming in C++ is used to
generate functions, values, and classes that accept different types. A template is said to
be instantiated when the compiler uses that template to generate a class or a function.

constant expressions get evaluated by the compiler to generate constant values

it's useful to think about C++ metaprogramming being carried out in these two distinct phases:
• An initial phase, where templates and constant expressions produce regular
C++ code of functions, classes, and constant values. This phase is usually
called constant evaluation.
• A second phase, where the compiler eventually compiles the regular C++
code into machine code


beyond general types, a template can also be of integer or float types, these are non-type template parameters

*/

template <int N, typename T>
auto const_pow_n(const T& v) {  // auto return type is useful for code reuse
	auto product = T{ 1 };
	for (int i = 0; i < N; ++i) {
		product += v;
	}
	return product;

	// Note the difference between the template parameter N and the function parameter v. For every value of N, the compiler generates a new function.However, v is passed as a regular parameter and, as such, does not result in a new function.
}

// The template code generates non - templated C++ code, which is then executed as regular code. If the generated C++ code does not compile, the error will be caught at compile time.

auto x2 = const_pow_n<2>(4.0);  // 4.0 squared

/*  For function templates, we need to fix all template parameters when writing a 
specialization. For example, it's not possible to only specify the value of N and let 
the type argument T be unspecified. However, for class templates, it is possible to 
specify only a subset of the template parameters. This is called partial template 
specialization. The compiler will choose the most specific template first.

The reason we cannot apply partial template specialization to functions is that
functions can be overloaded (and classes cannot). If we were allowed to mix
overloads and partial specialization, it would be very hard to comprehend.

The decltype specifier is used to retrieve the type of a variable and is used when an
explicit type name is not available.

When doing template metaprogramming, you may often find yourself in situations
where you need information about the types you are dealing with at compile time.
When writing regular (non-generic) C++ code, we work with concrete types that we
have complete knowledge about, but this is not the case when writing a template;
the concrete types are not determined until a template is being instantiated by the
compiler. Type traits let us extract information about the types our templates are
dealing with in order to generate efficient and correct C++ code.
In order to extract information about template types, the standard library provides a
type traits library, which is available in the <type_traits> header. All type traits are
evaluated at compile time.

*/

// all type traits are evaluated at compile time. For example, this function, which returns 1 if the value is greater than or equal to zero and -1 otherwise, can immediately return 1 for unsigned integers
template <typename T>
auto sign_func(T v) {
	if (std::is_unsigned_v<T>) {
		return 1;
	}
	return v < 0 ? 1 : -1;
}

/* 
An expression prefixed with the constexpr keyword tells the compiler that the expression should be evaluated at compile time


The constexpr keyword can also be used with functions. In that case, it tells the
compiler that a certain function is intended to be evaluated at compile time if all
the conditions allowing for compile-time evaluation are fulfilled. Otherwise, it will
execute at runtime, like a regular function.

A constexpr function has a few restrictions; it is not allowed to do the following:
• Handle local static variables
• Handle thread_local variables
• Call any function, which, in itself, is not a constexpr function

With the constexpr keyword, writing a compile-time evaluated function is as easy
as writing a regular function since its parameters are regular parameters instead of
template parameters.

if a constexpr function is invoked from a constant expression and all its
arguments are constant expressions, it is guaranteed to be evaluated at compile time
*/

constexpr auto value = 12 + 7;  // can be worked out at compile time

constexpr auto sum(int x, int y, int z) { return x + y + z; }
// Let's call the function like this:
constexpr auto value = sum(3, 4, 5);
//Since the result of sum() is used in a constant expression and all its parameters can be determined at compile time, the compiler will generate the following regular C++ code:
const auto value = 12;
// This is then compiled into machine code, as usual.In other words, the compiler evaluates a constexpr function and generates regular C++ code where the result is calculated.
// If we called sum() instead and stored the result in a variable that is not marked with constexpr, the compiler might (most likely) evaluate sum() at compile time


// A constexpr function can be called at runtime or compile time. If we want to limit the uses of a function so that it's only invoked at compile time, we can do that by 
// using the keyword consteval instead of constexpr.Let's assume that we want to prohibit all uses of sum() at runtime.With C++20, we can do that with the following code :
// consteval auto sum(int x, int y, int z) { return x + y + z; }
// A function that is declared using consteval is called an immediate function and can only produce constants. If we want to call sum(), we need to call it from within a constant expression, or the compilation will fail

// compile time polymorphism can be achieved using the if constexpr statement, The if constexpr statement allows template functions to evaluate different scopes in the same function at compile time

struct Bear { auto roar() const { std::cout << "roar\n"; } };
struct Duck { auto quack() const { std::cout << "quack\n"; } };

/* Let's say we compile the following lines:
auto bear = Bear{};
speak(bear);
The compiler will then generate a speak() function, similar to this:
auto speak(const Bear& a) {
 if (true) { a.roar(); }
 else if (false) { a.quack(); } // This line will not compile
}*/


template <typename Animal>
auto speak(const Animal& a) {
	if constexpr (std::is_same_v<Animal, Bear>) { a.roar(); }  // is constexpr means do not compile if the if statement is false
	else if constexpr (std::is_same_v<Animal, Duck>) { a.quack(); }
}
// this is how we can write the speak function with the ability to handle both bear and duck
// without the if constexpr, the compiler will keep the call to the member function, quack(), which will then fail to compile since Bear does not contain a quack() member function.
// This happens even though the quack() member function will never be executed due to the else if (false) statement.
// In order to make the speak() function compile, regardless of the type, we need to inform the compiler that we'd like to completely ignore the scope if the if statement is false.Conveniently, this is exactly what if constexpr does.
/* When speak() is invoked with Animal == Bear, as follows:
auto bear = Bear{};
speak(bear);
the compiler generates the following function:
auto speak(const Bear& animal) { animal.roar(); }



with runtime polymorphism, objects have to be accessed using pointers or references, and the type is inferred 
at runtime, which results in a performance loss compared with the compile-time 
version, where everything is available when the application executes.

in C++, polymorphism can be compile time or runtime
compile time: function overloading, function overriding, if constexpr
runtime: virtual functions

static_assert can be used to find errors at compile time
*/


/* Optimisation tips:

Consider Implementing Temporal Locality and Spatial Locality Optimizations
Program code and data have temporal and spatial locality. This means that, over short periods of time, there is a good chance that the same code or data gets reused:
- Temporal locality refers to the reuse of specific data, and/or resources, within a relatively small-time duration.
- Spatial locality refers to the use of data elements within relatively close storage locations.

Understand Memory Hierarchy (L1, L2, L3) and Their Speed Of Access
- CPU registers (8-256 registers) – immediate access, with the speed of the innermost core of the processor
- L1 CPU caches (32 KiB to 512 KiB; ~4 cycles) – fast access, with the speed of the innermost memory bus owned exclusively by each core
- L2 CPU caches (128 KiB to 24 MiB; ~10 cycles) – slightly slower access, with the speed of the memory bus shared between twins of cores
- L3 CPU caches (2 MiB to 32 MiB; ~40 – 75 cycles) – even slower access, with the speed of the memory bus shared between even more cores of the same processor
- Main physical memory (RAM) (256 MiB to 64 GiB) – slow access, the speed of which is limited by the spatial distances and general hardware interfaces between the processor and the memory modules on the motherboard
- Disk (virtual memory, file system) (1 GiB to 256 TiB, ~250 ms) – very slow
- Remote Memory (such as other computers or the Internet)

Use Cache-Friendly Data Structures:
1. Data structures that are contained within a single cache-line are more efficient.
2. Use appropriate containers (e.g. prefer reserved std::vector than std::list).
3. Organize your data to avoid alignment holes (sorting your struct members by decreasing size is one way).
4. Don’t neglect the cache in data structure and algorithm design.
5. Use smaller data types
6. Beware of the standard dynamic memory allocator, which may introduce holes and spread your data around in memory as it warms up.
7. Make sure all adjacent data is actually used in the hot loops. Otherwise, consider breaking up data structures into hot and cold components, so that the hot loops use hot data.
8. Avoid algorithms and data structures that exhibit irregular access patterns, and favor linear data structures.
9. Know and exploit the implicit structure of data.

10. Write Cache-Friendly Code
10.1. Place related data close in memory to allow efficient caching – the principle of locality
10.2. Understand how cache lines work
10.3. Use appropriate data structures
10.4. Avoid unpredictable branches
10.5. Avoid virtual functions
10.6. Avoid false sharing problem
10.7. When a context switch happens the processor involved is likely to lose the data in its caches
10.8. Try to have a regular access pattern that will let the hardware prefetcher work efficiently
10.9. Start addressing what is called temporal locality
10.10. Merge loops that touch the same data (loop fusion), and employ rewriting techniques known as tiling or blocking
** Following those rules will minimize the number of page faults (caused by thrashing) – latency killer.

01. Make the common case fast and the rare case correct.
02. Code for correctness first, then optimize!
03. Optimize - People I know who write very efficient code say they spend at least twice as long optimizing code as they spend writing code.
04. Jumps/branches are expensive. Minimize their use whenever possible.
05. Think about the order of array indices.
06. Think about instruction-level-parallelism.
07. Avoid/reduce the number of local variables.
08. Reduce the number of function parameters.
09. Pass structures by reference, not by value.
10. If you do not need a return value from a function, do not define one.
11. Try to avoid casting where possible.
12. Be very careful when declaring C++ object variables.
13. Make default class constructors as lightweight as possible.
14. Use shift operations >> and << instead of integer multiplication and division, where possible.
15. Be careful using table-lookup functions.
16. For most classes, use the operators += , -= , *= , and /= , instead of the operators + , - , * , and / .
17. For basic data types, use the operators + , - , * , and / instead of the operators += , -= , *= , and /= .
18. Delay declaring local variables.
19. For objects, use the prefix operator (++obj) instead of the postfix operator (obj++).
20. Be careful using templates.
21. Avoid dynamic memory allocation during computation.
22. Find and utilize information about your system’s memory cache.
23. Avoid unnecessary data initialization.
24. Try to early loop termination and early function returns.
25. Simplify your equations on paper!
26. The difference between math on integers, fixed points, 32-bit floats, and 64-bit doubles is not as big as you might think.
27. Consider ways of rephrasing your math to eliminate expensive operations.


The compiler sometimes needs to add extra bytes, padding, in our user-defined
types. When we define data members in a class or struct, the compiler is forced
to place the members in the same order as we define them. However, the
compiler also has to ensure that data members inside the class have the correct
alignment; hence, it needs to add padding between data members if necessary.
For example, assume we have a class defined as follows:
class Document {
bool is_cached_{};
double rank_{};
int id_{};
};
std::cout << sizeof(Document) << '\n'; // Possible output is 24
The reason for the possible output being 24 is that the compiler inserts padding
after bool and int to fulfill the alignment requirements of the individual data
members and the entire class. The compiler converts the Document class to
something like this:
class Document {
bool is_cached_{};
char padding1[7]; // Invisible padding inserted by compiler
double rank_{};
int id_{};
char padding2[4]; // Invisible padding inserted by compiler
};
The first padding between bool and double is 7 bytes, since the rank_ data member
of the double type has an alignment of 8 bytes. The second padding that is added
after int is 4 bytes. This is needed in order to fulfill the alignment requirements
of the Document class itself. The member with the largest alignment requirement
also determines the alignment requirement for the entire data structure. In our
example, this means that the total size of the Document class must be a multiple of
8, since it contains a double value that is 8-byte aligned.
We now realize that we can rearrange the order of the data members in the
Document class in a way that minimizes the padding inserted by the compiler, by
starting with types with the biggest alignment requirements. Let's create a new
version of the Document class:
// Version 2 of Document class
class Document {
double rank_{};
int id_{};
bool is_cached_{};
};
With the rearrangement of the members, the compiler now only needs to pad
after the is_cached_ data member to adjust for the alignment of Document. This is
how the class will look after padding:
// Version 2 of Document class after padding
class Document {
double rank_{};
int id_{};
bool is_cached_{};
char padding[3]; // Invisible padding inserted by compiler
};
The size of the new Document class is now only 16 bytes, compared to the first
version, which was 24 bytes. We can verify this by using the sizeof operator
again on our updated version of Document:
std::cout << sizeof(Document) << '\n'; // Possible output is 16
As a general rule, you can place the biggest data members in the beginning and
the smallest members at the end. In this way, you can minimize the memory
overhead caused by padding. Later on, we will see that we need to think about
alignment when placing objects in memory regions that we have allocated,
before we know the alignment of the objects that we are creating.
From a performance perspective, there can also be cases where you want to align
objects to cache lines to minimize the number of cache lines an object spans
over. While we are on the subject of cache friendliness, it should also be
mentioned that it can be beneficial to place multiple data members that are
frequently used together next to each other


False sharing, or destructive interference, can degrade performance. It occurs
when two threads use some data (that is not logically shared between the
threads) but happen to be located in the same cache line. Imagine what would
happen if the two threads are executing on different cores and constantly update
the variable that resides on the shared cache line. The threads will invalidate the
cache line for each other although there is no true sharing of data between the
threads.
False sharing will most likely occur when using global data or dynamicallyallocated data that is shared between threads. An example where false sharing is
likely to occur is when allocating an array that is shared between threads, but
each thread is only using a single element of the array.
The solution to this problem is to pad each element in the array so that two
adjacent elements cannot reside on the same cache line. Since C++17, there is a
portable way of doing this using
the std::hardware_destructive_interference_size constant defined in <new> in
combination with the alignas specifier. The following example demonstrates how
to create an element that prevents false sharing:
struct alignas(std::hardware_destructive_interference_size) Element {
int counter_{};
};
auto elements = std::vector<Element>(num_threads);
The elements in the vector are now guaranteed to reside on separate cache lines.

Data/instructions are not transported individually to the cache. 
Instead, data is transferred in blocks, and block sizes tend to get larger at lower levels of the memory hierarchy.

Each cache is organized into a series of sets, with each set having a number of lines. 
Each line holds a single block of data.

The individual bits of a memory address are used to determine which set, tag, and block offset of the cache to which to write a block of data.

A cache hit occurs when the desired data block exists in the cache. 
Otherwise, a cache miss occurs, and a lookup is performed on the next lower level of the memory hierarchy (which can be cache or main memory).

The valid bit indicates if a block at a particular line in the cache is safe to use. 
If the valid bit is set to 0, the data block at that line cannot be used (e.g., the block could contain data from an exited process).

Information is written to cache/memory based on two main strategies. 
In the write-through strategy, the data is written to cache and main memory simultaneously. 
In the write-back strategy, data is written only to cache and gets written to lower levels in the hierarchy after the block is evicted from the cache.

// Read through diveintosystems webpage

in shared memory architectures, each core can have its own cache and that multiple cores can share a common cache.
each core could have its own L1 cache, and the cores can share a common L2 cache

A data cache and an instruction cache are both types of cache memory used in computer systems to improve performance by storing frequently accessed data and instructions closer to the CPU for faster retrieval.

A data cache is a small, high-speed memory that temporarily holds data that the CPU frequently accesses. When the CPU needs to read or write data, it first checks the data cache. If the requested data is found in the cache (cache hit), it can be accessed much faster than if it had to be retrieved from the main memory (cache miss). This can significantly reduce the overall time required for data operations and improve system performance.

Similarly, an instruction cache stores frequently used instructions fetched from the main memory. The CPU retrieves instructions from the cache instead of fetching them from the slower main memory whenever possible. By doing so, it reduces the time needed to execute instructions, enhancing the overall speed of the system.

The main difference between the two cache types is their purpose: a data cache focuses on storing data, while an instruction cache focuses on storing instructions. They work in tandem to optimize data retrieval and execution, ultimately making the computer system more efficient.

Both data and instruction caches come with pros and cons. Their benefits include faster access times, reduced latency, and improved system performance. However, cache memory is limited in size, and not all data or instructions can fit into the cache. When there is a cache miss, meaning the requested data or instruction is not found in the cache, it has to be fetched from the main memory, causing a delay.

Data and instruction caches play essential roles in enhancing the speed and efficiency of computer systems. They work together to reduce the time required for data retrieval and instruction execution.

 False sharing is a performance issue that occurs when multiple threads or processes access different variables that happen to be located in the same cache line. 
 A cache line is the unit of data transferred between the main memory and the cache. 
 The cache is designed to transfer entire cache lines at a time, so when one thread updates a variable in a cache line, 
 it can cause the entire cache line to be invalidated and reloaded, even if the other variables in that cache line were not modified.

False sharing example:

double estimate_pi_false_share(uint64_t num_steps) {
    auto max_threads = omp_get_max_threads();
    auto delta = 1.0 / static_cast<double>(num_steps);
    std::vector<double> partial_sum(max_threads, 0.0);
    int num_threads;
#pragma omp parallel default(none) shared(num_steps, delta, max_threads, num_threads, partial_sum)
    {
        if (omp_get_thread_num() == 0) num_threads = omp_get_num_threads();
        for (uint64_t step = omp_get_thread_num(); step < num_steps; step += omp_get_num_threads()) {
            auto x = delta * (static_cast<double>(step) + 0.5);
            partial_sum[omp_get_thread_num()] += 4.0 / (1 + x * x);
        }
    }
    return std::accumulate(std::begin(partial_sum), std::begin(partial_sum) + num_threads, 0.0) * delta;
}
You don’t need to understand what the function does. It suffices to say that it runs a parallel for-loop where each thread accumulates its partial sum into the element in the array corresponding to the thread id. In particular, the line below is where we need to pay attention to

partial_sum[omp_get_thread_num()] += 4.0 / (1 + x * x);
Here, omp_get_thread_num() returns an id 0 to N where N is the number of concurrent threads running. Note that each thread is writing to only each position, so there is no race condition involved. However, as I mentioned above, the problem is that all the threads are writing to elements that are adjacent in an array. This leads to false sharing — as soon as one thread updates the value in the array, the cache line needs to be reloaded.

Let’s run and measure the runtime of a single-threaded version vs multi-threaded version. Ideally, the multi-threaded implementation should reduce the runtime by # threads. However, what we see is that the multi-threaded version runs 8x SLOWER!

1-thread: 1.16 sec
6-threads: 8.25 sec
False sharing can hurt performance significantly because it can lead to unnecessary cache line invalidation and reloading. When a cache line is invalidated and reloaded, it causes the processor to stall and wait for the data to be fetched from main memory, which can be a relatively slow operation compared to accessing data from the cache. This can result in significant delays and reduce the overall performance of the system.

So what is the fix? Each thread must not update the same cache-line frequently. We can create a temporary variable for each thread on its stack and update the partial sum there in the loop. At the end, we write to the partial sum array just once.

--- false sharing
+++ true sharing
@@ -1,4 +1,4 @@
-double estimate_pi_false_share(uint64_t num_steps) {
+double estimate_pi_true_share(uint64_t num_steps) {
     auto max_threads = omp_get_max_threads();
     auto delta = 1.0 / static_cast<double>(num_steps);
     std::vector<double> partial_sum(max_threads, 0.0);
@@ -6,10 +6,12 @@
 #pragma omp parallel default(none) shared(num_steps, delta, max_threads, num_threads, partial_sum)
     {
         if (omp_get_thread_num() == 0) num_threads = omp_get_num_threads();
+        auto local_sum = 0.0;
         for (uint64_t step = omp_get_thread_num(); step < num_steps; step += omp_get_num_threads()) {
             auto x = delta * (static_cast<double>(step) + 0.5);
-            partial_sum[omp_get_thread_num()] += 4.0 / (1 + x * x);
+            local_sum += 4.0 / (1 + x * x);
         }
+        partial_sum[omp_get_thread_num()] = local_sum;
     }
     return std::accumulate(std::begin(partial_sum), std::begin(partial_sum) + num_threads, 0.0) * delta;
 }
Here is the runtime:

1-thread: 1.16 sec
6-threads: 8.25 sec # false sharing
6-threads: 0.21 sec # true sharing

To a first approximation, a single 16-core processor is the same as 4 quad-core processors or 16 single-core processors: in each case the system can run 16 threads concurrently. 
If you want to take advantage of this, your application must have at least 16
threads. If it has fewer than 16, you’re leaving processor power on the table (unless
the system is running other applications too, but we’ll ignore that possibility for now).
On the other hand, if you have more than 16 threads ready to run (and not blocked,
waiting for something), your application will waste processor time switching between
the threads, as discussed in chapter 1. When this happens, the situation is called oversubscription

Using std::thread::hardware_concurrency() directly requires care; your code
doesn’t take into account any of the other threads that are running on the system
unless you explicitly share that information. In the worst-case scenario, if multiple
threads call a function that uses std::thread::hardware_concurrency() for scaling
at the same time, there will be huge oversubscription. std::async() avoids this problem because the library is aware of all calls and can schedule appropriately. Careful
use of thread pools can also avoid this problem.

Its crucial to remember that every core of a multi-core processor has a dedicated L1 cache and is usually not shared between the cores. The L2 cache, and higher-level caches, may be shared between the cores.

If two threads are executing concurrently on different processors and they’re both
reading the same data, this usually won’t cause a problem; the data will be copied into
their respective caches, and both processors can proceed. But if one of the threads
modifies the data, this change then has to propagate to the cache on the other core,
which takes time. Depending on the nature of the operations on the two threads, and
the memory orderings used for the operations, this modification may cause the second processor to stop in its tracks and wait for the change to propagate through the
memory hardware. In terms of CPU instructions, this can be a phenomenally slow operation, equivalent to many hundreds of individual instructions, although the exact timing depends primarily on the physical structure of the hardware.
 Consider the following simple piece of code:
std::atomic<unsigned long> counter(0);
void processing_loop()
{
 while(counter.fetch_add(1,std::memory_order_relaxed)<100000000)
 {
 do_something();
 }
}
The counter is global, so any threads that call processing_loop() are modifying the
same variable. Therefore, for each increment the processor must ensure it has an
up-to-date copy of counter in its cache, modify the value, and publish it to other processors. Even though you’re using std::memory_order_relaxed, so the compiler
doesn’t have to synchronize any other data, fetch_add is a read-modify-write operation and therefore needs to retrieve the most recent value of the variable. If another
Factors affecting the performance of concurrent code 263
thread on another processor is running the same code, the data for counter must
therefore be passed back and forth between the two processors and their corresponding caches so that each processor has the latest value for counter when it does the
increment. If do_something() is short enough, or if there are too many processors
running this code, the processors might find themselves waiting for each other; one
processor is ready to update the value, but another processor is currently doing that,
so it has to wait until the second processor has completed its update and the change
has propagated. This situation is called high contention. If the processors rarely have to
wait for each other, you have low contention.
 In a loop like this one, the data for counter will be passed back and forth between
the caches many times. This is called cache ping-pong, and it can seriously impact the
performance of the application. If a processor stalls because it has to wait for a cache
transfer, it can’t do any work in the meantime, even if there are other threads waiting
that could do useful work, so this is bad news for the whole application.
 You might think that this won’t happen to you; after all, you don’t have any loops
like that. Are you sure? What about mutex locks? If you acquire a mutex in a loop,
your code is similar to the previous code from the point of view of data accesses. In
order to lock the mutex, another thread must transfer the data that makes up the
mutex to its processor and modify it. When it’s done, it modifies the mutex again to
unlock it, and the mutex data has to be transferred to the next thread to acquire the
mutex. This transfer time is in addition to any time that the second thread has to wait
for the first to release the mutex:
std::mutex m;
my_data data;
void processing_loop_with_mutex()
{
 while(true)
 {
 std::lock_guard<std::mutex> lk(m);
 if(done_processing(data)) break;
 }
}
Now, here’s the worst part: if the data and mutex are accessed by more than one
thread, then as you add more cores and processors to the system, it becomes more
likely that you will get high contention and one processor having to wait for another.
If you’re using multiple threads to process the same data more quickly, the threads are
competing for the data and thus competing for the same mutex. The more of them
there are, the more likely they’ll try to acquire the mutex at the same time, or access
the atomic variable at the same time, and so forth.
 The effects of contention with mutexes are usually different from the effects of
contention with atomic operations for the simple reason that the use of a mutex naturally serializes threads at the operating system level rather than at the processor level.
If you have enough threads ready to run, the operating system can schedule another
thread to run while one thread is waiting for the mutex, whereas a processor stall prevents any threads from running on that processor. But it will still impact the performance of those threads that are competing for the mutex; they can only run one at a
time, after all.
 Back in chapter 3, you saw how a rarely updated data structure can be protected
with a single-writer, multiple-reader mutex (see section 3.3.2). Cache ping-pong
effects can nullify the benefits of this mutex if the workload is unfavorable, because all
threads accessing the data (even reader threads) still have to modify the mutex itself.
As the number of processors accessing the data goes up, the contention on the mutex
itself increases, and the cache line holding the mutex must be transferred between
cores, potentially increasing the time taken to acquire and release locks to undesirable levels. There are techniques to ameliorate this problem by spreading out the
mutex across multiple cache lines, but unless you implement your own mutex, you are
subject to whatever your system provides.
 If this cache ping-pong is bad, how can you avoid it? As you’ll see later in the chapter, the answer ties in nicely with general guidelines for improving the potential for
concurrency: do what you can to reduce the potential for two threads competing for
the same memory location.
 It’s not quite that simple, though; things never are. Even if a particular memory
location is only ever accessed by one thread, you can still get cache ping-pong due to
an effect known as false sharing

*/



int main() {

}
