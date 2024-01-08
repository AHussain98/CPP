# include <iostream>
# include <algorithm>
# include <vector>

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


*/

auto x = 10;  // auto is useful because you can't leave an auto variable uninitialised
auto v = { 1,2,3,4,5 }
auto num_above_3 = std::count_if(v.begin(), v.end(), [](int i) {return i > 3; });  //  stateless lambda

int main() {

}

# include <iostream>
# include <algorithm>
# include <vector>
# include <array>

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



*/



int main() {

}
