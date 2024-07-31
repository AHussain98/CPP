/*
c++ notes
:: -> scope resolution operator
std::string -> this is a string object that belongs to the std namespace
Namespaces are used to group classes and variables, to avoid naming conflicts with other classes/variables that may share the same name
Bring in the namespace you want to use with the using keyword at the top of your code
*/
namespace asad{
int age;	
};
/* namespace created above , namespaces are useful to group things of common functionality, or group categories of different things together, or for avoiding name clashes mentioned earlier
*/
asad::age; //this is how we would call the int variable defined in the asad namespace

/*
A class is like a blueprint of an object. It is a user-defined data type with data members and member functions and is defined with the keyword class.
You define objects as an instance of a class. Once it creates the object, then it can operate on both data members and member functions.

Access modifiers used to define accessibility for the class members: Private, Public, Protected
Public: All member functions and data members are accessible outside the class.
Protected: All member functions and data members are accessible within the class and to the derived class.
Private: All member functions and data members cannot be accessed outside the class.

While loop only iterates loop if the condition is true, do-while loop first iterates the body once then checks the condition

int is 4 bytes

size and length functions used to return the number of characters in a string

In prefix (++i), first, it increments the value, and then it assigns the value to the expression.

In postfix (i++), it assigns the value to the expression, and then it increments the variable's value.

you can compile a program without the main function, but you cannot run or execute the program because the main() function is the entry point, from where all the execution begins.

4 Data types:
Primitive/Basic: Char, int, short, float, double, long, bool, etc.
Derived: Array, pointer, etc.
Enumeration: Enum
User-defined: Structure, class, etc.

Struct is different from a class because its members are public by default, and the default access specifiers are public when deriving a struct from a class/struct. You can't interit from a struct.

A member function in the base class redefined in a derived class is a virtual function. It is declared using the virtual keyword. It ensures that the correct function is called for an object, irrespective of the type of reference/pointer used for the function call. Virtual functions are mainly used for runtime polymorphism.

Like a friend function, a friend class can access personal and guarded variables of the type in which it is declared. All member functions for classes specified as friends to another class are friend functions for the friend class.

An abstract class is a class whose objects cannot be created. It serves as a parent for the derived classes. Placing a pure virtual function in the class makes it an abstract class.

A variable in a class declared as static has its space allocated for the lifetime of the program. Regardless of the number of objects of that class created, there is only a single copy of the static member. The same static member is accessible to all the objects of that class.

A static member function can be called even if no class objects exist. It is accessed using only the class name and the scope resolution operator (::).

You use the void() return type when you don’t want to return any value. It specifies that the function doesn’t return a value. A function with a void return type completes its task and then returns the control to the caller.

You can define a friend function as a function that can access private, public and protect members of the class. You declare the friend function with the help of the friend keyword. You declare this function inside the class.

Structures (also called structs) are a way to group several related variables into one place. Each variable in the structure is known as a member of the structure.

Unlike an array, a structure can contain many different data types (int, string, bool, etc.).

To create a structure, use the struct keyword and declare each of its members inside curly braces. After the declaration, specify the name of the structure variable. Structs are instantiated same as classes

 getline() function in C++. This is an inbuilt function that accepts single and multiple character inputs. cin is the first parameter in the getline function -> getline(cin, "my name is asad")

 '\0' is not required if you are using it as character array. But if you use character array as string, you need to put '\0'. This allows to find the point where a string ends.

 Symbol Table is an important data structure created and maintained by the compiler in order to keep track of semantics of variables i.e. it stores information about the scope and binding information about names, information about instances of various entities such as variable and function names, classes, objects, etc.

 The dot and arrow operator are both used in C++ to access the members of a class. They are just used in different scenarios. In C++, types declared as class, struct, or union are considered "of class type". So the following refers to all three of them.

a.b is only used if b is a member of the object (or reference[1] to an object) a. So for a.b, a will always be an actual object (or a reference to an object) of a class.
a→b is essentially a shorthand notation for (*a).b, ie, if a is a pointer to an object, then a→b is accessing the property b of the object that a points to.

 The auto keyword is a simple way to declare a variable that has a complicated type. For example, you can use auto to declare a variable where the initialization expression involves templates, pointers to functions, or pointers to members.

 Loop is more efficient for factorials. When you do recursion, you have up to x function calls on the stack.

You almost never use recursion for performance reasons. You use recursion to make the problem more simple.

 References are often confused with pointers but three major differences between references and pointers are −

You cannot have NULL references. You must always be able to assume that a reference is connected to a legitimate piece of storage.

Once a reference is initialized to an object, it cannot be changed to refer to another object. Pointers can be pointed to another object at any time.

A reference must be initialized when it is created. Pointers can be initialized at any time.

Think of a variable name as a label attached to the variable's location in memory. You can then think of a reference as a second label attached to that memory location. Therefore, you can access the contents of the variable through either the original variable name or the reference. For example, suppose we have the following example −

int i = 17;
We can declare reference variables for i as follows.

int& r = i;

Buffer is a basic term that denotes a computer memory block that acts as a temporary placeholder. Buffer term is used in almost all fields like video streaming, RAM, etc. In the programming part, a software buffer is a place where data can be kept before it starts processing. It is done in order to make the process faster.
 That is, normally if data write using direct operation, it takes time. In the case of buffer, it is performed in a fast manner.

 “Heap” memory, also known as “dynamic” memory, is an alternative to local stack memory. Local memory is quite automatic. Local variables are allocated automatically when a function is called, and they are deallocated automatically when the function exits.
  Heap memory is different in every way. The programmer explicitly requests that space be allocated, using the new operator in Java or C++.
  This memory “block” will be of a particular size, ususally determined automatically from the size of the object being created.
  That memory block (your object) continues to be allocated until something happens that makes it go away.
   In some languages (noteably, C and C++), an object in heap memory only goes away when the programmer explicitly requests that it be deallocated.
   So the programmer has much greater control of memory, but with greater responsibility since the memory must now be actively managed.
   Dropping all references to a memory location without deallocating it is a signficant source of errors in C/C++, and this is so common that it has a name: memory leak.
   (In fact, many commercial programs implemented in C++ have memory leaks, that will eventually make them crash after being used for a long time.)
 Java removes this source of errors by handling memory deallocation automatically, using garbage collection. The downside is that garbage collection is a slow process that happens at unpredictable times.

 Function Overloading (achieved at compile time) provides multiple definitions of the function by changing signature i.e changing number of parameters, change datatype of parameters, return type doesn’t play anyrole.

 Function Overriding (achieved at run time) It is the redefinition of base class function in its derived class with same signature i.e return type and parameters.

 C/C++ IO are based on streams, which are sequence of bytes flowing in and out of the programs (just like water and oil flowing through a pipe).
 In input operations, data bytes flow from an input source (such as keyboard, file, network or another program) into the program. In output operations, data bytes flow from the program to an output sink (such as console, file, network or another program).
 Streams acts as an intermediaries between the programs and the actual IO devices, in such the way that frees the programmers from handling the actual devices, so as to archive device independent IO operations.
 C++ IO is provided in headers <iostream> (which included <ios>, <istream>, <ostream> and <streambuf>), <fstream> (for file IO), and <sstream> (for string IO). Furthermore, the header <iomanip> provided manipulators such as setw(), setprecision()setfill() and setbase() for formatting.
 << is stream insertion operator, used to print data
 >> is stream extraction operator, used to take in data

 the difference between 32-bit and a 64-bit is all about processing power. Computers with 32-bit processors are older, slower, and less secure, while a 64-bit processor is newer, faster, and more secure.


 c++ data types:
 boolean -> 1 byte, set = to true or false, returns 1 or 0
 char -> 1 byte, declared in ' '
 int -> 2 or 4 bytes, whole numbers
 float -> 4 bytes, fractional numbers
 double -> 8 bytes, fractional numbers, larger
 string -> stores a sequence of text, to use strings, use #include <string> library and then set youur string = " "

 switch(expression) {
 case 1:
 //code block
 break;

 default: ;
}
  RAM is a form of temporary storage that gets wiped when you turn your computer off. RAM offers lightning-fast data access, which makes it ideal for the processes, apps, and programs your computer is actively working on
 Cache memory is a very high speed semiconductor memory which can speed up the CPU. It acts as a buffer between the CPU and the main memory. It is used to hold those parts of data and program which are most frequently used by the CPU. The parts of data and programs are transferred from the disk to cache memory by the operating system, from where the CPU can access them.
 Primary memory holds only those data and instructions on which the computer is currently working. It has a limited capacity and data is lost when power is switched off. It is generally made up of semiconductor device. These memories are not as fast as registers. The data and instruction required to be processed resides in the main memory. It is divided into two subcategories RAM and ROM.
 Secondary memory is also known as external memory or non-volatile. It is slower than the main memory. These are used for storing data/information permanently. CPU directly does not access these memories, instead they are accessed via input-output routines. The contents of secondary memories are first transferred to the main memory, and then the CPU can access it. For example, disk, CD-ROM, DVD, etc.
 ROM stands for Read Only Memory. The memory from which we can only read but cannot write on it. This type of memory is non-volatile. The information is stored permanently in such memories during manufacture. A ROM stores such instructions that are required to start a computer. This operation is referred to as bootstrap. ROM chips are not only used in the computer but also in other electronic items like washing machine and microwave oven.

 A port is a physical/programmatic docking point using which an external device can be connected to the computer. It can also be programmatic docking point through which information flows from a program to the computer or over the Internet.

 A CPU core is a CPU’s processor. In the old days, every processor had just one core that could focus on one task at a time. Today, CPUs have been two and 18 cores, each of which can work on a different task.

 A core is a physical component contained within the physical CPU. CPU performance will depend on the number of cores and the speed at which the individual cores can execute instructions. Single-core CPUs are rare these days with modern multi-core processors dominating.
Multi-core processors are capable of dividing processes into sub-tasks with each sub-task being executed simultaneously. This is also known as parallel execution because all of the sub-tasks are executed in parallel.

 A thread is a virtual component typically created by the operating system that helps the CPU handle multiple tasks more efficiently. In simple terms, a thread is a component of a process.
 One of the most commonly used analogies is to think of the core as a person’s mouth and the threads as the hands. The mouth does all the eating, while the hands help organize the ‘workload’. Think of threads as a management system for feeding tasks to the core.
 The biggest difference then between cores and threads is that cores are a physical component whereas threads are a virtual component. Cores increase the amount of work that can be accomplished in a time while threads help organize and optimize that workload. Essentially, multiple cores and threads are what enable users to multi-task without too much degradation in performance.

 These are the steps in compiling source code into executable code −

Pre-processing − In this stage pre-processor instructions, typically used by languages like C and C++ are interpreted, i.e. converted to assembly level language.

Lexical analysis − Here all instructions are converted to lexical units like constants, variables, arithmetic symbols, etc.

Parsing − Here all instructions are checked to see if they conform to grammar rules of the language. If there are errors, compiler will ask you to fix them before you can proceed.

Compiling − At this stage the source code is converted into object code.

Linking − If there are any links to external files or libraries, addresses of their executable will be added to the program. Also, if the code needs to be rearranged for actual execution, they will be rearranged. The final output is the executable code that is ready to be executed.

Pragmatic General Multicast (PGM) is a reliable multicast computer network transport protocol. PGM provides a reliable sequence of packets to multiple recipients simultaneously, making it suitable for applications like multi-receiver file-transfer.PGM uses the concept of negative acknowledgements (NAKs).

big O notation -> used to describe worst case time and space complexity of algorithms
time complexity is not a measure of the actual time taken to run an algorithm, instead, it is a measure of how the time taken scales with change in the input length.
The overall amount of memory or space utilized by an algorithm/program, including the space of input values for execution, is called space complexity.

When there is no dependence on the input size n, an algorithm is said to have a constant time of order O(1).
linear search -> worst case is O(n) because it will run for every entry in the array (n entries) if the value is at the end, this has linear time complexity because the running time of linear search algorithm increases linearly with the length of the input
binary search -> logN (much better)
finding maximum value in array -> O(n), as it needs to search every value in array, and so will increase linearly with amount of array entries
bubble sort -> comparing entries and swapping them, you have n elements and do n-1 swaps, then in the next sweep you have n-2 swaps as last 2 elemnts are sorted, etc... until no swaps, but bubble sort emplys two loops, therefore two sets of operations, so worst case scenario is n x n, or n^2
selection sort -> we perform the searching and swapping for each iteration and for both a sorted and unsorted subarray ( nested loops like bubble sort), so for worst case scenario with a completely disrodered array the time complexity of the selection sort becomes N*N i.e. O(N^2)
insertion sort -> n^2 as above

It is always a good practice to assign the pointer NULL to a pointer variable in case you do not have exact address to be assigned.
 This is done at the time of variable declaration. A pointer that is assigned NULL is called a null pointer.

 .h files should always be in double quotes, #include " "
 The exact behavior of the preprocessor varies between compilers. The following answer applies for GCC and several other compilers.

#include <file.h> tells the compiler to search for the header in its "includes" directory, e.g. for MinGW the compiler would search for file.h in C:\MinGW\include\ or wherever your compiler is installed.

#include "file" tells the compiler to search the current directory (i.e. the directory in which the source file resides) for file.

argc and arg v?

Inline fucntions?
printf?




if you want the object on the stack, try this:

MyClass myclass;
myclass.DoSomething();

If you need a stack pointer to that object:

MyClass* myclassptr = &myclass;
myclassptr->DoSomething();

First I need to say that your code,

MyClass *myclass;
myclass->DoSomething();
will cause an undefined behavior. Because the pointer "myclass" isn't pointing to any "MyClass" type objects.

Here I have three suggestions for you:-

option 1:- You can simply declare and use a MyClass type object on the stack as below.

MyClass myclass; //allocates memory for the object "myclass", on the stack.
myclass.DoSomething();

option 2:- By using the new operator.

MyClass *myclass = new MyClass();
Three things will hapen here.

i) Allocates memory for the "MyClass" type object on the heap.

ii) Allocates memory for the "MyClass" type pointer "myclass" on the stack.

iii) pointer "myclass" points to the memory address of "MyClass" type object on the heap

Now you can use the pointer to access member functions of the object after dereferencing the pointer by "->"

myclass->DoSomething();
But you should free the memory allocated to "MyClass" type object on the heap, before returning from the scope unless you want it to exists. Otherwise it will cause a memory leak!

delete myclass; // free the memory pointed by the pointer "myclass"
option 3:- you can also do as below.

MyClass myclass; // allocates memory for the "MyClass" type object on the stack.
MyClass *myclassPtr; // allocates memory for the "MyClass" type pointer on the stack.
myclassPtr = &myclass; // "myclassPtr" pointer points to the momory address of myclass object.
Now, pointer and object both are on the stack. Now you can't return this pointer to the outside of the current scope because both allocated memory of the pointer and the object will be freed while stepping outside the scope.

cache is a memory space where the cpu can store data it needs to rapidly access in future, so it access it quicker
Any modern CPU has several layers of cache that are typically named things like L1, L2, L3 or even L4. This is called a multi-level cache. The lower the number, the faster the cache will be.

It's important to remember that the CPU runs at speeds that are significantly faster than the memory subsystem. It takes the CPU a tiny eternity to wait for something to be fetched from system memory, many, many clock-cycles elapse from the time the request is made to when the data is fetched, sent over the system bus, and received by the CPU.

There's no programming construct for dealing with caches, but if your code and data can fit neatly in the L1 cache, then it will be fastest. Next is if it can fit in the L2, and so on. If your code or data cannot fit at all, then you'll be at the mercy of the system memory, which can be orders of magnitude slower.

This is why counter-intuitive things like unrolling loops, which should be faster, might end up being slower because your code becomes too large to fit in cache. It's also why shaving a few bytes off a data structure could pay huge dividends even though the memory footprint barely changes. If it fits neatly in the cache, it will be faster.

The only way to know if you have a performance problem related to caching is to benchmark very carefully. Remember each processor type has varying amounts of cache, so what might work well on your i7 CPU might be relatively terrible on an i5.

It's only in extremely performance sensitive applications that the cache really becomes something you worry about. For example, if you need to maintain a steady 60FPS frame rate in a game, you'll be looking at cache problems constantly. Every millisecond counts here. Likewise, anything that runs the CPU at 100% for extended periods of time, such as rendering video, will want to pay very close attention to how much they could gain from adjusting the code that's emitted.

You do have control over how your code is generated with compiler flags. Some will produce smaller code, some theoretically faster by unrolling loops and other tricks. To find the optimal setting can be a very time-consuming process. Likewise, you'll need to pay very careful attention to your data structures and how they're used.
we access memory indirectly through an object. An object is a region of storage (usually memory) that has a value and other associated properties

Objects can be named or unnamed (anonymous). A named object is called a variable, and the name of the object is called an identifier. In our programs, most of the objects we create and use will be variables.

At compile time, when the compiler sees this statement, it makes a note to itself that we are defining a variable, giving it the name x, and that it is of type int. From that point forward (with some limitations that we’ll talk about in a future lesson), whenever the compiler sees the identifier x, it will know that we’re referencing this variable.

When the program is run (called runtime), the variable will be instantiated. Instantiation is a fancy word that means the object will be created and assigned a memory address. Variables must be instantiated before they can be used to store values. For the sake of example, let’s say that variable x is instantiated at memory location 140. Whenever the program uses variable x, it will access the value in memory location 140. An instantiated object is sometimes also called an instance.

After a variable has been defined, you can give it a value (in a separate statement) using the = operator. This process is called copy assignment (or just assignment) for short.

int width; // define an integer variable named width
width = 5; // copy assignment of value 5 into variable width

// variable width now has value 5
Copy assignment is named such because it copies the value on the right-hand side of the = operator to the variable on the left-hand side of the operator. The = operator is called the assignment operator.

int a; //default initalisation

int b = 6; //copy initalisation
int h;
h = 7; //copy assignment

int c {5}; //direct list initialisation

ind d {}; //empty initialsation

List initialization has an added benefit: it disallows “narrowing conversions”. This means that if you try to brace initialize a variable using a value that the variable can not safely hold, the compiler will produce an error. For example:

int width { 4.5 }; // error: a number with a fractional value can't fit into an int
In the above snippet, we’re trying to assign a number (4.5) that has a fractional part (the .5 part) to an integer variable (which can only hold numbers without fractional parts).

Copy and direct initialization would simply drop the fractional part, resulting in the initialization of value 4 into variable width (your compiler may produce a warning about this, since losing data is rarely desired). However, with list initialization, the compiler will generate an error instead, forcing you to remedy this issue before proceeding.

 Modern compilers will typically generate warnings if a variable is initialized but not used (since this is rarely desirable). And if “treat warnings as errors” is enabled, these warnings will be promoted to errors and cause the compilation to fail.

the best solution is to use the [[maybe_unused]] attribute. This attribute tells the compiler to expect that the variable may not be used, so it will not generate unused variable warnings.

The following program should generate no warnings/errors, even though x is unused:

int main()
{
    [[maybe_unused]] int x { 5 };

    // since x is [[maybe_unused]], no warning generated

    return 0;
}


differences between versions of C++:
C++ 11:
Unified Initialization
Multithreading
Smart Pointers
Hash Tables
std::array container
Move semantics
Lambda functions included
auto and decltype added

C++ 14:
Generalized Lambdas
Reader-Writer Locks
constexpr included
Return type deductions extended to all functions

C++ 17:
The file system library and Network concepts included
Improved Lambdas
Fold Expressions included
Initializers in if and switch statements
Concurrent and Parallel algorithms in Standard Template Library(STL)
Nested Namespaces
Transactional memory
Inline Variables
Optional header file
Class Template argument deduction

 insertion operator (<<)
 extraction operator >>

 std::cout is buffered,  output sent to std::cout is typically processed in C++. Statements in our program request that output be sent to the console. However, that output is typically not sent to the console immediately. Instead, the requested output “gets in line”, and is stored in a region of memory set aside to collect such requests (called a buffer). Periodically, the buffer is flushed, meaning all of the data collected in the buffer is transferred to its destination (in this case, the console).

To use another analogy, flushing a buffer is kind of like flushing a toilet. All of your collected “output” is transferred to … wherever it goes next. Eew.

Buffered systems are often used in cases where processing a few large batches of data is more efficient than processing many smaller batches of data. Buffering maximizes overall throughput, at the cost of increasing response time.

Using std::endl can be a bit inefficient, as it actually does two jobs: it moves the cursor to the next line of the console, and it flushes the buffer. When writing text to the console, we typically don’t need to flush the buffer at the end of each line. It’s more efficient to let the system flush itself periodically (which it has been designed to do efficiently).

Because of this, use of the ‘\n’ character is typically preferred instead. The ‘\n’ character moves the cursor to the next line of the console, but doesn’t request a flush, so it will often perform better. The ‘\n’ character also tends to be easier to read since it’s both shorter and can be embedded into existing text.

std::cin is another predefined variable that is defined in the iostream library. Whereas std::cout prints data to the console using the insertion operator (<<), std::cin (which stands for “character input”) reads input from keyboard using the extraction operator (>>). The input must be stored in a variable to be used.

Initialization = The object is given a known value at the point of definition.
Assignment = The object is given a known value beyond the point of definition.
Uninitialized = The object has not been given a known value yet.

A statement is a type of instruction that causes the program to perform some action. Statements are often terminated by a semicolon.

std::cout << "Hello world!";
int x{ 5 };

What are ‘”Hello world!”‘ and ‘5’? They are literals. A literal (also known as a literal constant) is a fixed value that has been inserted directly into the source code.

The number of operands that an operator takes as input is called the operator’s arity. Few people know what this word means, so don’t drop it in a conversation and expect anybody to have any idea what you’re talking about. Operators in C++ come in four different arities:

Unary operators act on one operand. An example of a unary operator is the - operator. For example, given -5, operator- takes literal operand 5 and flips its sign to produce new output value -5.


Binary operators act on two operands (often called left and right, as the left operand appears on the left side of the operator, and the right operand appears on the right side of the operator). An example of a binary operator is the + operator. For example, given 3 + 4, operator+ takes the left operand 3 and the right operand 4 and applies mathematical addition to produce new output value 7. The insertion (<<) and extraction (>>) operators are binary operators, taking std::cout or std::cin on the left side, and the value to output or variable to input to on the right side.

Ternary operators act on three operands. There is only one of these in C++ (the conditional operator), which we’ll cover later.

Nullary operators act on zero operands. There is also only one of these in C++ (the throw operator), which we’ll also cover later.

Note that some operators have more than one meaning depending on how they are used. For example, operator- has two contexts. It can be used in unary form to invert a number’s sign (e.g. to convert 5 to -5, or vice versa), or it can be used in binary form to do subtraction (e.g. 4 - 3).

arithmetic operators execute in the same order as they do in standard mathematics: Parenthesis first, then Exponents, then Multiplication & Division, then Addition & Subtraction.

For the operators that we call primarily for their return values (e.g. operator+ or operator*), it’s usually obvious what their return values will be (e.g. the sum or product of the operands).

For the operators we call primarily for their side effects (e.g. operator= or operator<<), it’s not always obvious what return values they produce (if any). For example, what return value would you expect x = 5 to have?

Both operator= and operator<< (when used to output values to the console) return their left operand. Thus, x = 5 returns x, and std::cout << 5 returns std::cout. This is done so that these operators can be chained.

For example, x = y = 5 evaluates as x = (y = 5). First y = 5 assigns 5 to y. This operation then returns y, which can then be assigned to x.

std::cout << "Hello " << "world" evaluates as (std::cout << "Hello ") << "world!". This first prints "Hello " to the console. This operation returns std::cout, which can then be used to print "world!" to the console as well.

An expression is a combination of literals, variables, operators, and function calls that calculates a single value. The process of executing an expression is called evaluation, and the single value produced is called the result of the expression.

x = 5           // has side effect of assigning 5 to x, evaluates to x
x = 2 + 3       // has side effect of assigning 5 to x, evaluates to x
std::cout << x  // has side effect of printing x to console, evaluates to std::cout

std:: out returns itself, so do = assignments, this is why we can chain them

expressions are always evaluated as part of statements.

For example, take this statement:

int x{ 2 + 3 }; // 2 + 3 is an expression that has no semicolon -- the semicolon is at the end of the statement containing the expression
If you were to break this statement down into its syntax, it would look like this:

type identifier { expression };

type could be any valid type (we chose int). identifier could be any valid name (we chose x). And expression could be any valid expression (we chose 2 + 3, which uses two literals and an operator).

Certain expressions (like x = 5) are useful for their side effects (in this case, to assign the value 5 to the variable x). However, we mentioned above that expressions cannot be executed by themselves -- they must exist as part of a statement. So how can we use such expressions?

Fortunately, it’s easy to convert any expression into an equivalent statement. An expression statement is a statement that consists of an expression followed by a semicolon. When the expression statement is executed, the expression will be evaluated.

Thus, we can take any expression (such as x = 5), and turn it into an expression statement (x = 5;) that will compile.


When an expression is used in an expression statement, any return value generated by the expression is discarded (because it is not used).


Inline functions were originally designed as a way to request that the compiler replace your function call with inline expansion of the function code. You should not need to use the inline keyword for this purpose because the compiler will generally determine this for you. In modern C++, the inline keyword is used to exempt a function from the one-definition rule, allowing its definition to be imported into multiple code files. Inline functions are typically defined in header files so they can be #included into any code files that needs them.

When an assertion evaluates to false, your program is immediately stopped. This gives you an opportunity to use debugging tools to examine the state of your program and determine why the assertion failed. Working backwards, you can then find and fix the issue.
In C++, runtime assertions are implemented via the assert preprocessor macro, which lives in the <cassert> header.

To implement virtual functions, C++ implementations typically use a form of late binding known as the virtual table. The virtual table is a lookup table of functions used to resolve function calls in a dynamic/late binding manner. The virtual table sometimes goes by other names, such as “vtable”, “virtual function table”, “virtual method table”, or “dispatch table”.

The virtual table is actually quite simple, though it’s a little complex to describe in words. First, every class that uses virtual functions (or is derived from a class that uses virtual functions) is given its own virtual table. This table is simply a static array that the compiler sets up at compile time. A virtual table contains one entry for each virtual function that can be called by objects of the class. Each entry in this table is simply a function pointer that points to the most-derived function accessible by that class.

Second, the compiler also adds a hidden pointer that is a member of the base class, which we will call *__vptr. *__vptr is set (automatically) when a class object is created so that it points to the virtual table for that class. Unlike the *this pointer, which is actually a function parameter used by the compiler to resolve self-references, *__vptr is a real pointer. Consequently, it makes each class object allocated bigger by the size of one pointer. It also means that *__vptr is inherited by derived classes, which is important.

To address some common challenges with inheritance, C++ has two inheritance-related identifiers: override and final. Note that these identifiers are not keywords -- they are normal words that have special meaning only when used in certain contexts.
the override specifier can be applied to any virtual function by placing the override specifier after the function signature (the same place a function-level const specifier goes).
If the function does not override a base class function (or is applied to a non-virtual function), the compiler will flag the function as an error.
Use the virtual keyword on virtual functions in a base class. Use the override specifier (but not the virtual keyword) on override functions in derived classes.
There may be cases where you don’t want someone to be able to override a virtual function, or inherit from a class. The final specifier can be used to tell the compiler to enforce this. If the user tries to override a function or inherit from a class that has been specified as final, the compiler will give a compile error.

The process of building complex objects from simpler ones is called object composition. There are two types of object composition: composition, and aggregation.

Composition exists when a member of a class has a part-of relationship with the class. In a composition relationship, the class manages the existence of the members. To qualify as a composition, an object and a part must have the following relationship:

The part (member) is part of the object (class)
The part (member) can only belong to one object (class) at a time
The part (member) has its existence managed by the object (class)
The part (member) does not know about the existence of the object (class)
Compositions are typically implemented via normal member variables, or by pointers where the class manages all the memory allocation and deallocation. If you can implement a class as a composition, you should implement a class as a composition.

Aggregations exists when a class has a has-a relationship with the member. In an aggregation relationship, the class does not manage the existence of the members. To qualify as an aggregation, an object and its parts must have the following relationship:

The part (member) is part of the object (class)
The part (member) can belong to more than one object (class) at a time
The part (member) does not have its existence managed by the object (class)
The part (member) does not know about the existence of the object (class)
Aggregations are typically implemented via pointer or reference.


Associations are a looser type of relationship, where the class uses-an otherwise unrelated object. To qualify as an association, an object and an associated object must have the following relationship:

The associated object (member) is otherwise unrelated to the object (class)
The associated object (member) can belong to more than one object (class) at a time
The associated object (member) does not have its existence managed by the object (class)
The associated object (member) may or may not know about the existence of the object (class)
Associations may be implemented via pointer or reference, or by a more indirect means (such as holding the index or key of the associated object).

In a dependency, one class uses another class to perform a task. The dependent class typically is not a member of the class using it, but rather is temporarily created, used, and then destroyed, or passed into a member function from an external source.

A virtual function is a special type of function that resolves to the most-derived version of the function (called an override) that exists between the base and derived class. To be considered an override, the derived class function must have the same signature and return type as the virtual base class function. The one exception is for covariant return types, which allow an override to return a pointer or reference to a derived class if the base class function returns a pointer or reference to the base class.

An interface class is one with no member variables and all pure virtual functions. These are often named starting with a capital I.

When a derived class is assigned to a base class object, the base class only receives a copy of the base portion of the derived class. This is called object slicing.

Dynamic casting can be used to convert a pointer to a base class object into a pointer to a derived class object. This is called downcasting. A failed conversion will return a null pointer.

All template functions or classes must start with a template parameter declaration that tells the compiler that the following function or class is a template function or class. Within the template parameter declaration, the template type parameters or expression parameters are specified. Template type parameters are just placeholder types, normally named T, T1, T2, or other single letter names (e.g. S). Expression parameters are usually integral types, but can be a pointer or reference to a function, class object, or member function.

Splitting up template class definition and member function definitions doesn’t work like normal classes -- you can’t put your class definition in a header and member function definitions in a .cpp file. It’s usually best to keep all of them in a header file, with the member function definitions underneath the class.

Template specialization can be used when we want to override the default behavior from the templated function or class for a specific type. If all types are overridden, this is called full specialization. Classes also support partial specialization, where only some of the templated parameters are specialized. Functions can not be partially specialized.
A throw statement is used to raise an exception. Try blocks look for exceptions thrown by the code written or called within them. These exceptions get routed to catch blocks, which catch exceptions of particular types (if they match) and handle them. By default, an exception that is caught is considered handled.
Exceptions are handled immediately. If an exception is raised, control jumps to the nearest enclosing try block, looking for catch handlers that can handle the exception. If a matching try/catch is found, the stack is unwound to the point of the catch block, and control resumes at the top of the matching catch. If no try block is found or no catch blocks matches, the program calls std::terminate, which will terminate with an unhandled exception error.
Exceptions of any data type can be thrown, including classes.
Catch blocks can be configured to catch exceptions of a particular data type, or a catch-all handler can be set up by using the ellipses (…). A catch block catching a base class reference will also catch exceptions of a derived class. All of the exceptions thrown by the standard library are derived from the std::exception class (which lives in the exception header), so catching a std::exception by reference will catch all standard library exceptions. The what() member function can be used to determine what kind of std::exception was thrown.

Function try blocks give you a way to catch any exception that occurs within a function or an associated member initialization list. These are typically only used with derived class constructors.

You should never throw an exception from a destructor.
Unlike constructors, where throwing exceptions can be a useful way to indicate that object creation did not succeed, exceptions should never be thrown in destructors.
The problem occurs when an exception is thrown from a destructor during the stack unwinding process. If that happens, the compiler is put in a situation where it doesn’t know whether to continue the stack unwinding process or handle the new exception. The end result is that your program will be terminated immediately.
Consequently, the best course of action is just to abstain from using exceptions in destructors altogether. Write a message to a log file instead.

The noexcept exception specifier can be used to denote that a function is no-throw/no-fail.
Finally, exception handling does have a cost. In most cases, code using exceptions will run slightly slower, and the cost of handling an exception is very high. You should only use exceptions to handle exceptional circumstances, not for normal error handling cases (e.g. invalid input).

A smart pointer class is a composition class that is designed to manage dynamically allocated memory, and ensure that memory gets deleted when the smart pointer object goes out of scope.

Copy semantics allow our classes to be copied. This is done primarily via the copy constructor and copy assignment operator.

Move semantics mean a class will transfer ownership of the object rather than making a copy. This is done primarily via the move constructor and move assignment operator.

std::auto_ptr is deprecated and should be avoided.

An r-value reference is a reference that is designed to be initialized with an r-value. An r-value reference is created using a double ampersand. It’s fine to write functions that take r-value reference parameters, but you should almost never return an r-value reference.

If we construct an object or do an assignment where the argument is an l-value, the only thing we can reasonably do is copy the l-value. We can’t assume it’s safe to alter the l-value, because it may be used again later in the program. If we have an expression “a = b”, we wouldn’t reasonably expect b to be changed in any way.

However, if we construct an object or do an assignment where the argument is an r-value, then we know that r-value is just a temporary object of some kind. Instead of copying it (which can be expensive), we can simply transfer its resources (which is cheap) to the object we’re constructing or assigning. This is safe to do because the temporary will be destroyed at the end of the expression anyway, so we know it will never be used again!

You can use the delete keyword to disable copy semantics for classes you create by deleting the copy constructor and copy assignment operator.

std::move allows you to treat an l-value as r-value. This is useful when we want to invoke move semantics instead of copy semantics on an l-value.

std::move_if_noexcept will return a movable r-value if the object has a noexcept move constructor, otherwise it will return a copyable l-value. We can use the noexcept specifier in conjunction with std::move_if_noexcept to use move semantics only when a strong exception guarantee exists (and use copy semantics otherwise).

std::unique_ptr is the smart pointer class that you should probably be using. It manages a single non-shareable resource. std::make_unique() (in C++14) should be preferred to create new std::unique_ptr. std::unique_ptr disables copy semantics.

std::shared_ptr is the smart pointer class used when you need multiple objects accessing the same resource. The resource will not be destroyed until the last std::shared_ptr managing it is destroyed. std::make_shared() should be preferred to create new std::shared_ptr. With std::shared_ptr, copy semantics should be used to create additional std::shared_ptr pointing to the same object.

std::weak_ptr is the smart pointer class used when you need one or more objects with the ability to view and access a resource managed by a std::shared_ptr, but unlike std::shared_ptr, std::weak_ptr is not considered when determining whether the resource should be destroyed.

A static library (also known as an archive) consists of routines that are compiled and linked directly into your program. When you compile a program that uses a static library, all the functionality of the static library that your program uses becomes part of your executable. On Windows, static libraries typically have a .lib extension, whereas on Linux, static libraries typically have an .a (archive) extension. One advantage of static libraries is that you only have to distribute the executable in order for users to run your program. Because the library becomes part of your program, this ensures that the right version of the library is always used with your program. Also, because static libraries become part of your program, you can use them just like functionality you’ve written for your own program. On the downside, because a copy of the library becomes part of every executable that uses it, this can cause a lot of wasted space. Static libraries also can not be upgraded easy -- to update the library, the entire executable needs to be replaced.

A dynamic library (also called a shared library) consists of routines that are loaded into your application at run time. When you compile a program that uses a dynamic library, the library does not become part of your executable -- it remains as a separate unit. On Windows, dynamic libraries typically have a .dll (dynamic link library) extension, whereas on Linux, dynamic libraries typically have a .so (shared object) extension. One advantage of dynamic libraries is that many programs can share one copy, which saves space. Perhaps a bigger advantage is that the dynamic library can be upgraded to a newer version without replacing all of the executables that use it.

Because dynamic libraries are not linked into your program, programs using dynamic libraries must explicitly load and interface with the dynamic library. This mechanism can be confusing, and makes interfacing with a dynamic library awkward. To make dynamic libraries easier to use, an import library can be used.

Const: Whenever const keyword is attached with any method(), variable, pointer variable, and with the object of a class it prevents that specific object/method()/variable to modify its data items value.
Mutable: The mutable storage class specifier in C++ (or use of mutable keyword in C++) auto, register, static and extern are the storage class specifiers in C. typedef is also considered as a storage class specifier in C. C++ also supports all these storage class specifiers. In addition to this C++, adds one important storage class specifier whose name is mutable.
Explicit: In C++, the explicit keyword is used with a constructor to prevent it from performing implicit conversions. A C++ explicit constructor is marked to not convert types implicitly. This is extremely important as implicit conversions often lead to unexpected results.
Auto: The auto keyword in C++ automatically detects and assigns a data type to the variable with which it is used. The compiler analyses the variable's data type by looking at its initialization. It is necessary to initialize the variable when declaring it using the auto keyword.
Extern: The extern keyword in C and C++ extends the visibility of variables and functions across multiple source files. In the case of functions, the extern keyword is used implicitly. But with variables, you have to use the keyword explicitly.
Static: Static variables are initialized only once. Compiler persist the variable till the end of the program. Static variable can be defined inside or outside the function. They are local to the block. The default value of static variable is zero. The static variables are alive till the execution of the program.
Mutex: A mutex is a lockable object that is designed to signal when critical sections of code need exclusive access, preventing other threads with the same protection from executing concurrently and access the same memory locations.
Semaphore: Semaphores are just normal variables used to coordinate the activities of multiple processes in a computer system. They are used to enforce mutual exclusion, avoid race conditions and implement synchronization between processes. The process of using Semaphores provides two operations: wait (P) and signal (V). The wait operation decrements the value of the semaphore, and the signal operation increments the value of the semaphore.
Atomic: Consider a multithreaded program with one shared variable. Now, imagine that all the threads are trying to access and modify this shared variable at the same time. When multiple threads try to access the same variable concurrently, and at least one of them is a write operation, then this is known as a data race. Some data races can cause race conditions which are a problem. Race condition is an error caused by the ordering of events such that the correctness of a program is compromised. Not all data races lead to race conditions and not all race conditions are caused by data races. In order to solve this problem, C++ offers atomic variables that are thread-safe. They allow indivisible read, update and write operations on the shared variable without using mutexes (locks). Mutexes use software routines to lock and unlock operation/s, however, atomic variables utilise processor support through compare and swap instructions. In case of simple increments and decrements, atomic variables are significantly faster than locks.

Storage classes -> A storage class defines the scope (visibility) and life-time of variables and/or functions within a C++ Program. These specifiers precede the type that they modify. There are following storage classes, which can be used in a C++ Program

auto: The auto storage class is the default storage class for all local variables.
register: The register storage class is used to define local variables that should be stored in a register instead of RAM. This means that the variable has a maximum size equal to the register size (usually one word) and can't have the unary '&' operator applied to it (as it does not have a memory location). Used when we need quick access to something small like a counter
static: The static storage class instructs the compiler to keep a local variable in existence during the life-time of the program instead of creating and destroying it each time it comes into and goes out of scope. Therefore, making local variables static allows them to maintain their values between function calls. The static modifier may also be applied to global variables. When this is done, it causes that variable's scope to be restricted to the file in which it is declared.
extern: The extern storage class is used to give a reference of a global variable that is visible to ALL the program files. When you use 'extern' the variable cannot be initialized as all it does is point the variable name at a storage location that has been previously defined. When you have multiple files and you define a global variable or function, which will be used in other files also, then extern will be used in another file to give reference of defined variable or function. Just for understanding extern is used to declare a global variable or function in another file.
mutable: The mutable specifier applies only to class objects, which are discussed later in this tutorial. It allows a member of an object to override const member function. That is, a mutable member can be modified by a const member function.


Cohesion refers to what the class (or module) can do. Low cohesion would mean that the class does a great variety of actions - it is broad, unfocused on what it should do. High cohesion means that the class is focused on what it should be doing, i.e. only methods relating to the intention of the class.

Example of Low Cohesion:

-------------------
| Staff           |
-------------------
| checkEmail()    |
| sendEmail()     |
| emailValidate() |
| PrintLetter()   |
-------------------
Example of High Cohesion:

----------------------------
| Staff                   |
----------------------------
| -salary                 |
| -emailAddr              |
----------------------------
| setSalary(newSalary)    |
| getSalary()             |
| setEmailAddr(newEmail)  |
| getEmailAddr()          |
----------------------------
As for coupling, it refers to how related or dependent two classes/modules are toward each other. For low coupled classes, changing something major in one class should not affect the other. High coupling would make it difficult to change and maintain your code; since classes are closely knit together, making a change could require an entire system revamp.

Good software design has high cohesion and low coupling.

With few exceptions, place code in a namespace. Namespaces should have unique names based on the project name, and possibly its path. Do not use using-directives (e.g., using namespace foo). Do not use inline namespaces. For unnamed namespaces, see Internal Linkage.

A decent rule of thumb is to not inline a function if it is more than 10 lines long.

Beware of destructors, which are often longer than they appear because of implicit member- and base-destructor calls!

Another useful rule of thumb: it's typically not cost effective to inline functions with loops or switch statements (unless, in the common case, the loop or switch statement is never executed).

It is important to know that functions are not always inlined even if they are declared as such; for example, virtual and recursive functions are not normally inlined. Usually recursive functions should not be inline. The main reason for making a virtual function inline is to place its definition in the class, either for convenience or to document its behavior, e.g., for accessors and mutators.



Inline functions are commonly used when the function definitions are small, and the functions are called several times in a program. Using inline functions saves time to transfer the control of the program from the calling function to the definition of the called function. 

However, inlining a function is just a request or suggestion to the compiler, not any mandatory command. It depends on the compiler whether to accept or decline this suggestion of inlining a particular function. The compiler is most likely to not consider the inlining of a function under certain circumstances that are mentioned here as follows-

When a function with a return statement is not returning any value and marked as inline, the compiler does not respond to the programmer’s request of making it an inline function.
When a programmer tries to inline a function containing a loop (for, while, or do-while), the compiler refuses the inline suggestion.
When a function is recursive, it cannot be inlined.
A function containing static variables cannot be made an inline function. 
The compiler declines the request of inlining a function if it contains any switch or go-to statements.


Prefer placing nonmember functions in a namespace; use completely global functions rarely. Do not use a class simply to group static members. Static methods of a class should generally be closely related to instances of the class or the class's static data.



It's best to declare and initialise variables as close to first use as possible.



Variables needed for if, while and for statements should normally be declared within those statements, so that such variables are confined to those scopes. E.g.:

while (const char* p = strchr(str, '/')) str = p + 1;
There is one caveat: if the variable is an object, its constructor is invoked every time it enters scope and is created, and its destructor is invoked every time it goes out of scope.

// Inefficient implementation:
for (int i = 0; i < 1000000; ++i) {
  Foo f;  // My ctor and dtor get called 1000000 times each.
  f.DoSomething(i);
}
It may be more efficient to declare such a variable used in a loop outside that loop:

Foo f;  // My ctor and dtor get called once each.
for (int i = 0; i < 1000000; ++i) {
  f.DoSomething(i);
}

Objects with static storage duration are forbidden unless they are trivially destructible. Informally this means that the destructor does not do anything, even taking member and base destructors into account. More formally it means that the type has no user-defined or virtual destructor and that all bases and non-static members are trivially destructible. Static function-local variables may use dynamic initialization. Use of dynamic initialization for static class member variables or variables at namespace scope is discouraged, but allowed in limited circumstances; see below for details.

As a rule of thumb: a global variable satisfies these requirements if its declaration, considered in isolation, could be constexpr.



Every object has a storage duration, which correlates with its lifetime. Objects with static storage duration live from the point of their initialization until the end of the program. Such objects appear as variables at namespace scope ("global variables"), as static data members of classes, or as function-local variables that are declared with the static specifier. Function-local static variables are initialized when control first passes through their declaration; all other objects with static storage duration are initialized as part of program start-up. All objects with static storage duration are destroyed at program exit (which happens before unjoined threads are terminated).

Initialization may be dynamic, which means that something non-trivial happens during initialization. (For example, consider a constructor that allocates memory, or a variable that is initialized with the current process ID.) The other kind of initialization is static initialization. The two aren't quite opposites, though: static initialization always happens to objects with static storage duration (initializing the object either to a given constant or to a representation consisting of all bytes set to zero), whereas dynamic initialization happens after that, if required.



Global and static variables are very useful for a large number of applications: named constants, auxiliary data structures internal to some translation unit, command-line flags, logging, registration mechanisms, background infrastructure, etc.



Global and static variables that use dynamic initialization or have non-trivial destructors create complexity that can easily lead to hard-to-find bugs. Dynamic initialization is not ordered across translation units, and neither is destruction (except that destruction happens in reverse order of initialization). When one initialization refers to another variable with static storage duration, it is possible that this causes an object to be accessed before its lifetime has begun (or after its lifetime has ended). Moreover, when a program starts threads that are not joined at exit, those threads may attempt to access objects after their lifetime has ended if their destructor has already run.



Avoid virtual method calls in constructors, and avoid initialization that can fail if you can't signal an error.



Do not define implicit conversions. Use the explicit keyword for conversion operators and single-argument constructors.

The explicit keyword can be applied to a constructor or a conversion operator, to ensure that it can only be used when the destination type is explicit at the point of use, e.g., with a cast. This applies not only to implicit conversions, but to list initialization syntax:

class Foo {
  explicit Foo(int x, double y);
  ...
};

void Func(Foo f);
Func({42, 3.14});  // Error


A type should not be copyable/movable if the meaning of copying/moving is unclear to a casual user, or if it incurs unexpected costs. Move operations for copyable types are strictly a performance optimization and are a potential source of bugs and complexity, so avoid defining them unless they are significantly more efficient than the corresponding copy operations. If your type provides copy operations, it is recommended that you design your class so that the default implementation of those operations is correct. Remember to review the correctness of any defaulted operations as you would any other code.



In C++ programming, object slicing occurs when an object of a subclass type is copied to an object of superclass type: the superclass copy will not have any of the member variables or Member functions defined in the subclass. These variables and functions have, in effect, been "sliced off".

Object slicing can be prevented by making the base class function pure virtual thereby disallowing object creation. It is not possible to create the object of a class that contains a pure virtual method.

To eliminate the risk of slicing, prefer to make base classes abstract, by making their constructors protected, by declaring their destructors protected, or by giving them one or more pure virtual member functions. Prefer to avoid deriving from concrete classes.



Use a struct only for passive objects that carry data; everything else is a class.



Composition is often more appropriate than inheritance. When using inheritance, make it public.



"Interface inheritance" is inheritance from a pure abstract base class (one with no state or defined methods); all other inheritance is "implementation inheritance"

All inheritance should be public. If you want to do private inheritance, you should be including an instance of the base class as a member instead. You may use final on classes when you don't intend to support using them as base classes.

Do not overuse implementation inheritance. Composition is often more appropriate. Try to restrict use of inheritance to the "is-a" case: Bar subclasses Foo if it can reasonably be said that Bar "is a kind of" Foo.

Limit the use of protected to those member functions that might need to be accessed from subclasses. Note that data members should be private.

Explicitly annotate overrides of virtual functions or virtual destructors with exactly one of an override or (less frequently) final specifier. Do not use virtual when declaring an override. Rationale: A function or destructor marked override or final that is not an override of a base class virtual function will not compile, and this helps catch common errors. The specifiers serve as documentation; if no specifier is present, the reader has to check all ancestors of the class in question to determine if the function or destructor is virtual or not.

Multiple inheritance is permitted, but multiple implementation inheritance is strongly discouraged.



Specifying noexcept on a function can trigger compiler optimizations in environments where exceptions are enabled, e.g., compiler does not have to generate extra code for stack-unwinding, if it knows that no exceptions can be thrown due to a noexcept specifier.



Use constexpr to define true constants or to ensure constant initialization.

Some variables can be declared constexpr to indicate the variables are true constants, i.e., fixed at compilation/link time. Some functions and constructors can be declared constexpr which enables them to be used in defining a constexpr variable.

Use of constexpr enables definition of constants with floating-point expressions rather than just literals; definition of constants of user-defined types; and definition of constants with function calls.

Prematurely marking something as constexpr may cause migration problems if later on it has to be downgraded. Current restrictions on what is allowed in constexpr functions and constructors may invite obscure workarounds in these definitions.

constexpr definitions enable a more robust specification of the constant parts of an interface. Use constexpr to specify true constants and the functions that support their definitions. Avoid complexifying function definitions to enable their use with constexpr. Do not use constexpr to force inlining.



Referencing and Dereferencing of the Function Pointer in C++
Similar to the pointer used with variables we perform referencing and dereferencing with a function pointer.

Referencing: When pointer is allocated the address of the function to be associated with it then this process is referred to as referencing.

Dereferencing: When we use the (*)operator  to get the value stored in the pointer.

Syntax:

// Declaring
return_type (*FuncPtr) (parameter type, ....); 

// Referencing
FuncPtr= function_name;

// Dereferencing
data_type x=*FuncPtr;
Function pointer used to call the function
In this, we see how we point a pointer to a function and call it using that pointer. It is an efficient way to use 

Example:

C++
// C++ program to implementation
// Function Pointer
#include <iostream>
using namespace std;
 
int multiply(int a, int b) { return a * b; }
 
int main()
{
    int (*func)(int, int);
 
    // func is pointing to the multiplyTwoValues function
 
    func = multiply;
 
    int prod = func(15, 2);
    cout << "The value of the product is: " << prod << endl;
 
    return 0;
}

Output

The value of the product is: 30
In the above program, we are declaring a function multiply where we are multiplying two elements a and b, then returning the result. But, rather than directly calling the function we are using a function pointer prod which is doing the same work for us.

Passing a function pointer as a parameter
When declaring a function pointer to store the memory address of the function but, when we want to pass the return value to the next function. We have two methods to perform this task. First, either pass the value we got or second pass the function pointer that already exists.

Example:

C++
// C++ Program for demonstrating
// function pointer as pointer
#include <iostream>
using namespace std;
 
const int a = 15;
const int b = 2;
 
// Function for Multiplication
int multiply() { return a * b; }
 
// Function containing function pointer
// as parameter
void print(int (*funcptr)())
{
    cout << "The value of the product is: " << funcptr()
         << endl;
}
 
// Driver Function
int main()
{
    print(multiply);
    return 0;
}

Output

The value of the product is: 30


Static member functions in C++ are the functions that can access only the static data members. These static data members share a single copy of themselves with the different objects of the same class. A function can be made static by using the keyword static before the function name while defining a class.



Pure virtual functions must be implemented in child classes, non-pure virtual functions do not.



The size_t type is the unsigned integer type that is the result of the sizeof operator (and the offsetof operator), so it is guaranteed to be big enough to contain the size of the biggest object your system can handle (e.g., a static array of 8Gb).

The size_t type may be bigger than, equal to, or smaller than an unsigned int, and your compiler might make assumptions about it for optimization.

size_t is used in place of unsigned int sometimes as it is the max size regardless of whether your system is 64 or 32 bit.



uint64_t is guaranteed to be 64 bits. If you need 64 bits, you should use it.

size_t isn't guaranteed to be 64 bits; it could be 128 bits in a future machine. So, keyword uint_64 its reserved by that


 
In a statically typed language, such as C++ or Java for example, static may refer to the information known at compilation time while dynamic refers to the information known at runtime.

For example:

struct Base { virtual std::string name() const { return "Base"; } };

struct Derived: Base { std::string name() const { return "Derived"; } };

void print(Base const& b) { std::cout << b.name() << "\n"; }
In the print method, the static type of b is Base const&. Therefore, the compiler will check that all methods called exist in the context of a Base object.

However, when execution comes, the call to name, as the method is virtual, is performed with regard to the dynamic type of the object:

this may be Base
this may be Derived
this may be another derived class from Base that we know not yet
Therefore, in the following example:

int main(int argc, char* argv[]) {
  if (argc == 1) {
    Base base;
    print();
  } else {
    Derived derived;
    print(derived);
  }
};
The static and dynamic type of base is Base and derived is Derived.
In the print method, the static type of b is Base (always)
Depending on the number of arguments, the dynamic of b is either Base or Derived
It is a current mistake to assume that polymorphism is necessarily based on dynamic memory allocation, but the two concepts, while not orthogonal, can be used without one another in some conditions.

Whenever another shared_ptr is created that points to the same object, its reference count is incremented by 1. 
When a shared_ptr goes out of scope or is reset, its reference count is decremented by 1. When the reference count reaches 0, the managed object is deleted. 
std::shared_ptr is thread-safe in the sense that it can safely be accessed by multiple threads simultaneously. 
The reference count that shared_ptr uses to keep track of the number of references to the managed object is atomic, which means that it can be updated safely by multiple threads at the same time without causing race conditions or undefined behavior.
However, if multiple threads are accessing the same std::shared_ptr object without proper synchronization, there is indeed a risk of data corruption or other errors. To ensure safe concurrent access to the shared resource, proper synchronization mechanisms such as mutex locks or atomic operations must be employed. 
Otherwise, if not properly synchronized, concurrent access to the same std::shared_ptr object could lead to race conditions and data corruption.

The auto keyword in C++ automatically detects and assigns a data type to the variable with which it is used. The compiler analyses the variable's data type by looking at its initialization. It is necessary to initialize the variable when declaring it using the auto keyword.

The only problem with using the auto keyword is that constant variables will not be analyzed. If we want a variable to be constant and define it using the auto keyword, we will also have to use the keyword const along with the auto keyword. 

The auto keyword is also used as the return type for any function. The only condition is that each return statement inside this function should return the same variable type. The compiler decides the function's return type by analyzing the return statement expression. 

Like the auto keyword in C++, the auto&& keyword can be used as a universal reference value, which means it will accept any value, whether an lvalue or an rvalue reference expression. Let us look in detail at what this exactly means.

To recap, an lvalue expression is one whose resources cant be reused, like normal variables in C++ or any other objects that are declared using a name directly. 
For example, in the code int y = 7; 
y is an lvalue. Similarly, 
arr[0] is also an lvalue where
arr is a vector. These objects are such that they are declared with a name and are permanent.

But an rvalue expression denotes an object whose resources cannot be reused, which means a temporary disposable object. These objects are not declared or defined explicitly. For example, in the code func(class_obj()) where func() is a function that takes a class object as a parameter. It is clear in the code that we have not explicitly defined any class object. Instead, we have just passed the function class_obj() as a parameter which will create a temporary class object and pass it to the function func(). Hence, this class object is temporary, disposable, and an rvalue.

Now, to reference an lvalue object or variable, we have to use one & symbol, but to reference an rvalue object or variable, we have to use two ampersands &&. But, if we use the auto keyword to declare the reference, we can use auto&&, which will work for both lvalue and rvalue reference expressions.


/*
c++ notes
:: -> scope resolution operator
std::string -> this is a string object that belongs to the std namespace
Namespaces are used to group classes and variables, to avoid naming conflicts with other classes/variables that may share the same name
Bring in the namespace you want to use with the using keyword at the top of your code
*/
namespace asad{
int age;	
};
/* namespace created above , namespaces are useful to group things of common functionality, or group categories of different things together, or for avoiding name clashes mentioned earlier
*/
asad::age; //this is how we would call the int variable defined in the asad namespace

/*
A class is like a blueprint of an object. It is a user-defined data type with data members and member functions and is defined with the keyword class.
You define objects as an instance of a class. Once it creates the object, then it can operate on both data members and member functions.

Access modifiers used to define accessibility for the class members: Private, Public, Protected
Public: All member functions and data members are accessible outside the class.
Protected: All member functions and data members are accessible within the class and to the derived class.
Private: All member functions and data members cannot be accessed outside the class.

While loop only iterates loop if the condition is true, do-while loop first iterates the body once then checks the condition

int is 4 bytes

size and length functions used to return the number of characters in a string

In prefix (++i), first, it increments the value, and then it assigns the value to the expression.

In postfix (i++), it assigns the value to the expression, and then it increments the variable's value.

you can compile a program without the main function, but you cannot run or execute the program because the main() function is the entry point, from where all the execution begins.

4 Data types:
Primitive/Basic: Char, int, short, float, double, long, bool, etc.
Derived: Array, pointer, etc.
Enumeration: Enum
User-defined: Structure, class, etc.

Struct is different from a class because its members are public by default, and the default access specifiers are public when deriving a struct from a class/struct. You can't interit from a struct.

A member function in the base class redefined in a derived class is a virtual function. It is declared using the virtual keyword. It ensures that the correct function is called for an object, irrespective of the type of reference/pointer used for the function call. Virtual functions are mainly used for runtime polymorphism.

Like a friend function, a friend class can access personal and guarded variables of the type in which it is declared. All member functions for classes specified as friends to another class are friend functions for the friend class.

An abstract class is a class whose objects cannot be created. It serves as a parent for the derived classes. Placing a pure virtual function in the class makes it an abstract class.

A variable in a class declared as static has its space allocated for the lifetime of the program. Regardless of the number of objects of that class created, there is only a single copy of the static member. The same static member is accessible to all the objects of that class.

A static member function can be called even if no class objects exist. It is accessed using only the class name and the scope resolution operator (::).

You use the void() return type when you don’t want to return any value. It specifies that the function doesn’t return a value. A function with a void return type completes its task and then returns the control to the caller.

You can define a friend function as a function that can access private, public and protect members of the class. You declare the friend function with the help of the friend keyword. You declare this function inside the class.

Structures (also called structs) are a way to group several related variables into one place. Each variable in the structure is known as a member of the structure.

Unlike an array, a structure can contain many different data types (int, string, bool, etc.).

To create a structure, use the struct keyword and declare each of its members inside curly braces. After the declaration, specify the name of the structure variable. Structs are instantiated same as classes

 getline() function in C++. This is an inbuilt function that accepts single and multiple character inputs. cin is the first parameter in the getline function -> getline(cin, "my name is asad")

 '\0' is not required if you are using it as character array. But if you use character array as string, you need to put '\0'. This allows to find the point where a string ends.

 Symbol Table is an important data structure created and maintained by the compiler in order to keep track of semantics of variables i.e. it stores information about the scope and binding information about names, information about instances of various entities such as variable and function names, classes, objects, etc.

 The dot and arrow operator are both used in C++ to access the members of a class. They are just used in different scenarios. In C++, types declared as class, struct, or union are considered "of class type". So the following refers to all three of them.

a.b is only used if b is a member of the object (or reference[1] to an object) a. So for a.b, a will always be an actual object (or a reference to an object) of a class.
a→b is essentially a shorthand notation for (*a).b, ie, if a is a pointer to an object, then a→b is accessing the property b of the object that a points to.

 The auto keyword is a simple way to declare a variable that has a complicated type. For example, you can use auto to declare a variable where the initialization expression involves templates, pointers to functions, or pointers to members.

 Loop is more efficient for factorials. When you do recursion, you have up to x function calls on the stack.

You almost never use recursion for performance reasons. You use recursion to make the problem more simple.

 References are often confused with pointers but three major differences between references and pointers are −

You cannot have NULL references. You must always be able to assume that a reference is connected to a legitimate piece of storage.

Once a reference is initialized to an object, it cannot be changed to refer to another object. Pointers can be pointed to another object at any time.

A reference must be initialized when it is created. Pointers can be initialized at any time.

Think of a variable name as a label attached to the variable's location in memory. You can then think of a reference as a second label attached to that memory location. Therefore, you can access the contents of the variable through either the original variable name or the reference. For example, suppose we have the following example −

int i = 17;
We can declare reference variables for i as follows.

int& r = i;

Buffer is a basic term that denotes a computer memory block that acts as a temporary placeholder. Buffer term is used in almost all fields like video streaming, RAM, etc. In the programming part, a software buffer is a place where data can be kept before it starts processing. It is done in order to make the process faster.
 That is, normally if data write using direct operation, it takes time. In the case of buffer, it is performed in a fast manner.

 “Heap” memory, also known as “dynamic” memory, is an alternative to local stack memory. Local memory is quite automatic. Local variables are allocated automatically when a function is called, and they are deallocated automatically when the function exits.
  Heap memory is different in every way. The programmer explicitly requests that space be allocated, using the new operator in Java or C++.
  This memory “block” will be of a particular size, ususally determined automatically from the size of the object being created.
  That memory block (your object) continues to be allocated until something happens that makes it go away.
   In some languages (noteably, C and C++), an object in heap memory only goes away when the programmer explicitly requests that it be deallocated.
   So the programmer has much greater control of memory, but with greater responsibility since the memory must now be actively managed.
   Dropping all references to a memory location without deallocating it is a signficant source of errors in C/C++, and this is so common that it has a name: memory leak.
   (In fact, many commercial programs implemented in C++ have memory leaks, that will eventually make them crash after being used for a long time.)
 Java removes this source of errors by handling memory deallocation automatically, using garbage collection. The downside is that garbage collection is a slow process that happens at unpredictable times.

 Function Overloading (achieved at compile time) provides multiple definitions of the function by changing signature i.e changing number of parameters, change datatype of parameters, return type doesn’t play anyrole.

 Function Overriding (achieved at run time) It is the redefinition of base class function in its derived class with same signature i.e return type and parameters.

 C/C++ IO are based on streams, which are sequence of bytes flowing in and out of the programs (just like water and oil flowing through a pipe).
 In input operations, data bytes flow from an input source (such as keyboard, file, network or another program) into the program. In output operations, data bytes flow from the program to an output sink (such as console, file, network or another program).
 Streams acts as an intermediaries between the programs and the actual IO devices, in such the way that frees the programmers from handling the actual devices, so as to archive device independent IO operations.
 C++ IO is provided in headers <iostream> (which included <ios>, <istream>, <ostream> and <streambuf>), <fstream> (for file IO), and <sstream> (for string IO). Furthermore, the header <iomanip> provided manipulators such as setw(), setprecision()setfill() and setbase() for formatting.
 << is stream insertion operator, used to print data
 >> is stream extraction operator, used to take in data

 the difference between 32-bit and a 64-bit is all about processing power. Computers with 32-bit processors are older, slower, and less secure, while a 64-bit processor is newer, faster, and more secure.


 c++ data types:
 boolean -> 1 byte, set = to true or false, returns 1 or 0
 char -> 1 byte, declared in ' '
 int -> 2 or 4 bytes, whole numbers
 float -> 4 bytes, fractional numbers
 double -> 8 bytes, fractional numbers, larger
 string -> stores a sequence of text, to use strings, use #include <string> library and then set youur string = " "

 switch(expression) {
 case 1:
 //code block
 break;

 default: ;
}
  RAM is a form of temporary storage that gets wiped when you turn your computer off. RAM offers lightning-fast data access, which makes it ideal for the processes, apps, and programs your computer is actively working on
 Cache memory is a very high speed semiconductor memory which can speed up the CPU. It acts as a buffer between the CPU and the main memory. It is used to hold those parts of data and program which are most frequently used by the CPU. The parts of data and programs are transferred from the disk to cache memory by the operating system, from where the CPU can access them.
 Primary memory holds only those data and instructions on which the computer is currently working. It has a limited capacity and data is lost when power is switched off. It is generally made up of semiconductor device. These memories are not as fast as registers. The data and instruction required to be processed resides in the main memory. It is divided into two subcategories RAM and ROM.
 Secondary memory is also known as external memory or non-volatile. It is slower than the main memory. These are used for storing data/information permanently. CPU directly does not access these memories, instead they are accessed via input-output routines. The contents of secondary memories are first transferred to the main memory, and then the CPU can access it. For example, disk, CD-ROM, DVD, etc.
 ROM stands for Read Only Memory. The memory from which we can only read but cannot write on it. This type of memory is non-volatile. The information is stored permanently in such memories during manufacture. A ROM stores such instructions that are required to start a computer. This operation is referred to as bootstrap. ROM chips are not only used in the computer but also in other electronic items like washing machine and microwave oven.

 A port is a physical/programmatic docking point using which an external device can be connected to the computer. It can also be programmatic docking point through which information flows from a program to the computer or over the Internet.

 A CPU core is a CPU’s processor. In the old days, every processor had just one core that could focus on one task at a time. Today, CPUs have been two and 18 cores, each of which can work on a different task.

 A core is a physical component contained within the physical CPU. CPU performance will depend on the number of cores and the speed at which the individual cores can execute instructions. Single-core CPUs are rare these days with modern multi-core processors dominating.
Multi-core processors are capable of dividing processes into sub-tasks with each sub-task being executed simultaneously. This is also known as parallel execution because all of the sub-tasks are executed in parallel.

 A thread is a virtual component typically created by the operating system that helps the CPU handle multiple tasks more efficiently. In simple terms, a thread is a component of a process.
 One of the most commonly used analogies is to think of the core as a person’s mouth and the threads as the hands. The mouth does all the eating, while the hands help organize the ‘workload’. Think of threads as a management system for feeding tasks to the core.
 The biggest difference then between cores and threads is that cores are a physical component whereas threads are a virtual component. Cores increase the amount of work that can be accomplished in a time while threads help organize and optimize that workload. Essentially, multiple cores and threads are what enable users to multi-task without too much degradation in performance.

 These are the steps in compiling source code into executable code −

Pre-processing − In this stage pre-processor instructions, typically used by languages like C and C++ are interpreted, i.e. converted to assembly level language.

Lexical analysis − Here all instructions are converted to lexical units like constants, variables, arithmetic symbols, etc.

Parsing − Here all instructions are checked to see if they conform to grammar rules of the language. If there are errors, compiler will ask you to fix them before you can proceed.

Compiling − At this stage the source code is converted into object code.

Linking − If there are any links to external files or libraries, addresses of their executable will be added to the program. Also, if the code needs to be rearranged for actual execution, they will be rearranged. The final output is the executable code that is ready to be executed.

Pragmatic General Multicast (PGM) is a reliable multicast computer network transport protocol. PGM provides a reliable sequence of packets to multiple recipients simultaneously, making it suitable for applications like multi-receiver file-transfer.PGM uses the concept of negative acknowledgements (NAKs).

big O notation -> used to describe worst case time and space complexity of algorithms
time complexity is not a measure of the actual time taken to run an algorithm, instead, it is a measure of how the time taken scales with change in the input length.
The overall amount of memory or space utilized by an algorithm/program, including the space of input values for execution, is called space complexity.

When there is no dependence on the input size n, an algorithm is said to have a constant time of order O(1).
linear search -> worst case is O(n) because it will run for every entry in the array (n entries) if the value is at the end, this has linear time complexity because the running time of linear search algorithm increases linearly with the length of the input
binary search -> logN (much better)
finding maximum value in array -> O(n), as it needs to search every value in array, and so will increase linearly with amount of array entries
bubble sort -> comparing entries and swapping them, you have n elements and do n-1 swaps, then in the next sweep you have n-2 swaps as last 2 elemnts are sorted, etc... until no swaps, but bubble sort emplys two loops, therefore two sets of operations, so worst case scenario is n x n, or n^2
selection sort -> we perform the searching and swapping for each iteration and for both a sorted and unsorted subarray ( nested loops like bubble sort), so for worst case scenario with a completely disrodered array the time complexity of the selection sort becomes N*N i.e. O(N^2)
insertion sort -> n^2 as above

It is always a good practice to assign the pointer NULL to a pointer variable in case you do not have exact address to be assigned.
 This is done at the time of variable declaration. A pointer that is assigned NULL is called a null pointer.

 .h files should always be in double quotes, #include " "
 The exact behavior of the preprocessor varies between compilers. The following answer applies for GCC and several other compilers.

#include <file.h> tells the compiler to search for the header in its "includes" directory, e.g. for MinGW the compiler would search for file.h in C:\MinGW\include\ or wherever your compiler is installed.

#include "file" tells the compiler to search the current directory (i.e. the directory in which the source file resides) for file.

argc and arg v?

Inline fucntions?
printf?




if you want the object on the stack, try this:

MyClass myclass;
myclass.DoSomething();

If you need a stack pointer to that object:

MyClass* myclassptr = &myclass;
myclassptr->DoSomething();

First I need to say that your code,

MyClass *myclass;
myclass->DoSomething();
will cause an undefined behavior. Because the pointer "myclass" isn't pointing to any "MyClass" type objects.

Here I have three suggestions for you:-

option 1:- You can simply declare and use a MyClass type object on the stack as below.

MyClass myclass; //allocates memory for the object "myclass", on the stack.
myclass.DoSomething();

option 2:- By using the new operator.

MyClass *myclass = new MyClass();
Three things will hapen here.

i) Allocates memory for the "MyClass" type object on the heap.

ii) Allocates memory for the "MyClass" type pointer "myclass" on the stack.

iii) pointer "myclass" points to the memory address of "MyClass" type object on the heap

Now you can use the pointer to access member functions of the object after dereferencing the pointer by "->"

myclass->DoSomething();
But you should free the memory allocated to "MyClass" type object on the heap, before returning from the scope unless you want it to exists. Otherwise it will cause a memory leak!

delete myclass; // free the memory pointed by the pointer "myclass"
option 3:- you can also do as below.

MyClass myclass; // allocates memory for the "MyClass" type object on the stack.
MyClass *myclassPtr; // allocates memory for the "MyClass" type pointer on the stack.
myclassPtr = &myclass; // "myclassPtr" pointer points to the momory address of myclass object.
Now, pointer and object both are on the stack. Now you can't return this pointer to the outside of the current scope because both allocated memory of the pointer and the object will be freed while stepping outside the scope.

cache is a memory space where the cpu can store data it needs to rapidly access in future, so it access it quicker
Any modern CPU has several layers of cache that are typically named things like L1, L2, L3 or even L4. This is called a multi-level cache. The lower the number, the faster the cache will be.

It's important to remember that the CPU runs at speeds that are significantly faster than the memory subsystem. It takes the CPU a tiny eternity to wait for something to be fetched from system memory, many, many clock-cycles elapse from the time the request is made to when the data is fetched, sent over the system bus, and received by the CPU.

There's no programming construct for dealing with caches, but if your code and data can fit neatly in the L1 cache, then it will be fastest. Next is if it can fit in the L2, and so on. If your code or data cannot fit at all, then you'll be at the mercy of the system memory, which can be orders of magnitude slower.

This is why counter-intuitive things like unrolling loops, which should be faster, might end up being slower because your code becomes too large to fit in cache. It's also why shaving a few bytes off a data structure could pay huge dividends even though the memory footprint barely changes. If it fits neatly in the cache, it will be faster.

The only way to know if you have a performance problem related to caching is to benchmark very carefully. Remember each processor type has varying amounts of cache, so what might work well on your i7 CPU might be relatively terrible on an i5.

It's only in extremely performance sensitive applications that the cache really becomes something you worry about. For example, if you need to maintain a steady 60FPS frame rate in a game, you'll be looking at cache problems constantly. Every millisecond counts here. Likewise, anything that runs the CPU at 100% for extended periods of time, such as rendering video, will want to pay very close attention to how much they could gain from adjusting the code that's emitted.

You do have control over how your code is generated with compiler flags. Some will produce smaller code, some theoretically faster by unrolling loops and other tricks. To find the optimal setting can be a very time-consuming process. Likewise, you'll need to pay very careful attention to your data structures and how they're used.
we access memory indirectly through an object. An object is a region of storage (usually memory) that has a value and other associated properties

Objects can be named or unnamed (anonymous). A named object is called a variable, and the name of the object is called an identifier. In our programs, most of the objects we create and use will be variables.

At compile time, when the compiler sees this statement, it makes a note to itself that we are defining a variable, giving it the name x, and that it is of type int. From that point forward (with some limitations that we’ll talk about in a future lesson), whenever the compiler sees the identifier x, it will know that we’re referencing this variable.

When the program is run (called runtime), the variable will be instantiated. Instantiation is a fancy word that means the object will be created and assigned a memory address. Variables must be instantiated before they can be used to store values. For the sake of example, let’s say that variable x is instantiated at memory location 140. Whenever the program uses variable x, it will access the value in memory location 140. An instantiated object is sometimes also called an instance.

After a variable has been defined, you can give it a value (in a separate statement) using the = operator. This process is called copy assignment (or just assignment) for short.

int width; // define an integer variable named width
width = 5; // copy assignment of value 5 into variable width

// variable width now has value 5
Copy assignment is named such because it copies the value on the right-hand side of the = operator to the variable on the left-hand side of the operator. The = operator is called the assignment operator.

int a; //default initalisation

int b = 6; //copy initalisation
int h;
h = 7; //copy assignment

int c {5}; //direct list initialisation

ind d {}; //empty initialsation

List initialization has an added benefit: it disallows “narrowing conversions”. This means that if you try to brace initialize a variable using a value that the variable can not safely hold, the compiler will produce an error. For example:

int width { 4.5 }; // error: a number with a fractional value can't fit into an int
In the above snippet, we’re trying to assign a number (4.5) that has a fractional part (the .5 part) to an integer variable (which can only hold numbers without fractional parts).

Copy and direct initialization would simply drop the fractional part, resulting in the initialization of value 4 into variable width (your compiler may produce a warning about this, since losing data is rarely desired). However, with list initialization, the compiler will generate an error instead, forcing you to remedy this issue before proceeding.

 Modern compilers will typically generate warnings if a variable is initialized but not used (since this is rarely desirable). And if “treat warnings as errors” is enabled, these warnings will be promoted to errors and cause the compilation to fail.

the best solution is to use the [[maybe_unused]] attribute. This attribute tells the compiler to expect that the variable may not be used, so it will not generate unused variable warnings.

The following program should generate no warnings/errors, even though x is unused:

int main()
{
    [[maybe_unused]] int x { 5 };

    // since x is [[maybe_unused]], no warning generated

    return 0;
}


differences between versions of C++:
C++ 11:
Unified Initialization
Multithreading
Smart Pointers
Hash Tables
std::array container
Move semantics
Lambda functions included
auto and decltype added

C++ 14:
Generalized Lambdas
Reader-Writer Locks
constexpr included
Return type deductions extended to all functions

C++ 17:
The file system library and Network concepts included
Improved Lambdas
Fold Expressions included
Initializers in if and switch statements
Concurrent and Parallel algorithms in Standard Template Library(STL)
Nested Namespaces
Transactional memory
Inline Variables
Optional header file
Class Template argument deduction

 insertion operator (<<)
 extraction operator >>

 std::cout is buffered,  output sent to std::cout is typically processed in C++. Statements in our program request that output be sent to the console. However, that output is typically not sent to the console immediately. Instead, the requested output “gets in line”, and is stored in a region of memory set aside to collect such requests (called a buffer). Periodically, the buffer is flushed, meaning all of the data collected in the buffer is transferred to its destination (in this case, the console).

To use another analogy, flushing a buffer is kind of like flushing a toilet. All of your collected “output” is transferred to … wherever it goes next. Eew.

Buffered systems are often used in cases where processing a few large batches of data is more efficient than processing many smaller batches of data. Buffering maximizes overall throughput, at the cost of increasing response time.

Using std::endl can be a bit inefficient, as it actually does two jobs: it moves the cursor to the next line of the console, and it flushes the buffer. When writing text to the console, we typically don’t need to flush the buffer at the end of each line. It’s more efficient to let the system flush itself periodically (which it has been designed to do efficiently).

Because of this, use of the ‘\n’ character is typically preferred instead. The ‘\n’ character moves the cursor to the next line of the console, but doesn’t request a flush, so it will often perform better. The ‘\n’ character also tends to be easier to read since it’s both shorter and can be embedded into existing text.

std::cin is another predefined variable that is defined in the iostream library. Whereas std::cout prints data to the console using the insertion operator (<<), std::cin (which stands for “character input”) reads input from keyboard using the extraction operator (>>). The input must be stored in a variable to be used.

Initialization = The object is given a known value at the point of definition.
Assignment = The object is given a known value beyond the point of definition.
Uninitialized = The object has not been given a known value yet.

A statement is a type of instruction that causes the program to perform some action. Statements are often terminated by a semicolon.

std::cout << "Hello world!";
int x{ 5 };

What are ‘”Hello world!”‘ and ‘5’? They are literals. A literal (also known as a literal constant) is a fixed value that has been inserted directly into the source code.

The number of operands that an operator takes as input is called the operator’s arity. Few people know what this word means, so don’t drop it in a conversation and expect anybody to have any idea what you’re talking about. Operators in C++ come in four different arities:

Unary operators act on one operand. An example of a unary operator is the - operator. For example, given -5, operator- takes literal operand 5 and flips its sign to produce new output value -5.


Binary operators act on two operands (often called left and right, as the left operand appears on the left side of the operator, and the right operand appears on the right side of the operator). An example of a binary operator is the + operator. For example, given 3 + 4, operator+ takes the left operand 3 and the right operand 4 and applies mathematical addition to produce new output value 7. The insertion (<<) and extraction (>>) operators are binary operators, taking std::cout or std::cin on the left side, and the value to output or variable to input to on the right side.

Ternary operators act on three operands. There is only one of these in C++ (the conditional operator), which we’ll cover later.

Nullary operators act on zero operands. There is also only one of these in C++ (the throw operator), which we’ll also cover later.

Note that some operators have more than one meaning depending on how they are used. For example, operator- has two contexts. It can be used in unary form to invert a number’s sign (e.g. to convert 5 to -5, or vice versa), or it can be used in binary form to do subtraction (e.g. 4 - 3).

arithmetic operators execute in the same order as they do in standard mathematics: Parenthesis first, then Exponents, then Multiplication & Division, then Addition & Subtraction.

For the operators that we call primarily for their return values (e.g. operator+ or operator*), it’s usually obvious what their return values will be (e.g. the sum or product of the operands).

For the operators we call primarily for their side effects (e.g. operator= or operator<<), it’s not always obvious what return values they produce (if any). For example, what return value would you expect x = 5 to have?

Both operator= and operator<< (when used to output values to the console) return their left operand. Thus, x = 5 returns x, and std::cout << 5 returns std::cout. This is done so that these operators can be chained.

For example, x = y = 5 evaluates as x = (y = 5). First y = 5 assigns 5 to y. This operation then returns y, which can then be assigned to x.

std::cout << "Hello " << "world" evaluates as (std::cout << "Hello ") << "world!". This first prints "Hello " to the console. This operation returns std::cout, which can then be used to print "world!" to the console as well.

An expression is a combination of literals, variables, operators, and function calls that calculates a single value. The process of executing an expression is called evaluation, and the single value produced is called the result of the expression.

x = 5           // has side effect of assigning 5 to x, evaluates to x
x = 2 + 3       // has side effect of assigning 5 to x, evaluates to x
std::cout << x  // has side effect of printing x to console, evaluates to std::cout

std:: out returns itself, so do = assignments, this is why we can chain them

expressions are always evaluated as part of statements.

For example, take this statement:

int x{ 2 + 3 }; // 2 + 3 is an expression that has no semicolon -- the semicolon is at the end of the statement containing the expression
If you were to break this statement down into its syntax, it would look like this:

type identifier { expression };

type could be any valid type (we chose int). identifier could be any valid name (we chose x). And expression could be any valid expression (we chose 2 + 3, which uses two literals and an operator).

Certain expressions (like x = 5) are useful for their side effects (in this case, to assign the value 5 to the variable x). However, we mentioned above that expressions cannot be executed by themselves -- they must exist as part of a statement. So how can we use such expressions?

Fortunately, it’s easy to convert any expression into an equivalent statement. An expression statement is a statement that consists of an expression followed by a semicolon. When the expression statement is executed, the expression will be evaluated.

Thus, we can take any expression (such as x = 5), and turn it into an expression statement (x = 5;) that will compile.


When an expression is used in an expression statement, any return value generated by the expression is discarded (because it is not used).


Inline functions were originally designed as a way to request that the compiler replace your function call with inline expansion of the function code. You should not need to use the inline keyword for this purpose because the compiler will generally determine this for you. In modern C++, the inline keyword is used to exempt a function from the one-definition rule, allowing its definition to be imported into multiple code files. Inline functions are typically defined in header files so they can be #included into any code files that needs them.

When an assertion evaluates to false, your program is immediately stopped. This gives you an opportunity to use debugging tools to examine the state of your program and determine why the assertion failed. Working backwards, you can then find and fix the issue.
In C++, runtime assertions are implemented via the assert preprocessor macro, which lives in the <cassert> header.

To implement virtual functions, C++ implementations typically use a form of late binding known as the virtual table. The virtual table is a lookup table of functions used to resolve function calls in a dynamic/late binding manner. The virtual table sometimes goes by other names, such as “vtable”, “virtual function table”, “virtual method table”, or “dispatch table”.

The virtual table is actually quite simple, though it’s a little complex to describe in words. First, every class that uses virtual functions (or is derived from a class that uses virtual functions) is given its own virtual table. This table is simply a static array that the compiler sets up at compile time. A virtual table contains one entry for each virtual function that can be called by objects of the class. Each entry in this table is simply a function pointer that points to the most-derived function accessible by that class.

Second, the compiler also adds a hidden pointer that is a member of the base class, which we will call *__vptr. *__vptr is set (automatically) when a class object is created so that it points to the virtual table for that class. Unlike the *this pointer, which is actually a function parameter used by the compiler to resolve self-references, *__vptr is a real pointer. Consequently, it makes each class object allocated bigger by the size of one pointer. It also means that *__vptr is inherited by derived classes, which is important.

To address some common challenges with inheritance, C++ has two inheritance-related identifiers: override and final. Note that these identifiers are not keywords -- they are normal words that have special meaning only when used in certain contexts.
the override specifier can be applied to any virtual function by placing the override specifier after the function signature (the same place a function-level const specifier goes).
If the function does not override a base class function (or is applied to a non-virtual function), the compiler will flag the function as an error.
Use the virtual keyword on virtual functions in a base class. Use the override specifier (but not the virtual keyword) on override functions in derived classes.
There may be cases where you don’t want someone to be able to override a virtual function, or inherit from a class. The final specifier can be used to tell the compiler to enforce this. If the user tries to override a function or inherit from a class that has been specified as final, the compiler will give a compile error.

The process of building complex objects from simpler ones is called object composition. There are two types of object composition: composition, and aggregation.

Composition exists when a member of a class has a part-of relationship with the class. In a composition relationship, the class manages the existence of the members. To qualify as a composition, an object and a part must have the following relationship:

The part (member) is part of the object (class)
The part (member) can only belong to one object (class) at a time
The part (member) has its existence managed by the object (class)
The part (member) does not know about the existence of the object (class)
Compositions are typically implemented via normal member variables, or by pointers where the class manages all the memory allocation and deallocation. If you can implement a class as a composition, you should implement a class as a composition.

Aggregations exists when a class has a has-a relationship with the member. In an aggregation relationship, the class does not manage the existence of the members. To qualify as an aggregation, an object and its parts must have the following relationship:

The part (member) is part of the object (class)
The part (member) can belong to more than one object (class) at a time
The part (member) does not have its existence managed by the object (class)
The part (member) does not know about the existence of the object (class)
Aggregations are typically implemented via pointer or reference.


Associations are a looser type of relationship, where the class uses-an otherwise unrelated object. To qualify as an association, an object and an associated object must have the following relationship:

The associated object (member) is otherwise unrelated to the object (class)
The associated object (member) can belong to more than one object (class) at a time
The associated object (member) does not have its existence managed by the object (class)
The associated object (member) may or may not know about the existence of the object (class)
Associations may be implemented via pointer or reference, or by a more indirect means (such as holding the index or key of the associated object).

In a dependency, one class uses another class to perform a task. The dependent class typically is not a member of the class using it, but rather is temporarily created, used, and then destroyed, or passed into a member function from an external source.

A virtual function is a special type of function that resolves to the most-derived version of the function (called an override) that exists between the base and derived class. To be considered an override, the derived class function must have the same signature and return type as the virtual base class function. The one exception is for covariant return types, which allow an override to return a pointer or reference to a derived class if the base class function returns a pointer or reference to the base class.

An interface class is one with no member variables and all pure virtual functions. These are often named starting with a capital I.

When a derived class is assigned to a base class object, the base class only receives a copy of the base portion of the derived class. This is called object slicing.

Dynamic casting can be used to convert a pointer to a base class object into a pointer to a derived class object. This is called downcasting. A failed conversion will return a null pointer.

All template functions or classes must start with a template parameter declaration that tells the compiler that the following function or class is a template function or class. Within the template parameter declaration, the template type parameters or expression parameters are specified. Template type parameters are just placeholder types, normally named T, T1, T2, or other single letter names (e.g. S). Expression parameters are usually integral types, but can be a pointer or reference to a function, class object, or member function.

Splitting up template class definition and member function definitions doesn’t work like normal classes -- you can’t put your class definition in a header and member function definitions in a .cpp file. It’s usually best to keep all of them in a header file, with the member function definitions underneath the class.

Template specialization can be used when we want to override the default behavior from the templated function or class for a specific type. If all types are overridden, this is called full specialization. Classes also support partial specialization, where only some of the templated parameters are specialized. Functions can not be partially specialized.
A throw statement is used to raise an exception. Try blocks look for exceptions thrown by the code written or called within them. These exceptions get routed to catch blocks, which catch exceptions of particular types (if they match) and handle them. By default, an exception that is caught is considered handled.
Exceptions are handled immediately. If an exception is raised, control jumps to the nearest enclosing try block, looking for catch handlers that can handle the exception. If a matching try/catch is found, the stack is unwound to the point of the catch block, and control resumes at the top of the matching catch. If no try block is found or no catch blocks matches, the program calls std::terminate, which will terminate with an unhandled exception error.
Exceptions of any data type can be thrown, including classes.
Catch blocks can be configured to catch exceptions of a particular data type, or a catch-all handler can be set up by using the ellipses (…). A catch block catching a base class reference will also catch exceptions of a derived class. All of the exceptions thrown by the standard library are derived from the std::exception class (which lives in the exception header), so catching a std::exception by reference will catch all standard library exceptions. The what() member function can be used to determine what kind of std::exception was thrown.

Function try blocks give you a way to catch any exception that occurs within a function or an associated member initialization list. These are typically only used with derived class constructors.

You should never throw an exception from a destructor.
Unlike constructors, where throwing exceptions can be a useful way to indicate that object creation did not succeed, exceptions should never be thrown in destructors.
The problem occurs when an exception is thrown from a destructor during the stack unwinding process. If that happens, the compiler is put in a situation where it doesn’t know whether to continue the stack unwinding process or handle the new exception. The end result is that your program will be terminated immediately.
Consequently, the best course of action is just to abstain from using exceptions in destructors altogether. Write a message to a log file instead.

The noexcept exception specifier can be used to denote that a function is no-throw/no-fail.
Finally, exception handling does have a cost. In most cases, code using exceptions will run slightly slower, and the cost of handling an exception is very high. You should only use exceptions to handle exceptional circumstances, not for normal error handling cases (e.g. invalid input).

A smart pointer class is a composition class that is designed to manage dynamically allocated memory, and ensure that memory gets deleted when the smart pointer object goes out of scope.

Copy semantics allow our classes to be copied. This is done primarily via the copy constructor and copy assignment operator.

Move semantics mean a class will transfer ownership of the object rather than making a copy. This is done primarily via the move constructor and move assignment operator.

std::auto_ptr is deprecated and should be avoided.

An r-value reference is a reference that is designed to be initialized with an r-value. An r-value reference is created using a double ampersand. It’s fine to write functions that take r-value reference parameters, but you should almost never return an r-value reference.

If we construct an object or do an assignment where the argument is an l-value, the only thing we can reasonably do is copy the l-value. We can’t assume it’s safe to alter the l-value, because it may be used again later in the program. If we have an expression “a = b”, we wouldn’t reasonably expect b to be changed in any way.

However, if we construct an object or do an assignment where the argument is an r-value, then we know that r-value is just a temporary object of some kind. Instead of copying it (which can be expensive), we can simply transfer its resources (which is cheap) to the object we’re constructing or assigning. This is safe to do because the temporary will be destroyed at the end of the expression anyway, so we know it will never be used again!

You can use the delete keyword to disable copy semantics for classes you create by deleting the copy constructor and copy assignment operator.

std::move allows you to treat an l-value as r-value. This is useful when we want to invoke move semantics instead of copy semantics on an l-value.

std::move_if_noexcept will return a movable r-value if the object has a noexcept move constructor, otherwise it will return a copyable l-value. We can use the noexcept specifier in conjunction with std::move_if_noexcept to use move semantics only when a strong exception guarantee exists (and use copy semantics otherwise).

std::unique_ptr is the smart pointer class that you should probably be using. It manages a single non-shareable resource. std::make_unique() (in C++14) should be preferred to create new std::unique_ptr. std::unique_ptr disables copy semantics.

std::shared_ptr is the smart pointer class used when you need multiple objects accessing the same resource. The resource will not be destroyed until the last std::shared_ptr managing it is destroyed. std::make_shared() should be preferred to create new std::shared_ptr. With std::shared_ptr, copy semantics should be used to create additional std::shared_ptr pointing to the same object.

std::weak_ptr is the smart pointer class used when you need one or more objects with the ability to view and access a resource managed by a std::shared_ptr, but unlike std::shared_ptr, std::weak_ptr is not considered when determining whether the resource should be destroyed.

A static library (also known as an archive) consists of routines that are compiled and linked directly into your program. When you compile a program that uses a static library, all the functionality of the static library that your program uses becomes part of your executable. On Windows, static libraries typically have a .lib extension, whereas on Linux, static libraries typically have an .a (archive) extension. One advantage of static libraries is that you only have to distribute the executable in order for users to run your program. Because the library becomes part of your program, this ensures that the right version of the library is always used with your program. Also, because static libraries become part of your program, you can use them just like functionality you’ve written for your own program. On the downside, because a copy of the library becomes part of every executable that uses it, this can cause a lot of wasted space. Static libraries also can not be upgraded easy -- to update the library, the entire executable needs to be replaced.

A dynamic library (also called a shared library) consists of routines that are loaded into your application at run time. When you compile a program that uses a dynamic library, the library does not become part of your executable -- it remains as a separate unit. On Windows, dynamic libraries typically have a .dll (dynamic link library) extension, whereas on Linux, dynamic libraries typically have a .so (shared object) extension. One advantage of dynamic libraries is that many programs can share one copy, which saves space. Perhaps a bigger advantage is that the dynamic library can be upgraded to a newer version without replacing all of the executables that use it.

Because dynamic libraries are not linked into your program, programs using dynamic libraries must explicitly load and interface with the dynamic library. This mechanism can be confusing, and makes interfacing with a dynamic library awkward. To make dynamic libraries easier to use, an import library can be used.

Const: Whenever const keyword is attached with any method(), variable, pointer variable, and with the object of a class it prevents that specific object/method()/variable to modify its data items value.
Mutable: The mutable storage class specifier in C++ (or use of mutable keyword in C++) auto, register, static and extern are the storage class specifiers in C. typedef is also considered as a storage class specifier in C. C++ also supports all these storage class specifiers. In addition to this C++, adds one important storage class specifier whose name is mutable.
Explicit: In C++, the explicit keyword is used with a constructor to prevent it from performing implicit conversions. A C++ explicit constructor is marked to not convert types implicitly. This is extremely important as implicit conversions often lead to unexpected results.
Auto: The auto keyword in C++ automatically detects and assigns a data type to the variable with which it is used. The compiler analyses the variable's data type by looking at its initialization. It is necessary to initialize the variable when declaring it using the auto keyword.
Extern: The extern keyword in C and C++ extends the visibility of variables and functions across multiple source files. In the case of functions, the extern keyword is used implicitly. But with variables, you have to use the keyword explicitly.
Static: Static variables are initialized only once. Compiler persist the variable till the end of the program. Static variable can be defined inside or outside the function. They are local to the block. The default value of static variable is zero. The static variables are alive till the execution of the program.
Mutex: A mutex is a lockable object that is designed to signal when critical sections of code need exclusive access, preventing other threads with the same protection from executing concurrently and access the same memory locations.
Semaphore: Semaphores are just normal variables used to coordinate the activities of multiple processes in a computer system. They are used to enforce mutual exclusion, avoid race conditions and implement synchronization between processes. The process of using Semaphores provides two operations: wait (P) and signal (V). The wait operation decrements the value of the semaphore, and the signal operation increments the value of the semaphore.
Atomic: Consider a multithreaded program with one shared variable. Now, imagine that all the threads are trying to access and modify this shared variable at the same time. When multiple threads try to access the same variable concurrently, and at least one of them is a write operation, then this is known as a data race. Some data races can cause race conditions which are a problem. Race condition is an error caused by the ordering of events such that the correctness of a program is compromised. Not all data races lead to race conditions and not all race conditions are caused by data races. In order to solve this problem, C++ offers atomic variables that are thread-safe. They allow indivisible read, update and write operations on the shared variable without using mutexes (locks). Mutexes use software routines to lock and unlock operation/s, however, atomic variables utilise processor support through compare and swap instructions. In case of simple increments and decrements, atomic variables are significantly faster than locks.

Storage classes -> A storage class defines the scope (visibility) and life-time of variables and/or functions within a C++ Program. These specifiers precede the type that they modify. There are following storage classes, which can be used in a C++ Program

auto: The auto storage class is the default storage class for all local variables.
register: The register storage class is used to define local variables that should be stored in a register instead of RAM. This means that the variable has a maximum size equal to the register size (usually one word) and can't have the unary '&' operator applied to it (as it does not have a memory location). Used when we need quick access to something small like a counter
static: The static storage class instructs the compiler to keep a local variable in existence during the life-time of the program instead of creating and destroying it each time it comes into and goes out of scope. Therefore, making local variables static allows them to maintain their values between function calls. The static modifier may also be applied to global variables. When this is done, it causes that variable's scope to be restricted to the file in which it is declared.
extern: The extern storage class is used to give a reference of a global variable that is visible to ALL the program files. When you use 'extern' the variable cannot be initialized as all it does is point the variable name at a storage location that has been previously defined. When you have multiple files and you define a global variable or function, which will be used in other files also, then extern will be used in another file to give reference of defined variable or function. Just for understanding extern is used to declare a global variable or function in another file.
mutable: The mutable specifier applies only to class objects, which are discussed later in this tutorial. It allows a member of an object to override const member function. That is, a mutable member can be modified by a const member function.


Cohesion refers to what the class (or module) can do. Low cohesion would mean that the class does a great variety of actions - it is broad, unfocused on what it should do. High cohesion means that the class is focused on what it should be doing, i.e. only methods relating to the intention of the class.

Example of Low Cohesion:

-------------------
| Staff           |
-------------------
| checkEmail()    |
| sendEmail()     |
| emailValidate() |
| PrintLetter()   |
-------------------
Example of High Cohesion:

----------------------------
| Staff                   |
----------------------------
| -salary                 |
| -emailAddr              |
----------------------------
| setSalary(newSalary)    |
| getSalary()             |
| setEmailAddr(newEmail)  |
| getEmailAddr()          |
----------------------------
As for coupling, it refers to how related or dependent two classes/modules are toward each other. For low coupled classes, changing something major in one class should not affect the other. High coupling would make it difficult to change and maintain your code; since classes are closely knit together, making a change could require an entire system revamp.

Good software design has high cohesion and low coupling.

With few exceptions, place code in a namespace. Namespaces should have unique names based on the project name, and possibly its path. Do not use using-directives (e.g., using namespace foo). Do not use inline namespaces. For unnamed namespaces, see Internal Linkage.

A decent rule of thumb is to not inline a function if it is more than 10 lines long.

Beware of destructors, which are often longer than they appear because of implicit member- and base-destructor calls!

Another useful rule of thumb: it's typically not cost effective to inline functions with loops or switch statements (unless, in the common case, the loop or switch statement is never executed).

It is important to know that functions are not always inlined even if they are declared as such; for example, virtual and recursive functions are not normally inlined. Usually recursive functions should not be inline. The main reason for making a virtual function inline is to place its definition in the class, either for convenience or to document its behavior, e.g., for accessors and mutators.



Inline functions are commonly used when the function definitions are small, and the functions are called several times in a program. Using inline functions saves time to transfer the control of the program from the calling function to the definition of the called function. 

However, inlining a function is just a request or suggestion to the compiler, not any mandatory command. It depends on the compiler whether to accept or decline this suggestion of inlining a particular function. The compiler is most likely to not consider the inlining of a function under certain circumstances that are mentioned here as follows-

When a function with a return statement is not returning any value and marked as inline, the compiler does not respond to the programmer’s request of making it an inline function.
When a programmer tries to inline a function containing a loop (for, while, or do-while), the compiler refuses the inline suggestion.
When a function is recursive, it cannot be inlined.
A function containing static variables cannot be made an inline function. 
The compiler declines the request of inlining a function if it contains any switch or go-to statements.


Prefer placing nonmember functions in a namespace; use completely global functions rarely. Do not use a class simply to group static members. Static methods of a class should generally be closely related to instances of the class or the class's static data.



It's best to declare and initialise variables as close to first use as possible.



Variables needed for if, while and for statements should normally be declared within those statements, so that such variables are confined to those scopes. E.g.:

while (const char* p = strchr(str, '/')) str = p + 1;
There is one caveat: if the variable is an object, its constructor is invoked every time it enters scope and is created, and its destructor is invoked every time it goes out of scope.

// Inefficient implementation:
for (int i = 0; i < 1000000; ++i) {
  Foo f;  // My ctor and dtor get called 1000000 times each.
  f.DoSomething(i);
}
It may be more efficient to declare such a variable used in a loop outside that loop:

Foo f;  // My ctor and dtor get called once each.
for (int i = 0; i < 1000000; ++i) {
  f.DoSomething(i);
}

Objects with static storage duration are forbidden unless they are trivially destructible. Informally this means that the destructor does not do anything, even taking member and base destructors into account. More formally it means that the type has no user-defined or virtual destructor and that all bases and non-static members are trivially destructible. Static function-local variables may use dynamic initialization. Use of dynamic initialization for static class member variables or variables at namespace scope is discouraged, but allowed in limited circumstances; see below for details.

As a rule of thumb: a global variable satisfies these requirements if its declaration, considered in isolation, could be constexpr.



Every object has a storage duration, which correlates with its lifetime. Objects with static storage duration live from the point of their initialization until the end of the program. Such objects appear as variables at namespace scope ("global variables"), as static data members of classes, or as function-local variables that are declared with the static specifier. Function-local static variables are initialized when control first passes through their declaration; all other objects with static storage duration are initialized as part of program start-up. All objects with static storage duration are destroyed at program exit (which happens before unjoined threads are terminated).

Initialization may be dynamic, which means that something non-trivial happens during initialization. (For example, consider a constructor that allocates memory, or a variable that is initialized with the current process ID.) The other kind of initialization is static initialization. The two aren't quite opposites, though: static initialization always happens to objects with static storage duration (initializing the object either to a given constant or to a representation consisting of all bytes set to zero), whereas dynamic initialization happens after that, if required.



Global and static variables are very useful for a large number of applications: named constants, auxiliary data structures internal to some translation unit, command-line flags, logging, registration mechanisms, background infrastructure, etc.



Global and static variables that use dynamic initialization or have non-trivial destructors create complexity that can easily lead to hard-to-find bugs. Dynamic initialization is not ordered across translation units, and neither is destruction (except that destruction happens in reverse order of initialization). When one initialization refers to another variable with static storage duration, it is possible that this causes an object to be accessed before its lifetime has begun (or after its lifetime has ended). Moreover, when a program starts threads that are not joined at exit, those threads may attempt to access objects after their lifetime has ended if their destructor has already run.



Avoid virtual method calls in constructors, and avoid initialization that can fail if you can't signal an error.



Do not define implicit conversions. Use the explicit keyword for conversion operators and single-argument constructors.

The explicit keyword can be applied to a constructor or a conversion operator, to ensure that it can only be used when the destination type is explicit at the point of use, e.g., with a cast. This applies not only to implicit conversions, but to list initialization syntax:

class Foo {
  explicit Foo(int x, double y);
  ...
};

void Func(Foo f);
Func({42, 3.14});  // Error


A type should not be copyable/movable if the meaning of copying/moving is unclear to a casual user, or if it incurs unexpected costs. Move operations for copyable types are strictly a performance optimization and are a potential source of bugs and complexity, so avoid defining them unless they are significantly more efficient than the corresponding copy operations. If your type provides copy operations, it is recommended that you design your class so that the default implementation of those operations is correct. Remember to review the correctness of any defaulted operations as you would any other code.



In C++ programming, object slicing occurs when an object of a subclass type is copied to an object of superclass type: the superclass copy will not have any of the member variables or Member functions defined in the subclass. These variables and functions have, in effect, been "sliced off".

Object slicing can be prevented by making the base class function pure virtual thereby disallowing object creation. It is not possible to create the object of a class that contains a pure virtual method.

To eliminate the risk of slicing, prefer to make base classes abstract, by making their constructors protected, by declaring their destructors protected, or by giving them one or more pure virtual member functions. Prefer to avoid deriving from concrete classes.



Use a struct only for passive objects that carry data; everything else is a class.



Composition is often more appropriate than inheritance. When using inheritance, make it public.



"Interface inheritance" is inheritance from a pure abstract base class (one with no state or defined methods); all other inheritance is "implementation inheritance"

All inheritance should be public. If you want to do private inheritance, you should be including an instance of the base class as a member instead. You may use final on classes when you don't intend to support using them as base classes.

Do not overuse implementation inheritance. Composition is often more appropriate. Try to restrict use of inheritance to the "is-a" case: Bar subclasses Foo if it can reasonably be said that Bar "is a kind of" Foo.

Limit the use of protected to those member functions that might need to be accessed from subclasses. Note that data members should be private.

Explicitly annotate overrides of virtual functions or virtual destructors with exactly one of an override or (less frequently) final specifier. Do not use virtual when declaring an override. Rationale: A function or destructor marked override or final that is not an override of a base class virtual function will not compile, and this helps catch common errors. The specifiers serve as documentation; if no specifier is present, the reader has to check all ancestors of the class in question to determine if the function or destructor is virtual or not.

Multiple inheritance is permitted, but multiple implementation inheritance is strongly discouraged.



Specifying noexcept on a function can trigger compiler optimizations in environments where exceptions are enabled, e.g., compiler does not have to generate extra code for stack-unwinding, if it knows that no exceptions can be thrown due to a noexcept specifier.



Use constexpr to define true constants or to ensure constant initialization.

Some variables can be declared constexpr to indicate the variables are true constants, i.e., fixed at compilation/link time. Some functions and constructors can be declared constexpr which enables them to be used in defining a constexpr variable.

Use of constexpr enables definition of constants with floating-point expressions rather than just literals; definition of constants of user-defined types; and definition of constants with function calls.

Prematurely marking something as constexpr may cause migration problems if later on it has to be downgraded. Current restrictions on what is allowed in constexpr functions and constructors may invite obscure workarounds in these definitions.

constexpr definitions enable a more robust specification of the constant parts of an interface. Use constexpr to specify true constants and the functions that support their definitions. Avoid complexifying function definitions to enable their use with constexpr. Do not use constexpr to force inlining.



Referencing and Dereferencing of the Function Pointer in C++
Similar to the pointer used with variables we perform referencing and dereferencing with a function pointer.

Referencing: When pointer is allocated the address of the function to be associated with it then this process is referred to as referencing.

Dereferencing: When we use the (*)operator  to get the value stored in the pointer.

Syntax:

// Declaring
return_type (*FuncPtr) (parameter type, ....); 

// Referencing
FuncPtr= function_name;

// Dereferencing
data_type x=*FuncPtr;
Function pointer used to call the function
In this, we see how we point a pointer to a function and call it using that pointer. It is an efficient way to use 

Example:

C++
// C++ program to implementation
// Function Pointer
#include <iostream>
using namespace std;
 
int multiply(int a, int b) { return a * b; }
 
int main()
{
    int (*func)(int, int);
 
    // func is pointing to the multiplyTwoValues function
 
    func = multiply;
 
    int prod = func(15, 2);
    cout << "The value of the product is: " << prod << endl;
 
    return 0;
}

Output

The value of the product is: 30
In the above program, we are declaring a function multiply where we are multiplying two elements a and b, then returning the result. But, rather than directly calling the function we are using a function pointer prod which is doing the same work for us.

Passing a function pointer as a parameter
When declaring a function pointer to store the memory address of the function but, when we want to pass the return value to the next function. We have two methods to perform this task. First, either pass the value we got or second pass the function pointer that already exists.

Example:

C++
// C++ Program for demonstrating
// function pointer as pointer
#include <iostream>
using namespace std;
 
const int a = 15;
const int b = 2;
 
// Function for Multiplication
int multiply() { return a * b; }
 
// Function containing function pointer
// as parameter
void print(int (*funcptr)())
{
    cout << "The value of the product is: " << funcptr()
         << endl;
}
 
// Driver Function
int main()
{
    print(multiply);
    return 0;
}

Output

The value of the product is: 30


Static member functions in C++ are the functions that can access only the static data members. These static data members share a single copy of themselves with the different objects of the same class. A function can be made static by using the keyword static before the function name while defining a class.



Pure virtual functions must be implemented in child classes, non-pure virtual functions do not.



The size_t type is the unsigned integer type that is the result of the sizeof operator (and the offsetof operator), so it is guaranteed to be big enough to contain the size of the biggest object your system can handle (e.g., a static array of 8Gb).

The size_t type may be bigger than, equal to, or smaller than an unsigned int, and your compiler might make assumptions about it for optimization.

size_t is used in place of unsigned int sometimes as it is the max size regardless of whether your system is 64 or 32 bit.



uint64_t is guaranteed to be 64 bits. If you need 64 bits, you should use it.

size_t isn't guaranteed to be 64 bits; it could be 128 bits in a future machine. So, keyword uint_64 its reserved by that


 
In a statically typed language, such as C++ or Java for example, static may refer to the information known at compilation time while dynamic refers to the information known at runtime.

For example:

struct Base { virtual std::string name() const { return "Base"; } };

struct Derived: Base { std::string name() const { return "Derived"; } };

void print(Base const& b) { std::cout << b.name() << "\n"; }
In the print method, the static type of b is Base const&. Therefore, the compiler will check that all methods called exist in the context of a Base object.

However, when execution comes, the call to name, as the method is virtual, is performed with regard to the dynamic type of the object:

this may be Base
this may be Derived
this may be another derived class from Base that we know not yet
Therefore, in the following example:

int main(int argc, char* argv[]) {
  if (argc == 1) {
    Base base;
    print();
  } else {
    Derived derived;
    print(derived);
  }
};
The static and dynamic type of base is Base and derived is Derived.
In the print method, the static type of b is Base (always)
Depending on the number of arguments, the dynamic of b is either Base or Derived
It is a current mistake to assume that polymorphism is necessarily based on dynamic memory allocation, but the two concepts, while not orthogonal, can be used without one another in some conditions.

Whenever another shared_ptr is created that points to the same object, its reference count is incremented by 1. 
When a shared_ptr goes out of scope or is reset, its reference count is decremented by 1. When the reference count reaches 0, the managed object is deleted. 
std::shared_ptr is thread-safe in the sense that it can safely be accessed by multiple threads simultaneously. 
The reference count that shared_ptr uses to keep track of the number of references to the managed object is atomic, which means that it can be updated safely by multiple threads at the same time without causing race conditions or undefined behavior.
However, if multiple threads are accessing the same std::shared_ptr object without proper synchronization, there is indeed a risk of data corruption or other errors. To ensure safe concurrent access to the shared resource, proper synchronization mechanisms such as mutex locks or atomic operations must be employed. 
Otherwise, if not properly synchronized, concurrent access to the same std::shared_ptr object could lead to race conditions and data corruption.

The auto keyword in C++ automatically detects and assigns a data type to the variable with which it is used. The compiler analyses the variable's data type by looking at its initialization. It is necessary to initialize the variable when declaring it using the auto keyword.

The only problem with using the auto keyword is that constant variables will not be analyzed. If we want a variable to be constant and define it using the auto keyword, we will also have to use the keyword const along with the auto keyword. 

The auto keyword is also used as the return type for any function. The only condition is that each return statement inside this function should return the same variable type. The compiler decides the function's return type by analyzing the return statement expression. 

Like the auto keyword in C++, the auto&& keyword can be used as a universal reference value, which means it will accept any value, whether an lvalue or an rvalue reference expression. Let us look in detail at what this exactly means.

To recap, an lvalue expression is one whose resources cant be reused, like normal variables in C++ or any other objects that are declared using a name directly. 
For example, in the code int y = 7; 
y is an lvalue. Similarly, 
arr[0] is also an lvalue where
arr is a vector. These objects are such that they are declared with a name and are permanent.

But an rvalue expression denotes an object whose resources cannot be reused, which means a temporary disposable object. These objects are not declared or defined explicitly. For example, in the code func(class_obj()) where func() is a function that takes a class object as a parameter. It is clear in the code that we have not explicitly defined any class object. Instead, we have just passed the function class_obj() as a parameter which will create a temporary class object and pass it to the function func(). Hence, this class object is temporary, disposable, and an rvalue.

Now, to reference an lvalue object or variable, we have to use one & symbol, but to reference an rvalue object or variable, we have to use two ampersands &&. But, if we use the auto keyword to declare the reference, we can use auto&&, which will work for both lvalue and rvalue reference expressions.

Understanding std::string:
std::string is a versatile and widely used class in C++. It represents a sequence of characters and offers a rich set of member functions for string manipulation. It is part of the C++ Standard Library and provides dynamic memory management for the underlying string data. With std::string, you can easily modify, concatenate, compare, and perform various operations on strings.

Key Features of std::string:
1. Dynamic memory allocation: std::string manages memory internally, automatically handling the allocation and deallocation of memory required for storing the string data. This dynamic memory management simplifies string handling and eliminates the need for manual memory management.

2. Mutable operations: std::string allows you to modify its content directly. You can change characters, concatenate strings, replace substrings, and perform other mutable operations without limitations. This flexibility comes at the cost of potential performance overhead due to memory reallocation.

3. Wide range of member functions: std::string provides a rich interface of member functions, including find, substr, erase, insert, and more. These functions make it convenient to manipulate strings and perform complex operations with ease.

Understanding std::string_view:
Introduced in C++17, std::string_view is a lightweight alternative to std::string. It serves as a non-owning, read-only view of a string or a part of a string. Unlike std::string, it does not manage the underlying memory but instead provides a reference to an existing string. std::string_view is commonly used when you want to efficiently process and operate on strings without modifying them.

Key Features of std::string_view:
1. Non-owning view: std::string_view does not own the string data; it merely provides a view or reference to an existing string. This makes it suitable for scenarios where you need to access or process strings without the overhead of memory allocation or reallocation.

2. Lightweight and efficient: Since std::string_view does not manage memory, it has a minimal memory footprint. Assigning or copying a string_view is fast and inexpensive because it involves only copying the reference, length, and start position of the string.

3. Immutable operations: std::string_view offers a subset of the member functions provided by std::string, primarily focused on read-only operations. While you can access characters and perform searches, you cannot modify the content of a string_view. This immutability ensures the safety of operations and guarantees that the viewed string remains unaltered.

Choosing the Right Tool for the Job:
When deciding whether to use std::string or std::string_view, consider the following guidelines:

1. Ownership: If you need to modify the string or manage the memory explicitly, std::string is the appropriate choice. It provides flexibility, extensive functionality, and is suitable for scenarios where dynamic changes to the string are required.

2. Performance and efficiency: If your use case revolves around read-only access to strings, or you need a lightweight and efficient solution, std::string_view is the preferred option. It avoids unnecessary memory allocations and provides a convenient way to operate on string data without copying or modifying it.

3. Compatibility: std::string_view is particularly useful when dealing with legacy code or external interfaces that return strings as null-terminated character arrays or other string-like objects. It allows you to efficiently work with these existing data structures without the need for conversion or additional memory allocation.

std::move is used to indicate that an object t may be "moved from", i.e. allowing the efficient transfer of resources from t to another object.

Resource Acquisition Is Initialization or RAII, is a C++ programming technique[1][2] which binds the life cycle of a resource that must be acquired before use (allocated heap memory, thread of execution, open socket, open file, locked mutex, disk space, database connection—anything that exists in limited supply) to the lifetime of an object.

RAII guarantees that the resource is available to any function that may access the object (resource availability is a class invariant, eliminating redundant runtime tests). It also guarantees that all resources are released when the lifetime of their controlling object ends, in reverse order of acquisition. Likewise, if resource acquisition fails (the constructor exits with an exception), all resources acquired by every fully-constructed member and base subobject are released in reverse order of initialization. This leverages the core language features (object lifetime, scope exit, order of initialization and stack unwinding) to eliminate resource leaks and guarantee exception safety. Another name for this technique is Scope-Bound Resource Management (SBRM), after the basic use case where the lifetime of an RAII object ends due to scope exit.

RAII can be summarized as follows:

encapsulate each resource into a class, where
the constructor acquires the resource and establishes all class invariants or throws an exception if that cannot be done,
the destructor releases the resource and never throws exceptions;
always use the resource via an instance of a RAII-class that either
has automatic storage duration or temporary lifetime itself, or
has lifetime that is bounded by the lifetime of an automatic or temporary object.
Move semantics make it possible to safely transfer resource ownership between objects, across scopes, and in and out of threads, while maintaining resource safety.
RAII makes it so library classes manage their own resources, like std::string, vector etc...



Variables:
static variables exist for the "lifetime" of the translation unit that it's defined in, and:

If it's in a namespace scope (i.e. outside of functions and classes), then it can't be accessed from any other translation unit. This is known as "internal linkage" or "static storage duration". (Don't do this in headers except for constexpr. Anything else, and you end up with a separate variable in each translation unit, which is crazy confusing)
If it's a variable in a function, it can't be accessed from outside of the function, just like any other local variable. (this is the local they mentioned)
class members have no restricted scope due to static, but can be addressed from the class as well as an instance (like std::string::npos). [Note: you can declare static members in a class, but they should usually still be defined in a translation unit (cpp file), and as such, there's only one per class]
locations as code:

static std::string namespaceScope = "Hello";
void foo() {
    static std::string functionScope= "World";
}
struct A {
   static std::string classScope = "!";
};
Before any function in a translation unit is executed (possibly after main began execution), the variables with static storage duration (namespace scope) in that translation unit will be "constant initialized" (to constexpr where possible, or zero otherwise), and then non-locals are "dynamically initialized" properly in the order they are defined in the translation unit (for things like std::string="HI"; that aren't constexpr). Finally, function-local statics will be initialized the first time execution "reaches" the line where they are declared. All static variables all destroyed in the reverse order of initialization.

The easiest way to get all this right is to make all static variables that are not constexpr initialized into function static locals, which makes sure all of your statics/globals are initialized properly when you try to use them no matter what, thus preventing the static initialization order fiasco.

T& get_global() {
    static T global = initial_value();
    return global;
}
Be careful, because when the spec says namespace-scope variables have "static storage duration" by default, they mean the "lifetime of the translation unit" bit, but that does not mean it can't be accessed outside of the file.

Functions
Significantly more straightforward, static is often used as a class member function, and only very rarely used for a free-standing function.

A static member function differs from a regular member function in that it can be called without an instance of a class, and since it has no instance, it cannot access non-static members of the class. Static variables are useful when you want to have a function for a class that definitely absolutely does not refer to any instance members, or for managing static member variables.

struct A {
    A() {++A_count;}
    A(const A&) {++A_count;}
    A(A&&) {++A_count;}
    ~A() {--A_count;}

    static int get_count() {return A_count;}
private:
    static int A_count;
}

int main() {
    A var;

    int c0 = var.get_count(); //some compilers give a warning, but it's ok.
    int c1 = A::get_count(); //normal way
}
A static free-function means that the function will not be referred to by any other translation unit, and thus the linker can ignore it entirely. This has a small number of purposes:

Can be used in a cpp file to guarantee that the function is never used from any other file.
Can be put in a header and every file will have it's own copy of the function. Not useful, since inline does pretty much the same thing.
Speeds up link time by reducing work
Can put a function with the same name in each translation unit, and they can all do different things. For instance, you could put a static void log(const char*) {} in each cpp file, and they could each all log in a different way.

what the output of the following code is:

struct A {
    int data[2];
    A(int x, int y) { data[0] = x; data[1] = y; }

    virtual void f() {}
};

int main(){
    A a(22, 33);
    int* data = (int*)&a;
    cout << data[2] << endl;
}
I talked through it but couldn't figure it out exactly. He mentioned that the virtual function was a hint. Afterwards I compiled it and got the output:

22
I then thought about the virtual function and removed it:

struct A {
    int data[2];
    A(int x, int y) { data[0] = x; data[1] = y; }

    //virtual void f() {}
};

int main(){
    A a(22, 33);
    int* data = (int*)&a;
    cout << data[2] << endl;
}
Resulting in the ouput:

0

Adding 1 or more virtual methods to a class causes (in this case 1) an object instance of that class to contain a hidden pointer to a compiler-managed "virtual method table" (vtable) at the front of the object's memory, eg:

int *data = &a;     A a;
   data -> --------------------
           | vtable           | -> [0]: &A::f
           | (8 bytes)        |
           |------------------|
data[2] -> | data[0]: 22      |
           |------------------|
           | data[1]: 33      |
           --------------------
Assuming sizeof(int) is 4 (which is usually the case), being able to access the object's data[0] member via an int* pointer to the object, where that pointer is indexing the 3rd int, tells us that there is an extra 8 bytes present at the front of the object, which can be accounted for by the vtable pointer, if the code is being compiling as 64bit (if it were compiled as 32bit instead, the vtable pointer would be 4 bytes, and data[2] would be accessing A::data[1] = 33).

Without any virtual methods, there is no vtable present, so the extra 8 bytes are not present, and thus indexing to the 3rd int from the front of the object will exceed past the bounds of the object into surrounding memory, eg:

int *data = &a;     A a;
   data -> --------------------
           | data[0]: 22      |
           |------------------|
           | data[1]: 33      |
           --------------------
data[2] -> 

Because the class doesn't have any other virtual functions, adding a virtual function adds a pointer to the class. The pointer points to a vtable, unique to that class.

The pointer might be the size of an int, but it might not. On a 64 bit system, it is typically twice the size of an int. But it doesn't have to be.

The pointer might be at the beginning of the class's memory layout, but it might not. The beginning is a common location, but popular commercial C++ compilers will sometimes place it elsewhere.

size of the struct or class is the sum of its member data, in the order that they're stated, plus extra bits of padding added for alignment (memory fetched in 8 bytes)
Functions do not occupy space in the object for the same reason static member variables do not occupy object space. There only needs to exist one instance of the function, used by all object instances.
 If a structure has virtual functions then it implicitly includes a pointer to the table of virtual function pointers as a data member for each object of the structure type.

For every class that contains virtual functions, the compiler constructs a virtual table, a.k.a vtable. The vtable contains an entry for each virtual function accessible by the class and stores a pointer to its definition. Only the most specific function definition callable by the class is stored in the vtable. Entries in the vtable can point to either functions declared in the class itself (e.g. C::bar()), or virtual functions inherited from a base class (e.g. C::qux()).
The vtable of class B has two entries, one for each of the two virtual functions declared in B’s scope: bar() and qux(). Additionally, the vtable of B points to the local definition of functions, since they are the most specific (and only) from B’s point of view.

More interesting is C’s vtable. In this case, the entry for bar() points to own C’s implementation, given that it is more specific than B::bar(). Since C doesn’t override qux(), its entry in the vtable points to B’s definition (the most specific definition).

Note that vtables exist at the class level, meaning there exists a single vtable per class, and is shared by all instances.
Every time the compiler creates a vtable for a class, it adds an extra argument to it: a pointer to the corresponding virtual table, called the vpointer.

In C++, the size of a struct or class is primarily determined by the size of its data members and any padding added for memory alignment. However, it’s essential to note that various factors, including the introduction of virtual functions, can influence this size. In the following example, we demonstrate how you can use this feature to visualize the impact of these factors, including the presence of a hidden vptr, on the size of a class.

Non-static data members of a (non-union) class with the same access control are allocated so that later members have higher addresses within a class object. The order of allocation of non-static data members with different access control is unspecified. Implementation alignment requirements might cause two adjacent members not to be allocated immediately after each other; so might requirements for space for managing virtual functions and virtual base classes.
If a pointer to the base class is assigned a derived object, it can only see the subobject part. It can be deemed as an object slicing.

Objects of Derived are laid out by simply stacking the Base subobject on the data member of its own.

To solve the Diamond Inheritance Problem, C++ introduces the virtual inheritance mechanism to guarantee only one copy of virtually inherited bases under the diamond hierarchy. 
To keep only one virtual base in the derived object, a class can be spliced into two parts, the virtual base subobject, which will be shared in the diamond inheritance case, and the other parts. The virtual base is accessed through a virtual table pointer either.

Virtual functions are slightly more expensive than a regular function, so if you’re trying to make an ultra low-latency program, this section is important. Calling a virtual function involves dereferencing the vtable pointer which is an extra lookup that regular functions don’t have to do.

The other thing is that compiler optimizations like inlining can’t be run on virtual function. Inlining is when function code is copied and pasted where a function is called which avoids the creation of a stack frame, pushing arguments on the stack, etc. This can’t be done with virtual functions because the function that’s being run is only determined at run time. These are very small performance hits, but worth knowing.
You might also be wondering where are all the functions are being stored in memory. All function instructions are stored in a special place in memory once, and not per object. When things are compiled, those function calls will point to the location of the function instructions.

TCP is a communication protocol through which data packets are transmitted over a network. It includes error-checking, guarantees the delivery, and preserves the order of the data packets. UDP is the same as TCP, except this doesn’t have error-checking and does not ensure or maintain the data packets’ order. For example, you are sending a message to your friend on a new chatting platform. Imagine you are sending a statement: “Good morning Jake.” In the case of the TCP protocol, the message sent to your friend would be “Good morning Jake,” but in the case of UDP, the message may be sent as “Morning Jake Good” (a lot of combinations).
TCP is a connection-oriented protocol, but UDP is a connection-less protocol. What does this mean? It means TCP does not send the data when there is no connection with the server. Imagine a lot of users are sending data on the server at the same time. The network is congested, and the server cannot take the load. In TCP, if a connection is made to the server (usually the server accepts the connection), the data is sent. In UDP, no connection is required, which means if the server is too congested, it will receive data through the UDP protocol. Gosh, UDP seems ruthless in these cases, and yes, it is brutal.
The data packets transferred in TCP are in sequence that I explained in the first point. The data packets in UDP are not in sequence, and the application layer of the OSI needs to handle the sequence of the data packets.
TCP is much more reliable than UDP since TCP provides error checking support and guarantees data delivery to the destination. In contrast, UDP provides only fundamental error checking support.
