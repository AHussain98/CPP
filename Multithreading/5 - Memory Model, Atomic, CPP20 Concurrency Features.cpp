#include <iostream>
#include <coroutine>
#include <atomic>

// cpp20 introduced a new form of thread called jthread
// currently threads have to explicitly join or detach, otherwise when the threads destructor is called, std::terminate will be called
// we also cannot interrupt the execution of a thread after we launch it

// c++20 also introduces co-routines
// there are two type sof routines, subroutine and coroutine
// a subroutine is the name for just a normal function
// remember that the main function is put first on the run time stack in a stack frame with all its local variables, any functions called by the main function then get placed on top of it in their own stack frames with their own local variables
// when a function concludes, it is popped off the runtime stack and the function below it begins running
// there are two stages in subroutines, a caller invokes the functions and then when the fucntion completes, it finalizes (destructor calls)

// in a coroutine, there are 4 stages, invoke, suspend, resume and finalise
// a coroutine consists of a promise object which we return results via, a handle which we use to resume or destroy the coroutine from outside and the coroutine state, which is a heap allocated object containing the promise, arguments to coroutine and local variables
// we can use these to implement generators like in python

// a barrier is a synchronisation mechanism that makes threads wait until the required number of threads has reached a certain point in code. 
// Once all the threads reach the barrier, they're all unblocked and may proceed

// an atomic operation is an indivisible operation. We cannot observe such an operation half-done from any thread in the system
// the atomicity of these atomic types may be achieved by internal locks in some OS, but for all OS's, these types are guaranteed to behave in a lock free manner
// 
// atomic_flag is the most simple atmic type available, it represents a boolean value
// atomic_flag should be initialised with ATOMIC_FLAG_INIT, only has two function's clear() and test_and_set()

// atomic bool has more features than atomic flag does

// atomic types are neither copy constructable or copy assignable 
// we can assign non-atomic booleans to atomic booleans and construct atomic booleans using non atomic booleans
// 6 functions that can be used on any atomic type (apart from flag): is_lock_free, store, load, exchange, compare_exchange_weak, comapare_exchange_strong

// the compare functions compare the value of the atomic variable with a supplied expected value and stores the supplied desired value if they are equal.
// if they are not equal, the expected value is updated with the actual value of the atomic varibale.
// This will return true if store is performed, false otherwise

// cpp standard specifies 6 memory ordering options
// using these memory ordering options with atomic operations, we can create synchronization points the code
// we can specify memory order options in the parameters of methods of atomic types
// the compiler uses memory order sequential consistent as a default option

// memory_order_seq_cst is the easiest memory ordering option
// this implies that the behaviour of the program is consistent with a simple sequential view of the world
// so if you write any atomic operation without specifying a memory ordering option, you are using sequential consistent by default
// seq_cst means every thread gets the same global view of shared memory

// todays processors have multiple levels of caches
// a store buffer stores write instructions and sits between the l1 cache on the actual processor and the l2 cache
// because writing operations are faster than read operations, it's beneficial to store many write operations and execute them when teh store buffer is flushed
// instruction reordering can occur in firstly by teh compiler, then in the cache, then by the procesor directlu via prefetch speculation
// mutexes prevent implicit instruction reordering and provide thread safety
// memory_order_relaxed is the total opposite to seq_cst
// view of the threads is not consistent with each other and there is no restruction on instriction re-ordering
// memory order acquire and release are used to provide synchronisation, acquire waits for release


// atomic operations can be seperated into load/acquire operations, store/release operations and read,modify,write / acquire, release operations
// store: memory orders used here are relaxed, release or seq_cst
// load: memory orders used here are relaxed, comsume, aquire and seq_cst
// rmw: relaxed, consume, acquire, release, rel_acq, seq_cst

// lets implement a spin lock mutex
class spinlock_mutex {

private:

	std::atomic_flag flag = ATOMIC_FLAG_INIT;

public:

	spinlock_mutex(){}

	void lock() {
		while (flag.test_and_set(std::memory_order_acquire));  // one thread will wait in this while loop until it sees this flag as false
	}

	void unlock() {
		flag.clear(std::memory_order_release);
	}

};





int main() {
	std::atomic_flag flag1 = ATOMIC_FLAG_INIT; // initalise the flag
	std::cout << flag1.test_and_set() << std::endl; // changes the value of the flag and returns the previous value, so here its set to true but returns false

	std::atomic<bool> flag2;  // true by default
	bool val = false;
	std::atomic<bool> flag3 = val; // assign to the atomic version using the normal version

	flag3.store(flag2); // we can use store to store the atomic value of flag 2 in flag3
	std::cout << "The value of flag3 is: " << flag3.load() << std::endl;  // load function

	bool z = flag2.exchange(false);  // assign the value of flag 2 to z and assign flag 2 to false

	std::cout << "is flag3 inplemented lock free? " << flag3.is_lock_free() << std::endl; // check if this is implemented lock free

	// lets test out the weak compare function

	std::atomic<int> x = 25;
	int expected_value = 25;
	std::cout << "The expected value of x is: " << expected_value << std::endl;
	bool return_val = x.compare_exchange_weak(expected_value, 50);  // so for x, the expected value is 25 and the desired value is 50
	std::cout << "does x have the expected value? " << (return_val ? "true" : "false") << std::endl;  // return_val is true in this case
	std::cout << "therefore, the new value of x is: " << x << std::endl;  // compare_exchange returned true, so x's value is now the desired value

	// if x was not the same as the expected value, the expected value would have been updated to the atomic variable's current value, x is unchanged
	// comapare_exchange_weak cannot guarantee that the operation will happen successfully, compare_echange_string does

	// atomic<T*> is an atomic form of pointer
	// this does not mean that the object pointed to is atomic, but that the pointer itself is atomic
	// atomic pointers are not copy constructable or copy assignable, but can be constructed and assigned using non atomic values

	// other than the above functions common to all atomic types, there are a few specific operations only for atomic pointers
	// these are fetch_add, fetch_sub, ++, --

	int values[20]; // integer array called values of size 20
	for (int i = 0; i < 20; ++i) {
		values[i] = i;
	}

	std::atomic<int*> val_pointer = values; // atomic pointer points to values
	std::cout << *val_pointer << std::endl;  // first value is 0

	// fetch_add adds the given offset to the pointer and returns the previous pointer
	int* prev_pointer = val_pointer.fetch_add(12);  // val pointer is moved on by 12, prev pointer points to where val pointer used to point
	// fetch_sub determines the given negative offset from the atomic pointer and also returns the previous value

	// ++ and -- work the same as for normal pointers as they do for atomic pointers

    //  if we want to use an atomic user defined type, we must ensure:
	// the type has a trivial copy assignment operator
	// must not have virtual functions
	// every non static member should have trivial copy assignmnet operator
	// not be a descendent of a virtual base class
	// base class must use a compiler generated copy assignment operator
	// they type must be bitwise equality comparable



	std::cout << "Hello there!";
}






	std::cout << "Hello there!";
}
