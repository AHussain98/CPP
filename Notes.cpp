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

Struct is different from a class because its members are public by default, and the default access specifiers are public when deriving a struct from a class/struct.

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
inline fucntions?
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
