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


The operands of the Boolean operators && and || are evaluated in the following way. If the
first operand of && is false, then the second operand is not evaluated at all because the
result is known to be false regardless of the value of the second operand. Likewise, if the
first operand of || is true, then the second operand is not evaluated, because the result is
known to be true anyway.

It may be advantageous to put the operand that is most often true last in an && expression,
or first in an || expression. Assume, for example, that a is true 50% of the time and b is
true 10% of the time. The expression a && b needs to evaluate b when a is true, which is
50% of the cases. The equivalent expression b && a needs to evaluate a only when b is
true, which is only 10% of the time. This is faster if a and b take the same time to evaluate
and are equally likely to be predicted by the branch prediction mechanism. 

If one operand is more predictable than the other, then put the most predictable operand
first.
If one operand is faster to calculate than the other then put the operand that is calculated
the fastest first.

Boolean variables are stored as 8-bit integers with the value 0 for false and 1 for true.
Boolean variables are overdetermined in the sense that all operators that have Boolean
variables as input check if the inputs have any other value than 0 or 1, but operators that
have Booleans as output can produce no other value than 0 or 1. This makes operations
with Boolean variables as input less efficient than necessary

. The Boolean operations can be made much more efficient if it
is known with certainty that the operands have no other values than 0 and 1. The reason
why the compiler does not make such an assumption is that the variables might have other
values if they are uninitialized or come from unknown sources. code can be
optimized if a and b have been initialized to valid values or if they come from operators that
produce Boolean output. The optimized code looks like this:

char a = 0, b = 0, c, d;
c = a & b;
d = a | b;
Here, I have used char (or int) instead of bool in order to make it possible to use the
bitwise operators (& and |) instead of the Boolean operators (&& and ||). The bitwise
operators are single instructions that take only one clock cycle. The OR operator (|) works
35
even if a and b have other values than 0 or 1. The AND operator (&) and the EXCLUSIVE
OR operator (^) may give inconsistent results if the operands have other values than 0 and
1.

pointers and references are equally efficient because they are in fact doing the same thing.

The advantages of using pointers rather than references are:

• it is clear that p is a pointer, but it is not
clear whether r is a reference or a simple variable. Using pointers makes it more clear
to the reader what is happening.
• It is possible to do things with pointers that are impossible with references. You can
change what a pointer points to and you can do arithmetic operations with pointers.
The advantages of using references rather than pointers are:
• The syntax is simpler when using references.
• References are safer to use than pointers because in most cases they are sure to point
to a valid address. Pointers can be invalid and cause fatal errors if they are uninitialized,
if pointer arithmetic calculations go outside the bounds of valid addresses, or if pointers
are type-casted to a wrong type.
• References are useful for copy constructors and overloaded operators.
• Function parameters that are declared as constant references accept expressions as
arguments while pointers and non-constant references require a variable.

Accessing a variable or object through a pointer or reference may be just as fast as
accessing it directly. The reason for this efficiency lies in the way microprocessors are
constructed. All non-static variables and objects declared inside a function are stored on the
stack and are in fact addressed relative to the stack pointer. Likewise, all non-static
variables and objects declared in a class are accessed through the implicit pointer known in
C++ as 'this'. We can therefore conclude that most variables in a well-structured C++
program are in fact accessed through pointers in one way or another. Therefore, microprocessors have to be designed so as to make pointers efficient, and that's what they are.
However, there are disadvantages of using pointers and references. Most importantly, it
requires an extra register to hold the value of the pointer or reference. Registers are a
scarce resource, especially in 32-bit mode. If there are not enough registers then the pointer
has to be loaded from memory each time it is used and this will make the program slower.
Another disadvantage is that the value of the pointer is needed a few clock cycles before
the time the variable pointed to can be accessed.

Calling a function through a function pointer may take a few clock cycles more than calling
the function directly if the target address can be predicted. The target address is predicted if
the value of the function pointer is the same as last time the statement was executed. The
target address will quite likely be mispredicted if the value of the function pointer changes.

A smart pointer is an object that behaves like a pointer. It has the special feature that the
object it points to is deleted when the pointer is deleted. Smart pointers are convenient for
objects stored in dynamically allocated memory, using new. The purpose of using smart
pointers is to make sure the object is deleted properly and the memory released when the
object is no longer used. A smart pointer may be regarded as a simple way to implement a
data container or a dynamically sized array without defining a container class.
The C++11 standard defines smart pointers as std::unique_ptr and
std::shared_ptr. std::unique_ptr has the feature that there is always one, and
only one pointer that owns the allocated object. Ownership is transferred from one
38
unique_ptr to another by assignment. shared_ptr allows multiple pointers to the same
object.
There is no extra cost to accessing an object through a smart pointer. Accessing an object
by *p or p->member is equally fast whether p is a simple pointer or a smart pointer. But
there is an extra cost whenever a smart pointer is created, deleted, copied, or transferred
from one function to another. These costs are higher for shared_ptr than for
unique_ptr.
The best optimizing compilers (Clang, Gnu) are able to peel off most or all of the overhead
for a unique_ptr in simple cases so that the compiled code contains just the calls to new
and delete.
Smart pointers can be useful in the situation where the logic structure of a program dictates
that an object must be dynamically created by one function and later deleted by another
function and these two functions are unrelated to each other (not member of the same
class). If the same function or class is responsible for creating and deleting the object then
you do not need a smart pointer.
If a program uses many small dynamically allocated objects with each their smart pointer
then you may consider if the cost of this solution is too high. It may be more efficient to pool
all the objects together into a single container, preferably with contiguous memory



*/

/* BRANCH PREDICTION

The high speed of modern microprocessors is obtained by using a pipeline where
instructions are fetched and decoded in several stages before they are executed. However,
the pipeline structure has one big problem. Whenever the code has a branch (e.g. an if-else
structure), the microprocessor does not know in advance which of the two branches to feed
into the pipeline. If the wrong branch is fed into the pipeline then the error is not detected
until 10 - 20 clock cycles later and the work it has done by fetching, decoding, and perhaps
speculatively executing instructions during this time has been wasted. The consequence is
that the microprocessor wastes several clock cycles whenever it feeds a branch into the
pipeline and later discovers that it has chosen the wrong branch.
Microprocessor designers have gone to great lengths to reduce this problem. 

The most important method that is used is branch prediction. Modern microprocessors are using
advanced algorithms to predict which way a branch will go based on the past history of that
branch and other nearby branches. The algorithms used for branch prediction are different
for each type of microprocessor.

Branches are relatively cheap if they are predicted most of the time, but expensive if they
are often mispredicted. A branch that always goes the same way is predicted well, of
course. A branch that goes one way most of the time and rarely the other way is
mispredicted only when it goes the other way. A branch that goes many times one way,
then many times the other way is mispredicted only when it changes. A branch that follows
a simple periodic pattern can also be predicted quite well if it is inside a loop with few or no
other branches. A simple periodic pattern can be, for example, to go one way two times and
the other way three times. Then again two times the first way and three times the other way,
etc. The worst case is a branch that goes randomly one way or the other with a 50-50
chance of going either way. Such a branch will be mispredicted 50% of the time.


A for-loop or while-loop is also a kind of branch. After each iteration it decides whether to
repeat or to exit the loop. The loop-branch is usually predicted well if the repeat count is
small and always the same. The maximum loop count that can be predicted perfectly varies
between 9 and 64, depending on the processor. Nested loops are predicted well only on
some processors. On many processors, a loop that contains several branches is not
predicted well.
A switch statements is a kind of branch that can go more than two ways. Switch statements
are most efficient if the case labels follow a sequence where each label is equal to the
preceding label plus one, because it can be implemented as a table of jump targets. A
switch statement with many labels that have values far from each other is inefficient
because the compiler must convert it to a branch tree.
On older processors, a switch statement with sequential labels is simply predicted to go the
same way as last time it was executed. It is therefore certain to be mispredicted whenever it
goes another way than last time. Newer processors are sometimes able to predict a switch
statement if it follows a simple periodic pattern or if it is correlated with preceding branches
and the number of different targets is small.
The number of branches and switch statements should preferably be kept small in the
critical part of a program, especially if the branches are poorly predictable. It may be useful
to roll out a loop if this can eliminate branches, as explained in the next paragraph.
The target of branches and function calls are saved in a special cache called the branch
target buffer. Contentions in the branch target buffer can occur if a program has many
branches or function calls. The consequence of such contentions is that branches can be
mispredicted even if they otherwise would be predicted well. Even direct function calls can
be mispredicted for this reason. A program with many branches and function calls in the
critical part of the code can therefore suffer from mispredictions.
In some cases it is possible to replace a poorly predictable branch by a table lookup. For
example:
// Example 7.29a
float a; bool b;
a = b ? 1.5f : 2.6f;
The ?: operator here is a branch. If it is poorly predictable then replace it by a table lookup:
// Example 7.29b
float a; bool b = 0;
const float lookup[2] = {2.6f, 1.5f};
a = lookup[b];
If a bool is used as an array index then it is important to make sure it is initialized or comes
from a reliable source so that it can have no other values than 0 or 1.

Generally, prefer switch statements to if else blocks as switches can be converted to jump tables, very efficient

The efficiency of a loop depends on how well the microprocessor can predict the loop
control branch.

. A loop with a small and fixed
repeat count and no branches inside can be predicted perfectly. As explained above, the
maximum loop count that can be predicted depends on the processor. Nested loops are
predicted well only on some processors that have a special loop predictor. On other
processors, only the innermost loop is predicted well. A loop with a high repeat count is
mispredicted only when it exits. For example, if a loop repeats a thousand times then the
loop control branch is mispredicted only one time in thousand so the misprediction penalty
is only a negligible contribution to the total execution time.

Function calls may slow down a program for the following reasons:
• The function call makes the microprocessor jump to a different code address and back
again. This may take up to 4 clock cycles. In most cases the microprocessor is able to
overlap the call and return operations with other calculations to save time.
• The code cache works less efficiently if the code is fragmented and scattered around in
memory.
48
• Function parameters are stored on the stack in 32-bit mode. Storing the parameters on
the stack and reading them again takes extra time. The delay is significant if a
parameter is part of a critical dependency chain.
• Extra time is needed for setting up a stack frame, saving and restoring registers, and
possibly save exception handling information.
• Each function call statement occupies a space in the branch target buffer (BTB).
Contentions in the BTB can cause branch mispredictions if the critical part of a program
has many calls and branches.

Some programming textbooks recommend that every function that is longer than a few lines
should be split up into multiple functions. I disagree with this rule. Splitting up a function into
multiple smaller functions only makes the program less efficient. Splitting up a function just
because it is long does not make the program more clear unless the function is doing
multiple logically distinct tasks. A critical innermost loop should preferably be kept entirely
inside one function, if possible.

An inline function is expanded like a macro so that each statement that calls the function is
replaced by the function body. A function is usually inlined if the inline keyword is used or
if its body is defined inside a class definition. Inlining a function is advantageous if the
function is small or if it is called only from one place in the program. Small functions are
often inlined automatically by the compiler. On the other hand, the compiler may in some
cases ignore a request for inlining a function if the inlining causes technical problems or
performance problems.

A function that calls other functions is called a frame function, while a function that does not
call any other function is called a leaf function. Leaf functions are more efficient than frame
functions. If the critical innermost loop of a program
contains calls to frame functions then the code can probably be improved by inlining the
frame function or by turning the frame function into a leaf function by inlining all the
functions that it calls.

A function that is used only within the same module (i.e. the current .cpp file) should be
made local. This makes it easier for the compiler to inline the function and to optimize
across function calls. There are three ways to make a function local:
1. Add the keyword static to the function declaration. This is the simplest method,
but it does not work with class member functions, where static has a different
meaning.
2. Put the function or class into an anonymous namespace.
3. The Gnu compiler allows "__attribute__((visibility("hidden")))".

Function parameters are transferred by value in most cases. This means that the value of
the parameter is copied to a local variable. This is efficient for simple types such as int,
float, double, bool, enum as well as pointers and references.
Arrays are always transferred as pointers unless they are wrapped into a class or structure.
The situation is more complex if the parameter has a composite type such as a structure or
class. The transfer of a parameter of composite type is most efficient if all of the following
conditions are met:
• the object is so small that it fits into a single register
• the object has no copy constructor and no destructor
• the object has no virtual member
• the object does not use runtime type identification (RTTI)
If any of these conditions is not met then it is usually faster to transfer a pointer or reference
to the object. If the object is large then it obviously takes time to copy the entire object. Any
copy constructor must be called when the object is copied to the parameter, and the
destructor, if any, must be called before the function returns.
The preferred method for transferring composite objects to a function is by a const
reference. A const reference makes sure that the original object is not modified. Unlike a
pointer or a non-const reference, a const reference allows the function argument to be an
expression or an anonymous object. The compiler can easily optimize away a const
reference if the function is inlined.
An alternative solution is to make the function a member of the object's class or structure.
This is equally efficient.
Simple function parameters are transferred on the stack in 32-bit systems, but in registers in
64-bit systems. The latter is more efficient. 64-bit Windows allows a maximum of four
parameters to be transferred in registers. 64-bit Unix systems allow up to fourteen
parameters to be transferred in registers (8 float or double plus 6 integer, pointer or
reference parameters). The this pointer in member functions counts a one parameter.


The return type of a function should preferably be a simple type, a pointer, a reference, or
void. Returning objects of a composite type is more complex and often inefficient.

Except for the simplest cases, composite objects are returned by copying them into a place
indicated by the caller through a hidden pointer. The copy constructor, if any, is usually
called in the copying process, and the destructor is called when the original is destroyed. In
simple cases, the compiler may be able to avoid the calls to the copy constructor and the
destructor by constructing the object on its final destination, but do not count on it.
Instead of returning a composite object, you may consider the following alternatives:
• Make the function a constructor for the object.
• Make the function modify an existing object rather than making a new one. The
existing object can be made available to the function through a pointer or reference,
or the function could be a member of the object's class.
• Make the function return a pointer or reference to a static object defined inside the
function. This is efficient, but risky. The returned pointer or reference is valid only
until the next time the function is called and the local object is overwritten, possibly in
a different thread. If you forget to make the local object static then it becomes invalid
as soon as the function returns.
• Make the function construct an object with new and return a pointer to it. This is
inefficient because of the costs of dynamic memory allocation. This method also
involves the risk of memory leaks if you forget to delete the object.


Recursive function calls can still be the most efficient solution for handling a branching data
tree structure. Recursion is more efficient if the tree structure is broad than if it is deep. A
non-branching recursion can always be replaced by a loop, which is more efficient.


OOP benefits for optimisation: 
• Variables that are used together are also stored together if they are members of the
same structure or class. This makes data caching more efficient.
• Variables that are members of a class need not be passed as parameters to a class
member function. The overhead of parameter transfer is avoided for these variables.

The negative effects of object oriented programming are:
• Some programmers are dividing the code into too many small classes. This is
inefficient.
• Non-static member functions have a 'this' pointer which is transferred as an implicit
parameter to the function. The overhead of parameter transfer for 'this' is incurred
on all non-static member functions.
• The 'this' pointer takes up one register. Registers are a scarce resource in 32-bit
systems.
• Virtual member functions are less efficient

You may use an object oriented programming style
if it is good for the logical structure and clarity of the program as long as you avoid an
excessive number of function calls in the most critical part of the program. The use of
structures (without member functions) has no negative effect on performance.

Each time a new object of a class is declared or created it will generate a new instance of
the data members. But each member function has only one instance. The function code is
not copied because the same code can be applied to all instances of the class.
Calling a member function is as fast as calling a simple function with a pointer or reference
to a structure. For example:
// Example 7.41
class S3 {
public:
int a;
int b;
int Sum1() {return a + b;}
};
int Sum2(S3 * p) {return p->a + p->b;}
int Sum3(S3 & r) {return r.a + r.b;}
The three functions Sum1, Sum2 and Sum3 are doing exactly the same thing and they are
equally efficient. If you look at the code generated by the compiler, you will notice that some
compilers will make exactly identical code for the three functions. Sum1 has an implicit
'this' pointer which does the same thing as p and r in Sum2 and Sum3. Whether you want
to make the function a member of the class or give it a pointer or reference to the class or
structure is simply a matter of programming style.

A static member function cannot access any non-static data members or non-static
member functions. A static member function is faster than a non-static member function
because it does not need the 'this' pointer. You may make member functions faster by
making them static if they do not need any non-static access.

Virtual functions are used for implementing polymorphic classes. Each instance of a
polymorphic class has a pointer to a table of pointers to the different versions of the virtual
functions. This so-called virtual table is used for finding the right version of the virtual
function at runtime. Polymorphism is one of the main reasons why object oriented programs
can be less efficient than non-object oriented programs. If you can avoid virtual functions
then you can obtain most of the advantages of object oriented programming without paying
the performance costs.
The time it takes to call a virtual member function is a few clock cycles more than it takes to
call a non-virtual member function, provided that the function call statement always calls the
same version of the virtual function. If the version changes then you may get a misprediction
penalty of 10 - 20 clock cycles. The rules for prediction and misprediction of virtual function
calls is the same as for switch statements, as explained on page 44.
The dispatching mechanism can be bypassed when the virtual function is called on an
object of known type, but you cannot always rely on the compiler bypassing the dispatch
mechanism even when it would be obvious to do so. See page 76.
Runtime polymorphism is needed only if it cannot be known at compile time which version
of a polymorphic member function is called. If virtual functions are used in a critical part of a
program then you may consider whether it is possible to obtain the desired functionality
without polymorphism or with compile-time polymorphism.
It is sometimes possible to obtain the desired polymorphism effect with templates instead of
virtual functions. The template parameter should be a class containing the functions that
have multiple versions. This method is faster because the template parameter is always
resolved at compile time rather than at runtime. Example 7.47 on page 59 shows an
example of how to do this. Unfortunately, the syntax is so kludgy that it may not be worth
the effort.

A union is a structure where data members share the same memory space. A union can be
used for saving memory space by allowing two data members that are never used at the
same time to share the same piece of memory.

Overloaded functions and Overloaded operators have no performance penalty

Threads are used for doing two or more jobs simultaneously or seemingly simultaneously.
Modern CPUs have multiple cores that makes it possible to run multiple threads
simultaneously. Each thread will get time slices of typically 30 ms for foreground jobs and
10 ms for background jobs when there are more threads than CPU cores. The context
switches after each time slice are quite costly because all caches have to adapt to the new
context. It is possible to reduce the number of context switches by making longer time
slices. This will make applications run faster at the cost of longer response times for user
input.

Threads are useful for assigning different priorities to different tasks. For example, in a word
processor the user expects an immediate response to pressing a key or moving the mouse.
This task must have a high priority. Other tasks such as spell-checking and repagination are
running in other threads with lower priority. If the different tasks were not divided into
threads with different priorities, then the user might experience unacceptably long response
times to keyboard and mouse inputs when the program is busy doing the spell checking.
Any task that takes a long time, such as heavy mathematical calculations, should be
scheduled in a separate thread if the application has a graphical user interface. Otherwise
the program will be unable to respond quickly to keyboard or mouse input.
It is possible to make a thread-like scheduling in an application program without invoking the
overhead of the operating system thread scheduler. This can be accomplished by doing the
heavy background calculations piece by piece in a function that is called from the message
loop of a graphical user interface (OnIdle in Windows MFC). This method may be faster
than making a separate thread in systems with few CPU cores, but it requires that the
background job can be divided into small pieces of a suitable duration.

The best way to fully utilize systems with multiple CPU cores is to divide the job into multiple
threads. Each thread can then run on its own CPU core.
There are four kinds of costs to multithreading that we have to take into account when
optimizing multithreaded applications:

• The cost of starting and stopping threads. Do not put a task into a separate thread if
it is short in duration compared with the time it takes to start and stop the thread.
• The cost of task switching. This cost is minimized if the number of threads with the
same priority is no more than the number of CPU cores.
• The cost of synchronizing and communicating between threads. The overhead of
semaphores, mutexes, etc. is considerable. If two threads are often waiting for each
other in order to get access to the same resource, then it may be better to join them
into one thread. A variable that is shared between multiple threads must be declared
volatile. This prevents the compiler from storing that variable in a register, which
is not shared between threads.
• The different threads need separate storage. No function or class that is used by
multiple threads should rely on static or global variables. (See thread-local storage p.
28) The threads have each their stack. This can cause cache contentions if the
threads share the same cache.
Multithreaded programs must use thread-safe functions. A thread-safe function should
never use static variables.



Exception handling is intended for detecting errors that seldom occur and recovering from
error conditions in a graceful way. You may think that exception handling takes no extra
time as long as the error does not occur, but unfortunately this is not always true. The
program may have to do a lot of bookkeeping in order to know how to recover in the event
of an exception. The costs of this bookkeeping depends very much on the compiler.



A cache is a proxy for the main memory in a computer. The proxy is smaller and closer to
the CPU than the main memory and therefore it is accessed much faster. There may be two
or three levels of cache for the sake of fastest possible access to the most used data.
The speed of the CPU is much faster than the speed of RAM memory. Efficient caching is
therefore quite important.

If a program contains many variables and objects that are scattered around in memory, then
there is a risk that several variables happen to be spaced by a multiple of the critical stride
and cause contentions in the data cache. The same can happen in the code cache if there
are many functions scattered around in program memory. If several functions that are used
in the same part of the program happen to be spaced by a multiple of the critical stride then
this can cause contentions in the code cache. The subsequent sections describe various
ways to avoid these problems.

The code cache works most efficiently if functions that are used near each other are also
stored near each other in the code memory. The functions are usually stored in the order in
which they appear in the source code. It is therefore a good idea to collect the functions that
are used in the most critical part of the code together near each other in the same source
file. Keep often used functions separate from seldom used functions, and put seldom used
branches such as error handling in the end of a function or in a separate function.
Sometimes, functions are kept in different source files for the sake of modularity. For
example, it may be convenient to have the member functions of a parent class in one
source file and the derived class in another source file. If the member functions of parent
class and derived class are called from the same critical part of the program then it can be
advantageous to keep the two modules contiguous in program memory. This can be done
by controlling the order in which the modules are linked together. The link order is usually
the order in which the modules appear in the project window or makefile. You can check the
order of functions in memory by requesting a map file from the linker. The map file tells the
address of each function relative to the beginning of the program. The map file includes the
addresses of library functions linked from static libraries (.lib or .a), but not dynamic
libraries (.dll or .so). There is no easy way to control the addresses of dynamically linked
library functions.

Cache misses are very expensive. A variable can be fetched from the cache in just a few
clock cycles, but it can take more than a hundred clock cycles to fetch the variable from
RAM memory if it is not in the cache.
The cache works most efficiently if pieces of data that are used together are stored near
each other in memory. Variables and objects should preferably be declared in the function
in which they are used. Such variables and objects will be stored on the stack, which is very
likely to be in the level-1 cache. The different kinds of variable storage are explained on
page 25. Avoid global and static variables if possible, and avoid dynamic memory allocation
(new and delete).
Object oriented programming can be an efficient way of keeping data together. Data
members of a class (also called properties) are always stored together in an object of the
class. Data members of a parent class and a derived class are stored together in an object
of the derived class

The order in which data are stored can be important if you have big data structures. For
example, if a program has two arrays, a and b, and the elements are accessed in the order
a[0], b[0], a[1], b[1], ... then you may improve the performance by organizing the data
as an array of structures:
// Example 9.1a
int Func(int);
const int size = 1024;
int a[size], b[size], i;
...
for (i = 0; i < size; i++) {
b[i] = Func(a[i]);
}
The data in this example can be accessed sequentially in memory if organized as follows:
// Example 9.1b
int Func(int);
const int size = 1024;
struct Sab {int a; int b;};
Sab ab[size];
int i;
...
for (i = 0; i < size; i++) {
ab[i].b = Func(ab[i].a);
}
There will be no extra overhead in the program code for making the structure in example
9.1b. On the contrary, the code becomes simpler because it needs only calculate element
addresses for one array rather than two.

A variable is accessed most efficiently if it is stored at a memory address which is divisible
by the size of the variable. For example, a double takes 8 bytes of storage space. It should
therefore preferably be stored at an address divisible by 8. The size should always be a
power of 2. Objects bigger than 16 bytes should be stored at an address divisible by 16.
You can generally assume that the compiler takes care of this alignment automatically.


Objects and arrays can be allocated dynamically with new and delete, or malloc and
free. This can be useful when the amount of memory required is not known at compile
time. Four typical uses of dynamic memory allocation can be mentioned here:
• A large array can be allocated dynamically when the size of the array is not known at
compile time.
• A variable number of objects can be allocated dynamically when the total number of
objects is not known at compile time.
• Text strings and similar objects of variable size can be allocated dynamically.
• Arrays that are too large for the stack can be allocated dynamically.
The advantages of dynamic memory allocation are:
• Gives a more clear program structure in some cases.
• Does not allocate more space than needed. This makes data caching more efficient
than when a fixed-size array is made very big in order to cover the worst case
situation of the maximum possible memory requirement.
• Useful when no reasonable upper limit to the required amount of memory space can
be given in advance.
The disadvantages of dynamic memory allocation are:
• The process of dynamic allocation and deallocation of memory takes much more
time than other kinds of storage. See page 25.
• The heap space becomes fragmented when objects of different sizes are allocated
and deallocated in random order. This makes data caching inefficient.
• An allocated array may need to be resized in the event that it becomes full. This may
require that a new bigger memory block is allocated and the entire contents copied
to the new block. Any pointers to data in the old block then become invalid.
• The heap manager will start garbage collection when the heap space has become
too fragmented. This garbage collection may start at unpredictable times and cause
delays in the program flow at inconvenient times when a user is waiting for
response.
• It is the responsibility of the programmer to make sure that everything that has been
allocated is also deallocated. Failure to do so will cause the heap to be filled up. This
is a common programming error known as memory leaks.
• It is the responsibility of the programmer to make sure that no object is accessed
after it has been deallocated. Failure to do so is also a common programming error.
• The allocated memory may not be optimally aligned. See page 133 for how to align
dynamically allocated memory.
• It is difficult for the compiler to optimize code that uses pointers because it cannot
rule out aliasing (see page 81).

• A matrix or multidimensional array is less efficient when the row length is not known
at compile time because of the extra work needed for calculating row addresses at
each access. The compiler may not be able to optimize this with induction variables.
It is important to weigh the advantages over the disadvantages when deciding whether to
use dynamic memory allocation. There is no reason to use dynamic memory allocation
when the size of an array or the number of objects is known at compile time or a reasonable
upper limit can be defined.
The cost of dynamic memory allocation is negligible when the number of allocations is
limited. Dynamic memory allocation can therefore be advantageous when a program has
one or a few arrays of variable size. The alternative solution of making the arrays very big to
cover the worst case situation is a waste of cache space. A situation where a program has
several large arrays and where the size of each array is a multiple of the critical stride (see
above, page 91) is likely to cause contentions in the data cache.


If the number of elements in an array grows during program execution, then it is preferable
to allocate the final array size right from the beginning rather than allocating more space
step by step. In most systems, you cannot increase the size of a memory block that has
already been allocated. If the final size cannot be predicted or if the prediction turns out to
be too small, then it is necessary to allocate a new bigger memory block and copy the
contents of the old memory block into the beginning of the new bigger memory block. This is
inefficient, of course, and causes the heap space to become fragmented. An alternative is to
keep multiple memory blocks, either in the form of a linked list or with an index of memory
blocks. A method with multiple memory blocks makes the access to individual array
elements more complicated and time consuming.
A collection of a variable number of objects is often implemented as a linked list. Each
element in a linked list has its own memory block and a pointer to the next block. A linked
list is less efficient than a linear array for the following reasons:
• Each object is allocated separately. The allocation, deallocation and garbage
collection takes a considerable amount of time.
• The objects are not stored contiguously in the memory. This makes data caching
less efficient.
• Extra memory space is used for the link pointers and for information stored by the
heap manager for each allocated block.
• Walking through a linked list takes more time than looping through a linear array. No
link pointer can be loaded until the previous link pointer has been loaded. This
makes a critical dependency chain which prevents out-of-order execution.



Whenever dynamic memory allocation is used, it is recommended to wrap the allocated
memory into a container class. The container class must have a destructor to make sure
everything that is allocated is also de-allocated. This is the best way to prevent memory
leaks and other common programming errors associated with dynamic memory allocation. A
simple alternative to a container class is to use a smart pointer, as explained on page 37.
Container classes can also be convenient for adding bounds-checking to an array and for
more advanced data structures with First-In-First-Out or Last-In-First-Out access, sort and
search facilities, binary trees, hash maps etc.
It is common to make container classes in the form of templates where the type of objects
they contain is provided as a template parameter. There is no performance cost to using
templates.
Ready-made container class templates are available in standard C++ libraries with the
C++11 and later standards. The advantage of using ready-made containers is that you do
not have to reinvent the wheel. The standard containers are universal, flexible, well tested,
and very useful for many different purposes.
But while the standard containers are designed for generality and flexibility, efficiency has
been sacrificed. Execution speed, memory economy, cache efficiency, and code size have
got low priority. Especially the memory allocation is unnecessarily wasteful in many
standard containers. Many container class templates are implemented as linked lists that
allocate one or more new memory blocks for every object in the container.


std::vector stores all the objects in one contiguous memory block, but this memory
block is re-allocated every time it is filled up, which happens quite often because the block
size grows by only 50% or less each time. An experiment where 10 elements were inserted,
one by one, into a std::vector turned up to cause seven memory allocations of sizes 1,
2, 3, 4, 6, 9 and 13 objects, respectively (MS Visual Studio 2019). This wasteful behavior
can be prevented by calling std::vector::reserve with a prediction or estimate of the
final size needed before adding the first object to the vector. Most other containers do not
have such a feature for reserving memory in advance.
The frequent allocation and de-allocation of memory with new and delete causes the
memory to become fragmented so that caching is very inefficient. There is a large overhead
cost to memory management and garbage collection, as mentioned above.
The generality of the standard containers also costs in terms of code size. In fact, the
standard library has been criticized for code bloat and complexity
(en.wikipedia.org/wiki/Standard_Template_Library). The objects stored in a standard
container are allowed to have constructors and destructors. The move constructors or copy
constructors and destructors of each object are called every time an object is moved, which
may happen quite often. This is necessary if the objects stored are containers themselves.
But implementing a matrix as a vector of vectors, as is often seen, is certainly a very
inefficient solution.
Many containers use linked lists. A linked list is a convenient way of making the container
expandable, but it is very inefficient. Linear arrays with contiguous memory are usually
much faster than linked lists.
The so-called iterators that are used in containers for accessing container elements are
cumbersome to use for many programmers and they are not necessary if you can use a
linear list with a simple index. A good compiler can optimize away the extra overhead of the
iterators in some cases, but not all.
Fortunately, there are more efficient alternatives that can be used where execution speed,
memory economy and small code size has higher priority than code generality. The most
important remedy is memory pooling. It is more efficient to store many objects together in
one big memory block than to store each object in its own allocated memory block. A large
block containing many objects can be copied or moved with a single call to memcpy rather
than moving each object separately if there are no move constructors, copy constructors, or
destructors that need to be called

The following considerations should be taken into account when choosing a container for a
specific purpose:
• Contain one or multiple elements? If the container is to hold only one element then
you should use local allocation or perhaps a smart pointer (see page 37).
• Is the size known at compile time? If the maximum number of elements is known at
compile time or a not-too-big upper limit can be set, then the optimal solution is a
fixed size array. Dynamic memory allocation may be needed, however, if the array or
container is too big for the stack.
99
• Is the size known before the first element is stored? If the total number of elements
to store is known before the first element is stored, or if a reasonable estimate or
upper limit can be made, then it is preferred to use a container such as
std::vector that allows you to reserve the amount of memory needed in advance
rather than allocating piecewise or re-allocating when a memory block turns out to
be too small.
• Is the size big or small? A big and complex solution may not be worth the trouble for
a small data structure, even if you need features for searching, adding, and
removing objects. Linear search in an unsorted array is certainly not the most
efficient algorithm, but it may still be the best solution if the array is small.
• Are objects numbered consecutively? If objects are identified by consecutive indices
or by keys within a limited range then a simple array is the most efficient solution.
• Is a multidimensional structure needed? A matrix or multidimensional array should
be stored in one contiguous memory block. Do not use one container for each row or
column. A nested container is certainly not the most efficient solution. The access is
faster if the number of elements per row is a constant known at compile time.
• Are objects accessed in a FIFO manner? If objects are accessed on a First-In-FirstOut (FIFO) basis then use a queue. It is much more efficient to implement a queue
as a circular buffer than as a linked list. See example 9.6 page 103.
• Are objects accessed in a LIFO manner? If objects are accessed on a Last-In-FirstOut (LIFO) basis then use a linear array with a top-of-stack index. See example 9.5
page 102.
• Are objects identified by a key? If the key values are confined to a limited range then
a simple array can be used. If the number of objects is high then the most efficient
solution may be a binary tree or a hash map.
• Do objects have a natural ordering? If you need to do searches of the kind: "what is
the nearest element to x?" or "how many elements are there between x and y?" then
you may use a sorted list or a binary tree.
• Is searching needed after all objects have been added? If search facilities are
needed, but only after all objects have been stored in the container, then a linear
array will be an efficient solution. Sort the array after all elements have been added.
Then use binary search for finding elements. A sorted list may still be useful if adding
objects is rare while searching is frequent, and the list is not too big. A hash map
may also be an efficient solution.
• Is searching needed before all objects have been added? If search facilities are
needed, and objects can be added or removed at any time, then the solution is more
complicated. If the total number of elements is small then a sorted list can still be the
most efficient solution because of its simplicity. But a sorted list can be very
inefficient if the list is large. The insertion of a new element in the list causes all
subsequent elements in the sequence to be moved. A binary tree or a hash map is
more efficient in this case. A binary tree may be used if elements have a natural
order and there are search requests for elements in a specific interval. A hash map
can be used if elements have no specific order but are identified by a unique key.
• Do objects have mixed types or sizes? It is possible to store objects of different
types or strings of different lengths in the same memory pool. See
www.agner.org/optimize/cppexamples.zip. If the number and types of elements is
known at compile time then there is no need to use a container or memory pool.
• Alignment? Some applications require that data are aligned at round addresses.
Especially the use of intrinsic vectors requires alignment to addresses divisible by
16, 32, or 64. Alignment of data structures to addresses divisible by the cache line
size (typically 64) can improve performance in some cases. C++98 and later
standards guarantee that allocated memory is correctly aligned for the object type
specified to the new operator.
• Multiple threads? Container classes are generally not thread safe if multiple threads
can add, remove, or modify objects simultaneously. It is more efficient to have
separate containers for each thread in multithreaded applications than to temporarily
lock a container for exclusive access by each thread.
• Pointers to contained objects? It may not be safe to make a pointer to an object
inside a container because the container may move the object in case memory reallocation is needed. Objects inside containers should be identified by their index or
key in the container rather than by pointers or references. It is OK, however, to pass
a pointer or reference to such an object to a function that does not add or remove
any objects if no other threads have access to the container.
• Can the container be recycled? There is a significant cost to creating and deleting
containers. It may be more efficient to re-use a container than to delete it and create
a new one, if the program logic allows it.


The standard C++ container class templates provide convenient and well-tested solutions to
common problems of organizing data structures. Unfortunately, these containers are quite
complicated and not always very efficient. Linked lists, in particular, are inefficient because
the data objects are stored in fragmented bits of memory with poor caching as a consequence. The code is bulky with a lot of overhead. A good optimizing compiler can peel off
much of the overhead, but the code is still difficult to understand and difficult to debug
because of the excessive complexity. The most common C++ container class templates are
listed here:
• std::array. This works like a simple array. The size is fixed at compile time.
There is no bounds checking.
• std::vector. This works like a linear array. The elements are stored in one
contiguous memory block. The size can grow. The growth is organized is such a way
that a new memory block (50% bigger) is allocated when the previous memory block
becomes too small. All data have to be moved to the new memory block every time it
is reallocated. It is important to use the reserve function with an estimate or upper
limit of the size needed before adding the first element. This will reduce the number
of reallocations. std::vector is the simplest and most efficient of the standard
containers with dynamic memory allocation.
• std::deque. This is a double-ended queue. It can be used both as a linear array
and as a queue where elements can be inserted and removed efficiently in both
ends. A deque may allocate fewer memory blocks than a linked list, because each
memory block can contain multiple elements if the elements are small. It allows
random access to any element in the list, just like an array. A deque provides a
useful compromise between a linear array and a linked list.
• std::forward_list. This is a linked list. A new memory block is allocated for
each element. The elements can only be accessed sequentially. The list can be
sorted, but sorting is not particularly efficient.
• std::list. This is a doubly linked list. Elements can be added and removed at
both ends. A list is similar to a forward_list, but the list can be traversed both
forwards and backwards.
• std:stack. This is a Last-In-First-Out (LIFO) list. It is a special case of deque.
• std::set. This is an ordered list. The objects are identified by their value and
ordered by their value. Objects can be added and removed in random order at any
time. Searching for objects is efficient. A set is implemented as a self-balancing
binary tree (red-black tree). This is useful if objects are added in random order and
searched for in random order.
• std::map. This is similar to std::set. The difference from std::set is that a map
contains key-value pairs. Objects are identified and ordered by their key while the
value contains other information related to the key.
• std::unordered_set. This can be used instead of std::set if the objects have no
natural order. It is implemented as a hash map. Objects can be added and removed
efficiently. Finding an object is efficient.
• std::unordered_map. This is similar to an unordered_set, but contains keyvalue pairs.



An efficient container class should allocate as few memory blocks as possible. Preferably,
all data should be stored in one contiguous memory block. Dynamic memory allocation is
necessary only if a reasonable maximum size is not known at compile time. The type of
objects that the container contains can be specified conveniently as a template parameter.
Remember to define a destructor to deallocate all allocated memory.

// Example 9.4
// Template for simple array with bounds checking
template <typename T> // T is the element type
class SafeArray {
protected:
T * p = 0; // pointer to array
int size = 0; // array size
public:
// Constructor
SafeArray(int n) { // n is the desired size
p = new T[n]; // allocate memory
if (p == 0) {
// .. error message here: memory allocation failed
}
size = n; // save size
}


// Return the size of the array
int getSize() const {
return size;
}
// [] array index operator
T & operator[] (int i) {
if ((unsigned int)i >= (unsigned int)size) {
// Index out of range
// .. error message here: index out of range
return p[0];
}
// No error
return p[i]; // Return reference to element
}
~SafeArray() { // destructor
if (p) delete[] p; // free the memory
}
};
// ...
// Example of use:
SafeArray<float> myArray(100);
for (int i = 0; i < 100; i++) {
myArray[i] = 0;
}
myArray[2] = 9;
Example 9.5 shows a Last-In-First-Out list (also called a stack) where a fixed maximum size
is specified as a template parameter. No dynamic memory allocation is needed.
// Example 9.5
// Template for Last-In-First-Out list
template <typename T, int maxsize>
class LIFOStack {
protected:
int n = 0; // Number of objects in list
T list[maxsize]; // Data buffer
public:
LIFOStack() { // Constructor
n = 0;
}
bool put(T const & x) { // Put object into list
if (n >= maxsize) {
return false; // Return false if list full
}
list[n] = x;
n++; // Increment count
return true; // Return true if success
}
T get() { // Get object from list
if (n <= 0) {
// Error: list empty
// Put error message here: list empty
return T(0);
} n
--; // Decrement count
return list[n]; // Return object
}
int getNum() const { // Tell number of objects in list
return n;
}


};
// ...
// Example of use:
LIFOStack<int, 100> myQ;
// put numbers in
for (int i = 0; i < 5; i++) {
myQ.put(i*10);
}
// get numbers out in reverse order
while (myQ.getNum() > 0) {
printf("\n%i ", myQ.get());
}
Example 9.6 shows a First-In-First-Out list (also called a queue) where a fixed maximum
size is specified as a template parameter. No dynamic memory allocation is needed. The list
is implemented as a circular buffer.
// Example 9.6
// Template for First-In-First-Out list
template <typename T, int maxsize>
class FIFOQueue {
protected:
T * head, * tail; // Pointers to current head and tail
int n; // Number of objects in list
T list[maxsize]; // Circular buffer
public:
FIFOQueue() { // Constructor
head = tail = list; // Initialize
n = 0;
}
bool put(T const & x) { // Put object into list
if (n >= maxsize) {
return false; // Return false if list full
}
n++; // Increment count
*head = x; // Copy x to list
head++; // Increment head pointer
if (head >= list + maxsize) {
head = list; // Wrap around
}
return true; // Return true if success
}
T get() { // Get object from list
if (n <= 0) {
// Put an error message here: list empty
return T(0); // return zero object if possible
} n
--; // Decrement count
T * p = tail; // Pointer to object
tail++; // Increment tail pointer
if (tail >= list + maxsize) {
tail = list; // Wrap around
}
return *p; // Return object
}
int getNum() const { // Tell number of objects in list
return n;
}
};
// ...


// Example of use:
FIFOQueue<int, 100> myQ;
// put numbers in
for (int i = 0; i < 5; i++) {
myQ.put(i*10);
}
// get numbers out in same order
while (myQ.getNum() > 0) {
printf("\n%i ", myQ.get());
}
The C++ standard does not currently define an efficient way of making a matrix with
dimensions determined at run time. Example 9.7 shows a possible solution:
// Example 9.7
// Template for a matrix. The dimensions are decided at run time
// This template makes a matrix of arbitrary dimensions
// There is no bounds checking
template <typename T>
class Matrix {
public:
// constructor with number of rows and columns
Matrix(int rows, int columns) {
// save number of rows and columns
this->rows = rows;
this->columns = columns;
// allocate memory
p = new T[rows * columns];
if (p == 0) {
// .. error message here: allocation failed
}
else {
// initialize all elements to zero
for (int i = 0; i < rows * columns; i++) {
p[i] = 0;
}
}
}
// get number of rows
int nrows() const {
return rows;
}
// get number of columns
int ncols() const {
return columns;
}
// destructor
~Matrix() {
if (p) delete[] p; // free the memory
}
// Operator [] gives a pointer to row number r.
// A second [] with the column number gives a single element
T * operator[] (int r) {
// no bounds check
return p + r * columns;
}
protected:
int rows; // number of rows
int columns; // number of columns
T * p; // pointer to memory
};


// ...
// Example of use:
// Make a matrix of doubles with 8 rows and 10 columns
Matrix<double> mat(8,10);
// Put a value in row 3, column 5
mat[3][5] = 12.34;
// Print out the matrix
for (int r = 0; r < mat.nrows(); r++) {
for (int c = 0; c < mat.ncols(); c++) {
printf("%5.2f ", mat[r][c]);
}


Text strings typically have variable lengths that are not known at compile time. The storage
of text strings in classes like string, or wstring is using new and delete to allocate a
new memory block every time a string is created or modified. This can be quite inefficient if
a program creates or modifies many strings.
In most cases, the fastest way to handle strings is the old fashioned C style with character
arrays. Strings can be manipulated with C functions such as strcpy, strcat, strlen,
sprintf, etc. But beware that these functions have no check for overflow of the arrays. An
array overflow can cause unpredictable errors elsewhere in the program that are very
difficult to diagnose. It is the responsibility of the programmer to make sure the arrays are
sufficiently large to handle the strings including the terminating zero and to make overflow
checks where necessary. Fast versions of common string functions as well as efficient
functions for string searching and parsing are provided in the asmlib library at
www.agner.org/optimize/asmlib.zip.



A cache works most efficiently when the data are accessed sequentially. It works somewhat
less efficiently when data are accessed backwards and much less efficiently when data are
accessed in a random manner. This applies to reading as well as writing data.
Multidimensional arrays should be accessed with the last index changing in the innermost
loop. This reflects the order in which the elements are stored in memory. Example:
// Example 9.8
const int NUMROWS = 100, NUMCOLUMNS = 100;
int matrix[NUMROWS][NUMCOLUMNS];
int row, column;
for (row = 0; row < NUMROWS; row++)
106
for (column = 0; column < NUMCOLUMNS; column++)
matrix[row][column] = row + column;
Do not swap the order of the two loops (except in Fortran where the storage order is
opposite).

*/



*/




int main() {




}
