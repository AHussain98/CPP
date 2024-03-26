# include <iostream>
# include <atomic>
# include <vector>
# include <thread>

// mutexes provide mutual exclusion, only one thread can acquire the lock on a mutex at a time
// this prevents true concurrency
//  this is called serialisation, threads take turns accessing the data protected by the mutex
// the smaller the protected region, the fewer operations are serialsed, the greater the potential for concurrency

// designing concurrent code
// factors affecting the performance of concurrent code:
// if two threads are executing concurrently on different processors and they're both reading the same data, this usually won't cause a problem, the data will be copied into their respective caches and both processors can proceed
// but if one of the threads modifies the data, then this change has to propagate to the cache on the other core, which takes time and can be phenominally slow
/*  If the function is short enough, or if there are too many processors
running this code, the processors might find themselves waiting for each other; one
processor is ready to update the value, but another processor is currently doing that,
so it has to wait until the second processor has completed its update and the change
has propagated. This situation is called high contention. If the processors rarely have to
wait for each other, you have low contention.
 the data will be passed back and forth between
the caches many times. This is called cache ping-pong, and it can seriously impact the
performance of the application. If a processor stalls because it has to wait for a cache
transfer, it can’t do any work in the meantime, even if there are other threads waiting
that could do useful work, so this is bad news for the whole application

Even if a particular memory
location is only ever accessed by one thread, you can still get cache ping-pong due to
an effect known as false sharing.

Processor caches don’t generally deal in individual memory locations; instead, they
deal in blocks of memory called cache lines. These blocks of memory are typically 32 or
64 bytes in size, but the exact details depend on the particular processor model being
used. Because the cache hardware only deals in cache-line-sized blocks of memory,
small data items in adjacent memory locations will be in the same cache line. Sometimes
this is good: if a set of data accessed by a thread is in the same cache line, this is better
for the performance of the application than if the same set of data was spread over multiple cache lines. But if the data items in a cache line are unrelated and need to be
accessed by different threads, this can be a major cause of performance problems.
 Suppose you have an array of int values and a set of threads that each access their
own entry in the array but do so repeatedly, including updates. Because an int is typically much smaller than a cache line, quite a few of those array entries will be in the
same cache line. Consequently, even though each thread only accesses its own array
entry, the cache hardware still has to play cache ping-pong. Every time the thread
accessing entry 0 needs to update the value, ownership of the cache line needs to be
transferred to the processor running that thread, only to be transferred to the cache
for the processor running the thread for entry 1 when that thread needs to update its
data item. The cache line is shared, even though none of the data is, hence the term
false sharing. The solution here is to structure the data so that data items to be accessed
by the same thread are close together in memory (and thus more likely to be in the
same cache line), whereas those that are to be accessed by separate threads are far
apart in memory and thus more likely to be in separate cache lines

 The C++17 standard
defines std::hardware_destructive_interference_size in the header <new>, which
specifies the maximum number of consecutive bytes that may be subject to false sharing for the current compilation target. If you ensure that your data is at least this number of bytes apart, then there will be no false sharing.

Although false sharing is caused by having data accessed by one thread too close to
data accessed by another thread, another pitfall associated with data layout directly
impacts the performance of a single thread on its own. The issue is data proximity: if
the data accessed by a single thread is spread out in memory, it’s likely that it lies on
separate cache lines. On the flip side, if the data accessed by a single thread is close
together in memory, it’s more likely to lie on the same cache line. Consequently, if
data is spread out, more cache lines must be loaded from memory onto the processor
cache, which can increase memory access latency and reduce performance compared
to data that’s located close together.
 Also, if the data is spread out, there’s an increased chance that a given cache line
containing data for the current thread also contains data that’s not for the current
thread. At the extreme, there’ll be more data in the cache that you don’t care about
than data that you do. This wastes precious cache space and increases the chance that
the processor will experience a cache miss and have to fetch a data item from main
memory even if it once held it in the cache, because it had to remove the item from
the cache to make room for another

. If you have too many additional threads, there will
be more threads ready to run than there are available processors, and the operating
system will have to start task switching quite heavily in order to ensure they all get a
fair time slice. As you saw in chapter 1, this can increase the overhead of the task
switching as well as compound any cache problems resulting from lack of proximity.
Oversubscription can arise when you have a task that repeatedly spawns new threads
without limits, as the recursive quick sort from chapter 4 did, or where the natural
number of threads when you separate by task type is more than the number of processors and the work is naturally CPU-bound rather than I/O-bound.

 The key things to bear in mind when designing your data structures for multithreaded performance are contention, false sharing, and data proximity. All three of these
can have a big impact on performance, and you can often improve things by altering
the data layout or changing which data elements are assigned to which thread. First
off, let’s look at an easy win: dividing array elements between threads.

Fundamentally, the same considerations apply when trying to optimize the data access
patterns of other data structures as when optimizing access to arrays:
 Try to adjust the data distribution between threads so that data that’s close
together is worked on by the same thread.
 Try to minimize the data required by any given thread.
 Try to ensure that data accessed by separate threads is sufficiently far apart to
avoid false sharing using std::hardware_destructive_interference_size as
a guide.

A program contains a sequence of instructions that the CPU executes. The sequence
of instructions is stored somewhere in the memory of the computer. The CPU keeps
track of the address of the currently executing instruction in a register called a
program counter. In that way, the CPU knows what instruction to execute next.
The CPU contains a fixed number of registers. A register is similar to a variable
with a predefined name that can store a value or a memory address. Registers
are the fastest data storage available on a computer and sit closest to the CPU.
When the CPU manipulates data, it uses the registers. Some of the registers have a
special meaning to the CPU, whereas other registers can be used more freely by the
currently executing program.
Two very important registers that have a special meaning to the CPU are:
• Program counter (PC): The register that stores the memory address of the
currently executing instruction. This value is automatically incremented
whenever an instruction is executed. Sometimes it is also called an instruction
pointer.

• Stack pointer (SP): It stores the address of the top of the currently used call
stack. Allocating and deallocating stack memory is a matter of changing the
value stored in this single register.
Figure 12.3: A CPU with registers
Assume that the registers are called R0, R1, R2, and R3 as in the preceding diagram.
A typical arithmetic instruction could then look like this:
add 73, R1 // Add 73 to the value stored in R1
Data can also be copied between registers and memory:
mov SP, R2 // Copy the stack pointer address to R2
mov R2, [R1] // Copy value of R2 to memory address stored in R1
A set of instructions refers implicitly to the call stack. The CPU knows where the top
of the call stack is through the stack pointer. Allocating memory on the stack is only
a matter of updating the stack pointer. The value increases or decreases depending
on whether the stack grows towards higher or lower addresses.
The following instruction uses the stack:
push R1 // Push value of R1 to the top of the stack
The push instruction copies the value in the register to the place in memory pointed
at by the stack pointer and increments (or decrements) the stack pointer.
We can also pop values from the stack by using the pop instruction, which also reads
and updates the stack pointer:
pop R2 // Pop value from the stack into R2
Whenever an instruction is executed, the CPU automatically increments the
program counter. But the program counter can also be explicitly updated through
instructions, for example, the jump instruction:
jump R3 // Set the program counter to the address in R3

The CPU can operate in two modes: user mode or kernel mode. The CPU registers
are used differently when running in user mode and kernel mode. When the CPU
is executing in user mode, it runs with restricted privileges that cannot access
hardware. The operating system provides system calls that run in kernel mode.
A C++ library function such as std::puts(), which prints values to stdout, must
therefore make a system call to complete its task, forcing the CPU to switch between
user mode and kernel mode.
Transitioning between user and kernel mode is expensive. To understand why,
let's think about our schematic CPU again. The CPU operates efficiently by using
its registers and therefore avoids spilling values onto the stack unnecessarily. But
the CPU is a shared resource among all user processes and the operating system,
and whenever we need to switch between tasks (for example, when entering kernel
mode), the state of the processor, including all of its registers, needs to be saved in
memory so that it can be resumed later on.
Call and return
Now that you have a basic understanding of how the CPU uses registers and the
stack, we can discuss subroutine invocations. There are a lot of mechanisms involved
when calling and returning from a subroutine that we might take for granted. Our
compilers are doing an excellent job when they transform a C++ function to highly
optimized machine code.
The following list shows the aspects that need to be considered when calling,
executing, and returning from a subroutine:
• Calling and returning (jumping between points in the code).
• Passing parameters—parameters can be passed through registers or on the
stack, or both.
• Allocating storage for local variables on the stack.
• Returning a value—the value returned from a subroutine needs to be stored
in a place where the caller can find it. Typically, this is a dedicated CPU
register.
• Using registers without interfering with other functions—the registers that
a subroutine uses need to be restored to the state they were in before the
subroutine was called.
The exact details about how function calls are carried out are specified by something
called calling conventions. They provide a protocol for the caller/callee to agree
on who is responsible for which parts. Calling conventions differ among CPU
architectures and compilers and are one of the major parts that constitutes an
application binary interface (ABI).

When a function is being called, a call frame (or activation frame) for that function is
being created. The call frame contains:
• The parameters passed to the function.
• The local variables of the function.
• A snapshot of the registers that we intend to use and therefore need to restore
before returning.
• A return address that links back to the place in memory where the caller
invoked the function from.
• An optional frame pointer that points back to the top of the caller's call frame.
Frame pointers are useful for debuggers when inspecting the stack. We will
not discuss frame pointers further in this book.
Thanks to the strictly nested nature of subroutines, we can save the call frames of the
subroutines on the stack to support nested calls very efficiently. A call frame stored
on the stack is usually called a stack frame

False sharing, or destructive interference, can degrade performance very
significantly. It occurs when two threads use some data (that is not logically shared
between the threads) but happen to be located in the same cache line. Imagine
what will happen if the two threads are executing on different cores and constantly
updating the variable residing on the shared cache line. The threads will invalidate
the cache line for each other, although there is no true sharing of data between the
threads.
False sharing will most likely occur when using global data or dynamically allocated
data that is shared between threads. An example where false sharing is likely to
occur is when allocating an array that is shared between threads, but each thread is
only using a single element of the array.
The solution to this problem is to pad each element in the array so that two adjacent
elements cannot reside on the same cache line. Since C++17, there is a portable way
of doing this using the std::hardware_destructive_interference_size constant
defined in <new> in combination with the alignas specifier. The following example
demonstrates how to create an element that prevents false sharing:
struct alignas(std::hardware_destructive_interference_size) Element {
 int counter_{};
};
auto elements = std::vector<Element>(num_threads);
The elements in the vector are now guaranteed to reside on separate cache lines.

A data race happens when two threads are accessing the same memory at the same
time and at least one of the threads is mutating the data. If your program has a
data race, it means that your program has undefined behavior. The compiler and
optimizer will assume that there are no data races in your code and optimize it under
that assumption. This may result in crashes or other completely surprising behavior.
In other words, you can under no circumstances allow data races in your program.
The compiler usually doesn't warn you about data races since they are hard to detect
at compile time

Anything could happen when your program has a data race. One such
example is tearing, which is the common term for torn reads and torn writes. This
happens when a thread writes parts of a value to memory while another thread
reads the value at the same time and therefore ends up with a corrupt value.

Now, having data end up in different places on the heap isn’t a particular problem
in itself, but it does mean that the processor has to keep more things in cache. This
can be beneficial. If multiple threads need to traverse the tree, then they all need to
access the tree nodes, but if the tree nodes only contain pointers to the real data held
at the node, then the processor only has to load the data from memory if it’s
needed. If the data is being modified by the threads that need it, this can avoid the
performance hit of false sharing between the node data itself and the data that provides the tree structure.

advanced thread management
on most systems, its impractical to have e a separate thread for every task that
can potentially be done in parallel with other tasks, but you’d still like to take advantage of the available concurrency where possible. A thread pool allows you to accomplish this; tasks that can be executed concurrently are submitted to the pool, which
puts them on a queue of pending work. Each task is then taken from the queue by
one of the worker threads, which executes the task before looping back to take another
from the queue.
 There are several key design issues when building a thread pool, such as how many
threads to use, the most efficient way to allocate tasks to threads, and whether or not
you can wait for a task to complete.

at its simplest, a thread pool is a fixed number of worker threads (same num as hardware concurrency) that process work
 When you have work to do, you call a function to put it on the queue of
pending work. Each worker thread takes work off the queue, runs the specified task,
and then goes back to the queue for more work

*/

class thread_pool
{
	std::atomic_bool done;  // declared first because it must be destroyed last
	threadsafe_queue<std::function<void()> > work_queue;  // threadsafe queue, can only be copy constrcutible elements because std::fucntion requires that the stored function objects are copy constructible
	std::vector<std::thread> threads;  // vector of worker threads, this is declared here because it must be destroyed before the work queue
	join_threads joiner;

	void worker_thread()
	{
		while (!done)
		{
			std::function<void()> task;
			if (work_queue.try_pop(task))
			{
				task();
			}
			else
			{
				std::this_thread::yield();
			}
		}
	}
public:
	thread_pool() :
		done(false), joiner(threads)
	{
		unsigned const thread_count = std::thread::hardware_concurrency();
		try
		{
			for (unsigned i = 0; i < thread_count; ++i)
			{
				threads.push_back(
					std::thread(&thread_pool::worker_thread, this));  // threads started in the constructor, only create as many as num of cores
			}
		}
		catch (...)  //
		{
			done = true;
			throw;
		}
	}
	~thread_pool()
	{
		done = true;
	}
	template<typename FunctionType>
	void submit(FunctionType f)
	{
		work_queue.push(std::function<void()>(f));  // wraps whatever function or callable object is passed to the function in an std::function wrapper and pushes it onto the queue
	}
};

/*
Every time a thread calls submit() on a particular instance of the thread pool, it has
to push a new item onto the single shared work queue. Likewise, the worker threads
are continually popping items off the queue in order to run the tasks. This means that
as the number of processors increases, there’s increasing contention on the queue.
This can be a real performance drain; even if you use a lock-free queue so there’s no
explicit waiting, cache ping-pong can be a substantial time sink.

 One way to avoid cache ping-pong is to use a separate work queue per thread.
Each thread then posts new items to its own queue and takes work from the global
work queue only if there’s no work on its own individual queue. The following listing
shows an implementation that makes use of a thread_local variable to ensure that
each thread has its own work queue, as well as the global one.
*/

class thread_pool
{
	threadsafe_queue<function_wrapper> pool_work_queue;
	typedef std::queue<function_wrapper> local_queue_type;
	static thread_local std::unique_ptr<local_queue_type> local_work_queue;  // static unique pointer to thread local queue used because we dont want other threads that arent part of our thread pool to have one, destruction of unique pointer ensures work queue destroyed when thread exits
	void worker_thread()
	{
		local_work_queue.reset(new local_queue_type);

		while (!done)
		{
			run_pending_task();
		}
	}
public:
	template<typename FunctionType>
	std::future<typename std::result_of<FunctionType()>::type> submit(FunctionType f)
	{
		typedef typename std::result_of<FunctionType()>::type result_type;
		std::packaged_task<result_type()> task(f);
		std::future<result_type> res(task.get_future());
		if (local_work_queue)  // checks to see if current thread has work queue
		{
			local_work_queue->push(std::move(task));  // push onto local queue
		}
		else  // if not, then push into pool work queue
		{
			pool_work_queue.push(std::move(task));
		}
		return res;
	}
	void run_pending_task()
	{
		function_wrapper task;
	
			if (local_work_queue && !local_work_queue->empty())
			{
				task = std::move(local_work_queue->front());
				local_work_queue->pop();
				task();
			}
			else if (pool_work_queue.try_pop(task))
			{
				task();
			}
			else
			{
				std::this_thread::yield();
			}
	}
	// rest as before
}

/*

There’s a similar check in run_pending_task() , except this time you also need
to check to see if there are any items on the local queue. If there are, you can take the
front one and process it; notice that the local queue can be a plain std::queue
because it’s only ever accessed by the one thread. If there are no tasks on the local
queue, you try the pool queue as before



concurrency-related bugs fall into two
categories:
 Unwanted blocking
 Race conditions
These are broad categories, so let’s divide them up a bit. First, let’s look at unwanted
blocking.
11.1.1 Unwanted blocking
What do I mean by unwanted blocking? A thread is blocked when it’s unable to proceed
because it’s waiting for something. This is typically something like a mutex, a condition variable, or a future, but it could be waiting for I/O. This is a natural part of
multithreaded code, but it’s not always desirable—hence the problem of unwanted
blocking. This leads us to the next question: why is this blocking unwanted? Typically, this is because some other thread is also waiting for the blocked thread to perform some action, and so that thread in turn is blocked. There are several variations
on this theme:
 Deadlock—As you saw in chapter 3, in the case of deadlock, one thread is waiting
for another, which is in turn waiting for the first. If your threads deadlock, the
tasks they’re supposed to be doing won’t get done. In the most visible cases, one
of the threads involved is the thread responsible for the user interface, in which
case the interface will cease to respond. In other cases, the interface will remain
responsive, but some required tasks won’t complete, such as a search not
returning or a document not printing.
 Livelock—Livelock is similar to deadlock in that one thread is waiting for
another, which is in turn waiting for the first. The key difference here is that the
wait is not a blocking wait but an active checking loop, such as a spin lock. In
serious cases, the symptoms are the same as deadlock (the app doesn’t make
any progress), except that the CPU usage is high because threads are still running but blocking each other. In not-so-serious cases, the livelock will eventually
resolve because of the random scheduling, but there will be a long delay in the
task that got livelocked, with a high CPU usage during that delay.
 Blocking on I/O or other external input—If your thread is blocked waiting for external input, it can’t proceed, even if the waited-for input is never going to come.
It’s therefore undesirable to block on external input from a thread that also
performs tasks that other threads may be waiting for.
That briefly covers unwanted blocking. What about race conditions?

Race conditions are the most common cause of problems in multithreaded code—
many deadlocks and livelocks only manifest because of a race condition. Not all race
conditions are problematic—a race condition occurs any time the behavior depends
on the relative scheduling of operations in separate threads. A large number of race
conditions are entirely benign; for example, which worker thread processes the next
task in the task queue is largely irrelevant. But many concurrency bugs are due to race
conditions. In particular, race conditions often cause the following types of problems:
 Data races—A data race is the specific type of race condition that results in
undefined behavior because of unsynchronized concurrent access to a shared
memory location. I introduced data races in chapter 5 when we looked at the
C++ memory model. Data races usually occur through incorrect usage of atomic
operations to synchronize threads or through access to shared data without
locking the appropriate mutex.
 Broken invariants—These can manifest as dangling pointers (because another
thread deleted the data being accessed), random memory corruption (due to a
thread reading inconsistent values resulting from partial updates), and doublefree (such as when two threads pop the same value from a queue, and so both
delete some associated data), among others. The invariants being broken can
be temporal- as well as value-based. If operations on separate threads are required
to execute in a particular order, incorrect synchronization can lead to a race
condition in which the required order is sometimes violated.
 Lifetime issues—Although you could bundle these problems in with broken
invariants, this is a separate category. The basic problem with bugs in this category is that the thread outlives the data that it accesses, so it is accessing data
that has been deleted or otherwise destroyed, and potentially the storage is
even reused for another object. You typically get lifetime issues where a thread
references local variables that go out of scope before the thread function has
completed, but they aren’t limited to that scenario. Whenever the lifetime of
the thread and the data it operates on aren’t tied together in some way, there’s
the potential for the data to be destroyed before the thread has finished and for
the thread function to have the rug pulled out from under its feet. If you manually call join() in order to wait for the thread to complete, you need to ensure
that the call to join() can’t be skipped if an exception is thrown. This is basic
exception safety applied to threads.
It’s the problematic race conditions that are the killers. With deadlock and livelock,
the application appears to hang and become completely unresponsive or takes too
long to complete a task. Often, you can attach a debugger to the running process to
identify which threads are involved in the deadlock or livelock and which synchronization objects they’re fighting over. With data races, broken invariants, and lifetime
issues, the visible symptoms of the problem (such as random crashes or incorrect
output) can manifest anywhere in the code—the code may overwrite memory used by
another part of the system that isn’t touched until much later. The fault will then manifest in code completely unrelated to the location of the buggy code, possibly much
later in the execution of the program. This is the true curse of shared memory systems—however much you try to limit which data is accessible by which thread, and try
to ensure that correct synchronization is used, any thread can overwrite the data
being used by any other thread in the application.



 Here are my questions:
 Which data needs to be protected from concurrent access?
 How do you ensure that the data is protected?
 Where in the code could other threads be at this time?
 Which mutexes does this thread hold?
 Which mutexes might other threads hold?
 Are there any ordering requirements between the operations done in this
thread and those done in another? How are those requirements enforced?
 Is the data loaded by this thread still valid? Could it have been modified by
other threads?
 If you assume that another thread could be modifying the data, what would that
mean and how could you ensure that this never happens?
This last question is my favorite, because it makes me think about the relationships
between the threads. 

*/



int main()
{

}