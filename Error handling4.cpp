# include <iostream>

// std::exception subclasses:
// bad_alloc -> when a memory allocation fails
// bas_cast -> when a dynamic_cast fails
// logic_error -> parent class for faults from faulty logic
// runtime_error -> parent class for error conditions beyond th eprogrammers control

// c++ streams do not throw exceptions by default, the programmer can ussually deal with error conditions by checking the stream state
// exceptions can be optionally enabled, but teh resulting code is usually more complex
// c++ STL makes little use of exceptions due to efficiency, checking for exceptions and handling them requires extr work, in some applications teh overhead may not be acceptable

// when an exception is thrown, the destructor is called for all local veriables in the current scope
// when a destructor throws an exception, if the exception is handled by a catch block in the destructor, this is safe
// if the exception is not handled by the destructor, a stack unwind will ensue
// if another exception is being processed, there could be two concurrent stack unwind operations
// this results in undefined behaviour

// destructors should never throw exceptions, if code in a destructor does throw, it must be hanled by the destructor, this is usually not a problem as destructors should only release resources

// if an unhandled exception is thrown during a constructor call, the partially initalized object is destroyed, aswell as its data members and its parent part if its a child object
// as far as the rest of the program is concerned, an object does not exist until its constructor has successfully completed

// an exception thrown in a constructor should be left for teh caller to handle, the caller will then know the object has not been successfully created
// the constructor should only handle the exception if it can solve the problem and continue initializing the object
// if we allow the caller to handle the exception, there's either no exception and a successfully created object or an exception is thrown and there is no object
// this way, we have no half initialzed objects left over, as would happen if the constructor handled the error

// constructors can also throw exceptions to report errors to the caller, which is useful because constructors do not have return values

// we can write our own exception classes, usually it is best to derive it from one of the std::exception subclasses, as we have an existing interface and can inherit code etc...
// do not derive directly from std::exception, it has default constructor only can no provision for passing custom error messages

// exception safety means that code behaves correctly when exceptions are thrown, all our programs should be exception safe!

// three main ways to write exception safe code:
// basic exception guarantee: if an exception is thrown during an operation, no resrouces are leaksed, any memory allocated is released, any files opened are closed
// strong exception guarantee: if an exeption is thrown, the program reverts to its previous state: as if the operation had not happened
// no-throw guarantee: the code does not throw any exceptions


// the basic exception guaraentee provides the minimum level of exception safety, an operation will either succeed or throw an exception, if it throws an exception, no resources will be leaked
// all the operations and functions in the c++ standard library provide this basic guarantee

// the strong exception guarantee states that an operation will either succeed or have no effect, if an exception is thrown, the program will be left in the same state as it was before the operation
// the operation has transactional semantics, similar to commit and rollback in databases
// all iterators and referenced obtained before the operation remain valid, all operations on STL containers provide the strong exception guarantee (except some special case insert operations)

// the no-throw guarantee means that an operation will not thrown an exception, when writing code that provides the basic or strong guarantees, it is helpful to know that a sub-operation will not throw
// none of the functions and operators in the core c++ language and library throw exceptions, apart from new, dynamic_cast and throw

// c++11 has the noexcept keyword, if an exception is thrown, the program terminates immediately
// noexcept is a promise to the caller that the function will not throw an exception, noexcept functions provide the no-throw guarantee
// this is helpful if we are writing exceptionsafe code which calls the function
// noexcept helps the compiler generate better optimised code, gives compiler more information about how the code behaves and compiler is not required to generate code for stack unwinding
// modern c++ has optimized versions of some operators, these are not intrinsically exception-safe, STL algos will only use these operators if they are delcared noexcept, otherwose they will call the non-optimised versions which are slower
//  noexcept should be used wherever possible, if we are certain a function will not throw any exceptions, or we cannot do anything useful if an exception is thrown e.g. destructors
// you cant use noexcept to pverload a function, a function is either noexcept or it is not, its a part of the functions type
// noexceptness is inherited, a child class can add noexcept to an inherited function but cannot remove it
// the compiler will assume a class's destructor sis noexcept if all members of the class have a noexcept destructor, or all parent classes ahve a noexcept destructor

// the c++ std library provides an std::swap function, this exchanges the data in its arguments
// std::swap() is declared noexcept, it offers the no throw guarantee
// swap is a generic function, it copies its arguments, there are overloads for some library types that atke advangtage pf thier internal structure
// when we write a class, we can overload swap() for that class, this i sworth doing is the class is expensive to copy and its objects can be swapped (by sorteing a container etc...)

// with RAII, the contructor and copy constructor automatically provide the strong exception guarantee
// the destructor automatically provides the no-throw guarantee
// the assignment operator, if implemented carefully, also offers the string guarantee


int main(){



}