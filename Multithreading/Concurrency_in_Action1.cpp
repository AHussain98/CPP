# include <iostream>
# include <thread>


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




int main()  // main thread starts here
{
	std::thread t1(hello);  // thread launched and executes, main thread continues execution
	t1.join();  // join causes the calling thread to pause and wait for the joined thread

	std::thread t2(hello);
	thread_guard tg1(t2);  // create the thread guard and pass in the thread object


}