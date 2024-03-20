# include <iostream>
# include <vector>
# include <algorithm>
# include <array>
# include <string>
# include <unordered_set>
# include <span>
# include <ranges>

// c++ treats memory as a sequence of cells, each is 1 byte in size and each has an address
// accessing a byte by its address is O(1)
// cores wit within the cpu, each core has its own two levels of cahce and register, and access to the cpu-wide L3 cache

// cachelines are also known as blocks, usually 64 bytes
// when accessing a byte in memory, the machine is not only fetching the byte that is asked for, instead the machine always fetches a cacheline
// the various caches between the CPU and main memory keep track of these 64 byte blocks, instead of individual bytes

// caches are tiny compared to the amount of main memory available
// there are orders of magnitude of difference between two adjacent layers of cache

// accessing data that has recently been used and therefore potentially already resides in cache will make your program faster. This is known as temporal locality
// accessing data located near some other data you are using will increase the likelyhood that the data you need is already in a cacheline that was fetched from the main memory earlier, this is known as spatial locality, this is why its beneficial to access elements sequentially in memory

// constantly wiping out the cache lines in inner loops results in poor performance, this is called cache thrashing
// modern processors are also usually equipped with a prefetcher, which can automatically recognise memory access patterns and try to prefetch data from memory into the caches that are likely to be accessed in the near future
// REMEMBER: even if memory accesses are constant time operations, caching can have dramatic effects on the actual time it takes to access the memory. Think about cache constantly

/* A container is
a data structure that contains a collection of elements. The container manages the
memory of the elements it holds. This means that we don't have to explicitly create
and delete the objects that we put in a container. We can pass objects created on the
stack to a container and the container will copy and store them on the free store*/

// sequence containers keep the elements in the order we specify when adding the elements to the container
// these are array, vector, deque, list and forward list
// choosing a sequence container -> number of elements, useage pattern? read? traverse> delete? rearrange? where is data most often added or removed in the sequence? sorting? order important?

// vector is dynamic array, laid out contigously in memory, constant random access, excellent performance when traversing elements in order due to spatial locality
// size and capacity
// adding elements to teh end of a vector using pushback is fast as long as size is less than capacity
/* When adding an element and there is no room for
more, the vector will allocate a new internal buffer and then move all of the elements
to the new space. The capacity will grow in such a way that resizing the buffer rarely
happens, thus making push_back() an amortized constant-time operation.
A vector template instance of type std::vector<Person> will store Person objects
by value. When the vector needs to rearrange the Person objects (for example, as
a result of an insert), the values will be copy constructed or moved. Objects will be
moved if they have a nothrow move constructor. Otherwise, the objects will be copy
constructed in order to guarantee strong exception safety

Internally, std::vector uses std::move_if_noexcept in order to determine whether
the object should be copied or moved. The <type_traits> header can help you to
verify at compile time that your classes are guaranteed to not throw an exception
when moved:
static_assert(std::is_nothrow_move_constructible<Person>::value);*/

// if we are adding newly created objects to the vector, we can use emplace_back(), which will create the object in place for you, instead creating an object and copying/moving it to the vector with push_back
// capacity of the vector changes by adding an element so size == capacity, by calling reserve() and by calling shrink_to_fit()
// other than that, the vector will not change the capacity, and hence will not allocate or deallocate dynamic memory. For example, even clear() does not resize teh vector

// c++20 introduced two free functions, erase and erase_if

std::vector<int> vec{ 1,2,3,4,5 };
//std::erase(vec, 5); // erase 5 from vec

// as an alternative to the dynamically sized vector, the standard library also provides a fixed size version named std::array that managed its elements by using the stack as opposed to the free store
std::array<int, 5> arr{ 1,2,3,4,5 }; // declare an array called arr with 5 int elements
auto b = std::array<int, 10>{}; // another way of declaring a stack array

// a and b are not the same type, so we have to specify the size and type of the array when passing it as a function parameter, for exmaple
// this is a big advantage of std::array over c style arrays, which lose size information when passed to a function, since they are automatically converted to a pointer to the first element of the array (this is referred to as array decay)

void array_func(const std::array<int, 5>& arr)
{
	// this function only takes an array of 5 ints by reference
}


// Deque: useful when we want to frequently add elements to the front and end of a sequence
/* If you are using a std::vector
and need to speed up the inserts at the front, you can instead use std::deque, which
is short for double-ended queue. std::deque is usually implemented as a collection
of fixed-size arrays, which makes it possible to access elements by their index in
constant time. However, all of the elements
are not stored contiguously in memory, which is the case with std::vector and
std::array, bad for cache performance */


// std::list is a doubly linked ist, each element has a link to the next element and the previous element, list can be iterate over forwards and backwards
// singly linked list is called forward_list
// backward links take up more memory so use forward list if you dont need backwards traversal

/* Another interesting feature of the forward list is
that it's optimized for very short lists. When the list is empty, it only occupies one
word, which makes it a viable data structure for sparse data.
Note that even if the elements are ordered in a sequence, they are not laid out
contiguously in memory like the vector and array are, which means that iterating a
linked list will most likely generate a lot more cache misses compared to the vector.*/

// forward_list is more memory efficient since it only has one forward pointer per element

// lists are the only containers that support splicing, which means transferring elements without moving or copying them
// its therefore possible to concatenate two lists into one in constant time O(1)


// std::string is a typedef for std::basic_string, after c++17 this is now laid out contigously in memory and now we can pass string objects to API's that expect an array of chars
/*Most implementations of std::basic_string utilize something called small object
optimization, which means that they do not allocate any dynamic memory if the size
of the string is small.*/


// Associative containers place their elements based on the element itself, you cant push front or push back
// instead the elements are added in a way that makes it possible to find the element without the need to scan the entire container
// therefore the associative containers have some requirements for the object we want to store in the containers

// two main types of associative container:

// ordered associative containers, these are based on trees, they use trees for storing their elements. map, set, multimap, multiset
// they require that the elements are ordered by the less than < operator. The functions for adding, deleting and finding elements are logN

// unordered associative containers, based on hash tables, the containers use a hash table for storing the elements
// they require that the elements are compared with the equality operator == and that there is a way to compute a hash value based on an element
// the functions for adding, deleting and finding elements are all O(1) in the hash table-based containers. These are unordered set and unorderd map, unordered multiset and unordered multimap

/* Since C++20, all associative containers are equipped with a function named 
contains(), which should be used when you want to know whether a container 
contains some specific elements.  Always use pecialised functions such as these when needed, they're uaranteed to be most efficient  */

// ordered associative containers guarantee that insert, delete and search can be done in logarithmic time logN
// library implementations we know about use some kind of self balancing binary search tree
/* The fact that the tree stays approximately 
balanced is necessary for controlling the height of the tree, and, hence, also the 
worst-case running time when accessing elements. There is no need for the tree to 
pre-allocate memory, so, typically, a tree will allocate memory on the free store each 
time an element is inserted and also free up memory whenever elements are erased. */

// the unordered versions of sets and maps use hash tables to store elements
// in theory these have amortized constant insert, add and delete operations, which perform better than the tree based versions
// However in practice the difference may not be so obvious, especially if we do NOT store a very large number of elements 
// A hash table keeps it elements in some sort of array of buckets. When adding an element to the hash table, an integer is computed for the element using a hash function. This integer is called the hash of the element
/*  The hash value is then limited to the size of the array 
(by using the modulo operation, for example) so that the new limited value can be 
used as an index in the array. Once the index is computed, the hash table can store 
the element in the array at that index. The lookup of an element works in a similar 
manner by first computing a hash value for the element we are looking for and then 
accessing the array

 What if two different elements generate the same index,
either because they produced the same hash value, or because two different hash
values are being limited to the same index? When two non-equal elements end up at
the same index, we call that a hash collision. This is not just an edge case: this will
happen a lot, even if we are using a good hash function, and especially if the array is
small when compared to the number of elements we are adding. There are various
ways of dealing with hash collisions. Here, we will focus on the one that is being
used in the standard library, which is called separate chaining.

Separate chaining solves the problem of two unequal elements ending up at the
same index. Instead of just storing the elements directly in the array, the array is a
sequence of buckets. Each bucket can contain multiple elements, that is, all of the
elements that are hashed to the same index. So, each bucket is also some sort of
container. The exact data structure used for the buckets is not defined, and it can
vary for different implementations. However, we can think of it as a linked list and
assume that finding an element in a specific bucket is slow, since it needs to scan the
elements in the buckets linearly.

*/

// the hash value, which can be computed in constant time wrt the size of the container, determines which bucket an element will be placed in
// since objects can generate the same hash value and therefore be stored in the same bucket, each key needs to provide an equals function, which is used to compare the key we are looking for with all the keys in the bucket
// If two keys are equal, they are required to generate the same hash value. But objects with the same hash value do not need to be the same

// a good hash function ensures that elements are distributed evenly among the buckets to minimise hash collisions
// suppose we want to use a person class as a key in an unordered_set, lets write the equal predicate
struct person
{
	int age;
	std::string name;
};

auto person_eq = [](const person& lhs, const person& rhs) { return lhs.name == rhs.name && lhs.age == rhs.age; };

// for two person objects to be equal, they need to have the same name and age
/* We can now define the hash predicate by combining the hash values of all of 
the data members that are included in the equals predicate. Unfortunately, there is 
no function in the C++ standard yet to combine hash values, but there is a good one 
available in Boost, which we will use here:
#include <boost/functional/hash.hpp>
auto person_hash = [](const Person& person) { 
 auto seed = size_t{0};
 boost::hash_combine(seed, person.name()); 
 boost::hash_combine(seed, person.age()); 
 return seed;
}*/


// with the equality and hash functions defined, we can create our unordered_set, remember decltype yields the type of a specified expression
// auto persons = std::unordered_set<person, decltype(person_hash), decltype(person_eq)>{ 100, person_hash, person_eq };  // 100 buckets
// <key, hash, keyequal>, constructor is bucket_count, hash func, equality func

/* A good rule of thumb is to always use all of the data members that are being used 
in the equal function when producing the hash value. That way, we adhere to the 
contract between equals and hash, and, at the same time, this enables us to provide 
an effective hash value. For example, it would be correct but inefficient to only use 
the name when computing the hash value, since that would mean that all Person
objects with the same name would end up in the same bucket. Even worse, though, 
would be to include data members in the hash function that are not being used in the 
equals function. This would most likely result in a disaster where you cannot find 
objects in your unordered_set that, in fact, compare equally  */

/* Apart from creating hash values that distribute the keys evenly among the buckets, 
we can reduce the number of collisions by having many buckets. The average 
number of elements per bucket is called the load factor. In the preceding example, 
we created an unordered_set with 100 buckets. If we add 50 Person objects to the set, 
load_factor() would return 0.5. The max_load_factor is an upper limit of the load 
factor, and when that value is reached, the set will need to increase the number of 
buckets, and, as a consequence, also rehash all the elements that are currently in the 
set. It's also possible to trigger a rehash manually with the rehash() and reserve()
member functions.  */


// container adaptors: stack, queue and priority queue, these can be implemented by vector, list or deque


// priority queue gives a constant time lookup of the element with highest priority
// by default, priority is defined using the less than operator of the elements, insert and delete both run in logarithmic time


// c++17 introduced string_view and c++20 instroduced std::span
// these are not containers, but lightweight views of a sequence of contigous elements
// they are non-owning reference types, they do not allocate memory
/* A std::string_view contains a pointer to the beginning of an immutable string 
buffer and a size. Since a string is a contiguous sequence of characters, the pointer 
and the size fully define a valid substring range. Typically, a std::string_view
points to some memory that is owned by a std::string. But it could also point to 
a string literal with static storage duration or something like a memory-mapped file.  */

// performance improvement for creating substrings becaus eyou dont need to create a new string with null char termination, you can just point to thechar in constant time
// also performance improvement when passing to a fucntion as here's no copies made 

auto some_func(std::string_view s) {  // pass by value  
}


/* A std::string_view instance can be constructed efficiently both from a std::string and a string literal and is, therefore, a well-suited type for function parameters  */

// eliminate array decay with std::span, this represents a safer way to pass arrays to functions
// span holds both the pointer to the memory and the size together in one object, we can use ti as a single type when passing sequences of elements to functions

auto span_func(std::span<float> buffer)  // pass by value
{
	for (auto a : buffer)
	{
		std::cout << a;  // using iterators with a build in array!!
	}
}

/* A span is also more convenient to use over a built-in array since it acts more like a 
regular container with support for iterators.
There are many similarities between std::string_view and std::span when it comes 
to the data members (pointer and size) and the member functions. But there are also 
some notable differences: the memory pointed to by std::span is mutable, whereas 
the std::string_view always points to constant memory. std::string_view also 
contains string-specific functions such as hash() and substr(), which are naturally 
not part of std::span. Lastly, there is no compare() function in std::span, so it's not 
possible to directly use the comparison operators on std::span objects  */


// complexity guarantees only become relevant for large datasets, each container has its own overhead costs
// remember computers are equipped with memory caches that make the use of data structures like vectors preferred

/*  Use contains() when checking whether 
an element exists in an associated container. Use empty() if you want to know 
whether a container has any elements or is empty. Apart from expressing the intent 
more clearly, it also has performance benefits. Checking the size of a linked list is an 
O(n) operation, whereas calling empty() on a list runs in constant time, O(1).*/


// when iterating over elements, consider spatial and temporal locality
// when iterating over elements stored contigously in memory, we increase the probability that the data we need is already cached if we keep our objects small, thanks to spatial locality

// define two structs

struct smallObject {
	std::array<char, 4> data{};
	int score_{std::rand()};
};

struct bigObject {
	std::array<char, 256> data{};
	int score{ std::rand() };
};

// only array size differs
// iterating over a vector of small objects will end up being almost 10 times faster! This is due to objects being small eough to fit in cache


// keep classes small and give them a single responsibility

// whenever possible, make classes smaller by moving sensible member data and functions into a ne class, and store a pointer to the neew class instead, this reduces the memory size of the initial class


// algorithms:
// for each, calls the function provided once for each element in the container, return value is ignored

void print(const std::vector<int>& v)
{
	std::ranges::for_each(v, [](auto i) {std::cout << i << ","; });
}

auto in = std::vector{ 1, 2, 3, 4 };
auto out = std::vector<int>(in.size());
auto lambda = [](auto&& i) { return i * i; };

// std::ranges::fill to fill a container with an element
// generate() calls a function for each element and stores the return value at the current element

// sort() is most common sorting function

// find() for searching a container, returns end() iterator if element cannot be found, O(N) in worst case

// if we know the collection is already sorted, we can use binary search, returns true or false if the element is/isnt found. O(N) for containers that provide random access to their elements

// is_sorted can be used to check if a container is sorted, runs in O(N)

// distance() to get the inde of a element

// none_of, all_of, any_of check for conditions

// count() to count the number of matching elements, O(N)

// std::min, std::max


// Iterators are objects that provide a generic way to navigate through the elements in a sequence
// algorithms can operate on iterators so they do not depend on the type of container and how its elements are arranged
// Iterators are objects that represent a position in a sequence. They are used to navigate through the sequence and readn/write the element at their current position
// Iterators can be considered an object with the same properties of a raw pointer, it can be stepped to the next element and dereferenced
// a sentinel value is a special value that indicates the end of a sequence, they make it possible for iterators to run through a sequence without knowing how many elements are in it
// the only requirement of the sentinel is that it can be compared with the iterator

std::vector<int> numbers{ 1,2,3,4,5 };
auto it = numbers.begin();
auto end = numbers.end();  // this actually points to one past the last element of the vector

// end actually points out of bounds, so we are not allowed to dereference it, but we can read the pointer value and compare with it

// a range is a replacement for the iterator-sentinel pairs
// any type that exposes begin() and end() functions is considered a range (given that these functions return iterators)
// algorithms in the std::range namespace can operate on ranges instead of iterator pairs, we can pass the ranges directly to the algorithms

auto vec = std::vector{ 1,2,3,4,5 };

// iterators cna be moved forward or backwards
std::next(it); // or it++
std::prev(it);  // it it--

// Jump to an arbitrary position: std::advance(it, n) or it += n
// read: auto value = *it;
//write: *it = 5;

/* iterators might operate on data sources where a write or read implies 
a step forward. Examples of such data sources could be user input, a network 
connection, or a file. These data sources require the following operations:
• Read only and step forward: auto value = *it; ++it;
• Write only and step forward: *it = value; ++it;    */


/*  Types of iterator:

• std::input_iterator: Supports read only and step forward (once). One-pass
algorithms such as std::count() can use input iterators. std::istream_
iterator is an example of an input iterator.
• std::output_iterator: Supports write only and step forward (once). Note that
an output iterator can only write, not read. std::ostream_iterator is an
example of an output iterator.
• std::forward_iterator: Supports read and write and step forward. The value
at the current position can be read or written multiple times. Singly linked
lists such as std::forward_list expose forward iterators.
• std::bidirectional_iterator: Supports read, write, step forward, and step
backward. The doubly linked std::list exposes bidirectional iterators.
• std::random_access_iterator: Supports read, write, step forward, step
backward, and jump to an arbitrary position in constant time. The elements
inside std::deque can be accessed with random access iterators.
• std::contiguous_iterator: The same as random access iterators, but also
guarantees that the underlying data is a contiguous block of memory, such
as std::string, std::vector, std::array, std::span, and the (rarely used)
std::valarray

*/

// functions from <algorithm> can only modify the elements in a specified range, elements are never added or deleted from the underlying container. Therefore the size of the container is not changed by the algorithm
/* For example, std::remove() or std::unique() do not actually remove elements from 
a container (despite their names). Rather, it moves the elements that should be kept 
to the front of the container and then returns a sentinel that defines the new end of 
the valid range of elements:
*/


// algorithms with output require allocating data

/* Algorithms that write data to an output iterator, such as std::copy() or 
std::transform(), require already allocated data reserved for the output. As the 
algorithms only use iterators as arguments, they cannot allocate data by themselves. 
To enlarge the container the algorithms operate on, they rely on the iterator being 
capable of enlarging the container it iterates.
If an iterator to an empty container is passed to the algorithms for output, the 
program will likely crash. */

/*   Instead, you have to do either of the following:
  • Preallocate the required size for the resulting container, or
  • Use an insert iterator, which inserts elements into a container while iterating, such as std::back_inserter  */


/* Algorithms use operator==() and operator<() 
by default
For comparison, an algorithm relies on the fundamental == and < operators, as in the 
case of an integer. To be able to use your own classes with algorithms, operator==() 
and operator<() must either be provided by the class or as an argument to the
algorithm   */

/*  All algorithms use std::swap() and std::move() when moving elements around, but 
only if the move constructor and move assignment are marked noexcept. Therefore, 
it is important to have these implemented for heavy objects when using algorithms. 
If they are not available and exception free, the elements will be copied instead. */

/*  The constrained algorithms under std::ranges introduced with C++20 offer some 
benefits over the iterator-based algorithms under std. The constrained algorithms do 
the following:
• Support projections, which simplifies custom comparisons of elements.
• Support ranges instead of iterator pairs. There is no need to pass begin() and 
end() iterators as separate arguments.
• Are easy to use correctly and provide descriptive error messages during 
compilation as a result of being constrained by C++ concepts  */


// While sort() sorts the entire range, partial_sort() and nth_element() could be thought of as algorithms for inspecting parts of that sorted range.  nth element sorts only that element
/* std::sort() O(n log n)
std::partial_sort() O(n log m)
std::nth_element() O(n)     */

// nth element is much faster for finding a median, for example

// ranges and views






int main()
{
	some_func("Hi");  // called with literal

	float buffer[256];
	span_func(buffer);  // okay! array passed as span with size

	std::cout << sizeof(smallObject) << " " << sizeof(bigObject) << std::endl;  // possible output is 8 and 260

	std::vector<int> vec{ 1,2,3,4,5 };

	print(vec);

	std::ranges::transform(in, out.begin(), lambda);  // applies function and stores result in out

	print(out);

	*it++;   // dereference the iterator and increase the value it points at
	it++;  // move the iterator on
	std::cout << *it << std::endl;

	std::cout << std::ranges::count(vec, 3);  // pass the range directly to the algorithm


}
