# include <iostream>
# include <algorithm>
# include <vector>
# include <utility>
# include <string>
# include <tuple>

/* C++ containers are homogenous, meaning that they can only store elements of 
one single type. A std::vector<int> stores a collection of integers and all objects 
stored in a std::list<Boat> are of type Boat. But sometimes, we need to keep 
track of a collection of elements of different types. I will refer to these collections 
as heterogenous collections. In a heterogeneous collection, the elements may have 
different types 

Before the introduction of std::optional, there was no clear way to define functions
that may not return a defined value, such as the intersection point of two line
segments. With the introduction of std::optional, such optional return values can
be clearly expressed. 

The C++ Utility library includes two class templates that can be used for storing
multiple values of different types: std::pair and std::tuple. They are both
collections with a fixed size. Just like std::array, it's not possible to add more
values dynamically at runtime.
The big difference between std::pair and std::tuple is that std::pair can only
hold two values, whereas std::tuple can be instantiated with an arbitrary size at
compile time. We will begin with a brief introduction to std::pair before moving
on to std::tuple.



*/

std::pair<int, int> v = std::minmax({ 1,2,3,4,5 });  // pairs also allow us to store items of different types

// The std::tuple can be used as a fixed-size heterogeneous collection that can be 
// declared to be of any size.In contrast to std::vector, for example, its size cannot
// change at runtime; you cannot add or remove elements.

auto t = std::tuple<int, bool> (42, true);
auto t_1 = std::get<0>(t);  // you use get to return from a tuple

auto make_t_1() {return std::tuple<int, bool>(42, true);}
// for accessing multiple tuple elements we can use std::tie

/* Using structured bindings, multiple variables can be initialized at once using auto
and a bracket declaration list. As with the auto keyword in general, you can apply 
control over whether the variables should be mutable references, forward references, 
const references, or values by using the corresponding modifier.*/

// const auto& [int num, bool truth] = make_t_1();

/* Interpreted code is very inefficient because 
the body of a loop is interpreted again and again for every iteration of the loop.

Interpreted languages
are out of the question when efficiency is important. A language based on intermediate code
and just-in-time compilation may be a viable compromise when portability and ease of
development are more important than speed. This includes languages such as C#, Visual
Basic .NET and the best Java implementations. However, these languages have the
disadvantage of a very large runtime framework that must be loaded every time the program
is run. The time it takes to load the framework and compile the program are often much
more than the time it takes to execute the program. The runtime framework may use more
resources than the program itself when running. Programs using such a framework
sometimes have unacceptably long response times for simple tasks like pressing a button
or moving the mouse. The .NET framework should definitely be avoided when speed is
critical.
The fastest execution is no doubt obtained with a fully compiled code. Compiled languages
include C, C++

Accessing data from RAM memory can take quite a long time compared to the time it takes
to do calculations on the data. This is the reason why all modern computers have memory
caches. Typically, there is a level-1 data cache of 8 - 64 Kbytes and a level-2 cache of 256
Kbytes to 2 Mbytes. Often, there is also a level-3 cache of several Mbytes.
If the combined size of all data in a program is bigger than the level-2 cache and the data
are scattered around in memory or accessed in a non-sequential manner then it is likely that
memory access is the biggest time-consumer in the program. Reading or writing to a
variable in memory takes only 2-4 clock cycles if it is cached, but several hundred clock
cycles if it is not cached.

A context switch is a switch between different tasks in a multitasking environment, between
different threads in a multithreaded program, or between different parts of a big program.
Frequent context switches can reduce the performance because the contents of data cache,
code cache, branch target buffer, branch pattern history, etc. may have to be renewed.
Context switches are more frequent if the time slices allocated to each task or thread are
smaller. The lengths of the time slices is determined by the operating system, not by the
application program.
The number of context switches is smaller in a computer with multiple CPUs or a CPU with
multiple cores

Modern microprocessors can do out-of-order execution. This means that if a piece of
software specifies the calculation of A and then B, and the calculation of A is slow, then the
microprocessor can begin the calculation of B before the calculation of A is finished.
Obviously, this is only possible if the value of A is not needed for the calculation of B.
In order to take advantage of out-of-order execution, you have to avoid long dependency
chains. A dependency chain is a series of calculations, where each calculation depends on
the result of the preceding one. This prevents the CPU from doing multiple calculations
simultaneously or out of order.

The execution core of modern microprocessors is split between several execution units.
Typically, there are two or more integer units, one or two floating point addition units, and
one or two floating point multiplication units. This means that it is possible to do an integer
addition, a floating point addition, and a floating point multiplication at the same time.
A code that does floating point calculations should therefore preferably have a balanced mix
of additions and multiplications. Subtractions use the same unit as additions. Divisions take
longer time. It is possible to do integer operations in-between the floating point operations
without reducing the performance because the integer operations use different execution
units. For example, a loop that does floating point calculations will typically use integer
operations for incrementing a loop counter, comparing the loop counter with its limit, etc. In
most cases, you can assume that these integer operations do not add to the total
computation time.

The first thing to do when you want to optimize a piece of CPU-intensive software is to find
the best algorithm. The choice of algorithm is very important for tasks such as sorting,
searching, and mathematical calculations. In such cases, you can obtain much more by
choosing the best algorithm than by optimizing the first algorithm that comes to mind. In
some cases you may have to test several different algorithms in order to find the one that
works best on a typical set of test data.
That being said, I must warn against overkill. Do not use an advanced and complicated
algorithm if a simple algorithm can do the job fast enough. For example, some programmers
use a hash table for even the smallest list of data. A hash table can improve search times
dramatically for very large databases, but there is no reason to use it for lists that are so
small that a binary search, or even a linear search, is fast enough. A hash table increases
the size of the program as well as the size of data files. This can actually reduce speed if
the bottleneck is file access or cache access rather than CPU time. Another disadvantage of
complicated algorithms is that it makes program development more expensive and more
error prone.

In C++, double precision calculations are just as fast as single precision, and template classes are MORE efficient than polumorphous classes

/* Variables and objects are stored in different parts of the memory, depending on how they
are declared in a C++ program. This has influence on the efficiency of the data cache. Data caching is poor if data are scattered randomly around in the memory. It is
therefore important to understand how variables are stored

Variables and objects declared inside a function are stored on the stack (generally)

Every time a function is called, it allocates the required amount of space on
the stack for all these purposes. This memory space is freed when the function returns. The
next time a function is called, it can use the same space for the parameters of the new
function.

The stack is the most efficient memory space to store data in because the same range of
memory addresses is reused again and again. It is almost certain that this part of the
memory is mirrored in the level-1 data cache if there are no big arrays.

The lesson we can learn from this is that all variables and objects should preferably be
declared inside the function in which they are used.

Variables that are declared outside of any function are called global variables. They can be
accessed from any function. Global variables are stored in a static part of the memory. The
static memory is also used for variables declared with the static keyword, for floating
point constants, string constants, array initializer lists, switch statement jump tables, and
virtual function tables.

The advantage of static data is that it can be initialized to desired values before the program
starts. The disadvantage is that the memory space is occupied throughout the whole
program execution, even if the variable is only used in a small part of the program. This
makes data caching less efficient because the memory space cannot be reused for another
purpose.

Do not make variables global if you can avoid it. Global variables may be needed for
communication between different threads, but that is about the only situation where they are
unavoidable. It may be useful to make a variable global if it is accessed by several different
functions and you want to avoid the overhead of transferring the variable as function
parameter. But it may be a better solution to make the functions that access the saved
variable members of the same class and store the shared variable inside the class. 
*/

// it is preferable to declare a lookup table static and constant
float someFunc(int x) {
	static const float list[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
	return list[x];
}
// due to be being static and const, the list does not need to be initialised every time the function is called
// The static declaration helps the compiler decide that the table can be reused from one call to the next. The const declaration helps the compiler see that the table never changes.
// A static declaration on an initialized variable inside a function means that the variable has to be initialized the first time the function is called, but not on subsequent calls.
// This is inefficient because the function needs extra overhead to check whether it called for the first time or it has been called before. 
// The const declaration helps the compiler decide that the check for first call is not needed. 
// Some compilers are able to optimize the lookup table anyway, but it is best to put both static and const on lookup tables in order to optimize performance on all compilers

// string constants and floating point constants are also often stored in static memory
/*
a = b * 3.5;
c = d + 3.5;
Here, the constant 3.5 will be stored in static memory. Most compilers will recognize that
the two constants are identical so that only one constant needs to be stored. All identical
constants in the entire program will be joined together in order to minimize the amount of
cache space used for constants.
Integer constants are usually included as part of the instruction code. You can assume that
there are no caching problems for integer constants.*/

/* 

A limited number of variables can be stored in registers instead of main memory. A register
is a small piece of memory inside the CPU used for temporary storage. Variables that are
stored in registers are accessed very fast. All optimizing compilers will automatically choose
the most often used variables in a function for register storage. The same register can be
used for multiple variables as long as their uses (live ranges) do not overlap.

Local variables are particularly suited for register storage. This is another reason for
preferring local variables.
The number of registers is limited. There are approximately six integer registers available for
general purposes in 32-bit x86 operating systems and fourteen integer registers in 64-bit
systems.

Floating point variables use a different kind of registers. There are eight floating point
registers available in 32-bit operating systems, sixteen in 64-bit operating systems, and
thirty two when the AVX512 instruction set is enabled in 64-bit mode. Some compilers have
difficulties making floating point register variables in 32-bit mode unless the SSE instruction
set (or higher) is enabled.

The volatile keyword specifies that a variable can be changed by another thread. This
prevents the compiler from making optimizations that rely on the assumption that the
variable always has the value it was assigned previously in the code. Example:
// Example 7.3. Explain volatile

volatile int seconds; // incremented every second by another thread
void DelayFiveSeconds() {
seconds = 0;
while (seconds < 5) {
// do nothing while seconds count to 5
}
}

In this example, the DelayFiveSeconds function will wait until seconds has been
incremented to 5 by another thread. If seconds was not declared volatile then an
optimizing compiler would assume that seconds remains zero in the while loop because
nothing inside the loop can change the value. The loop would be while (0 < 5) {}
which would be an infinite loop.
The effect of the keyword volatile is that it makes sure the variable is stored in memory
rather than in a register and prevents all optimizations on the variable. This can be useful in
test situations to avoid that some expression is optimized away.
Note that volatile does not mean atomic. It will not prevent two threads from attempting
to write the variable at the same time. The code in the above example may fail in the event
that it attempts to set seconds to zero at the same time as the other thread increments
seconds. A safer implementation would only read the value of seconds and wait until the
value has changed five times.

Most compilers can make thread-local storage of static and global variables by using the
keyword thread_local, __thread or __declspec(thread). Such variables have
one instance for each thread. Thread-local storage is inefficient because it is accessed
through a pointer stored in a thread environment block. Static thread-local storage should
be avoided, if possible, and replaced by storage on the thread's own stack. Non-static variables and objects that are declared in the thread function, or in any
function called by the thread function, will be stored on the thread's stack. These variables
and objects will have a separate instance for each thread. The need for static thread-local
storage can be avoided in most cases by declaring the variables or objects inside the thread
function.

Dynamic memory allocation is done with the operators new and delete or with the
functions malloc and free. These operators and functions consume a significant amount
of time. A part of memory called the heap is reserved for dynamic allocation. The heap can
easily become fragmented when objects of different sizes are allocated and deallocated in
random order. The heap manager can spend a lot of time cleaning up spaces that are no
longer used and searching for vacant spaces. This is called garbage collection. Objects that
are allocated in sequence are not necessarily stored sequentially in memory. They may be
scattered around at different places when the heap has become fragmented. This makes
data caching inefficient.
Dynamic memory allocation also tends to make the code more complicated and error-prone.
The program has to keep pointers to all allocated objects and keep track of when they are
no longer used. It is important that all allocated objects are also deallocated in all possible
cases of program flow. Failure to do so is a common source of error known as memory leak.
An even worse kind of error is to access an object after it has been deallocated. The
program logic may need extra overhead to prevent such errors.

Some programming languages, such as Java, use dynamic memory allocation for all
objects. This is of course inefficient.


Variables declared inside a class are stored in the order in which they appear in the class
declaration. The type of storage is determined when the object of the class is declared. An
object of a class, structure, or union can use any of the storage methods mentioned above.
An object cannot be stored in a register except in the simplest cases, but its data members
can be copied into registers.

A class member variable with the static modifier will be stored in static memory and will
have one and only one instance. Non-static members of the same class will be stored with
each instance of the class.

Storing variables in a class or structure is a good way of making sure that variables that are
used in the same part of the program are also stored near each oher

The compiler will always select the most efficient integer size if you declare an int, without
specifying the size. Integers of smaller sizes (char, short int) are only slightly less
efficient. In many cases, the compiler will convert these types to integers of the default size
when doing calculations, and then use only the lower 8 or 16 bits of the result. You can
assume that the type conversion takes zero or one clock cycle.

The unsigned integer type size_t is 32 bits in 32-bit systems and 64 bits in 64-bit systems.
It is intended for array sizes and array indices when you want to make sure that overflow
never occurs, even for arrays bigger than 2 GB.

In most cases, there is no difference in speed between using signed and unsigned integers.
But there are a few cases where it matters:
• Division by a constant: Unsigned is faster than signed when you divide an integer with a
constant. This also applies to the modulo operator %.
• Conversion to floating point is faster with signed than with unsigned integers for most
instruction sets.
• Overflow behaves differently on signed and unsigned variables. An overflow of an
unsigned variable produces a low positive result. An overflow of a signed variable is
officially undefined. The normal behavior is wrap-around of positive overflow to a
negative value, but the compiler may optimize away branches that depend on overflow,
based on the assumption that overflow does not occur.
The conversion between signed and unsigned integers is costless. It is simply a matter of
interpreting the same bits differently. A negative integer will be interpreted as a very large
positive number when converted to unsigned.

Integer operations are generally very fast. Simple integer operations such as addition,
subtraction, comparison, bit operations and shift operations take only one clock cycle on
most microprocessors.
Multiplication and division take longer time. Integer multiplication takes 11 clock cycles on
Pentium 4 processors, and 3 - 4 clock cycles on most other microprocessors. Integer
division takes 40 - 80 clock cycles, depending on the microprocessor.


The pre-increment operator ++i and the post-increment operator i++ are as fast as
additions. When used simply to increment an integer variable, it makes no difference
whether you use pre-increment or post-increment. The effect is simply identical. For
example,
for (i=0; i<n; i++) is the same as for (i=0; i<n; ++i). But when the result of
the expression is used, then there may be a difference in efficiency. For example,
x = array[i++] is more efficient than x = array[++i] because in the latter case,
the calculation of the address of the array element has to wait for the new value of i which
will delay the availability of x for approximately two clock cycles. Obviously, the initial value
of i must be adjusted if you change pre-increment to post-increment.
There are also situations where pre-increment is more efficient than post-increment. For
example, in the case a = ++b; the compiler will recognize that the values of a and b are
the same after this statement so that it can use the same register for both, while the
expression a = b++; will make the values of a and b different so that they cannot use the
same register.
Everything that is said here about increment operators also applies to decrement operators
on integer variables.

An enum is simply an integer in disguise. Enums are exactly as efficient as integers.
Note that the enumerators (value names) will clash with any variable or function having the
same name. Enums in header files should therefore have long and unique enumerator
names or be put into a namespace.


Upto page 33

*/




int main() {




}
