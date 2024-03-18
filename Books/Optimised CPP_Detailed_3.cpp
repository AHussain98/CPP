# include <iostream>
# include <vector>
# include <algorithm>
# include <array>

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








int main()
{

}