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






