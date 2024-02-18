# include <iostream>
# include <thread>
# include <vector>


// cpus have cores, which have caches. Cores produce threads
// tasks can execute on individual cores
/*
In order to do the interleaving, the system has to perform a context switch every time it changes
from one task to another, and this takes time. In order to perform a context switch,
the OS has to save the CPU state and instruction pointer for the currently running
task, work out which task to switch to, and reload the CPU state for the task being
switched to. The CPU will then potentially have to load the memory for the instructions and data for the new task into the cache, which can prevent the CPU from executing any instructions, causing further delay.

Concurrency and parallelism have largely overlapping meanings with respect to
multithreaded code. Indeed, to many they mean the same thing. The difference is
primarily a matter of nuance, focus, and intent. Both terms are about running multiple tasks simultaneously, using the available hardware, but parallelism is much more
performance-oriented. People talk about parallelism when their primary concern is
taking advantage of the available hardware to increase the performance of bulk data
processing, whereas people talk about concurrency when their primary concern is separation of concerns, or responsiveness. This dichotomy is not cut and dried, and there
is still considerable overlap in meaning, but it can help clarify discussions to know of
this distinction. 

concurrency is good to use for performance and for seperation of concerns, giing certain tasks to certain threads to keep others free

There are two ways to use concurrency for performance. The first, and most obvious, is to divide a single task into parts and run each in parallel, reducing the total
runtime. This is task parallelism. Although this sounds straightforward, it can be quite a
complex process, because there may be many dependencies between the various
parts. The divisions may be either in terms of processing—one thread performs one
part of the algorithm while another thread performs a different part—or in terms of
data—each thread performs the same operation on different parts of the data. This
latter approach is called data parallelism.

there’s an inherent
overhead associated with launching a thread, because the OS has to allocate the associated kernel resources and stack space and then add the new thread to the scheduler,
all of which takes time. If the task being run on the thread is completed quickly, the
time taken by the task may be dwarfed by the overhead of launching the thread, possibly making the overall performance of the application worse than if the task had been
executed directly by the spawning thread.
 Furthermore, threads are a limited resource. If you have too many threads running at once, this consumes OS resources and may make the system as a whole run
slower. Not only that, but using too many threads can exhaust the available memory or
address space for a process, because each thread requires a separate stack space. T

The more threads you have running, the more context switching the operating system has to do

To achieve best possible performance, adjust the number of threads running to take into account the available number of cores

main thread launches other threads, which can launch other threads etc...

*/

/*
every thread has to have an initial function, where the new thread of execution begins

threads are started (launched) by creating an std::thread object that specifies the callable task to run on that object

if you pass a temporary rather than a named variable, the compiler will interperet the expression as a function returning an std::thread object

we can also pass in lambdas

// we must join or detach a thread before the std::thread object goes out of scope and is destroyed, otherwise the program terminates
the thread itself may well have finished executing by the time you call join or detach, but you still need to call them


if we call detach, we must ensure the data accessed by the thread is valid until the thread has finished with it
its wise to make the thread function self contained, and copy the data required into the thread rather than sharing the data from external
if you use a callable object for your thread, that object is copied into the thread, so its okay of the original is destroyed
In particular, it’s a bad idea to create a thread within a function that has access to the local variables in that function, unless
the thread is guaranteed to finish before the function exits.
 Alternatively, you can ensure that the thread has completed execution before the
function exits by joining with the thread

The act of calling join() also cleans up any storage associated with the thread, so the std::thread object is no longer associated with the nowfinished thread; it isn’t associated with any thread. This means that you can call join()
only once for a given thread; once you’ve called join(), the std::thread object is no
longer joinable, and joinable() will return false
*/


void hello()
{
	std::cout << "Hello Concurrent World!" << std::endl;
}

// if you don't call join or detach on a thread object, and then your code throws an exception, this will result in termination when the thread object goes out of scope
// to solve this, either join or detach the thread immediately after launching it or put the join/detach function call in the catch block of the exception

// Use RAII to wait for a thread to complete
class thread_guard {
	
	std::thread& t;  // private thread object

public:
	explicit thread_guard(std::thread& _t) : t(_t) {}
	~thread_guard()
	{
		if (t.joinable())  // check if the thread can be joined at the point of the thread_guards destruction, call if it can
		{
			t.join();  // 
		}
	}
	thread_guard(const thread_guard& t1) = delete;  // delete the copy constructor
	thread_guard& operator= (const thread_guard& t1) = delete;  // delete the assignment operator, we don't want threads living longer than their scope accidentally
};

// calling detach() on a thread means it runs in the background with no direct means of communicating with it
/*  Detached threads truly run in the background; ownership and control are passed over to the
C++ Runtime Library, which ensures that the resources associated with the thread are
correctly reclaimed when the thread exits. */

// function objects can still access their member data within a thread 

// the std::thread constructor copies the arguments as they are typed, so even if the function takes a const ref argument, if you don't label teh argument as const ref, it won't be treated as such
// this is also true for type conversions, if you construct a thread with a fucntion that expects a string but pass in a char * instead of a string, the thread will copy the char pointer into its local memory and then make the conversion to std::string itself, this can be time consuming

/*

Its crucial to remember that when supplying arguments to the function, the arguments are copied into the threads local data and then passed to the callable as rvalues
You can't pass an rvalue to a non const reference so keep that in mind when writing thread parameters
if you want a thread to reference an external object, the external object must be wrapped in std::ref within the thread constructor, this means that the thread has a reference to the external object and gets around the rvalue issue

Key point, when giving thread objects parameters, it will copy them regardless of the type the fucntion gives them, the only way around this is to wrap the parameters in std::ref()

passing arguments to the callable object or function is fundamentally as simple as passing additional arguments to the std::thread constructor.
But it’s important to bear in mind that by default, the arguments are copied into internal storage, where they can be accessed by the newly created thread of execution, and
then passed to the callable object or function as rvalues as if they were temporaries.
This is done even if the corresponding parameter in the function is expecting a reference. Here’s an example:
void f(int i,std::string const& s);
std::thread t(f,3,”hello”);
This creates a new thread of execution associated with t, which calls f(3,”hello”).
Note that even though f takes a std::string as the second parameter, the string literal is passed as a char const* and converted to a std::string only in the context of
the new thread. This is particularly important when the argument supplied is a
pointer to an automatic variable, as follows:

void f(int i,std::string const& s);
void oops(int some_param)
{
 char buffer[1024];
 sprintf(buffer, "%i",some_param);
Passing arguments to a thread function 25
 std::thread t(f,3,buffer);
 t.detach();
}
In this case, it’s the pointer to the local variable buffer that’s passed through to the
new thread and there’s a significant chance that the oops function will exit before
the buffer has been converted to a std::string on the new thread, thus leading to
undefined behavior. The solution is to cast to std::string before passing the buffer
to the std::thread constructor

void f(int i,std::string const& s);
void not_oops(int some_param)
{
 char buffer[1024];
 sprintf(buffer,"%i",some_param);
 std::thread t(f,3,std::string(buffer));
 t.detach();
}
In this case, the problem is that you were relying on the implicit conversion of the
pointer to the buffer into the std::string object expected as a function parameter,
but this conversion happens too late because the std::thread constructor copies the
supplied values as is, without converting to the expected argument type.
 It’s not possible to get the reverse scenario: the object is copied, and you wanted a
non-const reference, because this won't compile. You might try this if the thread is
updating a data structure that’s passed in by reference; for example:

void update_data_for_widget(widget_id w,widget_data& data);
void oops_again(widget_id w)
{
 widget_data data;
 std::thread t(update_data_for_widget,w,data);
 display_status();
 t.join();
 process_widget_data(data);
}
Although update_data_for_widget expects the second parameter to be passed by reference, the std::thread constructor doesn’t know that; it’s oblivious to the types of
the arguments expected by the function and blindly copies the supplied values. But
the internal code passes copied arguments as rvalues in order to work with move-only
types, and will thus try to call update_data_for_widget with an rvalue. This will fail to
compile because you can't pass an rvalue to a function that expects a non-const reference. For those of you familiar with std::bind, the solution will be readily apparent:
you need to wrap the arguments that need to be references in std::ref. In this case,
if you change the thread invocation to

std::thread t(update_data_for_widget,w,std::ref(data));

then update_data_for_widget will be correctly passed a reference to data rather
than a temporary copy of data, and the code will now compile successfully.
 If you’re familiar with std::bind, the parameter-passing semantics will be unsurprising, because both the operation of the std::thread constructor and the operation of std::bind are defined in terms of the same mechanism. This means that, for
example, you can pass a member function pointer as the function, provided you supply a suitable object pointer as the first argument:
class X
{
public:
 void do_lengthy_work();
};
X my_x;
std::thread t(&X::do_lengthy_work,&my_x);
This code will invoke my_x.do_lengthy_work() on the new thread, because the address
of my_x is supplied as the object pointer. You can also supply arguments to such a
member function call: the third argument to the std::thread constructor will be the
first argument to the member function, and so forth.

Remember: you can pass a member function reference to the thread via a ref to the class, second argument is the address of the object
This does not create any copies
you have to create an instance of the class to pass for the second argument, and any other params may need to be references, else they will be created locally in teh thread and passed as rvalues


unique pointers cannot be copied, only moved
because of this behaviour, unique pointers can be passed into and returned from fucntions
where the source object is temporary, the move is automatic, where the source object is named, you have to use the std::move() function
you have to use std::move in the parameters of the thread object aswell

The following example shows the use of
std::move to transfer ownership of a dynamic object into a thread:

void process_big_object(std::unique_ptr<big_object>);
std::unique_ptr<big_object> p(new big_object);
p->prepare_data(42);
std::thread t(process_big_object,std::move(p));

By specifying std::move(p) in the std::thread constructor, the ownership of big_
object is transferred first into internal storage for the newly created thread and then
into process_big_object

So use std::move() in the thread constructor parameter if we want to move the object into the thread context
*/

class test {
public:
	void do_some_work(int& value)
	{
		std::cout << "Threaded value: " <<  value  <<  std::endl;
		value++;
	}
};

// instances of std::thread are moveable, not copyable
// this can be done to pass ownership of threads between different functions
// a thread that has been moved from can have a new thread object moved into it
/*
void some_function();
void some_other_function();
std::thread t1(some_function);
std::thread t2=std::move(t1);
t1=std::thread(some_other_function);   This is valid, t1 had a thread associated with it, this was moved to t2, then t1 had a new thread moved to it via this temporary thread object
std::thread t3;
t3=std::move(t2);
t1=std::move(t3);  // This is not, cant accept a move from an empty thread object, and t1 can't accept the thread from t3 since t1 already has a thread object it is responsible for
*/

// you can't move from a thread object that hasn't been associated with a thread of execution (not had a function passed in)
// so you cant move from a thread thats default constructed
// you also cant move to a thread that already has a associated thread of execution running

/*
if ownership should be transferred into a function, it can accept an instance
of std::thread by value as one of the parameters, as shown here:

void f(std::thread t);
void g()
{
 void some_function();
 f(std::thread(some_function));  // pass a temporary rvalue, this gets moved to f
 std::thread t(some_function);
 f(std::move(t));  // pass a named object as an rvalue, this also gets moved

 }
 
 This is consistent behaviour with the moveable type std::thread

 Because of this move support, we can create a thread guard class that takes responsibility for managing threads
*/

class scoped_thread
{
	std::thread t; // private std::thread object

public:
	scoped_thread(std::thread t_) : t(std::move(t_)) {  // std::move simply casts to an rvalue, it had no effect if the type is already an rvalue, so we can use it here even if its redundant 
		if (!t.joinable())  // thread has to be associated with a thread of execution to be joinable, so check this first, throw if not
		{
			throw std::logic_error("no thread!");
		}
	}
    ~scoped_thread()  // destructor calls join regardless, this will happen when the scoped_thread object goes out of scope
		{
			t.join();
		}
	scoped_thread(const scoped_thread& t) = delete;
	scoped_thread& operator=(const scoped_thread& t) = delete;  // we can't copy or assign the scoped thread object
};

/*

struct func;  // an example of how this can work
void f()
{
 int some_local_state;
 scoped_thread t{std::thread(func(some_local_state))};
 do_something_in_current_thread();
} */  // scoped_thread destructs here so calls join on the thread it holds

// we can spawn threads and wait for them to finish
void say_hi()
{
	std::cout << "hi from thread " << std::this_thread::get_id() << std::endl;
}

// std::thread::hardware_concurrency() returns the number of threads that can truly run concurrently, because it returns the number of cpu cores on the machine
// we want to use the number of threads given by this function, any more and we introduce time slicing overhead, any less and we leave power on the table
// but we also shouldn't use more threads than necessary since they need to be shared out by the OS for every process on the machine
// you can't return a value from a thread, but you can pass in an object by reference for a thread to write to

// thread objects have a get_id() function, the thread header also has std::this_thread::get_id()
// thread id's are hashable and have comparison operators so can be used as keys in ordered and unordered associatove data structures





int main()  // main thread starts here
{
	std::thread t1(hello);  // thread launched and executes, main thread continues execution
	t1.join();  // join causes the calling thread to pause and wait for the joined thread

	std::thread t2(hello);
	thread_guard tg1(t2);  // create the thread guard and pass in the thread object

	int value = 5;
	test test_1;

	std::thread t3(&test::do_some_work, &test_1, std::ref(value));  // first arg is reference to the class fucntion, second is reference to instance
	t3.join();

	std::cout << "the value in main is now: " << value << std::endl;  // therad has sucessfully updated the referenced integer

	std::vector<std::thread> threads;
	for (size_t i = 0; i < 20; ++i)
	{
		threads.emplace_back(say_hi); // create threads in the vector running this function
	}
	for (auto& i : threads)
	{
		i.join();
	}

	std::cout << "number of cores on this machine: " << std::thread::hardware_concurrency() << std::endl;

}