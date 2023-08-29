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







	std::cout << "Hello there!";
}