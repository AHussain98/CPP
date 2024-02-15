# include <iostream>

// latency is the time between a task starting to when the task is finished
// hft firms have applications and processes that are latency critical and fail completely if performance latency is higher than a specific threshold

// Time to first byte is measured as the time elapsed from when the sender sends the first byte
// of a request or response to the moment the reciever recieves the last byte

// Round trip time is the sum of time it takes for a packet to travel from one process to nanother
// and then the time it takes for the response packet to reach the original process

// tick to trade is defined as the time from when a market data packet hits a participants trading server to when the server is done 
//processing the packet, calculates trading signals and puts an order request on the wire (writes to a network socket)

// cpu clock cycles are the smallest increments of work that can be done by the CPU processor
// measuring these and working out how many instructions are executes and kernel level optimisations are the higherst level of optimisation possible

// throughput is how much work gets done in a period of time and latency is how quickly a single task is completed

// ping is the latency between how fast a server and client communicate with each other

// network bandwith measures how many megabits per second can be uploaded or downloaed from the server
// contention is a measure of how many simultaenous users are trying to access the server and whether that causes the server to overload or not

// network packet loss reduces the effective bandwith and causes retransmission and recovery protocols which introduce additional delays
// jitter is like packet losses except packets arrive out of order

// two common network protocols to transfer data across the internet: TCP and UDP
// TCP provides reliable transpot by tracking packets successfully delivered to the reciever and having mechanisms to retransmit lost packets, though this can cause additional latencies, used during online shopping or banking
// UDP instead focuses on making sure the data is delivered as quickly as possible and with greater bandwith effectiveness but does not guarantee delivery or in order delivery of packets and has no retransmitting feature
// rendering systems for online games commonly use UDP

// improving performance
// manage memory, optimise cache access and optimise hot path
// avoid memory leaks, pre-allocate and pre-initialise as many things as possible, avoid garbage collection and dynamic memory allocation and deallocation on the critical path
// focus on using the data and instruction cache, optimise the critical loop
// cache calculations

// a market making algorithm has orders in the market that other participants can trade against when needed
// a market making algo therefore needs to be constantly re-evaluating its active orders and changing the prices and quantities for them depending on market conditions
// a liquidity taking algo waits for an opportunity to present itself and then trades against a market making algo's active order in the book.

// low latency trading applications have high CPU usage, low kernel usage (system calls), low memory consumption and high network resource usage
// as we increase the number of threads, we must think about currency and thread safety, and if we need to use locks for synchronization and concurrency between threads, that adds additional latencies and context switches
// Context switches are not free because the scheduler and OS must save the state of the thread or process being switched out and load the state of the thread or process that will run next
// for optimal performance, we try to get the CPU scheduler to do little to no work (processes and threads are never context switched out) by pinning specific processes to cores

// Dynamic memory allocations and deallocations are handled by the OS looking for blocks of free memory and then deleting them
// searching for this memory can incur higher latencies as the memory becomes more and more fragmented
// avoid this on the critical path

// dynamic linking incurs a large extra runtime cost the first time the shared library code is called, and the compiler and linker are unable to optimise the shared library code since it's external
// static linking avoids this but results in extra large binaries

// first code for correctness, not speed. Once the application works correctly, only then should focus be shifted to optimising the critical parts of the application while maintaining correctness
// optimising code can take significantly longer than coding for correctness so get it correct first

// array is better than hashmap for searching for few elements due to cache performance

// always think about whats in the cache

// when designing data structures, think about reducing the amount of work done, think about cache and memory accesses
// the memory hierarchy works in such a way that if the CPU cannot find the data or instruction it needs next in the register (smallest yet fastest storage), it goes to the L0 cache, and then L1,L2, other caches and eventually to the main memory
// storage is accessed fastest to slowest with a reducing amount of space

// maximise the concept of temporal locality and spatial locality
// this means data accessed recently is likely to be in cache and data next to what we just accesses is also likely to be in cache
// think carefully about cache and memory access patterns for the algo and application as a whole

// for low latency applications, dynamic polymorphism, dynamic memory allocations and exception handling should be kept to a minimum due to large overheads

// local variables created within a function are stored on the stack by default and stack memory is also used to store function return values
// assuming no large objects are creted, the same range of stack storage space is reused a lot, resulting in great cache performance due to locality of reference

// the compiler tries to put local variables that are used the most into the register, these are accessed the fastest and are closest to the processor

// static variables are ineffient wrt cache performance sunce that memory cannot be reused for other variables and accessing static variables and global variables is another memory access

// volatile prevents optimisation

// dynamically allocated memory is inefficient to allocate and deallocate and depending on its use can result in poor cache performance

// SSO -> small string optimisation, uses local storage for small strings if they are smaller than 32 chars, don't dynamically allocate this

// use registers and local variables as much as possible to optimise cache performance, use the stack!
// avoid static, global and dynamic memory on the critical path

// integer operations are super fast as long as the int fits in the register
// unsigned slightly faster than signed generally, multiplication is longer, division is longest

// converting from floating point to integer is expensive, and vice versa
// // converting from bigger to smaller costs nothing
// converting from small to bigger has a little cost
// converting pointers from one type to another is free

// remember that two pointers to different types cannot point to the same memory location

// static_cast, const_cast, reinterpret_cast do not incur any overhead
// dynamic cast checks whether a conversion is valid using run time type information which is slow and possibly throws an error if conversion is invalid

// double calcs take same as ints

// mixing single and double precision calcs should be avoided since this causes implicit type conversion which adds clock cycles

// order boolean probabilities to short circuit whenever possible
// booleans are stored at 1 byte

// constructors and destructors for defined classes should be kept as light and efficient as possible since they can be called without the developer expecting it
// keeping these methods small also allows the compiler to inline them to improve performance
// same applies to copy and move constructors

// smart pointers add very little overhead generally unless there are a lot of them

// in modern processor pipelines, instructions are fetched and decoded in stages
// the processor tried to predict which branch will be taken and fetches instructions from that branch ahead of time
// branch misprediction wastes man clock cycles every time it happens
// long chains of if-else must be avoided, keep these simple and easy to predict
// for and while loops can be predicted well if the loop count is small
// switch statements should have cases that increment by 1 ascendingly, this may cause an implementation as an efficient jump table

// cpp20 [[likely]] attribute

// functions cause overhead, only create them if logical and if there's enough re-useability to justify it

// class member and non class member functions get assigned memory addresses in the order they are created
// group together performance critical finctions that call each other frequently or operate on the same data, this facilitates better code and data cache performance

// calling a function through a pointer has larger overhead than calling the function directly, this also prevents prediction and prefetching

// pass primitives by value, pass composite types by const reference

// returning primitives is very efficient
// returning composite types is much less efficient
// the optimal way to return a composite type is to have the caller create an object of that type and then pass a reference to it in the fucntion

// avoid recursive functions, replace them with loops

// curiously recurring template pattern facilitates compile time polymorphism
// this is more efficient than using virtual functions, though is more complex
template <typename actual_type>
class CRTP_Example {
public:
	void placeOrder() { static_cast<actual_type*>(this)->actualPlaceOrder(); }
	void actualPlaceOrder() { std::cout << "CRTP_Example::actualPlaceOrder() \n"; }
};

class SpecificCRTP_Example : public CRTP_Example<SpecificCRTP_Example>
{
public:
	void actualPlaceOrder() { std::cout << "SpecificCRTP_Example::actualPlaceOrder() \n"; }
};
/* A dynamic_cast is used when you want to make sure at run-time that the derived class you are casting into is the correct one. 
But here we don’t need this guarantee: 
the Base class is designed to be inherited from by its template parameter, and by nothing else. 
Therefore it takes this as an assumption, and a static_cast is enough.
The purpose of doing this is using the derived class in the base class. 
From the perspective of the base object, the derived object is itself, but downcasted. 
Therefore the base class can access the derived class by static_casting itself into the derived class.*/

// Template metaprogramming means writing code that generates more code
// This helps move computation from runtime to compile time


// including exceptions causes overhead even when they're not thrown
// with nested functions, exceptions need to be propagated all the way up the call chain, and the call stack needs to be cleaned up
// this is known as stack unwinding and requires the exception handler to track all the information it needs to walk backwards during an exception

// noexcept is an optimisation, but remember that the exception can then not be propagated along the call stack, the program terminates then and there

// when trying to optimise cache and memory access:
// variables that are aligned, in that they are placed at memory locations that are multiples of the sie of the variable, are accessed most efficientlu

// align data in multiples of 8/16/32/64 in a struct or class to minimise padding and improve the number of bits that can be read up in a single read operation by the processor (this is word count)

// cache friendly data access is when data is accessed sequentially, in order and eady to predict, such as iterating through a vector from the end
// for example, accessing memory through an array is significantly more efficient than accessing elements in a linked list, tree or hash map due to the contigous memory storage versus random memory storage
// if elements are small enough, searching through an array is faster than a hash map due to cache performance and algorithm overhead

// dynamically allocated memory is very slow, repeated allocation and deallocation of memory blocks of varied sizes fragments the heap
// fragmented heap makes the allocation and deallocation process even slower

// improve prediction by avoiding branches, unrolling loops and inlining
enum class Side : int16_t {BUY = 1, SELL = -1};


int main()
{
	CRTP_Example<SpecificCRTP_Example> crtp_example;
	crtp_example.placeOrder();  // calls the derived version

	// calculate last quantity without branches
    Side fill_side = Side::BUY;
	int fill_qty = 10;
	int last_qty[3] = { 0,0,0 }, position = 0;
	auto sideToInt = [](Side side) noexcept {return static_cast<int16_t>(side); };
	const auto int_fill_side = sideToInt(fill_side);
	position += int_fill_side * fill_qty;
	last_qty[int_fill_side + 1] = fill_qty;
	std::cout << "last quantity: " << last_qty[int_fill_side + 1];
}