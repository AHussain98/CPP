# include <iostream>
# include <type_traits>
# include <utility>
# include <string>

// Compile time programming
// metaprogramming allows you to write code that transforms into regular c++ code
// template metaprogramming in c++ is used to generate functions, values and classes that accept different types
// teplate is instantiated when the compiler uses that template to generate a class or function
// constant expressions are evaluated by the compiler to generate constant values

// beyond general types, a template can also be of int and float types
template<int T, typename U>
auto pow(U val)
{
	auto product{ 1 };
	for (int i = 0; i < T; ++i)
	{
		product *= val;
	}
	return product;
}

// for every vaue of T, a new function is created. However U is passed like a regular parameter so does not result in a new function
// now lets write a specialisation where T is fixed and U's type is fixed. they both have to be fixed for a fucntion specialisation to work
template<>
auto pow<2, int>(const int v)
{
	return v * v;
}

/* For function templates, we need to fix all template parameters when writing a 
specialization. For example, it's not possible to only specify the value of N and let 
the type argument T be unspecified. However, for class templates, it is possible to 
specify only a subset of the template parameters. This is called partial template 
specialization. The compiler will choose the most specific template first.
The reason we cannot apply partial template specialization to functions is that 
functions can be overloaded (and classes cannot). If we were allowed to mix 
overloads and partial specialization, it would be very hard to comprehend  */


// when the template fucntion is handled by the cmopiler, it constructs a regular function with the template parameters expanded
// the compiler will generate new functions for every unique set of template parameters. The template code generates non template code, which is executed as regular code

// c++20 allows us to use auto for function parameter types, this creates a fucntion template rather than a ragular fucntion
// the decltype specifier is used to retrieve the type of a varible and is used when an explicit typename is not available
/*
auto pow_20(auto v, int n)
{
	auto product = decltype(v){1};
	for (int i = 0; i < n; ++i)
	{
		product *= v;
	}
	return product;
}
*/

// type_traits allow us to extract information about template types
// there are type traits that return information about a type as a boolean or an integer value, and there are type traits that return a new type (these are also called metafunctions)

// compile time type checking using type traits for fundamental types
auto same_type = std::is_same_v<uint8_t, unsigned char>;
auto is_float_or_double = std::is_floating_point_v<decltype(3.0f)>;

// type traits can also be used on user defined types:
class Planet{};

class Mars : public Planet{};

static_assert(std::is_base_of_v<Planet,Mars>);

// the second type of type traits returna new type and are useful when dealing with pointers and references
using value_type = std::remove_pointer_t<int*>;  // returns int
using ptr_type = std::add_pointer_t<float>; // returns float*

// all type traits are evaluated at compile time

// an expression prefixed with constexpr keyword tells the compiler that the expression should be evaluated at compile time
constexpr auto v = 42 + 17;  /// constant expression
// constexpr can also be used with functions, it tells the compiler that a certain function is intended to be evaluated at compie time if all the conditions allowing for compile-time evaluation are fulfilled, otherwise it executes at runtime
// constexpr functions cannot handle local static variables, handle thread_local variables and cannot call any function which is not a constexpr function

constexpr auto sum(int a, int b, int c) { return a + b + c; };

// if constexpr functions contain values that are not known at compile time, the execution will be just like a regular function

// therefore, an immediate function can be called at runtime or compile time
// if we want to limit the uses of a function so its only invoked at compile time, we can do that with the consteval keyword CPP20

consteval auto sum_compile(int x, int y, int z) { return x + y + z; };

/* A function that is declared using consteval is called an immediate function and can only produce constants.If we want to call sum(), we need to call it from within a constant expression, or the compilation will fail */

// if constexpr statement allows template functions to evaluate different scopes in the same function at compile time, this is compile time polymorphism
// this allows us to ignore scopes if the if statement is false, which can help the compiler avoid failing

struct Bear { auto roar() const { std::cout << "roar\n"; } };
struct Duck { auto quack() const { std::cout << "quack\n"; } };

/*  template <typename Animal> 
auto speak(const Animal& a) { 
 if (std::is_same_v<Animal, Bear>) { a.roar(); } 
 else if (std::is_same_v<Animal, Duck>) { a.quack(); } 
}

Let's say we compile the following lines:
auto bear = Bear{};
speak(bear);
The compiler will then generate a speak() function, similar to this:
auto speak(const Bear& a) {
 if (true) { a.roar(); }
 else if (false) { a.quack(); } // This line will not compile
}
As you can see, the compiler will keep the call to the member function, quack(), 
which will then fail to compile since Bear does not contain a quack() member 
function. This happens even though the quack() member function will never be 
executed due to the else if (false) statement.
In order to make the speak() function compile, regardless of the type, we need to 
inform the compiler that we'd like to completely ignore the scope if the if statement 
is false. Conveniently, this is exactly what if constexpr does.*/

template <typename Animal>
auto speak(const Animal a)
{
	if constexpr (std::is_same_v<Animal, Bear>) { a.roar(); };
	else if constexpr (std::is_same_v<Animal, Duck>) { a.quack(); };
}

/*
When speak() is invoked with Animal == Bear, as follows:
auto bear = Bear{};
speak(bear);
the compiler generates the following function:
auto speak(const Bear& animal) { animal.roar(); }
When speak() is invoked with Animal == Duck, as follows:
auto duck = Duck{};
speak(duck);
the compiler generates the following function:
auto speak(const Duck& animal) { animal.quack(); }

If speak() is invoked with any other primitive type, such as Animal == int, as
follows:
speak(42);
the compiler generates an empty function:
auto speak(const int& animal) {}
*/

// static assert will refuse to compile if the condition is not fulfilled

/*
template <int N, typename T>
auto const_pow_n(const T& v) {
 static_assert(N >= 0, "N must be positive");
 auto product = T{1};
 for (int i = 0; i < N; ++i) {
 product *= v;
 }
 return product;
}
auto x = const_pow_n<5>(2); // Compiles, N is positive
auto y = const_pow_n<-1>(2); // Does not compile, N is negative
*/

// c++ containers are homogenous, they can only store elements of one single type
// heterogenous collections contain elements of different types

// std::optional represents a wrapper for a any type where the wrapped type can be either initialised or uninitialised
// std::optional helps define functions that may not return a defined value
// the object held by a std::optional is always stack allocated and the memory overhead for wrapping a type into a std::optional is the size of a bool (1 byte) plus padding

// pair and tuple are fixed size and are heterogenous, you cannot add values dynamically at runtime

std::pair<int, int> dub{ 1,2 };

// std::tuple can be used as a foxed size heterogenous collection that can be declared to be of any size
// unlike vector, its size cannot change at runtime, you cannot add or remove elements

auto t = std::tuple{ 0,std::string{},false };

/* 
This will make the compiler generate a class, which can roughly be viewed like this:
struct Tuple {
 int data0_{};
 std::string data1_{};
 bool data2_{};
};
*/

// there's also a make_pair and make_tuple function, although from c++17 they arent necessary due to template type deduction
// you access the element using std::get<index>

// std::tuple is basically a simple struct whose members can be accesed by compile-time-index

// because they contain different types, we cant iterate through tuples like we can with homogenous data structures


/*  When we write and run a program, it would be reasonable to assume that the 
instructions in the source code will be executed in the same order as they appear in 
the source code. This is not true. The code we write will be optimized in multiple 
stages before it is finally executed. Both the compiler and the hardware will reorder 
instructions with the goal of executing the program more efficiently. This is not 
new technology: compilers have done this for a long time, and this is one reason 
why an optimized build runs faster than a non-optimized build. The compiler (and 
hardware) are free to reorder instructions as long as the reordering is not observable 
when running the program. The program runs as if everything happens in program 
order.

When protecting a critical section with a mutex, it is guaranteed that only the thread
that currently owns the lock can execute the critical section. But, the mutex is also
creating memory fences around the critical section to inform the system that certain
re-orderings are not allowed at the critical section boundaries. When acquiring the
lock, an acquire fence is added, and when releasing the lock, a release fence is
added. The one-way fences ensure that no instructions can be moved out from the critical section

 When we use a shared
atomic variable in our program, it gives us two things:
• Protection against torn writes: The atomic variable is always updated
atomically so there is no way a reader can read a partially written value.
• Synchronization of memory by adding sufficient memory fences: This
prevents certain instruction re-orderings to guarantee a certain memory
order specified by the atomic operations.
The C++ memory model guarantees sequential consistency if our program is free
from data races and we use the default memory order when using atomics. So, what
is sequential consistency? Sequential consistency guarantees that the result of the
execution is the same as if the operations were executed in the order specified by the
original program. The interleaving of instructions among threads is arbitrary; that is,
we have no control over the scheduling of the threads. This may sound complicated
at first, but it is probably the way you already think about how a concurrent program
is executed.
The downside with sequential consistency is that it can hurt performance. It is,
therefore, possible to use atomics with a relaxed memory model instead. This means
that you only get the protection against torn writes, but not the memory order
guarantees provided by sequential consistency.

Avoid contention
Whenever multiple threads are using shared data, there will be contention.
Contention hurts performance and sometimes the overhead caused by contention
can make a parallel algorithm work slower than a single-threaded alternative.
Using a lock that causes a wait and a context switch is an obvious performance
penalty, but what is not equally obvious is that both locks and atomics disable
optimizations in the code generated by the compiler, and they do so at runtime
when the CPU executes the code. This is necessary in order to guarantee sequential
consistency. But remember, the solution to such problems is never to ignore
synchronization and therefore introduce data races. Data races mean undefined
behavior, and having a fast but incorrect program makes nobody happy.
Instead, we need to minimize the time spent in critical sections. We can do that by
entering a critical section less often, and by minimizing the critical section itself so
that once we are in it, we leave it as soon as possible

Avoid blocking operations
To write a modern responsive UI application that always runs smoothly, it
is absolutely necessary to never block the main thread for more than a few
milliseconds. A smoothly running app updates its interface 60 times per second.
This means that if you are doing something that blocks the UI thread for more
than 16 ms, the FPS will drop.
You can design your internal APIs in an application with this in mind. Whenever
you write a function that performs I/O or something else that might take more than
a few milliseconds, it needs to be implemented as an asynchronous function. This
pattern has become very common in iOS and Windows, where, for example, all
network APIs have become asynchronous.

Number of threads/CPU cores
The more CPU cores a machine has, the more active running threads you can have.
If you manage to split a sequential CPU-bound task into a parallel version, you can
gain performance by having multiple cores working on the task in parallel.
Going from a single-threaded algorithm to an algorithm that can be run by two
threads can, in the best-case scenario, double the performance. But, after adding
more and more threads, you will eventually reach a limit when there is no more
performance gain. Adding more threads beyond that limit will actually degrade
performance since the overhead caused by context switching becomes more
significant the more threads you add.
I/O-intensive tasks, for example, a web crawler that will spend a lot of time waiting
for network data, require a lot of threads before reaching the limit where the CPU
is oversubscribed. A thread that is waiting for I/O will most likely be switched out
from the CPU to make room for other threads that are ready to execute. For CPUbound tasks, there is usually no point in using more threads than there are cores on
the machine.
Controlling the total number of threads in a big program can be hard. A good way
of controlling the number of threads is to use a thread pool that can be sized to match
the current hardware.

Thread priorities
The priority of a thread affects how the thread is scheduled. A thread with high
priority is likely to be scheduled more often than threads with lower priorities.
Thread priorities are important for lowering the latency of tasks.
Threads provided by the operating system usually have priorities. There is
currently no way of setting the priority on a thread with the current C++ thread
APIs. However, by using std::thread::native_handle, you can get a handle to the
underlying operating system thread and use native APIs to set priorities.
One phenomenon related to thread priorities that can hurt the performance, and
should be avoided, is called priority inversion. It happens when a thread with high
priority is waiting to acquire a lock that is currently held by a low-priority thread.
Such dependencies hurt the high-priority thread, which is blocked until the next time
the low-priority thread gets scheduled so that it can release the lock.

For real-time applications, this is a big problem. In practice, it means that you cannot
use locks to protect any shared resources that need to be accessed by real-time
threads. A thread that produces real-time audio, for example, runs with the highest
possible priority, and in order to avoid priority inversion, it is not possible for the
audio thread to call any functions (including std::malloc()) that might block and
cause a context switch

Thread affinity
Thread affinity makes it possible to give the scheduler hints about which threads
could benefit from sharing the same CPU caches. In other words, this is a request to
the scheduler that some threads should be executed on a particular core if possible,
to minimize cache misses.
Why would you want one thread to be executed on a particular core? The answer
is (again) caching. Threads that operate on the same memory could benefit from
running on the same core, and hence take advantage of warm caches. For the
scheduler, this is just one of many parameters to take into account when assigning
a thread to a core, so this is hardly any guarantee, but again, the behavior is very
different among operating systems. Thread priorities, and even utilization of all
cores (to avoid overheating), are one of the requirements that need to be taken into
account by a modern scheduler.
It is not possible to set thread affinity in a portable way with the current C++ APIs,
but most platforms support some way of setting an affinity mask on a thread. In
order to access platform-specific functionality, you need to get a handle on the native
thread.

False sharing
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

*/



int main()
{
	std::cout << pow<3>(3) << std::endl;  // compiler instantiates a distinct function called pow with 3 as the int

	// call the constexpr function 
	constexpr auto val = sum(1, 2, 3);  // since result of sum() is used in a constant expression and all its parameters can be determined at compile time, this calc is done at compile time
	// since val is constexpr this is guaranteed to execute at compile time. If we called sum() instead and stored the result in a variable that is not marked with constexpr, the compiler might(most likely) evaluate sum() a

	constexpr auto s = sum_compile(1, 2, 3);  // only works if we call it like this

	auto first = dub.first;

	auto second = std::get<2>(t);
}