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

// Upto point 7 of Optimised C++


*/




int main() {




}