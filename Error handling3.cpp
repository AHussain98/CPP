# include <iostream>
# include <vector>

// when an exception is thrown, several things happen:
// the thrown object is copied into a special area of memory, this area is set up by the compiler, it is accessible by any catch block that can handle the object type
// every local variable in scope is destroyed, including the original thrown object, the program immdediately leaves this scope and does not execute any further instructions in the scope
// the program will look for a catch block that can handle teh exception, if it cannot find one, it will immediately destroy all local variables and exit the current scope, it then looks in the enclosing scope
// this continues until it finds a suitable handler, if it reaches main() without finding one, the programme calls std::terminate()
// this process of repeatedly destroying local variables and exiting the current scope is known as stack unwinding
// when a suitable handler is found, the program executes the code in it and continues, normally it will proceed to teh next instruction after the try/catch block and continue executing from there
// however the handler can rethrow the exception (this means the exception can possibly become live again), in this case, the exception will be handled again, but in a handler belongin to another try/catch block

// to rethrow the same exception object, use the throw keyword with no argument, if we give an argument, it will throw a copy of that object
// since the exception is thrown outside of the current try block, the program will regard this as a new exception and a fresh process of stack unwinding begins
//


void func(const std::vector<int>& vec){
    try{
        std::cout << vec.at(2) << std::endl; // throws an exception
    }
    catch (const std::out_of_range& e){  // handler for the out of range exception
        std::cout<< "abandoning operation due to exception: " << e.what() << std::endl; // print out a description of the exception
       throw; // no args so throws std::out_of_range(e), because this is thrown out of the current try block, the program will look for onother catch block in the current scope, there isnt one, so it will look in the scope of the function caller
        // the "throw" exception will by caught due to us using polymorphism in the catch block below, by passing by reference, so even though its a std::exception object, the what function is polmorphic and so the derived explanation is shown
     //  throw std::exception(e); // if we do this instead, a generic explanation will be shown by out of scope catch block below, we've converted the out of range exception to the generic exception
    }
}


int main(){

std::vector<int> vec;
try{
    func(vec);
}
catch (const std::exception& s){  // the exception thrown by the throw keyword in func() is caught by this catch block outside its scope
    std::cout << "call to func failed due to: " << s.what() << std::endl;

}

}

// c++ defines an std::exception class, this is the base class for an inheritance hierarchy, consistent interface for exception objects and enables polymorphism, reduces number of handlers needed
// a logic error represents something that is under the control of the programmer e.g. violating a precondition
// a logic error could be prevented by the programmer e.g. checking fucntion arguments before processing them
// a runtime error represents something that is beyond the programmers direct control, e.g. running out of memory

// std::exception base class defines 5 public member functions: constructor, copy cinstructor, assignment operator, virtual member function what() and virtual destructor
// what() returns a c-style string, what() cannot throw an exception


