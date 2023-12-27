#include <iostream>
#include <string>
#include <vector>

// 90/10 rule, the notion that only about 10 % of a program’s code is performance - critical.It is thus neither necessary nor helpful to change every line of a program in order to improve the program’s performance.Since only 10 % of the program has a significant impact on performance, your chances of picking a good starting point at random are poor.
// The most important thing when optimising for performance is the algorithm itself. It is foolish to struggle heroically to optimize a bad algorithm. Learning and using optimal algorithms for searchingand sorting is a broad path to optimal code.

/*
to improve code performance:
• Use better compilers, and turn on the optimizer.
• Use optimal algorithms.
• Use better libraries, and use libraries better.
• Reduce memory allocation.
• Reduce copying.
• Remove computation.
• Use optimal data structures.
• Increase concurrency.
• Optimize memory management.


Certain memory addresses may be device registers instead of ordinary memory.
The values at these addresses may change during the interval between two con‐
secutive reads of the location by the same thread, indicating some change in the
hardware. Such locations are described to C++ as volatile. Declaring a variable
volatile requires the compiler to fetch a new copy of the variable every time it is
used, rather than optimizing the program by saving the value in a register and
reusing it. Pointers to volatile memory may also be declared.

• C++11 offers a magical spell called std::atomic<> that causes memory to behave
for just a moment as if it really was a simple linear store of bytes, wishing away all
the complexities of modern microprocessors, with their multiple threads of exe‐
cution, multilayer memory caches, and so on. Some developers think this is what
volatile is for. They are mistaken

In C++ terms, the implication is that a block of code containing a loop may execute
faster because instructions making up the loop are heavily used and close together,
and thus likely to stay in cache. A block of code containing function calls or if state‐
ments that causes execution to hop around may execute more slowly because individ‐
ual parts of the code are less heavily used, and not close together. Such a code block
uses up more cache space than a tight loop. If the program is large and the cache is
finite, some of the code must be discarded from the cache to make room for other
things, slowing access the next time that code is needed. Similarly, a data structure
consisting of consecutive locations, like an array or vector, may be faster to access
than a data structure consisting of nodes linked by pointers, because data in consecu‐
tive locations remains in a small number of cache locations. Accessing a data struc‐
ture consisting of records connected by pointers (e.g., a list or tree) may be slower
because of the need to read data for each node from main memory into new cache
lines.

 Computers that read
the most significant bits at the first byte address are called big-endian. Little-endian
computers read the least significant bits first. There are two ways to store an integer
(or pointer), and no reason to choose one over the other, so different teams working
on different processors for different companies may choose differently.
The problem comes when data written on disk or sent over a network by one com‐
puter must be read by a different computer. Disks and networks send a byte at a time,
not a whole int at a time. So it matters which end is stored or sent first.

memory access dominates the cost of computation
computation is faster than decision, branching statements slow down execution because they can't be predicted and computed ahead of time

What does it mean to switch contexts? If the operating system is switching from one
thread to another thread in the same program, it means saving the processor’s regis‐
ters for the thread being suspended, and loading the saved registers for the thread
being resumed. The registers of a modern processor contain hundreds of bytes of
data. When the new thread resumes execution, its data may not be in cache, so there
is an initial period of slow execution while the new context is loaded into cache.
There is thus a considerable cost to switching thread contexts.
When the operating system switches context from one program to another, the pro‐
cedure is even more expensive.

system calls are expensive;
hundreds of times more expensive than function calls within a single thread of one
program

some statements hide large amounts of computation. The form of the statement does
not tell how expensive it is. Keep this in mind with constructors especially

approach the optimiza‐
tion task systematically:
• They make testable predictions, and write their predictions down.
• They keep a record of code changes.
• They make measurements with the best instruments available.
• They keep detailed notes of experimental results

• Performance must be measured.
• Make testable predictions, and write the predictions down.
• Make a record of code changes.
• If each experiment run is documented, it can quickly be repeated.
• A program spends 90% of its run time in 10% of its code.
• A measurement must be both true and precise to be accurate.
• Resolution is not accuracy.
• On Windows, the function clock() provides a reliable 1-millisecond clock tick. For
Windows 8 and later, the function GetSystemTimePreciseAsFileTime() provides
a submicrosecond tick.
• Accepting only large changes in performance frees the developer from worrying
about methodology.
• To estimate how expensive a C++ statement is, count the number of memory reads
and writes performed by the statement.
*/


// Strings have some behaviors that make them expensive to use, no matter the imple‐
// mentation.They are dynamically allocated, they behave as values in expressions, and
// their implementation requires a lot of copying

/*  std::string implementations do a trick to amortize the cost of reallocating storage
for the character buffer as the string grows. Instead of making a request to the mem‐
ory manager for the exact number of characters needed, the string implementation
rounds up the request to some larger number of characters. For instance, some
implementations round up the request to the next power of 2. The string then has the
capacity to grow to twice its current size before needing to call the into the memory
manager again. The next time an operation needs to extend the length of the string,
there is room in the existing buffer, avoiding the need to allocate a new buffer. The
benefit of this trick is that the cost of appending characters to a string approaches a
constant asymptotically as the string grows longer. The cost of this trick is that strings
carry around some unused space. If the string implements a policy of rounding up
requests to a power of 2, up to half the storage in a string may be unused.


// strings behave as values

Because strings are values, the results of string expressions are also values. If you con‐
catenate strings, as in the statement s1 = s2 + s3 + s4;, the result of s2 + s3 is a
newly allocated temporary string value. The result of concatenating s4 to this tempo‐
rary string is another temporary string value. This value replaces the previous value of
s1. Then the dynamically allocated storage for the first temporary string and the pre‐
vious value of s1 are freed. This adds up to a lot of calls into the memory manager

Because strings behave as values, modifying one string must not change any other
strings. But strings also have mutating operations that change the contents of a string.
Because of these mutating operations, each string variable must behave as if it has a
private copy of its string. The simplest way to implement this behavior is to copy the
string when it is constructed, assigned, or passed as an argument to a function. If
strings are implemented this way, then assignment and argument passing are expen‐
sive, but mutating functions and non-const references are cheap.
There is a well-known programming idiom for things that behave as values but are
expensive to copy. It is called “copy on write,” and often abbreviated COW in C++
literature (see “Implement the “Copy on Write” Idiom” on page 136). In a COW
string, the dynamically allocated storage can be shared between strings. A reference
count lets each string know if it is using shared storage. When one string is assigned
to another, only a pointer is copied, and the reference count is incremented. Any
operation that changes a string’s value first checks to see that there is only one pointer
to that storage. If multiple strings point to the storage, any mutating operation (any
operation that may change the contents of the string) allocates new storage and
makes a copy of the string before making its change:

COWstring s1, s2;
s1 = "hot"; // s1 is "hot"
s2 = s1; // s2 is "hot" (s1 and s2 point to the same storage)
s1[0] = 'n'; // s1 makes a new copy of its storage before
 // changing anything
 // s2 is still "hot", s1 is "not"
Copy-on-write is such a well-known idiom that developers may easily assume
std::string is implemented that way. But copy-on-write isn’t even permitted for
C++11-conforming implementations, and is problematic in any case.

As noted previously, the string concatenation operator is expensive. It calls into the
memory manager to construct a new temporary string object to hold the concatenated string.

below is the function we will be optimising
*/

std::string remove_ctrl(std::string s) {
	std::string result;
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] >= 0x20) {
			result = result + s[i]; 
		}
	}
	return result;
}
// this function processes each char in string s in a loop, the code in the loop is the hot spot
// the assignment to result is expensive because string concatenation is expensive
// a call to the memory manager is amde each loop iteration to generate the temporary string, and then all characters are copied each time

// first optimisation, remove allocation and copy operations
//std::string remove_ctrl_mutating(std::string s) {
//	std::string result;
//	for (int i = 0; i < s.length(); ++i) {
//		if (s[i] >= 0x20)
//			result += s[i];
//	}
//	return result;
//}
// this eliminates all the calls to allocate temporary string objects to hold the concatenation expression result, and the associated copying and deleting of temporaries
// result = result + s[i] creates extra allocations and copy operations, rmeove this and replace with result += s[i]
// this is because we have eliminated all the calls to allocate temporary string objects to hold the concatenation result and the associated copying and deleting of temporaries

// we can also reduce reallocation by reserving storage
// we are currently lengthening result, so result is periodically copied into a larger internal dynamic buffer
// use the reserve function to prevent reallocation of the string buffer nd improve cache locality of the data accessed by the function

// since we're not modifying the string s, we dont need to copy it in by value, we can simply sue a const reference to it, another optimisation
// since allocation is expensive, it can be worth eliminating even one allocation
// however, remember that reference variables are implemented as pointers, so everywhere s appears in the function, the program dereferences a pointer it didnt have to before, this extra work can cause reduced perfromance
// the solution is to use iterators over the string. These are simple pointers inot the char buffer, this saves two dereference operations per loop
// also s.end() is cached on loop initialisation, this improves performance further
// you could also prevent returning a string by value, instead modifying the function to accept another string which it operates on and returning void instead, as another optimisation
// also using char arrays instead of strings would further boost performance

std::string remove_control_reserve(const std::string& s) {  // s passed in by const reference
	std::string result;
	result.reserve(s.length()); // reserve the size of s within result
	for (auto it = s.begin(), end = s.end(); it != end; ++it) {  // use iterators over the string
		if (*it >= 0x20) {
			result += *it;  // add the dereferenced iterator
		}
	}
}

// Example 4-7. remove_ctrl_cstrings(): coding on the bare metal
//void remove_ctrl_cstrings(char* destp, char const* srcp, size_t size) {
//	for (size_t i = 0; i < size; ++i) {
//		if (srcp[i] >= 0x20)
//			*destp++ = srcp[i];
//	}
//	*destp = 0;
//}

// further improvements include improving the algorithm
// now we reduce the number of allocations so instead of copying one character to the string we copy whole substrings, this reduces the number fo allocate and copy operations
// also cache the length of s to reduce the reeuce the cost of loop termination
std::string remove_ctrl_block_append(std::string s) {
	std::string result;
	result.reserve(s.length());
	for (size_t b = 0, i = b, e = s.length(); b < s.length(); b = i + 1) {
		for (i = b; i < e; ++i) {
			if (s[i] < 0x20) break;
		}
		result.append(s, b, i - b);
	}
		return result;	
}

// finally, using a strings erase function is a further performance improvement
// Example 4 - 10. remove_ctrl_erase() : mutating the string argument instead of building a result string
//std::string remove_ctrl_erase(std::string s) {
//	for (size_t i = 0; i < s.length(); )
//		if (s[i] < 0x20)
//			s.erase(i, 1);
//		else ++i;
//	return s;
//}
// the advantage of this algorithm is that since s gets shorter, there is never any reallocation, except for the returned value

// to improve further, use the boost string library, or use std::stringstream to avoid value semantics

/*
If you know that the input data is sorted or nearly sorted, the normally unacceptable
insertion sort has excellent O(n) performance on such data.
A relatively new hybrid sort called Timsort also has excellent O(n) performance if the
data is sorted or nearly sorted, and optimal O(n log 2 n) performance the rest of the
time. Timsort is now the standard sort in Python.
A recent sort called introsort is a hybrid of quicksort and heapsort. Introsort starts
doing a quicksort, but switches to a heapsort if unfortunate input data causes quick‐
sort’s recursion depth to become too great. Introsort guarantees a reasonable O(n log2
n) worst-case time, while taking advantage of quicksort’s efficient implementation to
modestly reduce average-case run time. Since C++11, introsort has been the prefer‐
red implementation of std::sort().
Another recently proposed sort called flashsort has excellent O(n) performance for
data drawn from a particular probability distribution. Flashsort is related to radix
sorting; data is sorted into buckets based on percentile in the probability distribution.
A simple case of flashsort occurs when the data items are uniformly distributed.

• Beware of strangers selling constant-time algorithms. They may be O(n).
• Multiple ecient algorithms can be combined in ways that make their overall run
time O(n2
) or worse.
• Binary search, at O(log2 n), isn’t the fastest search. Interpolation search is
O(log log n) and hashing is constant-time.
• For small tables with < 4 entries, all search algorithms examine about the same
number of entries

little optimisation tricks:
In if-then-else code with several else-if arms, if the tests are laid out in random
order, each time execution passes through the if-then-else block, about half the
tests will be computed. If there is one case that happens 95% of the time, and that test
is performed first, then 95% of the time only one test will be performed.
double checking:  Comparing two std::string instances for equality normally requires comparing
them character-by-character. However, a preliminary comparison of the lengths
of the two strings can quickly rule out equality.
 std::string is dynamically resizable to hold variable-length character strings. It
provides many operations to manipulate strings. If it’s only necessary to compare
fixed strings, a C-style array or pointer to literal string and a comparison func‐
tion may have better performance.
 A template function call with particular arguments is evaluated at compile time.
The compiler generates efficient code when the arguments are constants

*/

// we also need to optimise dynamically allocated variables
// the naive use of dynamically allocated varibales is the biggest performance killer in C++ programs
// the more calls into the memory manager you can remove, the better
// class instances should be created statically unless there is a reason to make them dynamic
// std::array is indistinguishable from c style arrays, this can be very useful if your vector isnt changing size
// maybe make a large c style array on the stack instead of a vector that youre constantly adding to, to avoid expensive allocations
// binary tree in an array can be more efficient than creating a linked binary tree, especially to easily computer child and parent nodes and left balances trees
// use circular buffer instead of dequeue, boost has circular buffer, useful because you don't need to reallocate
// 
// use make_shared instead of new, this avoids an extra call into the memory manager for the new object and teh shared pointer seperately:
// std::shared_ptr<MyClass> p = std::make_shared<MyClass>("hello", 123);
// 
// creating and useing shared pointers can be expensive however, as changing reference counts is anotehr memory manager call each time
// as data is appended to dynamic variables such as strings and vectors, its dynamically allocated internal storage eventually becomes full, the next append causes the string or vector to allocate a larger block of storage and copy the contents over to it
// the call to the memory manager and the copy operation perform many memory accesses and take up a lot of instructions
// both string and vector have a reserve function that should be leveraged to prevent this

std::vector<int> myVec;
myVec.reserve(100);  // reserve 100 elements in the vector, only one allocation


// remember alos to create dynamic variables outside of loops, so we're not constantky recreating the each time, which is expensive

// look out for unneeded copying (especially constructors) in these:
//• Initialization(calls constructor)
//• Assignment(calls assignment operator)
//• Function arguments(each argument expression is move - or copy - constructed
//	into its formal argument)
//	• Function return (calls move or copy constructor, perhaps twice)
//	• Inserting items into a standard library container(items are move - or copyconstructed)
//	• Inserting items into a vector(all items are move - or copy - constructed if the vec‐		tor is reallocated)

// you can declare the copy and assignment constructors private in the class definition to prevent copying, or else use the delete keyword when defining them
// we can still assign or initialuse variables with pointers or references to the class instance, which is much more efficient than copying

// pass by const reference rather than copying where necessary

// returning a value can cause it to be copy constructed into the calling expression
// to avoid this (if RVO is not enacted by teh compiler) you can simply return void, pass the parameter by reference and modify the function to it sumply operates on the parameter object and doesnt return anything

// apply move semantic to classes where appropriate, with a moce constructor and move assignment operator
// move semantics should be implemented for all the bases and derived classes aswell, otherwise these will be copied and not moved

// prefer flat data structures rather than node based ones

// cache loop control statements wherever possible, as they will be enacted every time the loop executes

// Example 7 - 2. for loop with cached end value
for (size_t i = 0, len = strlen(s); i < len; ++i)  // len is cached, do this!
	if (s[i] == ' ')
		s[i] = '*';
// also remove any invariants in the loop, so any constants that can be computed outside of teh loop should be

// also remove any hidden function calls from loops where possible:
//• Declaration of a class instance (calls constructor)
//• Initialization of a class instance(calls constructor)
//• Assignment to a class instance(calls assignment operator)
//• Arithmetic expressions involving class instances(calls operator member functions)
//	• Scope exit(calls destructor of class instances declared in the scope)
//	• Function arguments(each argument expression is copy - constructed into its formal argument)
//	• Function return of a class instance(calls copy constructor, perhaps twice)
//	• Inserting items into a standard library container(items are move - or copyconstructed)
//	• Inserting items into a vector(all items are move - or copy - constructed if the vector is reallocated)

// The destructor of any class that will have derived classes should be declared virtual.
// This is necessary so that if a delete - expression references a pointer to the base class, both the derived class destructorand the base class destructor will be called.

// floating point arithmetic is expensive, prefer integers
// group constants together in an expression, the compiler will automatically calulate them and speed up computation

// always prefer switch instead of if, else if ...
/* In a frequently occurring case, when the constants to be tested against are taken from
a set of sequential or nearly sequential values, the switch statement compiles into a
jump table indexed by the test value or an expression derived from the test value. The
switch statement performs a single indexing operation and jumps to the address in
the table. The cost of the comparison is O(1), no matter how many cases appear. The
cases don’t have to be presented in sequential order; the compiler can sort the jump
table.
When the constants form a sequence with large gaps, a jump table becomes unma‐
nageably large. The compiler may still sort the tested constants and emit code that
performs a binary search. For a switch statement comparing against n values, the
worst-case cost of this search is O(log2 n). In any case, the compiler never emits code
for a switch statement that is slower than an equivalent if-then statement.*/

/*Memory fences
Most std::atomic member functions take an optional memory_order argument that
selects a memory fence around the operation. If the memory_order argument is not
provided, the default is memory_order_acq_rel. This provides a full fence that is
always safe, but can be expensive. More refined fences can be selected, but this should
be done only by knowledgeable users.
Memory fences synchronize main memory with the cache of multiple hardware
threads. In general, a memory fence is executed on each of two threads to synchron‐
ize one thread with the other. C++ allows the following memory fences:
memory_order_acquire
memory_order_acquire may be casually thought to mean “acquire all work done
by other threads.” It ensures that subsequent loads are not moved before the cur‐
rent load or any previous loads. It does this, paradoxically, by waiting for store
operations currently in flight between the processor and main memory to com‐
plete. Without the fence, if a store is in flight when this thread does a load to the
same address, the thread gets old information, as if the load had moved up inside
the program.
memory_order_acquire may be less expensive than the default full fence. It
would be appropriate, for instance, to use memory_order_acquire when atomi‐
cally reading the flag in the while loop of a busy-wait.
memory_order_release
memory_order_release may casually be thought to mean “release all work done
by this thread to this point.” It ensures that previous loads and stores done by this
thread are not moved past the current store. It does this by waiting for store
operations currently in flight within this thread to complete.
302 | Chapter 12: Optimize Concurrency
memory_order_release may be less expensive than the default full fence. It
would be appropriate, for instance, when setting the flag at the end of a homebuilt mutex.
memory_order_acq_rel
This combines the two previous guarantees, creating a full fence.
memory_order_consume
memory_order_consume is a potentially weaker (and faster) form of
memory_order_acquire that requires only that the current load take place before
other operations that are data-dependent on it. For instance, when a load of a
pointer is marked memory_order_consume, subsequent operations that derefer‐
ence this pointer won’t be moved before it.
memory_order_relaxed
With this value, all reorderings are OK

• A multithreaded C++ program is sequentially consistent if it contains no races.
• A large and vocal design community thinks explicit synchronization and shared
variables are a bad idea.
• Performing I/O in a critical section does not lead to optimal performance.
• The number of runnable threads should be less than or equal to the number of pro‐
cessor cores.
• The ideal number of threads contending for a brief critical section is two.
*/

int main() {



}