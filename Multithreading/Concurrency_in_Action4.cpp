# include <iostream>
# include <atomic>
# include <assert.h>
# include <vector>
# include <thread>
# include <chrono>

// the memory model matters when we are trying to get close to the machine
// there are two aspects to the memory model, the structural aspects which relate to how things are laid out in memory and the concurrency aspects. Structural aspects are important for concurrency
// All data in a c++ program is made up of objects, an object is a region of storage and they have types and lifetimes
// whatever its type, an object is stored in one or more memory locations
/* Each memory location is either an object (or sub-object) of a scalar type such as unsigned short
or my_class* or a sequence of adjacent bit fields. If you use bit fields, this is an
important point to note: though adjacent bit fields are distinct objects, they’re still
counted as the same memory location.*/

// every variable is an object, including those that are members of other objects
// every object occupies at least one memory location
// variables of fundamental types such as int ot char occupy exactly one memory location, whatever their size, even if they're adjacent or part of an array
// adjacent bitfields are part of the same memory location, so the chars in a string are in the same memory location, in adjacent bitfields, same as the elements in an array

// in multithreaded applications, everything hinges on these memory locations
/* . If two threads access separate memory locations,
there’s no problem: everything works fine. On the other hand, if two threads access
the same memory location, then you have to be careful. If neither thread is updating
the memory location, you’re fine; read-only data doesn’t need protection or synchronization. If either thread is modifying the data, there’s a potential for a race condition,*/

// one way to ensure a defined ordering is to use mutexes, the other is to use synchronisation properties of atomic operations, either on the same or other memory locations to enforce an ordering between the accesses in the two threads
// if more than two threads access the same memory location, each pair of threads must have a defined ordering
// if there is no enforced ordering between two accesses to a single memory location from seperate threads, one or both of these accesses is not atomic, and if one or both is a write, we have a data race and this causes undefined behaviour

// modification orders: every object in a c++ program has a modification order composed of all the writes to that object from all threads in the program, starting with the objects initialisation
// in most cases this order will vary between runs, but in any given execution of the program, all threads must agree on the order
// if different threads see distinct sequences of values for a single variable, you have a data race and undefined behaviour. If you do use atomic operations, the compiler is responsible for ensuring that the necessary synchronisation is in place

// an atomic operation is an indivisible operation, you cannot observe such an operation half-done from any thread in the system, its either done or it's not done
// if the load operation that reads the value of an object is atomic, and all modifications to that object are also atomic, that load will retrieve either the inital value of the object or the value stored by one of teh modifications

// the standard atomic types are in the atomic header, all operations on such types are atomic, and only operations on these types are atomic in the sense of the language definition, although you can use mutexes to make other operations appear atomic
// the key use for atomic operations is as a replacement for an operation that would otherwise use a mutex for synchronisation
// however, sometimes atomics can use mutexes under the hood if their operations are not supported on certain platforms, you can use the is_lock_free() atomic member function to check this along with some macros. We want to check this because mutexes decreae performance so we want to know if tehy're being used internally

// types:
// std::atomic_flag, simple boolean flag, operations on this are lock free, this is always lock free and mutexes are not implemented under the hood for this type only
// the remaining std::atomic<> types are all accessed through specialisations of the atomic<> class template and have more features but may not be lock free
// atomic_size_t is teh atomic typedef for size_t

// standard atomic types ae not copyable or assignable in the conventional sense, they have no copy constructors or copy assignment operators
/* they do support assignment nd implicit conversion to the corresponding built - in types as well as direct load() and store() member functions, exchange(),
compare_exchange_weak(), and compare_exchange_strong(). They also support the
compound assignment operators where appropriate: +=, -=, *=, |=, and so on, and
the integral types and std::atomic<> specializations for ++ and -- pointers support.
These operators also have corresponding named member functions with the same
functionality: fetch_add(), fetch_or(), and so on. The return value from the assignment operators and member functions is either the value stored (in the case of the
assignment operators) or the value prior to the operation (in the case of the named
functions). This avoids the potential problems that could stem from the usual habit of
these assignment operators returning a reference to the object being assigned to. In
order to get the stored value from these references, the code would have to perform a
separate read, allowing another thread to modify the value between the assignment
and the read and opening the door for a race condition.  */

// the std::atomic<> class template has a primary template that can be used to create an atomic variant of a user-defined type
// because its a generic class, the operations are limited to load(), store() and assignment to and from the user defined type, exchange(), compar_exchange_weak() and compare_exchange_strong()
// each of the operations on the atomic types has an optional memory-ordering argument which is one of the values of the std::memory_order enumeration. This argument is used to specify the required memory ordering semantics
// permitted values for the memory ordering depend on the operation category. If you do not specify an ordering value, then the default is used, which is strongest, std::memory_order_seq_cst

// memory ordering operations are divided into three categories:
// store operations, which ccan have memory_order_relaxed, memory_order_release or memory_order_seq_cst ordering
// load operations, which can have memory_order_relaxed, memory_order_consume, memory_order_acquire, or memory_order_seq_cst ordering
// read-modify-write operations which can have memory_order_relaxed, memory_order_consume, memory_order_acquire, memory_order_release, memory_order_acq_rel, or memory_order_seq_cst ordering

// std::atomic_flag is the simplest standard atomic type, which represents a Boolean flag
// Objects of this type can be in one of two states, set or clear
// Objects of the std::atomic_flag type must be initialised with ATOMIC_FLAG_INIT, this initalises the flag to a clear state, the flag always starts clear

std::atomic_flag f{ ATOMIC_FLAG_INIT };

/* You can’t copy-construct another std::atomic_flag object from the first, and
you can’t assign one std::atomic_flag to another. This isn’t something peculiar to
std::atomic_flag but something common with all the atomic types. All operations on
an atomic type are defined as atomic, and assignment and copy-construction involve two
objects. A single operation on two distinct objects can’t be atomic. In the case of copyconstruction or copy-assignment, the value must first be read from one object and then
written to the other. These are two separate operations on two separate objects, and the
combination can’t be atomic. Therefore, these operations aren’t permitted.*/

// the most basic of the atomic integral types is std::atomic<bool>
// its still not copy constructible or copy assignable, and can be constructed from a non-atomic bool, so it can be initially true or false, and you can also assign to instances of std::atomic<bool> from a non-atomic bool

std::atomic<bool> b{ true };  // initialsed using non atomic bool
//b = false;  // assignment operator returns values, not references, for atomic types

// writes of either true or false are done by calling store(), memory order semantics can still be specified
// exchange() member function lets you replace the stored value with one of your choosing and atomically retrieve the original value
// store is a store operation, load() is a load operation and exchange is a read-modify-write operation

// the compare-exchange operation has strong and weak variants
// this operation compares the value of the atomic variable with a supplied expected value and stores the supplied desired value if they're equal
// if the variables are not equal, the expected value is updated with the value of the atomic variable
// the return type of the compare exchange functions is a bool, true if the store was performaned

// comapre_exchange_weak(), the store may fail even if the original value is equal to the expected value, in which case the function returns false
// it may fail when the processor cannot guarantee the operation is done atomically, such as when the performning thread was switched out by the OS, this is a spurious failure
// compare_exchange_strong() is guaranteed to return false ONLY if the value wasn't equal to the expected value
// we can supply memory ordering params for both success and failure to the compare-exchange functions

/* One further difference between std::atomic<bool> and std::atomic_flag is
that std::atomic<bool> may not be lock-free; the implementation may have to
acquire a mutex internally in order to ensure the atomicity of the operations. For the
rare case when this matters, you can use the is_lock_free() member function to
check whether operations on std::atomic<bool> are lock-free. This is another feature common to all atomic types other than std::atomic_flag*/

// atomic pointer is std::atomic<T*>
// behaves same as the bool but also has pointer aruthmeic operations
// fetch_add and fetch_sub member functions do atomic addition and subtraction on the stored address
/* The operators work as you’d expect
from the built-in types: if x is std::atomic<Foo*> to the first entry of an array of Foo
objects, then x+=3 changes it to point to the fourth entry and returns a plain Foo* that
also points to that fourth entry. fetch_add() and fetch_sub() are slightly different in
that they return the original value (so x.fetch_add(3) will update x to point to the
fourth value but return a pointer to the first value in the array). This operation is also
known as exchange-and-add, and it’s an atomic read-modify-write operation, like
exchange() and compare_exchange_weak()/compare_exchange_strong(). As with
the other operations, the return value is a plain T* value rather than a reference to the
std::atomic<T*> object, so that the calling code can perform actions based on what
the previous value*/


class Foo{};
Foo some_arr[5];  // array of 5 Foos
std::atomic<Foo*> p(some_arr); // p points to some_arr
//Foo* x = p.fetch_add(2, std::memory_order_release); // add 2 to p and return the old value
//assert(x == some_arr);
//assert(p.load() == &some_arr[2]);
//x = (p -= 1);  // subtract 1 from p and return new value
//assert(x == &some_arr[1]);
//assert(p.load() == &some_arr[1]);

// fetch_add and fetch_sub are read-modify-write operations so they can have any memory order param
// specifying memory order semantics is not possible for the operator forms, so they have seq_cst

// we can create atomic variants of user defiend types
// given a UDT, this is done by std::atomic<UDT>
// in order to use std::atomic<UDT> for some user defined type UDT, this type must have a trivial copy-assignment operator
// so the UDT must not have any virtual functions or virtua base classes and must use the compiler generated copy assignment operator
// also, every base class and non-static data member of a UDT must also have a trivial copy assignment operator
// this allows the compiler to use memcpy() for assignment operations
/* Finally, it is worth noting that the compare-exchange operations do bitwise comparison as if using memcmp, rather than using any comparison operator that may be
defined for UDT. If the type provides comparison operations that have different semantics, or the type has padding bits that do not participate in normal comparisons, then
this can lead to a compare-exchange operation failing, even though the values compare equally*/

// the standard atomic types do more than avoid the undefined behaviour associated with a data race, they allow the user to enforce an ordering of operations between threads
// this enforced ordering is the basis of the facilities for protecting data and synchronising operations such as std::mutex and std::future<>

// suppose you have two threads, one of which is populating a data structure to be read by the second
// in order to avoid a problematic race condition, the first thread sets a flag to indicate the data is ready, and the seocnd thread doesn't read the data until the flag is set

std::vector<int> data;
std::atomic<bool> data_ready{ false };

void reader_thread() 
{
	while (!data_ready.load())  // read of the flag happens before the read of the data
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::cout << "the answer is : " << data[0] << std::endl;  // non-atomic read
}

void writer_thread()
{
	data.push_back(42);  // non-atomic write
	data_ready = true;  // write to data happens before write to the atomic bool
}

// we know its undefined behaviour to have non-atomic reads and writes accessing the same data without enforcesd ordering, so for this to work, we need an enforced ordering somewhere
// the enforced ordering comes from the operations on the atomic bool variable, 
// when the value read from data_ready is true, the write synchronises with that read, creating a happens before relationship
// therefore the write of the data happens before the read of the data and everything is ok
// with the default atomic operations, the operation that writes a value happens before an operation that reads teh value, which is what's spelled out above


// the synchronises with relationship is something we can only get between operations on atomic types
// operations on a data structure, such as locking a mutex, might provide this relationship if the data structure contains atomic types and the operations on that data structure perform the appropriate atomic operations internally, but fundamentally, it comes only from operations on atomic types

// if thread A stores a value and thread B reads that value, there's a synchronises with relationship between the store in thread A and the read in thread B
// the c++ memory model allows various ordering constraints to be applied to the operations on atomic types

// happens before and strongly happens before relationships are the basic building blocks of operation ordering in a program
// it specifes which operations see the effects of other operations
// operations in a single statement are unsequenced, and therefore there is no happens before relationship between them
// you can decalre and initialise static variables in a function, they are initialised and created when execution first reaches them and are destroyed at end of teh program

/*
There are circumstances where operations within a single statement are sequenced,
such as where the built-in comma operator is used or where the result of one expression is used as an argument to another expression. But in general, operations within a
single statement are nonsequenced, and there’s no sequenced-before (and thus no
happens-before) relationship between them. All operations in a statement happen
before all of the operations in the next statement.
*/

// interaction between threads: if operation A in one thread inter-thread happens before operation B on another thread, then A happens before B
// inter-thread happens before is relatively simple and relies on the synchronizes with relationship, if operation A in one thread synchronizes with operation B in another thread, then A inter-thread happens before B

// there are 6 memory ordering options that can be applied to operations on atomic types: relaxed, consume, acquire, release, acq_rel, seq_cst
// unlesss specified otherwise, all operations on atomic are sequential consistent by default

/* The C++11 memory ordering parameters for atomic operations specify constraints on the ordering. If you do a store with std::memory_order_release, and a load from another thread reads the value with std::memory_order_acquire then subsequent read operations from the second thread will see any values stored to any memory location by the first thread that were prior to the store-release, or a later store to any of those memory locations.

If both the store and subsequent load are std::memory_order_seq_cst then the relationship between these two threads is the same. You need more threads to see the difference.

e.g. std::atomic<int> variables x and y, both initially 0.

Thread 1:

x.store(1,std::memory_order_release);
Thread 2:

y.store(1,std::memory_order_release);
Thread 3:

int a=x.load(std::memory_order_acquire); // x before y
int b=y.load(std::memory_order_acquire); 
Thread 4:

int c=y.load(std::memory_order_acquire); // y before x
int d=x.load(std::memory_order_acquire);
As written, there is no relationship between the stores to x and y, so it is quite possible to see a==1, b==0 in thread 3, and c==1 and d==0 in thread 4.

If all the memory orderings are changed to std::memory_order_seq_cst then this enforces an ordering between the stores to x and y. Consequently, if thread 3 sees a==1 and b==0 then that means the store to x must be before the store to y, so if thread 4 sees c==1, meaning the store to y has completed, then the store to x must also have completed, so we must have d==1.

In practice, then using std::memory_order_seq_cst everywhere will add additional overhead to either loads or stores or both, depending on your compiler and processor architecture.*/


// sequential consistent imples the behaviour of the program is consistent with a sequential view of the world
// if all operations on instances of atomic types are sequentially consistent, the behaviour of the program is such that the operations were performed in some particular sequencce by a single thread
// all threads must see the same order of operations, operations can't be reordered, if the code has one operation before another in one thread, that ordering must be seen by all other threads
// this constraint doesnt carry forward for relaxed memory ordering, so sequentially consistent must be used everywhere to get teh benefit
// from the point of view of synchronisation, a sequentially consistent store synchronises with a sequentially consistent load of the same variable that reads the value stored
// this provides one ordering constraint on the operation of two or more threads, and any sequentially consistent atomic operations done after that load must also appear after the store to other threads in the system using sequentially consistent atomic operations


std::atomic<bool> x, y;
std::atomic<int> z;

void write_x()
{
	x.store(true, std::memory_order_seq_cst);
}

void write_y()
{
	y.store(true, std::memory_order_seq_cst);
}

void read_x_then_y()  // if the load of y in here returns false, the store to x must occur before the store to y
{
	while (!x.load(std::memory_order_seq_cst));  // wait until x is true
	
	if (y.load(std::memory_order_seq_cst))
	{
			++z;
	}
	
}

void read_y_then_x()
{
	while (!y.load(std::memory_order_seq_cst));  // wait until y is true
	if (x.load(std::memory_order_seq_cst))  // if therefore the store of x occurs before the store of y, the load of x in here must be true
		++z;
}

// because the semantics of sequentially consistent ordering require a single total ordering over all operations tagged dequentially consistent, there is an miplied ordering relationship between a load of y that returns flase and the store to y
// for there to be a single total order, if one thread sees x == true and then subsequently sees y == false, this imples the store to x occurs before the store to y in the total order
// everything is symettrical so it could happen the otehr way around, with x being fale and y returning true, in both cases z is 1
// both loads could also return trye in which case z is 2
// but under no circumstances can z be zero

/*Architects and programming language designers believe the rules we just explored to be intuitive to programmers. The idea is that multiple threads running in parallel are manipulating a single main memory, and so everything must happen in order. There’s no notion that two events can occur “at the same time”, because they are all accessing a single main memory.

Note that this rule says nothing about what order the events happen in—just that they happen in some order. The other part of this intuitive model is that events happen in program order: the events in a single thread happen in the order in which they were written. This is what programmers expect: all sorts of bad things would start happening if my programs were allowed to launch their missiles before checking that the key was turned.

Together, these two rules—a single main memory, and program order—define sequential consistency.*/


// on a multiprocessor system, squential consistency may require extensive nd time consuming communicatio between processors

// with non-sequentially consistent memory orderings, there is no longer a single global order of events
// this means different threads can see different views of the same operations, threads do not have to agree on the order of events

// operations on atomic types performed with relaxed ordering don't participate in synchronises-with relationships
// operations on the same variable within a single thread still obey the happens-before relationship, but theres almost no requirement on ordering relative to other threads
/*The only requirement is that accesses to a single atomic
variable from the same thread can’t be reordered; once a given thread has seen a particular value of an atomic variable, a subsequent read by that thread can’t retrieve
an earlier value of the variable. Without any additional synchronization, the modification order of each variable is the only thing shared between threads that are using
memory_order_relaxed.*/

std::atomic<bool> x1, y1;
std::atomic<int> z1;

void write_x1_then_y1()
{
	x1.store(true, std::memory_order_relaxed);
	y1.store(true, std::memory_order_relaxed);
}

void read_x1_then_y1()
{
	while (!y1.load(std::memory_order_relaxed));  // wait for y1 to become true
	
	if (x1.load(std::memory_order_relaxed))
		{
			z1++;
		}
	
}

// relaxed operations on different variables can be freely reordered provided they obey any happens-before relationships they're bound by (e.g. within the same trhead)
// they dont introduce synchronises with relationships
// stores and loads happen in different threads, so there's a hapens before relationship in each individual thread
// however there is no relatioship between threads, so reading a value in one thread that was changed by another can fail the assert
// for example, the thread doing loads may see the stores out of order


// acquire-release ordering is a step up from relaxed ordering, there's still no total order of operations, but it does introduce some synchronisation
// under this ordering model, atomic loads are acquire operations (memory_order_acquire), atomic stores are release operations (memory_order_release) and atomic read-modify-write operations (such as fetch_add() or exchange()) are either acquire, release, or both (memory_order_acq_rel)
// synchronisation is pairwise between the thread that does the release and the thread that does the acquire
// a release operation synchronises with an acquire operation that reads the value written, this means that different threads can still see different orderings, but these are restricted

std::atomic<bool> x2, y2;
std::atomic<int> z2;

void write_x2()
{
	x2.store(true, std::memory_order_release);
}

void write_y2()
{
	y2.store(true, std::memory_order_release);
}

void read_x2_then_y2()
{
	while (!x2.load(std::memory_order_acquire));  // wait until x2 is true
	if (y2.load(std::memory_order_acquire))
	{
		++z2;
	}
}

void read_y2_then_x2()
{
	while (!y2.load(std::memory_order_acquire)); // wait until y2 is true
	if (x2.load(std::memory_order_acquire))
	{
		++z2;
	}
}


// the thread modifying x and the thread modifying y can have totally different views of the world, this is because there's no happens-before relationship to force an ordering


// in order to see the benefit of acquire-release ordering, we need to consider two stores from the same thread
// if you change teh store to y to use memory-order-release and the load from y to use memory order acquire, we impose an ondering on the operations on x

std::atomic<bool> x3, y3;
std::atomic<int> z3;
void write_x3_then_y3()
{
	x3.store(true, std::memory_order_relaxed);
	y3.store(true, std::memory_order_release);
}
void read_y3_then_x3()
{
	while (!y3.load(std::memory_order_acquire)); // spin, waiting for y to be set to true, eventually this load will see true, as written by the store above
	if (x3.load(std::memory_order_relaxed))
	{
		++z;
	}
}

// because the store uses memory_order_release and the load uses memory_order_acquire, the store synchronises with the load
// the store to x3 happens before the store to y3, because they're in the same thread
// because the store to y synchronises with the load from y, the store to x also happens before the load from y and by extension happens before the load from x
// thus the load from x must read true and the assert cannot fire
/*If the load from y wasn’t in a while loop, this wouldn’t necessarily be the case; the
load from y might read false, in which case there’d be no requirement on the value
read from x. In order to provide any synchronization, acquire and release operations
must be paired up. The value stored by a release operation must be seen by an acquire
operation for either to have any effect. If either the store or the load was a
relaxed operation, there’d be no ordering on the accesses to x, so there’d be no guarantee that the load would read true, and the assert could fire.*/

// acquire release ordering can be used to synchronse data across several threads, even when intermediate threads haven't touched the data

// to think about transitive ordering, we need three threads.
// first thread modifies some shared variables and does a store-release to one of them
// a second thread then reads the variable subject to the store-release with a load-acquire and performs a store-release on a second shared variable
// Finally, a third thread does a load-acquire on that second shared variable
/*  Provided that the load-acquire operations see the values written by the store-release operations to ensure the synchronizeswith relationships, this third thread can read the values of the other variables stored
by the first thread, even if the intermediate thread didn’t touch any of them. This scenario is shown in the next listing.*/

std::atomic<int> data[5];
std::atomic<bool> sync1{ false }, sync2{ false };

void thread_1()
{
	data[0].store(42, std::memory_order_relaxed);
	data[1].store(97, std::memory_order_relaxed);
	data[2].store(17, std::memory_order_relaxed);
	data[3].store(-141, std::memory_order_relaxed);
	data[4].store(2003, std::memory_order_relaxed);
	sync1.store(true, std::memory_order_release);  // set sync 1, stores to data from thread 1 happen before the store to sync, because theyre sequenced before it in the same thread
}

void thread_2()
{
	while (!sync1.load(std::memory_order_acquire));  // loop until sync1 is set
	sync2.store(true, std::memory_order_release);  // set sync2
}

// because the load of sync1 is in a while loop, it will eventually see the value stored from thread 1 and form teh second half of the release acquire pair
// therefore the store to sync1 happens before the final load from sync1 in the while loop
// this load is sequenced before and therefore happens before the store to sync 2, which forms a release acquire pair with the final load from the while loop in thread 3


void thread_3()
{
	while (!sync2.load(std::memory_order_acquire));  // loop until sync2 is set
	assert(data[0].load(std::memory_order_relaxed) == 42);
	assert(data[1].load(std::memory_order_relaxed) == 97);
	assert(data[2].load(std::memory_order_relaxed) == 17);
	assert(data[3].load(std::memory_order_relaxed) == -141);
	assert(data[4].load(std::memory_order_relaxed) == 2003);
}

// even though thread2 only touches the variables sync1 and sync2, this is enough for synchronisation between thread 1 and 3 to ensure the asserts do not go off

/*
In this case, you could combine sync1 and sync2 into a single variable by using a
read-modify-write operation with memory_order_acq_rel in thread_2. One option
would be to use compare_exchange_strong() to ensure that the value is updated only
once the store from thread_1 has been seen:
std::atomic<int> sync(0);
void thread_1()
{
 // ...
 sync.store(1,std::memory_order_release);
}
void thread_2()
{
 int expected=1;
 while(!sync.compare_exchange_strong(expected,2,
 std::memory_order_acq_rel))
 expected=1;
}
void thread_3()
{
 while(sync.load(std::memory_order_acquire)<2);
 // ...
 
 */

// you can get a synchronises with relationship between a store to an atomic variable and a load of that atomic variable from another thread, even when theer's a sequence of read-modify-write operations betweeen the store and load, provided all operations are suitably tagged
/* If the store is tagged
with memory_order_release, memory_order_acq_rel, or memory_order_seq_cst, and
the load is tagged with memory_order_consume, memory_order_acquire, or memory
_order_seq_cst, and each operation in the chain loads the value written by the previous operation, then the chain of operations constitutes a release sequence and the initial store synchronizes with (for memory_order_acquire or memory_order_seq_cst)
or is dependency-ordered-before (for memory_order_consume) the final load. Any
atomic read-modify-write operations in the chain can have any memory ordering
(even memory_order_relaxed).*/


// consider atomic int being used as a count of the number of items in a shared queue:
std::vector<int> queue_data;
std::atomic<int> count;

void populate_queue()
{
	unsigned const number_of_items = 20;
	queue_data.clear();
	for (unsigned i = 0; i < number_of_items; ++i)
	{
		queue_data.push_back(i);
	}

	count.store(number_of_items, std::memory_order_release);   // initial store
}

void consume_queue_items()
{
	while (true)
	{
		int item_index;
		if ((item_index = count.fetch_sub(1, std::memory_order_acquire)) <= 0)   // read-modify-write operation
		{
			wait_for_more_items();  // wait for more items
			continue;
		}
		process(queue_data[item_index - 1]);  // reading queue data is safe
	}
}

/*int main()
{
 std::thread a(populate_queue);
 std::thread b(consume_queue_items);
 std::thread c(consume_queue_items);
 a.join();
 b.join();
 c.join();
}

one way to handle things would be to have the thread that's producing the data store the items in a shared buffer and then store in count to let other threads know that data is available
the threads consuming the queue items can do fetch_sub to claim an item from the queue
once count becomes zero, there are no more items and the thread must wait
 If there’s one consumer thread, this is fine; fetch_sub() is a read with memory
_order_acquire semantics, and the store had memory_order_release semantics, so
the store synchronizes with the load and the thread can read the item from the buffer.
If there are two threads reading, the second fetch_sub() will see the value written by
the first and not the value written by the store. Without the rule about the release
sequence, this second thread wouldn’t have a happens-before relationship with the
first thread, and it wouldn’t be safe to read the shared buffer unless the first fetch_
sub() also had memory_order_release semantics, which would introduce unnecessary
synchronization between the two consumer threads. Without the release sequence
rule or memory_order_release on the fetch_sub operations, there would be nothing
to require that the stores to the queue_data were visible to the second consumer, and
you would have a data race. Thankfully, the first fetch_sub() does participate in the
release sequence, and so the store() synchronizes with the second fetch_sub().
There’s still no synchronizes-with relationship between the two consumer threads.
There can be any number of links in the chain, but provided they’re all readmodify-write operations such as fetch_sub(), the store() will still synchronize with
each one that’s tagged memory_order_acquire. In this example, all the links are the
same, and all are acquire operations, but they could be a mix of different operations
with different memory-ordering semantics.
 Although most of the synchronization relationships come from the memoryordering semantics applied to operations on atomic variables, it’s also possible to
introduce additional ordering constraints by using fences
*/


// fences
// fences are operations that enforce memry-ordering constraints without modifying any data and are typically combined with atomic operations that use the memory_order_relaxed ordering constraints
// fences are global operations that affect the ordering of other atomic operations in the thread that executed the fence
// fences are also called memory barriers, they get their names because they put a line in the code that certain operations cannot cross
// relaxed operations on seperate variables can usually be freely reordered by the compiler or hardware, fences restrct this and introduce happens-before and synchronises with relationships 

// adding a fence between two atomic operations on each thread:
std::atomic<bool> x4, y4;
std::atomic<int> z4;
void write_x4_then_y4()
{
	x4.store(true, std::memory_order_relaxed);
	std::atomic_thread_fence(std::memory_order_release);  // release fence here synchronises with the acquire fence becuase the load from y reads the value stored at y4 in here
	y4.store(true, std::memory_order_relaxed);            // this means the store to x happens before the load from x, so the value read must be true and the assert cannot fire
}                                                         // this is in contrats to the original case without teh fences where teh store and load form x werent ordered so the assert could fire
                                                          // note that both fences are necessary, you need a release in one thread and an acquire in another thread to get a synchronise with relationship
void read_y4_then_x4()
{
	while (!y4.load(std::memory_order_relaxed));
	std::atomic_thread_fence(std::memory_order_acquire);
	if (x4.load(std::memory_order_relaxed))
	{
		z4++;
	}
}

/* int main()
{
 x=false;
 y=false;
 z=0;
 std::thread a(write_x_then_y);
 std::thread b(read_y_then_x);
 a.join();
 b.join();
 assert(z.load()!=0); 
}*/

/*  In this case, the release fence has the same effect as if the store to y was
tagged with memory_order_release rather than memory_order_relaxed. Likewise, the
acquire fence makes it as if the load from y was tagged with memory_order_
acquire. This is the general idea with fences: if an acquire operation sees the result of
a store that takes place after a release fence, the fence synchronizes with that acquire
operation; and if a load that takes place before an acquire fence sees the result of a
release operation, the release operation synchronizes with the acquire fence. You can
have fences on both sides, as in the example here, in which case if a load that takes
place before the acquire fence sees a value written by a store that takes place after the
release fence, the release fence synchronizes with the acquire fence*/

// important note, the synchronisation point is the fence itself
/* Although the fence synchronization depends on the values read or written by
operations before or after the fence, it’s important to note that the synchronization
point is the fence itself. If you take write_x_then_y from listing 5.12 and move the
write to x after the fence as follows, the condition in the assert is no longer guaranteed
to be true, even though the write to x comes before the write to y:

void write_x_then_y()
{
 std::atomic_thread_fence(std::memory_order_release);
 x.store(true,std::memory_order_relaxed); 
 y.store(true,std::memory_order_relaxed); 
}
These two operations are no longer separated by the fence and so are no longer
ordered. It’s only when the fence comes between the store to x and the store to y that
it imposes an ordering. The presence or absence of a fence doesn’t affect any
enforced orderings on happens-before relationships that exist because of other
atomic operations.
*/


// ordering non-atomic operations with atomics


int main()
{

	std::cout << "Hi there!" << std::endl;
	std::atomic_size_t st{ 15 };  // atomic size t

	//std::atomic<bool> b{ true };  // initialsed using non atomic bool
	//b = false;  // assignment operator returns values, not references, for atomic types

	// writes of either true or false are done by calling store(), memory order semantics can still be specified
	// exchange() member function lets you replace the stored value with one of your choosing and atomically retrieve the original value
	// store is a store operation, load() is a load operation and exchange is a read-modify-write operation

	//bool x = b.load(std::memory_order_acquire);
	//b.store(true);
	//x = b.exchange(false, std::memory_order_acq_rel);

	y = false;
	x = false;
	z = 0;
	std::thread a(write_x);
	std::thread b(write_y);
	std::thread c(read_x_then_y);
	std::thread d(read_y_then_x);
	a.join();
	b.join();
	c.join();
	d.join();
	assert(z.load() != 0);  // this assert can never fire because wither the store to x or y must happen first, even though its not specified which
	// load here is sequentially consistent by default
	std::cout << z << std::endl;

	x1 = false;
	y1 = false;
	z1 = 0;
	std::thread a1(write_x1_then_y1);
	std::thread a2(read_x1_then_y1);
	a1.join();
	a2.join();
	assert(z1.load() != 0);  // this time, assert can fire because load of x can read dalse, even though the load of y above reads true and the store of x happens before the store of y
	// x and y are different variables, so there are no ordering guarantees relating to the visibility of values arising from operations on each


	x2 = false;
	y2 = false;
	z2 = 0;
	std::thread a3(write_x2);
	std::thread b2(write_y2);
	std::thread c2(read_x2_then_y2);
	std::thread d2(read_y2_then_x2);
	a3.join();
	b2.join();
	c2.join();
	d2.join();
	assert(z2.load() != 0);  // this assert can fire because its possible for both the load of x2 and y2 to read false
	// this is because x2 and y2 are written by different threads so the ordering from the release to the acquire in each case has no effect on the operations in the other threads

	x3 = false;
	y3 = false;
	z3 = 0;
	std::thread a4(write_x3_then_y3);
	std::thread b3(read_y3_then_x3);
	a4.join();
	b3.join();
	assert(z3.load() != 0);
}