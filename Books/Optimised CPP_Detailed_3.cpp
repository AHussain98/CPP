# include <iostream>
# include <vector>
# include <algorithm>
# include <array>
# include <string>
# include <unordered_set>

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
std::erase(vec, 5); // erase 5 from vec

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
auto persons = std::unordered_set<person, decltype(person_hash), decltype(person_eq)>{ 100, person_hash, person_eq };  // 100 buckets
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















int main()
{

}
