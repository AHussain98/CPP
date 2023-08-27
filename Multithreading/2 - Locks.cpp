#include <iostream>
#include <mutex>
#include <list>
#include <thread>
#include <stack>

// if we share memory across multiple threads, we have to provide a valid locking mechanism
// invariants: statements that are always true for a particular data structure, e.g.
// for a list data structure, size variable contains the number of elements in the list
// in a doubly linked list data structure, if you follow a next pointer from node a to node b, the previous pointer in b should point to node a
// the most common problem of multithreaded applications is broken invariants while updating

// race condition: in concurrency, race condition is anything where the outcome is dependent on the relative ordering of execution of operations on two or more threads
// most of the time this ordering does not matter, but if this race condition results in broken data structures, then such race conditions are problematic
// we can address problematic race conditions via mutexes

// the mutex class is a synchronization primitive that can be used to protect shared data from being simultaneously accessed by multiple threads
// the mutex provides mutually exclusive access of shared data fro multiple threads


// note that a list is not a thread safe data structure, in fact most of the data structures in the STL are not
// pushing an element to a list is not a atomic operation, we have to create a new node, set that nodes next to the current head and change heads pointer to point to new node
// if two threads try to push an element to the list at once, one of the nodes could be lost, not thread safe

// to avoid this, lets instantiate an object of the mutex class
// mutex class objects have 3 fucntions, lock, unlock and try_lock

// after one thread acquires the lock and proceeds to computation, the other thread has to wait until the first thread releases the lock


// calling lock and unlock on a mutex manually is cumbersome
// therefore we can use the lock_guard class instead
// the lock_guard object acts as a mutex wrapper that provides a convenient RAII-style mechanism for owning a mutex for the duration of a scoped block
// when a lock_guard object is created, it attempts to take ownership of the mutex it is given
// when control leaves the scope in which the lock_guard object was created, the lock_guard is destructed and the mutex is released

// there are two main scenarios where using a mutex can go wrong
// one is returning a pointer or reference to the protected data
// the second is passing code to the protected data structure which you don't have control over

std::list<int> my_list;
std::mutex m;  // create a mutex object

void add_to_list(int const& x) {
	// m.lock(); // call the lock method of the mutex
	std::lock_guard<std::mutex> lg(m);  // lock guard used instead of manual lock and unlock
	my_list.push_front(x);
	// m.unlock();  // now unlock the mutex, remember to unlock otherwise another thread may never be able to acquire the lock and complete the fucntion call
}

void size() {

	m.lock();  // as we have used the same mutex in size() and add_to_list(), access to both of these functions is mutually exclusive
	// this means even though multiple threads will try to access this mutex, only one thread will succeed and acquire the lock
	int size = my_list.size();
	m.unlock();
	std::cout << "The size of the list is " << size << std::endl;
}

void run_code() {
	// lets launch two threads in here
	std::thread thread1(add_to_list, 4);  // both threads try to acquire the add_to_list function, but only one thread will be allowed to acquire the lock
	std::thread thread2(add_to_list, 11);  // waits until first thread releases the lock

	thread1.join();
	thread2.join();
}

// lets now have a go at implementing the trhead safe version of the stack data structure
// we need to avoid the race condition between pushing and popping in particular
// functions we need to implement are empty, size, top, push and pop

// when we wrap functionalities with synchronization mechanisms, we have achieved thread safety
// but this also limits true parallel access to the data structure, even though many threads try to access it, only one can actually do any operation at once

// we have a race condition that we inherit from the original stack object, where two threads can race between top() and pop() functions
// we can solve this by combining top and pop

template <typename T>
class thread_safe_stack {

private:
	std::stack<T> stk;  // member objects are a stack and a mutex
	std::mutex m1;

public:
	void push(T element) {
		std::lock_guard<std::mutex> lg(m);  // in each method, we have to construct the lock guard object with the same mutex
		stk.push(element);
	}

	void pop(){
		std::lock_guard<std::mutex> lg(m);
		stk.pop();
	}

	T& top(){
		std::lock_guard<std::mutex> lg(m);
		return stk.top();
	}

	bool empty() {

	}

	size_t size(){ // size_t is the type returned by the sizeOf function
	
	}

};


// deadlock -> two threads waiting for each other to finish, wait forever as neither thread is allowed to proceed

// unique_lock is a general purpose mutex ownership wrapper
// it can be used to manage mutexes like we did with lock_guard objects
// but unlike lock_guard objects, it does not have to acquire the lock for the associated mutex in the construction
// unique_locks are neither copy constructible or copy assignable but they are move constructable and move assignable


int main() {

	run_code();
}

