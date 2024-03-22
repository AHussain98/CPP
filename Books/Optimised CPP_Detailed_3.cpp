# include <iostream>
# include <vector>
# include <algorithm>
# include <array>
# include <string>
# include <unordered_set>
# include <span>
# include <ranges>
# include <memory>

/* data structure called bit arrays. It turns 
out that std::vector<bool> is not at all a standard vector of C++ bool objects. 
Instead, internally, it's a bit array. Operations such as count() and find() can be 
optimized very efficiently in a bit array since it can process 64 bits at a time (on 
a 64-bit machine), or possibly even more by using SIMD registers.*/


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
//std::next(it); // or it++
//std::prev(it);  // it it--

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

// memory management

// cpu spends a lot of time shuffling data between cpu registers and main memory, cpu uses memory caches to speed up access to memory, and programs need to be cache-friendly to run quickly
// physical memory of the computer is shared between all the processes running on a system
// most operating systems today are virtual memory operating systems, which provide the illusion that a process has all the memory for itself
// each process has its own virtual address space
// addresses in the virtual address space that programmers see are mapped to physical addresses by the operating system and the memory management unit. This translation happens each time we access a memory address
// this makes it possible for the OS to use physical memory for the parts of a process that are currently being used and back the rest of the virtual memory up on disk. The physical memory acts as a cache for the virtual memory space, which resides on secondary storage
// The areas of the secondary storage that are used for backing up memory pages are usually called swap space, swap file, or simply pagefile, depending on the operating system
// virtual memory makes it possible for processes to have a virtual address space bigger than the physical address space, since virtual memory that is not in use does not have to occupy physical memory

/* The most common way to implement virtual memory today is to divide the address 
space into fixed-size blocks called memory pages. When a process accesses memory 
at a virtual address, the operating system checks whether the memory page is 
backed by physical memory (a page frame). If the memory page is not mapped in the 
main memory, a hardware exception occurs, and the page is loaded from disk into 
memory. This type of hardware exception is called a page fault. This is not an error 
but a necessary interrupt in order to load data from disk to memory. As you may 
have guessed, though, this is very slow compared to reading data that is already 
resident in memory

When there are no more available page frames in the main physical memory, a page frame
has to be evicted. If the page to be evicted is dirty, that is, it has been modified since
it was last loaded from disk, it needs to be written to disk before it can be replaced.
This mechanism is called paging. If the memory page has not been modified, the
memory page is simply evicted.

Not all operating systems that support virtual memory support paging. iOS, for
example, does have virtual memory but dirty pages are never stored on disk; only
clean pages can be evicted from memory. If the main memory is full, iOS will start
terminating processes until there is enough free memory again. Android uses a
similar strategy. One reason for not writing memory pages back to the flash storage
of the mobile devices is that it drains the battery, and it also shortens the lifespan of
the flash storage itself

Thrashing can happen when a system runs low on physical memory and is,
therefore, constantly paging. Whenever a process gets time scheduled on the CPU,
it tries to access memory that has been paged out. Loading new memory pages
means that the other pages first have to be stored on disk. Moving data back and
forth between disk and memory is usually very slow; in some cases, this more or
less stalls the computer since the system spends all its time paging. Looking at the
system's page fault frequency is a good way to determine whether the program has
started thrashing.

C++ uses stack to implement function calls and manage the automatic storage of local variables
both stack and heap reside in the processes virtual memory space
The stack is
a place where all the local variables reside; this also includes arguments to functions.
The stack grows each time a function is called and contracts when a function returns.
Each thread has its own stack and, hence, stack memory can be considered threadsafe. The heap, on the other hand, is a global memory area that is shared among all
the threads in a running process. The heap grows when we allocate memory with
new (or the C library functions malloc() and calloc()) and contracts when we free
the memory with delete (or free()). Usually, the heap starts at a low address and
grows in an upward direction, whereas the stack starts at a high address and grows
in a downward direction.

stack is a contigous memory block
it has a fixed maximum size, the program crashes, this is called stack overflow
stack memory never becomes fragmented
allocating memory from the stack is almost always fast. page faults are possible but rare
each thread in a program has its own stack

total memory allocated for the stack is a fixed size contigous memory block created at thread startup
stack grows each time the program enters a function and contracts when the function returns
the stack also grows whenever we create a new stack variable within the same fucntion and contracts whenever such a variable goes out of scope

The most common reason for the stack to overflow is by deep recursive
calls and/or by using large, automatic variables on the stack. The maximum size
of the stack differs among platforms and can also be configured for individual
processes and threads.

the heap is where the data with dynamic storage lives. the heap is shared among multiple threads, which means memory management for the heap needs to take concurrency into account
this makes memory allocation in the heap more complicated than stack allocations, which are local per thread

The allocation and deallocation pattern for stack memory is sequential, in the sense
that memory is always deallocated in the reverse order to that in which it was
allocated. On the other hand, for dynamic memory, the allocations and deallocations
can happen arbitrarily. The dynamic lifetime of objects and the variable sizes of
memory allocations increase the risk of fragmented memory.


An easy way to understand the issue with memory fragmentation is to go through
an example of how fragmented memory can occur. Suppose that we have a small
contiguous memory block of 16 KB that we are allocating memory from. We are
allocating objects of two types: type A, which is 1 KB, and type B, which is 2 KB. We
first allocate an object of type A, followed by an object of type B. 
Next, all objects of type A are no longer needed, so they can be deallocated. 
There is now 10 KB of memory in use and 6 KB is available. Now, suppose we want
to allocate a new object of type B, which is 2 KB. Although there is 6 KB of free
memory, there is nowhere we can find a 2 KB memory block because the memory
has become fragmented.


all objects we use in a c++ program reside in memory

the new keyword allocates memory to hold a new object of the type, and then constructs a new object in the allocated memory space by calling the constructor of the class
the delete keyword destructs the user object by calling the destructor and dealloctes the memory that was used by the object

C++ allows us to separate memory allocation from object construction. We could, for
example, allocate a byte array with malloc() and construct a new User object in that
region of memory. Have a look at the following code snippet:
auto* memory = std::malloc(sizeof(User));
auto* user = ::new (memory) User("john");
The perhaps unfamiliar syntax that's using ::new (memory) is called placement new.
It is a non-allocating form of new, which only constructs an object. The double colon
(::) in front of new ensures that the resolution occurs from the global namespace to
avoid picking up an overloaded version of operator new.
In the preceding example, placement new constructs the User object and places
it at the specified memory location. Since we are allocating the memory with
std::malloc() for a single object, it is guaranteed to be correctly aligned (unless
the class User has been declared to be overaligned). Later on, we will explore cases
where we have to take alignment into account when using placement new.
There is no placement delete, so in order to destruct the object and free the memory,
we need to call the destructor explicitly and then free the memory:
user->~User();
std::free(memory);



*/

//memory alignment
/*
the cpu reads memory into its registers one word at a time.this is 64 bits or 32 bits depending on architecture
for the cpu to work efficiently with different data types, it has restrictions on the addresses where objects of different types are located
every type in C++ has an alignment requirement that defines the addresses that a object of a certain type should be located in memory

if the alignment of a type is 1, it means objects of that type can be located at any byte address
if the alignment of a type is 2, it means that the number of bytes between successive allowed addresses is 2
"An alignment is an implementation-defined integer value representing the number of bytes between successive addresses at which a given object can be allocated."
objects placed at aligned memory addresses can be read into registers by the cpu in an efficient way


we can check if an object is correctly aligned using std::align

It is possible to specify custom alignment requirements that are stricter than the
default alignment when declaring a variable using the alignas specifier. Let's say we
have a cache line size of 64 bytes and that we, for some reason, want to ensure that
two variables are placed on separate cache lines. We could do the following:
alignas(64) int x{};
alignas(64) int y{};
// x and y will be placed on different cache lines
It's also possible to specify a custom alignment when defining a type. The following
is a struct that will occupy exactly one cache line when being used:
struct alignas(64) CacheLine {
 std::byte data[64];
};

 if we want to write fully portable C++ code, we need to use std::align()
and not modulo to check the alignment of an object. std::align() is a function from
<memory> that will adjust a pointer according to an alignment that we pass as an
argument. If the memory address we pass to it is already aligned, the pointer will
not be adjusted. Therefore, we can use std::align() to implement a small utility
function called is_aligned(), as follows:

bool is_aligned(void* ptr, std::size_t alignment) {
 assert(ptr != nullptr);
 assert(std::has_single_bit(alignment)); // Power of 2
 auto s = std::numeric_limits<std::size_t>::max();
 auto aligned_ptr = ptr;
 std::align(alignment, 1, aligned_ptr, s);
 return ptr == aligned_ptr;
}
At first, we make sure that the ptr argument isn't null and that alignment is a power
of 2, which is stated as a requirement in the C++ standard. We are using C++20
std::has_single_bit() from the <bit> header to check this. Next, we are calling
std::align(). The typical use case for std::align() is when we have a memory
buffer of some size in which we want to store an object with some alignment
requirement. In this case, we don't have a buffer, and we don't care about the size of
the objects, so we say that the object is of size 1 and the buffer is the maximum value
of a std::size_t. Then, we can compare the original ptr and the adjusted aligned_
ptr to see if the original pointer was already aligned. We will have use for this utility
in the examples to come.
When allocating memory with new or std::malloc(), the memory we get back
should be correctly aligned for the type we specify. The following code shows that
the memory allocated for int is at least 4 bytes aligned on my platform:

auto* p = new int{};
assert(is_aligned(p, 4ul)); // True

In fact, new and malloc() are guaranteed to always return memory suitably aligned
for any scalar type (if it manages to return memory at all).

As follows is an example in which we allocate a block of heap memory that should
occupy exactly one memory page. In this case, the alignment-aware versions of
operator new() and operator delete() will be invoked when using new and delete:

constexpr auto ps = std::size_t{4096}; // Page size
struct alignas(ps) Page {
 std::byte data_[ps];
};
auto* page = new Page{}; // Memory page
assert(is_aligned(page, ps)); // True
// Use page ...
delete page;


the compiler sometimes needs to add extra bytes, padding to our user defined types. when we define data members in a class or struct,the compiler is forced to place the members in the ame order as we define them
however, the compiler also has to ensure that the data members inside the class have the correct alignment, hence it needs to add padding between data members if necessary

*/


class Document {
	bool is_cached{};
	double rank{};
	int id{};
};

// size of Document can be 24, this may be because the compiler adds padding for the bool and int, to fulfill the alignment requirements of the individual data members and the entire class

/* The compiler converts the Document class into something 
like this:
class Document {
 bool is_cached_{};
 std::byte padding1[7]; // Invisible padding inserted by compiler
 double rank_{};
 int id_{};
 std::byte padding2[4]; // Invisible padding inserted by compiler
};

The first padding between bool and double is 7 bytes, since the rank_ data member
of the double type has an alignment of 8 bytes. The second padding that is added
after int is 4 bytes. This is needed in order to fulfill the alignment requirements of
the Document class itself. The member with the largest alignment requirement also
determines the alignment requirement for the entire data structure. In our example,
this means that the total size of the Document class must be a multiple of 8, since it
contains a double value that is 8-byte aligned.
*/

// lets create a new version fo document that minimises the padding inserted by the compiler:
/*
class Document {
 double rank_{}; // Rearranged data members
 int id_{};
 bool is_cached_{};
};
*/
// size of document is now 16 bytes, padding is only after is_cached
// size of an object can change just by changing the order in which its members are declared

/* As a general rule, you can place the biggest data members at the beginning and the 
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
the ownership of resources. This is the topic of the following section.      */

// Memory Ownership

// smart pointers help us specify the ownership of dynamic variables
// other types of variables have defined ownership, local variables are owned by the current scope, when that scope ends, the objects within that scope are destroyed
// static and global variables are owned by the program and will be destroyed when the program terminates
// Data members are owned by the instances of the class they belong to
// only dynamically allocated variables do not have a default owner


auto func()
{
	std::vector<int> v {1, 2, 3, 4, 5};
}

// here we use stack and dynamic memory
// vector is an automatic object that lives on the stack, owned by the stack scope
// vector object uses dynamic memory to store the integer elements
// when v goes out of scope, the destructor cleans up the dynamic memory


// RAII -> resource acquisition is initialisation
// lifetime of a resource is controlled by the lifetime of an object, this could be memory, database or network connection etc...
// object to handle network connection:

/*

class RAIIConnection {
public:
 explicit RAIIConnection(const std::string& url) : connection_{open_connection(url)} {}
 ~RAIIConnection() {
      try {
      close(connection_);
       }
       catch (const std::exception&) {
        // Handle error, but never throw from a destructor
       }
    }
 auto& get() { return connection_; }

 private:
 Connection connection_;
};

connection object now wrapped in a class that controls its lifetime. RAII makes our code safer

containers are also a method of controlling elements

smart pointers, weak, shared, unique

unique: only I own this object, delete it when im done
shared: i and others use this object, delete it when were done
weak: ill use the object if it exists, but dont keep it alove just for me

*/

// unique pointer can only be owned by one entity, they can be moved but not copied
auto owner { std::make_unique<std::string> ("Asad") };
auto new_owner{ std::move(owner) }; // move ownership to this new unique pointer

// unique pointers are efficient since they add very little perfprmance overhead
/* The slight overhead is incurred by the 
fact that std::unique_ptr has a non-trivial destructor, which means that (unlike a 
raw pointer) it cannot be passed in a CPU register when being passed to a function. 
This makes them slower than raw pointers */


// shared pointer
