# include <iostream>
# include <thread>
# include <vector>
# include <string>
# include <mutex>
# include <list>
# include <algorithm>
# include <stack>
# include <memory>
# include <shared_mutex>
# include <map>

// c++ compilers will automatically create a constructor, copy constructor and destructor and make them public by deafult 
// no default move constuctor is created if there is a defined destructor

// mutexes cannot be copied or moved

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
	threadsafe_stack() {}

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
		std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);  // adopt_lock parameter is supplied in addition to the mutex to indicate to the std::lock_guard objects that the mutexes are already locked and they should adopt the ownership of the existing lock on the mutex rather than attempt to lock the mutex in the constructor
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
are locked using the same algorithm as std::lock, so that when the constructor completes they are all locked, and they are then all unlocked in the destructor. The
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

// scoped lock can be used instead of thread guard to lock multiple mutexes at once, using std::lock under the hood

// further guidelines for avoiding deadlocks:
// deadlocks cannot only occur with locks, you can get a deadlock with two threads and no locks by having each thread call join() on the std::thread object for each other 
// in that case, neither thread can make progress since they're waiting for each other to finish
// don't every wait for another thread if there's a chance it's waiting for you
// avoid nested locks, don't acquire a lock if you already have one. This way makes it impossible to get a deadlock due to locks because each thread only holds one lock. If you need to acquire multiple threads, do it as a single action with std::lock(0 to acquire them without a deadlock
// avoid calling user-supplied code while holding a lock, user supplied code could do many things, including acquiring another lock
// acquire locks in a fixed order, in the same order for every thread. establish an order of traversal for every thread
/* use a lock hierarchy, divide the application into layers and identify all the mutexes that may be locked in any given layers.When code tries to lock a mutex, it isn’t permitted to lock that mutex
if it already holds a lock from a lower layer. You can check this at runtime by assigning layer numbers to each mutex and keeping a record of which mutexes are locked by each thread. */

class hierarchical_mutex  // this code allows us to check the behaviour of each thread seperately, and the code for each mutex can check whether that current thread is allowed to lock that mutex
{
	std::mutex internal_mutex;
	unsigned long const hierarchy_value;  // value passed into the object, this is the level of the mutex
	unsigned long previous_hierarchy_value;
	static thread_local unsigned long this_thread_hierarchy_value;  // thread local variable to store current hierrchical value, this is accessible to all mutex instances but has a different value on each thread

	// this_thread_hierarchy_value is static and thread_local, so its unique for each thread and every time the thread comes across a hierarchical_mutex object, the check is made with the value specific to that thread, static so used across all objects

	void check_for_hierarchy_violation()
	{
		if (this_thread_hierarchy_value <= hierarchy_value)  // if you try to lock another mutex, the value must be less than that of the mutex already held in order to pass
		{
			throw std::logic_error("mutex hierarchy violated");
		}
	}
	void update_hierarchy_value()
	{
		previous_hierarchy_value = this_thread_hierarchy_value;  // save the previous value of the hierarchy so it can be restored in unlock()
		this_thread_hierarchy_value = hierarchy_value;  // thread local value here is initialised to the maximum value as seen below so its greater than any other value and check_for_hierarchy_violation will pass initally, every thread gets their own copy
	}
public:
	explicit hierarchical_mutex(unsigned long value) : hierarchy_value(value), previous_hierarchy_value(0) {}  // constructor
	void lock()  // delegates to the internal mutex for locking
	{
		check_for_hierarchy_violation();
		internal_mutex.lock();
		update_hierarchy_value();  // if lock succeeded, update the hierarchical value
	}
	void unlock()  // restore the previous value, otherwise you'd never be able to lock a mutex with a higher value again
	{
		if (this_thread_hierarchy_value != hierarchy_value)
		{
			throw std::logic_error("mutex hierarchy violated");
		}
		this_thread_hierarchy_value = previous_hierarchy_value;  // previous_hierarchy_value is safely protected by the mutex
		internal_mutex.unlock();
	}
	bool try_lock()
	{
		check_for_hierarchy_violation();
		if (!internal_mutex.try_lock()) return false;
		update_hierarchy_value();
		return true;
	}
};

thread_local unsigned long hierarchical_mutex::this_thread_hierarchy_value(ULONG_MAX); // initalise the thread local value to maximum initally, so any lock can be aquired at the start

// now an example of how this can work with 2 threads using a hierarchical mutex

hierarchical_mutex high_level_mutex(10000);
hierarchical_mutex low_level_mutex(5000);  // three instances of hierarchical mutex, which are constructed with progressively lower hierarchy numbers
hierarchical_mutex other_mutex(6000);
// because the mechanism is designed so if you hold a lock on a hierarchical mutex, then you can only acquire a lock on another hierarchical mutex with a lower hierarchy number, this imposes restrictions on what the code can do

int do_low_level_stuff();

int low_level_func()
{
	std::lock_guard<hierarchical_mutex> lk(low_level_mutex);
	return do_low_level_stuff();  // assuming this doesnt lock any mutexes, low_level_func is the bottom of the hirarchy and locks the low level mutex
}

void high_level_stuff(int some_param);
void high_level_func()
{
	std::lock_guard<hierarchical_mutex> lk(high_level_mutex);
	high_level_stuff(low_level_func());  // high level func calls low level func, while holding a lock on high level mutex, this is good because the hierarchy level of high_level_mutex is higher than that of low_level_mutex
}
void thread_a()
{
	high_level_func();  // thread a abides by the rules so it runs fine
}

void do_other_stuff();
void other_stuff()
{
	high_level_func();
	do_other_stuff();
}

void thread_b()  // thread b disregards the rukes so will fail at runtime
{
	std::lock_guard<hierarchical_mutex> lk(other_mutex);  // thread b locks off other_mutex which has a hierarchy value of only 6000, which is midway in the hierarchy
	other_stuff();  // other_stuff calls high_level-func(), which is violating the hierarchy, high_level_func() tries to acquire the high_level_mutex but can't because 10000 is greater than its current hierarchy value
}

/*
The hierarchical_mutex will therefore report an error, possibly by throwing an exception or aborting the program. Deadlocks
between hierarchical mutexes are impossible, because the mutexes themselves enforce the lock ordering. This does mean that you can’t hold two locks at the same
time if they’re the same level in the hierarchy, so hand-over-hand locking schemes require that each mutex in the chain has a lower hierarchy value than the prior one, which may be impractical in some cases
*/

// std::lock_guard<> template can be used with a user defined mutex type, as seen here
// hierarchical mutex can be used with lock_guard because it implements the three member functions required to satisfy the mutex concept, lock(), unlock() and try_lock()
// try_lock() returns false if the mutex has already been acquired by another thread

/*
 just as you should avoid acquiring nested locks if possible, it’s a bad idea to
wait for a thread while holding a lock, because that thread might need to acquire the
lock in order to proceed. Similarly, if you’re going to wait for a thread to finish, it
might be worth identifying a thread hierarchy, so that a thread waits only for threads
lower down the hierarchy. One simple way to do this is to ensure that your threads are
joined in the same function that started them.
 Once you’ve designed your code to avoid deadlock, std::lock() and std::
lock_guard cover most of the cases of simple locking, but sometimes more flexibility
is required. For those cases, the Standard Library provides the std::unique_lock
template. Like std::lock_guard, this is a class template parameterized on the mutex
type, and it also provides the same RAII-style lock management as std::lock_guard,
but with a bit more flexibility.
*/

// thread_local variables allow you to have a seperate instance of a variable for each thread in your program
// variables at namespace scope, static data members of classes and local variables can be declared thread_local, and are said to have thread storage duration

thread_local int x;  // thread local variable at namespace scope

class X
{
	static thread_local std::string x;  // static thread_local class member,, will be the same for all objects of this class created by this thread
};
thread_local std::string X::x{ "Yo!" };  // definition of X::s, when defining a static variable, don't put static in front, this causes an error

void foo()
{
	thread_local int x;  // thread_local local variable in this function
}

// thread_local variables at namespace scope and thread_local static class data members are constructed before first use of a thread_local variable from the same translation unit, but its not specified when
// these thread_local variables may be constructed when the thread is started or immediately before first use
// if the thread_local variables are not used, they are not guaranteed to be constructed

/*  Thread-local variables declared inside a function are initialized the first time the
flow of control passes through their declaration on a given thread. If the function is
not called by a given thread, any thread-local variables declared in that function are
not constructed. This is the same as the behavior for local static variables, except it
applies separately to each thread.
 Thread-local variables share other properties with static variables—they’re zeroinitialized prior to any further initialization (such as dynamic initialization), and if the
construction of a thread-local variable throws an exception, std::terminate() is called
to abort the application.

The destructors for all thread-local variables that have been constructed on a given
thread are run when the thread function returns, in the reverse order of construction.
Because the order of initialization is unspecified, it’s important to ensure that there
are no interdependencies between the destructors of these variables. If the destructor
of a thread-local variable exits with an exception, std::terminate() is called, as for
construction.
*/


// std::unique_lock is like std::lock_guard, a class template parameterised on the mutex type, and it provides the same RAII style lock management ast std::lock_guard but with more flexibility
// std::unique_lock provides a bit more flexibility than std::lock_guard by relaxing the invariants
// std::unique_lock instance doesn't always own the mutex it's associated with
// remember that you can pass std::adopt_lock as a second argument to the constructor to have the lock object manage the lock on a mutex, you can also pass std::defer_lock as the second argument to indicate that the mutex should remain unlocked on construction
// this means that the lock can then be acquired by calling lock() on the unique_lock object, not on the mutex itself, or by passing the unique_lock object to std::lock
// std::unique_lock takes more space and is slightly slower to use than std::lock_guard. The flexibility of allowing an std::unique_lock instance not to own the mutex comes at a price: this information has to be stored, and it has to be updated

class some_big_object
{
};

void swap(some_big_object& lhs, some_big_object& rhs);

class X_1
{
	some_big_object some_detail;
	std::mutex m;

public:
	X_1(const some_big_object& sd) : some_detail(sd){}  // constructor

	friend void swap(X_1& lhs, X_1& rhs)  // here we're declaring a friend function and making it inline, while also defining it. Remember that friend functions are not member fucntions
		// this fucntion is able to call the swap function below because its a friend fucntion, so the swap below is able to access the private some_detail objects of class X
	{
		if (&lhs == &rhs)
		{
			return;
		}
		std::unique_lock<std::mutex> lock_a(lhs.m, std::defer_lock);  // std::defer_lock leaves mutexes unlocked
		std::unique_lock<std::mutex> lock_b(rhs.m, std::defer_lock);  // mutexes are not owned yet
		std::lock(lock_a, lock_b);  // mutexes are locked here, now the unique_lock owns the mutexes. instead of being locked upon creation of the unique_lock
		swap(lhs.some_detail, rhs.some_detail);
	}
};

// std::unique_lock objects can be passed to std::lock() because unique_lock provides lock(), try_lock() and unlock()
// these forward to the underlying mutex member fucntions of the same name to do the work and update a flag in the unique_lock instance to indicate whether the mutex is currently owned by that instance
// flag allows destructor to check if it needs to call unlock
// this flag can be queried by calling the owns_lock() member function
// unless you're going to be transferring lock ownership around, its better to use std::coped_lock than unique_lock
// unique_lock performance is worse than lock_guard due to this flag updating

// unique_lock should be used when we want deferred locking or if we want to transfer ownership of teh lock from one scope to another

// because unique_locks dont have thier own associated mutexes, the ownership of a mutex can be transferred between instances by moving the instances around
// unique_locks are moveable but not copyable, like threads are
// one possible use is to allow a fucntion to lock a mutex and transfer ownership of the lock to the caller, so the caller can performn additional actions under the protection of teh same lock

// get_lock() fucntion locks the mutex then prepares the data before returning the lock to its caller
std::unique_lock<std::mutex> get_lock()
{
	extern std::mutex some_mutex;  // externally declared lock
	std::unique_lock<std::mutex> lk(some_mutex);  // remember that unique_lock does not need to own the lock, so it can be moved to transfer ownership of the held lock to another scope
	prepare_data();
	return lk;  // because lk is an automatic variable defined in the fucntion, it can be returned directly without calling std::move(), the compiler takes care of calling the move constructor
}

void process_data()
{
	std::unique_lock<std::mutex> lk(get_lock());  // the process_data function can then transfer ownershipdirectly into its own unique_lock instance and the call to do_something() can rely on the data being prepared correctly without any other thread altering teh data
	do_something();
}

// the unique_lock is also teh exclusive owener of a lock, at any time, only one unique lock can own a specific mutex, so the unique lock cannot be copied
// however the unique_lock does not have to actually own the mutex, so it can be moved to trasnfer ownership to another scope
// the mutex itself is locked wherever it is, we've just transferred ownership of it

/*
 The flexibility of std::unique_lock also allows instances to relinquish their locks
before they’re destroyed. You can do this with the unlock() member function, like for
a mutex. std::unique_lock supports the same basic set of member functions for locking and unlocking as a mutex does, so that it can be used with generic functions such
as std::lock. The ability to release a lock before the std::unique_lock instance is
destroyed means that you can optionally release it in a specific code branch if it’s
apparent that the lock is no longer required. This can be important for the performance of the application; holding a lock for longer than required can cause a drop in
performance, because other threads waiting for the lock are prevented from proceeding for longer than necessary.
*/


// its important to ensure that a lock is only held for the operations that require it
// lock guard does not support manual locking and unlock of the mutex, this is done only upson constructiona nd destriction of the object
// unique lock gives us more control

// if multiple threads are waiting for the same resource, and some threads hold the lock for longer than necessary, this increses the total time spent waiting
// lock a mutex only when accessing the shared data, try to do any data processing outside the lock, especially not somehting time consuming like file input/output
// std::unique_lock works well in this situation, because you can call unlock() when the code no longer needs access to the shared dataand then call lock() again if access is required later in the code

void get_and_process_data()
{
	std::unique_lock<std::mutex> my_lock(the_mutex); // example unqiue lock, unique locks are locked by default upon construction
	some_class data_to_process = get_next_data_chunk();
	my_lock.unlock();  // dont need the lock at this point
	result_type result = process(data_to_process);  // we can process the data without the lock
	my_lock.lock();
	write_result(data_to_process, result); // relock the mutex to write safely 
}
// if you only have one mutex protecting an entire data structure, there is likely to be more contention for the lock but there's less chance of reduceing the time the lock is held
/*  In general, a lock should be held for only the minimum possible time needed to perform the required operations. This also means that timeconsuming operations such as acquiring another lock (even if you know it won’t
deadlock) or waiting for I/O to complete shouldn’t be done while holding a lock
unless absolutely necessary */

/*  the swap operation previously required locking both mutexes, which due to being a swap obvioudly requies concurrent access to both objects
Suppose
instead you were trying to compare a simple data member that was a plain int. Would
this make a difference? ints are cheap to copy, so you could easily copy the data for
each object being compared while only holding the lock for that object and then compare the copied values. This would mean that you were holding the lock on each
mutex for the minimum amount of time and also that you weren’t holding one lock
while locking another. The following listing shows a class Y for which this is the case
and a sample implementation of the equality comparison operator

*/

// locking one mutex at a time in a comparison operator
class Y
{
private:
	int some_detail;
	mutable std::mutex m;
	int get_detail() const{
		std::lock_guard<std::mutex> lock_a(m);  // retrieve the value while prtecting it with the lock
		return some_detail;
	}

public:
	Y(int sd) : some_detail(sd) {}
	friend bool operator==(const Y& lhs, const Y& rhs) {
		if (&lhs == &rhs) {
			return true;
		}
		int const lhs_value = lhs.get_detail();  // reduce the locking period so only one lock is held at a time
		int const rhs_value = rhs.get_detail();
		return lhs_value == rhs_value;
	}
};

// howvwe there may be a change to one of teh values by another thread inbetween get_detail being called for lhs and rhs, 
// we dont hold both mutexes at once, so this result is only true for a moment in time
/*
. It’s therefore important to be careful when making these changes
that the semantics of the operation are not changed in a problematic fashion: if you
don’t hold the required locks for the entire duration of an operation, you’re exposing yourself to
race conditions.
 Sometimes, there isn’t an appropriate level of granularity because not all accesses
to the data structure require the same level of protection. In this case, it might be
appropriate to use an alternative mechanism, instead of a plain std::mutex.*/

// a common example is when shared data needs protection from concurrent access while its being initialised, but after that its not necessary
// the data may be read only after creating for example
// the C++ standard provides a mechanism for this, called lazy initialisation

// suppose you have a shared resource thats so expensive to create that you only want to do it once (like a database connection)
// If the shared resource itself is safe for concurrent access, the only part that needs protecting when converting this to multithreaded code is the initialization

std::shared_ptr<some_resource> resource_ptr;
std::mutex resource_mutex;
void foo()
{   
	std::unique_lock<std::mutex> lk(resource_mutex);  // all threads serialised here
	if (!resource_ptr)
	{
		resource_ptr.reset(new some_resource);  // initialisation is the only thing that needs protection
	}
	lk.unlock();
	resource_ptr->do_something();
}

// this is unnecessary serialisation because each thread must wait on the mutex in order to check whether the resource has already been initialised
/*This code is common enough, and the unnecessary serialization problematic enough,
that many people have tried to come up with a better way of doing this, including the
infamous double-checked locking pattern: the pointer is first read without acquiring the
lock (B in the following code), and the lock is acquired only if the pointer is NULL.
The pointer is then checked again once the lock has been acquired (c, hence the
double-checked part) in case another thread has done the initialization between the first
check and this thread acquiring the lock:
void undefined_behaviour_with_double_checked_locking()
{
   if(!resource_ptr) 
   {
    std::lock_guard<std::mutex> lk(resource_mutex);
    if(!resource_ptr) 
      {
          resource_ptr.reset(new some_resource); 
      }
    }
   resource_ptr->do_something(); 
}
Unfortunately, this pattern is infamous for a reason: it has the potential for nasty race
conditions, because the read outside the lock B, isn’t synchronized with the write
done by another thread inside the lock d. This creates a race condition that covers
not only the pointer itself but also the object pointed to; even if a thread sees the
pointer written by another thread, it might not see the newly created instance of
some_resource, resulting in the call to do_something() e operating on incorrect values. This is an example of the type of race condition defined as a data race by the C++
Standard and specified as undefined behavior. It’s therefore quite definitely something
to avoid.*/

// so to avoid a race condition where the pointer is set before the object is created, we can use the std::once_flag and std::call_once to handle this

// rather than locking a mutex and explicitly checking the pointer, every thread can use std::call_once, safe in the knowledge that the pointer will have been initialised by some thread (in a synchronised fashion) by the time std::call_once returns
// the synchronisation data is stored in std::once_flag instance, each instance of once_flag corresponds to a diffrent initialisation
/*
Use of std::call_once will typically have a lower overhead than using a
mutex explicitly, especially when the initialization has already been done, so it should be
used in preference where it matches the required functionality. */

std::shared_ptr<some_resource> resource_ptr;
std::once_flag resource_flag;
void init_resource()
{
	resource_ptr.reset(new some_resource);
}
void foo()
{
	std::call_once(resource_flag, init_resource);  // initialisation is called exactly once by calling the init_resource fucntion
	resource_ptr->do_something();  
}
/*
In this case,
the initialization is done by calling a function, but it could easily have been done with
an instance of a class with a function call operator. Like most of the functions in the
standard library that take functions or predicates as arguments, std::call_once
works with any function or callable object

both the std::once_flag and data being initialized are namespacescope objects, but std::call_once() can easily be used for lazy initialization of class
members
*/

// below is an example of a class member use of std::call_once and std::once_flag
/*
class X
{
private:
	connection_info connection_details;
	connection_handle connection;
	std::once_flag connection_init_flag;
	void open_connection()
	{
		connection = connection_manager.open(connection_details);
	}
public:
	X(connection_info const& connection_details_) :
		connection_details(connection_details_)
	{}
	void send_data(data_packet const& data)
	{
		std::call_once(connection_init_flag, &X::open_connection, this);
		connection.send_data(data);
	}
	data_packet receive_data()
	{
		std::call_once(connection_init_flag, &X::open_connection, this);
		return connection.receive_data();
	}
};
In that example, the initialization is done either by the first call to send_data() B,
or by the first call to receive_data() d.The use of the open_connection() member
function to initialize the data also requires that the this pointer be passed in.Just as
for other functions in the Standard Library that accept callable objects, such as the
constructors for std::threadand std::bind(), this is done by passing an additional
argument to std::call_once() c.
It’s worth noting that like std::mutex, std::once_flag instances can’t be copied
or moved, so if you use them as a class member like this, you’ll have to explicitly
define these special member functions should you require them.

*/

// global static variables and static class memebrs are initialsed by once one thread, no other threads will procees wuntil that initialisation is complete

// this can be used as an alternative to std::call_once for those cases where a single global instance is required

class myclass {
};
myclass& get_my_class_instance()
{
	static myclass instance;  //  initialisation guaranteed to be thread safe
	return instance;
}

// mutiple threads can call the above function safely without having to worry about race conditions on the initialisation


// protecting rarely updated data structures
// std::shared_mutex and std::shared_timed_mutex are special types of mutex called reader-writer mutexes
// they allow exclusive access for a single writer thread and shared.concurrent access by multiple reader threads

/*
Rather than using an instance of std::mutex for the synchronization, you use an
instance of std::shared_mutex.For the update operations, std::lock_guard
<std::shared_mutex>and std::unique_lock<std::shared_mutex> can be used for
the locking, in place of the corresponding std::mutex specializations.These ensure
exclusive access, as with std::mutex.Those threads that don’t need to update the
data structure can instead use std::shared_lock<std::shared_mutex> to obtain
shared access.This RAII class template was added in C++14, and is used the same as
std::unique_lock, except that multiple threads may have a shared lock on the same
std::shared_mutex at the same time.The only constraint is that if any thread has a
shared lock, a thread that tries to acquire an exclusive lock will block until all other
threads have relinquished their locks, and likewise if any thread has an exclusive lock,
no other thread may acquire a shared or exclusive lock until the first thread has relinquished its lock. */

class dns_entry;
class dns_cache
{
	std::map<std::string, dns_entry> entries;
	mutable std::shared_mutex entry_mutex;
public:
	dns_entry find_entry(const std::string& domain) const
	{
		std::shared_lock<std::shared_mutex> lk(entry_mutex);
		std::map<std::string, dns_entry>::const_iterator const it = entries.find(domain);
		return (it == entries.end()) ? dns_entry() : it->second;
	}
	void update_or_add_entry(const std::string& domain, const dns_entry& dns_details)
	{
		std::lock_guard<std::shared_mutex> lk(entry_mutex);
		entries[domain] = dns_details;
	}
};

/*
find_entry() uses an instance of std::shared_lock<> to protect it for
shared, read-only access; multiple threads can therefore call find_entry() simultaneously without problems. On the other hand, update_or_add_entry() uses an
instance of std::lock_guard<> to provide exclusive access while the table is updated; not only are other threads prevented from doing updates in a call to update_
or_add_entry(), but threads that call find_entry() are blocked too */

//  Recursive locking
// with std::mutex, its an error for a thread to try to lock a mutex it already wns, and attempting to do so will result in undefined behaviour
// std::recursive_mutex allows the same thread to reaquire the same mutex multiple times without having released it
// with recursive_mutex, you have to release all your locks before another thread can access it, so if lock() is called 3 times, unlock() will also need to be called 3 times




int main()
{

}