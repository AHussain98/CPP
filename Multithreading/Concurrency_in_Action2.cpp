# include <iostream>
# include <thread>
# include <vector>
# include <string>
# include <mutex>
# include <list>
# include <algorithm>
# include <stack>
# include <memory>

// if shared data between threads is read only, there's no problem because the data read by one thread is unaffected by whether or not another thread is reading the same data
// but if data is shared between threads and one or more threads modify the data, there's lots of potential for bugs
// invariants are statements that are always true about a particular data structure
// these invariants can be broken temporarily during an update to the data structure, the simplest potential problem with modifying data shared between threads is that of broken invariants

// in concurrency, a race condition is anything where the outcome  depends om the relative ordering of execution of operations on two or more threads, the threads race to perform their respective operations
// when race conditions lead to broken invariants, this is a problematic race condition
// data races cause undefined behaviour

// race conditions are often hard to find and can be difficult to duplicate

// the simplest way to deal with problematic race conditions is to wrap your data structure with a protection mechanism to ensure that only the thread performing the modification can see the intermediate states when the invariants are broken
// from the point of view of the other threads accessing that data structure, such modifications either haven't started or haven't completed

// another option is to modify your data structure and its invariants so that modifications are done as a series of indivisible changes, each of which preserves the invariants
// this is referred to as lock free programming, which takes advantage of the memory model

// using mutexes: before accessing a shared data structure, you lock the mutex associated with that data, and then when you've finished accessing the data, you unlock the mutex
// the thread library ensures that once one thread has locked the mutex, all other threads that try to lock the same mutex will have to wait until the thread that locked the mutex unlocks it
// this ensures that all threads see a consistent view of the shared data without any broken invariants

// you can create a mutex object and lock and unlock it manually, but its preferred to create a lock_guard object and use that to manage the mutex via RAII 
// the lock guard locks the supplied mutex upon construction and unlocks it at destruction

// protecting a list with a mutex:

std::list<int> some_list;
std::mutex m;  // mutex associated with some_list

void add_to_list(int new_value)
{
	std::lock_guard<std::mutex> guard(m);  // create the lock guard within this scope, pass in mutex m
	some_list.push_back(new_value);
}

bool list_contains(int value)
{
	std::lock_guard<std::mutex> guard(m);
	return std::find(some_list.begin(), some_list.end(), value) != some_list.end();
}

// use of lock guard in the above functions means that accesses in these functions are mutually exclusive
// this means that two threads cannot add to the list at the same time

// cpp17 has class template auto deduction, which can be used here:
// std::lock_guard guard(m)  // don't need the template

// we could wrap the list and mutex in a class, marking them as private and setting the above functions as public to nicely control access to the list
// however if a function returned a pointer or reference to the list, the mutex can be bypassed. interfaces with mutexes therefore need to eb carefully deisgned
// we also need to ensure we don't pass protected resources into fucntions we may call within our member fucntions

/*
Rule: Don’t pass pointers and references to protected data outside the scope of the lock, whether by
returning them from a function, storing them in externally visible memory, or passing them as
arguments to user-supplied functions
*/

// just because individual operations on the list may be safe, there can still be race conditions
// for example, consider a stack using a mutex for each one of its operations, this could be considered safe 
// however, what if a thread calling empty() executed just after a thred calling pop? the thread calling empty may get a false result and then attempt to call top
// but by the time top is called, the other thread calling pop has executed and the other thread is calling top on an empty stack, thereby causing undefined behaviour

// these fucntions therefore may be safe in single threaded code but this doesn't carry over when multithreading due to data races like these where use of a mutex internally doesn't prevent it
// lets create a stack that combines the top and pop methods, in order to make it thread safe
// the issue is two threads calling the top() function can get the same value, but if the ordering isn't thread safe, they can then call pop() and two different items can be popped
// so the same item gets stored, and another item in teh stack gets lost
// another issue is if we combine top() and pop(), it can cause an issue if the copy constructor of the stack element can throw an exception
/*
consider stack<vector<int>>.
Now, a vector is a dynamically sized container, so when you copy a vector, the library
has to allocate some more memory from the heap in order to copy the contents. If the
system is heavily loaded or there are significant resource constraints, this memory allocation can fail, so the copy constructor for vector might throw a std::bad_alloc
exception. This is likely if the vector contains a lot of elements. If the pop() function
was defined to return the value popped, as well as remove it from the stack, you have a
potential problem: the value being popped is returned to the caller only after the stack
has been modified, but the process of copying the data to return to the caller might
throw an exception. If this happens, the data popped is lost; it has been removed from
the stack, but the copy was unsuccessful! The designers of the std::stack interface
helpfully split the operation in two: get the top element (top()) and then remove it
from the stack (pop()), so that if you can’t safely copy the data, it stays on the stack. If
the problem was lack of heap memory, maybe the application can free some memory
and try again.
 Unfortunately, it’s precisely this split that you’re trying to avoid in eliminating the
race condition! Thankfully, there are alternatives, but they aren’t without cost

option 1: pass in a reference to a variable in which we want to recieve the popped value as an argument in the call to pop(), not ideal as it requres an element of teh stacks type to eb created and the elements in the stack to be assignable
option 2: require a no-throw copy or move constructor, this works but limits the types we can store on the stack
option 3: return a smart pointer to the popped item, more overhead than returning by value but pointers can freely be copied without throwing an exception, the disadvantage is that returning a pointer requires a means of managing the memory allocated to the object, and for simple types like ints, the overhead of such memory management can exceed the cost of returning the type by value
// For any interface that uses this option, std::shared_ptr would be a good choice of pointer type; not only does it
avoid memory leaks, because the object is destroyed once the last pointer is destroyed, but the library is in full control of the memory allocation scheme and doesn’t have to use new and delete. 

lets use option 1 and 3

*/

// by reducing the number of operations the stack can do, we allow for maximum safety

/*
* Difference between initialiser list and using body of copy constructor
They are not the same if member1 and member2 are non-POD (i.e. non-Plain Old Data) types:

public : Thing(int _foo, int _bar){
	member1 = _foo;
	member2 = _bar;
}
is equivalent to

public : Thing(int _foo, int _bar) : member1(), member2(){
	member1 = _foo;
	member2 = _bar;
}
because they will be initialized before the constructor body starts executing, so basically twice the work is done. That also means, if the type of these members don't have default constructor, then your code will not compile.*/

// remember that mutexes cannot be copied or moved
// use a smart pointer to do this instead


// its critical to remember that each class has one mutex, and once the mutex is locked in one function, that means all the other fucntions it appears in will also not be able to modify the object
// below, we have locked the mutex in the copy constrcutor, this is important because we need the cpoy of data to go through without a race condition, the data should not be altered while this happens

struct empty_stack : std::exception
{
	const char* what() const throw();
};

template <typename T>
class threadsafe_stack
{
private:
	std::stack<T> data;
	mutable std::mutex m;  // this must be mutable as other is const reference in the copy constructor, and the lock and unlock methods are non const
public:
	threadsafe_stack(){}
	
	threadsafe_stack(const threadsafe_stack& other)  // class is copy constructible
	{
		std::lock_guard<std::mutex> lock(other.m);  // this is necessary due to the mutex being non copyable and non moveable, we need to lock the mutex m since this is what protects data
		data = other.data;  
	}
	
	threadsafe_stack& operator= (const threadsafe_stack&) = delete;  // cant be assigned
	
	void push(T new_value)
	{
		std::lock_guard<std::mutex> lock(m);
		data.push(std::move(new_value));
	}

	std::shared_ptr<T> pop()
	{
		std::lock_guard<std::mutex> lock(m);
		if (data.empty()) throw empty_stack();  // check for empty before trying to pop value
		std::shared_ptr<T> const res(std::make_shared<T>(data.top()));  // allocate return value before modifying stack
		data.pop();
		return res;
	}

	void pop(T& value)
	{
		std::lock_guard<std::mutex> lock(m);
		if (data.empty()) throw empty_stack();
		value = data.top();
		data.pop();
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> lock(m);
		return data.empty();
	}

};

// stack implementation is copyable, the copy constructor locks the mutex in the source object and then copies the internal stack
// fine grained locking introduces the potential for problematic race conditions
// introducing mutexes at too large a scale also risks removing the perofrmance benefits of concurrency

// if two or more mutexes are locked for a given operation, there's the potential for deadlock
// deadlock is the opposute of a race, each one is waiting for the other
/*  each of a pair of threads needs to lock both of a pair of
mutexes to perform some operation, and each thread has one mutex and is waiting
for the other. Neither thread can proceed, because each is waiting for the other to
release its mutex. This scenario is called deadlock, and it’s the biggest problem with
having to lock two or more mutexes in order to perform an operation. */

// the common advice for avoiding deadlock is to lock the two mutexes in the same order, if you always lock mutex A before mutex B, then you'll never deadlock

// the cpp stl has std::lock(), which is a function which can lock two or more mutexes as once without risk of deadlock

class some_big_object
{

};

void swap(some_big_object& lhs, some_big_object& rhs)
{

}

class X {
private:
	some_big_object some_detail;
	std::mutex m;
public:
	X(const some_big_object& sd) : some_detail(sd) {}

	friend void swap(X& lhs, X& rhs) {
		if (&lhs == &rhs) return;  // check they are different instances, undefined behaviour to lock a mutex you already acquired
		std::lock(lhs.m, rhs.m);  // call to std::lock locks both mutexes
		std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock); // lock guard instances created, one for each mutex
		std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);  // adopt_lock parameter is supplied in addition to the mutex to indicate to the std::lock_guard objects that the mutexes are already locked and they should adopy the ownership of the existing lock on the mutex rather than attempt to lock the mutex in the constructor
		swap(lhs.some_detail, rhs.some_detail);
	}
};// adopt lock param helps ensure mutexes are correctly unlocked upon function exit
/*
. Also, it’s worth noting that locking either lhs.m or rhs.m inside the call
to std::lock can throw an exception; in this case, the exception is propagated out of
std::lock. If std::lock has successfully acquired a lock on one mutex and an exception is thrown when it tries to acquire a lock on the other mutex, this first lock is
released automatically: std::lock provides all-or-nothing semantics with regard to
locking the supplied mutexes. */

/*
C++17 provides additional support for this scenario, in the form of a new RAII template, std::scoped_lock<>. This is exactly equivalent to std::lock_guard<>, except
that it is a variadic template, accepting a list of mutex types as template parameters, and
a list of mutexes as constructor arguments. The mutexes supplied to the constructor
are locked using the same algorithm as std::lock, so that when the constructor completes they are all locked, and they are then all unlocked in the destructor. The
swap() operation from listing 3.6 can be rewritten as follows:
void swap(X& lhs, X& rhs)
 {
 if(&lhs==&rhs)
 return;
 std::scoped_lock guard(lhs.m,rhs.m);
 swap(lhs.some_detail,rhs.some_detail);
 }
This example uses another feature added with C++17: automatic deduction of class
template parameters.
*/

// scoped lock can be unsed instead of thread guard to lock multiple mutexes at once, using std::lock under the hood
// further guidelines for avoiding deadlocks:


int main()
{

}