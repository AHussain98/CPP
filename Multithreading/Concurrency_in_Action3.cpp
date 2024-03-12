# include <iostream>
# include <thread>
# include <mutex>
# include <vector>
# include <chrono>
# include <condition_variable>
# include <queue>
# include <memory>
# include <future>
# include <string>
# include <deque>
# include <utility>



// synchronise concurrent operations
// sometimes we don't need to just protect the data, we also need to synchrnoise actions on seperate threads
// one thread might need to wait for another thread to complete a task before the first thread can complete its own, for example
// in general, its common to want a thread to wait for a specific event to happen or a condition to become true
// you can do this by constantly polling or checking for a "task complete" flag or something similar, this is far from optimal
// we can synchronise operations between threads like this through the use of condition_variables and futures.

// if one thread is waiting for a second thread to complete a task, it has several options
// first, it could keep checking a flag in shared memory (protected by a mutex) and have the second thread set the flag when it completes the task
// this is wasteful, the first thread wastes computation by continoually checking the flag and when the mutex is locked by the waiting thread, it can't be locked by any other thread
// the waiting thread is then taking away computation resources from the thread being waited on, and reducing performance by holding the mutex so the flag can't be changed

// a second option is to have the waiting thread sleep for short periods between the checks using the std::this_thread::sleep_for() function

bool flag;
std::mutex m;
void wait_for_flag() {
	std::unique_lock<std::mutex> lk(m);  // unique lock created but not locked yet
	while (!flag) {
		lk.unlock();  // unlock the mutex before sleeping, so another thread gets the chance to acquire it and set the flag
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		lk.lock();  // relock the mutex
	}
}

// this is an improvement because the thread doesn't waste processing time while it's sleeping but it's hard to get the sleep period right

// the third and preferred option is to use the standard library to wait for the event itself
// the most basic mechanism for waiting for an event to be triggered by another thread (such as the presence of additional work in the pipeline mentioned previously is the condition variable
// a condition variable is associated with an event or other condition, and one or more threads can wait for that condition to be satisfied
// when a thread has determined that the condition is satisfied, then it can notify one or more of the threads waiting on the cindition variable in order to wake them up and allow them to continue processing

// the standard library provides two implementations of a condition variable, std::condition_variable and std::condition_variable_any, both defined in <condition_variable>
// they need to work with a mutex in order to provide appropriate synchronisation
// std::condition_variable needs to work with only std::mutex, and std::condition_variable_any can work with any type that meets the minimal criteria for being mutex-like
// std::condition_variable is therefore lower cost

// waiting for data to process with std::condition_variable
/*
std::mutex mut;
std::queue<data_chunk> data_queue;  // queue thats used to pass the data between two threads
std::condition_variable cond;

void data_preperation_thread()
{
	while (more_data_to_prepare())
	{ // when the data is ready, the thread preparing the data locks the mutex protecting the queue using std::lock_guard
		data_chunk const data = prepare_data();
		{
			std::lock_guard<std::mutex> lk(mut);  // code to push the data in the queue is in a smaller scope, so you notify the condition variable after unlocking the mutex, this is so that if the waiting thread wakes immediately, it doesnt have to block again, waiting for you to unlock the mutex
			data_queue.push(data);
		}
		cond.notify_one();  // it then calls the notify_one() member fucntion of the condition variable to notify the waiting thread (if there is one)
	}
}
// on the other side of the fence, you have the processing thread

void data_processing_thread()
{
	while (true)
	{
		std::unique_lock<std::mutex> lk(mut);  // this thread first locks the mutex with a unique lock rather than a lock_guard
		cond.wait(lk, [] {return !data_queue.empty(); });  // wait is called on the condition variable with the speific condition being waited for in the lambda
		// the lambda checks to see if the data queue is empty or not, the wait function returns if the condition is true
		// if the condition is not satisfied, the lamda function returns false and wait() unlocks the mutex and puts the thread in a blocked or waiting state
		// when the condition variable is notofied by the call to notify_one() in the preperation_thread() fucntion, the thread wakes from its slumber (is unblocked), reacquires the lock on the mutex and and checks the condition again, returning from wait() with the mutex still locked if the condition is true
		// if the condition has not been satisfied, the thread unlocks the mutex and resumes waiting
		// this is why we need std::unique_lock rather than lock_guard, the waiting thread must unlock the mutex while its waiting and lock it again afterwards, and lock_guard doesn't have that much flexibility
		// if the mutex remained locked while the thread was sleeping, we wouldnt be able to access the queue to add data, which would mean the condition would never be satisfied
		// during a call to wait(), the condition variable may check the supplied condition any number fo times, and it will always do so with the mutex locked and will return immediately only if the function provided to the mutex returns true
		// when the waiting thread reacquires the mutex and checks the condition, if this isnt in direct response to a notify() call in another thread,it's called a spurious wake
		// because this check can happen an indeterminate number of times, itrs important that your condition check function not have any side effects, as they too will occur each time
		data_chink data = data_queue.front();
		data_queue.pop();
		lk.unlock();
		process(data);  // unique lock is used because we can unlock before we start processing data, which we only want to do once we don't have the lock, so it can be acquired by any other threads
		// mutexes should not be held onto longer than necessary
		if (is_last_chunk(data)) break;
	}
}

// condition_variable::wait is an optimisation over a busy-wait
// using a queue to transfer data between threads is a common scenario, the synchronisation can be limited to the queue itself, which greatly reduces the number of possible synchronization problems and race conditions

// building a thread safe queue with condition variables
// query the whole of the whole queue (empty() and size()), query the elements of the queue (front() and back()) and thise that modify the queue (push), pop() and emplace())
// same considerations of race conditions inherent in the stack
// combine front() and pop() into a single function call, same as when we combines top() and pop() for the stack
// when using a queue to pass data between threads, the recieveing thread often needs ti wait for the data. Lets provide two variants on pop, try_pop() which tries to pop the value from the queue but always returns immediately with an indication of failure even if there wasnt a value to retrieve
// and wait_and_pop() which waits until there's a value to retrieve

// contain the mutex and condition variable in the threadsafe_queue instance, so that seperate variables are no longer required and no external synchronisatin is required for the call to push()
// wait_and_pop() can take care of the condition variable wait

template <typename T>
class threadsafe_queue
{
private:
	mutable std::mutex mut;  // make this mutable
	std::queue<T> data_queue;
	std::condition_variable cond;

public:
	threadsafe_queue(){};
	threadsafe_queue& operator=(const threadsafe_queue& other) = delete;   // we want this non assignable for simplicity
	threadsafe_queue(const threadsafe_queue& other)
	{
		std::lock_guard<std::mutex> lk(other.mut);  // lock the other mutex, this is why mutex must be mutable in order to violate const
		data_queue = other.data_queue;
	}
	void push(T value)
	{
		std::lock_guard<std::mutex> lk(mut);
		data_queue.push(value);
		cond.notify_one();  // notify any thread waiting for the queue to not be empty
	}
	void wait_and_pop(T& value)
	{
		std::unique_lock<std::mutex> lk(mut); // lock here
		cond.wait(lk, [this]() {return !data_queue.empty(); });  // why pass this?
		value = data_queue.front();
		data_queue.pop();
	}
	std::shared_ptr<T> wait_and_pop() {  // overloaded 
		std::unique_lock<std::mutex> lk(mut);
		cond.wait(lk, [this]() {return !data_queue.empty(); });
		std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
		data_queue.pop();
		return res;  // return a shared pointer to the front element
	}
	bool try_pop(T& value)  // no waiting
	{
		std::lock_guard<std::mutex> lk(mut);
		if (data_queue.empty()) return false;
		value = data_queue.front();
		data_queue.pop();
		return true;
	}
	std::shared_ptr<T> try_pop()  // overload, no waiting
	{
		std::lock_guard<std::mutex> lk(mut);
		if (data_queue.empty()) return std::shared_ptr<T>();  // return empty shared pointer
		std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));  // create shared pointer to front element
		data_queue.pop();
		return res;
	}
	bool empty() const
	{
		std::lock_guard<std::mutex> lk(mut);  // mutex locked as its mutable, even though function is const
		return data_queue.empty();
	}

};

*/


// although empty() is a const member function, and the other parameter in the copy constructor is const reference, other threads may have non-const references to the object, and may be calling mutating member functions so you still need to lock the mutex
// since locking a mutex is a mutating operation, the mutex object must be marked mutable so that it can be locked in empty() and in the constructor
// condition variables are useful when there's more than one thread waiting for the same event
// notify_one() will trigger one of te threads currenctly executing wait() to check its condition and return from wait() (because you've just added an item to the queue)
// there's no guarantee of which thread will be notified or even if there's a thread to be notified at all, all the processing threads may still be procesing data
// another possibility is that several threads are waiting for the same event and all of them need to respond. This can happen where shared data is being initialised and the processing threads can all use the same data but need to wait for it to be initialised
// or where the threads need to wait for a periodic update to shared data
// in these cases, the thread preparing teh data can call notify_all() on the condition variable. This causes all the threads currently executing wait() to check the cindition they're waiting for.

// if the waiting thread is only going to wait once, where the condition becomes true means it will never wait again, a condition variable may not be the best choice of synchronisation mechanism
// this is particularly true if the event being waited for is availability of a specific piece of data
// in this scenario, a future may be more appropriate

// if a thread needs to wait for a specific one off event, it somehow obtains a future representing that event
// the thread can then periodically wait on the future for short periods of time to see if the event has occured while performing some other task between checks
// alternatively it can do another task until it needs the event to have happened before it can proceed and then just waits for the future to become ready
// the future cant be reset after it happens

// two sorts of futures, unique futures std::future<> and shared features std::shared_future<>
// these are based on unique and shared pointers
/* an instance of std::future is the one and only instance that refers to its associated event
* multiple instances of shared_future can refer to the same event, all the instances will become ready at the same time and they may all access any data associated with the event
* the template parameter is the type of the associated data
* futures are used to communicate between threads, but if multiple threads need to access a single future object, they must still use a mutex or synchronisation mechanism
* multiple threads may each access their own copy of shared_future, even if they all refer to the same asynchronous result
* 
* 

futures are useful for returning values from threads

std::async starts an asynchrounous task for which we dont need the result right now, pass it a callable 
std::async returns a std::future object, which will eventually hold the return value of the function
When you need the value, you can call get() on the future and the thread blocks until the future is ready and then returns the value
get() can only be called ONCE on the future object! Only one thread can retireve the std::future value because after the first call to get(), there's no value left to retrieve


*/

int find_the_answer();

void do_other_stuff();

// std::async allows you to pass additional arguments to the function by adding extra arguments to the call
// if arguments are rvalues, they are moved into the async. This allows move only types to be used for both the function object and the argument
// can give async a pointer to a member function then next param is the object to call it on, then functiojn params
struct X
{
	void foo(int i, const std::string& s);
	std::string bar(const std::string& s);
};

struct Y
{
	double operator() (double d);
};

/* If the first argument is
a pointer to a member function, the second argument provides the object on which to
apply the member function (either directly, or via a pointer, or wrapped in std::ref),
and the remaining arguments are passed as arguments to the member function*/

X bax(X&);  

class move_only
{
public:
	move_only();
	move_only(move_only&&);
	move_only& operator=(move_only&&);
	move_only & operator=(move_only const&) = delete;
	void operator()();
};

// by default, its up to the implementation whether std::async starts a new thread or whether the task runs synchronously when the future is waited for
// we can specify which to use with an additional parameter to std::async before the function to call
/*  This parameter is of the type std::launch,
and can either be std::launch::deferred to indicate that the function call is to be
deferred until either wait() or get() is called on the future, std::launch::async to
indicate that the function must be run on its own thread, 
or std::launch::deferred | std::launch::async to indicate that the implementation may choose*/
// this last option is the default. If the function is called, it may never run




// an std::future can be associated with a task by wrapping it in an instance of std::packaged_task<> or writing code to explicitly set the values using std::promise
// packaged_task<> ties a future to a function or callable object, when it is invoked, it calls the associated function or callable object and makes the future ready, with the return value stored as the associated data
// template parameter for the std::packaged_task<> class template is a fucntion signature, like void() for a fucntion taking no parameters and int(std::string&,double*) for a function that takes a non-const refernce to a std::string and a pointer to a double and returns an int

// std::packaged_task<> is a callable object, it can be wrapped in a std::function object, passed to a std::thread as the thread function, passed to another function that requires a callable or even invoked directly
// passing tasks between threads:

std::mutex m;
std::deque<std::packaged_task<void()>> tasks;
bool gui_shutdown_message_recieved();
void get_and_process_gui_message();

void gui_thread()
{
	while (!gui_shutdown_message_recieved())  // gui thread loops until a message is recieved to gui to shut down
	{
		get_and_process_gui_message();  // repeatedly polling for messages to handle and tasks on the task queue
		std::packaged_task<void()> task;
		{
			std::lock_guard<std::mutex> lk(m);
			if (tasks.empty()) continue;   // if there are no tasks on the queue then loop again
			task = std::move(tasks.front());  // extract the task from the queue, release the lock on the queue
			tasks.pop_front();
		}
		task();  // run the task, the future associated with the task will then be made ready when the task completes
	}
}
// posting a task on the queue is simple
std::thread gui_bg_thread(gui_thread);
template<typename Func>
std::future<void> post_task_for_gui_thread(Func f)
{
	std::packaged_task<void()> task(f);  // a packaged task is created from the supplied function
	std::future<void> res = task.get_future();  // the future is obtained from the task
	std::lock_guard<std::mutex> lk(m);
	tasks.push_back(std::move(task));  // by calling the get_future() member function and the task is put on the list
	return res;  // before the future is returned to the caller
}

// this example uses std::packaged_task<void()> for the tasks, which wraps a function or other callable object that takes no parameters and returns void
// std::promise is used to set a future when the tasks cant be expressed as a simple fucntion call or we have tasks where the results come from more than one place

// std::promise<T> provides a means of setting a value of type T that can later be read through an associated std::future<T> object
// you can obtain the std::future object associated with a given std::promise by calling the get_future() member function, just like with packaged task
// when the value of the promise is set using the set_value() method, the future becomes ready and can be used to retreieve the stored value
// If you destroy the std::promise without setting a value, an exception is stored instead.

// if the function call invoked as part of std::async throws an exception, that exception is stored in the future in place of a stored value, the future becomes ready and a call to get() rethrows that stored exception
// the same happens if you wrap the function in an std::packaged_task- when the task is invoked, if the wrapped function throws an exception, the exception is stored in the future in place of the retunred result, ready to be thrown on a call to get()
// std::promise provides the same facility, with an explicit function call. If you want to store an exception rather than a value, you can call the set_exception() member function rather than set_value()
/*
Another way to store an exception in a future is to destroy the std::promise or
std::packaged_task associated with the future without calling either of the set functions on the promise or invoking the packaged task. In either case, the destructor of
std::promise or std::packaged_task will store a std::future_error exception with
an error code of std::future_errc::broken_promise in the associated state if the
future isn’t already ready; by creating a future you make a promise to provide a value
or exception, and by destroying the source of that value or exception without providing one, you break that promise. If the compiler didn’t store anything in the future in
this case, waiting threads could potentially wait forever.
 Up until now, all the examples have used std::future. However, std::future has
its limitations, not the least of which being that only one thread can wait for the result.
If you need to wait for the same event from more than one thread, you need to use
std::shared_future instead.
*/

// when using std::future, only one thread can wait for the result
// if you need to wait for the same event from more than one thread, you need to use std::shared_future instead

// calls to the member functions of a particular std::future instance are not synchronised with each other
// If you access a single std::future object from multiple threads without additional synchronization, you have a data race
// and undefined behavior.This is by design : std::future models unique ownership of
// the asynchronous result, and the one - shot nature of get() makes such concurrent
// access pointless anyway—only one thread can retrieve the value, because after the first
// call to get() there’s no value left to retrieve.

// if the design of the concurrent code requires that multiple threads wait for the same event, std::shared_future allows that
// std::future is only moveable, ownership can be transferred between instances but only one instance refers to a particular asynchronous result at a time
// std::shared_future instances are copyable, so you can have multiple objects referring to the same associated state

// the preferred way to access a shared_future in a thread safe way would be via mutex, or to give each thread its own copy of the shared_future object

// we can call wait() and wait_for() on future objects to give them time to get readied
// Duration - based waits are done with instances of std::chrono::duration<>.For
// example, you can wait for up to 35 milliseconds for a future to be ready :
// std::future<int> f = std::async(some_task);
// if (f.wait_for(std::chrono::milliseconds(35)) == std::future_status::ready)
// do_something_with(f.get());
// The wait functions all return a status to indicate whether the wait timed out or the
// waited - for event occurred.In this case, you’re waiting for a future, so the function
// returns std::future_status::timeout if the wait times out, std::future_status::
// ready if the future is ready, or std::future_status::deferred if the future’s task is deferred.


// MEMORY MODEL
// There are two aspects to the memory model, the basic structural aspects, which relate to how things are laid out in memory, and the concurrency aspects



int main()
{
	std::future<int> the_answer = std::async(find_the_answer);  // using std::future to get the returned result of asynchronous task
	do_other_stuff();
	std::cout << the_answer.get() << std::endl;  // get the returned value from the asynchronous task

	X x;
	auto f1 = std::async(&X::foo, &x, 42, "hello");  // callable, object to call it on, then parameters. so foo(42,"hello") is called on x
	auto f2 = std::async(&X::bar, x, "goodbye"); // // calls bar("goodbye") on a copy of x

	auto f3 = std::async(Y(), 3.1415);  // calls Y(3.1415) where Y in async is move constucted
	Y y;
	auto f4 = std::async(std::ref(y), 3.1415);  // calls y(3.1415)

	auto f5 = std::async(bax, std::ref(x));  // calls bax(x)

	auto f6 = std::async(move_only());  // calls tmo() where tmp is constructed from std::move(move_only())

	auto f7 = std::async(std::launch::async, Y(), 1.2);  // run in new thread

	auto f8 = std::async(std::launch::deferred, bax, std::ref(x));  // run in wait() or get()

	auto f9 = std::async(std::launch::deferred | std::launch::async, bax, std::ref(x));  // implementation chooses

	auto f10 = std::async(bax, std::ref(x));  // implementation chooses again

	f10.get();  // remember that to get the value from a future you actually have to call get() on it
	// now no other thread can call get() on f10, the value has already been taken

	f8.wait();

}





