# include <iostream>
# include <atomic>
# include <cassert>
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
Foo* x = p.fetch_add(2, std::memory_order_release); // add 2 to p and return the old value
assert(x == some_arr);
assert(p.load() == &some_arr[2]);
x = (p -= 1);  // subtract 1 from p and return new value
assert(x == &some_arr[1]);
assert(p.load() == &some_arr[1]);

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
	while (!data_ready.load())
	{
		std::this_thread::sleep(std::chrono::milliseconds(100));
	}
	std::cout << "the answer is : " << data[0] << std::endl;
}

void writer_thread()
{
	data.push_back(42);
	data_ready = true;
}

// we know its undefined behaviour to have non-atomic reads and writes accessing the same data without enforcesd ordering, so for this to work, we need an enforced ordering somewhere
//







int main()
{

	std::cout << "Hi there!" << std::endl;
	std::atomic_size_t st{ 15 };  // atomic size t

	std::atomic<bool> b{ true };  // initialsed using non atomic bool
	b = false;  // assignment operator returns values, not references, for atomic types

	// writes of either true or false are done by calling store(), memory order semantics can still be specified
	// exchange() member function lets you replace the stored value with one of your choosing and atomically retrieve the original value
	// store is a store operation, load() is a load operation and exchange is a read-modify-write operation

	bool x = b.load(std::memory_order_acquire);
	b.store(true);
	x = b.exchange(false, std::memory_order_acq_rel);




}